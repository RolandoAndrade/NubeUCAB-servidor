all:
	g++ -c main.cpp -o main.o
	g++ main.o -o nuserver
	rm main.o

clean:
	rm nuserver
