CC=gcc
CFLAGS=-Wall

default: all

all: daytime_client

daytime_client: daytime_client.cpp
	$(CC) $(CFLAGS) -o daytime_client daytime_client.cpp

clean:
	rm -f daytime_client
