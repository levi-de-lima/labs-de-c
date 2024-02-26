#include <stdio.h>
#include <stdlib.h>

int main ()
{
    char letra;
    int i, n;

    //7 = som
    for (i=0; i<=225; i++)
    {
        letra = i;
        if (i%10 == 0)
            printf ("\n");
        if (i==13)
            printf ("  13:CR");
        else
        printf ("%4d: %c", letra, letra);
    }
    printf ("\n\n\n");

    printf ("Digite uma letra maiuscula: ");
    fflush (stdin);
    letra = getchar ();
    n = letra - 'A' + 1;
    printf ("Essa eh a %d-esima letra do alfabeto.", n);
    printf ("\n\n\n");

    printf ("Agora digite um numero: ");
    scanf ("%d", &n);
    letra = n + 'A' -1;
    printf ("A %d-esima letra do alfabeto eh: %c", n, letra);
    printf ("\n\n\n");

    printf ("Digite uma letra: ");
    fflush (stdin);
    letra = getchar ();
    if ('a' <= letra && letra <= 'z')
        printf ("Essa letra eh minuscula");
    else printf ("Essa letra eh MAIUSCULA");
    printf ("\n\n\n");

    system ("pause");
    return 0;
}
