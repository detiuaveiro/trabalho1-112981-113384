// imageTest - A program that performs some image processing.
//
// This program is an example use of the image8bit module,
// a programming project for the course AED, DETI / UA.PT
//
// You may freely use and modify this code, NO WARRANTY, blah blah,
// as long as you give proper credit to the original and subsequent authors.
//
// João Manuel Rodrigues <jmr@ua.pt>
// 2023

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
  if (argc != 7) {
    error(1, 0, "Usage: imageTest input.pgm output.pgm");
  }

  ImageInit();
  

  // imagem para colar nas outras 3 imagens
  Image imageToPaste = ImageLoad(argv[1]);
  if (imageToPaste == NULL) {
    error(2, errno, "Loading %s: %s", argv[1], ImageErrMsg());
  }

  // imagem grande
  Image image1 = ImageLoad(argv[2]);
  if (image1 == NULL) {
      error(2, errno, "Loading %s: %s", argv[2], ImageErrMsg());
  }

  // imagem grande 2
  Image image2 = ImageLoad(argv[3]);
  if (image2 == NULL) {
      error(2, errno, "Loading %s: %s", argv[3], ImageErrMsg());
  }

  // imagem media
  Image image3 = ImageLoad(argv[4]);
  if (image3 == NULL) {
      error(2, errno, "Loading %s: %s", argv[4], ImageErrMsg());
  }

  // imagem media 2
  Image image4 = ImageLoad(argv[5]);
  if (image4 == NULL) {
      error(2, errno, "Loading %s: %s", argv[5], ImageErrMsg());
  }

  // imagem imagem pequena
  Image image5 = ImageLoad(argv[6]);
  if (image5 == NULL) {
      error(2, errno, "Loading %s: %s", argv[6], ImageErrMsg());
  }

  // as seguintes linhas criam as imagens que serão usadas para testar a função ImageLocateSubImage
  // estas imagens possuem tamanhos diferentes e a subimagem está presente no centro
  int X1 = (ImageWidth(image1) - ImageWidth(imageToPaste)) / 2;
  int Y1 = (ImageHeight(image1) - ImageHeight(imageToPaste)) / 2;
  ImagePaste(image1, X1, Y1, imageToPaste);

  int X2 = (ImageWidth(image2) - ImageWidth(imageToPaste)) / 2;
  int Y2 = (ImageHeight(image2) - ImageHeight(imageToPaste)) / 2;
  ImagePaste(image2, X2, Y2, imageToPaste);

  int X3 = (ImageWidth(image3) - ImageWidth(imageToPaste)) / 2;
  int Y3 = (ImageHeight(image3) - ImageHeight(imageToPaste)) / 2;
  ImagePaste(image3, X3, Y3, imageToPaste);

  int X4 = (ImageWidth(image4) - ImageWidth(imageToPaste)) / 2;
  int Y4 = (ImageHeight(image4) - ImageHeight(imageToPaste)) / 2;
  ImagePaste(image4, X4, Y4, imageToPaste);

  int X5 = (ImageWidth(image5) - ImageWidth(imageToPaste)) / 2;
  int Y5 = (ImageHeight(image5) - ImageHeight(imageToPaste)) / 2;
  ImagePaste(image5, X5, Y5, imageToPaste);

  

  // Testar a função:

  // Variáveis para armazenar as posições encontradas
  int px, py;

  // Testar a função ImageLocateSubImage na imagem 1

  InstrReset();
  printf("\n");
  printf("Imagem 1:\n");
  if (ImageLocateSubImage(image1, &px, &py, imageToPaste)) {
      printf("Subimagem encontrada na imagem 1. Posição: (%d, %d)\n", px, py);
  } else {
      printf("Subimagem não encontrada na imagem 1.\n");
  }
  InstrPrint();

  // Testar a função ImageLocateSubImage na imagem 2

  InstrReset();
  printf("\n");
  printf("Imagem 2:\n");
  if (ImageLocateSubImage(image2, &px, &py, imageToPaste)) {
      printf("Subimagem encontrada na imagem 2. Posição: (%d, %d)\n", px, py);
  } else {
      printf("Subimagem não encontrada na imagem 2.\n");
  }
  InstrPrint();

  // Testar a função ImageLocateSubImage na imagem 3

  InstrReset();
  printf("\n");
  printf("Imagem 3:\n");
  if (ImageLocateSubImage(image3, &px, &py, imageToPaste)) {
      printf("Subimagem encontrada na imagem 3. Posição: (%d, %d)\n", px, py);
  } else {
      printf("Subimagem não encontrada na imagem 3.\n");
  }
  InstrPrint();

  // Testar a função ImageLocateSubImage na imagem 4

  InstrReset();
  printf("\n");
  printf("Imagem 4:\n");
  if (ImageLocateSubImage(image4, &px, &py, imageToPaste)) {
      printf("Subimagem encontrada na imagem 4. Posição: (%d, %d)\n", px, py);
  } else {
      printf("Subimagem não encontrada na imagem 4.\n");
  }
  InstrPrint();

  // Testar a função ImageLocateSubImage na imagem 5

  InstrReset();
  printf("\n");
  printf("Imagem 5:\n");
  if (ImageLocateSubImage(image5, &px, &py, imageToPaste)) {
      printf("Subimagem encontrada na imagem 5. Posição: (%d, %d)\n", px, py);
  } else {
      printf("Subimagem não encontrada na imagem 5.\n");
  }
  InstrPrint();

  ImageDestroy(&imageToPaste);
  ImageDestroy(&image1);
  ImageDestroy(&image2);
  ImageDestroy(&image3);
  ImageDestroy(&image4);
  ImageDestroy(&image5);
  return 0;
}

