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
    if (rank == MASTER) {
        for (int tid = 1; tid < numtasks; ++tid) {
            int start = chunk * tid;
            int end = std::min(chunk * (tid + 1) + 1, (int)image->height);  // [ast last index]
            end += (end != (int)image->height ? 1 : 0);  // past last index

            for(int i = start; i < end; ++i) {
                MPI_Send(image->matrix[i], image->width * sizeof(Pixel), MPI_UNSIGNED_CHAR, tid, 0, MPI_COMM_WORLD);
            }
        }
    } else {
        for(unsigned int i = 0; i < image->height; ++i) {
            MPI_Recv(image->matrix[i], image->width * sizeof(Pixel), MPI_UNSIGNED_CHAR, MASTER, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
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
    if (rank == MASTER) {
        for (int tid = 1; tid < numtasks; ++tid) {
            int start = chunk * tid + 1;
            int end = std::min(chunk * (tid + 1) + 1, (int)image->height - 1);
            for(int i = start; i < end; ++i) {
                MPI_Recv(image->matrix[i], image->width * sizeof(Pixel), MPI_UNSIGNED_CHAR, tid, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
        }
    } else {
        for(unsigned int i = 1; i < image->height - 1; ++i) {
            MPI_Send(image->matrix[i], image->width * sizeof(Pixel), MPI_UNSIGNED_CHAR, MASTER, 0, MPI_COMM_WORLD);
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
    newImage = new Image((*image)->width - 2, (*image)->height - 2);

    if(rank == MASTER) {
        old_img_h = (*image)->height;
        set_img_proc_limits(*image, rank, chunk, old_img_h);
        set_img_proc_limits(newImage, rank, chunk, old_img_h);
    }

    for (int i = 0; i < n; ++i) {
        std::string f = filters[i];
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
                  << " \n - double-threshold \n - edge-tracking"
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


    if (rank != MASTER) {
        int start = chunk * rank;  // row index of upper padd
        int end = std::min(chunk * (rank + 1), (int)buff[0] - 1);  // row index of last line or padd
        end += (end != (int)buff[0] - 1 ? 1 : 0);  // row index of lower padd
        int no_rows = end - start + 1;

        image = new Image(buff[1] - 2, no_rows - 2);
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
