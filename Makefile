CC = g++
FLAGS = -Wall -Wextra -Wno-unused-parameter #-g
LIBRARY = 
CC_FOLDER = build

FILTERS_SER = $(CC_FOLDER)/black-white_filter.o $(CC_FOLDER)/canny-edge-detection_filter.o $(CC_FOLDER)/contrast_filter.o \
				$(CC_FOLDER)/dummy_filter.o $(CC_FOLDER)/edge-tracking_filter.o $(CC_FOLDER)/emboss_filter.o \
				$(CC_FOLDER)/brightness.o $(CC_FOLDER)/double-treshold.o $(CC_FOLDER)/gaussian-blur_filter.o \
				$(CC_FOLDER)/non-maximum-suppression_filter.o $(CC_FOLDER)/sepia_filter.o $(CC_FOLDER)/sharpen_filter.o

build: ser_version

ser_version: main.cpp $(CC_FOLDER)/lodepng.o $(FILTERS_SER)
	$(CC) $(FLAGS) -DASSERT_ENABLE $^ -o $@ $(LIBRARY)

$(CC_FOLDER)/brightness.o: ./filters/brightness_filter.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/double-treshold.o: ./filters/double-treshold_filter.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/black-white_filter.o: ./filters/black-white_filter.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/canny-edge-detection_filter.o: ./filters/canny-edge-detection_filter.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/contrast_filter.o: ./filters/contrast_filter.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/dummy_filter.o: ./filters/dummy_filter.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/edge-tracking_filter.o: ./filters/edge-tracking_filter.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/emboss_filter.o: ./filters/emboss_filter.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/gaussian-blur_filter.o: ./filters/gaussian-blur_filter.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/non-maximum-suppression_filter.o: ./filters/non-maximum-supression_filter.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/sepia_filter.o: ./filters/sepia_filter.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/sharpen_filter.o: ./filters/sharpen_filter.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/lodepng.o: ./third-party/lodepng.cpp
	$(CC) $(FLAGS) -O3 $^ -C -c -o $@

clean:
	rm -rf build/*
