/* Load image */
image *image_load_bmp(char *filename){
    FILE *f;
    int w,h,x,y,bypp;
    unsigned short bpp;
    char tag[2];
    image *im;
    unsigned char *data,*ptr;
    unsigned char header[IMAGE_BMP_FILE_HEADER_SIZE+IMAGE_BMP_INFO_HEADER_SIZE-2];
    color *col;
    /* Open file */
    f = fopen(filename,"rb");
    if(!f)
    {
        fprintf(stderr,"Could not open %s\n",filename);
        return 0;
    }
    /* Read tag */
    if(fread(tag,1,2,f) != 2){
        fprintf(stderr,"Error reading image tag for %s\n",filename);
        fclose(f);
        return 0;
    }
    if(tag[0] != 'B' || tag[1] != 'M'){
        fprintf(stderr,"%s is not a valid WIN32 bitmap file\n",filename);
        fclose(f);
        return 0;
    }
    /* Read the rest of file header */
    if(fread(header,1,IMAGE_BMP_FILE_HEADER_SIZE+IMAGE_BMP_INFO_HEADER_SIZE-2,f) != IMAGE_BMP_FILE_HEADER_SIZE+IMAGE_BMP_INFO_HEADER_SIZE-2){
        fprintf(stderr,"Error reading image header for %s\n",filename);
        fclose(f);
        return 0;
    }
    w = *((int*)&header[IMAGE_BMP_FILE_HEADER_SIZE-2+4]);
    h = *((int*)&header[IMAGE_BMP_FILE_HEADER_SIZE-2+4+4]);
    bpp = *((unsigned short*)&header[IMAGE_BMP_FILE_HEADER_SIZE-2+4+4+4+2]);
    bypp = bpp/8;
    /* 24 or 32 bit */
    if(bpp != 24 && bpp != 32){
        fprintf(stderr,"%s is not a 24 or 32 bit bitmap (%dBPP)\n",filename,bpp);
        fclose(f);
        return 0;
    }
    /* Warning: if the image data doesn't evenly lay on a 4-byte alignment, the data may be askew */
    /* This doesn't happen in 32-bit bitmaps because each pixel is 4 bytes */
    /* You should be aligning your images to 8x8 blocks of pixels anyway */
    if(w%8 != 0 || h%8 != 0){
        fprintf(stderr,"%s doesn't have width or height a multiple of 8\n",filename);
        fclose(f);
        return 0;
    }
    /* New image */
    im = image_new(w,h);
    /* Read it in */
    data = (unsigned char*)malloc(bypp*w*h);
    if(fread(data,bypp,w*h,f) != w*h){
        fprintf(stderr,"Error reading image data for %s\n",filename);
        fclose(f);
        return 0;
    }
    fclose(f);
    /* Read pixels */
    for(y = 0;y < h;y++){
        for(x = 0;x < w;x++){
            /* Find pixels */
            ptr = &data[(x*bypp)+((h-y-1)*w*bypp)]; /* Don't ask me why WIN32 bitmaps are upside-down */
            col = &im->data[x+y*w];
            /* Copy data */
            col->red = ptr[2];
            col->green = ptr[1];
            col->blue = ptr[0];
            /* Alpha channel */
            if(bpp == 32)
                col->alpha = ptr[3];
            else
                col->alpha = 0xFF; /* Opaque */
        }
    }
    /* Done */
    free(data);
    return im;
}

