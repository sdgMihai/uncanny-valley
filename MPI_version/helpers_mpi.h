#ifndef HELPERS_MPI_H
#define HELPERS_MPI_H
#include "../utils/image.h"

#define OMPI_SKIP_MPICXX 1
#include "mpi.h"

#define MASTER 0

inline void updateLines(Image *image, int rank, int numtasks, int chunk) {
    // TODO IF need optimisation CREATE DIFFERENT COMMUNICATORS
    if (rank != MASTER){
        MPI_Send(image->matrix[1], image->width * sizeof(Pixel), MPI_UNSIGNED_CHAR, rank - 1, 0, MPI_COMM_WORLD);
        MPI_Recv(image->matrix[0], image->width * sizeof(Pixel), MPI_UNSIGNED_CHAR, rank - 1, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    if (rank != numtasks - 1){
        MPI_Recv(image->matrix[image->height - 1], image->width * sizeof(Pixel), MPI_UNSIGNED_CHAR, rank + 1, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Send(image->matrix[image->height - 2], image->width * sizeof(Pixel), MPI_UNSIGNED_CHAR, rank + 1, 0, MPI_COMM_WORLD);
    }
}

#endif /* HELPERS_MPI_H */