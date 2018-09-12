myPower: power.o test.o
	gcc -o myPower power.o test.o
power.o: power.c
	gcc -Werror -Wall -std=gnu99 -pedantic -c power.c
test.o: test-power.c power.c
	gcc -Werror -Wall -std=gnu99 -pedantic -c test-power.c -o test.o
