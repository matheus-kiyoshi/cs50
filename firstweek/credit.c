#include <stdio.h>
#include <math.h>

char* check_card_type(long long int card_number);
int card_verfiy(long long int card_number);

int main(void) 
{
	long long int card_number;
	int ret;
	printf("Number: ");
	do {
       ret = scanf("%lld", &card_number);
      if (ret != 1 || card_number < 0) {
          while (getchar() != '\n');
          printf("Invalid input. Please enter a positive integer:  ");
      }
    } 
    while (ret != 1 || card_number < 0);
	card_verfiy(card_number);
}

int card_verfiy(long long int card_number) 
{
	char *card_type = check_card_type(card_number);
	long long int reversed_card_number = 0;
	while (card_number > 0) 
	{
        reversed_card_number = reversed_card_number * 10 + card_number % 10;
        card_number /= 10;
    }
	
	int sum = 0;
	int multiplyByTwo = 0;
	while (reversed_card_number > 0) 
	{
        multiplyByTwo = 2 * (reversed_card_number % 10);
        sum += (multiplyByTwo % 10) + (multiplyByTwo / 10);
        reversed_card_number /= 10;

        if (reversed_card_number > 0) {
            sum += reversed_card_number % 10;
            reversed_card_number /= 10;
        }
    }

	if (sum % 10 == 0) {
		printf("%s\n", card_type);
    } else {
        printf("INVALID.\n");
    }

	return 0;
}

char* check_card_type(long long int card_number) 
{
	long long int first2 = card_number;
	while(first2 >= 100)
	{
		first2 = first2 / 10;
	}

	int firstDigit = first2 / 10;
	int secondDigit = first2 % 10;

	if (firstDigit == 3 && (secondDigit == 4 || secondDigit == 7)) {
		return "AMEX";
	} else if (firstDigit == 5 && (secondDigit == 1 || secondDigit == 2 || secondDigit == 3 || secondDigit == 4 || secondDigit == 5)) {
		return "MASTERCARD";
	} else if (firstDigit == 4) {
		return "VISA";
	} else {
		return "INVALID";
	}
}
