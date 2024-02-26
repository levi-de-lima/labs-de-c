/*  Levi Gurgel de Lima                      */
/*  Turma 3                                  */
/*  Exercício 8: Matrix                      */
/*                                           */
/*  Programa compilado com CodeBlocks 17.12  */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main ()
{
    //declaracao de variaveis
    //variaveis gerais
    float M [10][10];   //matriz
    int I, K;   //linhas e colunas da matriz
    int i, k;   //contadores de linhas e colunas
    float n;    //cada numero lido na matriz

    //variaveis item A
    int iMenor, kMenor; //posicao do menor numero
    float nMenor;   //menor numero

    //variaveis item B
    int iMaisNeg, kMaisNeg; //posicao do numero mais negativo
    float nMaisNeg; //numero mais negativo
    int c,  //contador de vizinhos negativos
        cMaisNeg=0;    //quant vizinhos negativos daquele que tem mais + atribuicao inicial

    //variaveis item C
    int p, q;   //contadores linhas e colunas da matriz na segunda vez que percorre
    float Dif=0,    //diferenca entre 2 numeros da matriz + atribuicao inicial
          MenorDif=0;   //menor diferenca entre 2 numeros da matriz
    int iMenorDif, kMenorDif;   //posicao do primeiro numero da menor diferenca
    int pMenorDif, qMenorDif;   //posicao do segundo numero da menor diferenca

    //variaveis item D
    float soma,    //soma dos modulos dos numeros das colunas
          norma=0;  //norma um
    int kNorma;    //coluna da norma um

    //arquivos
    FILE*entrada;
    FILE*saida;

    //ecrever mensagem inicial na tela
    printf ("Inicio do programa.\n");

    //abrir arquivos de entrada e saida
    entrada = fopen("entrada8.txt", "r");
    saida = fopen("Lab8_Levi_Gurgel_de_Lima.txt", "w");

    //escrever mensagem inicial no arquivo
    fprintf (saida, "A matrix estah em todo lugar.\n");
    fprintf (saida, "Eh tudo que nos rodeia. Mesmo agora, nesta sala.\n");
    fprintf (saida, "TAKE THE RED PILL!\n");
    fprintf (saida, "----------\n");

    //ler o numero de linhas e colunas da matriz
    fscanf (entrada,"%d %d ",&I, &K);
    //ler a matriz no arquivo e atribuir os valores a M
    for (i=0;i<I;i++)
    {
        for (k=0;k<K;k++)
        {
            fscanf (entrada, "%g ",&n);
            M[i][k]=n;
        }
    }
    //fechar arquivo de entrada
    fclose (entrada);
    //-------------------------------------------------------------------------------------------------
    //Item A
    //percorrer a matriz
    for (i=0;i<I;i++)
    {
        for (k=0;k<K;k++)
        {
            //se um numero eh menor que o minimo ate entao
            //ou se eh o primeiro numero lido, necessario para a primeira atribuicao
            if ((i==0&&k==0)||M[i][k]<nMenor)
            {
                //atribuicao do menor numero e da posicao deste as variaveis
                nMenor=M[i][k];
                iMenor=i;
                kMenor=k;
            }
        }
    }
    //escrever cabecalho do item A com os valores
    fprintf (saida, " (a)\n");
    fprintf (saida, "O menor elemento eh %g\n", nMenor);
    fprintf (saida, "Estah na posicao (%d, %d)\n", iMenor, kMenor);
    //-------------------------------------------------------------------------------------------------
    //Item B
    //percorrer a matriz
    for (i=0;i<I;i++)
    {
        for (k=0;k<K;k++)
        {
            //zero contador para cada numero
            c=0;
            //canto superior esquerdo
            if (i==0&&k==0)
            {
               //soma 1 as posicoes vizinhas
               if (M[0][1]<0)
                c++;
               if (M[1][0]<0)
                c++;
               if (M[1][1]<0)
                c++;
            }
            //canto superior direito
            if (i==0&&k==K-1)
            {
               //soma 1 as posicoes vizinhas
               if (M[1][K-1]<0)
                c++;
               if (M[0][K-2]<0)
                c++;
               if (M[1][K-2]<0)
                c++;
            }
            //canto inferior esquerdo
            if (i==I-1&&k==0)
            {
               //soma 1 as posicoes vizinhas
               if (M[I-2][0]<0)
                c++;
               if (M[I-1][1]<0)
                c++;
               if (M[I-2][1]<0)
                c++;
            }
            //canto inferior direito
            if (i==I-1&&k==K-1)
            {
               //soma 1 as posicoes vizinhas
               if (M[I-2][K-1]<0)
                c++;
               if (M[I-1][K-2]<0)
                c++;
               if (M[I-2][K-2]<0)
                c++;
            }
            //borda superior (sem os cantos)
            if (i==0&&k!=0&&k!=K-1)
            {
                //soma 1 as posicoes vizinhas
                if (M[0][k-1]<0)
                    c++;
                if (M[0][k+1]<0)
                    c++;
                if (M[1][k]<0)
                    c++;
                if (M[1][k+1]<0)
                    c++;
                if (M[1][k-1]<0)
                    c++;
            }
            //borda inferior (sem os cantos)
            if (i==I-1&&k!=0&&k!=K-1)
            {
                //soma 1 as posicoes vizinhas
                if (M[I-1][k-1]<0)
                    c++;
                if (M[I-1][k+1]<0)
                    c++;
                if (M[I-2][k]<0)
                    c++;
                if (M[I-2][k-1]<0)
                    c++;
                if (M[I-2][k+1]<0)
                    c++;
            }
            //borda esquerda (sem os cantos)
            if (k==0&&i!=0&&i!=I-1)
            {
                //soma 1 as posicoes vizinhas
                if (M[i-1][0]<0)
                    c++;
                if (M[i+1][0]<0)
                    c++;
                if (M[i][1]<0)
                    c++;
                if (M[i+1][1]<0)
                    c++;
                if (M[i-1][1]<0)
                    c++;
            }
            //borda direita (sem os cantos)
            if (k==K-1&&i!=0&&i!=K-1)
            {
                //soma 1 as posicoes vizinhas
                if (M[i-1][K-1]<0)
                    c++;
                if (M[i+1][K-1]<0)
                    c++;
                if (M[i][K-2]<0)
                    c++;
                if (M[i-1][K-2]<0)
                    c++;
                if (M[i+1][K-2]<0)
                    c++;
            }
            //meio da matriz
            if (i>0&&i<I-1&&k>0&&k<K-1)
            {
                //soma 1 as posicoes vizinhas
                if (M[i-1][k-1]<0)
                    c++;
                if (M[i-1][k]<0)
                    c++;
                if (M[i-1][k+1]<0)
                    c++;
                if (M[i][k-1]<0)
                    c++;
                if (M[i][k+1]<0)
                    c++;
                if (M[i+1][k-1]<0)
                    c++;
                if (M[i+1][k]<0)
                    c++;
                if (M[i+1][k+1]<0)
                    c++;
            }
            //se tiver mais vizinhos negativos que o maior ate entao
            if (c>=cMaisNeg)
            {
                //atribuicao do num com mais vizinhos negativos e sua quantidade e posicao
                nMaisNeg=M[i][k];
                cMaisNeg=c;
                iMaisNeg=i;
                kMaisNeg=k;
            }
        }
    }
    //escrever cabecalho do item B com os valores
    fprintf (saida, " (b)\n");
    fprintf (saida, "O elemento que contem mais vizinhos negativos eh %g\n", nMaisNeg);
    fprintf (saida, "Estah na posicao (%d, %d)\n", iMaisNeg, kMaisNeg);
    fprintf (saida, "Possui %d vizinhos negativos\n",cMaisNeg);
    //-------------------------------------------------------------------------------------------------
    //Item C
    //percorre a matriz
    for (i=0;i<I;i++)
    {
        for (k=0;k<K;k++)
        {
            //percorre a matriz de novo
            for (p=0;p<I;p++)
            {
                for (q=0;q<K;q++)
                {
                    //se os nao estao na mesma posicao
                    if (p!=i||q!=k)
                    {
                        //calcular a diferenca entre dois numeros na matriz, em modulo
                        Dif=fabs(M[p][q]-M[i][k]);
                        //se a diferenca for menor que a menor diferenca ate entao
                        //ou se for a diferenca entra o primeiro e o segundo termos, necessario para atribuicao incial
                        if ((i==0&&k==0&&p==0&&q==1)||(Dif<MenorDif))
                        {
                            //atribuicao da menor diferenca e das posicoes dos numeros envolvidos
                            MenorDif=Dif;
                            iMenorDif=i;
                            kMenorDif=k;
                            pMenorDif=p;
                            qMenorDif=q;
                        }
                    }
                }
            }
        }
    }
    //escrever cabecalho do item C com os valores
    fprintf (saida, " (c)\nO par de elementos com menor diferença de valor eh:\n");
    fprintf (saida, "%g na posicao (%d, %d)\n", M[iMenorDif][kMenorDif], iMenorDif, kMenorDif);
    fprintf (saida, "%g na posicao (%d, %d)\n", M[pMenorDif][qMenorDif], pMenorDif, qMenorDif);
    //-------------------------------------------------------------------------------------------------
    //Item D
    //percorre a matriz
    for (k=0;k<K;k++)
    {
        //zera a soma para cada numero
        soma=0;
        for (i=0;i<I;i++)
        {
            //ir somando os numeros da coluna, em modula
            soma=soma+fabs(M[i][k]);
        }
        //se a soma for maior que a maior soma ate entao
        if (soma>=norma)
        {
            //atribuicao dessa soma a norma e de sua coluna a coluna da norma
            norma=soma;
            kNorma=k;
        }
    }
    //escrever cabecalho do item D com os valores
    fprintf (saida, " (d)\nA \"norma um\" vale %g\n", norma);
    fprintf (saida, "Ocorre na coluna %d\n", kNorma);

    //fechar o arquivo de saida
    fclose (saida);

    //mensagem final na tela + pausa
    printf ("Fim do programa.\n");
    system ("pause");
    //finalizar
    return 0;
}
