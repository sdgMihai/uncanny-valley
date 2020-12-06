#include <iostream>
#include <math.h>

#define OMPI_SKIP_MPICXX 1
#include "mpi.h"
#include "../utils/imageIO.h"
#include "../utils/image.h"
#include "../utils/filter.h"
#include "../utils/filter_factory.h"

#define MASTER 0

 /**
 * trimite fiecarui thread un chunk de linii, acelasi pt orice thread
 * (mai putin pt ultimul, care ia ce ramane)
 * @param image referinta catre imagine
 * @param rank id-ul procesului care cheama functia
 * @param chunk cate linii vor fi trimise in afara de liniile de padding
 */
void commLines(Image *image, int rank, int numtasks, int chunk) {
    // TODO I assume the number of cores << number of rows
    int time_start = -1;
    int time_stop = 0;
    if (rank == MASTER) {
        for (int tid = 1; tid < numtasks; ++tid) {
            int start = chunk * tid;
            int end = std::min(chunk * (tid + 1) + 1, (int)image->height);  // [ast last index]
            end += (end != (int)image->height ? 1 : 0);  // past last index
            fflush(stdout);
            printf("\nsending to tid %d start %d end %d no of rows %d\n", tid, start, end -1,  end - start);

            for(int i = start; i < end; ++i) {
                time_start = MPI_Wtime();
                MPI_Send(image->matrix[i], image->width * sizeof(Pixel), MPI_UNSIGNED_CHAR, tid, 0, MPI_COMM_WORLD);
                time_stop = MPI_Wtime();
                // printf("time send no %d -> %d\n", tid + i - start - 1, time_stop - time_start);
            }
            printf("end sending to tid %d\n", tid);
            fflush(stdout);
        }
    } else {
        for(unsigned int i = 0; i < image->height; ++i) {
            int time_start = MPI_Wtime();
            MPI_Recv(image->matrix[i], image->width * sizeof(Pixel), MPI_UNSIGNED_CHAR, MASTER, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            int time_stop = MPI_Wtime();
            if (rank == 3)
                printf("time recv in r:%d, no:%u -> %d\n", rank, i, time_stop - time_start);
        }
        printf("rank  %d received all lines\n", rank);
    }
}

 /**
 * trimite fiecarui thread un chunk de linii, acelasi pt orice thread
 * (mai putin pt ultimul, care ia ce ramane)
 * @param image referinta catre imagine
 * @param rank id-ul procesului care cheama functia
 * @param chunk cate linii vor fi trimise in afara de liniile de padding
 */
void retrieveLines(Image *image, int rank, int numtasks, int chunk) {
    // TODO I assume the number of cores << number of rows
    if (rank == MASTER) {
        for (int tid = 1; tid < numtasks; ++tid) {
            int start = chunk * tid + 1;
            int end = std::min(chunk * (tid + 1) + 1, (int)image->height - 1);
            printf("master recv start %d end %d\n", start, end);
            for(int i = start; i < end; ++i) {
                if (start == 475) {
                    printf("recv %d\n", i);
                }
                MPI_Recv(image->matrix[i], image->width * sizeof(Pixel), MPI_UNSIGNED_CHAR, tid, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
            puts("end recv");
        }
    } else {
        if (rank == 3) {
            printf("send width: %u\n", image->width);
        }
        for(unsigned int i = 1; i < image->height - 1; ++i) {
            if (rank == 3) {
                printf("send %d\n", i);
            }
            MPI_Send(image->matrix[i], image->width * sizeof(Pixel), MPI_UNSIGNED_CHAR, MASTER, 0, MPI_COMM_WORLD);
        }
        if (rank == 3) {
            puts("end send");
        }
    }
}

void set_img_proc_limits(Image *image, int rank, int chunk, unsigned int old_img_h) {
    image->height = std::min(chunk * (rank + 1) + 1, (int)old_img_h);
    if (image->height != old_img_h) {
        image->height++;
    }
}

/**
 * aplica filtrele pe imaginea primita
 * @param image referita catre imagine
 * @param filters lista de filtre ce trebuie aplicata
 * @param n numarul de filtre
 * @param rank id procesului care ruleaza functia
 * @return imaginea obtinuta in urma aplicarii filtrelor
 */
Image* processImage(Image **image, char **filters, int n, int rank, int numstasks, int chunk) {
    Filter *filter;
    Image *newImage;
    Image *aux;
    unsigned int old_img_h;

    commLines(*image, rank, numstasks, chunk);
    printf("chunk: %d\n", chunk);
    newImage = new Image((*image)->width - 2, (*image)->height - 2);

    if(rank == MASTER) {
        old_img_h = (*image)->height;
        set_img_proc_limits(*image, rank, chunk, old_img_h);
        set_img_proc_limits(newImage, rank, chunk, old_img_h);
    }
    printf("in rank %d image height:%u image width:%u", rank, (*image)->height, (*image)->width);

    for (int i = 0; i < n; ++i) {
        std::string f = filters[i];
        printf("filter rank:%d\n", rank);
        std::cout << "Filtrul: " << f << '\n';

        filter = FilterFactory::filterCreate(f);
        filter->applyFilter(*image, newImage);
        delete filter;

        if (i == (n - 1)) {
            break;
        } 

        aux = *image;
        *image = newImage;
        newImage = aux;
    }

    if(rank == MASTER) {
        (*image)->height = old_img_h;
        newImage->height = old_img_h;
    }
    printf("get here rank %d\n", rank);
    retrieveLines(newImage, rank, numstasks, chunk);

    return newImage;
}


int main(int argc, char *argv[])
{
    Image *image, *newImage;
    int numtasks, rank, chunk;
    int buff[2];

    if(argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <file_in> <file_out> [f1, f2, ..., fn]\n\n";
        exit(EXIT_FAILURE);
    }

    /*  init mpi and time*/
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    if (argc == 3) {
        /**
         * OBS:
         * la filtrul: non-maximum-suppression, daca vem sa rulam doar pe el
         * va treb ui sa furnizam acei parametrii, deci zic sa renuntam
         * in a rula doar acest filtru 
         */
        std::cout << "No filter/s provided.\n";
        std::cout << "Filters: \n - sharpen \n - emboss \n - sepia \n - contrast \n"
                  << " - brightness \n - black-white \n - gaussian-blur \n"
                  << " - non-maximum-suppression \n - double-threshold \n - edge-tracking"
                  << "\n - canny-edge-detection \n\n";
        return 0;
    }

    if (rank == MASTER) {
        std::string fileIn = argv[1];
        image = ImageIo::imageRead(fileIn);
        buff[0] = image->height;
        buff[1] = image->width;
    }
	MPI_Bcast(buff, 2, MPI_INT, MASTER, MPI_COMM_WORLD);
    chunk = ceil(((float)(buff[0] - 2)) / numtasks);  // chunk of rows
    printf("rank:%d buff[0]:%d buff[1]%d with chunk %d\n", rank, buff[0], buff[1], chunk);


    if (rank != MASTER) {
        int start = chunk * rank;  // row index of upper padd
        int end = std::min(chunk * (rank + 1), (int)buff[0] - 1);  // row index of last line or padd
        end += (end != (int)buff[0] - 1 ? 1 : 0);  // row index of lower padd
        int no_rows = end - start + 1;
        printf("start %d end %d no rows %d\n", start, end, no_rows);

        image = new Image(buff[1] - 2, no_rows - 2);
        printf("rank %d height %u width %u\n", rank, image->height, image->width);
    }
    
    newImage = processImage(&image, (char **)&argv[3], argc - 3, rank, numtasks, chunk);

    if (rank == MASTER) {
        std::string fileOut = argv[2];
	    ImageIo::imageWrite(fileOut, newImage);
    }
	

    delete image;
    delete newImage;
    MPI_Finalize();

    return 0;
}
