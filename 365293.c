//Firat Kahreman 365293  365293@ogr.ktu.edu.tr   1
//Aysenur Dagdelen 383223  383223@ogr.ktu.edu.tr   2

#include <stdio.h>
#include <stdlib.h>
int takimsayisi;            //Toplam takim sayimiz
int sayac = 0;              //Kacinci maci ekledigimizi saymak icin(Hatasiz maclar)
int atlananmaclar = 0;      //Hatali maclari saymak icin olusturuldu

int ayarlar();
void takimlar();
void macekle();
void d_macekle();
void k_macekle();
void galibiyet();
void beraberlik();
void maglubiyet();
void puandurumu();
void siralama_kisaltma();
void siralama_puan();
void siralama_alfabetik();
void buyukharf();
void kucukharf();
void dosyayaz();
int menu();

struct takimlar        //Takimlar ve bilgilerini tutar
{
    char *kisaltma;
    char takimismi[12];
    int oynanan;
    int galibiyet;
    int beraberlik;
    int maglubiyet;
    int at_gol;
    int yen_gol;
    int av;
    int puan;
} takim[100];

struct ayarlar         //Takim sayisi ve puan ayarlarini tutar
{
    unsigned int t_sayi;
    int gp;
    int bp;
    int mp;
} ayar;

struct macekle         //Maclardaki takimlar ve skorlari tutar
{
    char takimbir;
    unsigned int skorbir;
    char takimiki;
    int skoriki;
} mac[100];

int ayarlar()         //Dosyadaki ayarlari ayarlar structi icine atar
{
    ayar.t_sayi = 10;    //Dokumanda istenen baslangic degerleri
    ayar.gp = 2;
    ayar.bp = 1;
    ayar.mp = -1;

    printf("ayarlar.txt dosyasi araniyor...\n");


    FILE*fp;
    if(fp=fopen("ayarlar.txt","r"))
    {
        fscanf(fp,"%d %d %d %d",&ayar.t_sayi,&ayar.gp,&ayar.bp,&ayar.mp);
        printf("Ayarlar yapildi. %d takim icin galibiyet %d puan, beraberlik %d puan, maglubiyet %d puan olarak guncellendi.\n",ayar.t_sayi,ayar.gp,ayar.bp,ayar.mp);

        takimsayisi = ayar.t_sayi;          //bazi donguler icinde ayar.t_sayi okunmadigi icin bir degiskene atadik
    }
    else
    {
        printf("ayarlar.txt dosyasi bulunamadi\n");
        printf("Baslangic ayarlari atandi. %d takim icin galibiyet %d puan, beraberlik %d puan, maglubiyet %d puan olarak guncellendi.\n",ayar.t_sayi,ayar.gp,ayar.bp,ayar.mp);
    }
    fclose(fp);
    takimlar();
}

void takimlar()        //Takim isimlerini takimlar structu icine atar ve kisaltmalarini tanimlar
{
    int i,x=0;
    printf("takimlar.txt dosyasi araniyor...\n");

    FILE *ft;
    if(ft=fopen("takimlar.txt","r"))
    {
        while(!feof(ft))
        {
            fscanf(ft,"%s",&takim[x].takimismi);
            takim[x].kisaltma = (char) 65 + x;        //A harfinin ASCII kodu 65 oldugundan takimlara A'dan baslayarak harf atadik
            takim[x].oynanan = 0;
            takim[x].galibiyet = 0;
            takim[x].maglubiyet = 0;
            takim[x].beraberlik = 0;
            takim[x].at_gol = 0;                      //Takimlarin ilk degerlerini sifirladik
            takim[x].yen_gol = 0;
            takim[x].av = 0;
            takim[x].puan = 0;

            x++;
        }

        printf("\n%d takim tanimlandi ve kisaltmalari atandi.\nTakimlar:",x);

        if(x!=takimsayisi)               //Ayarlardaki takim sayisinin toplam takim sayisina esitligini kontrol ettik
        {
            printf("\n(!) ayarlar.txt dosyasindan okunan takim sayisi ile takimlar.txt dosyasindaki toplam takim sayisi esit degil. Fazla takimlar varsa atanmamistir.\n");
        }


    }
    else
    {
        printf("takimlar.txt dosyasi bulunamadi.");
    }
    fclose(ft);

    for(i=0; i<takimsayisi; i++)                          //Atanan takimlari ekrana yazdirdik
    {
        printf("\n(%s) %s \n",&takim[i].kisaltma,takim[i].takimismi);
    }

    menu();

}

