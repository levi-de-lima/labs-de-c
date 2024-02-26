/*  Levi Gurgel de Lima                      */
/*  Turma 3                                  */
/*  Exercício 10: Vestibular                 */
/*                                           */
/*  Programa compilado com CodeBlocks 17.12  */
#include <stdio.h>
#include <stdlib.h>
int x,y;

FILE*entrada;
FILE*saida;

int NMinMult(int L[], int C[], int i, int j)
{
    int k;
    int Minimo=0,
        Minimo2=0;
    int aux,
        aux2;
    if(i==j)
        return 0;
    else
    {
        for(k=i;k<j;k++)
        {
            aux2=NMinMult(L,C,i,k);
            if(aux2<=Minimo2||Minimo2==0)
                Minimo2=aux2;
            aux=Minimo2+NMinMult(L,C,k+1,j)+L[i]*C[k]*C[j];
            if(aux<=Minimo||Minimo==0)
                Minimo=aux;
        }
        return Minimo;
    }
}
int main()
{
    entrada=fopen("entrada2.txt","r");
    saida=fopen("Lab2_Levi_Gurgel_de_Lima.txt","w");

    int nMat;
    int Linhas[20];
    int Colunas[20];
    int i;
    int p;

    fscanf(entrada,"%d ",&nMat);
    for(i=1;i<=nMat;i++)
    {
       fscanf(entrada,"%d %d ",&Linhas[i],&Colunas[i]);
    }

    p=NMinMult(Linhas,Colunas,1,nMat);

    printf("%d",p);

    fclose(entrada);
    fclose(saida);
}
