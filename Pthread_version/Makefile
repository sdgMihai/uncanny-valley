CC = g++
FLAGS = --std=c++17 -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable #-g
LIBRARY = -lm -lpthread
CC_FOLDER = build

UTILS = ../utils

FILTERS_SER = $(CC_FOLDER)/black-white_filter_pthread.o $(CC_FOLDER)/canny-edge-detection_filter_pthread.o $(CC_FOLDER)/contrast_filter_pthread.o \
				$(CC_FOLDER)/dummy_filter_pthread.o $(CC_FOLDER)/edge-tracking_filter_pthread.o $(CC_FOLDER)/emboss_filter_pthread.o \
				$(CC_FOLDER)/brightness_pthread.o $(CC_FOLDER)/double-treshold_pthread.o $(CC_FOLDER)/gaussian-blur_filter_pthread.o \
				$(CC_FOLDER)/non-maximum-suppression_filter_pthread.o $(CC_FOLDER)/sepia_filter_pthread.o $(CC_FOLDER)/sharpen_filter_pthread.o \
				$(CC_FOLDER)/gradient_pthread.o

build: pthread_version #pthread_version_assert

pthread_version: main_pthread.cpp $(CC_FOLDER)/lodepng.o $(FILTERS_SER)
	$(CC) $(FLAGS) $^ -o $@ $(LIBRARY)

pthread_version_assert: main_pthread.cpp $(HEADER_FILES) $(CC_FOLDER)/lodepng.o $(FILTERS_SER)
	$(CC) $(FLAGS) -DASSERT_ENABLE $^ -o $@ $(LIBRARY)

$(CC_FOLDER)/brightness_pthread.o: ./filters/brightness_filter_pthread.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/gradient_pthread.o: ./filters/gradient_filter_pthread.cpp 
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/double-treshold_pthread.o: ./filters/double-treshold_filter_pthread.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/black-white_filter_pthread.o: ./filters/black-white_filter_pthread.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/canny-edge-detection_filter_pthread.o: ./filters/canny-edge-detection_filter_pthread.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/contrast_filter_pthread.o: ./filters/contrast_filter_pthread.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/dummy_filter_pthread.o: ./filters/dummy_filter_pthread.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/edge-tracking_filter_pthread.o: ./filters/edge-tracking_filter_pthread.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/emboss_filter_pthread.o: ./filters/emboss_filter_pthread.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/gaussian-blur_filter_pthread.o: ./filters/gaussian-blur_filter_pthread.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/non-maximum-suppression_filter_pthread.o: ./filters/non-maximum-suppression_filter_pthread.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/sepia_filter_pthread.o: ./filters/sepia_filter_pthread.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/sharpen_filter_pthread.o: ./filters/sharpen_filter_pthread.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/lodepng.o: ../third-party/lodepng.cpp
	$(CC) $(FLAGS) -O3 $^ -C -c -o $@

clean:
	rm -rf pthread_version pthread_version_assert build/*
