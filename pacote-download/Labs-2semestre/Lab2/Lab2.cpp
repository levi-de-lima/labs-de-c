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

int M[21][21];
int contador=0;

int NMinMult(int L[], int C[], int i, int j)
{
    contador++;
    int k,
        kmin;
    int Minimo=0;
    int aux1,
        aux2;
    if(i==j)
    {
        return 0;
    }
    else
    {
        for(k=i;k<j;k++)
        {
            aux1=NMinMult(L,C,i,k);
            aux2=aux1+NMinMult(L,C,k+1,j)+L[i]*C[k]*C[j];
            if(aux2<=Minimo||Minimo==0)
            {
                Minimo=aux2;
                kmin=k;
            }
        }
        M[i][j]=kmin;
        return Minimo;
    }
}
void Caminho(int x, int y)
{
    if(x!=y)
    {
        Caminho(x,M[x][y]);

        //printf("%dx%d\n",x,y);

        Caminho(M[x][y]+1,y);

        if(y-x==1)
            printf("%dx%d\n",x,y);
        else if(M[x][y]==x)
            printf("%dx(%d-%d)\n",x,x+1,y);
        else if(M[x][y]==y-1)
            printf("(%d-%d)x%d\n",x,y-1,y);
        else printf("(%d-%d)x%(d-%d)\n",x,M[x][y],M[x][y]+1,y);
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

    printf("%d\n",p);
    printf("%d\n",contador);
    //printf("%d\n",M[1][nMat]);
    Caminho(1,nMat);

    fclose(entrada);
    fclose(saida);
}
