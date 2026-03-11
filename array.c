#include <stdio.h> 

int main() {
    double number[6]= {20, 10, 20.2, 43.2, 54.0, 3.14159};
    char letters= 'A';

    double sum = number[0] + number[1] + number[2] + number[3] + number[4] + number[5] + number[6];

    printf("the sum of % .2f, %.2f, %.2f, %.2f, %.2f and %.5f is %.5f\n",number[0], number[1], number[2], number[3], number[4], number[5], sum, letters);
    return 0;
}
