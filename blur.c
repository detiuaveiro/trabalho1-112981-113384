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

    /* Inicializar */
    ImageInit(); 
    

    /* Criar a imagem original, para depois cortá-la nas dimensões desejadas para os testes */
    Image referenceImage = ImageLoad(argv[1]);
    if (referenceImage == NULL) {
        error(2, errno, "Loading %s: %s", argv[1], ImageErrMsg());
    }

    Image image1 = ImageCrop(referenceImage, 0, 0, 400, 400);
    if (image1 == NULL) {
        printf("Erro ao cortar a imagem.");
    }

    Image image2 = ImageCrop(referenceImage, 0, 0, 350, 350);
    if (image2 == NULL) {
        printf("Erro ao cortar a imagem.");
    }

    Image image3 = ImageCrop(referenceImage, 0, 0, 300, 300);
    if (image3 == NULL) {
        printf("Erro ao cortar a imagem.");
    }

    Image image4 = ImageCrop(referenceImage, 0, 0, 250, 250);
    if (image4 == NULL) {
        printf("Erro ao cortar a imagem.");
    }

    Image image5 = ImageCrop(referenceImage, 0, 0, 200, 200);
    if (image5 == NULL) {
        printf("Erro ao cortar a imagem.");
    }

    Image image6 = ImageCrop(referenceImage, 0, 0, 150, 150);
    if (image6 == NULL) {
        printf("Erro ao cortar a imagem.");
    }

    Image image7 = ImageCrop(referenceImage, 0, 0, 100, 100);
    if (image7 == NULL) {
        printf("Erro ao cortar a imagem.");
    }

    Image image8 = ImageCrop(referenceImage, 0, 0, 50, 50);
    if (image8 == NULL) {
        printf("Erro ao cortar a imagem.");
    }

    


    /* ================================ Testar a função ================================ */


    printf("\n\nContagem do número de operações da função ImageBlur() em imagens com tamanhos diferentes\n");
    printf("========================================================================================\n\n");

    InstrReset();
    printf("Imagem 1 : 400x400\n");
    ImageBlur(image1, ImageWidth(image1), ImageHeight(image1));
    InstrPrint();

    printf("----------------------------------------------------------------------------------------\n");

    InstrReset();
    printf("Imagem 2 : 350x350\n");
    ImageBlur(image2, ImageWidth(image2), ImageHeight(image2));
    InstrPrint();

    printf("----------------------------------------------------------------------------------------\n");

    InstrReset();
    printf("Imagem 3 : 300x300\n");
    ImageBlur(image3, ImageWidth(image3), ImageHeight(image3));
    InstrPrint();

    printf("----------------------------------------------------------------------------------------\n");

    InstrReset();
    printf("Imagem 4 : 250x250\n");
    ImageBlur(image4, ImageWidth(image4), ImageHeight(image4));
    InstrPrint();

    printf("----------------------------------------------------------------------------------------\n");

    InstrReset();
    printf("Imagem 5 : 200x200\n");
    ImageBlur(image5, ImageWidth(image5), ImageHeight(image5));
    InstrPrint();

    printf("----------------------------------------------------------------------------------------\n");

    InstrReset();
    printf("Imagem 6 : 150x150\n");
    ImageBlur(image6, ImageWidth(image6), ImageHeight(image6));
    InstrPrint();

    printf("----------------------------------------------------------------------------------------\n");

    InstrReset();
    printf("Imagem 7 : 100x100\n");
    ImageBlur(image7, ImageWidth(image7), ImageHeight(image7));
    InstrPrint();

    printf("----------------------------------------------------------------------------------------\n");

    InstrReset();
    printf("Imagem 8 : 50x50\n");
    ImageBlur(image8, ImageWidth(image8), ImageHeight(image8));
    InstrPrint();

    printf("\n========================================================================================\n");
    

    /* Destruir as imagens (libertar o espaço) */
    ImageDestroy(&referenceImage);
    ImageDestroy(&image1);
    ImageDestroy(&image2);
    ImageDestroy(&image3);
    ImageDestroy(&image4);
    ImageDestroy(&image5);
    ImageDestroy(&image6);
    ImageDestroy(&image7);
    ImageDestroy(&image8);

    return 0;
}