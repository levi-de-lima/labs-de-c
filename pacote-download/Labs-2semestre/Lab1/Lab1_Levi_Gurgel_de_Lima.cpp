#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//definindo "noh" como a struct abaixo
typedef struct voo noh;
struct voo
{
    char message[100];  //mensagens enviadas pelo aviao e peloaeroporto
    int flight;         //numero de voo
    char from[100];     //de onde vem o aviao
    noh*prox=NULL;      //ponteiro para o proximo elemento da lista
};
int main()
{
    //declaracao de arquivos
    FILE*entrada;
    FILE*saida;

    //declaracao de ponteiros
    noh *inicio,    //marca o incio da lista
        *ult,         //marca o ultimo elemento da lista
        *prim,         //marca o primeiro elemento da lista
        *ant,       //percorrem a lista procurando o voo de urgencia
        *dep,
        *aux;       //marca o ultimo da fila dos urgentes

    char lixo[100]; //para "descartar" as primeiras lihas da entrada

    //abertura dos arquivos
    entrada=fopen("entrada1.txt","r");
    saida=fopen("Lab1_Levi_Gurgel_de_Lima.txt","w");

    //descarte das primeiras lihas da entrada
    fgets(lixo,100,entrada);
    fgets(lixo,100,entrada);
    fgets(lixo,100,entrada);
    fgets(lixo,100,entrada);
    fgets(lixo,100,entrada);
    fgets(lixo,100,entrada);
    fgets(lixo,100,entrada);

    //mensagem inicial no arquivo de saida
    fprintf(saida,"O Senhor é o meu pastor; nada me faltará.\n");
    fprintf(saida,"Ele me faz repousar em pastos verdejantes.\n");
    fprintf(saida,"Leva-me para junto das águas de descanso; refrigera-me a alma.\n");
    fprintf(saida,"Guia-me pelas veredas da justiça por amor do seu nome. Salmos 23:1-3\n");
    fprintf(saida,"=========================================\n");
    fprintf(saida,"FLIGHT FROM\n\n");

    //alocacao de memoria para o noh inicial
    inicio=(noh*)malloc(sizeof(noh));
    //ultimo elemento e o proprio inicio
    ult=inicio;

    //inicializacao
    aux=inicio;

    //leitura das informacoes de "INICIO" na entrada e alocacao no noh
    fscanf(entrada,"%s ",&ult->message);
    fscanf(entrada,"%d ",&ult->flight);
    fgets(ult->from,100,entrada);

    //enquanto nao chegar ao fim do arquivo
    while(strcmp(ult->message,"FIM")!=0)
    {
        //inicializacao
        ant=inicio;
        dep=inicio->prox;

        //cria os elementos da lista
        ult->prox=(noh*)malloc(sizeof(noh));
        prim=inicio->prox;

        //leitura das informacoes na entrada e alocacao no noh
        fscanf(entrada,"%s ",&ult->prox->message);
        fscanf(entrada,"%d ",&ult->prox->flight);
        fgets(ult->prox->from,100,entrada);

        //se a proxima liha da entrada for "pista_liberada"
        if(strcmp(ult->prox->message,"pista_liberada")==0)
        {
            //se nao houver avioes na fila
            if(strcmp(prim->message,"pista_liberada")==0)
            {
                //informar que nao ha avioes e retirar o noh da lista
                ult->prox=NULL;
                fprintf(saida,"0000   Nenhum aviao pousando\n");
                //caso haja um unico voo pedindo urgencia e este seja liberado
                if(aux==prim)
                    aux=inicio;
            }
            //se houver apenas um aviao na fila
            else if(strcmp(prim->prox->message,"pista_liberada")==0)
            {
                //retirar o noh da lista
                ult->prox=NULL;
                //retirar o primeiro da fila da lista
                inicio->prox=inicio->prox->prox;
                //imprimir os dados do primeiro na saida
                fprintf(saida,"%04d   %s",prim->flight,prim->from);
                //"reiniciar" o ponteiro que aponta para o ultimo
                ult=inicio;
                //caso haja um unico voo pedindo urgencia e este seja liberado
                if(aux==prim)
                    aux=inicio;
            }
            //se houver mais de um aviao na fila
            else
            {
                //retirar o noh da lista
                ult->prox=NULL;
                //retirar o primeiro da fila da lista
                inicio->prox=inicio->prox->prox;
                prim->prox=NULL;
                //imprimir os dados do primeiro na saida
                fprintf(saida,"%04d   %s",prim->flight,prim->from);
                //caso haja um unico voo pedindo urgencia e este seja liberado
                if(aux==prim)
                    aux=inicio;
            }
        }
        //se a proxima liha da entrada for "URGENCIA"
        else if (strcmp(ult->prox->message,"URGENCIA")==0)
        {
            //se nao houver avioes na fila
            if(strcmp(prim->message,"URGENCIA")==0)
            {
                //retirar o noh da lista
                ult->prox=NULL;
            }
            //se houver apenas um aviao na fila
            else if(strcmp(prim->prox->message,"URGENCIA")==0)
            {
                //retirar o noh de "URGENCIA" da lista
                ult->prox=NULL;
            }
            //se houver mais de um aviao na fila
            else
            {
                //percorrer a lista ate achar o voo que pediu urgencia
                while(dep->flight!=ult->prox->flight)
                {
                    ant=ant->prox;
                    dep=dep->prox;
                }
                //retirar o noh de "URGENCIA"
                ult->prox=NULL;

                //se o aviao que pediu urgencia for o ultimo, "o ponteiro que aponta para o ultimo vai para o noh anterior
                if(dep==ult)
                    ult=ant;

                //retirar o noh da lista
                ant->prox=ant->prox->prox;
                dep->prox=NULL;

                //colocar o noh no final da fila dos urgentes
                dep->prox=aux->prox;
                aux->prox=dep;

                //apontar aux para o ultimo elemento urgente
                aux=aux->prox;
            }
        }
        //caso "default", ponteiro que aponta para o ultimo elemento avança um noh
        else ult=ult->prox;
    }

    //garantir que m esteja apontando para o primeiro elemento;
    prim=inicio->prox;

    //se percorreu todo o arquivo
    if(strcmp(prim->message,"FIM")!=0)
    {
        //imprimir na saida a situacao da fila
        fprintf(saida,"\nSituacao da fila\n\n");
        //m percorrera a lista para imprimir os remanescentes
        while(strcmp(prim->message,"FIM")!=0)
        {
            fprintf(saida,"%04d   %s",prim->flight,prim->from);
            prim=prim->prox;
        }
    }
    //se nao ha remanescentes
    else
        fprintf(saida,"\nA pista esta vazia.");

    //fechar os arquivos
    fclose(entrada);
    fclose(saida);

    //finalizar
    return 0;
}
