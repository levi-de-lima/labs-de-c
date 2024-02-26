/*  Levi Gurgel de Lima                      */
/*  Turma 3                                  */
/*  Exercício 4: Agenda                      */
/*                                           */
/*  Programa compilado com CodeBlocks 17.12  */
//inclui as bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//simplifica alguns nomes grandes que aparecem com frequencia
#define ini ApontaPraSS->PosicaoDoInicio    //inicio do vetor circular
#define fim ApontaPraSS->PosicaoDoFim       //fim do vetor circular
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
    int PosicaoDoInicio;
    int PosicaoDoFim;
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
    //posicao do meio do vetor
    int Meio;
    //"aponta" para uma posicao do vetor
    int i;
    //se a fila estiver vazia
    if(FilaVazia(ApontaPraSS))
    {
        //insere as informacoes do novo elemento na posicao inicial do vetor
        fim=ini;
        (ApontaPraSS->ApontaPraFila[ini]).import=novo.import;
        strcpy((ApontaPraSS->ApontaPraFila[ini]).descri,novo.descri);
        ApontaPraSS->QuantidadeDeElementos++;
    }
    //se a fila nao esta cheia
    else if(!FilaCheia(ApontaPraSS))
    {
        //define a posicao do meio
        Meio=(ini + quant/2)%NMax;
        //se o novo elemento localizar-se depois do meio ou no meio
        if(novo.import <= (ApontaPraSS->ApontaPraFila[Meio]).import)
        {
            //i comeca no fim
            i=fim;
            //enquanto nao for encontrado um elemento cuja importancia e maior ou igual a do novo elemento
            while((ApontaPraSS->ApontaPraFila[i%NMax]).import < novo.import)
            {
                //mover o elemento da posicao i para a proxima posicao (fazer o shift)
                (ApontaPraSS->ApontaPraFila[(i+1)%NMax]).import=(ApontaPraSS->ApontaPraFila[i%NMax]).import;
                strcpy((ApontaPraSS->ApontaPraFila[(i+1)%NMax]).descri,(ApontaPraSS->ApontaPraFila[i%NMax]).descri);
                //ir para o elemento anterior
                i=(i-1+NMax)%NMax;
            }
            //apos feito o shift, relocalizar a posicao final
            fim=(fim+1)%NMax;
            //inserir o novo elemento
            (ApontaPraSS->ApontaPraFila[(i+1)%NMax]).import=novo.import;
            strcpy((ApontaPraSS->ApontaPraFila[(i+1)%NMax]).descri,novo.descri);
        }
        //se o novo elemento localizar-se antes do meio
        else
        {
            //i comeca no inicio
            i=ini;
             //enquanto nao for encontrado um elemento cuja importancia e menor que a do novo elemento
            while((ApontaPraSS->ApontaPraFila[i%NMax]).import >= novo.import)
            {
                //mover o elemento da posicao i para a posicao anterior (fazer o shift)
                (ApontaPraSS->ApontaPraFila[(i-1+NMax)%NMax]).import=(ApontaPraSS->ApontaPraFila[i%NMax]).import;
                strcpy((ApontaPraSS->ApontaPraFila[(i-1+NMax)%NMax]).descri,(ApontaPraSS->ApontaPraFila[i%NMax]).descri);
                //ir para o proximo elemento
                i=(i+1)%NMax;
            }
            //apos feito o shift, relocalizar a posicao inicial
            ini=(ini-1+NMax)%NMax;
            //inserir o novo elemento
            (ApontaPraSS->ApontaPraFila[(i-1+NMax)%NMax]).import=novo.import;
            strcpy((ApontaPraSS->ApontaPraFila[(i-1+NMax)%NMax]).descri,novo.descri);
        }
        //adicionar 1 na quantidade de elementos presentes no vetor
        quant++;
    }
}
//retorna o elemento de maior prioridade no vetor
ElementoDaFila Maximum(SuperStruct* ApontaPraSS)
{
    ElementoDaFila Maximo;
    //insere as informacoes da posicao inicial em Maximo
    Maximo.import=(ApontaPraSS->ApontaPraFila[ApontaPraSS->PosicaoDoInicio]).import;
    strcpy(Maximo.descri,(ApontaPraSS->ApontaPraFila[ApontaPraSS->PosicaoDoInicio]).descri);
    //retorna Maximo
    return Maximo;
}
//remove o elemento de maior prioridade da fila
void RemoveMax(SuperStruct* ApontaPraSS)
{
    //consiste em avançar uma posicao com a variavel ini
    ini=(ini+1)%NMax;
    //subtrai 1 na quantidade
    quant--;
    //se o vetor que sobra nao tiver elementos, deve-se mover tambem a posicao final
    if(quant==0)
        fim=(fim+1)%NMax;
}
//insere as informacoes iniciais na "SuperStruct" e aloca o espaco do vetor
int Inicializar(SuperStruct* ApontaPraSS)
{
    ApontaPraSS->QuantidadeDeElementos=0;
    ApontaPraSS->PosicaoDoInicio=0;
    ApontaPraSS->PosicaoDoFim=0;
    ApontaPraSS->ApontaPraFila=(ElementoDaFila*)malloc(ApontaPraSS->QuantMax*sizeof(ElementoDaFila));
}
//da free no vetor
void Finalizar(SuperStruct* ApontaPraSS)
{
    free(ApontaPraSS->ApontaPraFila);
}
int main()
{
    //declaracao dos arquivos de entrada e saida
    FILE*entrada;
    FILE*saida;

    char lixo[71];  //utilizada para ler os cabecalhos
    char tarefa[41];    //le a tarefa no arquivp de entrada

    //auxiliar para imprimir a lista que sobra
    int k;

    ElementoDaFila Novo;    //novo elemento a ser inserido
    ElementoDaFila Maximo;          //elemento maximo
    SuperStruct StructComAsInfos;   //SuperStruct com as informacoes utilizada na main

    //abre os arquivos de entrada e saida
    entrada=fopen("entrada4.txt","r");
    saida=fopen("Lab4_Levi_Gurgel_de_Lima.txt","w");

    //le o cabecalho da entrada
    fgets(lixo,71,entrada);
    fgets(lixo,71,entrada);
    fgets(lixo,71,entrada);
    fgets(lixo,71,entrada);
    fgets(lixo,71,entrada);
    //le a quantidade maxima de elementos
    fscanf(entrada,"%d ",&StructComAsInfos.QuantMax);
    fgets(lixo,71,entrada);
    fgets(lixo,71,entrada);
    fgets(lixo,71,entrada);

    //chama a inicializacao
    Inicializar(&StructComAsInfos);

    fprintf(saida,"\"Em todo tempo ama o amigo,\n");
    fprintf(saida,"mas na angustia nasce o irmão\"\n");
    fprintf(saida,"Provérbios 17:17\n");
    fprintf(saida,"Lab 4: Agenda\n\n");

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
    //inicializa k no inicio
    k=StructComAsInfos.PosicaoDoInicio;
    //se a fila nao estiver vazia
    if(!FilaVazia(&StructComAsInfos))
    {
        //percorre o vetor restante ate chegar ao fim
        while((k-1+StructComAsInfos.QuantMax)%StructComAsInfos.QuantMax!=StructComAsInfos.PosicaoDoFim)
        {
            //imprime as informacoes na saida
            fprintf(saida,"%2d      %s",(saida,StructComAsInfos.ApontaPraFila[k]).import,(StructComAsInfos.ApontaPraFila[k]).descri);
            //vai para a proxima posicao
            k=(k+1)%StructComAsInfos.QuantMax;
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
