#include <stdio.h>
#include <stdlib.h>
int main ()
{
    char letra;
    printf ("Digite seu conceito (uma letra):");
    letra = getchar ();
    switch (letra)
    {
        case 'L': printf ("Nota maior ou igual a 9.5\n");
                  break;
        case 'M': printf ("Nota maior ou igual a 8.5\n");
                  break;
        case 'B': printf ("Nota maior ou igual a 7.5\n");
                  break;
        case 'R': printf ("Nota maior ou igual a 6.5\n");
                  break;
        default: printf ("Sugou!\n");
        system ("pause");
        return 0;
    }
}
