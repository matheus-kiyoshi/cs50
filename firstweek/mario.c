#include <stdio.h>

void draw(int height);

int main(void) 
{
    int height;
    int ret;
    printf("Height: ");
    do {
       ret = scanf("%i", &height);
      if (ret != 1 || height < 0) {
          while (getchar() != '\n');
          printf("Invalid input. Please enter a positive integer:  ");
      }
    } 
    while (ret != 1 || height < 0);
    draw(height);
}

void draw(int height)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < height - i; j++)
        {
            printf(" ");
        }
        for (int k = 0; k < i + 1; k++)
        {
            printf("#");
        }
        printf("  ");
        for (int k = 0; k < i + 1; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}
