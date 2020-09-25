#include <stdio.h>
#include <unistd.h>
int main(){
    for(int i=0;i<7;i++){
       usleep(6000);
        printf("N");
       usleep(6000);
        printf("A");
       usleep(6000);
    }
    usleep(60000);
    printf("BATMAN\n");
    getchar();
    return 0;
}