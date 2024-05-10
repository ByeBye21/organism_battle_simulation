#include "Canli.h"
#include "Bitki.h"
#include "Bocek.h"
#include "Sinek.h"
#include "Pire.h"
#include <stdlib.h>
#include <stdio.h>

//Canlının türünü belirleyen fonksiyon
struct CANLI* canliTurunuBelirle(int deger, int row, int column) {
    struct CANLI* canli = malloc(sizeof(struct CANLI));
    if (!canli) {
        perror("Hicbir canli bulunamadi");
        return NULL;
    }

    canli->row = row;
    canli->column = column;
    canli->value = deger;

    if (deger >= 1 && deger <= 9) {
        canli->gorunum = bitkiGorunum;
    } else if (deger >= 10 && deger <= 20) {
        canli->gorunum = bocekGorunum;
    } else if (deger >= 21 && deger <= 50) {
        canli->gorunum = sinekGorunum;
    } else if (deger >= 51 && deger <= 99) {
        canli->gorunum = pireGorunum;
    } else {
        free(canli); //Tahsis edilmiş hafızayı NULL döndürmeden önce serbest bırakıyoruz
        return NULL;
    }

    return canli;
}

//Bir canlı başka bir canlıyı yiyip yiyemeyeceğini belirleyen fonksiyon
int kazananCanli(struct CANLI* canli1, struct CANLI* canli2) {

    //Savaşan canlıların türünü kontrol ediyoruz
    if (canli1->value >= 1 && canli1->value <= 9) { // Bitki
        if (canli2->value >= 10 && canli2->value <= 20) // Böcek
            return 0;
        if (canli2->value >= 21 && canli2->value <= 50) // Sinek
            return 1;
        if (canli2->value >= 51 && canli2->value <= 99) // Pire
            return 1;
    } else if (canli1->value >= 10 && canli1->value <= 20) { // Böcek
        if (canli2->value >= 1 && canli2->value <= 9) // Bitki
            return 1;
        if (canli2->value >= 21 && canli2->value <= 50) // Sinek
            return 0;
        if (canli2->value >= 51 && canli2->value <= 99) // Pire
            return 1;
    } else if (canli1->value >= 21 && canli1->value <= 50) { // Sinek
        if (canli2->value >= 1 && canli2->value <= 9) // Bitki
            return 0;
        if (canli2->value >= 10 && canli2->value <= 20) // Böcek
            return 1;
        if (canli2->value >= 51 && canli2->value <= 99) // Pire
            return 1;
    } else if (canli1->value >= 51 && canli1->value <= 99) { // Pire
        if (canli2->value >= 1 && canli2->value <= 9) // Bitki
            return 0;
        if (canli2->value >= 10 && canli2->value <= 20) // Böcek
            return 1;
        if (canli2->value >= 21 && canli2->value <= 50) // Sinek
            return 1;
    }
    //Her iki organizma da aynı türden ise
    if (canli1->value >= canli2->value) {
        return 1; //canli1 kazanır
    }
    if (canli1->value < canli2->value) {
        return 0; //canli2 kazanır
    }
}