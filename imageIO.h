#ifndef __IMAGE_IO_H_
#define __IMAGE_IO_H_

#include <string>
#include <vector>
#include "third-party/lodepng.h"
#include "image.h"

class ImageIo {
    public:
        /**
         * creeaza un obiet de tip Image si populeaza matricea
         * asociata
         * @param width latimea imaginii
         * @param height inaltimea imaginii
         * @return referinta catre obiectul creat
         */
        static Image* imageCreate(unsigned int &width, 
            unsigned int &height, std::vector<unsigned char> &rawImage) {
            Image *image = new Image(width, height);
            unsigned int step = 0;

            /**
             * TODO: cred ca am putea partitiona vectorul sa folosim cateva thread-uri
             * dar va trebui sa vedem cum il partitionam in functie de i si j
             */
            for (unsigned int i = 1; i <= height; ++i) {
                for (unsigned int j = 1; j <= width; ++j) {
                    image->matrix[i][j] = Pixel(rawImage[step], rawImage[step + 1],
                                                rawImage[step + 2], rawImage[step + 3]);
                    step += 4;
                }
            }

            return image;
        }
        
    public:
        /**
         * citeste o imagine PNG si o decodifica
         * @param filename numele fisierului care contine imaginea
         * @return un obiect de tip Image
         */
        static Image* imageRead(std::string &filename) {
            unsigned int width = 0, height = 0;
            std::vector<unsigned char> rawImage;

            unsigned int error = lodepng::decode(rawImage, width, height, filename);
            ASSERT(error == 0)
            ASSERT(width != 0)
            ASSERT(height != 0)
            ASSERT(!rawImage.empty())


            return ImageIo::imageCreate(width, height, rawImage);
        }

        /**
         * salveaza, pe disk, obiectul de tip Image sub forma de imagine PNG
         * @param filename fisierul in care se va stoca imaginea
         * @param image referinta catre obiectul de tip Image
         */
        static void imageWrite(std::string &filename, const Image *image) {
            std::vector<unsigned char> rawImage;

            /**
             * TODO:
             * va trebui cumva sa paralelizam crearea vectorului rawImage:
             * gen alocam de la inceput un array mare (h*w*4 - sper sa nu ma insel :)) )
             * si dupa partitionam imaginea cumva, doar am facut APD, SM, APP :))
             */
            for (unsigned int i = 1; i < image->height - 1; ++i) {
                for (unsigned int j = 1; j < image->width - 1; ++j) {
                    rawImage.push_back(image->matrix[i][j].r);
                    rawImage.push_back(image->matrix[i][j].g);
                    rawImage.push_back(image->matrix[i][j].b);
                    rawImage.push_back(image->matrix[i][j].a);
                }
            }

            unsigned int error = lodepng::encode(filename, rawImage,
                                                image->width - 2, image->height - 2);
            ASSERT(error == 0)
        }
};

#endif /* __IMAGE_IO_H_ */
