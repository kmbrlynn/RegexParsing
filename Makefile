CC = g++
CFLAGS = -Wall -Werror -ansi -pedantic -g

all: ps7a

ps7a: RegexParsing.o
	$(CC) $(FLAGS) -o ps7a RegexParsing.o -lboost_regex

# ==============================================================================
RegexParsing.o: RegexParsing.cpp Regex.cpp Regex.hpp
	$(CC) $(FLAGS) -c RegexParsing.cpp

clean:
	rm -rf ps7a *.o *.~

