#ifndef MPI_DATA_H
#define MPI_DATA_H

class my_t_data{
public:
    int rank;
    int numtasks;
    int chunk;
    my_t_data(int rank, int numtasks, int chunk) : rank(rank), numtasks(numtasks), chunk(chunk){}
};
#endif /* MPI_DATA_H */
