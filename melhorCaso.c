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

  printf("Mantém-se o tamanho da imagem a ser colada e varia-se o tamanho da imagem onde se dá paste.\n");

  InstrReset();
  printf("\n");
  printf("Imagem grande (940x940):\n");
  if (ImageLocateSubImage(imageLarge, &px, &py, imageToPaste)) {
      printf("Subimagem encontrada na imagem grande. Posição: (%d, %d)\n", px, py);
  } else {
      printf("Subimagem não encontrada na imagem grande.\n");
  }
  InstrPrint();

  // Testar a função ImageLocateSubImage na imagem média

  InstrReset();
  printf("\n");
  printf("Imagem média (640x480):\n");
  if (ImageLocateSubImage(imageMedium, &px, &py, imageToPaste)) {
      printf("Subimagem encontrada na imagem média. Posição: (%d, %d)\n", px, py);
  } else {
      printf("Subimagem não encontrada na imagem média.\n");
  }
  InstrPrint();

  // Testar a função ImageLocateSubImage na imagem pequena

  InstrReset();
  printf("\n");
  printf("Imagem pequena (300x300):\n");
  if (ImageLocateSubImage(imageSmall, &px, &py, imageToPaste)) {
      printf("Subimagem encontrada na imagem pequena. Posição: (%d, %d)\n", px, py);
  } else {
      printf("Subimagem não encontrada na imagem pequena.\n");
  }
  InstrPrint();

  printf("\n");
  printf("-------------------------------------------------------------------------------\n");
  printf("Mantém-se o tamanho da imagem onde se dá paste e varia-se o tamanho da imagem a ser colada.\n");

  Image subimage1 = ImageCrop(imageLarge, 0, 0, 100, 100);
  if (subimage1 == NULL) {
    error(2, errno, "Creating subimage1: %s", ImageErrMsg());
  }

  Image subimage2 = ImageCrop(imageLarge, 0, 0, 200, 200);
  if (subimage2 == NULL) {
    error(2, errno, "Creating subimage2: %s", ImageErrMsg());
  }

  Image subimage3 = ImageCrop(imageLarge, 0, 0, 300, 300);
  if (subimage3 == NULL) {
    error(2, errno, "Creating subimage3: %s", ImageErrMsg());
  }

  Image subimage4 = ImageCrop(imageLarge, 0, 0, 400, 400);
  if (subimage4 == NULL) {
    error(2, errno, "Creating subimage4: %s", ImageErrMsg());
  }

  InstrReset();
  printf("\n");
  printf("Subimagem 1 (100x100):\n");
  if (ImageLocateSubImage(imageLarge, &px, &py, subimage1)) {
      printf("Subimagem 1 encontrada. Posição: (%d, %d)\n", px, py);
  } else {
      printf("Subimagem 1 não encontrada.\n");
  }
  InstrPrint();

  InstrReset();
  printf("\n");
  printf("Subimagem 2 (200x200):\n");
  if (ImageLocateSubImage(imageLarge, &px, &py, subimage2)) {
      printf("Subimagem 2 encontrada. Posição: (%d, %d)\n", px, py);
  } else {
      printf("Subimagem 2 não encontrada.\n");
  }
  InstrPrint();

  InstrReset();
  printf("\n");
  printf("Subimagem 3 (300x300):\n");
  if (ImageLocateSubImage(imageLarge, &px, &py, subimage3)) {
      printf("Subimagem 3 encontrada. Posição: (%d, %d)\n", px, py);
  } else {
      printf("Subimagem 3 não encontrada.\n");
  }
  InstrPrint();

  InstrReset();
  printf("\n");
  printf("Subimagem 4 (400x400):\n");
  if (ImageLocateSubImage(imageLarge, &px, &py, subimage4)) {
      printf("Subimagem 4 encontrada. Posição: (%d, %d)\n", px, py);
  } else {
      printf("Subimagem 4 não encontrada.\n");
  }
  InstrPrint();
  

  ImageDestroy(&imageToPaste);
  ImageDestroy(&imageLarge);
  ImageDestroy(&imageMedium);
  ImageDestroy(&imageSmall);
  ImageDestroy(&subimage1);
  ImageDestroy(&subimage2);
  ImageDestroy(&subimage3);
  ImageDestroy(&subimage4);
  return 0;
}