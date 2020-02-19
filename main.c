#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
///Ön Verilerin Kontrol Edilmesi.
void veri_kontrol(char a[][40],int *versiyon,int *_alanformat,int *_nokta_adet,int *_data_format,char _hatalar[][100],int *hata,char dosya_ad[20],int *hata_bool)
{   *hata_bool=0;
    const char*bosluk=" ";
    char *birkelime=NULL;
    char dosya_ad_gecici[50];
    int i;
    birkelime=strtok(a[1],bosluk);
    if(strcmp(birkelime,"VERSION")==0)
    {
        birkelime=strtok(NULL,bosluk);
        *versiyon=0;
        for(i=0; birkelime[i]!='\n'; i++)
        {
            if(isdigit(birkelime[i])==1)
            {
                *versiyon=10*(*versiyon)+(birkelime[i]-48);
            }
            else
            {
            strcpy(dosya_ad_gecici,dosya_ad);
            sprintf(_hatalar[*hata],"%s Dosyasinda Versiyon Sayisi Gecersiz.(NOKTA VERILERI OKUNAMAZ)",dosya_ad_gecici);

            *hata=*hata+1;
            *hata_bool=1;// versiyon numarası girilmemiş
            }
        }

    }
    else
    {   strcpy(dosya_ad_gecici,dosya_ad);
    sprintf(_hatalar[*hata],"%s Dosyasinda Versiyon Gosterimi Yanlis.(NOKTA VERILERI OKUNAMAZ)",dosya_ad_gecici);
        *hata=*hata+1;
        *hata_bool=1;
        //versiyon girilmemiş
    }
    if(strcmp(a[2],"ALANLAR x y z r g b\n")==0)
    {

        *_alanformat=0;
    }
    else if(strcmp(a[2],"ALANLAR x y z\n")==0)
    {
        *_alanformat=1;

    }
    else
    {   strcpy(dosya_ad_gecici,dosya_ad);
    sprintf(_hatalar[*hata],"%s Dosyasinda alan Formati Gosterimi Yanlis.(NOKTA VERILERI OKUNAMAZ)",dosya_ad_gecici);
        *hata=*hata+1;
        *hata_bool=1;
        //alan format düzgün girilmemiş
    }
    birkelime=NULL;
    birkelime=strtok(a[3],bosluk);
    if(strcmp(birkelime,"NOKTALAR")==0)
    {
        *_nokta_adet=0;
        birkelime=strtok(NULL,bosluk);
        for(i=0; birkelime[i]!='\n'; i++)
        {
            if(isdigit(birkelime[i])==1)
            {
                *_nokta_adet=10*(*_nokta_adet)+(birkelime[i]-48);
            }
            else
            {
        strcpy(dosya_ad_gecici,dosya_ad);
        sprintf(_hatalar[*hata],"%s Dosyasinda Nokta Adeti Sayi Degil.(NOKTA VERILERI OKUNAMAZ)",dosya_ad_gecici);
        *hata=*hata+1;
        *hata_bool=1;//nokta adeti girilmemiş
            }
        }

    }
    else
    {   strcpy(dosya_ad_gecici,dosya_ad);
        sprintf(_hatalar[*hata],"%s Dosyasinda Nokta Adet Yzimi  Yanlis.(NOKTA VERILERI OKUNAMAZ)",dosya_ad_gecici);
        *hata=*hata+1;
        *hata_bool=1;// nokda adet yazımı hatalı
    }

    if(strcmp(a[4],"DATA ascii\n")==0)
    {
        *_data_format=0;
    }
    else if (strcmp(a[4],"DATA binary\n")==0)
    {
        *_data_format=1;
    }
    else
    {   strcpy(dosya_ad_gecici,dosya_ad);
        sprintf(_hatalar[*hata],"%s Dosyasinda Dosya Formati Gosterimi Yanlis.(NOKTA VERILERI OKUNAMAZ)",dosya_ad_gecici);
        *hata=*hata+1;
        *hata_bool=1;
       //alan formatı verilmemiş
    }
}
///Ön verilerin alınması için oluşturulmuş bir fonksiyon.
///--------------------------------------------------------------------
void veri_al(char _ctrl_info[][40],FILE *_fptr1){
    int _counterline=0;
while(fgets(_ctrl_info[(_counterline)],40,_fptr1))
    {
        (_counterline)=(_counterline)+1;

        if(_counterline==5)
        {
            break;
        }
    }
}
struct Nokta_rgb{
float x,y,z;
int r,g,b;
};
struct Nokta{
float x,y,z;
};
void nokta_kontrol(FILE *_fptr1,int *_gercek_nokta_adet,int _alan_format,int _nokta_adet,int *hata,char _hatalar[][100],char dosya_ad[20],int *hata_bool){
        char sayac;
        *hata_bool=0;
        int i;
        int satir_sayisi=0;
        int nokta_sayac=0,nokta_sayac_genel=0;
        int bosluk_sayac=0;
        char nokta_satir[100];
        char nokta_satir2[100];
        char dosya_ad_gecici[50];
        strcpy(dosya_ad_gecici,dosya_ad);
        *_gercek_nokta_adet=0;
        if(_alan_format==0){
        while(!feof(_fptr1)){
        strcpy(nokta_satir2,nokta_satir);
       fgets(nokta_satir,100,_fptr1);
       if(strcmp(nokta_satir2,nokta_satir)!=0){
        for(i=0;nokta_satir[i]!='\n';i++){

            if(nokta_satir[i]=='.'){
                if(satir_sayisi>_nokta_adet){
                    sprintf(_hatalar[*hata],"%s dosyada fazladan nokta var",dosya_ad_gecici);
                    *hata_bool=1;
                    *hata=*hata+1;
                    break;
                }
                nokta_sayac++;
                nokta_sayac_genel++;
            }
            if(nokta_satir[i]==' '){
                    if(satir_sayisi>_nokta_adet){
                    sprintf(_hatalar[*hata],"%s dosyada fazladan nokta var",dosya_ad_gecici);
                    *hata_bool=1;
                    *hata=*hata+1;
                }
                bosluk_sayac++;

            }



        }
        if(satir_sayisi<_nokta_adet){
        if(bosluk_sayac!=5){
                strcpy(dosya_ad_gecici,dosya_ad);
                sprintf(_hatalar[*hata],"%s dosyada %d. satirda rgb bilgileri eksik.\n",dosya_ad_gecici,satir_sayisi+1);
               // printf("%d.satirda rgb bilgileri eksik\n",satir_sayisi+1);
                *hata=*hata+1;
                *hata_bool=1;
    }}
    if(satir_sayisi<_nokta_adet){
    if(nokta_sayac!=3){
                strcpy(dosya_ad_gecici,dosya_ad);
                sprintf(_hatalar[*hata],"%s dosyada %d. satirda nokta bilgileri eksik.\n",dosya_ad_gecici,satir_sayisi+1);
               // printf("%d.satirda nokta bilgileri eksik\n",satir_sayisi+1);
                *hata=*hata+1;
                *hata_bool=1;
    }
    }}

        nokta_sayac=0;
        bosluk_sayac=0;
        satir_sayisi++;
        /*if(satir_sayisi>_nokta_adet+5){
            sprintf(_hatalar[*hata],"%s dosyada  fazla nokta bilgisi var.\n",dosya_ad_gecici);
            break;
        }*/




        }
        if((nokta_sayac_genel/3)!=_nokta_adet){
    sprintf(_hatalar[*hata],"%s nokta sayısında hata .\n",dosya_ad_gecici);
                *hata=*hata+1;
                *hata_bool=1;
}

}else if(_alan_format==1){
while(!feof(_fptr1)){
        strcpy(nokta_satir2,nokta_satir);
       fgets(nokta_satir,100,_fptr1);
       if(strcmp(nokta_satir2,nokta_satir)!=0){
        for(i=0;i<strlen(nokta_satir);i++){
            if(nokta_satir[i]=='.'){

                if(satir_sayisi>_nokta_adet&&*hata_bool==0){
                    *hata_bool=1;
                    sprintf(_hatalar[*hata],"%s. dosyada nokta sayisi fazla \n",dosya_ad_gecici);
                    *hata=*hata+1;
                }
                nokta_sayac++;
                nokta_sayac_genel++;
            }
        }
        if(satir_sayisi<_nokta_adet){
        if(nokta_sayac!=3){
                strcpy(dosya_ad_gecici,dosya_ad);
                sprintf(_hatalar[*hata],"%s dosyada %d. satirda nokta bilgileri eksik.\n",dosya_ad_gecici,satir_sayisi+1);
                *hata=*hata+1;
                *hata_bool=1;

}}}
        nokta_sayac=0;
        satir_sayisi++;

}
if((nokta_sayac_genel/3)!=_nokta_adet){
    sprintf(_hatalar[*hata],"%s nokta sayısında hata .\n",dosya_ad_gecici);
                *hata=*hata+1;
                *hata_bool=1;
}

}
}
void nokta_al(int _nokta_adet,FILE *_fptr1,struct Nokta_rgb *na_rgb,int _alanformat,struct Nokta *na){
    int i;
    char bosluk;
    float fx,fy,fz;
    int ir,ig,ib;
    if(_alanformat==0){
    for(i=0;i<_nokta_adet;i++){
    fscanf(_fptr1,"%f %f %f %d %d %d%c",&fx,&fy,&fz,&ir,&ig,&ib,&bosluk);
    na_rgb[i].x=fx;
    na_rgb[i].y=fy;
    na_rgb[i].z=fz;
    na_rgb[i].r=ir;
    na_rgb[i].g=ig;
    na_rgb[i].b=ib;
    //printf("%d. %f %f %f\n",i+1,fx,fy,fz);
    }}else{
for(i=0;i<_nokta_adet;i++){
    fscanf(_fptr1,"%f %f %f%c",&fx,&fy,&fz,&bosluk);
    na[i].x=fx;
    na[i].y=fy;
    na[i].z=fz;
    //printf("%d. %f %f %f\n",i+1,fx,fy,fz);
    }
}
}
void kure_nokta_bul(struct Nokta *na,struct Nokta_rgb *na_rgb,int _alanformat,int _nokta_adet,char dosya_ad_gelen[20],float *x,float *y,float *z,float *r,int *girmekontrol){
    if(*girmekontrol==0){
    printf("bir nokta x giriniz float formatinda:\n");
    scanf("%f",x);
    printf("bir nokta y giriniz float formatinda:\n");
    scanf("%f",y);
    printf("bir nokta z giriniz float formatinda:\n");
    scanf("%f",z);
    printf("bir nokta r giriniz float formatinda:\n");
    scanf("%f",r);
    *girmekontrol=1;
    }
    int i;
    if(_alanformat==0){
            FILE *fptr;
        fptr=fopen("output.nkt","a");
        fprintf(fptr,"Secim 4%s--------------------------------\n",dosya_ad_gelen);
        fprintf(fptr,"cx= %.f\n",*x);
        fprintf(fptr,"cy= %.f\n",*y);
        fprintf(fptr,"cz= %.f\n",*z);
        fprintf(fptr,"cr= %.f\n",*r);
        printf("lutfen bekleyiniz.........\n");
        for(i=0;i<_nokta_adet;i++){
            if(pow(na_rgb[i].x-*x,2)+pow(na_rgb[i].y-*y,2)+pow(na_rgb[i].z-*z,2)<=pow(*r,2)){
            fprintf(fptr,"%d.kürenin icine giren nokta %f %f %f %d %d %d\n",i+1,na_rgb[i].x,na_rgb[i].y,na_rgb[i].z,na_rgb[i].r,na_rgb[i].g,na_rgb[i].b);
            }
        }
fprintf(fptr,"--------------------------------------------\n");
fclose(fptr);
    }else{
         FILE *fptr;
         fptr=fopen("output.nkt","a");
         fprintf(fptr,"Secim 4%s--------------------------------\n",dosya_ad_gelen);
         fprintf(fptr,"cx= %.f\n",*x);
        fprintf(fptr,"cy= %.f\n",*y);
        fprintf(fptr,"cz= %.f\n",*z);
        fprintf(fptr,"cr= %.f\n",*r);
         printf("lutfen bekleyiniz.........\n");
          for(i=0;i<_nokta_adet;i++){
            if(pow(na[i].x-*x,2)+pow(na[i].y-*y,2)+pow(na[i].z-*z,2)<=pow(*r,2)){


fprintf(fptr,"%d.kürenin icine giren nokta %f %f %f\n",i+1,na[i].x,na[i].y,na[i].z);

            }
        }
        fprintf(fptr,"--------------------------------------------\n");
fclose(fptr);
    }
}
void nokta_uzaklik_ortalama(struct Nokta *na,struct Nokta_rgb *na_rgb,int _nokta_adet,int _alan_format,char dosya_ad_gelen[20]){
    printf("Noktalar arasi uzakligin ortalamasi hesaplaniyor...\n");
    int i,j;
    double d=0;
    double burda_nokta=(double)((double)_nokta_adet*(double)((double)_nokta_adet-(double)1)/(double)2);
if(_alan_format==0){
for(i=0;i<_nokta_adet;i++){
if(i==_nokta_adet-1){
    break;
}
for(j=i+1;j<_nokta_adet;j++){
    d=d+sqrt(pow(na_rgb[j].x-na_rgb[i].x,2)+pow(na_rgb[j].y-na_rgb[i].y,2)+pow(na_rgb[j].z-na_rgb[i].z,2));
}
}
        FILE *fptr;
        fptr=fopen("output.nkt","a");
        fprintf(fptr,"Secim 5%s--------------------------------\n",dosya_ad_gelen);
        fprintf(fptr,"ortalama uzaklik: %f\n",d/burda_nokta);
        fprintf(fptr,"--------------------------------------------\n");
        fclose(fptr);

}else if(_alan_format=1){
    for(i=0;i<_nokta_adet;i++){
if(i==_nokta_adet-1){
    break;
}
for(j=i+1;j<_nokta_adet;j++){
    d=d+sqrt(pow(na[j].x-na[i].x,2)+pow(na[j].y-na[i].y,2)+pow(na[j].z-na[i].z,2));
}
}

FILE *fptr;
fptr=fopen("output.nkt","a");
        fprintf(fptr,"Secim 5%s--------------------------------\n",dosya_ad_gelen);
        fprintf(fptr,"ortalama uzaklik: %f\n",d/burda_nokta);
        fprintf(fptr,"--------------------------------------------\n");
        fclose(fptr);
}
}
void kup_noktalari(struct Nokta *na,struct Nokta_rgb *na_rgb,int _nokta_adet,int _alan_format,char dosya_ad_gelen[20]){
    int i;
    float enx=0,eny=0,enz=0,lowx,lowy,lowz;
    float enk_r=0;
    float kenar_uzunluk=0;
    struct Nokta_rgb en_kucuk;
if(_alan_format==0){
        lowx=na_rgb[0].x;
        lowy=na_rgb[0].y;
        lowz=na_rgb[0].z;
        enk_r= sqrt(pow(na_rgb[0].x,2)+pow(na_rgb[0].y,2)+pow(na_rgb[0].z,2));
    for(i=0;i<_nokta_adet;i++){
        if(na_rgb[i].x>=na_rgb[i].y&&na_rgb[i].x>=na_rgb[i].z){
            enx=na_rgb[i].x;
            eny=0;
            enz=0;

        }else if(na_rgb[i].y>=na_rgb[i].x&&na_rgb[i].y>=na_rgb[i].z){
        eny=na_rgb[i].y;
        enx=0;
        enz=0;
        }else if(na_rgb[i].z>=na_rgb[i].x&&na_rgb[i].z>=na_rgb[i].y){
        enz=na_rgb[i].z;
        enx=0;
        eny=0;
        }
        if(lowx>=na_rgb[i].x){
            lowx=na_rgb[i].x;
        }

        if(lowy>=na_rgb[i].y){
            lowx=na_rgb[i].y;
        }

        if(lowz>=na_rgb[i].z){
            lowz=na_rgb[i].z;
        }
    }
    if(enx>0){
            kenar_uzunluk=enx-lowx;

                   FILE *fptr;
fptr=fopen("output.nkt","a");
fprintf(fptr,"Secim 3%s-----------------------------------\n",dosya_ad_gelen);
fprintf(fptr,"1. kose kordinatlari %f %f %f\n2. kose kordinatlari %f %f %f\n3.kose kordinatları %f %f %f\n4.kose kordinatları %f %f %f\n5.kose kordinatları %f %f %f\n6.kose kordinatları %f %f %f\n7.kose kordinatları %f %f %f\n8.kose kordinatları %f %f %f\n"
                   ,lowx,lowy,lowz,
                   lowx,lowy,lowz+kenar_uzunluk,
                   lowx,lowy+kenar_uzunluk,lowz,
                   lowx,lowy+kenar_uzunluk,lowz+kenar_uzunluk,
                   lowx+kenar_uzunluk,lowy,lowz,
                   lowx+kenar_uzunluk,lowy,lowz+kenar_uzunluk,
                   lowx+kenar_uzunluk,lowy+kenar_uzunluk,lowz,
                   lowx+kenar_uzunluk,lowy+kenar_uzunluk,lowz+kenar_uzunluk);
fprintf(fptr,"--------------------------------------------\n");
fclose(fptr);

    }else if(eny>0){
        kenar_uzunluk=eny-lowy;
                        FILE *fptr;
fptr=fopen("output.nkt","a");
fprintf(fptr,"Secim 3%s-----------------------------------\n",dosya_ad_gelen);
fprintf(fptr,"1. kose kordinatlari %f %f %f\n2. kose kordinatlari %f %f %f\n3.kose kordinatları %f %f %f\n4.kose kordinatları %f %f %f\n5.kose kordinatları %f %f %f\n6.kose kordinatları %f %f %f\n7.kose kordinatları %f %f %f\n8.kose kordinatları %f %f %f\n"
                   ,lowx,lowy,lowz,
                   lowx,lowy,lowz+kenar_uzunluk,
                   lowx,lowy+kenar_uzunluk,lowz,
                   lowx,lowy+kenar_uzunluk,lowz+kenar_uzunluk,
                   lowx+kenar_uzunluk,lowy,lowz,
                   lowx+kenar_uzunluk,lowy,lowz+kenar_uzunluk,
                   lowx+kenar_uzunluk,lowy+kenar_uzunluk,lowz,
                   lowx+kenar_uzunluk,lowy+kenar_uzunluk,lowz+kenar_uzunluk);
fprintf(fptr,"--------------------------------------------\n");
fclose(fptr);

    }else if(enz>0){
        kenar_uzunluk=enz-lowz;
                        FILE *fptr;
fptr=fopen("output.nkt","a");
fprintf(fptr,"Secim 3%s-----------------------------------\n",dosya_ad_gelen);
fprintf(fptr,"1. kose kordinatlari %f %f %f\n2. kose kordinatlari %f %f %f\n3.kose kordinatları %f %f %f\n4.kose kordinatları %f %f %f\n5.kose kordinatları %f %f %f\n6.kose kordinatları %f %f %f\n7.kose kordinatları %f %f %f\n8.kose kordinatları %f %f %f\n"
                   ,lowx,lowy,lowz,
                   lowx,lowy,lowz+kenar_uzunluk,
                   lowx,lowy+kenar_uzunluk,lowz,
                   lowx,lowy+kenar_uzunluk,lowz+kenar_uzunluk,
                   lowx+kenar_uzunluk,lowy,lowz,
                   lowx+kenar_uzunluk,lowy,lowz+kenar_uzunluk,
                   lowx+kenar_uzunluk,lowy+kenar_uzunluk,lowz,
                   lowx+kenar_uzunluk,lowy+kenar_uzunluk,lowz+kenar_uzunluk);
fprintf(fptr,"--------------------------------------------\n");
fclose(fptr);
    }



}else{
        lowx=na[0].x;
        lowy=na[0].y;
        lowz=na[0].z;
        enk_r= sqrt(pow(na[0].x,2)+pow(na[0].y,2)+pow(na[0].z,2));
    for(i=0;i<_nokta_adet;i++){
        if(na[i].x>=na[i].y&&na[i].x>=na[i].z){
            enx=na[i].x;
            eny=0;
            enz=0;

        }else if(na[i].y>=na[i].x&&na[i].y>=na[i].z){
        eny=na[i].y;
        enx=0;
        enz=0;
        }else if(na[i].z>=na[i].x&&na[i].z>=na[i].y){
        enz=na[i].z;
        enx=0;
        eny=0;
        }
        if(lowx>=na[i].x){
            lowx=na[i].x;
        }

        if(lowy>=na[i].y){
            lowx=na[i].y;
        }

        if(lowz>=na[i].z){
            lowz=na[i].z;
        }
    }
    if(enx>0){
            kenar_uzunluk=enx-lowx;
                     FILE *fptr;
fptr=fopen("output.nkt","a");
fprintf(fptr,"Secim 3%s-----------------------------------\n",dosya_ad_gelen);
fprintf(fptr,"1. kose kordinatlari %f %f %f\n2. kose kordinatlari %f %f %f\n3.kose kordinatları %f %f %f\n4.kose kordinatları %f %f %f\n5.kose kordinatları %f %f %f\n6.kose kordinatları %f %f %f\n7.kose kordinatları %f %f %f\n8.kose kordinatları %f %f %f\n"
                   ,lowx,lowy,lowz,
                   lowx,lowy,lowz+kenar_uzunluk,
                   lowx,lowy+kenar_uzunluk,lowz,
                   lowx,lowy+kenar_uzunluk,lowz+kenar_uzunluk,
                   lowx+kenar_uzunluk,lowy,lowz,
                   lowx+kenar_uzunluk,lowy,lowz+kenar_uzunluk,
                   lowx+kenar_uzunluk,lowy+kenar_uzunluk,lowz,
                   lowx+kenar_uzunluk,lowy+kenar_uzunluk,lowz+kenar_uzunluk);
fprintf(fptr,"--------------------------------------------\n");
fclose(fptr);
    }else if(eny>0){
        kenar_uzunluk=eny-lowy;
                       FILE *fptr;
fptr=fopen("output.nkt","a");
fprintf(fptr,"Secim 3%s-----------------------------------\n",dosya_ad_gelen);
fprintf(fptr,"1. kose kordinatlari %f %f %f\n2. kose kordinatlari %f %f %f\n3.kose kordinatları %f %f %f\n4.kose kordinatları %f %f %f\n5.kose kordinatları %f %f %f\n6.kose kordinatları %f %f %f\n7.kose kordinatları %f %f %f\n8.kose kordinatları %f %f %f\n"
                   ,lowx,lowy,lowz,
                   lowx,lowy,lowz+kenar_uzunluk,
                   lowx,lowy+kenar_uzunluk,lowz,
                   lowx,lowy+kenar_uzunluk,lowz+kenar_uzunluk,
                   lowx+kenar_uzunluk,lowy,lowz,
                   lowx+kenar_uzunluk,lowy,lowz+kenar_uzunluk,
                   lowx+kenar_uzunluk,lowy+kenar_uzunluk,lowz,
                   lowx+kenar_uzunluk,lowy+kenar_uzunluk,lowz+kenar_uzunluk);
fprintf(fptr,"--------------------------------------------\n");
fclose(fptr);

    }else if(enz>0){
        kenar_uzunluk=enz-lowz;
                        FILE *fptr;
fptr=fopen("output.nkt","a");
fprintf(fptr,"Secim 3%s-----------------------------------\n",dosya_ad_gelen);
fprintf(fptr,"1. kose kordinatlari %f %f %f\n2. kose kordinatlari %f %f %f\n3.kose kordinatları %f %f %f\n4.kose kordinatları %f %f %f\n5.kose kordinatları %f %f %f\n6.kose kordinatları %f %f %f\n7.kose kordinatları %f %f %f\n8.kose kordinatları %f %f %f\n"
                   ,lowx,lowy,lowz,
                   lowx,lowy,lowz+kenar_uzunluk,
                   lowx,lowy+kenar_uzunluk,lowz,
                   lowx,lowy+kenar_uzunluk,lowz+kenar_uzunluk,
                   lowx+kenar_uzunluk,lowy,lowz,
                   lowx+kenar_uzunluk,lowy,lowz+kenar_uzunluk,
                   lowx+kenar_uzunluk,lowy+kenar_uzunluk,lowz,
                   lowx+kenar_uzunluk,lowy+kenar_uzunluk,lowz+kenar_uzunluk);
fprintf(fptr,"--------------------------------------------\n");
fclose(fptr);
    }
}
}
void en_uzak_en_yakin(struct Nokta *na,struct Nokta_rgb *na_rgb,int _nokta_adet,int _alan_format,char dosya_ad_gelen[20]){
    float x=0,y=0,z=0,x1=0,y1=0,z1=0,x2=0,y2=0,z2=0,x3=0,y3=0,z3=0;
    int i,j;
    double d=0,d1=0;;
if(_alan_format==0){
        d=sqrt(pow(na_rgb[1].x-na_rgb[0].x,2)+pow(na_rgb[1].y-na_rgb[0].y,2)+pow(na_rgb[1].z-na_rgb[0].z,2));
        d1=sqrt(pow(na_rgb[1].x-na_rgb[0].x,2)+pow(na_rgb[1].y-na_rgb[0].y,2)+pow(na_rgb[1].z-na_rgb[0].z,2));
        printf("Hesaplaniyor Bekleyiniz\n");
for(i=0;i<_nokta_adet;i++){
if(i==_nokta_adet-1){
    break;
}
for(j=i+1;j<_nokta_adet;j++){
 if(d<=sqrt(pow(na_rgb[j].x-na_rgb[i].x,2)+pow(na_rgb[j].y-na_rgb[i].y,2)+pow(na_rgb[j].z-na_rgb[i].z,2))){
    d=sqrt(pow(na_rgb[j].x-na_rgb[i].x,2)+pow(na_rgb[j].y-na_rgb[i].y,2)+pow(na_rgb[j].z-na_rgb[i].z,2));
    x=na_rgb[j].x;
    y=na_rgb[j].y;
    z=na_rgb[j].z;
    x1=na_rgb[i].x;
    y1=na_rgb[i].y;
    z1=na_rgb[i].z;
 }
 if(d1>=sqrt(pow(na_rgb[j].x-na_rgb[i].x,2)+pow(na_rgb[j].y-na_rgb[i].y,2)+pow(na_rgb[j].z-na_rgb[i].z,2))){
    d1=sqrt(pow(na_rgb[j].x-na_rgb[i].x,2)+pow(na_rgb[j].y-na_rgb[i].y,2)+pow(na_rgb[j].z-na_rgb[i].z,2));
    x2=na_rgb[j].x;
    y2=na_rgb[j].y;
    z2=na_rgb[j].z;
    x3=na_rgb[i].x;
    y3=na_rgb[i].y;
    z3=na_rgb[i].z;
 }
}
}
FILE *fptr;
fptr=fopen("output.nkt","a");
fprintf(fptr,"Secim 2 %s--------------------------------\n",dosya_ad_gelen);
fprintf(fptr,"%f %f %f\n",x,y,z);
fprintf(fptr,"%f %f %f\n",x1,y1,z1);
fprintf(fptr,"%f %f %f\n",x2,y2,z2);
fprintf(fptr,"%f %f %f\n",x3,y3,z3);
fprintf(fptr,"--------------------------------------------\n");
fclose(fptr);
}else{
    d1=sqrt(pow(na[1].x-na[0].x,2)+pow(na[1].y-na[0].y,2)+pow(na[1].z-na[0].z,2));
    d=sqrt(pow(na[1].x-na[0].x,2)+pow(na[1].y-na[0].y,2)+pow(na[1].z-na[0].z,2));
    printf("Hesaplaniyor Bekleyiniz\n");
    for(i=0;i<_nokta_adet;i++){
if(i==_nokta_adet-1){
    break;
}
for(j=i+1;j<_nokta_adet;j++){
    if(d1>=sqrt(pow(na[j].x-na[i].x,2)+pow(na[j].y-na[i].y,2)+pow(na[j].z-na[i].z,2))){
    d1=sqrt(pow(na[j].x-na[i].x,2)+pow(na[j].y-na[i].y,2)+pow(na[j].z-na[i].z,2));
    x2=na[j].x;
    y2=na[j].y;
    z2=na[j].z;
    x3=na[i].x;
    y3=na[i].y;
    z3=na[i].z;

    }
    if(d<=sqrt(pow(na[j].x-na[i].x,2)+pow(na[j].y-na[i].y,2)+pow(na[j].z-na[i].z,2))){
        d=sqrt(pow(na[j].x-na[i].x,2)+pow(na[j].y-na[i].y,2)+pow(na[j].z-na[i].z,2));
        x=na[j].x;
        y=na[j].y;
        z=na[j].z;
        x1=na[i].x;
        y1=na[i].y;
        z1=na[i].z;


    }
}

}
FILE *fptr;
fptr=fopen("output.nkt","a");
fprintf(fptr,"Secim 2%s-----------------------------------\n",dosya_ad_gelen);
fprintf(fptr,"%f %f %f\n",x2,y2,z2);
fprintf(fptr,"%f %f %f\n",x3,y3,z3);
fprintf(fptr,"%f %f %f\n",x1,y1,z1);
fprintf(fptr,"%f %f %f\n",x,y,z);
fprintf(fptr,"--------------------------------------------\n");
fclose(fptr);
}
}
void binary_nokta_al(int _nokta_adet,char dosya_ad[20],struct Nokta_rgb *na_rgb,int _alanformat,struct Nokta *na,FILE *fptr){
    int i;


if(_alanformat==0){
for (i=0;i<_nokta_adet;i++){
    fread(na_rgb+i,sizeof(struct Nokta_rgb),1,fptr);
}
}else if(_alanformat==1){
for (i=0;i<_nokta_adet;i++){
    fread(na+i,sizeof(struct Nokta),1,fptr);
}

}
}
int main()
{
/// Burada veri tanımlamaları yapıldı.
///---------------------------------------------------------------------------------------------------------------
    int nokta_adet=0,alanformat=0,_versiyon=0,data_format=0,dosyalar = 0,counter_line=0,gercek_nokta_adet=0,cursor_konum,hata=0,vud=0,hata_boool,girme_kontrol=0;
    float x=0,y=0,z=0,r=0;
    DIR *dosya;
    struct dirent *girdi;
    char dosyaadi[20][50];
    char uygun_dosya[10][50];
    FILE *fptr1;
    char verileri_uygun_dosya[10][50];
    char ctrl_info[4][40];
    char hatalar[30][100];
    char filef[100];
    struct Nokta_rgb *nokta_rgb;
    struct Nokta *nokta;
///--------------------------------------------------------------------------------------------------------------------
    dosya = opendir(".");
    if(dosya == NULL)
    {
        perror("Dosya okunamadi");
        return(1);
    }

    while( (girdi=readdir(dosya)) )
    {
        dosyalar++;
        if(dosyalar>2)
        {
            printf("File %3d: %s\n",(dosyalar-2),girdi->d_name);
            strcpy(dosyaadi[dosyalar-3],girdi->d_name);
        }
    }
    int say,say1,uds=0;
    int dosya_ad_uzunluk;
    for(say =0;say<dosyalar-2;say++){
        dosya_ad_uzunluk=strlen(dosyaadi[say]);
        for(say1=0;say1<dosya_ad_uzunluk;say1++){
            if(dosyaadi[say][say1]=='.'&&dosyaadi[say][say1+1]=='n'&&dosyaadi[say][say1+2]=='k'&&dosyaadi[say][say1+3]=='t'){///.nkt ile bitmeyen dosyalar alınmaz
                strcpy(uygun_dosya[uds],dosyaadi[say]);
                uds++;
            }

        }
    }


    int i;
    for(i=0;i<uds;i++){
    strcpy(filef,uygun_dosya[i]);
    printf("dosya adi: %s\n",uygun_dosya[i]);
    char dosya_ad_deneme[20];
    strcpy(dosya_ad_deneme,uygun_dosya[i]);
    fptr1 = fopen(filef,"r");
    if(fptr1==NULL)
    {
        printf("dosya acilamadi.");
    }
        veri_al(ctrl_info,fptr1);
        veri_kontrol(ctrl_info,&_versiyon,&alanformat,&nokta_adet,&data_format,hatalar,&hata,dosya_ad_deneme,&hata_boool);

        if(hata_boool==0&&data_format==0){
        nokta_kontrol(fptr1,&gercek_nokta_adet,alanformat,nokta_adet,&hata,hatalar,dosya_ad_deneme,&hata_boool);

        }else if(hata_boool==0&&data_format==1){



        }
    ///hatasız ise

    if(hata_boool==0){
        strcpy(verileri_uygun_dosya[vud],dosya_ad_deneme);
        vud++;
    }
printf("Bu Dosya okundu \n\n\n");
    fclose(fptr1);
    }
    int islem=-1;
    int j,k;
    while(1){
    printf("Islem Yapmak Icin Bir Sayi Giriniz\n\n");
    printf("**********************************************\n");
    printf("Hatalari Gormek Icin 1 Giriniz\n");
    printf("**********************************************\n");
    printf("En uzak En yakin Noktalar Icin 2 Giriniz\n");
    printf("**********************************************\n");
    printf("Tum Noktalari Icine alacak Bir Kup Icin 3 Giriniz\n");
    printf("**********************************************\n");
    printf("Verilen Kordinatlarda Bir kurenin Icinde Kalan Noktalar Icin 4 Giriniz\n");
    printf("**********************************************\n");
    printf("Noktalar Arasi Uzaklik Ortalamasi Icin 5 Giriniz\n");
    printf("**********************************************\n");
    printf("Programdan Cikmak Icin 6 Giriniz\n");
    scanf("%d",&islem);
    if(islem==1){
            printf("**********************************************\n");
            printf("**********************************************\n");
        for(j=0;j<hata;j++){
    printf("%s\n",hatalar[j]);

    }
       printf("**********************************************\n");
    printf("**********************************************\n");
    }else if(islem==2){
        printf("**********************************************\n");
        printf("**********************************************\n");
        for(k=0;k<vud;k++){
        char dosya_ad_deneme1[20];
        strcpy(filef,verileri_uygun_dosya[k]);
        strcpy(dosya_ad_deneme1,verileri_uygun_dosya[k]);
        fptr1 = fopen(filef,"r");
        veri_al(ctrl_info,fptr1);
        veri_kontrol(ctrl_info,&_versiyon,&alanformat,&nokta_adet,&data_format,hatalar,&hata,dosya_ad_deneme1,&hata_boool);
        if(hata_boool==0&&data_format==0){
        nokta_kontrol(fptr1,&gercek_nokta_adet,alanformat,nokta_adet,&hata,hatalar,dosya_ad_deneme1,&hata_boool);
    }else if(hata_boool==0&&data_format==1){

    }
    fclose(fptr1);
    fptr1=fopen(filef,"r");
    int bosluk_sayac=0,atla_sayac=0;
    char kont;
    while(!feof(fptr1)){
            kont=fgetc(fptr1);
            bosluk_sayac++;
        if(kont=='\n'){
        atla_sayac++;
        }
        if(atla_sayac==5){
            break;
        }

    }
    fseek(fptr1,bosluk_sayac,SEEK_SET);
if(data_format==0){
            if(alanformat==1){
            nokta=malloc(nokta_adet*sizeof(struct Nokta));
            nokta_al(nokta_adet,fptr1,NULL,&alanformat,nokta);
            en_uzak_en_yakin(nokta,NULL,nokta_adet,alanformat,dosya_ad_deneme1);
            }else if(alanformat==0){
            nokta_rgb=malloc(nokta_adet*sizeof(struct Nokta_rgb));
            nokta_al(nokta_adet,fptr1,nokta_rgb,alanformat,NULL);
            en_uzak_en_yakin(NULL,nokta_rgb,nokta_adet,alanformat,dosya_ad_deneme1);
            }
        }else{

        if(alanformat==1){
            nokta=malloc(nokta_adet*sizeof(struct Nokta));
            binary_nokta_al(nokta_adet,dosya_ad_deneme1,NULL,alanformat,nokta,fptr1);
            en_uzak_en_yakin(nokta,NULL,nokta_adet,alanformat,dosya_ad_deneme1);
            }else if(alanformat==0){
            nokta_rgb=malloc(nokta_adet*sizeof(struct Nokta_rgb));
            binary_nokta_al(nokta_adet,dosya_ad_deneme1,nokta_rgb,alanformat,NULL,fptr1);
            en_uzak_en_yakin(NULL,nokta_rgb,nokta_adet,alanformat,dosya_ad_deneme1);
        }



    }}
    printf("**********************************************\n");
    printf("**********************************************\n");
    }else if(islem==3){
        printf("**********************************************\n");
        printf("**********************************************\n");
        for(k=0;k<vud;k++){
        char dosya_ad_deneme1[20];
    strcpy(filef,verileri_uygun_dosya[k]);
    strcpy(dosya_ad_deneme1,verileri_uygun_dosya[k]);
    fptr1 = fopen(filef,"r");
    veri_al(ctrl_info,fptr1);
    veri_kontrol(ctrl_info,&_versiyon,&alanformat,&nokta_adet,&data_format,hatalar,&hata,dosya_ad_deneme1,&hata_boool);
    if(hata_boool==0&&data_format==0){
        nokta_kontrol(fptr1,&gercek_nokta_adet,alanformat,nokta_adet,&hata,hatalar,dosya_ad_deneme1,&hata_boool);
    }else if(hata_boool==0&&data_format==1){

    }
    fclose(fptr1);
    fptr1=fopen(filef,"r");
    int bosluk_sayac=0,atla_sayac=0;
    char kont;
    while(!feof(fptr1)){
            kont=fgetc(fptr1);
            bosluk_sayac++;
        if(kont=='\n'){
        atla_sayac++;
        }
        if(atla_sayac==5){
            break;
        }

    }
    fseek(fptr1,bosluk_sayac,SEEK_SET);

if(data_format==0){
            if(alanformat==1){
            nokta=malloc(nokta_adet*sizeof(struct Nokta));
            nokta_al(nokta_adet,fptr1,NULL,&alanformat,nokta);
            kup_noktalari(nokta,NULL,nokta_adet,alanformat,dosya_ad_deneme1);
            }else if(alanformat==0){
            nokta_rgb=malloc(nokta_adet*sizeof(struct Nokta_rgb));
            nokta_al(nokta_adet,fptr1,nokta_rgb,alanformat,NULL);
            kup_noktalari(NULL,nokta_rgb,nokta_adet,alanformat,dosya_ad_deneme1);
            }
        }else{

        if(alanformat==1){
            nokta=malloc(nokta_adet*sizeof(struct Nokta));
            binary_nokta_al(nokta_adet,dosya_ad_deneme1,NULL,alanformat,nokta,fptr1);
            kup_noktalari(nokta,NULL,nokta_adet,alanformat,dosya_ad_deneme1);
            }else if(alanformat==0){
            nokta_rgb=malloc(nokta_adet*sizeof(struct Nokta_rgb));
            binary_nokta_al(nokta_adet,dosya_ad_deneme1,nokta_rgb,alanformat,NULL,fptr1);
            kup_noktalari(NULL,nokta_rgb,nokta_adet,alanformat,dosya_ad_deneme1);
        }



    }
        }
        printf("**********************************************\n");
        printf("**********************************************\n");
    }else if(islem==4){
        printf("**********************************************\n");
        printf("**********************************************\n");
        for(k=0;k<vud;k++){
        char dosya_ad_deneme1[20];
        strcpy(filef,verileri_uygun_dosya[k]);
        strcpy(dosya_ad_deneme1,verileri_uygun_dosya[k]);
        fptr1 = fopen(filef,"r");
        veri_al(ctrl_info,fptr1);
        veri_kontrol(ctrl_info,&_versiyon,&alanformat,&nokta_adet,&data_format,hatalar,&hata,dosya_ad_deneme1,&hata_boool);
        if(hata_boool==0&&data_format==0){
        nokta_kontrol(fptr1,&gercek_nokta_adet,alanformat,nokta_adet,&hata,hatalar,dosya_ad_deneme1,&hata_boool);
    }else if(hata_boool==0&&data_format==1){

    }
    fclose(fptr1);
    fptr1=fopen(filef,"r");
    int bosluk_sayac=0,atla_sayac=0;
    char kont;
    while(!feof(fptr1)){
            kont=fgetc(fptr1);
            bosluk_sayac++;
        if(kont=='\n'){
        atla_sayac++;
        }
        if(atla_sayac==5){
            break;
        }

    }
    fseek(fptr1,bosluk_sayac,SEEK_SET);

        if(data_format==0){
            if(alanformat==1){
            nokta=malloc(nokta_adet*sizeof(struct Nokta));
            nokta_al(nokta_adet,fptr1,NULL,&alanformat,nokta);
            kure_nokta_bul(nokta,NULL,alanformat,nokta_adet,dosya_ad_deneme1,&x,&y,&z,&r,&girme_kontrol);
            }else if(alanformat==0){
            nokta_rgb=malloc(nokta_adet*sizeof(struct Nokta_rgb));
            nokta_al(nokta_adet,fptr1,nokta_rgb,alanformat,NULL);
            kure_nokta_bul(NULL,nokta_rgb,alanformat,nokta_adet,dosya_ad_deneme1,&x,&y,&z,&r,&girme_kontrol);
            }
        }else{

        if(alanformat==1){
            nokta=malloc(nokta_adet*sizeof(struct Nokta));
            binary_nokta_al(nokta_adet,dosya_ad_deneme1,NULL,alanformat,nokta,fptr1);
            kure_nokta_bul(nokta,NULL,alanformat,nokta_adet,dosya_ad_deneme1,&x,&y,&z,&r,&girme_kontrol);
            }else if(alanformat==0){
            nokta_rgb=malloc(nokta_adet*sizeof(struct Nokta_rgb));
            binary_nokta_al(nokta_adet,dosya_ad_deneme1,nokta_rgb,alanformat,NULL,fptr1);
            kure_nokta_bul(NULL,nokta_rgb,alanformat,nokta_adet,dosya_ad_deneme1,&x,&y,&z,&r,&girme_kontrol);
        }



    }
        }
printf("**********************************************\n");
printf("**********************************************\n");


    }else if(islem==5){
        printf("**********************************************\n");
        printf("**********************************************\n");
        for(k=0;k<vud;k++){
        char dosya_ad_deneme1[20];
        strcpy(filef,verileri_uygun_dosya[k]);
        strcpy(dosya_ad_deneme1,verileri_uygun_dosya[k]);
        fptr1 = fopen(filef,"r");
        veri_al(ctrl_info,fptr1);
        veri_kontrol(ctrl_info,&_versiyon,&alanformat,&nokta_adet,&data_format,hatalar,&hata,dosya_ad_deneme1,&hata_boool);
        if(hata_boool==0&&data_format==0){
        nokta_kontrol(fptr1,&gercek_nokta_adet,alanformat,nokta_adet,&hata,hatalar,dosya_ad_deneme1,&hata_boool);
    }else if(hata_boool==0&&data_format==1){

    }
    fclose(fptr1);
    fptr1=fopen(filef,"r");
    int bosluk_sayac=0,atla_sayac=0;
    char kont;
    while(!feof(fptr1)){
            kont=fgetc(fptr1);
            bosluk_sayac++;
        if(kont=='\n'){
        atla_sayac++;
        }
        if(atla_sayac==5){
            break;
        }

    }
    fseek(fptr1,bosluk_sayac,SEEK_SET);

            if(data_format==0){
            if(alanformat==1){
            nokta=malloc(nokta_adet*sizeof(struct Nokta));
            nokta_al(nokta_adet,fptr1,NULL,&alanformat,nokta);
            nokta_uzaklik_ortalama(nokta,NULL,nokta_adet,alanformat,dosya_ad_deneme1);
            }else if(alanformat==0){
            nokta_rgb=malloc(nokta_adet*sizeof(struct Nokta_rgb));
            nokta_al(nokta_adet,fptr1,nokta_rgb,alanformat,NULL);
            nokta_uzaklik_ortalama(NULL,nokta_rgb,nokta_adet,alanformat,dosya_ad_deneme1);
            }
        }else{

        if(alanformat==1){
            nokta=malloc(nokta_adet*sizeof(struct Nokta));
            binary_nokta_al(nokta_adet,dosya_ad_deneme1,NULL,alanformat,nokta,fptr1);
            nokta_uzaklik_ortalama(nokta,NULL,nokta_adet,alanformat,dosya_ad_deneme1);
            }else if(alanformat==0){
            nokta_rgb=malloc(nokta_adet*sizeof(struct Nokta_rgb));
            binary_nokta_al(nokta_adet,dosya_ad_deneme1,nokta_rgb,alanformat,NULL,fptr1);
            nokta_uzaklik_ortalama(NULL,nokta_rgb,nokta_adet,alanformat,dosya_ad_deneme1);
        }



    }
        }
printf("**********************************************\n");
printf("**********************************************\n");
    }else if(islem==6){
        printf("**********************************************\n");
        printf("********HOSCA KALIN.***********\n");

    break;
    }

islem=-1;
    }
    closedir(dosya);
    return(0);

}
