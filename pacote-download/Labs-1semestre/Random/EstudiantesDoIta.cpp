#include <stdio.h>
#include <stdlib.h>
int main ()
{
    int i, x;

    // PRIMEIRA PARTE

    x = 0;
    i = 50;
                        //i = i + 1;
                        //x = i;
    x = ++i;
    printf ("x = %d \n", x);
    printf ("i = %d \n", i);
    printf ("\n\n", i);

    // SEGUNDA PARTE

    x = 5;
    printf ("   x = %d \n", x   );
    printf ("A:     %d \n", x+1 );
    printf ("   x = %d \n", x   );
    printf ("B:     %d \n", x++ );
    printf ("   x = %d \n", x   );
    printf ("C:     %d \n", ++x );
    printf ("   x = %d \n", x   );

    // TERCEIRA PARTE
    x = 7;
    printf ("\n\n");
    printf ("D:     %d %d %d \n", x, x + 1, x++);

    // QUARTA PARTE
    int y;
    int a = 5;
    y = (a++) / (a++);
    printf ("\n a = %d ", a);
    printf ("\n y = %d ", y);

    getchar ();
    return 0;
}/* */
