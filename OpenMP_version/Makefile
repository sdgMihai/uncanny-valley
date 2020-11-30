CC = g++
FLAGS = -Wall -Wextra -Wno-unused-parameter -fopenmp #-g
LIBRARY = -lm
CC_FOLDER = build

FILTERS_OPENMP = $(CC_FOLDER)/dummy_filter_openMP.o $(CC_FOLDER)/black-white_filter_openMP.o $(CC_FOLDER)/brightness_filter_openMP.o   \
              $(CC_FOLDER)/contrast_filter_openMP.o $(CC_FOLDER)/double-treshold_filter_openMP.o $(CC_FOLDER)/edge-tracking_filter_openMP.o \
              $(CC_FOLDER)/emboss_filter_openMP.o $(CC_FOLDER)/gaussian-blur_filter_openMP.o $(CC_FOLDER)/gradient_filter_openMP.o \
              $(CC_FOLDER)/non-maximum-suppression_filter_openMP.o $(CC_FOLDER)/sepia_filter_openMP.o $(CC_FOLDER)/sharpen_filter_openMP.o \
              $(CC_FOLDER)/canny-edge-detection_filter_openMP.o

build: openMP_version

openMP_version: main_openMP.cpp $(CC_FOLDER)/lodepng.o $(FILTERS_OPENMP)
	$(CC) $(FLAGS) -DASSERT_ENABLE $^ -o $@ $(LIBRARY)

$(CC_FOLDER)/black-white_filter_openMP.o: ./filters/black-white_filter_openMP.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/brightness_filter_openMP.o: ./filters/brightness_filter_openMP.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/contrast_filter_openMP.o: ./filters/contrast_filter_openMP.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/double-treshold_filter_openMP.o: ./filters/double-treshold_filter_openMP.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/edge-tracking_filter_openMP.o: ./filters/edge-tracking_filter_openMP.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/emboss_filter_openMP.o: ./filters/emboss_filter_openMP.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/gaussian-blur_filter_openMP.o: ./filters/gaussian-blur_filter_openMP.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/gradient_filter_openMP.o: ./filters/gradient_filter_openMP.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/non-maximum-suppression_filter_openMP.o: ./filters/non-maximum-suppression_filter_openMP.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/sepia_filter_openMP.o: ./filters/sepia_filter_openMP.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/sharpen_filter_openMP.o: ./filters/sharpen_filter_openMP.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/canny-edge-detection_filter_openMP.o: ./filters/canny-edge-detection_filter_openMP.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/dummy_filter_openMP.o: ./filters/dummy_filter_openMP.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/lodepng.o: ../third-party/lodepng.cpp
	$(CC) $(FLAGS) -O3 $^ -C -c -o $@

clean:
	rm -rf openMP_version build/*
