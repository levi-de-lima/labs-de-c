/*  Levi Gurgel de Lima                      */
/*  Turma 3                                  */
/*  Exercício 4: Strings                     */
/*                                           */
/*  Programa compilado com CodeBlocks 17.12  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main ()
{
    //declaracao de variaveis
    //colunas do arquivo de entrada
    char pasta [100],
         arquive [100],
         palavra [100];
    //caracteres "inuteis" serao colocados em:
    char lixo [100];
    //variaveis auxiliares
    char aux [100],
         aux2 [100],
         word [100];
    //contadores
    int i, j;
    //arquivos
    FILE * saida;
    FILE * entrada;
    FILE * arquivo;

    //abrir arquivos de entrada e saida
    entrada = fopen ("entrada6.txt", "r");
    saida = fopen ("saida6.txt", "w");

    //ecrever mensagem inicial na tela
    printf ("Inicio do programa.\n");

    //"descartar" as 7 primeiras linhas colocando-as em lixo
    fgets (lixo,100,entrada);
    fgets (lixo,100,entrada);
    fgets (lixo,100,entrada);
    fgets (lixo,100,entrada);
    fgets (lixo,100,entrada);
    fgets (lixo,100,entrada);
    fgets (lixo,100,entrada);

    //escrever mensagem inicial no arquivo
    fprintf (saida, "Senhoras e senhores,\n");
    fprintf (saida, "É com grande honra que vos apresento\n");
    fprintf (saida, "O lab mais dificil da historia.\n");
    fprintf (saida, "----------------------------------------\n");

    //enquanto o arquivo nao chegar ao fim, fazer
    while (!feof(entrada))
    {
        //atribuicao inicial para os contadores
        i=0;
        j=0;
        fscanf (entrada,"%s ", &lixo);
        //para garantir que a ultima linha nao seja impressa
        if (strcmp(lixo, "---------------------------------------------------------------")!=0)
        {
            //ler a pasta
            fscanf (entrada,"%s ", &pasta);
            //se tiver "=" repetir o anterior
            if (strcmp(pasta, "=")==0)
            {
                strcpy (pasta, aux);
                //somar 1 ao contador j para verificacao postertior
                j=j+1;
            }
            //ler "|" de separacao
            fscanf (entrada,"%s ", &lixo);
            //ler o arquivo
            fscanf (entrada,"%s ", &arquive);
            //se tiver "=" repetir o anterior
            if (strcmp(arquive, "=")==0)
            {
                strcpy (arquive, aux2);
                //somar 1 ao contador j para verificacao postertior
                j=j+1;
            }
            //ler "|" de separacao
            fscanf (entrada,"%s ", &lixo);
            //ler a palavra
            fscanf (entrada,"%s ", &palavra);
            //ler "|" de separacao
            fscanf (entrada,"%s ", &lixo);

            //armazenar os valores nas variaveis auxiliares para repeti-los no caso "="
            strcpy (aux, pasta);
            strcpy (aux2, arquive);

            //concatencao de strings para formar o endereco
            strcat (pasta, "\\");
            strcat (pasta, arquive);
            strcat (pasta, ".txt");

            //verificacao de j para escrever cada endereco apenas uma vez
            if (j!=2)
            fprintf (saida, "\n%s \n", pasta);

            arquivo = fopen (pasta, "r");

            //se existe o arquivo
            if (fopen(pasta, "r")!=0)
            {
              while (!feof(arquivo))
                {
                    //ler as palavras e armazenar na variavel auxiliar "word"
                    fscanf (arquivo, "%s ",&word);
                    //se word igual a palavra, contar +1 ocorrencia
                    if(strcmp (word, palavra)==0)
                    {
                        i=i+1;
                    }
                }
                //escrever "palavra: n ocorrencias" no arquivo de saida
                fprintf (saida, "\t%s: %d ocorrencias\n", palavra, i);
            }
            //se nao existe o arquivo
            //verificacao de j para que a mensagem apareca uma vez para cada endereco
            else if (j==2)
            {
                fprintf (saida, "\tARQUIVO NAO ENCONTRADO.\n", palavra, i);
            }
            //fechar arquivo
            fclose(arquivo);
        }
    }

    //fechar a entrada e a saida
    fclose(saida);
    fclose(entrada);

    //mensagem final na tela + pausa
    printf ("Fim do programa.\n");
    system ("pause");
    //finalizar
    return 0;
}
