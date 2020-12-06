PARALLEL_BUILD=&

build: serial openmp mpi #pthread

mpi: MPI_version/Makefile
	cd MPI_version && mkdir -p build && make && cd .. && \
	cp MPI_version/mpi_version mpi.exe $(PARALLEL_BUILD)

pthread: Pthread_version/Makefile
	cd Pthread_version && mkdir -p build && make && cd .. && \
	cp Pthread_version/pthread_version pthread.exe $(PARALLEL_BUILD)

serial: Serial_version/Makefile
	cd Serial_version && mkdir -p build && make && cd .. && \
	cp Serial_version/ser_version serial.exe $(PARALLEL_BUILD)

openmp: OpenMP_version/Makefile
	cd OpenMP_version && mkdir -p build && make && cd .. && \
	cp OpenMP_version/openMP_version openmp.exe $(PARALLEL_BUILD)

clean:
	rm -rf serial.exe openmp.exe pthread.exe mpi.exe && \
	cd OpenMP_version && make clean && cd .. && \
	cd Serial_version && make clean && cd .. && \
	cd Pthread_version && make clean && cd .. &&\
	cd MPI_version && make clean && cd ..
