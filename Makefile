	
	CC=gcc
	
	
	all: collect	
	
	collect: main.o curl.o parse.o
	$(CC) -o collect main.o curl.o -lcurl parse.o
	
	
	
	main.o: main.c
	$(CC) -c main.c
	
	
	curl.o: curl.c
	$(CC) -c curl.c 
	
	
	parse.o: parse.c
	$(CC) -c parse.c
	
	clean:
	rm -rf *.o collect