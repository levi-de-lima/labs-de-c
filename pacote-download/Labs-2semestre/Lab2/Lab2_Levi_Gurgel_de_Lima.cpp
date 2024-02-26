/*  Levi Gurgel de Lima                      */
/*  Turma 3                                  */
/*  Exercício 10: Vestibular                 */
/*                                           */
/*  Programa compilado com CodeBlocks 17.12  */
//bibliotecas usadas
#include <stdio.h>

//declaracao dos arquivos como variaveis globais pois serao utilizados nas tres funcoes do programa
FILE*entrada;
FILE*saida;

//outras variaveis globais
int M[21][21];      //matriz que recebe na posicao (x,y) a posicao do melhor corte de Ax,...,Ay
//Ex.: Se na multiplicacao de A1.A2.A3.A4 o melhor corte eh (A1.A2.A3).A4, M[1][4] recebe 3
int contador=0;     //conta a quantidade de vezes que a primeira funcao recursiva e chamada

//funcao que recebe dois vetores, com o numero de linhas e de colunas de cada matriz, alem de i e j que representam a multiplicacao Ai x ... x Aj
//a funcao devolve o numero minimo de multiplicacoes escalares na multiplicacao Ai x ... x Aj
int NMinMult(int L[], int C[], int i, int j)
{
    //soma 1 ao contador a cada chamada da funcao
    contador++;
    //declaracao de variaveis da funcao
    int k,          //posicao do corte. Ex.: i=1, j=4, k=3 -> (A1.A2.A3).A4
        kmin;       //posicao do melhor corte de Ai x ... x Aj
    int Minimo=0;   //numero minimo de multiplicacoes escalares
    int aux;        //variavel auxiliar que recebe cada valor do numero de multiplicacoes escalares e compara com o minimo
    if(i==j)        //se i igual a j retorna 0. Ex.: i=1, j=1 -> A1 -> retorna 0
        return 0;
    else            //se i diferente de j
    {
        //esse for percorrera a multiplicacao de matrizes de Ai x ... x Aj verificando cada corte
        //Ex.: (Ai x ... x Aj-1) x Aj, ... , Ai x (Ai+1 x ... x Aj)
        for(k=i;k<j;k++)
        {
            //a cada corte, o resultado do numero de multiplicacoe escalares e o resultado desse numero para cada subgrupo dividido pelo corte
            //mais o resultado da multiplicacao das matrizes reultantes da multiplicacao desses subgrupos
            //Ex.: (A1.A2.A3).A4.A5, o primeiro termo eh o minimo de 1 a 3, o segundo termo eh o minimo de 4 a 5
            //o terceiro termo eh a multiplicacao do resultado de 1-3 com o resultado de 4-5
            aux=NMinMult(L,C,i,k)+NMinMult(L,C,k+1,j)+L[i]*C[k]*C[j];
            //se o numero de multiplicacoes escalares recebidas em aux for o menor ate entao
            if(aux<=Minimo||Minimo==0)  //Minimo==0 e apenas uma condicao para a primeira entrada no if e primeira atribuicao de Minimo
            {
                Minimo=aux;     //Minimo recebe o menor resultado ate entao
                kmin=k;         //marca onde ocorreu o melhor corte
            }
        }
        M[i][j]=kmin;           //atribuicao a matriz conforme explicado anteriormente
        return Minimo;          //retorna o numero minimo de multiplicacoes escalares
    }
}
//funcao que recebe imprime na saida o caminho feito para alcancar o minimo
//essa funcao recebe x e y que representam Ax x ... x Ay e percorre a matriz para imprimir o caminho
void Caminho(int x, int y)
{
    //se x diferente de y, pois se forem iguais nao faz sentido e nem tem valor atribuido na matriz (apenas lixo)
    if(x!=y)
    {
        //chama a funcao da primeira matriz ate o melhor corte
        Caminho(x,M[x][y]);
        //chama a funcao do melhor corte + 1 ate a ultima matriz
        Caminho(M[x][y]+1,y);

        //se a multiplicacao for do tipo Ai x Ai+1
        if(y-x==1)
            fprintf(saida,"   %2d x %2d\n",x,y);                          //imprimir i x (i+1)
        //se o corte for no primeiro termo
        //Ex.: Ai x (Ai+1 x ... x Aj)
        else if(M[x][y]==x)
            fprintf(saida,"   %2d x %2d- %d\n",x,x+1,y);                  //imprimir i x (i+1)-j
        //se o corte for no ultimo termo
        //Ex.: (Ai x ... x Aj-1) x Aj
        else if(M[x][y]==y-1)
            fprintf(saida,"%2d-%2d x %d\n",x,y-1,y);                     //imprimir i-(j-1) x j
        //se o corte for "normal"
        //Ex.: (A1.A2.A3).(A4.A5)
        else fprintf(saida,"%2d-%2d x% d- %d\n",x,M[x][y],M[x][y]+1,y);  //imprimir 1-3 x 4-5, por exemplo
    }
}
int main()
{
    //abrir os arquivos de entrada e saida
    entrada=fopen("entrada2.txt","r");
    saida=fopen("Lab2_Levi_Gurgel_de_Lima.txt","w");

    //declaracao de variaveis
    int nMat;           //numero de matrizes
    int Linhas[21];     //vetor que recebe na posicao i a quantidade de linhas da i-esima matriz
    int Colunas[21];    //vetor que recebe na posicao j a quantidade de colunas da j-esima matriz
    int i, p;           //auxialeres para o contador do for e para receber o resultado da funcao NMinMult
    char lixo[100];     //string para receber as linhas inuteis da entrada

    //descarte das linhas inuteis da entrada
    fgets(lixo,100,entrada);
    fgets(lixo,100,entrada);
    fgets(lixo,100,entrada);
    fgets(lixo,100,entrada);
    fgets(lixo,100,entrada);

    //leitura do numero de matrizes
    fscanf(entrada,"%d ",&nMat);

    //descarte
    fgets(lixo,100,entrada);

    //leitura do numero de linhas e colunas das matrizes dadas no arquivo de entrada
    for(i=1;i<=nMat;i++)
        fscanf(entrada,"%d %d ",&Linhas[i],&Colunas[i]);


    //chama a funcao que devolve o numero minimo de multiplicacoes escalares
    //o resultado e armazenado em p
    p=NMinMult(Linhas,Colunas,1,nMat);

    //mensagem inicial no arquivo de saida
    fprintf(saida,"Quanto ao mais, irmãos, tudo o que é verdadeiro,\n");
    fprintf(saida,"tudo o que é honesto, tudo o que é justo, tudo o que é puro,\n");
    fprintf(saida,"tudo o que é amável, tudo o que é de boa fama, se há alguma virtude,\n");
    fprintf(saida,"e se há algum louvor, nisso pensai. Filipenses 4:8\n\n");

    //apresentacao dos resultados pedidos
    fprintf(saida,"Total de multiplicacoes escalares = %d\n\n",p);
    fprintf(saida,"Chamadas aa funcao: %d\n\n",contador);
    fprintf(saida,"Melhor ordem para realizar o produto:\n");

    //chama a funcao caminho que, ela propria, ja imprime o resultado na saida
    Caminho(1,nMat);

    //fecha os arquivos
    fclose(entrada);
    fclose(saida);

    //finalizar
    return 0;
}
