#include<stdio.h>


int is_prime(unsigned long number) {
    
    if (number <= 1) 
        return 0;
    
    for (unsigned long i = 2; i * i <= number; i++) {
        if (number % i == 0) 
            return 0;
    }

    return 1;
}


int main() {
    unsigned long user_input;
    printf("Please, input your number: ");
    scanf("%lu", &user_input);

    printf("Your number [%lu] is %s", user_input, is_prime(user_input) ? "prime" : "not prime");

    return 0;
}
