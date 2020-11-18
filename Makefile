CC = g++
FLAGS = -Wall #-g
LIBRARY = 

build: ser_version

ser_version: main.cpp ./third-party/lodepng.cpp
	# $(CC) $(FLAGS) $^ -o $@ $(LIBRARY)
	$(CC) $(FLAGS) -DASSERT_ENABLE $^ -o $@ $(LIBRARY)

clean:
	rm -f ser_version *.o
