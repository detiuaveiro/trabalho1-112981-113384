/// image8bit - A simple image processing module.
///
/// This module is part of a programming project
/// for the course AED, DETI / UA.PT
///
/// You may freely use and modify this code, at your own risk,
/// as long as you give proper credit to the original and subsequent authors.
///
/// João Manuel Rodrigues <jmr@ua.pt>
/// 2013, 2023

// Student authors (fill in below):
// NMec: 113384 Name: Danilo Micael Gregório Silva
// NMec: 112981 Name: Tomás Santos Fernandes
// 
// 
// Date:
//

#include "image8bit.h"

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "instrumentation.h"

// The data structure
//
// An image is stored in a structure containing 3 fields:
// Two integers store the image width and height.
// The other field is a pointer to an array that stores the 8-bit gray
// level of each pixel in the image.  The pixel array is one-dimensional
// and corresponds to a "raster scan" of the image from left to right,
// top to bottom.
// For example, in a 100-pixel wide image (img->width == 100),
//   pixel position (x,y) = (33,0) is stored in img->pixel[33];
//   pixel position (x,y) = (22,1) is stored in img->pixel[122].
// 
// Clients should use images only through variables of type Image,
// which are pointers to the image structure, and should not access the
// structure fields directly.

// Maximum value you can store in a pixel (maximum maxval accepted)
const uint8 PixMax = 255;

// Internal structure for storing 8-bit graymap images
struct image {
  int width;
  int height;
  int maxval;   // maximum gray value (pixels with maxval are pure WHITE)
  uint8* pixel; // pixel data (a raster scan)
};


// This module follows "design-by-contract" principles.
// Read `Design-by-Contract.md` for more details.

/// Error handling functions

// In this module, only functions dealing with memory allocation or file
// (I/O) operations use defensive techniques.
// 
// When one of these functions fails, it signals this by returning an error
// value such as NULL or 0 (see function documentation), and sets an internal
// variable (errCause) to a string indicating the failure cause.
// The errno global variable thoroughly used in the standard library is
// carefully preserved and propagated, and clients can use it together with
// the ImageErrMsg() function to produce informative error messages.
// The use of the GNU standard library error() function is recommended for
// this purpose.
//
// Additional information:  man 3 errno;  man 3 error;

// Variable to preserve errno temporarily
static int errsave = 0;

// Error cause
static char* errCause;

/// Error cause.
/// After some other module function fails (and returns an error code),
/// calling this function retrieves an appropriate message describing the
/// failure cause.  This may be used together with global variable errno
/// to produce informative error messages (using error(), for instance).
///
/// After a successful operation, the result is not garanteed (it might be
/// the previous error cause).  It is not meant to be used in that situation!
char* ImageErrMsg() { ///
  return errCause;
}


// Defensive programming aids
//
// Proper defensive programming in C, which lacks an exception mechanism,
// generally leads to possibly long chains of function calls, error checking,
// cleanup code, and return statements:
//   if ( funA(x) == errorA ) { return errorX; }
//   if ( funB(x) == errorB ) { cleanupForA(); return errorY; }
//   if ( funC(x) == errorC ) { cleanupForB(); cleanupForA(); return errorZ; }
//
// Understanding such chains is difficult, and writing them is boring, messy
// and error-prone.  Programmers tend to overlook the intricate details,
// and end up producing unsafe and sometimes incorrect programs.
//
// In this module, we try to deal with these chains using a somewhat
// unorthodox technique.  It resorts to a very simple internal function
// (check) that is used to wrap the function calls and error tests, and chain
// them into a long Boolean expression that reflects the success of the entire
// operation:
//   success = 
//   check( funA(x) != error , "MsgFailA" ) &&
//   check( funB(x) != error , "MsgFailB" ) &&
//   check( funC(x) != error , "MsgFailC" ) ;
//   if (!success) {
//     conditionalCleanupCode();
//   }
//   return success;
// 
// When a function fails, the chain is interrupted, thanks to the
// short-circuit && operator, and execution jumps to the cleanup code.
// Meanwhile, check() set errCause to an appropriate message.
// 
// This technique has some legibility issues and is not always applicable,
// but it is quite concise, and concentrates cleanup code in a single place.
// 
// See example utilization in ImageLoad and ImageSave.
//
// (You are not required to use this in your code!)


