#include <stdio.h>

void main(int argc, char *argv[]) {
    
    if (strcmp("cyberyeti", argv[1]) == 0){
        puts("You win!");
    } else {
        puts("Try again :(");
    }
}