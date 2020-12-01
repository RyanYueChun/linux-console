linux_console: main.o folder.o filePlan.o file.o
	g++ main.o folder.o filePlan.o file.o -o linux_console

main.o: main.cpp
	g++ -c main.cpp

folder.o: folder.cpp
	g++ -c folder.cpp

filePlan.o: filePlan.cpp
	g++ -c filePlan.cpp

file.o: file.cpp
	g++ -c file.cpp

clean:
	rm *.o linux_console