void macekle()         //Mac ekleme menusu
{
    int mactercihi;

    printf("Hangi yontemle mac eklemek istiyorsunuz?\n");
    printf("[1] - Dosyadan\n");
    printf("[2] - Klavyeden\n");
    printf("[3] - Menuye don\n");

    scanf("%d",&mactercihi);

    switch(mactercihi)
    {
    case 1:
        d_macekle();
        break;
    case 2:
        k_macekle();
        break;
    case 3:
        menu();
        break;
    default:
        printf("Gecerli bir islem numarasi girmediniz.\n");
        macekle();
        break;
    }
}

void d_macekle()       //Dosyadan mac ekleme fonksiyonu
{
    printf("\nmaclar1.txt dosyasi araniyor... \n");
    int i,j,k,z=0;

    FILE *fmaclar;
    if(fmaclar=fopen("maclar1.txt","r"))
    {
        printf("maclar1.txt dosyasindan maclar alindi.\n\n");
        while(!feof(fmaclar))
        {
            int kontrolbir=0,kontroliki=0,takimkontrol;            //Takimlarin var olup olmadigini kontrol icin olusturuldu

            fscanf(fmaclar,"%s %d %s %d",&mac[sayac].takimbir,&mac[sayac].skorbir,&mac[sayac].takimiki,&mac[sayac].skoriki);

            for(i=0 ; i<takimsayisi ; i++)
            {
                if(mac[sayac].takimbir == takim[i].kisaltma)             //Eger var olmayan takim birincisi ise
                {
                    kontrolbir = 1;
                }
                else if(mac[sayac].takimiki == takim[i].kisaltma)
                {
                    kontroliki = 2;                                      //Eger var olmayan takim ikincisi ise
                }
            }

            takimkontrol = kontrolbir + kontroliki;              //Iki kontrol degiskenine farkli sayilar verildiginden olmayan takimin birinci mi ikinci mi oldugu ayirt edilebiliyor

            if(mac[sayac].takimbir!=mac[sayac].takimiki && takimkontrol == 3)      //Eger takim kendi ile mac yapmiyorsa ve takimlar varsa if icine girer
            {
                for(i=0 ; i<=sayac ; i++)
                {
                    for(j=0 ; j<=sayac ; j++)
                    {
                        if(i!=j)
                        {
                            if (mac[i].takimbir == mac[j].takimbir)
                            {
                                if(mac[i].takimiki == mac[j].takimiki)              //Bu mac daha once oynanmis mi diye kontrol ediyor
                                {
                                    z = 1;                                          //Eger oynanmissa z'yi 1 yapiyor
                                }

                            }
                        }
                    }
                }

                if(z==0)                //z=0 ise mac daha once oynanmamistir ve if kosulu icine girebilir
                {
                    if(mac[sayac].skorbir>mac[sayac].skoriki)       //Ev sahibi takim deplasmani yenmisse
                    {
                        galibiyet(sayac);
                    }

                    else if(mac[sayac].skorbir==mac[sayac].skoriki)    //Berabere kalinmissa
                    {
                        beraberlik(sayac);
                    }

                    else                                 //Deplasman ev sahibi takimi yenmisse
                    {
                        maglubiyet(sayac);
                    }
                    sayac++;            //Mac oynandigindan oynanan maclari bir arttirdik
                }
                else
                {
                    printf("hata: %d. mac daha once oynandigi icin tanimlanmamistir.\n",sayac+atlananmaclar+1);
                    z = 0;                 //Sonraki mac tekrar hata vermesin diye z sifirlandi
                    atlananmaclar++;       //Mac oynanmadigindan atlanan maclari bir arttirdik
                }
            }
            else
            {
                if(mac[sayac].takimbir==mac[sayac].takimiki)
                {
                    printf("hata: %d. mac ayni takimlar arasinda oynandigindan tanimlanmamistir.(%c %c)\n\n",sayac+atlananmaclar+1,mac[sayac].takimbir,mac[sayac].takimiki);
                }
                if(takimkontrol == 2)
                {
                    printf("hata: %d. mactaki takimlardan birincisi (%c) bulunamadi\n\n",sayac+atlananmaclar+1,mac[sayac].takimbir);
                }
                if(takimkontrol == 1)
                {
                    printf("hata: %d. mactaki takimlardan ikincisi (%c) bulunamadi\n\n",sayac+atlananmaclar+1,mac[sayac].takimiki);
                }
                atlananmaclar++;     //Mac oynanmadigindan atlanan maclari bir arttirdik
            }
        }
    }
    else
    {
        printf("hata: maclar1.txt dosyasi bulunamadi\n");
    }
    fclose(fmaclar);

    macekle();    //Mac ekleme menusune donduk
}

