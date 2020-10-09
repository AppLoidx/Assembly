#include<stdio.h>

int scalar(
        const int* vector1, 
        const int* vector2,
        const size_t size) 
{
    int result = 0;
    for (size_t i = 0; i < size; i++) {
        result += vector1[i] * vector2[i];
    }

    return result;
}

int main() {
    const int a[] = {1,2,3};
    const int b[] = {666,666,666};

    int product = scalar(a, b, sizeof(a) / sizeof(a[0]));
    printf("Result is : %d\n", product);
    return 0;
}
