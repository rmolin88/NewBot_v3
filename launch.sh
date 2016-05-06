# prevents clock skew issues
find -exec touch \{\} \;
# make and launch odroid code
cd ~/Documents/NewRobot/odroid
make clean &&
make all && 
# make and launch atxmega code
cd ../atxmega/build && 
make clean &&
make all && 
sudo dfu-programmer atxmega128a4u erase &&
sudo dfu-programmer atxmega128a4u flash atxmega.hex &&
sudo dfu-programmer atxmega128a4u start &&
cd ~/Documents/NewRobot/odroid
./io