void k_macekle()      //Klavyeden mac ekleme fonksiyonu
{
    int i,j,y=0;
    int kontrolbir=0,kontroliki=0,takimkontrol;            //Takimlarin var olup olmadigini kontrol icin olusturuldu

    printf("Eklemek istediginiz maci A 1 B 2 formatinda giriniz: ");
    scanf("%s %d %s %d",&mac[sayac].takimbir,&mac[sayac].skorbir,&mac[sayac].takimiki,&mac[sayac].skoriki);

    for(i=0 ; i<takimsayisi ; i++)
    {
        if(mac[sayac].takimbir == takim[i].kisaltma)             //Eger var olmayan takim birincisi ise
        {
            kontrolbir = 1;
        }
        else if(mac[sayac].takimiki == takim[i].kisaltma)
        {
            kontroliki = 2;                                      //Eger var olmayan takim ikincisi ise
        }
    }

    takimkontrol = kontrolbir + kontroliki;              //Iki kontrol degiskenine farkli sayilar verildiginden olmayan takimin birinci mi ikinci mi oldugu ayirt edilebiliyor

    if(mac[sayac].takimbir!=mac[sayac].takimiki && takimkontrol == 3)        //Eger takim kendi ile mac yapmiyorsa ve takimlar varsa if icine girer
    {
        for(i=0 ; i<=sayac ; i++)
        {
            for(j=0 ; j<=sayac ; j++)
            {
                if(i!=j)
                {
                    if (mac[i].takimbir == mac[j].takimbir)
                    {
                        if(mac[i].takimiki == mac[j].takimiki)          //Bu mac daha once oynanmis mi diye kontrol ediyor
                        {
                            y = 1;                                      //Eger oynanmissa y'yi 1 yapiyor
                        }
                    }
                }
            }
        }

        if (y==0)          //y = 0 ise if kosulu icine girebilir
        {
            if(mac[sayac].skorbir>mac[sayac].skoriki)
            {
                galibiyet(sayac);
            }
            else if(mac[sayac].skorbir==mac[sayac].skoriki)
            {
                beraberlik(sayac);
            }
            else
            {
                maglubiyet(sayac);
            }
            sayac++;
        }
        else
        {
            printf("%d. mac daha once oynandigi icin tanimlanmamistir. \n",sayac);
            y--;
            atlananmaclar++;
        }
    }
    else
    {
        if(mac[sayac].takimbir==mac[sayac].takimiki)
        {
            printf("hata: %d. mac ayni takimlar arasinda oynandigindan tanimlanmamistir.(%c %c)\n\n",sayac+atlananmaclar+1,mac[sayac].takimbir,mac[sayac].takimiki);
        }
        if(takimkontrol == 2)
        {
            printf("hata: %d. mactaki takimlardan birincisi (%c) bulunamadi\n\n",sayac+atlananmaclar+1,mac[sayac].takimbir);
        }
        if(takimkontrol == 1)
        {
            printf("hata: %d. mactaki takimlardan ikincisi (%c) bulunamadi\n\n",sayac+atlananmaclar+1,mac[sayac].takimiki);
        }
        atlananmaclar++;
    }

    macekle();    //Mac ekleme menusune doner
}

void galibiyet(sonmac)        //Galibiyet halinde yapilacaklar(sonmac eklenen son macin kacinci oldugunu ifade eder)
{
    int a;
    for(a=0; a<takimsayisi; a++)
    {

        if (mac[sonmac].takimbir == takim[a].kisaltma)
        {
            takim[a].galibiyet++;
            takim[a].oynanan++;
            takim[a].at_gol = takim[a].at_gol + mac[sonmac].skorbir;
            takim[a].yen_gol = takim[a].yen_gol + mac[sonmac].skoriki;
        }
        else if (mac[sonmac].takimiki == takim[a].kisaltma)
        {
            takim[a].maglubiyet++;
            takim[a].oynanan++;
            takim[a].at_gol = takim[a].at_gol + mac[sonmac].skoriki;
            takim[a].yen_gol = takim[a].yen_gol + mac[sonmac].skorbir;
        }
    }
}

