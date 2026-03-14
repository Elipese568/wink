all: wink

wink: main.o
	g++ -o $@.out $^

%.o: %.cpp
	gcc -c -o $@ $<
