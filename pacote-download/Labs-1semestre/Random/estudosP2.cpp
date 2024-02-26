#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define boolean int
int main ()
{
    int A[100][100];
    int B[100][100];
    int C[100][100];
    int n, m;
    int p, q;
    int S;

    FILE*entrada;
    FILE*saida;

    entrada=fopen("entrada!.txt","r");
    saida=fopen("saida!.txt","w");

    fscanf(entrada,"%d %d ",&n, &m);

    for(int i=0;i<n;i++)
        for(int k=0;k<m;k++)
            fscanf(entrada,"%d ",&B[i][k]);

    fscanf(entrada,"%d %d ",&p, &q);

    for(int i=0;i<p;i++)
        for(int k=0;k<q;k++)
            fscanf(entrada,"%d ",&C[i][k]);

    for(int i=0;i<n;i++)
        for(int k=0;k<q;k++)
        {
            S=0;
            for(int w=0;w<m;w++)
                S=S+(B[i][w]*C[w][k]);
            A[i][k]=S;
        }

    for(int i=0;i<n;i++)
    {
        fprintf(saida,"\n");
        for(int k=0;k<q;k++)
            fprintf(saida,"%d ",A[i][k]);
    }

    fclose(entrada);
    fclose(saida);
    system("pause");
    return 0;
}
