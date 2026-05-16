//vcard
#include <stdio.h>

int main() {
    char person[256];
    int attachments = 2;

    scanf("%[^\n]", person);

    printf("Hallo %s \n", person);
    printf("Anhänge: %d \n", attachments);

    return 0;
}