// Check a condition and set errCause to failmsg in case of failure.
// This may be used to chain a sequence of operations and verify its success.
// Propagates the condition.
// Preserves global errno!
static int check(int condition, const char* failmsg) {
  errCause = (char*)(condition ? "" : failmsg);
  return condition;
}


/// Init Image library.  (Call once!)
/// Currently, simply calibrate instrumentation and set names of counters.
void ImageInit(void) { ///
  InstrCalibrate();
  InstrName[0] = "pixmem";  // InstrCount[0] will count pixel array acesses
  // Name other counters here...
  
}

// Macros to simplify accessing instrumentation counters:
#define PIXMEM InstrCount[0]
// Add more macros here...

// TIP: Search for PIXMEM or InstrCount to see where it is incremented!


/// Image management functions

/// Create a new black image.
///   width, height : the dimensions of the new image.
///   maxval: the maximum gray level (corresponding to white).
/// Requires: width and height must be non-negative, maxval > 0.
/// 
/// On success, a new image is returned.
/// (The caller is responsible for destroying the returned image!)
/// On failure, returns NULL and errno/errCause are set accordingly.
Image ImageCreate(int width, int height, uint8 maxval) { ///
  assert (width >= 0);
  assert (height >= 0);
  assert (0 < maxval && maxval <= PixMax);
  // Insert your code here!

  Image img = (Image)malloc(sizeof(struct image)); // aloca memória para a Imagem
  if (img == NULL) {
    errno = ENOMEM;
    errCause = "Memory allocation error";
    return NULL;
  }

  // inicializa as variáveis da imagem
  img->width = width;  
  img->height = height;
  img->maxval = maxval;

  img->pixel = (uint8*)malloc(width*height*sizeof(uint8)); // aloca memória para o array de pixeis
  if (img->pixel == NULL) {
    errno = ENOMEM;
    errCause = "Memory allocation error";
    free(img);
    return NULL;
  }

  for (int i = 0; i < width*height; i++) {
    img->pixel[i] = 0; // inicializa o array de pixeis a 0 (0->preto e 255->branco)
  }

  return img;
}

/// Destroy the image pointed to by (*imgp).
///   imgp : address of an Image variable.
/// If (*imgp)==NULL, no operation is performed.
/// Ensures: (*imgp)==NULL.
/// Should never fail, and should preserve global errno/errCause.
void ImageDestroy(Image* imgp) { ///
  assert (imgp != NULL);
  // Insert your code here!

  free((*imgp)->pixel); // liberta a memória do array de pixeis
  free(*imgp); // liberta a memória da imagem

  // preservar a variável errno:
  errsave = errno;

  *imgp = NULL; // ponteiro passa a apontar para NULL
  
}


/// PGM file operations

// See also:
// PGM format specification: http://netpbm.sourceforge.net/doc/pgm.html

// Match and skip 0 or more comment lines in file f.
// Comments start with a # and continue until the end-of-line, inclusive.
// Returns the number of comments skipped.
static int skipComments(FILE* f) {
  char c;
  int i = 0;
  while (fscanf(f, "#%*[^\n]%c", &c) == 1 && c == '\n') {
    i++;
  }
  return i;
}

/// Load a raw PGM file.
/// Only 8 bit PGM files are accepted.
/// On success, a new image is returned.
/// (The caller is responsible for destroying the returned image!)
/// On failure, returns NULL and errno/errCause are set accordingly.
Image ImageLoad(const char* filename) { ///
  int w, h;
  int maxval;
  char c;
  FILE* f = NULL;
  Image img = NULL;

  int success = 
  check( (f = fopen(filename, "rb")) != NULL, "Open failed" ) &&
  // Parse PGM header
  check( fscanf(f, "P%c ", &c) == 1 && c == '5' , "Invalid file format" ) &&
  skipComments(f) >= 0 &&
  check( fscanf(f, "%d ", &w) == 1 && w >= 0 , "Invalid width" ) &&
  skipComments(f) >= 0 &&
  check( fscanf(f, "%d ", &h) == 1 && h >= 0 , "Invalid height" ) &&
  skipComments(f) >= 0 &&
  check( fscanf(f, "%d", &maxval) == 1 && 0 < maxval && maxval <= (int)PixMax , "Invalid maxval" ) &&
  check( fscanf(f, "%c", &c) == 1 && isspace(c) , "Whitespace expected" ) &&
  // Allocate image
  (img = ImageCreate(w, h, (uint8)maxval)) != NULL &&
  // Read pixels
  check( fread(img->pixel, sizeof(uint8), w*h, f) == w*h , "Reading pixels" );
  PIXMEM += (unsigned long)(w*h);  // count pixel memory accesses

  // Cleanup
  if (!success) {
    errsave = errno;
    ImageDestroy(&img);
    errno = errsave;
  }
  if (f != NULL) fclose(f);
  return img;
}

