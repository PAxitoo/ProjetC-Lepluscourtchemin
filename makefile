all: projet projet

%: %.cc
	g++ -std=c++11 $< -o $@

%: %.c
	gcc -std=c99 $< -o $@

