#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *name = (char*) malloc(sizeof(char) * 100);
    scanf("%s", name);
    printf("Hello, %s!\n", name);
    return 0;
}