/// Save image to PGM file.
/// On success, returns nonzero.
/// On failure, returns 0, errno/errCause are set appropriately, and
/// a partial and invalid file may be left in the system.
int ImageSave(Image img, const char* filename) { ///
  assert (img != NULL);
  int w = img->width;
  int h = img->height;
  uint8 maxval = img->maxval;
  FILE* f = NULL;

  int success =
  check( (f = fopen(filename, "wb")) != NULL, "Open failed" ) &&
  check( fprintf(f, "P5\n%d %d\n%u\n", w, h, maxval) > 0, "Writing header failed" ) &&
  check( fwrite(img->pixel, sizeof(uint8), w*h, f) == w*h, "Writing pixels failed" ); 
  PIXMEM += (unsigned long)(w*h);  // count pixel memory accesses

  // Cleanup
  if (f != NULL) fclose(f);
  return success;
}


/// Information queries

/// These functions do not modify the image and never fail.

/// Get image width
int ImageWidth(Image img) { ///
  assert (img != NULL);
  return img->width;
}

/// Get image height
int ImageHeight(Image img) { ///
  assert (img != NULL);
  return img->height;
}

/// Get image maximum gray level
int ImageMaxval(Image img) { ///
  assert (img != NULL);
  return img->maxval;
}

/// Pixel stats
/// Find the minimum and maximum gray levels in image.
/// On return,
/// *min is set to the minimum gray level in the image,
/// *max is set to the maximum.
void ImageStats(Image img, uint8* min, uint8* max) { ///
  assert (img != NULL);
  // Insert your code here!

  int width = ImageWidth(img);    // obter o nº de píxeis na largura
  int height = ImageHeight(img);  // obter o nº de píxeis na altura

  *min = PixMax; // nível mais alto de cinza possível (branco)
  *max = 0; // nível mais baixo de cinza possível (preto)

  for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            uint8 pixelValue = ImageGetPixel(img, x, y);

            if (pixelValue < *min) {
                *min = pixelValue;
            }
            if (pixelValue > *max) {
                *max = pixelValue;
            }
        }
    }
}

/// Check if pixel position (x,y) is inside img.
int ImageValidPos(Image img, int x, int y) { ///
  assert (img != NULL);
  return (0 <= x && x < img->width) && (0 <= y && y < img->height);
}

/// Check if rectangular area (x,y,w,h) is completely inside img.
int ImageValidRect(Image img, int x, int y, int w, int h) { ///
  assert (img != NULL);
  // Insert your code here!

  int imgWidth = ImageWidth(img);
  int imgHeight = ImageHeight(img);

  // x é a abscissa do canto superior esquerdo da área retangular
  // y é a ordenada do canto superior esquerdo da área retangular
  // w é a largura
  // h é a altura

  if (x >= 0 && y >= 0 && x + w <= imgWidth && y + h <= imgHeight) {
    return 1; // está contida na imagem
  }

  return 0; // não está contida na imagem
}

/// Pixel get & set operations

/// These are the primitive operations to access and modify a single pixel
/// in the image.
/// These are very simple, but fundamental operations, which may be used to 
/// implement more complex operations.

// Transform (x, y) coords into linear pixel index.
// This internal function is used in ImageGetPixel / ImageSetPixel. 
// The returned index must satisfy (0 <= index < img->width*img->height)
static inline int G(Image img, int x, int y) {
  int index;
  // Insert your code here!

  assert(img != NULL);
  assert(0 <= x && x < img->width);
  assert(0 <= y && y < img->height);

  index = y * img->width + x; // ao multiplicar pela largura obtemos o número de pixeis 
                              // que estão antes da linha y, e depois somamos o número de pixeis que estão antes da coluna x

  assert (0 <= index && index < img->width*img->height);  // verificar pós-condições
  return index;
}

