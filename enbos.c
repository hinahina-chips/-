#include<stdio.h>
#include<math.h>

#define SIZE 256

int main(void){
    int i,j;
    unsigned char img[SIZE][SIZE];
    unsigned char img2[SIZE][SIZE];

     FILE *fp;


    fp = fopen("poppo1.raw","rb");
    fread(img,1,SIZE*SIZE,fp);
    fclose(fp);

    for(i=0;i<SIZE;i++)//エンボス処理
        for(j=0;j<SIZE;j++){
            img2[i][j] = img[i+5][j+5];//平行移動５
            img2[i][j]=255-img2[i][j];//ネガポジ反転
            img2[i][j]=img[i][j]+img2[i][j];
         }
         
         for(i=SIZE-5;i<SIZE;i++)
        for(j=SIZE-5;j<SIZE;j++){
            img2[i][j]=127;//隙間領域に127を設定
        }

fp = fopen("poppo1.raw","wb");
    fwrite(img2,1,SIZE*SIZE,fp);
    fclose(fp);
    return 0;
}

