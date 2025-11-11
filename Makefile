CFLAGS=-c -g -Wall -Werror
CC=gcc

all: signal_handler signal_alarm signal_segfault signal_sigaction send_signal recv_signal server receiver

signal_handler: signal_handler.o
	$(CC) -o signal_handler signal_handler.o

signal_alarm: signal_alarm.o
	$(CC) -o signal_alarm signal_alarm.o

signal_segfault: signal_segfault.o
	$(CC) -o signal_segfault signal_segfault.o

signal_sigaction: signal_sigaction.o
	$(CC) -o signal_sigaction signal_sigaction.o

send_signal: send_signal.o
	$(CC) -o send_signal send_signal.o

recv_signal: recv_signal.o
	$(CC) -o recv_signal recv_signal.o

server: server.o
	$(CC) -o server server.o

receiver: receiver.o
	$(CC) -o receiver receiver.o

clean:
	rm -f *.o signal_handler signal_alarm signal_segfault signal_sigaction send_signal recv_signal server receiver

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $<