void beraberlik(sonmac)      //Beraberlik halinde yapilacaklar
{
    int a;
    for(a=0; a<takimsayisi; a++)
    {
        if (mac[sonmac].takimbir == takim[a].kisaltma)
        {
            takim[a].beraberlik++;
            takim[a].oynanan++;
            takim[a].at_gol = takim[a].at_gol + mac[sonmac].skorbir;
            takim[a].yen_gol = takim[a].yen_gol + mac[sonmac].skoriki;
        }
        else if (mac[sonmac].takimiki == takim[a].kisaltma)
        {
            takim[a].beraberlik++;
            takim[a].oynanan++;
            takim[a].at_gol = takim[a].at_gol + mac[sonmac].skoriki;
            takim[a].yen_gol = takim[a].yen_gol + mac[sonmac].skorbir;
        }
    }
}

void maglubiyet(sonmac)      //Maglubiyet halinde yapilacaklar
{
    int a;
    for(a=0; a<takimsayisi; a++)
    {
        if (mac[sonmac].takimiki == takim[a].kisaltma)
        {
            takim[a].galibiyet++;
            takim[a].oynanan++;
            takim[a].at_gol = takim[a].at_gol + mac[sonmac].skoriki;
            takim[a].yen_gol = takim[a].yen_gol + mac[sonmac].skorbir;
        }
        else if (mac[sonmac].takimbir == takim[a].kisaltma)
        {
            takim[a].maglubiyet++;
            takim[a].oynanan++;
            takim[a].at_gol = takim[a].at_gol + mac[sonmac].skorbir;
            takim[a].yen_gol = takim[a].yen_gol + mac[sonmac].skoriki;
        }
    }
}

void puandurumu()       //Puan durumu menusu
{
    int h;
    int tablotercih;

    for(h=0; h<takimsayisi; h++)      //Takim puanlari ve averajlarini burada hesapladik
    {
        takim[h].av = takim[h].at_gol - takim[h].yen_gol;
        takim[h].puan = takim[h].galibiyet*ayar.gp + takim[h].beraberlik*ayar.bp + takim[h].maglubiyet*ayar.mp;
    }

    printf("Puan durumunu hangi siralama ile gormek istiyorsunuz?\n");
    printf("[1]-Kisaltmaya Gore (A-Z)\n[2]-Puana Gore (Azalan)\n[3]-Takim ismine gore (A-Z)\n[4]-Menuye don\n");
    scanf("%d",&tablotercih);

    switch(tablotercih)
    {
    case 1:
        siralama_kisaltma();
        break;
    case 2:
        siralama_puan();
        break;

    case 3:
        siralama_alfabetik();
        break;
    case 4:
        menu();
        break;
    default:
        printf("\n\nGecersiz islem numarasi!\n\n");
        puandurumu();
        break;
    }
}

void siralama_kisaltma()     //Kisaltmaya gore alfabetik siralama
{
    int i,k;
    int tablotercih4;

    for(k=1; k<takimsayisi ; k++)
    {
        for(i=0; i<takimsayisi-1; i++)
        {
            if(takim[i].kisaltma > takim[i+1].kisaltma)       //Siralama algoritmasi
            {
                takim[32] = takim[i];
                takim[i] = takim[i+1];
                takim[i+1] = takim[32];
            }
        }
    }

    printf("\nKisaltmaya gore alfabetik puan durumu:\n");
    printf("  Takim ismi  |  Kisaltma  | O | G | B | M | AG | YG |  AV  | PUAN \n");


    for(i=0; i<takimsayisi; i++)
    {
        printf("%12s        %s        %d   %d   %d   %d    %d    %d    %2d     %2d\n",takim[i].takimismi,&takim[i].kisaltma,takim[i].oynanan,takim[i].galibiyet,takim[i].beraberlik,takim[i].maglubiyet,takim[i].at_gol,takim[i].yen_gol,takim[i].av,takim[i].puan);
    }

    printf("\n[1]-Sirala(Puana Gore Azalan)  [2]-Dosyaya yazdir  [3]-Buyuk Harf  [4]-Kucuk Harf  [5]-Menu\n");
    scanf("%d",&tablotercih4);

    switch(tablotercih4)
    {
    case 1:
        siralama_puan();
        break;

    case 2:
        dosyayaz();
        siralama_kisaltma();
        break;

    case 3:
        buyukharf();
        siralama_kisaltma();
        break;

    case 4:
        kucukharf();
        siralama_kisaltma();
        break;
    case 5:
        menu();
        break;
    default:
        printf("\n\nGecersiz islem numarasi!\n\n");
        siralama_kisaltma();
        break;
    }
}

