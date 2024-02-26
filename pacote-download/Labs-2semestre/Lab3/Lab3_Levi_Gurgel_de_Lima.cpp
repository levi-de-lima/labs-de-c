/*  Levi Gurgel de Lima                      */
/*  Turma 3                                  */
/*  Exercício 3: Ordenação                   */
/*                                           */
/*  Programa compilado com CodeBlocks 17.12  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define TRUE 1
#define FALSE 0
#define boolean int

//define string de tamanho 50
typedef char String [51];

//declaracao dos arquivos de entrada e saida
FILE*entrada;
FILE*saida_bubble;
FILE*saida_merge;
FILE*saida_quick;

//declaracao de variaveis globais
int contador;   //contador do numero de comparacoes
int Num;        //tamanho do vetor de strings
boolean JaEntrou=FALSE;  //booleana que indica se o programa ja entrou em Merge alguma vez

//funcao que substitui o strcmp com o intuito de adicionar um contador do numero de comparacoes
int compara (const char * a, const char * b)
{
    contador ++;
    return strcmp (a, b);
}
//algoritmo BubbleSort
void BubbleSort(String V[],int n)
{
    //declaracao de variaveis
    int p;
    int i;
    char aux[51];
    //a cada iteraçã, fazer
    for(p=n-2;p>=0;p--)
        for(i=0;i<=p;i++)
            if(compara(V[i],V[i+1])>0)  //se nao estiver em ordem alfabetica
            {
                //permutar os elementos
                strcpy(aux,V[i]);
                strcpy(V[i],V[i+1]);
                strcpy(V[i+1],aux);
            }
}
//algoritmo MergeSort
//funcao Merge
/*Dado um vetor V e dadas duas posicoes ini e fim.
A metade da esquerda desse trecho ja´ esta´ ordenada e
a metade da direita  desse trecho ja´ esta´ ordenada.
Fazer intercalacao (merge) e obter V ordenado.*/
void Merge (String V[], int ini, int fim)
{
   static String* T;
   if(!JaEntrou)
   {
       T=(String*)malloc(Num*sizeof(String));
       JaEntrou=TRUE;
   }
   int med,
       i,       //percorre T
       j,       //percorre lado esquerdo de V
       k;       //percorre lado direito de V

   med = (ini+fim)/2;   //mesmo arredondamento feito ao chamar MergeSort
   j = ini;
   k = med+1;
   i = ini;
   //percorrer selecionando os menores
   while (j <= med && k <= fim)
   {
      if (compara(V[j],V[k])<=0)
      {
         strcpy(T[i],V[j]);
         j++;
      }
      else
      {
         strcpy(T[i],V[k]);
         k++;
      }
      i++;
   }
   //se sobrou algo `a esquerda, copiar para T
   while(j <= med)
   {
      strcpy(T[i],V[j]);
      i++;
      j++;
   }
   //se sobrou algo `a direita, copiar para T
   while(k<=fim)
   {
      strcpy(T[i],V[k]);
      i++;
      k++;
   }
   // V recebe T
   for(i=ini; i<=fim; i++)
        strcpy(V[i],T[i]);
}
//MergeSort propriamente dito
void MergeSort(String V[],int ini,int fim)
{
    int med;
    if(ini<fim)
    {
        med=(ini+fim)/2;        //dividir ao meio
        MergeSort(V,ini,med);   // ordenar lado esquerdo
        MergeSort(V,med+1,fim); // ordenar lado direito
        Merge(V,ini,fim);       // mesclar as duas metades
    }
}
//algoritmo QuickSort
//funcao Partition
/*Dado um vetor V com elementos em qualquer ordem,
escolher um elemento para ser pivo^
e então dividir os elementos de V em duas partes:
`a esquerda: menores que o pivo
`a direita:  maiores ou iguais ao pivo*/
int Partition (String V[], int ini, int fim)
{
   String pivo, aux;
   int esq, dir;

   strcpy(pivo,V[ini]); // neste exemplo, o pivo é o primeiro da esquerda
   esq  = ini + 1;
   dir  = fim;
   do
   {
      // percorrer da esquerda para a direita. encontrar alguem >= pivo
      while (esq < fim && compara(V[esq],pivo)<0)
         esq++;
      // percorrer da direita para a esquerda. encontrar alguem < pivo
      while (ini < dir && compara(pivo,V[dir])<=0)
         dir--;
      // se achou um `a esquerda e outro `a direita
      if(esq < dir)
      {
         // permutar
         strcpy(aux,V[esq]);
         strcpy(V[esq],V[dir]);
         strcpy(V[dir],aux);
      }
      // caso contrario, terminara´ a repeticao
   }while (esq < dir);

   // trocar o pivo com o elemento que "divide" os subvetores
   strcpy(V[ini],V[dir]);
   strcpy(V[dir],pivo);

   // retornar a posição da "divisa"
   return dir;
}
//QuickSort propriamente dito
void QuickSort (String V[], int ini, int fim)
{
   int p;       //posicao do pivo
   if (ini < fim)
   {
      p = Partition (V, ini, fim);
      QuickSort     (V, ini, p-1);
      QuickSort     (V, p+1, fim);
   }
}
int main()
{
    //variaveis que marcam o tempo gasto por cada algoritmo
    clock_t inicio,
            fim;
    float   delta_t;

    //auxiliar
    int i;
    //vetor de strings que será passado para as funcoes
    String* Vet;

    //abertura dos arquivos
    entrada=fopen("entrada3.txt","r");
    saida_bubble=fopen("Lab3_Levi_Gurgel_de_Lima_bubble.txt","w");
    saida_merge=fopen("Lab3_Levi_Gurgel_de_Lima_merge.txt","w");
    saida_quick=fopen("Lab3_Levi_Gurgel_de_Lima_quick.txt","w");

    //leitura do tamanho do vetor de strings
    fscanf(entrada,"%d ",&Num);

    //alocacao de memoria do vetor com o tamanho lido anteriormente
    Vet=(String*)malloc(Num*sizeof(String));

    //leitura das strings e alocacao no vetor
    for(i=0;i<Num;i++)
        fscanf(entrada,"%s ",&Vet[i]);

    //zera o contador ao entrar na funcao
    contador=0;

    //chama a funcao BubbleSort e conta o tempo gasto
    inicio = clock();
    BubbleSort(Vet,Num);
    fim    = clock();

    //calcula o tempo gatso
    delta_t = (fim - inicio) / (float) CLOCKS_PER_SEC;
    //imprime no arquivo de saida as informacoes necessarias
    fprintf(saida_bubble,"Algoritmo Bubble-Sort:\n\n");
    fprintf(saida_bubble,"Tamanho da entrada: %d\n", Num);
    fprintf(saida_bubble,"Comparacoes feitas: %d\n", contador);
    fprintf(saida_bubble,"Tempo de execucao : %.2f segundos\n\n", delta_t);
    fprintf(saida_bubble,"--------------------------------------------------\n");

    //imprimir os vetores em ordem alfabetica no arquivo de saida
    for(i=0;i<Num;i++)
        fprintf(saida_bubble,"%s \n",Vet[i]);

    //zera o contador ao entrar na funcao
    contador=0;

    //chama a funcao BubbleSort e conta o tempo gasto
    inicio = clock();
    MergeSort(Vet,0,Num-1);
    fim    = clock();

    //calcula o tempo gasto
    delta_t = (fim - inicio) / (float) CLOCKS_PER_SEC;
    fprintf(saida_merge,"Algoritmo Merge-Sort:\n\n");
    fprintf(saida_merge,"Tamanho da entrada: %d\n", Num);
    fprintf(saida_merge,"Comparacoes feitas: %d\n", contador);
    fprintf(saida_merge,"Tempo de execucao : %.2f segundos\n\n", delta_t);
    fprintf(saida_merge,"--------------------------------------------------\n");

    //imprimir os vetores em ordem alfabetica no arquivo de saida
    for(i=0;i<Num;i++)
        fprintf(saida_merge,"%s \n",Vet[i]);

    //zera o contador ao entrar na funcao
    contador=0;

    //chama a funcao BubbleSort e conta o tempo gasto
    inicio = clock();
    QuickSort(Vet,0,Num-1);
    fim    = clock();

    //calcula o tempo gasto
    delta_t = (fim - inicio) / (float) CLOCKS_PER_SEC;
    fprintf(saida_quick,"Algoritmo Quick-Sort:\n\n");
    fprintf(saida_quick,"Tamanho da entrada: %d\n", Num);
    fprintf(saida_quick,"Comparacoes feitas: %d\n", contador);
    fprintf(saida_quick,"Tempo de execucao : %.2f segundos\n\n", delta_t);
    fprintf(saida_quick,"--------------------------------------------------\n");

    //imprimir os vetores em ordem alfabetica no arquivo de saida
    for(i=0;i<Num;i++)
        fprintf(saida_quick,"%s \n",Vet[i]);

    //liberar espaco da memoria alocada para o vetor
    free(Vet);
    //fechar os arquivos
    fclose(entrada);
    fclose(saida_bubble);
    fclose(saida_merge);
    fclose(saida_quick);

    //finalizar
    return 0;
}
