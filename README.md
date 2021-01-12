# Canny Edge Detection and other filters

The project tackles the application of image filters in three different
parallelization methods (OpenMP, MPI, PThreads). The project applies the
following filters on PNG images:
    1. Canny Edge Detection
    2. Sepia
    3. Sharpen
    4. Contrast
    5. Brightness
    6. Emboss
    7. Gaussian-blur
    8. Double-threshold
    9. Black-white
    10. Edge-detection

The last 4 filters are used by Canny Edge, but can be used independently if
needed.

#### To compile just run `make` and the Makefile will build all available
#### versions. You will have to provide your own images to test the program.

##### To run the program use the following format:
##### `/foo.exe file_in file_out [filter_1, filter_2, ..., filter_n]`
# Authors
```
Mihai Gheoace
Cezar Craciunoiu
Adrian Stefan
```
