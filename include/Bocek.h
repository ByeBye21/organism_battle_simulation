#ifndef BOCEK_H
#define BOCEK_H

#include "Canli.h"

//Böcek organizması tanımı
struct BOCEK {
    struct CANLI base;
};

//Böcek görünümü işlevi
char* bocekGorunum();

#endif