#include <stdio.h>
#include <stdlib.h>
int main ()
{
    int i,
        quant,
        TF,
        TC;
    FILE * entrada;
    FILE * saida;

    entrada = fopen ("dados.txt", "r");
    saida = fopen ("result.txt", "w");

    printf ("Inicio do programa. \n\n");
    //printf ("Qual a quantidade de elementos? ");
    fscanf (entrada, "%d", &quant);
    printf ("\n");
    i=1;
    while (i <= quant)
    {
        //printf("Digite em Farenheitt: ");
        fscanf (entrada, "%d", &TF);
        TC = 5 * (TF-32) / 9;
        //TC = (5/9) * (TF-32);
        fprintf (saida, "%4d F equivale a %4d Celsius.\n", TF, TC);
        i = i + 1;
    }
    fclose (entrada);
    fclose (saida);
    printf ("\nFIM do programa.\n\n");
    system ("pause");
    return 0;
}
