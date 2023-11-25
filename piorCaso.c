#include <assert.h>
#include <errno.h>
#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "image8bit.h"
#include "instrumentation.h"

int main(int argc, char* argv[]) {
  program_name = argv[0];
  

  ImageInit();
  

  // imagem para colar nas outras 3 imagens
  Image imageToPaste = ImageCreate(300, 300, 255);
  ImageSetPixel(imageToPaste, 299, 299, 255); 
  if (imageToPaste == NULL) {
    error(2, errno, "Creating imageToPaste: %s", ImageErrMsg());
  }

  Image image1 = ImageCreate(500, 500, 255);
  ImageSetPixel(image1, 499, 499, 255); 
  if (image1 == NULL) {
    error(2, errno, "Creating image1: %s", ImageErrMsg());
  }

  Image image2 = ImageCreate(450, 450, 255);
  ImageSetPixel(image2, 449, 449, 255); 
  if (image2 == NULL) {
    error(2, errno, "Creating image2: %s", ImageErrMsg());
  }

  Image image3 = ImageCreate(400, 400, 255);
  ImageSetPixel(image3, 399, 399, 255); 
  if (image3 == NULL) {
    error(2, errno, "Creating image3: %s", ImageErrMsg());
  }

  Image image4 = ImageCreate(350, 350, 255);
  ImageSetPixel(image4, 349, 349, 255); 
  if (image4 == NULL) {
    error(2, errno, "Creating image4: %s", ImageErrMsg());
  }

  int px, py;

  printf("Mantém-se o tamanho da imagem a ser colada e varia-se o tamanho da imagem onde se dá paste.\n");

  InstrReset();
  printf("\n");
  printf("Imagem 1 (500x500):\n");
  if (ImageLocateSubImage(image1, &px, &py, imageToPaste)) {
      printf("Subimagem encontrada na imagem 1. Posição: (%d, %d)\n", px, py);
  } else {
      printf("Subimagem não encontrada na imagem 1.\n");
  }
  InstrPrint();

  InstrReset();
  printf("\n");
  printf("Imagem 2 (450x450):\n");
  if (ImageLocateSubImage(image2, &px, &py, imageToPaste)) {
      printf("Subimagem encontrada na imagem 2. Posição: (%d, %d)\n", px, py);
  } else {
      printf("Subimagem não encontrada na imagem 2.\n");
  }
  InstrPrint();

  InstrReset();
  printf("\n");
  printf("Imagem 3 (400x400):\n");
  if (ImageLocateSubImage(image3, &px, &py, imageToPaste)) {
      printf("Subimagem encontrada na imagem 3. Posição: (%d, %d)\n", px, py);
  } else {
      printf("Subimagem não encontrada na imagem 3.\n");
  }
  InstrPrint();

  InstrReset();
  printf("\n");
  printf("Imagem 4 (350x350):\n");
  if (ImageLocateSubImage(image4, &px, &py, imageToPaste)) {
      printf("Subimagem encontrada na imagem 4. Posição: (%d, %d)\n", px, py);
  } else {
      printf("Subimagem não encontrada na imagem 4.\n");
  }
  InstrPrint();

  printf("\n");
  printf("-------------------------------------------------------------------------------\n");
  printf("Mantém-se o tamanho da imagem onde se dá paste e varia-se o tamanho da imagem a ser colada.\n");

  InstrReset();
  printf("\n");
  printf("Subimagem 1 (300x300):\n");
  if (ImageLocateSubImage(image1, &px, &py, imageToPaste)) {
      printf("Subimagem encontrada. Posição: (%d, %d)\n", px, py);
  } else {
      printf("Subimagem não encontrada na imagem 1.\n");
  }
  InstrPrint();

  InstrReset();
  printf("\n");
  printf("Subimagem 2 (350x350):\n");
  if (ImageLocateSubImage(image1, &px, &py, image4)) {
      printf("Subimagem encontrada. Posição: (%d, %d)\n", px, py);
  } else {
      printf("Subimagem não encontrada na imagem 2.\n");
  }
  InstrPrint();

  InstrReset();
  printf("\n");
  printf("Subimagem 3 (400x400):\n");
  if (ImageLocateSubImage(image1, &px, &py, image3)) {
      printf("Subimagem encontrada. Posição: (%d, %d)\n", px, py);
  } else {
      printf("Subimagem não encontrada na imagem 3.\n");
  }
  InstrPrint();

  InstrReset();
  printf("\n");
  printf("Subimagem 4 (450x450):\n");
  if (ImageLocateSubImage(image1, &px, &py, image2)) {
      printf("Subimagem encontrada. Posição: (%d, %d)\n", px, py);
  } else {
      printf("Subimagem não encontrada na imagem 4.\n");
  }
  InstrPrint();

  ImageDestroy(&imageToPaste);
  ImageDestroy(&image1);
  ImageDestroy(&image2);
  ImageDestroy(&image3);
  ImageDestroy(&image4);
  
  return 0;
}