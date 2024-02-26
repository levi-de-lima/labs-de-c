#include <stdio.h>
#include <math.h>
int main()
{
    int cubo;
    int a, b;
    float x, y, w, t, z;

    a = 7/3;              printf ("a = %d \n", a);
    b = 8/3;              printf ("b = %d \n", b);
    x = 8/3;              printf ("x = %f \n", x);
    y = 8.0/3;            printf ("y = %f \n", y);
    a = 8;
    b = 3;
    w = a / b;            printf ("w = %f \n", w);
    t = (float) a / b;    printf ("t = %f \n", t);
    z = (float) (a / b);  printf ("z = %f \n", z);

    a = -7 / 3;           printf ("a = %d \n", a); //-2

    a = 5;
    cubo = pow (a,3);
    printf ("o cubo de %d vale %d \n", a, cubo);

    x = pow (a, 3);
    printf ("O cubo de %d vale %f \n", a, x);

    getchar();
    return 0;
}
