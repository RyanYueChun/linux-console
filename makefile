linux_console: main.o folder.o
	g++ main.o folder.o -o linux_console

main.o: main.cpp
	g++ -c main.cpp

folder.o: folder.cpp
	g++ -c folder.cpp

clean:
	rm *.o linux_console