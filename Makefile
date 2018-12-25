#Set compiler and compiler flags
CC = gcc
CFLAGS = -std=c99

all: duffing_euler duffing_rk4 duffing_ab2

duffing_euler: duffing.o euler.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

duffing_rk4: duffing.o rk4.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

duffing_ab2: duffing.o ab2.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

duffing.o: duffing.c integrator.h
	$(CC) $(CFLAGS) -c $<

euler.o: euler.c integrator.h
	$(CC) $(CFLAGS) -c $<

rk4.o: rk4.c integrator.h
	$(CC) $(CFLAGS) -c $<

ab2.o: ab2.c integrator.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm duffing_* *.o
