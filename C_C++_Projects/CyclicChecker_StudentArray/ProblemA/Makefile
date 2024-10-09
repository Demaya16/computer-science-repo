all: check_cycle

check_cycle: ll_cycle.o test_ll_cycle.o
	gcc -Wall -Wextra -Wpedantic ll_cycle.o test_ll_cycle.o -o check_cycle

ll_cycle.o: ll_cycle.c
	gcc -Wall -Wextra -Wpedantic -c ll_cycle.c

test_ll_cycle.o: test_ll_cycle.c
	gcc -Wall -Wextra -Wpedantic -c test_ll_cycle.c

clean:
	trm -f *.o check_cycle

