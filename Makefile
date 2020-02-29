
kmeans_app:	main.o	utils.o	kmeans.o
	g++ -o kmeans_app main.o utils.o kmeans.o

utils.o:	utils.cpp
	g++ -c utils.cpp

kmeans.o:	kmeans.cpp
	g++ -c kmeans.cpp

main.o:	main.cpp
	g++ -c main.cpp

clean:
	rm kmeans_app main.o utils.o kmeans.o output.txt
