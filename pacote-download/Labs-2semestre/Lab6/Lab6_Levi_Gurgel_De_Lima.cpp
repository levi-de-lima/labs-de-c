/*  Levi Gurgel de Lima                      */
/*  Turma 3                                  */
/*  Exercício 6: Agenda (Heap)               */
/*                                           */
/*  Programa compilado com CodeBlocks 17.12  */
//inclui as bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//simplifica alguns nomes grandes que aparecem com frequencia
#define quant ApontaPraSS->QuantidadeDeElementos    //quantidade de elementos no vetor
#define NMax ApontaPraSS->QuantMax                  //quantidade maxima de elementos no vetor
//define o tipo boolean
#define boolean int
#define FALSE 0
#define TRUE 1
//simplifica a declaracao dessas structs
typedef struct elemento ElementoDaFila;
typedef struct SuperStruct SuperStruct;
//cada elemento do vetor
struct elemento
{
    int import;
    char descri[41];
};
//contem o vetor e outras informações que compoem a lista
struct SuperStruct
{
    int QuantidadeDeElementos;
    int QuantMax;
    ElementoDaFila* ApontaPraFila; //Ponteiro para o vetor, doravante chamado apenas de "vetor"
};
//verifica se a fila esta cheia
boolean FilaCheia(SuperStruct* ApontaPraSS)
{
    boolean b;
    //se a quantidade for igual ao maximo a booleana e verdadeira
    if(quant==NMax)
        b=TRUE;
    //senao, e falsa
    else b=FALSE;
    //retorna b
    return b;
}
//verifica se a fila esta vazia
boolean FilaVazia(SuperStruct* ApontaPraSS)
{
    boolean b;
    //se a quantidade de elementos for nula a booleana e verdadeira
    if(quant==0)
        b=TRUE;
    //senao, e falsa
    else b=FALSE;
    //retorna b
    return b;
}
//insere os elementos novos no vetor circular
void Insert(SuperStruct* ApontaPraSS, ElementoDaFila novo)
{
    //"aponta" para uma posicao do vetor
    int i;
    //struct auxiliar utilizada para a permutacao de elementos do vetor
    ElementoDaFila aux;
    //se a fila estiver vazia
    if(FilaVazia(ApontaPraSS))
    {
        //insere as informacoes do novo elemento na posicao inicial do vetor
        (ApontaPraSS->ApontaPraFila[1])=novo;
        quant++;
    }
    //se a fila nao esta cheia
    else if(!FilaCheia(ApontaPraSS))
    {
        //incrementa 1 a quantidade
        quant++;
        i=quant;
        //acrescenta o novo elemento na ultima posicao do vetor
        ApontaPraSS->ApontaPraFila[i]=novo;
        //se i for impar, ou seja, novo tem irmao
        //excetuando o caso em que ha apenas 1 elemento
        if(i>1 && i%2==1)
        {
            //se novo for maior q seu irmao, permutar
            //isso ocorre para que o maior irmao fique sempre a esquerda
            if((ApontaPraSS->ApontaPraFila[i]).import > (ApontaPraSS->ApontaPraFila[i-1]).import)
            {
                aux=(ApontaPraSS->ApontaPraFila[i]);
                (ApontaPraSS->ApontaPraFila[i])=(ApontaPraSS->ApontaPraFila[i-1]);
                (ApontaPraSS->ApontaPraFila[i-1])=aux;
                //mudar a posicao de i para a do irmao
                i=i-1;
            }
        }
        //enquanto novo nao for a raiz e este for maior que seu pai, permuta-los
        while(i!=1 && (ApontaPraSS->ApontaPraFila[i]).import>(ApontaPraSS->ApontaPraFila[i/2]).import)
        {
            aux=(ApontaPraSS->ApontaPraFila[i]);
            (ApontaPraSS->ApontaPraFila[i])=(ApontaPraSS->ApontaPraFila[i/2]);
            (ApontaPraSS->ApontaPraFila[i/2])=aux;
            //mudar a posicao de i para a do pai
            i=i/2;
        }
    }
}
//retorna o elemento de maior prioridade no vetor
ElementoDaFila Maximum(SuperStruct* ApontaPraSS)
{
    ElementoDaFila Maximo;
    //insere as informacoes da posicao inicial em Maximo
    Maximo=(ApontaPraSS->ApontaPraFila[1]);
    //retorna Maximo
    return Maximo;
}
//remove o elemento de maior prioridade da fila
void RemoveMax(SuperStruct* ApontaPraSS)
{
    //"aponta" para uma posicao do vetor
    int i;
    //struct auxiliar utilizada para a permutacao de elementos do vetor
    ElementoDaFila aux;
    if(!FilaVazia(ApontaPraSS))
    {
        //permutar a raiz com o ultimo elemento
        aux=(ApontaPraSS->ApontaPraFila[quant]);
        (ApontaPraSS->ApontaPraFila[quant])=(ApontaPraSS->ApontaPraFila[1]);
        (ApontaPraSS->ApontaPraFila[1])=aux;
        //para evitar bugs, atribuir zero ao elemento removido
        (ApontaPraSS->ApontaPraFila[quant]).import=0;
        //retirar 1 da quantidade
        quant--;
        //inicializar a posicao do elemento permutado
        i=1;
        //enquanto esse elemento tiver filho e for menor q algum filho, permutar com o maior filho
        while(2*i <= quant && ((ApontaPraSS->ApontaPraFila[i]).import < (ApontaPraSS->ApontaPraFila[2*i]).import || (ApontaPraSS->ApontaPraFila[i]).import < (ApontaPraSS->ApontaPraFila[2*i+1]).import))
        {
            //se o filho esquerdo é maior que o direito, permutar o esquerdo com o pai
            if((ApontaPraSS->ApontaPraFila[2*i]).import > (ApontaPraSS->ApontaPraFila[2*i+1]).import)
            {
                aux=(ApontaPraSS->ApontaPraFila[i]);
                (ApontaPraSS->ApontaPraFila[i])=(ApontaPraSS->ApontaPraFila[2*i]);
                (ApontaPraSS->ApontaPraFila[2*i])=aux;
                i=2*i;
            }
            //senao, permutar o direito com o pai
            else
            {
                aux=(ApontaPraSS->ApontaPraFila[i]);
                (ApontaPraSS->ApontaPraFila[i])=(ApontaPraSS->ApontaPraFila[2*i+1]);
                (ApontaPraSS->ApontaPraFila[2*i+1])=aux;
                i=2*i+1;
            }
        }
    }
}
//insere as informacoes iniciais na "SuperStruct" e aloca o espaco do vetor
void Inicializar(SuperStruct* ApontaPraSS, int QuantAgenda)
{
    //incializa a quantidade de elementos
    quant=0;
    //armazena a quantidade de elementos máxima na agenda
    ApontaPraSS->QuantMax=QuantAgenda;
    //faz a alocacao de memoria para o vetor
    ApontaPraSS->ApontaPraFila=(ElementoDaFila*)malloc((NMax+1)*sizeof(ElementoDaFila));
}
//da free no vetor
void Finalizar(SuperStruct* ApontaPraSS)
{
    //libera o espaco anteriormente alocado
    free(ApontaPraSS->ApontaPraFila);
}
int main()
{
    //declaracao dos arquivos de entrada e saida
    FILE*entrada;
    FILE*saida;

    //variável que armazena a quantidade de elementos máxima na agenda
    int QuantAgenda;

    char lixo[71];  //utilizada para ler os cabecalhos
    char tarefa[41];    //le a tarefa no arquivp de entrada

    ElementoDaFila Novo;    //novo elemento a ser inserido
    ElementoDaFila Maximo;          //elemento maximo
    SuperStruct StructComAsInfos;   //SuperStruct com as informacoes utilizada na main

    //abre os arquivos de entrada e saida
    entrada=fopen("entrada6.txt","r");
    saida=fopen("Lab6_Levi_Gurgel_de_Lima.txt","w");

    //le o cabecalho da entrada
    fgets(lixo,71,entrada);
    fgets(lixo,71,entrada);
    fgets(lixo,71,entrada);
    fgets(lixo,71,entrada);
    fgets(lixo,71,entrada);
    //le a quantidade maxima de elementos
    fscanf(entrada,"%d ",&QuantAgenda);
    fgets(lixo,71,entrada);
    fgets(lixo,71,entrada);
    fgets(lixo,71,entrada);

    //chama a inicializacao
    Inicializar(&StructComAsInfos,QuantAgenda);

    fprintf(saida,"\"No coração do prudente repousa a sabedoria;\n");
    fprintf(saida,"mas no coração dos tolos não é conhecida.\"\n");
    fprintf(saida,"Provérbios 14:33\n");
    fprintf(saida,"Lab 6: Agenda\n\n");

    fprintf(saida,"--------------------------------------------------\n");
    fprintf(saida,"RESPOSTAS DAS CONSULTAS\n");
    fprintf(saida,"--------------------------------------------------\n");

    //enquanto nao chegar ao fim
    do
    {
        //ler a tarefa
        fscanf(entrada,"%s",&tarefa);
        //se for uma tarefa nova
        if(strcmp(tarefa,"NOVA")==0)
        {
            //ler a importancia
            fscanf(entrada,"%d ",&Novo.import);
            fgets(Novo.descri,100,entrada);
            //se a fila nao esta cheia, inserir o elemento na fila
            if(!FilaCheia(&StructComAsInfos))
                Insert(&StructComAsInfos,Novo);
            //se a fila esta cheia, avisar na saida
            else fprintf(saida,"ERRO     Agenda cheia. Impossivel inserir.\n");
        }
        //se o usuario convocar a proxima tarefa
        else if(strcmp(tarefa,"PROXIMA")==0)
        {
            //se a fila nao esta vazia
            if(!FilaVazia(&StructComAsInfos))
            {
                //recebe as informacoes do elemento de maior importancia da fila
                Maximo=Maximum(&StructComAsInfos);
                //imprime na saida essas informacoes
                fprintf(saida,"%2d       %s",Maximo.import,Maximo.descri);
                //remove-o da fila
                RemoveMax(&StructComAsInfos);
            }
            //se a fila esta vazia, avisar
            else fprintf(saida,"AVISO    Nao ha tarefas na agenda\n");
        }
    }while(strcmp(tarefa,"FIM")!=0);

    fprintf(saida,"\n--------------------------------------------------\n");
    fprintf(saida,"FICA PARA O DIA SEGUINTE\n");
    fprintf(saida,"--------------------------------------------------\n");

    //imprime a lista restante, o que fica para o dia seguinte
    //se a fila nao estiver vazia
    if(!FilaVazia(&StructComAsInfos))
    {
        //percorre o vetor restante ate chegar ao fim
        while(!FilaVazia(&StructComAsInfos))
        {
            //recebe as informacoes do elemento de maior importancia da fila
            Maximo=Maximum(&StructComAsInfos);
            //imprime na saida essas informacoes
            fprintf(saida,"%2d       %s",Maximo.import,Maximo.descri);
            //remove-o da fila
            RemoveMax(&StructComAsInfos);
        }
    }
    //se a fila estiver vazia, avisar
    else fprintf(saida,"Agenda vazia! Nao restam tarefas para o dia seguinte.\n");

    //chama a finalizacao
    Finalizar(&StructComAsInfos);

    //fecha os arquivos de entrada e saida
    fclose(entrada);
    fclose(saida);

    //finalizar
    return 0;
}

