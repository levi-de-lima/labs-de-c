/*  Levi Gurgel de Lima                      */
/*  Turma 3                                  */
/*  Exercício 7: PERT                        */
/*                                           */
/*  Programa compilado com CodeBlocks 17.12  */
//a saber, TMT = tempo de minimo trajeto
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct infos infos; //defino o tipo infos
//declaracao da struct
struct infos
{
    //variaveis gerais
    char letra;
    char descri[31];
    int durac;

    //variaveis referentes a verificacao de ciclo
    bool descoberto;
    bool descobertoDFS;

    //variaveis referentes ao calculo dos TMT e dos itens a) e b)
    int tmt;
    int indpredTMT;
};
//variaveis globais
//arquivos
FILE*entrada;
FILE*saida;

int Matriz[52][52]; //matriz de adjacencias
infos VetorComInfos[52];    //vetor que contemas informacoes dadas
infos OrdTop[52];   //vetor que armazena a ordem topologica
int y=0;            //quantidade de elementos presentes + inicializacao
int TMT[52];

//a funcao recebe um indice de um elemento no vetor e faz busca em profundidade no noh correspondente
bool BuscaProfund(int indice)
{
    int j;  //contador
    j=0;    //inicializa o contador
    bool achouCiclo;    //booleana que sera retornada
    achouCiclo=0;   //inicializa a booleana com falso

    //o no chamado foi visitado
    VetorComInfos[indice].descoberto=1;
    VetorComInfos[indice].descobertoDFS=1;

    //percorre as colunas da matriz enquanto nao tiver achado um ciclo
    while(j<52 && !achouCiclo)
    {
        //o indice do vetor corresponde a linha da matriz
        //se o elemento de indice j for adjacente ao no da chamada
        if(Matriz[indice][j]==1)
        {
            //se esse no adjacente nao tiver sido descoberto, chama o DFS para o adjacente
            if(VetorComInfos[j].descoberto==0)
                achouCiclo=BuscaProfund(j);
            //se ja tiver sido descoberto
            //se ele foi descoberto no mesmo DFS, tem ciclo
            else if(VetorComInfos[j].descobertoDFS==1)
                achouCiclo=1;   //booleana recebe verdadeiro
        }
        //incrementa o contador
        j++;
    }
    //ao terminar uma chamada de DFS, se nao tiver achado ciclo, a informacao descobertoDFS recebe falso
    if(!achouCiclo)
        VetorComInfos[indice].descobertoDFS=0;
    //retorna a booleana
    return achouCiclo;
}
//a funcao verifica se ha ciclo no grafo
bool VerificaCiclo()
{
    int i;  //contador
    i=0;    //inicializa o contador
    bool achouCiclo;    //booleana que diz se o ciclo foi achado ou nao
    achouCiclo=0;   //inicializa a booleana com falso

    //inicializa todos os nos como nao descobertos
    for(i=0;i<52;i++)
    {
        VetorComInfos[i].descoberto=0;
        VetorComInfos[i].descobertoDFS=0;
    }
    //reinicializa o contador
    i=0;
    //percorre o vetor enquanto nao achou ciclo
    while(i<52 && !achouCiclo)
    {
        //se houver nos nao descobertos, chamar a funcao de busca em profundidade (DFS)
        if(VetorComInfos[i].descoberto==0)
            achouCiclo=BuscaProfund(i);
        //incrementa o contador
        i++;
    }
    //retorna a booleana
    return achouCiclo;
}
//inverte o vetor OrdTop
void Inverte()
{
    int x;  //contador
    infos aux[52];  //vetor auxiliar
    //percorre o vetor ate onde esta preenchido (posicao y-1)
    //e armazena na ordem inversa no vetor auxiliar
    for(x=0;x<y;x++)
        aux[y-x-1]=OrdTop[x];
    //vetor OrdTop recebe o conteudo do vetor auxiliar
    for(x=0;x<52;x++)
        OrdTop[x]=aux[x];
}
//a funcao recebe um indice de um elemento no vetor e faz busca em profundidade no noh correspondente
void DFS(int Indice)
{
    int j;  //contador
    VetorComInfos[Indice].descoberto=1;     //marca o no como descoberto
    //percorre as colunas da matriz
    for(j=0;j<52;j++)
    {
        //o indice do vetor corresponde a linha da matriz
        //se o elemento de indice j for adjacente ao noh da chamada, chama o DFS para o adjacente
        if(Matriz[Indice][j]==1 && VetorComInfos[j].descoberto==0)
        {
            DFS(j);
        }
    }
    //se o indice da chamada corresponde a um noh do grafo
    if(VetorComInfos[Indice].letra!='0')
    {
        //coloca as informacoes desse no vetor ordem topologica
        OrdTop[y]=VetorComInfos[Indice];
        //incrementa o contador do numero de elementos no vetor OrdTop
        y++;
    }
}
//acha uma ordenacao topologica para o grafo e armazena no vetor OrdTop
void OrdenacaoTopologica()
{
    int i;  //contador
    i=0;    //inicializa o contador
    int j;  //contador
    bool TemPred;   //booleana que verifica se ha predecessor no noh
    //percorre o vetor enquanto houver nos nao descobertos
    while(i<52 && VetorComInfos[i].descoberto==0)
    {
        //inicializa a booleana
        TemPred=0;
        //se for uma posicao do vetor correspondente a um no
        if(VetorComInfos[i].letra!='0')
        {
            //percorre as colunas da matriz e verifica se o noh tem precedente
            for(j=0;j<52;j++)
               if(Matriz[j][i]==1)
                    TemPred=1;
            //se nao tem precedente
            if(!TemPred)
                DFS(i);
        }
        else VetorComInfos[i].descoberto=1;
        //incrementa o contador
        i++;
    }
    //pela natureza da busca em profundidade o vetor e armazenado na ordem inversa
    //chama a funcao que inverte o vetor
    Inverte();
}
//retorna o maior entre os TMT dos precedentes do noh chamado
int maxTMT(int indice)
{
    int i;  //contador
    int maximo;     //armazena o maximo TMT ate entao
    maximo=0;   //inicializa maximo
    //percorre o vetor OrdTop ate chegar no noh da chamada
    for(i=0;i<indice;i++)
    {
        if(Matriz[OrdTop[i].letra-'A'][OrdTop[indice].letra-'A']==1)    //se for precedente
            if(OrdTop[i].tmt>maximo)   //se o TMT do precedente for maior que o maximo ate entao
            {
                maximo=OrdTop[i].tmt;  //este TMT eh o novo maximo
                OrdTop[indice].indpredTMT=i;     //armazena indicie do maximo TMT do precedente
            }
    }
    //retorna o maximo
    return maximo;
}
//retorna o indice no vetor OrdTop do maior dos TMT entre todos os nos
int MaiorTMT()
{
    int i;  //contador
    i=0;    //inicializa o contador
    int imaximo;    //indice do maior TMT no vetor
    imaximo=0;      //inicializa o indice
    int maximo;     //valor do maximo TMT
    maximo=0;       //inicializa maximo
    //percorre o vetor ate onde esta preenchido (posicao y-1)
    for(i=0;i<y;i++)
    {
        //se o TMT for maior que o maximo ate entao
        if(OrdTop[i].tmt>maximo)
        {
            //esse TMT e o novo maximo
            maximo=OrdTop[i].tmt;
            //o indice dele eh o novo indice maximo
            imaximo=i;
        }
    }
    //retorna o indice
    return imaximo;
}
//escreve na saida o vaminho critico
void CaminhoCritico(int indice)
{
    //se nao chegou a um noh que nao tem precedentes
    if(OrdTop[indice].indpredTMT!=-1)
        CaminhoCritico(OrdTop[indice].indpredTMT);   //chama a funcao para o precedente de maior TMT
    //escreve na saida o caminho critico
    fprintf(saida,"  %c   %s  %2d\n",OrdTop[indice].letra,OrdTop[indice].descri,OrdTop[indice].durac);
}
int main()
{
    char lixo[100]; //string lixo
    char letra; //armazena a letra da tarefa
    letra='0';  //inicializa a letra
    char pred[100];     //string dos precedentes

    infos aux;  //noh auxiliar

    int i,j,k,w;    //contadores
    int indice1;    //indices da matriz
    int indice2;

    int IndiceMaiorTMT;
    bool TemCiclo;

    //abre os arquivos de entrada e saida
    entrada=fopen("entrada7.txt","r");
    saida=fopen("Lab7_Levi_Gurgel_de_Lima.txt","w");

    //pula as linha inuteis da entrada
    fgets(lixo,100,entrada);
    fgets(lixo,100,entrada);
    fgets(lixo,100,entrada);
    fgets(lixo,100,entrada);
    fgets(lixo,100,entrada);
    fgets(lixo,100,entrada);
    fgets(lixo,100,entrada);

    fprintf(saida,"\"Os que com lágrimas semeiam com júbilo ceifarão.\n");
    fprintf(saida,"Quem sai andando e chorando, enquanto semeia,\n");
    fprintf(saida,"voltará com júbilo, trazendo os seus feixes.\"\n");
    fprintf(saida,"Salmos 126:5-6\n\n");
    fprintf(saida,"------------------------------------------------------------\n\n");

    //inicializa a matriz de adjacencias com zeros
    for(j=0;j<52;j++)
        for(k=0;k<52;k++)
            Matriz[j][k]=0;

    //inicializa as letras do vetor como "zero"
        for(i=0;i<52;i++)
            VetorComInfos[i].letra='0';

    //enquanto nao chegar ao fim do arquivo, fazer
    do
    {
        //le a tarefa
        fscanf(entrada," %c ",&letra);
        //le a descricao
        fgets(aux.descri,30,entrada);
        //le a duracao
        fscanf(entrada," %d ",&aux.durac);

        //esses dados sao armazenados em um no auxiliar
        aux.letra=letra;
        //converte a letra para um numero indexavel na matriz
        //este sera o indice da coluna da matriz
        indice2=letra-'A';

        //le os precedentes
        fscanf(entrada," %s",&pred);

        //inicializa o contador
        w=0;
        //enquanto nao chegar ao fim da string dos precedentes
        while(pred[w] != '\0')
        {
            //se o caractere for uma letra
            if((pred[w]>='A' && pred[w]<='Z') || (pred[w]>='a' && pred[w]<='z'))
            {
                //este sera o indice da linha da matriz
                indice1=pred[w]-'A';
                //matriz recebe 1 na posicao que representa que o indice1 "aponta" para o indice2
                Matriz[indice1][indice2]=1;
            }
            //incrementa o contador
            w++;
        }

        //o vetor que armazenara as informacoes de cada no recebe o no auxiliar na posicao correspondente a coluna da matriz
        VetorComInfos[indice2]=aux;
    }while(letra!='-');

    //chama a funcao que verifica se tem ciclo e recebe 1 (verdadeiro) ou 0 (falso)
    TemCiclo=VerificaCiclo();

    //se tem ciclo, imprime mensagem na saida juntamente com o proprio ciclo
    if(TemCiclo)
    {
        //mensagens
        fprintf(saida,"Tem ciclo! Eh impossivel buscar o caminho critico.\n");
        fprintf(saida,"O ciclo eh: ");
        //imprime o ciclo
        for(i=0;i<52;i++)
            if(VetorComInfos[i].descoberto==1 && VetorComInfos[i].descobertoDFS==1)
                fprintf(saida,"%c ",VetorComInfos[i].letra);
    }
    //se nao tem ciclo
    else
    {
        //reinicializa os nos como nao descobertos
        for(i=0;i<52;i++)
            VetorComInfos[i].descoberto=0;

        //chama a funcao que descobre uma ordenacao topologica e coloca no vetor OrdTop
        OrdenacaoTopologica();

        fprintf(saida,"UMA ORDENACAO TOPOLOGICA:\n\n");

        for(i=0;i<y;i++)
            fprintf(saida,"%c ",OrdTop[i].letra);

        fprintf(saida,"\n\n------------------------------------------------------------\n");

        fprintf(saida,"\n");

        //inicializa as informacoes sobre o tmt no vetor
        for(i=0;i<52;i++)
        {
            OrdTop[i].tmt=0;
            OrdTop[i].indpredTMT=-1;
        }

        //percorre o vetor, se um noh for encontrado, calcular seu TMT
        //o tmt consiste na duracao dos nos adicionado do maximo tmt dos nos precedentes
        for(i=0;i<y;i++)
            OrdTop[i].tmt=OrdTop[i].durac + maxTMT(i);  //chama funcao que devolve o maximo TMT dos nos precedentes

        //armazena o indice do maior TMT no vetor
        IndiceMaiorTMT=MaiorTMT();

        fprintf(saida,"CAMINHO CRITICO:\n\n");

        fprintf(saida,"TAREFA        DESCRICAO           DURACAO\n\n");

        //chama a funcao que escreve o caminho critico
        CaminhoCritico(IndiceMaiorTMT);

        fprintf(saida,"                                   ----\n");

        //escreve o tempo minimo para o projeto na saida
        fprintf(saida,"TEMPO MINIMO PARA O PROJETO:         %2d semanas\n",OrdTop[IndiceMaiorTMT].tmt);
    }

    //fecha os arquivos de entrada e saida
    fclose(entrada);
    fclose(saida);
}
