#ifndef __IMAGE_H_
#define __IMAGE_H_

#include <stdlib.h>
#include <assert.h>
#include "utils.h"

class Pixel {
    public:
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;

    public:
        /**
         * constructor - creeaza un obiect pixel cu cele trei componente
         * @param r componenta red
         * @param g componenta green
         * @param b componenta blue
         * @param a componenta alfa
         */
        Pixel(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
            this->r = r;
            this->g = g;
            this->b = b;
            this->a = a;
        }
};

class Image {
    public:
        unsigned int width;
        unsigned int height;
        Pixel **matrix;

    public:
        /**
         * constructor - aloca memorie pentru o imagine bordata cu pixel-zero(r = g = b = a = 0)
         * OBS: Imaginea initial va contine doar pixeli-zero.
         * Ea va fi populata cand se vor citii datele din fisier(deci in ImageIO
         * functia de imageRead va popula imaginea)
         * @param width latime imagine
         * @param height inaltime imagine
         */
        Image(unsigned int width, unsigned int height) {
            this->width = width + 2;
            this->height = height + 2;

            this->matrix = (Pixel **)malloc(this->height * sizeof(Pixel *));
            ASSERT(this->matrix != nullptr)

            for (unsigned int i = 0; i < this->height; ++i) {
                this->matrix[i] = (Pixel *)calloc(this->width, sizeof(Pixel));
                ASSERT(this->matrix != nullptr)
            }
        }

        /**
         * destructor
         */
        ~Image() {
            for (unsigned int i = 0; i < this->height; ++i) {
                free(this->matrix[i]);
            }

            free(this->matrix);
        }
};

#endif /* __IMAGE_H_ */
