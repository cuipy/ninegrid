


shudu:main.o fullnine.o
	g++ -o shudu main.o fullnine.o
	
main.o:main.cc fullnine.h
	g++ -c main.cc fullnine.h -o main.o
	
fullnine.o:fullnine.cc fullnine.h
	g++ -c fullnine.h fullnine.cc -o fullnine.o
	

