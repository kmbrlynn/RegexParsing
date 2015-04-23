# Copyright 2015 Kim Douglas
#
# 	note: Regex.hpp and Regex.cpp are not needed
# 	for ps7a. However, I will abstract things further
# 	for ps7b, so this Makefile is structured as such.

CC = g++ -std=c++0x
CFLAGS = -Wall -Werror -ansi -pedantic -g

all: ps7a

ps7a: RegexParsing.o Regex.o
	$(CC) $(FLAGS) -o ps7a RegexParsing.o Regex.o -lboost_regex -lboost_date_time

RegexParsing.o: RegexParsing.cpp Regex.cpp Regex.hpp
	$(CC) $(FLAGS) -c RegexParsing.cpp

Regex.o: RegexParsing.cpp Regex.hpp
	$(CC) $(FLAGS) -c Regex.cpp

clean:
	rm -rf ps7a *.o *.~ #*.rpt

