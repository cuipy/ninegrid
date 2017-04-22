


shudu:main.o fullnine.o
	g++ -o shudu main.o fullnine.o -I.
	
main.o:main.cc fullnine.h
	g++ -c main.cc fullnine.h -o main.o -I.
	
fullnine.o:fullnine.cc fullnine.h
	g++ -c fullnine.h fullnine.cc -o fullnine.o -I.
	

