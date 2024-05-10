#ifndef HABITAT_H
#define HABITAT_H

#include "Canli.h"

struct Node {
    struct CANLI* data;
    struct Node* next;
};

void dosyadanOku(const char* dosyaAdi, struct Node** head, int* rowCount, int* columnCount);
void ekranaYazdir(struct Node* head, int rowCount, int columnCount);
void canliSavasi(struct Node** head, int rowCount, int columnCount);

#endif