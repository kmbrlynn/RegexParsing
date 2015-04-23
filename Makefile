CC = g++ -std=c++0x
CFLAGS = -Wall -Werror -ansi -pedantic -g

all: ps7a

ps7a: RegexParsing.o
	$(CC) $(FLAGS) -o ps7a RegexParsing.o -lboost_regex -lboost_date_time

# ==============================================================================
RegexParsing.o: RegexParsing.cpp Regex.cpp Regex.hpp
	$(CC) $(FLAGS) -c RegexParsing.cpp

clean:
	rm -rf ps7a *.o *.~ #*.rpt

