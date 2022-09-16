#include "myJpeg.h"

int jpegFileReadDecode(BITMAPDATA_t *bitmapData, const char* filename){
    struct jpeg_decompress_struct jpeg;
    struct jpeg_error_mgr err;

    FILE *fi;
    int j;
    JSAMPLE *tmp;
  
    jpeg.err = jpeg_std_error(&err);//エラーハンドラの設定

    fi = fopen(filename, "rb");
    if(fi == NULL){printf("%sは開けません\n", filename); return -1;}

    jpeg_create_decompress(&jpeg);//デコーダの初期化
    jpeg_stdio_src(&jpeg, fi);//読み込むjpegファイルの設定
    jpeg_read_header(&jpeg, TRUE);//ヘッダー情報の取得
    jpeg_start_decompress(&jpeg);//デコードの開始

    printf("width = %d, height = %d, ch = %d\n",
    jpeg.output_width, jpeg.output_height,
    jpeg.out_color_components);

    bitmapData->data = (unsigned char*)malloc(sizeof(unsigned char) 
    *jpeg.output_width * jpeg.output_height * jpeg.out_color_components);

    if(bitmapData->data == NULL){
        printf("data malloc error\n");
        fclose(fi);
        jpeg_destroy_decompress(&jpeg);
        return -1;
    }

    for(j = 0; j < jpeg.output_height; j++){
        tmp = bitmapData->data + j * jpeg.out_color_components * jpeg.output_width;
        jpeg_read_scanlines(&jpeg, &tmp, 1);
        //1ラインずつ順番にJPEGファイルがデコードされ、ビットマップデータに変換
    }
    bitmapData->height = jpeg.output_height;
    bitmapData->width = jpeg.output_width;
    bitmapData->ch = jpeg.out_color_components;
    
    jpeg_finish_decompress(&jpeg);
    jpeg_destroy_decompress(&jpeg);

    fclose(fi);
    return 0;
}

int jpegFileEncodeWrite(BITMAPDATA_t *bitmapData, const char *filename){
    struct jpeg_compress_struct jpeg;
    struct jpeg_error_mgr err;
    FILE *fo;
    JSAMPLE *address;
    int j;

    fo = fopen(filename, "wb");
    if(fo == NULL){
    printf("%sは開けません\n", filename);
    jpeg_destroy_compress(&jpeg);
    return -1;
    }

    jpeg_stdio_dest(&jpeg, fo);
    
//ヘッダ情報の設定-------------------------------
    jpeg.image_width = bitmapData->width;
    jpeg.image_height = bitmapData->height;
    jpeg.input_components = bitmapData->ch;
    jpeg.in_color_space = JCS_RGB;
    jpeg_set_defaults(&jpeg);//設定されていないヘッダ情報をデフォルト値に設定する関数
//-----------------------------------------------

    jpeg_set_quality(&jpeg, 50, TRUE);//画質の設定
    jpeg_start_compress(&jpeg, TRUE);

    for(j = 0; j < jpeg.image_height; j++){
        address = bitmapData->data + (j * bitmapData->width * bitmapData->ch);
        jpeg_write_scanlines(&jpeg, &address, 1);
    }

    jpeg_finish_compress(&jpeg);
    jpeg_destroy_compress(&jpeg);

    return 0;
}

int freeBitmapData(BITMAPDATA_t *bitmap){
  free(bitmap->data);
  return 0;
}


  