/// Get the pixel (level) at position (x,y).
uint8 ImageGetPixel(Image img, int x, int y) { ///
  assert (img != NULL);
  assert (ImageValidPos(img, x, y));
  PIXMEM += 1;  // count one pixel access (read)
  return img->pixel[G(img, x, y)];
} 

/// Set the pixel at position (x,y) to new level.
void ImageSetPixel(Image img, int x, int y, uint8 level) { ///
  assert (img != NULL);
  assert (ImageValidPos(img, x, y));
  PIXMEM += 1;  // count one pixel access (store)
  img->pixel[G(img, x, y)] = level;
} 


/// Pixel transformations

/// These functions modify the pixel levels in an image, but do not change
/// pixel positions or image geometry in any way.
/// All of these functions modify the image in-place: no allocation involved.
/// They never fail.


/// Transform image to negative image.
/// This transforms dark pixels to light pixels and vice-versa,
/// resulting in a "photographic negative" effect.
void ImageNegative(Image img) { ///
  assert (img != NULL);
  // Insert your code here!

  int width = ImageWidth(img);      // obter a largura
  int height = ImageHeight(img);    // obter a altura

  // percorrer todos os píxeis
  for (int y = 0; y < height; y++) {  
        for (int x = 0; x < width; x++) {
            uint8 pixelValue = ImageGetPixel(img, x, y);  // obter o valor de de cinza de cada um

            uint8 negativeValue = PixMax - pixelValue;  // ao fazer a diferença com o valor máximo 
                                                        // possível passamos para o seu "simetrico"/negativo num intervalo de [0, 255]

            ImageSetPixel(img, x, y, negativeValue);
        }
    }
}

/// Apply threshold to image.
/// Transform all pixels with level<thr to black (0) and
/// all pixels with level>=thr to white (maxval).
void ImageThreshold(Image img, uint8 thr) { ///
  assert (img != NULL);
  // Insert your code here!

  int width = ImageWidth(img);      // obter a largura
  int height = ImageHeight(img);    // obter a altura
  uint8 maxval = ImageMaxval(img);  // obter o máximo valor de cinzento na imagem

  // percorrer todos os píxeis
  for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            uint8 pixelValue = ImageGetPixel(img, x, y);  // obter o valor de cinza do píxel

            uint8 thrValue = 0;

            if (pixelValue >= thr) {
              thrValue = maxval;  // se for >= fica o maior tom de cinza, senão fica preto (como foi inicializada a variável thrValue)
            }

            ImageSetPixel(img, x, y, thrValue);
        }
    }
}

/// Brighten image by a factor.
/// Multiply each pixel level by a factor, but saturate at maxval.
/// This will brighten the image if factor>1.0 and
/// darken the image if factor<1.0.
void ImageBrighten(Image img, double factor) { ///
  assert (img != NULL);
  assert (factor >= 0.0);
  // Insert your code here!

  int width = ImageWidth(img);      // obter a largura 
  int height = ImageHeight(img);    // obter a altura
  uint8 maxval = ImageMaxval(img);  // obter o tom de cinza mais elevado

  // percorrer todos os píxeis
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      uint8 pixelValue = ImageGetPixel(img, x, y);  // obter o valor de de cinza de cada um

      double newPixelValue = (double)pixelValue * factor + 0.5; // é feita a soma para arredondar

      if (newPixelValue > maxval) { // no caso de ultrapassar o maxval
        newPixelValue = maxval;     // fica com  o valor deste
      }
      ImageSetPixel(img, x, y, (uint8)newPixelValue);
    }
  }
}


/// Geometric transformations

/// These functions apply geometric transformations to an image,
/// returning a new image as a result.
/// 
/// Success and failure are treated as in ImageCreate:
/// On success, a new image is returned.
/// (The caller is responsible for destroying the returned image!)
/// On failure, returns NULL and errno/errCause are set accordingly.

// Implementation hint: 
// Call ImageCreate whenever you need a new image!

