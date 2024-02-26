#include <stdio.h>
#include <stdlib.h>
typedef int vetor[5];
void EliminaNegativos(int V[],int tamanho)
{
    int i;
    for(i=0;i<tamanho;i++)
        if(V[i]<0)  //nao se usa *
            V[i]=0; //nao se usa *
}
int main()
{
    vetor A;
    int B[7];
    int quantA, quantB;

    for(int i=0;i<5;i++)
    {
        printf("vetor posicao %d\n",i);
        scanf("%d",&A[i]);
    }

    EliminaNegativos(A,quantA);
    //EliminaNegativos(B,quantB);

    for(int i=0;i<1;i++)
    {
        printf("%d ",A[i]);
    }

    system("pause");
    return 0;
}
