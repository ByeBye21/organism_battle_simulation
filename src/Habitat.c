#include "Habitat.h"
#include <stdio.h>
#include <stdlib.h>

//Bir dosyadaki sayıları okuma ve canlılar için bağlı listesi oluşturma işlevi
void dosyadanOku(const char* dosya_adi, struct Node** head, int* row_count, int* column_count) {
    FILE* dosya = fopen(dosya_adi, "r");
    if (!dosya) {
        perror("HATA : Dosya acilamadi");
        return;
    }

    int deger;
    int row = 0; //Satır sayacı
    int column = 0; //Sütun sayacı
    int maxColumn = 0; //Maksimum sütun sayısı
    struct Node* lastNode = NULL; //Listedeki son düğümün işaretçisi
    while ((deger = fgetc(dosya)) != EOF) {
        if (deger == '\n') {
            row++; //Satır sayacını artır
            maxColumn = column > maxColumn ? column : maxColumn; //Gerekirse maksimum sütun sayısını güncelle
            column = 0; //Sütun sayacını sıfırla
        } else if (deger >= '0' && deger <= '9') {
            fseek(dosya, -1, SEEK_CUR); //İşaretçiyi bir karakter geriye taşı
            fscanf(dosya, "%d", &deger); //Sayıları dosyadan okuyun
            struct CANLI* canli = canliTurunuBelirle(deger, row, column);
            if (canli) {
                //Yeni bir düğüm oluştur
                struct Node* newNode = malloc(sizeof(struct Node));
                if (!newNode) {
                    perror("HATA : Dugum olusturulamadi");
                    return;
                }
                newNode->data = canli;
                newNode->next = NULL;

                //Yeni düğümü listeye ekle
                if (*head == NULL) {
                    *head = newNode; //Liste boşsa yeni düğümü head olarak ayarlıyoruz
                } else {
                    lastNode->next = newNode; //Aksi halde yeni düğümü listenin sonuna bağlıyoruz
                }
                lastNode = newNode; //
            }
            column++; //Sütun sayacını artır
        }
    }

    *row_count = row + 1; // Satır sayısını güncelle
    *column_count = maxColumn; //Maksimum sütun sayısını güncelle

    fclose(dosya);
}

//Bağlı listede saklanan canlıları yazdırma işlevi
void ekranaYazdir(struct Node* head, int rowCount, int columnCount) {
    struct Node* current = head;
    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < columnCount; j++) {
            if (current && current->data && current->data->row == i && current->data->column == j) {
                printf("%s ", current->data->gorunum()); //Canlıyı yazdır
                current = current->next;
            } else {
                printf("X "); //Bu konumda herhangi bir canlı yoksa 'X' yazdır
            }
        }
        printf("\n"); //Her satırın yazdırılması bittiğinde yeni bir satıra geç
    }
}

//Yalnızca bir canlı kalana kadar yeme sürecini simüle etme işlevi
void canliSavasi(struct Node** head, int rowCount, int columnCount) {
    struct Node* current = *head;

    //Tek bir organizma kalana kadar listeyi tekrarlıyoruz
    while (*head && (*head)->next) {
        struct CANLI* canli1 = (*head)->data;
        struct CANLI* canli2 = (*head)->next->data;

        //Ölü canlıları listeden çıkarıyoruz
        if (kazananCanli(canli1, canli2)) {
            struct Node* temp = (*head)->next;
            (*head)->next = temp->next; //Düğümü listeden kaldırıyoruz
            free(temp->data); //Canlı 2 için ayrılan hafıza
            free(temp); //Canlı 2'yi içeren düğüm için ayrılan hafıza
        } else {
            struct Node* temp = *head;
            *head = (*head)->next; //Sonraki düğüme git
            free(temp->data); //Canlı 1 için ayrılan hafıza
            free(temp); //Canlı 1'yi içeren düğüm için ayrılan hafıza
        }

        //Güncellenen bilgileri yazdırıyoruz
        system("cls"); //Ekranı temizliyoruz
        ekranaYazdir(*head, rowCount, columnCount);
    }
}