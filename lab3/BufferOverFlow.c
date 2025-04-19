#include <stdio.h>
#include <string.h>

int main() {
    char B[10];             
    char s1[] = "I owe you $1000"; 
    char s2[] = "I don't know you"; 

    while (1) {
        printf("What's your name? ");
        gets(B);
        if (strstr(B, "joker") != NULL) {
           
            printf("%s\n", s1);
        } else {
           
            printf("%s\n", s2);
        }

    
    }

    return 0;
}
