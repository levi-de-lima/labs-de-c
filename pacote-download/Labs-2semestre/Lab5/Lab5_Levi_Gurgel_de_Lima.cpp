/*  Levi Gurgel de Lima                      */
/*  Turma 3                                  */
/*  Exercício 5: Livros                      */
/*                                           */
/*  Programa compilado com CodeBlocks 17.12  */
//inclui as bibliotecas
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//simplifica a declaracao dessas structs
typedef struct secao secao;
//cada secao do livro
struct secao
{
    char nome[21];  //nome da secao
    secao* fesq;    //filho esquerdo
    secao* irmao;   //irmao direito
    secao* pai;     //pai
};

//declara e inicializa
secao* raiz=NULL;

//busca, em pre ordem, um elemento na arvore e retorna um ponteiro para ele
secao* PreOrdem(secao* f, char* referencia)
{
    //p recebera o ponteiro que contem a referencia
    secao* p;
    p=NULL;
    //se a referencia passada estiver na raiz
    if(strcmp(f->nome,referencia)==0)
    {
        //p recebe f
        p=f;
    }
    //se nao estiver na raiz
    else
    {
        //se o filho esquerdo do ponteiro passado nao for NULL
        if(f->fesq!=NULL)
        {
            //f recebe o filho esquerdo
            f=f->fesq;
            //fazer, enquanto nao for achada a referencia ou nao chegar no final da arvore
            do
            {
                //chama a PreOrdem recursivamente
                p=PreOrdem(f,referencia);
                //f recebe o irmao direito
                f=f->irmao;
            }while(f!=NULL&&p==NULL);
        }
    }
    //retorna p
    return p;
}
//insere uma nova secao seguinte ou sub outra na arvore
void Insere(secao* inserido, char* SubOuSeg, char* referencia, FILE* saida)
{
    //ponteiro posicao que recebera o resultado da pre ordem
    secao* pos;
    pos=NULL;
    //chama o PreOrdem que devolve um ponteiro que aponta para a referencia na arvore
    pos=PreOrdem(raiz,referencia);
    //se o ponteiro for NULL
    if(pos==NULL)
    {
        //escrever mensagem de erro
        fprintf(saida,"ERRO: nao encontrado item %s\n",referencia);
        fprintf(saida,"--------------------------------------------------\n");
    }
    //se o ponteiro nao for NULL
    else
    {
        //se o comando for SUB
        if(strcmp("SUB",SubOuSeg) == 0)
        {
            //colocar o elemento inserido abaixo de pos
            inserido->irmao = pos->fesq;
            //colocar inserido como filho esquerdo de pos
            pos->fesq = inserido;
            //aponta para o pai
            inserido->pai=pos;
        }
        //se o comando for SEGUINTE_A
        if(strcmp("SEGUINTE_A",SubOuSeg) == 0)
        {
            //colocar o elemento inserido ao lado de pos
            inserido->irmao = pos->irmao;
            pos->irmao = inserido;
            //aponta para o pai
            inserido->pai = pos->pai;
        }
    }
}
//remove uma secao da arvore
void Remove(char* referencia, FILE* saida)
{
    //recebe o ponteiro posicao do PreOrdem
    secao* pos;
    //ponterio auxiliar
    secao* aux;
    //chama o PreOrdem que devolve um ponteiro que aponta para a referencia na arvore
    pos=PreOrdem(raiz,referencia);
    //se a posicao nao for NULL
    if(pos!=NULL)
    {
        //o auxiliar apontara para o pai de pos
        aux=pos;
        aux=aux->pai;
        //se o removido nao estiver na posicao de filho esquerdo de aux
        if(strcmp(aux->fesq->nome,referencia)!=0)
        {
            //aux recebe o filho esquerdo
            aux=aux->fesq;
            //executar ate chegar na posicao anterior a pos
            while(aux->irmao!=pos)
                aux=aux->irmao;
        }
        //remove o pos
        aux->irmao=pos->irmao;
        pos->irmao=NULL;
    }
    //se a posicao for NULL
    else
    {
        //escrever mensagem de erro
        fprintf(saida,"ERRO: nao encontrado item %s\n",referencia);
        fprintf(saida,"--------------------------------------------------\n");
    }
}
//imprime os indices no arquivo de saida
void Indice(secao* f, FILE* saida)
{
    int i;  //contador
    i=1;
    //se a secao recebida nao apontar para a raiz
    if(f!=raiz)
    {
        //declara um ponteiro auxiliar
        secao* aux;
        //inicializa-o com o filho esquerdo
        aux=f->pai->fesq;
        //chama o indice recursivamente
        Indice(f->pai, saida);
        //enquanto aux for diferente de f
        while(aux!=f)
        {
            //aux recebe o irmao direito
            aux=aux->irmao;
            //incremetna 1 no contador
            i++;
        }
        //escreve na saida o indice referente aquela secao
        fprintf(saida,"%d.",i);
    }
}
//escreve a lista na saida
void Lista(secao* f, FILE* saida)
{
    //se o ponteiro recebido for diferente de NULL
    if(f!=NULL)
    {
        //chama a funcao Indice
        Indice(f, saida);
        //escreve a secao na saida
        fprintf(saida,"      %s\n",f->nome);
        //f recebe o filho esquerdo
        f=f->fesq;
        //enquanto o ponteiro recebido for diferente de NULL
        while(f!=NULL)
        {
            //chama a lista recursivamente
            Lista(f, saida);
            //f recebe o irmao direito
            f=f->irmao;
        }
    }
}
int main()
{
    //declaracao dos arquivos de entrada e saida
    FILE*entrada;
    FILE*saida;

    //declaracao dos ponteiros utilizados
    secao* novo;    //elemento novo a ser inserido
    //auxiliares
    secao* aux;
    secao* aux2;

    //abertura dos arquivos
    entrada=fopen("entrada5.txt","r");
    saida=fopen("Lab5_Levi_Gurgel_de_Lima.txt","w");

    //strings utilizadas
    char lixo[71];
    char info[21];      //TITULO, INSERIR, etc.
    char auxiliar[21];
    char SubOuSeg[21];  //SUB ou SEGUINTE_A
    char PaiDoNovo[21]; //secao que fica acima da nova inserida
    char PaiDaSecao[21];    //analogo a PaiDoNovo mas para TRANSFERIR
    char SecRem[21];        //secao removida

    //contador
    int i;
    i=1;

    //descarta as linhas iniciais do arquivo de entrada
    fgets(lixo,71,entrada);
    fgets(lixo,71,entrada);
    fgets(lixo,71,entrada);
    fgets(lixo,71,entrada);

    //escreve as linhas iniciais na saida
    fprintf(saida,"\"Alegrem-se na esperança, sejam pacientes na tribulação,\n");
    fprintf(saida,"perseverem na oração.\"\n");
    fprintf(saida,"Romanos 12:12\n");
    fprintf(saida,"--------------------------------------------------\n");

    //fazer, enquanto nao chegar ao fim
    do
    {
        //alocacao do espaco de memoria de novo
        novo=(secao*)malloc(sizeof(secao));

        //inicializacao de novo
        novo->irmao=NULL;
        novo->pai=NULL;
        novo->fesq=NULL;

        //le a primeira informacao
        fscanf(entrada,"%s ",&info);
        //se info for TITULO
        if(strcmp(info,"TITULO")==0)
        {
            //se nao houver arvore
            if(raiz==NULL)
            {
                //alocacao do espaco de memoria
                raiz = (secao*)malloc(sizeof(secao));
                //inicializacao da raiz
                raiz->pai = NULL;
                raiz->irmao = NULL;
                raiz->fesq = NULL;
                //le o nome da secao e coloca na raiz
                fscanf(entrada,"%s ",raiz->nome);
            }
            //se ja houver arvore
            else
            {
                //aloca o espaco de memoria para o ponteiro auxiliar
                aux = (secao*)malloc(sizeof(secao));
                //le o nome da secao e coloca em aux
                fscanf(entrada,"%s ",aux->nome);
                //coloca o novo titulo e poe toda a arvore como secao dele
                aux->fesq=raiz;
                raiz=aux;
                free(aux);
            }
        }
        //se info for INSERIR
        if(strcmp(info,"INSERIR")==0)
        {
            //le o nome a ser inserido
            fscanf(entrada,"%s ",&novo->nome);
            //se ja houver arvore
            if(raiz!=NULL)
            {
                //ler informacao de SUB ou SEGUINTE_A
                fscanf(entrada,"%s ",&SubOuSeg);
                //ler onde a secao nova sera inserida
                fscanf(entrada,"%s ",&PaiDoNovo);
                //se tentar inserir seguinte ao titulo, escrever mensagem de erro
                if(strcmp(SubOuSeg,"SEGUINTE_A")==0 && strcmp(PaiDoNovo,raiz->nome)==0)
                    fprintf(saida,"Operacao invalida!\n");
                //senao, chama funcao inserir
                else Insere(novo,SubOuSeg,PaiDoNovo,saida);
            }
            //se nao houver arvore
            else
            {
                //escrever mensagem de erro
                fprintf(saida,"ERRO: nao encontrado item %s\n",novo->nome);
                fprintf(saida,"--------------------------------------------------\n");
            }
        }
        //se info for REMOVER
        if(strcmp(info,"REMOVER")==0)
        {
            //se ja houver arvore
            if(raiz!=NULL)
            {
                //le a secao a ser removida
                fscanf(entrada,"%s ",&SecRem);
                //se a secao a ser removida for o titulo
                if(strcmp(SecRem,raiz->nome)==0)
                    raiz=NULL;
                //se nao for o titulo, chama a funcao Remove
                else Remove(SecRem,saida);
            }
            //se nao houver arvore
            else
            {
                //escrever mensagem de erro na saida
                fprintf(saida,"ERRO: nao encontrado item %s\n",novo->nome);
                fprintf(saida,"--------------------------------------------------\n");
            }
        }
        //se info for TRANSFERIR
        if(strcmp(info,"TRANSFERIR")==0)
        {
            //le a secao a ser transferida e coloca numa string auxiliar
            fscanf(entrada,"%s ",&auxiliar);
            //aux2 recebe a posicao de auxiliar na arvore
            aux2=PreOrdem(raiz, auxiliar);
            //se houver arvore e o auxiliar estiver na arvore
            if(raiz!=NULL && aux2!=NULL)
            {
                //le se e SUB ou SEGUINTE_A
                fscanf(entrada,"%s ",&SubOuSeg);
                //le o nome da secao que ficara acima do transferido
                fscanf(entrada,"%s ",&PaiDaSecao);
                //se tentar transferir seguinte ao titulo, escrever mensagem de erro
                if(strcmp(SubOuSeg,"SEGUINTE_A")==0 && strcmp(PaiDaSecao,raiz->nome)==0)
                    fprintf(saida,"Operacao invalida!\n");
                //senao
                else
                {
                    //remove a secao do local em que esta e insere no local requerido
                    Remove(auxiliar, saida);
                    Insere(aux2,SubOuSeg,PaiDaSecao,saida);
                }
            }
            //senao
            else
            {
                //escrever mensagem de erro na saida
                fprintf(saida,"ERRO: nao encontrado item %s\n",novo->nome);
                fprintf(saida,"--------------------------------------------------\n");
            }
        }
        //se for LISTA
        if(strcmp(info,"LISTA")==0)
        {
            //escrever a lista na saida
            fprintf(saida,"LISTA %d\n\n",i);
            //chamar a funcao lista
            Lista(raiz,saida);
            fprintf(saida,"--------------------------------------------------\n");
            //contador da lista
            i++;
        }
        //libera o novo;
        novo=NULL;
    }while(strcmp(info,"FIM")!=0);

    //fecha os arquivos
    fclose(entrada);
    fclose(saida);

    //finaliza
    return 0;
}
