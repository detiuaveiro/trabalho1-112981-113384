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
  Image imageToPaste = ImageLoad(argv[1]);
  if (imageToPaste == NULL) {
    error(2, errno, "Loading %s: %s", argv[1], ImageErrMsg());
  }

  // imagem grande
  Image imageLarge = ImageLoad(argv[2]);
  if (imageLarge == NULL) {
      error(2, errno, "Loading %s: %s", argv[2], ImageErrMsg());
  }

  // imagem media
  Image imageMedium = ImageLoad(argv[3]);
  if (imageMedium == NULL) {
      error(2, errno, "Loading %s: %s", argv[3], ImageErrMsg());
  }

  // imagem imagem pequena
  Image imageSmall = ImageLoad(argv[4]);
  if (imageSmall == NULL) {
      error(2, errno, "Loading %s: %s", argv[4], ImageErrMsg());
  }

  Image image = ImageCreate(400, 400, 255);
  if (image == NULL) {
    error(2, errno, "Creating image: %s", ImageErrMsg());
  }

  Image subimage1 = ImageCrop(image, 0, 0, 1, 1);
  if (subimage1 == NULL) {
    error(2, errno, "Creating subimage1: %s", ImageErrMsg());
  }

  Image subimage2 = ImageCrop(image, 0, 0, 50, 50);
  if (subimage2 == NULL) {
    error(2, errno, "Creating subimage2: %s", ImageErrMsg());
  }

  Image subimage3 = ImageCrop(image, 0, 0, 100, 100);
  if (subimage3 == NULL) {
    error(2, errno, "Creating subimage3: %s", ImageErrMsg());
  }

  Image subimage4 = ImageCrop(image, 0, 0, 150, 150);
  if (subimage4 == NULL) {
    error(2, errno, "Creating subimage4: %s", ImageErrMsg());
  }

  Image subimage5 = ImageCrop(image, 0, 0, 200, 200);
  if (subimage5 == NULL) {
    error(2, errno, "Creating subimage5: %s", ImageErrMsg());
  }

  Image subimage6 = ImageCrop(image, 0, 0, 250, 250);
  if (subimage6 == NULL) {
    error(2, errno, "Creating subimage6: %s", ImageErrMsg());
  }

  Image subimage7 = ImageCrop(image, 0, 0, 300, 300);
  if (subimage7 == NULL) {
    error(2, errno, "Creating subimage7: %s", ImageErrMsg());
  }

  Image subimage8 = ImageCrop(image, 0, 0, 350, 350);
  if (subimage8 == NULL) {
    error(2, errno, "Creating subimage8: %s", ImageErrMsg());
  }


  // as seguintes linhas criam as imagens que serão usadas para testar a função ImageLocateSubImage
  // estas imagens possuem tamanhos diferentes e a subimagem está presente no início
  ImagePaste(imageLarge, 0, 0, imageToPaste);
  ImagePaste(imageMedium, 0, 0, imageToPaste);
  ImagePaste(imageSmall, 0, 0, imageToPaste);

  // dar save apenas para verificar se as imagens criadas eram o que esperavamos para poder testar
  if (ImageSave(imageLarge, argv[5]) == 0) {
    error(2, errno, "%s: %s", argv[5], ImageErrMsg());
  }
  if (ImageSave(imageMedium, argv[6]) == 0) {
    error(2, errno, "%s: %s", argv[6], ImageErrMsg());
  }
  if (ImageSave(imageSmall, argv[7]) == 0) {
    error(2, errno, "%s: %s", argv[7], ImageErrMsg());
  }

  // Testar a função:

  // Variáveis para armazenar as posições encontradas
  int px, py;

  // Testar a função ImageLocateSubImage na imagem grande

  printf("\n\nContagem do número de comparações da função ImageLocateSubImage() em imagens com tamanhos diferentes para uma subimagem (256x256)\n");
  printf("=================================================================================================================================\n\n");

  InstrReset();
  printf("Imagem 1 : 940x940\n");
  if (ImageLocateSubImage(imageLarge, &px, &py, imageToPaste)) {
      InstrPrint();
  } else {
      printf("Subimagem não encontrada na imagem grande.\n");
  }
  printf("---------------------------------------------------------------------------------------------------------------------------------\n");

  // Testar a função ImageLocateSubImage na imagem média

  InstrReset();
  printf("Imagem 2 : 640x480\n");
  if (ImageLocateSubImage(imageMedium, &px, &py, imageToPaste)) {
      InstrPrint();
  } else {
      printf("Subimagem não encontrada na imagem média.\n");
  }
  printf("---------------------------------------------------------------------------------------------------------------------------------\n");

  // Testar a função ImageLocateSubImage na imagem pequena

  InstrReset();
  printf("Imagem 3 : 300x300\n");
  if (ImageLocateSubImage(imageSmall, &px, &py, imageToPaste)) {
      InstrPrint();
  } else {
      printf("Subimagem não encontrada na imagem pequena.\n");
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
  

  ImageDestroy(&imageToPaste);
  ImageDestroy(&imageLarge);
  ImageDestroy(&imageMedium);
  ImageDestroy(&imageSmall);
  ImageDestroy(&image);
  ImageDestroy(&subimage1);
  ImageDestroy(&subimage2);
  ImageDestroy(&subimage3);
  ImageDestroy(&subimage4);
  ImageDestroy(&subimage5);
  ImageDestroy(&subimage6);
  ImageDestroy(&subimage7);
  return 0;
}