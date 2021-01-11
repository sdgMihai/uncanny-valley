CC = g++
FLAGS = --std=c++17 -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable #-ggdb
LIBRARY = -lm
CC_FOLDER = build

UTILS = ../utils

FILTERS_SER = $(CC_FOLDER)/black-white_filter.o $(CC_FOLDER)/canny-edge-detection_filter.o $(CC_FOLDER)/contrast_filter.o \
				$(CC_FOLDER)/dummy_filter.o $(CC_FOLDER)/edge-tracking_filter.o $(CC_FOLDER)/emboss_filter.o \
				$(CC_FOLDER)/brightness.o $(CC_FOLDER)/double-treshold.o $(CC_FOLDER)/gaussian-blur_filter.o \
				$(CC_FOLDER)/non-maximum-suppression_filter.o $(CC_FOLDER)/sepia_filter.o $(CC_FOLDER)/sharpen_filter.o \
				$(CC_FOLDER)/gradient.o

build: ser_version #ser_version_assert

ser_version: main_serial.cpp $(CC_FOLDER)/lodepng.o $(FILTERS_SER)
	$(CC) $(FLAGS) $^ -o $@ $(LIBRARY)

ser_version_assert: main_serial.cpp $(HEADER_FILES) $(CC_FOLDER)/lodepng.o $(FILTERS_SER)
	$(CC) $(FLAGS) -DASSERT_ENABLE $^ -o $@ $(LIBRARY)

$(CC_FOLDER)/brightness.o: ./filters/brightness_filter.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/gradient.o: ./filters/gradient_filter.cpp
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

$(CC_FOLDER)/non-maximum-suppression_filter.o: ./filters/non-maximum-suppression_filter.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/sepia_filter.o: ./filters/sepia_filter.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/sharpen_filter.o: ./filters/sharpen_filter.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/lodepng.o: ../third-party/lodepng.cpp
	$(CC) $(FLAGS) -O3 $^ -C -c -o $@

clean:
	rm -rf ser_version ser_version_assert build/*
