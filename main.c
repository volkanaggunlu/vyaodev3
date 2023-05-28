#include <stdio.h>
#include <stdlib.h>
#include <math.h>// gerekli k�t�phaneler tan�mlan�r.

#define TANIMSIZ -1// Tan�ms�z olarak kullan�lan sabit
#define ZIYARETEDILMEMIS 0 //Ziyaret edilmemi� noktay� belirten sabit
#define ZIYARETEDILMIS 1//Ziyaret edilmi� olan noktay� belirten sabit.

typedef struct {
    double x;
    double y;
} Point;

double uzaklikHesabi(Point p1, Point p2) {// �ki nokta aras�ndaki mesafeyi hesaplamak i�in olu�turulan fonksiyon
    double dx = p2.x - p1.x; 
    double dy = p2.y - p1.y;// Double tipi de�ikenler i�in de�er atamalar�
    return sqrt(dx * dx + dy * dy);// parantez i�indeki i�lemin sonucunun karek�k� d�ner.
}

void optics(Point* nokta, int veri_boyutu, double epsilon, int minPts, int* kume) {//Opt�cs fonksiyonudur. Algoritmay� uygulamak i�in olu�turuldu.
//Parametre olarak veri noktalar�n� (nokta), veri boyutunu (veri_boyutu), epsilon de�erini (epsilon), minPts de�erini (minPts) ve k�meleme bilgisini (kume) al�r.
    int* visited = (int*)malloc(veri_boyutu * sizeof(int));
    double* mesafe = (double*)malloc(veri_boyutu * sizeof(double));

    for (int i = 0; i < veri_boyutu; i++) {//Her bir veri noktas� i�in bir d�ng� olu�turulur. E�er nokta ziyaret edildiyse, bir sonraki noktaya ge�ilir.
        visited[i] = ZIYARETEDILMEMIS;// Nokta ziyaret edilmemi�se , komsu say�s�n� s�f�rlar ve t�m noktalar� kontrol ederiz.
        mesafe[i] = TANIMSIZ;
        kume[i] = TANIMSIZ;
    }

    for (int i = 0; i < veri_boyutu; i++) {
        if (visited[i] == ZIYARETEDILMIS) {
            continue;//devam ederiz.
        }

        visited[i] = ZIYARETEDILMIS;
        int komsu = 0;

        for (int j = 0; j < veri_boyutu; j++) {
            double distance = uzaklikHesabi(nokta[i],nokta[j]);

            if (distance <= epsilon) {//ki nokta aras�ndaki mesafeyi hesaplar ve epsilon de�erinden k���k veya e�itse,
			// bir kom�u bulunmu� demektir. Kom�u say�s�n� art�r�r ve kom�u nokta ziyaret edilmemi�se, ziyaret edilmi� olarak i�aretleriz.
                komsu++;

                if (visited[j] == ZIYARETEDILMEMIS) {
                    visited[j] = ZIYARETEDILMIS;
                }
            }

            if (mesafe[j] == TANIMSIZ || distance < mesafe[j]) {//E�er reachability mesafesi (mesafe) tan�ms�z (TANIMSIZ) veya yeni hesaplanan mesafeden daha b�y�kse, 
			//reachability mesafesini g�ncelleriz.
                mesafe[j] = distance;
            }
        }

        if (komsu >= minPts) {//E�er noktan�n kom�u say�s� (neighbors) minPts'ten b�y�k veya e�itse, nokta bir �ekirdek noktas�d�r.
        //Bu durumda, kume de�erini 1 olarak ayarlar�z ve t�m kom�u noktalar� ziyaret edilmi� olarak i�aretleriz.
            kume[i] = 1;

            for (int j = 0; j < veri_boyutu; j++) {
                if (visited[j] == ZIYARETEDILMEMIS && mesafe[j] <= epsilon) {
                    visited[j] = ZIYARETEDILMIS;
                    kume[j] = 1;
                }
            }
        }
    }

    free(visited);
    free(mesafe);
}

int main() {
    Point nokta[]= {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
    int veri_boyutu = sizeof(nokta) / sizeof(Point);
    int* kume = (int*)malloc(veri_boyutu * sizeof(int));

    double epsilon = 3.0;// epsilon de�erini belirleriz
    int minPts = 2; // minPts de�erini belirleriz.

    optics(nokta, veri_boyutu, epsilon, minPts, kume);//Optics fonksiyonunu �a��r�r�z ve k�meleme i�lemini ger�ekle�tiririz.

    for (int i =0; i < veri_boyutu; i++) {// S�rayla yaz�lacak sonu�lar i�in d�ng� olu�tururuz.
        printf("Nokta %d: Kume %d\n", i+1, kume[i]);//Sonu�lar� ekrana yazd�r�r�z.
    }

    free(kume);//Bellek i�indeki s�z�nt�y� �nlemek i�in kume dizisini serbest b�rak�r�z.

    return 0;
}

