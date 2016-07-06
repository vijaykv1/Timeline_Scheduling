#######################################################################
#Description  Makefile
#Authors      Varun Vijaykumar
#Date 	      12 June 2016
########################################################################
CC = gcc
HEADERS = timeline.h
SOURCES= timeline.c
CFLAGS = -std=c99 -Wall -lm -o

bin = timeline

$(bin) : $(HEADERS) $(SOURCES)
	$(CC) $(SOURCES) $(CFLAGS) $@

clean:
	rm -vrf $(bin)
