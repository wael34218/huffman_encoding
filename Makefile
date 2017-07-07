CC=g++

CFLAGS=-c -Wall
prefix=/usr/local
    
install: krammer
	install -m 0755 ./bin/krammer $(prefix)/bin

uninstall:
	rm -f $(prefix)/bin/krammer

krammer: src/*.cpp src/*.h
	$(CC) src/krammer.cpp -o bin/krammer

clean:
	rm bin/krammer