/// Rotate an image.
/// Returns a rotated version of the image.
/// The rotation is 90 degrees anti-clockwise.
/// Ensures: The original img is not modified.
/// 
/// On success, a new image is returned.
/// (The caller is responsible for destroying the returned image!)
/// On failure, returns NULL and errno/errCause are set accordingly.
Image ImageRotate(Image img) { ///
  assert (img != NULL);
  // Insert your code here!

  int imgWidth = ImageWidth(img);   // obter a largura
  int imgHeight = ImageHeight(img); // obter a altura
  int imgMaxVal = ImageMaxval(img); // obter o nível máximo de cinza na imagem

  // tem de ser criada uma nova imagem, porque a original não pode ser modificada
  Image rotatedImage = ImageCreate(imgHeight, imgWidth, imgMaxVal); // neste caso, preciso de trocar a altura pela largura (caso a imagem não seja quadrada)

  if (rotatedImage == NULL) {
    errsave = errno; // erro que vem de ImageCreate() (?)
    ImageDestroy(&rotatedImage);
    errno = errsave;  // caso tenha ocorrido erro em ImageDestroy(), o errno continua a conter o valor do erro que ocorreu em ImageCreate()
    errCause = "Failed to create a new image.";
    return NULL;
  }

  // percorrer todos os píxeis da imagem original
  for (int x=0; x<imgWidth; x++) {
    for (int y=0; y<imgHeight; y++) {

      uint8 pixelValue = ImageGetPixel(img, x, y);  // obter o valor do píxel na posição (x, y)

      // depois de desenhar e de visualizar as rotações, chegou-se à conclusão que a abcissa do ponto depois da rotção correspondia 
      // sempre à ordenada do píxel original, e que a ordenada do ponto depois da rotação era também ela sempre igual à diferença entre 
      // o maior índice da largura da imagem original e o valor da abcissa do píxel original
      ImageSetPixel(rotatedImage, y, (imgWidth-1)-x, pixelValue);   

    }  
  }

  return rotatedImage;
}

/// Mirror an image = flip left-right.
/// Returns a mirrored version of the image.
/// Ensures: The original img is not modified.
/// 
/// On success, a new image is returned.
/// (The caller is responsible for destroying the returned image!)
/// On failure, returns NULL and errno/errCause are set accordingly.
Image ImageMirror(Image img) { ///
  assert (img != NULL);
  // Insert your code here!
  
  int imgWidth = ImageWidth(img);   // obter a largura
  int imgHeight = ImageHeight(img); // obter a altura
  int imgMaxVal = ImageMaxval(img); // obter o nível máximo de cinza na imagem

  // tem de ser criada uma nova imagem, porque a original não pode ser modificada
  Image mirroredImage = ImageCreate(imgWidth, imgHeight, imgMaxVal);

  if (mirroredImage == NULL) {
    errsave = errno; // erro que vem de ImageCreate() (?)
    ImageDestroy(&mirroredImage);
    errno = errsave;  // caso tenha ocorrido erro em ImageDestroy(), o errno continua a conter o valor do erro que ocorreu em ImageCreate()
    errCause = "Failed to create a new image.";
    return NULL;
  }

  // para espelhar uma imagem, precisamos de garantir que os píxeis da altura (y) permanecem
  // como estavam (na mesma linha), e que a ordem dos píxeis da largura (x) seja invertida

  for (int x=0; x<imgWidth; x++) {
    for (int y=0; y<imgHeight; y++) {

      uint8 pixelValue = ImageGetPixel(img, x, y);  // obter o valor do píxel na posição (x, y) da imagem original

      // copiar o valor do píxel na posição (x, y) da imagem original para a coordenada simétrica de x, na mesma linha, na mirroredImage
      ImageSetPixel(mirroredImage, (imgWidth-1) - x, y, pixelValue);    
                                                                      
    }  
  }

  return mirroredImage;
}

