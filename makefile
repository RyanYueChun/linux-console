linux_console: main.o folder.o filePlan.o
	g++ main.o folder.o filePlan.o -o linux_console

main.o: main.cpp
	g++ -c main.cpp

folder.o: folder.cpp
	g++ -c folder.cpp

filePlan.o: filePlan.cpp
	g++ -c filePlan.cpp

clean:
	rm *.o linux_console