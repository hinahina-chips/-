#include "myJpeg.h"

int main(int argc, char *argv[]){

    BITMAPDATA_t bitmap;
    int i, j, c;
    int ave, sum;
    char outname[256];

    FILE *fo;
    if(argc != 2){
        printf("ファイル名が指定されていません\n");
        return -1;
    }

    if(jpegFileReadDecode(&bitmap, argv[1]) == -1){
        printf("jpegFileReadDecode error\n");
        return -1;
    }

    printf("bitmap->data = %p\n", bitmap.data);
    printf("bitmap->width = %d\n", bitmap.width);
    printf("bitmap->height = %d\n", bitmap.height);
    printf("bitmap->ch = %d\n", bitmap.ch);

#if 0
  /* ちゃんと読み込めているか確認する場合はここを有効に */
  fo = fopen("testoutput.ppm", "wb");
  fprintf(fo, "P6\n#\n%d %d\n255\n", bitmap.width, bitmap.height);
  fwrite(bitmap.data, bitmap.height * bitmap.width * 3, 1,fo);
  fclose(fo);
#endif

    for(j = 0; j < bitmap.height; j++){
        for(i = 0; i < bitmap.width; i++){
            sum = 0;
            for(c = 0; c < bitmap.ch; c++){
                sum += bitmap.data[bitmap.ch * (i + j * bitmap.width) + c];
            }
            ave = sum / bitmap.ch;
            for(c = 0; c < bitmap.ch; c++){
                bitmap.data[bitmap.ch * (i + j * bitmap.width) + c] = ave;
            }
        }
    }

    sprintf(outname, "%s", "output.jpg");

    if(jpegFileEncodeWrite(&bitmap, outname) == -1){
        printf("jpegFileEncodeWrite error\n");
        freeBitmapData(&bitmap);
        return -1;
    }

    freeBitmapData(&bitmap);

    return 0;
}
