/*  Levi Gurgel de Lima                      */
/*  Turma 3                                  */
/*  Exercício 10: Vestibular                 */
/*                                           */
/*  Programa compilado com CodeBlocks 17.12  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define boolean int
int main ()
{
    //declaracao de arquivos
    FILE*inscritos;
    FILE*respostas;
    FILE*gabarito;
    FILE*saida;

    //-----------------------------------------------------------------------------
    //leitura do arquivo "inscritos"

    //abre o arquivo
    inscritos=fopen("Lab10_inscritos.txt","r");

    //declaracao de variaveis
    char gab[50],       //gabarito
         lixo[100];
    int n;              //numero de candidatos inscritos
    int i, j, p;           //contadores dos for's

    //struct para armazenar os dados do candidato
    struct candidato
    {
        char nome[40],
             answers[51],   //respostas, em ingles
             situacao[100];
        char curso;
        int Ninsc; //numero de inscricao
        float nota;
        boolean FezProva;

    };
    //declaracao de variavel struct candidato
    struct candidato cand[100]; //vetor de structs

    //pula as linhas desnecessarias e coloca-as na variavel lixo
    fgets(lixo,100,inscritos);
    fgets(lixo,100,inscritos);
    fgets(lixo,100,inscritos);
    fgets(lixo,100,inscritos);
    fgets(lixo,32,inscritos);
    //le o numero de inscritos
    fscanf(inscritos,"%d",&n);
    fgets(lixo,100,inscritos);
    fgets(lixo,100,inscritos);
    fgets(lixo,100,inscritos);
    fgets(lixo,100,inscritos);

    //percorre o arquivo inscritos e le o numero de inscricao, o nome e o curso do candidato e armazena no vetor de structs
    for(i=0;i<n;i++)
    {
        fscanf(inscritos,"%d ",&cand[i].Ninsc);
        fgets(cand[i].nome,29,inscritos);
        fscanf(inscritos,"%c",&cand[i].curso);
        //inicializa a booleana com falso
        cand[i].FezProva=FALSE;
    }

    //fecha o arquivo "inscritos"
    fclose(inscritos);

    //-----------------------------------------------------------------------------
    //leitura do arquivo "respostas"

    //abre o arquivo
    respostas=fopen("Lab10_respostas_preenchidas.txt","r");

    //declaracao de variaveis
    int m;              //numero de folhas de respostas recebidas
    int insc;           //numero de inscricao
    char resp[51];      //gabarito de cada candidato

    //pula as linhas desnecessarias e coloca-as na variavel lixo
    fgets(lixo,100,respostas);
    fgets(lixo,100,respostas);
    fgets(lixo,100,respostas);
    fgets(lixo,100,respostas);
    fgets(lixo,32,respostas);
    //le o numero de folhas recebidas
    fscanf(respostas,"%d",&m);
    fgets(lixo,100,respostas);
    fgets(lixo,100,respostas);
    fgets(lixo,100,respostas);
    fgets(lixo,100,respostas);

    //percorre o arquivo "respostas" e le o numero de inscricao e o gabarito de cada candidato
    for(i=0;i<m;i++)
    {
        fscanf(respostas,"%d ",&insc);
        fgets(resp,51,respostas);
        //se o numero de isncricao do candidato esta presente nas folhas recebidas, FezProva recebe verdadeiro e cada struct do vetor recebe suas respostas
        for(j=0;j<n;j++)
        {
            if(insc==cand[j].Ninsc)
            {
                strcpy(cand[j].answers,resp);
                cand[j].FezProva=TRUE;
            }
        }
    }

    //fecha o arquivo "respostas"
    fclose(respostas);

    //-----------------------------------------------------------------------------
    //leitura do arquivo "gabarito"

    //abre o arqyuivo
    gabarito=fopen("Lab10_gabarito.txt","r");

    //declaracao de variaveis
    char gabs[51]; //gabarito
    int TotComp,    //total de vagas
        TotAst,
        TotTur;
    float MinComp,  //nota minima
          MinAst,
          MinTur;

    //pula as linhas desnecessarias e coloca-as na variavel lixo
    fgets(lixo,100,gabarito);
    fgets(lixo,100,gabarito);
    fgets(lixo,100,gabarito);
    fgets(lixo,100,gabarito);
    fgets(lixo,100,gabarito);
    fgets(lixo,100,gabarito);
    //le o gabarito e coloca em "gabs"
    fgets(gabs,51,gabarito);
    fgets(lixo,100,gabarito);
    fgets(lixo,100,gabarito);
    fgets(lixo,100,gabarito);
    fgets(lixo,100,gabarito);

    //le o total de vagas e a nota minima para cada materia
    fscanf(gabarito,"%s %d %g",&lixo,&TotComp,&MinComp);
    fscanf(gabarito,"%s %d %g",&lixo,&TotAst,&MinAst);
    fscanf(gabarito,"%s %d %g",&lixo,&TotTur,&MinTur);

    //fecha o arquivo "gabarito"
    fclose(gabarito);

    //-----------------------------------------------------------------------------

    //abre o arquivo "saida"
    saida=fopen("Lab10_Levi_Gurgel_de_Lima.txt","w");

    //declaracao de variaveis
    struct candidato aux,           //struct auxiliar
                     comput[100],   //armazena os candidatos que passaram em cada materia
                     astrom[100],
                     turis[100];
    int k,      //contador de questoes acertadas
        comp,   //contadores de pessoas que passaram em cada materia
        ast,
        tur;
    int c=0,    //contador que verifica se o candidato esta dentro dos classificados de cada materia
        a=0,    //+ inicializacao com zero
        t=0;

    //--------
    //item (a)
    //--------

    fprintf(saida,"Com os testes do enunciado, as respostas sao as seguintes.\n\n");
    fprintf(saida,"----------------------------------\n");
    fprintf(saida,"a) Classificados no vestibular\n");
    fprintf(saida,"----------------------------------\n\n");

    //percorre o vetor de structs e calcula a nota de cada candidato
    for(i=0;i<n;i++)
    {
        //inicializa o contador
        k=0;
        //percorre as respostas do candidato
        for(int j=0;j<50;j++)
        {
            //se a nota estiver correta somar 1 ao contador
            if(cand[i].answers[j]==gabs[j])
                k++;
        }
        //coloca a nota do candidato na struct
        cand[i].nota=(1.0*k/5);
    }

    //BubbleSort para ordenar os candidatos por nota
    for(p=n-2;p>=0;p--)
        for(int i=0;i<=p;i++)
            if(cand[i].nota<cand[i+1].nota)
            {
                aux=cand[i];
                cand[i]=cand[i+1];
                cand[i+1]=aux;
            }

    //escreve a lista de computacao
    fprintf(saida,"Sub-lista Computacao:\n\n");
    //inicializa o contador
    comp=0;
    //percorre o vetor de structs
    for(i=0;i<n;i++)
    {
        //se o curso e' comp, tirou acima do minimo e ainda ha vagas
        if(cand[i].curso=='C'&&cand[i].nota>=MinComp&&comp<TotComp)
        {
            //coloca quem passou em computacao no vetor de structs "comput"
            strcpy(comput[comp].nome,cand[i].nome);
            //incrementa o contador
            comp++;
        }
    }
    //BubbleSort para ordenar os candidatos em ordem alfabetica no vetor de structs "comput"
    for(p=comp-2;p>=0;p--)
        for(i=0;i<=p;i++)
            if(strcmp(comput[i].nome,comput[i+1].nome)>0)
            {
                aux=comput[i];
                comput[i]=comput[i+1];
                comput[i+1]=aux;
            }

    //escreve o nome dos candidatos que passaram em computacao em ordem alfabetica
    for(i=0;i<comp;i++)
        fprintf(saida,"\t%s\n",comput[i].nome);

    //escreve o numero de classificados e de vagas remanescentes
    fprintf(saida,"\n\t\tNumero de classificados: %d\n",comp);
    fprintf(saida,"\t\tVagas remanescentes:     %d\n\n",TotComp-comp);

    //escreve a lista de astronomia
    //segue analogo ao anterior
    fprintf(saida,"Sub-lista Astronomia:\n\n");
    ast=0;
    for(i=0;i<n;i++)
    {
        if(cand[i].curso=='A'&&cand[i].nota>=MinAst&&ast<TotAst)
        {
            strcpy(astrom[ast].nome,cand[i].nome);
            ast++;
        }
    }

    //BubbleSort para ordenar os candidatos que passaram em astronomia em ordem alfabetica
    for(p=ast-2;p>=0;p--)
        for(i=0;i<=p;i++)
            if(strcmp(astrom[i].nome,astrom[i+1].nome)>0)
            {
                aux=astrom[i];
                astrom[i]=astrom[i+1];
                astrom[i+1]=aux;
            }

    for(i=0;i<ast;i++)
        fprintf(saida,"\t%s\n",astrom[i].nome);

    fprintf(saida,"\n\t\tNumero de classificados: %d\n",ast);
    fprintf(saida,"\t\tVagas remanescentes:     %d\n\n",TotAst-ast);

    //escreve a lista de turismo
    //segue analogo ao anterior
    fprintf(saida,"Sub-lista Turismo:\n\n");
    tur=0;
    for(i=0;i<n;i++)
    {
        if(cand[i].curso=='T'&&cand[i].nota>=MinTur&&tur<TotTur)
        {
            strcpy(turis[tur].nome,cand[i].nome);
            tur++;
        }
    }

    //BubbleSort para ordenar os candidatos que passaram em turismo em ordem alfabetica
    for(p=tur-2;p>=0;p--)
        for(i=0;i<=p;i++)
            if(strcmp(turis[i].nome,turis[i+1].nome)>0)
            {
                aux=turis[i];
                turis[i]=turis[i+1];
                turis[i+1]=aux;
            }

    for(i=0;i<tur;i++)
    {
        fprintf(saida,"\t%s\n",turis[i].nome);
    }

    fprintf(saida,"\n\t\tNumero de classificados: %d\n",tur);
    fprintf(saida,"\t\tVagas remanescentes:     %d\n\n",TotTur-tur);

    //--------
    //item (b)
    //--------

    fprintf(saida,"----------------------------------\n");
    fprintf(saida,"b) Pontuacao geral\n");
    fprintf(saida,"----------------------------------\n\n");
    fprintf(saida,"Posicao       Nome                      Nota\n\n");

    //percorrer o vetor de structs e escrever na saida o nome e a nota dos candidatos nao faltantes
    for(i=0;i<n;i++)
    {
        if(cand[i].FezProva)
            fprintf(saida,"%6d       %s%.1f\n",i+1,cand[i].nome,cand[i].nota);
    }

    //--------
    //item (c)
    //--------

    fprintf(saida,"----------------------------------\n");
    fprintf(saida,"c) Relatorio completo\n");
    fprintf(saida,"----------------------------------\n\n");
    fprintf(saida,"   Num.       Nome                          Curso     Nota       Situacao\n\n");

    //percorre o vetor de structs e armazena a situacao do cantidato
    for(i=0;i<n;i++)
    {
        //se o candidato nao fez a prova
        if(!cand[i].FezProva)
            strcpy(cand[i].situacao,"ausente");
        //se o candidato fez a porva
        else
        {
            //se e de computacao
            if(cand[i].curso=='C')
            {
                //incrementa o contador
                c++;
                //se o candidato obteve nota menor que a minima
                if(cand[i].nota<MinComp)
                    //o campo situacao da struct recebe "reprovado"
                    strcpy(cand[i].situacao,"reprovado");
                //se o candidato esta dentro das vagas de computacao
                else if(c<=comp)
                      //o campo situacao da struct recebe "classificado"
                      strcpy(cand[i].situacao,"classificado");
                     //senao, o campo situacao da struct recebe "fila de espera"
                     else strcpy(cand[i].situacao,"fila de espera");
            }
            //se e de astronomia
            //segue analogo ao anterior
            if(cand[i].curso=='A')
            {
                a++;
                if(cand[i].nota<MinAst)
                    strcpy(cand[i].situacao,"reprovado");
                else if(a<=ast)
                      strcpy(cand[i].situacao,"classificado");
                     else strcpy(cand[i].situacao,"fila de espera");
            }
            //se e de turismo
            //segue analogo ao anterior
            if(cand[i].curso=='T')
            {
                t++;
                if(cand[i].nota<MinTur)
                    strcpy(cand[i].situacao,"reprovado");
                else if(t<=tur)
                      strcpy(cand[i].situacao,"classificado");
                     else strcpy(cand[i].situacao,"fila de espera");
            }
        }
    }
    //BubbleSort para ordenar os candidatos em ordem alfabetica
    for(p=n-2;p>=0;p--)
        for(i=0;i<=p;i++)
            if(strcmp(cand[i].nome,cand[i+1].nome)>0)
            {
                aux=cand[i];
                cand[i]=cand[i+1];
                cand[i+1]=aux;
            }

    //percorre o vetor de structs, escrevendo no arquivo as informacoes de cada candidato
    for(i=0;i<n;i++)
    {
        //se for de computacao
        if(cand[i].curso=='C')
            fprintf(saida,"%6d      %s Computacao    %.1f       %s\n",cand[i].Ninsc,cand[i].nome,cand[i].nota,cand[i].situacao);
        //se for de astronomia
        if(cand[i].curso=='A')
            fprintf(saida,"%6d      %s Astronomia    %.1f       %s\n",cand[i].Ninsc,cand[i].nome,cand[i].nota,cand[i].situacao);
        //se for de turismo
        if(cand[i].curso=='T')
            fprintf(saida,"%6d      %s Turismo       %.1f       %s\n",cand[i].Ninsc,cand[i].nome,cand[i].nota,cand[i].situacao);
    }

    //fechar arquivo "saida"
    fclose(saida);

    //pausa+finalizacao
    system("pause");
    return 0;
}
