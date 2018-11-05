all:
	g++ -Wall -lpthread -Ofast -frename-registers -funroll-loops -O3 *.cpp

debug:
	g++ -Wall -g *.cpp