/// Crop a rectangular subimage from img.
/// The rectangle is specified by the top left corner coords (x, y) and
/// width w and height h.
/// Requires:
///   The rectangle must be inside the original image.
/// Ensures:
///   The original img is not modified.
///   The returned image has width w and height h.
/// 
/// On success, a new image is returned.
/// (The caller is responsible for destroying the returned image!)
/// On failure, returns NULL and errno/errCause are set accordingly.
Image ImageCrop(Image img, int x, int y, int w, int h) { ///
  assert (img != NULL);
  assert (ImageValidRect(img, x, y, w, h));
  
  // Insert your code here!

  // tem de ser criada uma nova imagem, porque a original não pode ser modificada
  Image croppedImage = ImageCreate(w, h, ImageMaxval(img));

  if (croppedImage == NULL) {
    errsave = errno; // erro que vem de ImageCreate() (?)
    ImageDestroy(&croppedImage);
    errno = errsave;  // caso tenha ocorrido erro em ImageDestroy(), o errno continua a conter o valor do erro que ocorreu em ImageCreate()
    errCause = "Failed to create a new image.";
    return NULL;
  }

  // percorrer todos os píxeis presentes no retângulo a recortar na imagem original
  for (int new_y = 0; new_y < h; new_y++) {
    for (int new_x = 0; new_x < w; new_x++) {
      uint8 pixelValue = ImageGetPixel(img, new_x + x, new_y + y); // obter o valor do píxel na posição (x, y) da imagem original

      // transferir o valor do píxel para a posição (new_x, new_y) da imagem cortada
      ImageSetPixel(croppedImage, new_x, new_y, pixelValue);
    }
  }

  return croppedImage;

}


/// Operations on two images

/// Paste an image into a larger image.
/// Paste img2 into position (x, y) of img1.
/// This modifies img1 in-place: no allocation involved.
/// Requires: img2 must fit inside img1 at position (x, y).
void ImagePaste(Image img1, int x, int y, Image img2) { ///
  assert (img1 != NULL);
  assert (img2 != NULL);
  assert (ImageValidRect(img1, x, y, img2->width, img2->height));
  // Insert your code here!

  int img2Width = ImageWidth(img2);   // obter a largura da imagem a ser colada
  int img2Height = ImageHeight(img2); // obter a altura da imagem a ser colada

  // correr todos os píxeis da imagem a ser colada
  for (int abcissa=0; abcissa < img2Width; abcissa++) {
    for (int ordenada=0; ordenada < img2Height; ordenada++) {

        int img2PixelValue = ImageGetPixel(img2, abcissa, ordenada);  // obter o valor do píxel na posição (abcissa, ordenada) na imagem a ser colada
   
        // para colar no sítio certo, têm de ser feitas as somas x+abcissa e y+ordenada, o valor obtido acima é tranferido para estas coordenadas na imagem grande
        ImageSetPixel(img1, x+abcissa, y+ordenada, img2PixelValue);
    }
  }
}

/// Blend an image into a larger image.
/// Blend img2 into position (x, y) of img1.
/// This modifies img1 in-place: no allocation involved.
/// Requires: img2 must fit inside img1 at position (x, y).
/// alpha usually is in [0.0, 1.0], but values outside that interval
/// may provide interesting effects.  Over/underflows should saturate.
void ImageBlend(Image img1, int x, int y, Image img2, double alpha) { ///
  assert (img1 != NULL);
  assert (img2 != NULL);
  assert (ImageValidRect(img1, x, y, img2->width, img2->height));
  // Insert your code here!

  int img2Width = ImageWidth(img2);   // obter a largura da imagem a ser misturada
  int img2Height = ImageHeight(img2); // obter a altura da imagem a ser misturada

  // correr todos os píxeis da imagem a ser misturada
  for (int abcissa=0; abcissa < img2Width; abcissa++) {
    for (int ordenada=0; ordenada < img2Height; ordenada++) {

        uint8 img2PixelValue = ImageGetPixel(img2, abcissa, ordenada);      // obter o valor do píxel na posição (abcissa, ordenada) na imagem a ser misturada
        // obter o valor do píxel na posição (x+abcissa, y+ordenada) na imagem grande (desta maneira podemos posicionar a imagem pequena no sítio correto)
        uint8 img1PixelValue = ImageGetPixel(img1, x+abcissa, y+ordenada);

        double img2NewPixelValue = (1 - alpha) * img1PixelValue + alpha * img2PixelValue + 0.5;   
   
        // no píxel obtido na imagem original, substitui-se o seu valor pela exxpressão: (1 - alpha) * img1PixelValue + alpha * img2PixelValue + 0.5 
        // onde "alpha" indica o grau de opacidade da imagem pequena: 0.0 para não aparecer a pequena, 1.0 para a pequena aparecer opaca por cima da grande
        ImageSetPixel(img1, x+abcissa, y+ordenada, (uint8) img2NewPixelValue);
    }
  }
}

