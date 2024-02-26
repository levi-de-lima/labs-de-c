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

typedef char String [51];

FILE*entrada;
FILE*saida_bubble;
FILE*saida_merge;
FILE*saida_quick;

int contador;
int Num;
boolean buleana=FALSE;

int compara (const char * a, const char * b)
{
    contador ++;
    return strcmp (a, b);
}
void BubbleSort(String V[],int n)
{
    int p;
    int i;
    char aux[51];
    for(p=n-2;p>=0;p--)
        for(i=0;i<=p;i++)
            if(compara(V[i],V[i+1])>0)
            {
                strcpy(aux,V[i]);
                strcpy(V[i],V[i+1]);
                strcpy(V[i+1],aux);
            }
}
void Merge (String V[], int ini, int fim)
{
   String* T;
   T=(String*)malloc(Num*sizeof(String));
   int med,
       i,
       j,
       k;

   med = (ini+fim)/2;
   j = ini;
   k = med+1;
   i = ini;
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
   while(j <= med)
   {
      strcpy(T[i],V[j]);
      i++;
      j++;
   }
   while(k<=fim)
   {
      strcpy(T[i],V[k]);
      i++;
      k++;
   }
   for(i=ini; i<=fim; i++)
        strcpy(V[i],T[i]);

    free(T);
}
void MergeSort(String V[],int ini,int fim)
{
    int med;
    if(ini<fim)
    {
        med=(ini+fim)/2;

        MergeSort(V,ini,med);
        MergeSort(V,med+1,fim);
        Merge(V,ini,fim);
    }
}
void MergeStatic(String V[], int ini, int fim)
{
   static String* T;
   if(!buleana)
   {
       T=(String*)malloc(Num*sizeof(String));
       buleana=TRUE;
   }
   int med,
       i,
       j,
       k;

   med = (ini+fim)/2;
   j = ini;
   k = med+1;
   i = ini;
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
   while(j <= med)
   {
      strcpy(T[i],V[j]);
      i++;
      j++;
   }
   while(k<=fim)
   {
      strcpy(T[i],V[k]);
      i++;
      k++;
   }
   for(i=ini; i<=fim; i++)
        strcpy(V[i],T[i]);
}
void MergeSortStatic(String V[],int ini,int fim)
{
    int med;
    if(ini<fim)
    {
        med=(ini+fim)/2;

        MergeSortStatic(V,ini,med);
        MergeSortStatic(V,med+1,fim);
        MergeStatic(V,ini,fim);
    }
}
int Partition (String V[], int ini, int fim)
{
   String pivo, aux;
   int esq, dir;

   strcpy(pivo,V[ini]);
   esq  = ini + 1;
   dir  = fim;
   do
   {
      while (esq < fim && compara(V[esq],pivo)<0)
         esq++;
      while (ini < dir && compara(pivo,V[dir])<=0)
         dir--;
      if(esq < dir)
      {
         strcpy(aux,V[esq]);
         strcpy(V[esq],V[dir]);
         strcpy(V[dir],aux);
      }
   }while (esq < dir);

   strcpy(V[ini],V[dir]);
   strcpy(V[dir],pivo);

   return dir;
}
void QuickSort (String V[], int ini, int fim)
{
   int p;
   if (ini < fim)
   {
      p = Partition (V, ini, fim);
      QuickSort     (V, ini, p-1);
      QuickSort     (V, p+1, fim);
   }
}
int main()
{
    clock_t inicio,
            fim;
    float   delta_t;

    int i,j;
    String* Vet;

    entrada=fopen("entrada3.txt","r");
    saida_bubble=fopen("Lab3_Levi_Gurgel_de_Lima_bubble.txt","w");
    saida_merge=fopen("Lab3_Levi_Gurgel_de_Lima_merge.txt","w");
    saida_quick=fopen("Lab3_Levi_Gurgel_de_Lima_quick.txt","w");

    fscanf(entrada,"%d ",&Num);

    Vet=(String*)malloc(Num*sizeof(String));

    for(i=0;i<Num;i++)
        fscanf(entrada,"%s ",&Vet[i]);

    /*contador=0;

    inicio = clock();
    BubbleSort(Vet,Num);
    fim    = clock();

    delta_t = (fim - inicio) / (float) CLOCKS_PER_SEC;
    fprintf(saida_bubble,"Algoritmo Bubble-Sort:\n\n");
    fprintf(saida_bubble,"Tamanho da entrada: %d\n", Num);
    fprintf(saida_bubble,"Comparacoes feitas: %d\n", contador);
    fprintf(saida_bubble,"Tempo de execucao : %.2f segundos\n\n", delta_t);

    fprintf(saida_bubble,"--------------------------------------------------\n");

    for(i=0;i<Num;i++)
        fprintf(saida_bubble,"%s \n",Vet[i]);

    contador=0;

    inicio = clock();
    MergeSort(Vet,0,Num-1);
    fim    = clock();

    delta_t = (fim - inicio) / (float) CLOCKS_PER_SEC;
    fprintf(saida_merge,"Algoritmo Merge-Sort:\n\n");
    fprintf(saida_merge,"Tamanho da entrada: %d\n", Num);
    fprintf(saida_merge,"Comparacoes feitas: %d\n", contador);
    fprintf(saida_merge,"Tempo de execucao : %.2f segundos\n\n", delta_t);

    fprintf(saida_merge,"--------------------------------------------------\n");

    for(i=0;i<Num;i++)
        fprintf(saida_merge,"%s \n",Vet[i]);*/

    contador=0;

    inicio = clock();
    MergeSortStatic(Vet,0,Num-1);
    fim    = clock();

    delta_t = (fim - inicio) / (float) CLOCKS_PER_SEC;
    fprintf(saida_merge,"Algoritmo Merge-Sort:\n\n");
    fprintf(saida_merge,"Tamanho da entrada: %d\n", Num);
    fprintf(saida_merge,"Comparacoes feitas: %d\n", contador);
    fprintf(saida_merge,"Tempo de execucao : %.2f segundos\n\n", delta_t);

    fprintf(saida_merge,"--------------------------------------------------\n");

    for(i=0;i<Num;i++)
        fprintf(saida_merge,"%s \n",Vet[i]);

   /* contador=0;

    inicio = clock();
    QuickSort(Vet,0,Num-1);
    fim    = clock();

    delta_t = (fim - inicio) / (float) CLOCKS_PER_SEC;
    fprintf(saida_quick,"Algoritmo Quick-Sort:\n\n");
    fprintf(saida_quick,"Tamanho da entrada: %d\n", Num);
    fprintf(saida_quick,"Comparacoes feitas: %d\n", contador);
    fprintf(saida_quick,"Tempo de execucao : %.2f segundos\n\n", delta_t);

    fprintf(saida_quick,"--------------------------------------------------\n");

    for(i=0;i<Num;i++)
        fprintf(saida_quick,"%s \n",Vet[i]);*/

    fclose(entrada);
    fclose(saida_bubble);
    fclose(saida_merge);
    fclose(saida_quick);

    return 0;
}
