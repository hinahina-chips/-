#include<stdio.h>
#include<math.h>

#define SIZE 256

int main(void){
    int i,j;
    unsigned char img[SIZE][SIZE];
    unsigned char img2[SIZE][SIZE];


    FILE *fp;


    fp = fopen("poppo.raw","rb");
    fread(img,1,SIZE*SIZE,fp);
    fclose(fp);

    for(i=0;i<SIZE;i++)//トーンカーブによる変換、y=5x
        for(j = 0; j < SIZE; j++){
            img2[i][j] = 10 * img[i][j];
        }

 fp = fopen("poppo.raw","wb");
    fwrite(img2,1,SIZE*SIZE,fp);
    fclose(fp);

    return 0;
}

    