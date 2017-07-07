krammer: src/*.cpp src/*.h
	g++ src/krammer.cpp -o bin/krammer

clean:
	rm bin/krammer
