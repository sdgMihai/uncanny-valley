#include <iostream>
#include <string>

#include "../utils/image.h"
#include "../utils/imageIO.h"
#include "../utils/filter.h"
#include "../utils/filter_factory.h"
#include "helpers_pthread.h"

#define CONTRAST "contrast"
#define BRIGHTNESS "brightness"

typedef struct {
    Image *image, *newImage;
    thread_specific_data_t thread_data;
    const char **argv;
    int argc;
} thread_data_t;

/**
 * OBS:
 * Daca vrem varianta propusa de Cesar mai multe imagini 
 * cu mai multe filtre pe imagini (dar eu cred ca cel mai ok ar fi 
 * sa aplicam mai multe filtre pe o singura imagine, deoarece
 * scopul nostru este sa paralelizam algoritmi de filtare
 * nu sa procesam mai multe imagini de-odata) ar trebui sa avem un input
 * in cmd:
 * Usage: ./exec <nr_imagini> <image1> <n1> <f11> <f12>...<f1n1>
 *               <image2> <n2> <f21> <f22>...<f2n2>
 *                  ......
 *               <imagek> <nk> <fk1> <fk2>...<fkn2>
 * 
 * Ca sa ne fie usor sa pornim thread-urile:
 * for (int i = 0; i < atoi(argv[1]); ++i) {
 *      start a thread/process care citeste imaginea i si aplica filtrele 
 *          pentu imaginea respectiva
 * }
 * Dar eu zic ca ne complicam aiurea, mai ales ca trebui sa implementam si varianta
 * distribuita MPI(nu ar fi dificila ca am face cate un proce pentru fiecare imagine
 * dar problema va fi ca acel proce va trebui si el impartit in procese
 * pentru versiunea MPI)
 * Am lasat comentariul sa fie :))
 */

/**
 * aplica filtrele pe imaginea primita
 * @param image referinta catre imagine
 * @param filters lista de filtre ce trebuie aplicata
 * @param n numarul de filtre
 * @return imaginea obtinuta in urma aplicarii filtrelor
 */
static double param;
void processImage(Image **image, char **filters, int n, thread_data_t *thread_data) {
    Filter *filter;
    Image *aux;
    Image *newImage = thread_data->newImage;

    for (int i = 0; i < n; ++i) {
        std::string f = filters[i];

        if (thread_data->thread_data.thread_id == 0) {
            std::cout << "Filtrul: " << f << '\n';
        }

        if (f == BRIGHTNESS) {
            if (thread_data->thread_data.thread_id == 0) {
                std::cout << param << '\n';
                param = std::stod(filters[++i]);
            }
            pthread_barrier_wait(thread_data->thread_data.barrier);
            filter = FilterFactory::filterCreate(f, param, nullptr, 0, 0,
                &(thread_data->thread_data));
        } else if (f == CONTRAST) {
            if (thread_data->thread_data.thread_id == 0) {
                param = std::stod(filters[++i]);
                std::cout << param << '\n';
            }
            pthread_barrier_wait(thread_data->thread_data.barrier);
            filter = FilterFactory::filterCreate(f, param, nullptr, 0, 0,
                &(thread_data->thread_data));
        } else {
            filter = FilterFactory::filterCreate(f, 0.0, nullptr, 0, 0,
                &(thread_data->thread_data));
        }

        filter->applyFilter(*image, newImage);
        pthread_barrier_wait(thread_data->thread_data.barrier);
        delete filter;

        if (i == (n - 1)) {
            break;
        } 

        aux = *image;
        *image = newImage;
        newImage = aux;
    }
}

// Prepares the thread data and calls for the start of the filter
void *pthread_filter_wrapper(void *args)
{
    thread_data_t *data = (thread_data_t *) args;
    
    processImage(&data->image, (char **)&(data->argv[3]), data->argc - 3, data);
    return NULL;
}

int main(int argc, char const *argv[])
{
    Image *image;
    pthread_barrier_t barrier;
    pthread_mutex_t mutex;

    if(argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <file_in> <file_out> [f1, f2, ..., fn]\n\n";
        exit(EXIT_FAILURE);
    }

    if (argc == 3) {
        /**
         * OBS:
         * la filtrul: non-maximum-suppression, daca vem sa rulam doar pe el
         * va treb ui sa furnizam acei parametrii, deci zic sa renuntam
         * in a rula doar acest filtru 
         */
        std::cout << "No filter/s provided.\n";
        std::cout << "Filters: \n - sharpen \n - emboss \n - sepia \n - contrast [-128, 128] \n"
                  << " - brightness [0, 2] \n - black-white \n - gaussian-blur \n"
                  << " - double-threshold \n - edge-tracking"
                  << "\n - canny-edge-detection \n\n";
        return 0;
    }

    std::string fileIn = argv[1];
    std::string fileOut = argv[2];
    thread_data_t arguments[NUM_THREADS];
	pthread_t threads[NUM_THREADS];
    pthread_barrier_init(&barrier, NULL, NUM_THREADS);
    pthread_mutex_init(&mutex, NULL);

	image = ImageIo::imageRead(fileIn);
    Image *newImage = new Image(image->width - 2, image->height - 2);

    for (int i = 0; i < NUM_THREADS; ++i) {
        arguments[i].thread_data.thread_id = i;
        arguments[i].thread_data.barrier = &barrier;
        arguments[i].thread_data.mutex = &mutex;
        arguments[i].image = image;
        arguments[i].newImage = newImage;
        arguments[i].argc = argc;
        arguments[i].argv = argv;
    }

    for (int i = 1; i < NUM_THREADS; ++i) {
        pthread_create(&threads[i], NULL, pthread_filter_wrapper, &arguments[i]);
    }

    pthread_filter_wrapper(&arguments[0]);

	for (int i = 1; i < NUM_THREADS; ++i) {
		pthread_join(threads[i], NULL);
	}

	ImageIo::imageWrite(fileOut, newImage);

    delete image;
    delete newImage;
    pthread_barrier_destroy(&barrier);
    pthread_mutex_destroy(&mutex);
    return 0;
}
