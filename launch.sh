#! /bin/bash

if [ $# -lt 1 ]; then

	printf "USAGE\n \
		To launch the software use\n\
		\t./launch.sh x; for atxmega\n\
		\t./launch.sh o <arguments>; for odroid\n\
		\t./launch.sh r <arguments>; for remote\n\
		\t./lanuch.sh a <arguments>; for odroid and atxmega\n\
		To fix clock skew\n\
		\t./launch.sh t\n
		To clean builds\n\
		\t./launch.sh cx; for atxmega\n\
		\t./launch.sh co; for odroid\n\
		\t./launch.sh cr; for remote\n\
		\t./lanuch.sh ca; for all\n
		To do a git commit\n\
			\t./launch.sh g \"comment\"\n"
	exit 8
fi
	 
# prevents clock skew issues
if [ "$1" = t ]; then
	find -exec touch \{\} \;
	exit 0
fi

# git commit require
if [ "$1" = g ]; then
	if [ "$#" -ne 2 ]; then
		printf "Surround git comments in quotes\n\
			\ti.e: ./launch.sh g \"my comment\"\n"
		exit
	fi
	git add .
	git commit -m "$2"
	git push origin master
	exit 0
fi

# TODO:Separate make and launch
# make and launch atxmega code
if [ "$1" = x -o "$1" = a ]; then
	cd atxmega/build
	make clean &&
	make all && 
	sudo dfu-programmer atxmega128a4u erase &&
	sudo dfu-programmer atxmega128a4u flash atxmega.hex &&
	sudo dfu-programmer atxmega128a4u start
	cd ../..
fi
# make and launch odroid code
if [ "$1" = o -o "$1" = a ]; then
	cd odroid/build
	make clean &&
	make all && 
	./odroid.out $2 $3
fi
# make and launch remote code
if [ "$1" = r ]; then
	cd remote/build
	make clean &&
	make all && 
	./remote.out
fi

if [ "$1" = cx -o "$1" = ca ]; then
	cd atxmega/build
	make clean
	cd ../..
fi

if [ "$1" = co -o "$1" = ca ]; then
	cd odroid/build
	make clean
	cd ../..
fi

if [ "$1" = cr -o "$1" = ca ]; then
	cd remote/build
	make clean
fi
exit $? # exit with exit status of last command 
