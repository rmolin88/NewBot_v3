#include <atomic>
#include <chrono>
#include <deque>
#include <iostream>
#include <mutex>
#include <future>
#include <thread>


// shared stuff:
std::deque<std::packaged_task<void()>> tasks;
std::mutex tasks_mutex;
std::atomic<bool> gui_running;


void message()
{
   std::cout << std::this_thread::get_id() << std::endl;
}


void one_off()
{
    std::packaged_task<void()> task(message);
    std::future<void> result = task.get_future();

    {
        std::lock_guard<std::mutex> lock(tasks_mutex);
        tasks.push_back(std::move(task));
    }

    // wait on result
    result.get();
}


void gui_thread()
{
    std::cout << "gui thread: "; message();

    while (gui_running) {
        // process messages
        {
            std::unique_lock<std::mutex> lock(tasks_mutex);
            while (!tasks.empty()) {
                auto task(std::move(tasks.front()));
                tasks.pop_front();

                // unlock during the task
                lock.unlock();
                task();
                lock.lock();
            }
        }

        // "do gui work"
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}


int main()
{
    gui_running = true;

    std::cout << "main thread: "; message();
    std::thread gt(gui_thread);

    for (unsigned i = 0; i < 5; ++i) {
        // note:
        // these will be launched sequentially because result's
        // destructor will block until one_off completes
        auto result = std::async(std::launch::async, one_off);

        // maybe do something with result if it is not void
    }

    // the for loop will not complete until all the tasks have been
    // processed by gui_thread

    // ...

    // cleanup
    gui_running = false;
    gt.join();
}