/// Compare an image to a subimage of a larger image.
/// Returns 1 (true) if img2 matches subimage of img1 at pos (x, y).
/// Returns 0, otherwise.
int ImageMatchSubImage(Image img1, int x, int y, Image img2) { ///
  assert (img1 != NULL);
  assert (img2 != NULL);
  assert (ImageValidPos(img1, x, y));
  // Insert your code here! -> vou usar como píxel inicial o do canto sup esquerdo da img2

  int img2Width = ImageWidth(img2);   // obter a largura da imagem a ser comparada (pequena)
  int img2Height = ImageHeight(img2); // obter a altura da imagem a ser comparada (pequena)

  if (ImageValidRect(img1, x, y, img2Width-1, img2Height-1)) // verificar se é possível a imagem 2 estar contida na imagem 1
    return 0; 

  // percorrer todos os píxeis da imagem pequena
  for (int abcissa=0; abcissa<img2Width; abcissa++) {
    for (int ordenada=0; ordenada<img2Height; ordenada++) {

        int img2PixelValue = ImageGetPixel(img2, abcissa, ordenada);      // obter o valor do píxel na posição (abcissa, ordenada) da imagem pequena a ser comparada
        // obter o valor do píxel na posição (x+abcissa, y+ordenada) na imagem grande (correspondente ao píxel na posição (abcissa, ordenada) da imagem pequena)
        int img1PixelValue = ImageGetPixel(img1, x+abcissa, y+ordenada);  

        // caso os dois valores acima não sejam iguais, a igualdade do match falha e a função retorna 0
        if (img1PixelValue != img2PixelValue)
          return 0;
    }
  }
  return 1;
}

/// Locate a subimage inside another image.
/// Searches for img2 inside img1.
/// If a match is found, returns 1 and matching position is set in vars (*px, *py).
/// If no match is found, returns 0 and (*px, *py) are left untouched.
int ImageLocateSubImage(Image img1, int* px, int* py, Image img2) { ///
  assert (img1 != NULL);
  assert (img2 != NULL);
  // Insert your code here!

  int img2Width = ImageWidth(img2);   // obter a largura da imagem a ser comparada (pequena)
  int img2Height = ImageHeight(img2); // obter a altura da imagem a ser comparada (pequena)

  // percorrer todos os píxeis da imagem pequena
  for (int x=0; x<img2Width; x++) {
    for (int y=0; y<img2Height; y++) { 

      // em cada píxel, usamos a função ImageMatchSubImage() desenvolvida acima para verificar se o retângulo criado a partir do píxel na posição
      // (x, y) corresponde a uma subimagem na imagem grande;
      // se corresponder, atribuem-se aos valores dos endereços nos ponteiros px e py os valores de x e y, e a função devolve 1;
      if (ImageMatchSubImage(img1, x, y, img2)) {   
        *px = x;      
        *py = y;
        return 1;                                   
      }

    }  
  }

  return 0; // se não for encontrada nenhuma correspondência, a função devolve 0
}


/// Filtering


