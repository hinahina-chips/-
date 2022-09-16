#include<stdio.h>
#include<math.h>

#define SIZE 256

int main(void){
    int i, j;
    int X, Y;
    int center = SIZE / 2;
    double theta = M_PI / 3.0;

    unsigned char img[SIZE][SIZE];
    unsigned char img2[SIZE][SIZE];

    FILE *fp;

    fp = fopen("poppo.raw","rb");
    fread(img, 1, SIZE * SIZE,fp);
    fclose(fp);

    for(i = 0; i < SIZE; i++)
        for(j = 0; j < SIZE; j++){
            img2[i][j] = 255;
        }     //白に初期化

    //回転
    for(i = 0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++){
            X = (int)((j - center) * cos(theta) + (i - center) * sin(theta) + center + 0.5);
            Y = (int)((j - center) * sin(theta) - (i - center) * cos(theta) + center + 0.5); 

            if(X >=0 && X < SIZE && Y >= 0 && Y < SIZE){
                img2[i][j] = img[X][Y];
            }
        }
    }
    
    fp = fopen("poppo1.raw","wb");
    fwrite(img2,1,SIZE*SIZE,fp);
    fclose(fp);
    return 0;
}