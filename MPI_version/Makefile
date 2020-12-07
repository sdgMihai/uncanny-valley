CC = mpic++
FLAGS = -Wall -Wextra -Wno-unused-parameter -ggdb
LIBRARY = -lm
CC_FOLDER = build

FILTERS_MPI = $(CC_FOLDER)/black-white_filter.o $(CC_FOLDER)/canny-edge-detection_filter.o $(CC_FOLDER)/contrast_filter.o \
				$(CC_FOLDER)/dummy_filter.o $(CC_FOLDER)/edge-tracking_filter.o $(CC_FOLDER)/emboss_filter.o \
				$(CC_FOLDER)/brightness.o $(CC_FOLDER)/double-treshold.o $(CC_FOLDER)/gaussian-blur_filter.o \
				$(CC_FOLDER)/non-maximum-suppression_filter.o $(CC_FOLDER)/sepia_filter.o $(CC_FOLDER)/sharpen_filter.o \
				$(CC_FOLDER)/gradient.o

build: mpi_version

mpi_version: main_MPI.cpp $(CC_FOLDER)/lodepng.o $(FILTERS_MPI)
	$(CC) $(FLAGS) -DASSERT_ENABLE $^ -o $@ $(LIBRARY)

$(CC_FOLDER)/brightness.o: ./filters/brightness_filter_MPI.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/gradient.o: ./filters/gradient_filter_MPI.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/double-treshold.o: ./filters/double-treshold_filter_MPI.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/black-white_filter.o: ./filters/black-white_filter_MPI.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/canny-edge-detection_filter.o: ./filters/canny-edge-detection_filter_MPI.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/contrast_filter.o: ./filters/contrast_filter_MPI.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/dummy_filter.o: ./filters/dummy_filter_MPI.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/edge-tracking_filter.o: ./filters/edge-tracking_filter_MPI.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/emboss_filter.o: ./filters/emboss_filter_MPI.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/gaussian-blur_filter.o: ./filters/gaussian-blur_filter_MPI.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/non-maximum-suppression_filter.o: ./filters/non-maximum-suppression_filter_MPI.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/sepia_filter.o: ./filters/sepia_filter_MPI.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/sharpen_filter.o: ./filters/sharpen_filter_MPI.cpp
	$(CC) $(FLAGS) $^ -c -o $@

$(CC_FOLDER)/lodepng.o: ../third-party/lodepng.cpp
	$(CC) $(FLAGS) -O3 $^ -C -c -o $@

run:
	mpirun -np $(no_threads) ./mpi_version $(in) $(out) $(filter)

clean:
	rm -rf mpi_version build/*
