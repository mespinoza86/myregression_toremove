#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<assert.h> /* for evil uses of assert ;) */
#include<math.h>

#include<SDL/SDL.h>
#include<SDL/SDL_opengl.h>
#include <getopt.h>
#include<FreeImage.h>
#include<sys/types.h>


void Run(void);
void Init(void);
void LoadTexture(const char* filename, int tex_num);


SDL_Surface* window = NULL;

SDL_Event event;

GLuint tex[1];

time_t begin, end, func_last;


GLfloat diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f}; 

char *input_file;

/**/

int main(int argc, char** argv)
{
	u_int8_t done = 0x00;

    SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);

	window = SDL_SetVideoMode(300,300,0, SDL_HWSURFACE |
		       			SDL_HWPALETTE |
					SDL_GL_DOUBLEBUFFER | 
		       			SDL_OPENGL);
	FreeImage_Initialise(1);

	assert(window != NULL);



// structure for the long options. 
  static struct option lopts[] = {
    {"verbose"  ,no_argument,0,'v'},
    {"help"     ,no_argument,0,'h'},
    {0,0,0,0}
  };

  int optionIdx,c;
  int verbose=0;
  
  while ((c = getopt_long(argc, argv, "vhezci:o:",lopts,&optionIdx)) != -1) {
    switch (c) {
    case 'v':
      verbose=1;
      break;
    case 'i':
       input_file= optarg;
        break;

    case 'h':
      printf("Parametros de entrada: [-v|--verbose] [-h|--help] [-i]\n");
      printf("       -v: Indica que se desea imprimir informacion en pantalla\n");
      printf("       -i: Indica el nombre de la imagen de entrada\n");
      printf("       -h: Indica este menu de ayuda\n");
      printf("        Ejemplo: ./Main -v -i casa.jpg\n");
      printf("Parametros de uso:\n");
      printf("       Durante la ejecucion del programa, utilice los siguientes parametros\n");
      printf("       para manipular la imagen de entrada:\n");
      printf("       ---Rotacion de la imagen:\n");
      printf("       -q: Rotar la imagen hacia la izquierda.\n");
      printf("       -e: Rotar la imagen hacia la derecha\n");
      printf("       ---Zoom de la imagen:\n");
      printf("       -i: Realizar zoom in de la imagen.\n");
      printf("       -o: Realizar zoom out de la imagen.\n");
      printf("       ---Panoramica de la imagen:\n");
      printf("       -Tecla izquierda: Mover imagen hacia la izquierda\n");
      printf("       -Tecla derecha:   Mover imagen hacia la derecha\n");
      printf("       -Tecla arriba:    Mover imagen hacia la arriba\n");
      printf("       -Tecla abajo:     Mover imagen hacia la abajo\n");
      exit(0);
    default:
      printf("Option '-%c' not recognized.\n",c);
    }
  }

        if(input_file==NULL){
	   printf("-E- Fatal Error\n");
           printf("-E- No ha especificado una imagen de entrada\n");
           printf("-E- Utilice el argumento -i para indicar el nombre de la imagen\n");
	   printf("-E- Ejemplo: ./Main -i casa,jog\n");
           printf("-E- Utilice: ./Main -h para conocer el uso del sistema\n");
           exit(0);
        }

	Init();

	while(!done)
	{


		SDL_PollEvent(&event);

		switch(event.type)
		{

			case SDL_QUIT:
				done++;
				break;
                
            case SDL_KEYDOWN:           
              
                 switch( event.key.keysym.sym ){
                    case SDLK_LEFT:
                        if(verbose)printf("Left\n");                        
                        glTranslatef( 0.01f, 0 , 0 );
                        break;
                    case SDLK_RIGHT:
                        if(verbose)printf("Right\n");
                        glTranslatef( -0.01f, 0 , 0 );             
                        break;
                    case SDLK_UP:
                        if(verbose)printf("Up\n");
                        glTranslatef( 0, -0.01f , 0 );
                        break;
                    case SDLK_DOWN:
                        if(verbose)printf("Down\n");
                        glTranslatef( 0, 0.01f , 0 );
                        break; 
                    case SDLK_q:
                        if(verbose)printf("q for clockwise rotation\n");
                        glRotatef(1,0.0,0.0,1.0);
                        break;     
                    case SDLK_e:
                        if(verbose)printf("e for counterclock rotation\n");
                        glRotatef(-1,0.0,0.0,1.0);
                        break;   
                    case SDLK_i:
                        if(verbose)printf("i for zoom in\n");
                        glScaled(1.01, 1.01, 1.0);
                        break;   
                    case SDLK_o:
                        if(verbose)printf("o for zoom out\n");
                        glScaled(0.99, 0.99, 1.0);
                        break;                  
                    default:
                        break;
                }            
            
                break;
			default:
				break;
		}
		

		Run();
	}


	SDL_Quit();
	return 0;
}

void Init(void)
{
	glGenTextures(1, tex);

	glShadeModel(GL_SMOOTH);

	glClearDepth(1.0f);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);

	glMatrixMode(GL_PROJECTION);
	glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
		

	LoadTexture(input_file,0); 
	time(&begin);
	time(&func_last);

}



void Run(void)
{


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	time(&end);

    glBindTexture(GL_TEXTURE_2D, tex[0]);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);

    glBegin(GL_QUADS);

        glVertex2f(-1.0f, -1.0f);
        glTexCoord2f(0.0f, 0.0f);

        glVertex2f(-1.0f, 1.0f);
        glTexCoord2f(1.0f, 0.0f);

        glVertex2f( 1.0f,  1.0f);
        glTexCoord2f(1.0f,1.0f);

        glVertex2f( 1.0f, -1.0f);
        glTexCoord2f(0.0f, 1.0f);

    glEnd();


	func_last = end;

	SDL_GL_SwapBuffers();

}

void LoadTexture(const char* filename, int tex_num)
{

	int height=0, width=0,pitch=0;
	GLubyte* data;
	FREE_IMAGE_FORMAT blah = FreeImage_GetFileType(filename, 0);
	FIBITMAP* map = FreeImage_Load(blah, filename, JPEG_ACCURATE);
        map = FreeImage_ConvertTo24Bits(map);

	assert(map != NULL);

	width = FreeImage_GetWidth(map);
	height = FreeImage_GetHeight(map);
    
    
    printf("Image width: %d\n", width);
    printf("Image heigth: %d\n", height);

    
	pitch = FreeImage_GetPitch(map);

	glBindTexture(GL_TEXTURE_2D, tex[tex_num]);

	data = malloc(width * height * 3);
	FreeImage_ConvertToRawBits(data, map, pitch, 24, 0,0,0,1);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
				GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
				GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,width,	height, 0, GL_BGR, 
			GL_UNSIGNED_BYTE, data);
	FreeImage_Unload(map);
	free(data);
    
    if(width>=height){
        glScaled(height/300, height/300, 0);
    }else{
        glScaled(width/300, width/300, 0);
    }  

	printf("Succesfully loaded %s\n", filename);

}




