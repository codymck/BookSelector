BookSelector: ReadList.o
	g++ -c ReadList.cpp
	g++ -o BookSelector ReadList.o

clean:
	rm *.o BookSelector