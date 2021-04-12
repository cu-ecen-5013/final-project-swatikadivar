#AUTOMAKE_OPTIONS = foreign
#CFLAGS = -Wall -pedantic
#bin_PROGRAMS = socketserver
#socketserver_SOURCES = socketserver.c


# the compiler: gcc for C program, define as g++ for C++
ifeq ($(CC),)
	CC = $(CROSS_COMPILE)gcc
endif

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
ifeq ($(CFLAGS),)
	CFLAGS  = -g -Wall -Werror
endif

ifeq ($(LDFLAGS),)
	LDFLAGS = -pthread -lrt
endif

socketserver: socketserver.c
	$(CC) $(CFLAGS) -o socketserver socketserver.c $(LDFLAGS)

gpio: gpio.c
	$(CC) $(CFLAGS) -o gpio gpio.c $(LDFLAGS)

all: socketserver gpio

.PHONY: all

clean:
	\rm socketserver gpio
	$(RM) $(TARGET) 
