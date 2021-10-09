#include <cmath>
#include <cstdio>

int main() {
    double InOutPut;
    scanf("%lf", &InOutPut);
    InOutPut /= (2*M_PI);
    printf("R = %lf\n", InOutPut);
    InOutPut *= InOutPut * M_PI;
    printf("S = %lf\n", InOutPut);
    return 0;
}
