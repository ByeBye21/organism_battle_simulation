#ifndef CANLI_H
#define CANLI_H

struct CANLI {
    char* (*gorunum)();
    int row;
    int column;
    int value;
};

struct CANLI* canliTurunuBelirle(int deger, int row, int column);
int kazananCanli(struct CANLI* canli1, struct CANLI* canli2);

#endif