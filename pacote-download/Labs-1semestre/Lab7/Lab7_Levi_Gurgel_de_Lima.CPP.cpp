/*  Levi Gurgel de Lima                      */
/*  Turma 3                                  */
/*  Exercício 4: Bases numericas             */
/*                                           */
/*  Programa compilado com CodeBlocks 17.12  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main ()
{
    //declaracao de variaveis
    //auxiliares
    char lixo [100],
         aux[100];
    int i;
    //numeros de entrada e saida
    char numeroEntra[100],
         numeroSai[100];
    //bases de entrada e saida
    int BaseEntra,
        BaseSai;
    //variaveis intermediarias (usadas na transformacao para decimal)
    int resto,
        decimal;
    //contqadores
    int j,k,n;
    //arquivos
    FILE * entrada;
    FILE * saida;

    //abrir arquivos de entrada e saida
    entrada = fopen ("entrada7.txt", "r");
    saida = fopen ("saida7.txt", "w");

    //ecrever mensagem inicial na tela
    printf ("Inicio do programa.\n");

    //"descartar" as 4 primeiras linhas, colocando-as em lixo
    fgets (lixo, 100, entrada);
    fgets (lixo, 100, entrada);
    fgets (lixo, 100, entrada);
    fgets (lixo, 100, entrada);

    //escrever mensagem inicial no arquivo
    fprintf (saida, "Por que o programador confunde o natal com o halloween?\n");
    fprintf (saida, "Porque 25 dec = 31 oct.\n");
    fprintf (saida, "2.10 + 5 = 3.8 + 1\n");
    fprintf (saida, "----\n");

    //atribuicao inicial de n
    n=1;
    //enquanto o arquivo nao chegar ao fim, fazer
    while (!feof(entrada))
    {
        //ler base de entrada, base de saida e numero de entrada
        fscanf (entrada, "%d ", &BaseEntra);
        fscanf (entrada, "%d ", &BaseSai);
        fscanf (entrada, "%s", &numeroEntra);

        //se o primeiro char for um algarismo
        if (numeroEntra[0]<'A')
        //converter char para int e armazenar em 'decimal'
        decimal = numeroEntra[0]-'0';
        //se for letra
        //converter char para int e armazenar em 'decimal'
        else decimal = numeroEntra[0]-'A'+10;

        //definindo i como o tamanho do numero de entrada
        i = strlen (numeroEntra);
        //enquanto j for menor que o tamanho do numero de entrada
        for (j=1;j<i;j++)
        {
            //se for algarismo
            if (numeroEntra [j]<'A')
            //transformar o numero para decimal
            decimal = BaseEntra*(decimal) + (numeroEntra[j]-'0');
            //se for letra
            //transformar a letra para decimal
            else decimal = BaseEntra*(decimal) + (numeroEntra[j]-'A'+10);
        }
        //atribuicao inicial para k
        k=0;
        //enquanto decimal nao for zero
        while (decimal!=0)
        {
            //transformar de decimal para a base de saida atraves do metodo de divisoes
            resto = decimal%BaseSai;
            //se resto maior ou igual a 10
            if (resto>=10)
            {
                //transfor o numero em letra
                resto = resto - 10 + 'A';
                //guardar no numero de saida
                numeroSai[k] = resto;
            }
            //se resto menor que 10
            else
            {
                //guardar no numero de saida
                numeroSai[k] = resto + '0';
            }
            decimal = decimal/BaseSai;
            k=k+1;
        }
        //considerando o caso numero de entrada igual a zero
        if (k==0)
            strcpy (numeroSai, "0");
        //adicionar marca de fim de string apos o ultimo algarismo do numero de saida
        else numeroSai[k]='\0';

        //escrever a numeracao no arquivo de saida
        fprintf (saida, "%2d: ", n);

        //devido ao metodo de divisao, numeroSai é o numero de saida invertido
        //para desinverter
        for (i=strlen(numeroSai)-1;i>=0;i--)
        {
            fprintf (saida, "%c", numeroSai[i]);
        }
        fprintf (saida, "\n");
        n++;
    }

    //fechar a entrada e a saida
    fclose (entrada);
    fclose (saida);

    //mensagem final na tela + pausa
    printf ("Fim do programa.\n");
    system ("pause");
    //finalizar
    return 0;
}
