#include <stdio.h>

// Extended Euclidean Algorithm; x is the modular inverse of a mod b
int EEA(int a, int b, int *x, int *y);

int main(){
    int a, b;
    int x, y;

    scanf("%d %d", &a,&b);
    
    return 0;
}

int EEA(int a, int b, int *x, int *y){
    if (!b) {
        *x = 1;
        *y = 0;
        return a;
    }

    int x1, y1;
    int gcd = EEA(b, a % b, &x1, &y1);

    *x = y1;
    *y = x1 - y1 * (a / b);

    return gcd;
}