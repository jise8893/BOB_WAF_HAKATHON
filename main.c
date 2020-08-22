#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    //cpy.c 파일을 참고하여, 3개 이상의 파일인자를 마지막 인자값의 디렉터리에 복사하는 프로그램으로 완성해봅시다.

	int i = argc; // 인자 개수, 첫번째 인자는 cpy.exe이고 두번째 인자는 test.txt임
	printf("%d\n", i);
	printf("ARGC : %d\n", argc);

	if ( argc < 3 ) {
		printf("Usage : %s <filename1> <filename2>\n", argv[0]);
		printf("or\nUsage : %s <filename1> <filename2> ... <directory name>\n", argv[0]);
		//return 0;
	}
    for(int j=1;j<argc-1;j++){
        FILE *fd, *dest;
        char buf[257];
        char s1[255];
        strcpy(s1, argv[j]);
        char s2[255];
        strcpy(s2, argv[argc-1]);
        strcat (s2, "/");
        strcat(s2, s1);
        printf("%s\n", s2);
        int len;

        fd = fopen(argv[j], "r");
        dest = fopen(s2, "w");
        //printf("last argv : %s\n", argv[argc-1]);
        //printf("path : %s\n", argv[argc-1] + "/" + argv[2]);

        while ( len=fread(buf, 1, 256, fd)  )
        {
            printf("len : %d\n", len);

            buf[len] = '\0';
            printf("%s\n", buf);

            fwrite(buf, 1, len, dest);


        }

        fclose(dest);
        fclose(fd);

    }


	return 0;
}
