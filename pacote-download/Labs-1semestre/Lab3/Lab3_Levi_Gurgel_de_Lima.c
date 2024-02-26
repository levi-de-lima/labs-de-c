#include <stdio.h>
#include <stdlib.h>
int main ()
{
    int i,
        quilos,
        quant,
        libras;
    char letra;
    FILE * entrada;
    FILE * saida;

    entrada = fopen ("entrada3.txt", "r");
    saida = fopen ("resultado.txt", "w");

    fscanf (entrada, "%d", &quant);
    i=1;
    while (i <= quant)
    {
        fscanf (entrada, "%d", &quilos);
        fscanf (entrada, "%d", &libras);
        libras = quilos/2;
        fprintf (saida, "%d %c", libras, letra);
        i = i + 1;
    }
    fclose (entrada);
    fclose (saida);
    system ("pause");
    return 0;
}
