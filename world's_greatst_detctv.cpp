#include <stdio.h>
#include <unistd.h>
int main(){
    for(int i=0;i<20;i++){
       usleep(70000);
        printf("N");
        //printf("YEET\n");
       usleep(70000);
        printf("A");
       usleep(70000);
      // puts("");
    }
    puts("");
    usleep(600000000);
    printf("BATMAN!\n");
    getchar();
    return 0;
}
