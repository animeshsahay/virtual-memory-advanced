CC=g++

CFLAGS = -std=c++11

makepart1:
	$(CC) $(CFLAGS) assign1part1.cpp -o assign1part1
	./assign1part1 part1sequence
makepart2:
	$(CC) $(CFLAGS) assign1part2.cpp pagetable.cpp phyframes.cpp -o assign1part2
	./assign1part2 part2sequence
makepart3:
	$(CC) $(CFLAGS) assign1part3.cpp pagetable.cpp phyframes.cpp -o assign1
	./assign1 128 4096 2048 part2sequence		
