#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct voo noh;
struct voo
{
    char message[100];
    int flight;
    char from[100];
    noh*prox=NULL;
};
int main()
{
    FILE*entrada;
    FILE*saida;

    noh*inicio;
    noh*p;
    noh*m;
    noh*ant;
    noh*dep;
    noh*aux;

    char lixo[100];

    entrada=fopen("entrada1.txt","r");
    saida=fopen("Lab1_Levi_Gurgel_de_Lima.txt","w");

    fgets(lixo,100,entrada);
    fgets(lixo,100,entrada);
    fgets(lixo,100,entrada);
    fgets(lixo,100,entrada);
    fgets(lixo,100,entrada);
    fgets(lixo,100,entrada);
    fgets(lixo,100,entrada);
    fgets(lixo,100,entrada);

    fprintf(saida,"O Senhor é o meu pastor; nada me faltará.\n");
    fprintf(saida,"Ele me faz repousar em pastos verdejantes.\n");
    fprintf(saida,"Leva-me para junto das águas de descanso; refrigera-me a alma.\n");
    fprintf(saida,"Guia-me pelas veredas da justiça por amor do seu nome. Salmos 23:1-3\n");
    fprintf(saida,"=========================================\n");
    fprintf(saida,"FLIGHT FROM\n\n");

    do
    {
        inicio=NULL;
        inicio=(noh*)malloc(sizeof(noh));
        p=inicio;

        aux=inicio;

        fscanf(entrada,"%s ",&p->message);
        fscanf(entrada,"%d ",&p->flight);
        fgets(p->from,100,entrada);

        if(strcmp(p->message,"pista_liberada")==0)
            fprintf(saida,"0000   Nenhum aviao pousando\n");

    }while(strcmp(p->message,"pista_liberada")==0);

    if(strcmp(p->message,"FIM")!=0)
    {
        p->prox=(noh*)malloc(sizeof(noh));

        fscanf(entrada,"%s ",&p->prox->message);
        fscanf(entrada,"%d ",&p->prox->flight);
        fgets(p->prox->from,100,entrada);

        //printf("%s",p->prox->message);

        if(strcmp(p->prox->message,"pista_liberada")==0)
        {
            fprintf(saida,"%04d   %s",p->flight,p->from);
            p->prox=NULL;
        }
        else if(strcmp(p->prox->message,"URGENCIA")==0)
            p->prox=NULL;
    }

    /*while(strcmp(p->message,"FIM")!=0)
    {
        ant=inicio;
        dep=inicio->prox;

        p->prox=(noh*)malloc(sizeof(noh));
        m=inicio;

        fscanf(entrada,"%s ",&p->prox->message);
        fscanf(entrada,"%d ",&p->prox->flight);
        fgets(p->prox->from,100,entrada);

        if(strcmp(p->prox->message,"pista_liberada")==0)
        {
            if(strcmp(m->message,"pista_liberada")==0)
            {
                p->prox=NULL;
                fprintf(saida,"0000   Nenhum aviao pousando\n");
                if(aux==m)
                    aux=inicio;
            }
            else if(strcmp(m->prox->message,"pista_liberada")==0)
            {
                p->prox=NULL;
                inicio->prox=inicio->prox->prox;
                fprintf(saida,"%04d   %s",m->flight,m->from);
                p=inicio;
                if(aux==m)
                    aux=inicio;
            }
            else
            {
                p->prox=NULL;
                inicio->prox=inicio->prox->prox;
                m->prox=NULL;
                fprintf(saida,"%04d   %s",m->flight,m->from);
                if(aux==m)
                    aux=inicio;
            }
        }
        else if (strcmp(p->prox->message,"URGENCIA")==0)
        {
            if(strcmp(m->message,"URGENCIA")==0)
            {
                p->prox=NULL;
            }
            else if(strcmp(m->prox->message,"URGENCIA")==0)
            {
                p->prox=NULL;
            }
            else
            {
                while(dep->flight!=p->prox->flight)
                {
                    ant=ant->prox;
                    dep=dep->prox;
                }
                p->prox=NULL;

                if(dep==p)
                    p=ant;

                ant->prox=ant->prox->prox;
                dep->prox=NULL;

                dep->prox=aux->prox;
                aux->prox=dep;

                aux=aux->prox;
            }
        }
        else p=p->prox;
    }

    m=inicio->prox;

    if(strcmp(m->message,"FIM")!=0)
    {
        fprintf(saida,"\nSituacao da fila\n\n");
        while(strcmp(m->message,"FIM")!=0)
        {
            fprintf(saida,"%04d   %s",m->flight,m->from);
            m=m->prox;
        }
    }
    else
        fprintf(saida,"\nA pista esta vazia.");*/
    fclose(entrada);
    fclose(saida);

    return 0;
}


