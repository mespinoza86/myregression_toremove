/*  Image Show
    Loads and displays the given image
    written by Sayuri L. Kitsune (2012)
*/

/* Include */
#include <stdio.h>
#include "image.h"

/* Main */
int main(int argn,char **argv){
    image *im;
    /* Error */
    if(argn < 2){
        fprintf(stderr,"No input .bmp file specified\n");
        return -1;
    }
    if(argn > 2){
        fprintf(stderr,"Too many command line arguments, only specify input .bmp file\n");
        return -1;
    }
    /* Open */
    im = image_load_bmp(argv[1]);
    /* Print */
    printf("%s is %dx%d pixels\n",argv[1],im->width,im->height); /* Yeah I know, should use method access instead of direct access */
    /* Done */
    image_delete(im);
    return 0;
}

