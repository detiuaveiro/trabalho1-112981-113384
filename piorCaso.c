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
  


  Image subimage = ImageCreate(100, 100, 255);
  ImageSetPixel(subimage, 99, 99, 255); 
  if (subimage == NULL) {
    error(2, errno, "Creating subimage: %s", ImageErrMsg());
  }

  Image image = ImageCreate(400, 400, 255);
  ImageSetPixel(image, 399, 399, 255); 
  if (image == NULL) {
    error(2, errno, "Creating image: %s", ImageErrMsg());
  }

  Image image1 = ImageCreate(100, 100, 255);
  ImageSetPixel(image1, 99, 99, 255); 
  if (image1 == NULL) {
    error(2, errno, "Creating image1: %s", ImageErrMsg());
  }

  Image image2 = ImageCreate(150, 150, 255);
  ImageSetPixel(image2, 149, 149, 255); 
  if (image2 == NULL) {
    error(2, errno, "Creating image2: %s", ImageErrMsg());
  }

  Image image3 = ImageCreate(200, 200, 255);
  ImageSetPixel(image3, 199, 199, 255); 
  if (image3 == NULL) {
    error(2, errno, "Creating image3: %s", ImageErrMsg());
  }

  Image image4 = ImageCreate(250, 250, 255);
  ImageSetPixel(image4, 249, 249, 255); 
  if (image4 == NULL) {
    error(2, errno, "Creating image4: %s", ImageErrMsg());
  }

  Image image5 = ImageCreate(300, 300, 255);
  ImageSetPixel(image5, 299, 299, 255); 
  if (image5 == NULL) {
    error(2, errno, "Creating image5: %s", ImageErrMsg());
  }

  Image subimage1 = ImageCreate(1, 1, 255);
  ImageSetPixel(subimage1, 0, 0, 255); 
  if (subimage1 == NULL) {
    error(2, errno, "Creating subimage1: %s", ImageErrMsg());
  }

  Image subimage2 = ImageCreate(50, 50, 255);
  ImageSetPixel(subimage2, 49, 49, 255); 
  if (subimage2 == NULL) {
    error(2, errno, "Creating subimage2: %s", ImageErrMsg());
  }

  Image subimage3 = ImageCreate(100, 100, 255);
  ImageSetPixel(subimage3, 99, 99, 255); 
  if (subimage3 == NULL) {
    error(2, errno, "Creating subimage3: %s", ImageErrMsg());
  }

  Image subimage4 = ImageCreate(150, 150, 255);
  ImageSetPixel(subimage4, 149, 149, 255); 
  if (subimage4 == NULL) {
    error(2, errno, "Creating subimage4: %s", ImageErrMsg());
  }

  Image subimage5 = ImageCreate(200, 200, 255);
  ImageSetPixel(subimage5, 199, 199, 255); 
  if (subimage5 == NULL) {
    error(2, errno, "Creating subimage5: %s", ImageErrMsg());
  }

  Image subimage6 = ImageCreate(250, 250, 255);
  ImageSetPixel(subimage6, 249, 249, 255); 
  if (subimage6 == NULL) {
    error(2, errno, "Creating subimage6: %s", ImageErrMsg());
  }

  Image subimage7 = ImageCreate(300, 300, 255);
  ImageSetPixel(subimage7, 299, 299, 255); 
  if (subimage7 == NULL) {
    error(2, errno, "Creating subimage7: %s", ImageErrMsg());
  }

  Image subimage8 = ImageCreate(350, 350, 255);
  ImageSetPixel(subimage8, 349, 349, 255); 
  if (subimage8 == NULL) {
    error(2, errno, "Creating subimage8: %s", ImageErrMsg());
  }

  int px, py;

  printf("\n\nContagem do número de comparações da função ImageLocateSubImage() em imagens com tamanhos diferentes para uma subimagem (100x100)\n");
  printf("=================================================================================================================================\n\n");


  InstrReset();
  printf("Imagem 1 : 100x100\n");
  if (ImageLocateSubImage(image1, &px, &py, subimage)) {
      InstrPrint();
  } else {
      printf("Subimagem não encontrada na imagem.\n");
  }
  printf("---------------------------------------------------------------------------------------------------------------------------------\n");

  InstrReset();
  printf("Imagem 2 : 150x150\n");
  if (ImageLocateSubImage(image2, &px, &py, subimage)) {
      InstrPrint();
  } else {
      printf("Subimagem não encontrada na imagem.\n");
  }
  printf("---------------------------------------------------------------------------------------------------------------------------------\n");


  InstrReset();
  printf("\n");
  printf("Imagem 3 : 200x200\n");
  if (ImageLocateSubImage(image3, &px, &py, subimage)) {
      InstrPrint();
  } else {
      printf("Subimagem não encontrada na imagem.\n");
  }
  printf("---------------------------------------------------------------------------------------------------------------------------------\n");

  InstrReset();
  printf("Imagem 4 : 250x250\n");
  if (ImageLocateSubImage(image4, &px, &py, subimage)) {
      InstrPrint();
  } else {
      printf("Subimagem não encontrada na imagem.\n");
  }
  printf("---------------------------------------------------------------------------------------------------------------------------------\n");

  InstrReset();
  printf("Imagem 5 : 300x300\n");
  if (ImageLocateSubImage(image5, &px, &py, subimage)) {
      InstrPrint();
  } else {
      printf("Subimagem não encontrada na imagem.\n");
  }
  printf("\n=================================================================================================================================\n");

  printf("\n\nContagem do número de comparações da função ImageLocateSubImage() em subimagens com tamanhos diferentes para uma imagem (400x400)\n");
  printf("=================================================================================================================================\n\n");

  InstrReset();
  printf("Subimagem 1 : 1x1\n");
  if (ImageLocateSubImage(image, &px, &py, subimage1)) {
      InstrPrint();
  } else {
      printf("Subimagem não encontrada na imagem.\n");
  }
  printf("---------------------------------------------------------------------------------------------------------------------------------\n");

  InstrReset();
  printf("Subimagem 2 : 50x50\n");
  if (ImageLocateSubImage(image, &px, &py, subimage2)) {
      InstrPrint();
  } else {
      printf("Subimagem não encontrada na imagem.\n");
  }
  printf("---------------------------------------------------------------------------------------------------------------------------------\n");

  InstrReset();
  printf("Subimagem 3 : 100x100\n");
  if (ImageLocateSubImage(image, &px, &py, subimage3)) {
      InstrPrint();
  } else {
      printf("Subimagem não encontrada na imagem.\n");
  }
  printf("---------------------------------------------------------------------------------------------------------------------------------\n");

  InstrReset();
  printf("Subimagem 4 : 150x150\n");
  if (ImageLocateSubImage(image, &px, &py, subimage4)) {
      InstrPrint();
  } else {
      printf("Subimagem não encontrada na imagem.\n");
  }
  printf("---------------------------------------------------------------------------------------------------------------------------------\n");

  InstrReset();
  printf("Subimagem 5 : 200x200\n");
  if (ImageLocateSubImage(image, &px, &py, subimage5)) {
      InstrPrint();
  } else {
      printf("Subimagem não encontrada na imagem.\n");
  }
  printf("---------------------------------------------------------------------------------------------------------------------------------\n");

  InstrReset();
  printf("Subimagem 6 : 250x250\n");
  if (ImageLocateSubImage(image, &px, &py, subimage6)) {
      InstrPrint();
  } else {
      printf("Subimagem não encontrada na imagem.\n");
  }
  printf("---------------------------------------------------------------------------------------------------------------------------------\n");

  InstrReset();
  printf("Subimagem 7 : 300x300\n");
  if (ImageLocateSubImage(image, &px, &py, subimage7)) {
      InstrPrint();
  } else {
      printf("Subimagem não encontrada na imagem.\n");
  }
  printf("---------------------------------------------------------------------------------------------------------------------------------\n");

  InstrReset();
  printf("Subimagem 8 : 350x350\n");
  if (ImageLocateSubImage(image, &px, &py, subimage8)) {
      InstrPrint();
  } else {
      printf("Subimagem não encontrada na imagem.\n");
  }
  printf("---------------------------------------------------------------------------------------------------------------------------------\n");

  InstrReset();
  printf("Subimagem 9 : 400x400\n");
  if (ImageLocateSubImage(image, &px, &py, image)) {
      InstrPrint();
  } else {
      printf("Subimagem não encontrada na imagem.\n");
  }
  printf("\n=================================================================================================================================\n");


  ImageDestroy(&subimage);
  ImageDestroy(&image);
  ImageDestroy(&image1);
  ImageDestroy(&image2);
  ImageDestroy(&image3);
  ImageDestroy(&image4);
  ImageDestroy(&image5);
  ImageDestroy(&subimage1);
  ImageDestroy(&subimage2);
  ImageDestroy(&subimage3);
  ImageDestroy(&subimage4);
  ImageDestroy(&subimage5);
  ImageDestroy(&subimage6);
  ImageDestroy(&subimage7);
  ImageDestroy(&subimage8);
  
  return 0;
}