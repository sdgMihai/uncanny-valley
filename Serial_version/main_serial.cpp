#include <iostream>
#include "../utils/image.h"
#include "../utils/imageIO.h"
#include "../utils/filter.h"
#include "../utils/filter_factory.h"

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
 * @param image referita catre imagine
 * @param filters lista de filtre ce trebuie aplicata
 * @param n numarul de filtre
 * @return imaginea obtinuta in urma aplicarii filtrelor
 */
Image* processImage(Image **image, char **filters, int n) {
    Filter *filter;
    Image *newImage = new Image((*image)->width - 2, (*image)->height - 2);
    Image *aux;

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

    return newImage;
}


int main(int argc, char const *argv[])
{
    Image *image, *newImage;

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
        std::cout << "Filters: \n - sharpen \n - emboss \n - sepia \n - contrast \n"
                  << " - brightness \n - black-white \n - gaussian-blur \n"
                  << " - non-maximum-suppression \n - double-threshold \n - edge-tracking"
                  << "\n - canny-edge-detection \n\n";
        return 0;
    }

    std::string fileIn = argv[1];
    std::string fileOut = argv[2];

	image = ImageIo::imageRead(fileIn);
	newImage = processImage(&image, (char **)&argv[3], argc - 3);
	ImageIo::imageWrite(fileOut, newImage);

    delete image;
    delete newImage;

    return 0;
}
