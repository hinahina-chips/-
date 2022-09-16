#include<stdio.h>
#include<math.h>

#define SIZE 256

int main(void){
    int i,j;
    int imgh,imgv;
    unsigned char img[SIZE][SIZE];
    unsigned char img2[SIZE][SIZE];

    FILE *fp;

    fp = fopen("poppo2.raw","rb");
    fread(img, 1, SIZE * SIZE,fp);
    fclose(fp);

    for(i = 1;i < SIZE-1; i++){
        for(j = 1; j < SIZE-1; j++){

            imgh = img[i+1][j-1] + img[i+1][j] + img[i+1][j+1] - img[i-1][j-1] - img[i-1][j] - img[i-1][j+1];　//横方向のフィルタの適応
            imgv = img[i-1][j-1] + img[i][j-1] + img[i+1][j-1] - img[i-1][j+1] - img[i][j+1] - img[i+1][j+1];　//縦方向のフィルタの適応
        
            img2[i][j] = sqrt(imgh * imgh + imgv * imgv); //IhとIvの統合

            //二値化
            if(img2[i][j] > 100) img2[i][j] = 255;

            else if(img2[i][j] <= 100) img2[i][j] = 0;
        }
    }
    

    fp = fopen("poppo2.raw","wb");
    fwrite(img2,1,SIZE*SIZE,fp);
    fclose(fp);
    return 0;
}