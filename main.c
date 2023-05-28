#include <stdio.h>
#include <stdlib.h>
#include <math.h>// gerekli kütüphaneler tanýmlanýr.

#define TANIMSIZ -1// Tanýmsýz olarak kullanýlan sabit
#define ZIYARETEDILMEMIS 0 //Ziyaret edilmemiþ noktayý belirten sabit
#define ZIYARETEDILMIS 1//Ziyaret edilmiþ olan noktayý belirten sabit.

typedef struct {
    double x;
    double y;
} Point;

double uzaklikHesabi(Point p1, Point p2) {// Ýki nokta arasýndaki mesafeyi hesaplamak için oluþturulan fonksiyon
    double dx = p2.x - p1.x; 
    double dy = p2.y - p1.y;// Double tipi deðikenler için deðer atamalarý
    return sqrt(dx * dx + dy * dy);// parantez içindeki iþlemin sonucunun karekökü döner.
}

void optics(Point* nokta, int veri_boyutu, double epsilon, int minPts, int* kume) {//Optýcs fonksiyonudur. Algoritmayý uygulamak için oluþturuldu.
//Parametre olarak veri noktalarýný (nokta), veri boyutunu (veri_boyutu), epsilon deðerini (epsilon), minPts deðerini (minPts) ve kümeleme bilgisini (kume) alýr.
    int* visited = (int*)malloc(veri_boyutu * sizeof(int));
    double* mesafe = (double*)malloc(veri_boyutu * sizeof(double));

    for (int i = 0; i < veri_boyutu; i++) {//Her bir veri noktasý için bir döngü oluþturulur. Eðer nokta ziyaret edildiyse, bir sonraki noktaya geçilir.
        visited[i] = ZIYARETEDILMEMIS;// Nokta ziyaret edilmemiþse , komsu sayýsýný sýfýrlar ve tüm noktalarý kontrol ederiz.
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

            if (distance <= epsilon) {//ki nokta arasýndaki mesafeyi hesaplar ve epsilon deðerinden küçük veya eþitse,
			// bir komþu bulunmuþ demektir. Komþu sayýsýný artýrýr ve komþu nokta ziyaret edilmemiþse, ziyaret edilmiþ olarak iþaretleriz.
                komsu++;

                if (visited[j] == ZIYARETEDILMEMIS) {
                    visited[j] = ZIYARETEDILMIS;
                }
            }

            if (mesafe[j] == TANIMSIZ || distance < mesafe[j]) {//Eðer reachability mesafesi (mesafe) tanýmsýz (TANIMSIZ) veya yeni hesaplanan mesafeden daha büyükse, 
			//reachability mesafesini güncelleriz.
                mesafe[j] = distance;
            }
        }

        if (komsu >= minPts) {//Eðer noktanýn komþu sayýsý (neighbors) minPts'ten büyük veya eþitse, nokta bir çekirdek noktasýdýr.
        //Bu durumda, kume deðerini 1 olarak ayarlarýz ve tüm komþu noktalarý ziyaret edilmiþ olarak iþaretleriz.
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

    double epsilon = 3.0;// epsilon deðerini belirleriz
    int minPts = 2; // minPts deðerini belirleriz.

    optics(nokta, veri_boyutu, epsilon, minPts, kume);//Optics fonksiyonunu çaðýrýrýz ve kümeleme iþlemini gerçekleþtiririz.

    for (int i =0; i < veri_boyutu; i++) {// Sýrayla yazýlacak sonuçlar için döngü oluþtururuz.
        printf("Nokta %d: Kume %d\n", i+1, kume[i]);//Sonuçlarý ekrana yazdýrýrýz.
    }

    free(kume);//Bellek içindeki sýzýntýyý önlemek için kume dizisini serbest býrakýrýz.

    return 0;
}

