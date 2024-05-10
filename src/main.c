#include "Habitat.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    const char* dosyaAdi = "Veri.txt";
    int rowCount, columnCount;
    struct Node* head = NULL;

    //Dosyadan verileri oku ve bağlı listeyi oluşturuyoruz
    dosyadanOku(dosyaAdi, &head, &rowCount, &columnCount);

    //Ekrana bağlı listeyi yazdırıyoruz
    ekranaYazdir(head, rowCount, columnCount);

    printf("\nSavasi Baslatmak Icin Enter'a Basiniz....\n");
    getchar();

    //Yeme savaşını başlatıyoruz
    canliSavasi(&head, rowCount, columnCount);

    //Son kalan canlının konumunu yazdırıyoruz
    printf("Kazanan: %s : (%d, %d)\n", head->data->gorunum(), head->data->row, head->data->column);

    //Bağlı listede kalan son düğümü siliyoruz
    free(head->data);
    free(head);

    return 0;
}