// Esta função calcula a média dos píxeis no retângulo [x-dx, x+dx]x[y-dy, y+dy]
static uint8 rectMeanCalc(Image img, int x, int y, int dx, int dy) {
  
  int imgWidth = ImageWidth(img);   // obter a largura da imagem
  int imgHeight = ImageHeight(img); // obter a altura da imagem

  int xEsquerda = x - dx;           // obter a abcissa do(s) píxel(eis) mais à esquerda no retângulo
  int yCima = y - dy;               // obter a ordenada do(s) píxel(eis) mais acima no retângulo
  int xDireita = x + dx;            // obter a abcissa do(s) píxel(eis) mais à direita no retângulo
  int yBaixo = y + dy;              // obter a ordenada do(s) píxel(eis) mais abaixo no retângulo

  int sum = 0;                      // variável que conterá a soma dos valores dos píxeis no retângulo
  int pixelCount = 0;               // variável que conterá o nº de píxeis no retângulo


  // as verificações a seguir servem para saber se os limites do retângulo [x-dx, x+dx]x[y-dy, y+dy] ficam dentro da imagem
  // caso não fiquem, o respetivo lado é moldado ao limite da imagem (isto tudo, sabendo que o ponto (x, y) está dentro da imagem)

  // verificar se a abcissa do(s) píxel(eis) mais à esquerda no retângulo fica dentro da imagem
  // se não ficar, a mesma passa a ser 0 
  if (!ImageValidPos(img, xEsquerda, y)) 
    xEsquerda = 0;
  
  // verificar se a abcissa do(s) píxel(eis) mais à direita no retângulo fica dentro da imagem
  // se não ficar, a mesma passa a ser o índice limite da largura da imagem
  if (!ImageValidPos(img, xDireita, y)) 
    xDireita = (imgWidth-1);
  
  // verificar se a ordenada do(s) píxel(eis) mais acima no retângulo fica dentro da imagem
  // se não ficar, a mesma passa a ser 0 
  if (!ImageValidPos(img, x, yCima)) 
    yCima = 0;
  
  // verificar se a ordenada do(s) píxel(eis) mais abaixo no retângulo fica dentro da imagem
  // se não ficar, a mesma passa a ser o índice limite da altura da imagem
  if (!ImageValidPos(img, x, yBaixo)) 
    yBaixo = (imgHeight-1);
  
  // sabendo os limites finais do retângulo, percorrem-se os seus píxeis todos
  for (int i=xEsquerda; i<=xDireita; i++) {
    for (int j=yCima; j<=yBaixo; j++) {
      pixelCount++;                     // adiciona 1 píxel à contagem
      sum += ImageGetPixel(img, i, j);  // adiciona o seu valor à soma
    }
  }

  // no fim, devolve a média dos valores dos píxeis do retângulo
  return (uint8) (((sum+pixelCount/2)/pixelCount)); // somar ao numerador metade do denominador porque sum é inteiro
                                                    // outra forma seria passar sum para double e somas 0.5 no final para arrendondar para cima
  }



/// Blur an image by a applying a (2dx+1)x(2dy+1) mean filter.
/// Each pixel is substituted by the mean of the pixels in the rectangle
/// [x-dx, x+dx]x[y-dy, y+dy].
/// The image is changed in-place.
//int rectWidth = 2*dx + 1;
//int rectHeight = 2*dy + 1;
void ImageBlur(Image img, int dx, int dy) { ///
  // Insert your code here!

  int imgWidth = ImageWidth(img);   // obter a largura
  int imgHeight = ImageHeight(img); // obter a altura
  int imgMaxVal = ImageMaxval(img); // obter o nível máximo de cinza na imagem
  int mean; // variável que conterá a média cada iteração
  
  // criámos uma nova imagem igual à original (cópia), para podermos calcular a média de cada píxel de acordo com os valores originais dos píxeis, 
  // e não de acordo com a média deles, calculada nas iterações anteriores
  Image img2 = ImageCreate(imgWidth, imgHeight, imgMaxVal); 
  if (img2 == NULL) {
    errsave = errno; // erro que vem de ImageCreate() (?)
    ImageDestroy(&img2);
    errno = errsave;  // caso tenha ocorrido erro em ImageDestroy(), o errno continua a conter o valor do erro que ocorreu em ImageCreate()
    errCause = "Failed to create a new image.";
    return ;
  }

  // copiar os valores de cada píxel da imagem original para a sua cópia
  for (int i=0; i<=imgHeight*imgWidth; i++) {
    img2->pixel[i] = img->pixel[i];
  }

  // percorrer todos os píxeis na imagem original
  for (int x=0; x<imgWidth; x++) {
    for (int y=0; y<imgHeight; y++) {

      // em cada píxel, usamos a função criada em cima (rectMeanCalc()) que devolve a média calculada dos 
      // valores dos píxeis no retângulo [x-dx, x+dx]x[y-dy, y+dy];
      // passsamos a "img2" (cópia) como argumento, para a média ser efetuada com os valores originais 
      // dos píxeis da imagem, sem sofrerem as alterações feitas nas iterações anteriores
      mean = rectMeanCalc(img2, x, y, dx, dy); 

      // em seguida, substituímos o valor do píxel desta iteração pela média calculada
      ImageSetPixel(img, x, y, mean);
    }
  }
}

