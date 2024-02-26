#include <stdio.h>
int main ()
{
    int i;
    int quant;
    int di, mi, ai,
        df, mf, af;
    FILE * entrada;
    FILE * saida;

    entrada = fopen ("entrada4.txt", "r");
    saida = fopen ("saida4.txt", "w");

    fscanf (entrada, "%d", &quant);
    for (i = 0; i<quant; i++)
    {
    fscanf (entrada, "%d %d %d    %d %d %d ", &di, &mi, &ai, &df, &mf, &af);
    fprintf (saida, "%d %d %d    %d %d %d\n", di, mi, ai, df, mf, af);
    }
    fclose (entrada);
    fclose (saida);
    return 0;
}