void siralama_puan()         //Puana gore azalan siralama
{
    int i,j;
    int tablotercih2;

    for(i=1; i<takimsayisi; i++)
    {
        for (j=0; j<takimsayisi-1; j++)
        {
            if (takim[j].puan<takim[j+1].puan)
            {
                takim[30] = takim[j];               //Siralama algoritmasi
                takim[j] = takim[j+1];
                takim[j+1] = takim[30];
            }
        }
    }


    for(i=1; i<takimsayisi; i++)
    {
        for (j=0; j<takimsayisi-1; j++)
        {
            if (takim[j].puan==takim[j+1].puan)
            {
                if(takim[j].av<takim[j+1].av)         //Takim puanlari esitse averaja gore siralar
                {
                    takim[31] = takim[j];
                    takim[j] = takim[j+1];
                    takim[j+1] = takim[31];
                }

            }
        }
    }

    printf("\nPuana gore (Azalan) puan durumu:\n");
    printf("  Takim ismi  |  Kisaltma  | O | G | B | M | AG | YG |  AV  | PUAN \n");

    for(i=0; i<takimsayisi; i++)
    {

        printf("%12s        %s        %d   %d   %d   %d    %d    %d    %2d     %2d\n",takim[i].takimismi,&takim[i].kisaltma,takim[i].oynanan,takim[i].galibiyet,takim[i].beraberlik,takim[i].maglubiyet,takim[i].at_gol,takim[i].yen_gol,takim[i].av,takim[i].puan);

    }


    printf("\n[1]-Sirala(Takim ismine gore A-Z)  [2]-Dosyaya yazdir  [3]-Buyuk Harf  [4]-Kucuk Harf  [5]-Menu\n");
    scanf("%d",&tablotercih2);

    switch(tablotercih2)
    {
    case 1:
        siralama_alfabetik();
        break;
    case 2:
        dosyayaz();
        siralama_puan();
        break;
    case 3:
        buyukharf();
        siralama_puan();
        break;
    case 4:
        kucukharf();
        siralama_puan();
        break;
    case 5:
        menu();
        break;
    default:
        printf("\n\nGecersiz islem numarasi!\n\n");
        siralama_puan();
        break;
    }
}

void siralama_alfabetik()    //Takim isimlerini alfabetik siralama
{
    int i,j,k;
    int harf=0;
    int tablotercih3;


    for(k=1; k<takimsayisi ; k++)
    {

        for(i=0; i<takimsayisi-1; i++)
        {

            if(*takim[i].takimismi > *takim[i+1].takimismi)                           //Siralama algoritmasi
            {
                takim[32] = takim[i];
                takim[i] = takim[i+1];
                takim[i+1] = takim[32];
            }
            else if(*takim[i].takimismi == *takim[i+1].takimismi)                     //Birden fazla harfi esit olan isimler icin bir sonraki harfe bakan algoritma
            {


                while(takim[i].takimismi[harf] == takim[i+1].takimismi[harf])
                {
                    harf++;                   //Bir sonraki harfe bakmak icin harfi bir arttirdik
                }
                if(takim[i].takimismi[harf] > takim[i+1].takimismi[harf])
                {
                    takim[33] = takim[i];
                    takim[i] = takim[i+1];
                    takim[i+1] = takim[33];
                    harf = 0;
                }


            }
        }
    }

    printf("\nAlfabetik puan durumu:\n");
    printf("  Takim ismi  |  Kisaltma  | O | G | B | M | AG | YG |  AV  | PUAN \n");


    for(i=0; i<takimsayisi; i++)
    {

        printf("%12s        %s        %d   %d   %d   %d    %d    %d    %2d     %2d\n",takim[i].takimismi,&takim[i].kisaltma,takim[i].oynanan,takim[i].galibiyet,takim[i].beraberlik,takim[i].maglubiyet,takim[i].at_gol,takim[i].yen_gol,takim[i].av,takim[i].puan);

    }

    printf("\n[1]-Sirala(Kisaltmaya gore A-Z)  [2]-Dosyaya yazdir  [3]-Buyuk Harf  [4]-Kucuk Harf  [5]-Menu\n");
    scanf("%d",&tablotercih3);

    switch(tablotercih3)
    {
    case 1:
        siralama_kisaltma();
        break;
    case 2:
        dosyayaz();
        siralama_alfabetik();
        break;
    case 3:
        buyukharf();
        siralama_alfabetik();
        break;
    case 4:
        kucukharf();
        siralama_alfabetik();
        break;
    case 5:
        menu();
        break;
    default:
        printf("\n\nGecersiz islem numarasi!\n\n");
        siralama_alfabetik();
        break;
    }


}

