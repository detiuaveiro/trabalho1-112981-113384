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
  if (argc != 8) {
    error(1, 0, "Usage: imageTest input.pgm output.pgm");
  }

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
  // estas imagens possuem tamanhos diferentes e a subimagem está presente no fim
  int largeX = (ImageWidth(imageLarge) - ImageWidth(imageToPaste));
  int largeY = (ImageHeight(imageLarge) - ImageHeight(imageToPaste));
  ImagePaste(imageLarge, largeX, largeY, imageToPaste);

  int mediumX = (ImageWidth(imageMedium) - ImageWidth(imageToPaste));
  int mediumY = (ImageHeight(imageMedium) - ImageHeight(imageToPaste));
  ImagePaste(imageMedium, mediumX, mediumY, imageToPaste);

  int smallX = (ImageWidth(imageSmall) - ImageWidth(imageToPaste));
  int smallY = (ImageHeight(imageSmall) - ImageHeight(imageToPaste));
  ImagePaste(imageSmall, smallX, smallY, imageToPaste);

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

  InstrReset();
  printf("\n");
  printf("Imagem grande:\n");
  if (ImageLocateSubImage(imageLarge, &px, &py, imageToPaste)) {
      printf("Subimagem encontrada na imagem grande. Posição: (%d, %d)\n", px, py);
  } else {
      printf("Subimagem não encontrada na imagem grande.\n");
  }
  InstrPrint();

  // Testar a função ImageLocateSubImage na imagem média

  InstrReset();
  printf("\n");
  printf("Imagem média:\n");
  if (ImageLocateSubImage(imageMedium, &px, &py, imageToPaste)) {
      printf("Subimagem encontrada na imagem média. Posição: (%d, %d)\n", px, py);
  } else {
      printf("Subimagem não encontrada na imagem média.\n");
  }
  InstrPrint();

  // Testar a função ImageLocateSubImage na imagem pequena

  InstrReset();
  printf("\n");
  printf("Imagem pequena:\n");
  if (ImageLocateSubImage(imageSmall, &px, &py, imageToPaste)) {
      printf("Subimagem encontrada na imagem pequena. Posição: (%d, %d)\n", px, py);
  } else {
      printf("Subimagem não encontrada na imagem pequena.\n");
  }
  InstrPrint();

  ImageDestroy(&imageToPaste);
  ImageDestroy(&imageLarge);
  ImageDestroy(&imageMedium);
  ImageDestroy(&imageSmall);
  return 0;
}