#include <stdio.h>
#include <stdint.h>

int main(int32_t argc, char* argv[]){
    if (argc < 3) {
        printf("Use : add-nbo.exe <file1> <file2>");
        return 0;
    } // 인자 값이 부족하면 사용법을 알려준다.

    int32_t i;
    int32_t file1, file2, file3;

    for(i=1; i<=argc-1; i++){
        FILE *input;
        input = fopen(argv[i],"rb");
        // 파일의 바이너리를 읽어온다.
        
        if (input == NULL){
            printf("File Binary Read Error!");
            return 0;
        } // 파일을 정상적으로 불러오지 못하면 에러를 띄운다.

        int32_t n;
        fread(&n, sizeof(int32_t), 1, input);
        if (i==1) file1 = (n&0x000000FF)<<24|(n&0x0000FF00)<<8|(n&0x00FF0000)>>8|(n&0xFF000000)>>24;
        if (i==2) file2 = (n&0x000000FF)<<24|(n&0x0000FF00)<<8|(n&0x00FF0000)>>8|(n&0xFF000000)>>24;
        fclose(input);
    }
        /*  12 34 56 78 (NBO)
            78 56 34 12 (HBO)
                -> 00 00 00 12 (and) -> 12 00 00 00 (shift)
                -> 00 00 34 00 (and) -> 00 34 00 00 (shift)
                -> 00 56 00 00 (and) -> 00 00 56 00 (shift)
                -> 78 00 00 00 (and) -> 00 00 00 78 (shift)
                                     -> 12 34 56 78 (or) */
    
    file3 = file1 + file2;
    printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n",file1,file1,file2,file2,file3,file3);
    return 0;
}