void buyukharf()             //Takim isimlerini buyuk harfle yazdirir
{
    int i,j;
    for(i=0; i<takimsayisi; i++)
    {
        for(j=0; j<=12; j++)
        {
            if (takim[i].takimismi[j] >= 'a' && takim[i].takimismi[j] <= 'z')   //ASCII tablosuna gore kucuk a ve kucuk z arasinda ise kucuk harftir
            {
                takim[i].takimismi[j] -= 32;                 //ASCII tablosuna gore ayni harfin kucuk karakterinin kodu buyuk karakterinin kodundan 32 fazladir
            }
        }
    }
}

void kucukharf()             //Takim isimlerini kucuk harfle yazdirir
{
    int i,j;
    for(i=0; i<takimsayisi; i++)
    {
        for(j=0; j<=12; j++)
        {
            if (takim[i].takimismi[j] >= 'A' && takim[i].takimismi[j] <= 'Z')   //ASCII tablosuna gore buyuk A ve buyuk Z arasinda ise buyuk harftir
            {
                takim[i].takimismi[j] += 32;               //32 arttirarak kucuk harfin kodunu elde ettik
            }
        }
    }
}

void dosyayaz()              //Puan durumunu puandurumu.txt dosyasina yazdirir
{
    FILE *fa;
    fa = fopen("puandurumu.txt","w");
    int x;
    fprintf(fa,"  Takim ismi  |  Kisaltma  | O | G | B | M | AG | YG |  AV  | PUAN \n");
    for(x=0; x<takimsayisi; x++)
    {
        fprintf(fa,"%12s        %s        %d   %d   %d   %d    %d    %d    %2d     %2d\n",&takim[x].takimismi,&takim[x].kisaltma,takim[x].oynanan,takim[x].galibiyet,takim[x].beraberlik,takim[x].maglubiyet,takim[x].at_gol,takim[x].yen_gol,takim[x].av,takim[x].puan);
    }

    fclose(fa);
    printf("\nTablo puandurumu.txt dosyasina yazilmistir.\n");
}

int menu()           //Yapilacak islemleri secmek icin
{
    int tercihmenu;
    printf("\n-----------------------------------------------------------\n");
    printf("\nYapmak istediginiz islemi tuslayin.\n");
    printf("[1] - Mac Ekle\n");
    printf("[2] - Ayarlari ve Takimlari Guncelle\n");     //Ayarlar ve takimlari baslangicta otomatik atadigimiz icin guncelleme ekledik
    printf("[3] - Puan Durumunu Gor\n");

    scanf("%d",&tercihmenu);

    switch(tercihmenu)
    {
    case 1:
        macekle();
        break;
    case 2:
        ayarlar();
        break;
    case 3:
        puandurumu();
        break;
    default:
        printf("Gecerli bir islem numarasi girmediniz.");
        menu();
        break;
    }
}

int main()
{
    ayarlar();      //Sadece ayarlari cagirdik. Cunku program baslar baslamaz otomatik olarak ayarlarin ve takimlarin atanmasini istedik...
                    //...Takimlari atayan fonksiyondan sonra menuyu cagirdik
    return 0;
}
