if [ $# -lt 1 ]; then
	printf "USAGE\n \
		./launch.sh x; for atxmega\n\
		./launch.sh o <argument>; for odroid\n\
		./lanuch.sh a; for both\n\
		./lanuch.sh t; for touch to fix clock skew\n"
fi
	 
# prevents clock skew issues
if [ "$1" = t ]; then
	find -exec touch \{\} \;
fi

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
	./io $2
fi

if [ "$1" = cx -o "$1" = ca ]; then
	cd atxmega/build
	make clean
	cd ../..
fi

if [ "$1" = co -o "$1" = ca ]; then
	cd odroid/build
	make clean
fi
