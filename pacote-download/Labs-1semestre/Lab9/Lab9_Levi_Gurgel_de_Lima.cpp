/*  Levi Gurgel de Lima                      */
/*  Turma 3                                  */
/*  Exercício 9: Funcoes                      */
/*                                           */
/*  Programa compilado com CodeBlocks 17.12  */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define boolean int
//funcao que calcula juros simples ou compostos conforme indicacao do tipo
float juros (float montante, float pcento, int meses, char tipo)
{
    //declaracao de variaveis
    float dinheiro=montante; //inicializacao de dinheiro
    int i=0;
    //se for juros simples
    if (tipo == 's'|| tipo == 'S')
    {
        //calcula o resultado com juros simples
        dinheiro=montante*(1+(pcento*1.0/100)*meses);
        //retorna o resultado
        return dinheiro;
    }
    //se for juros compostos
    if (tipo == 'c'|| tipo == 'C')
    {
        //enqunato o contador for menor que o numero de meses
        while(i<meses)
        {
            //calcular o resultado com juros compostos
            dinheiro=dinheiro*(1+(pcento*1.0/100));
            //incremento no contador
            i++;
        }
        //retorna o resultado
        return dinheiro;
    }
}
//funcao que calcula a media entre dois numeros float
float media (float n1, float n2)
{
    //declaracao da variavel da media
    float m;
    //calculo da media
    m=(n1+n2)*0.5;
    //retorna a media
    return m;
}
//funcao que, dado um numero, calcula o proximo multiplo de 26
void pmvs (int*n)
{
    //para os casos (n>=0) e (n<0 divisivel por 26)
    if (*n>=0||(*n%26)==0)
        //calcular o proximo multiplo
        *n=((*n/26)+1)*26;
    //para o caso n<0 nao divisivel por 26
         //calcular o proximo multiplo
    else *n=(*n/26)*26;
}
//funcao que, dado uma string, devolve TRUE se e' um numero valido em hexadecimal e FALSE se nao
int hexa (char*S)
{
    //declçaracao de variaveis
    boolean b=TRUE;
    //percorrer a string
    for(int i=0;i<strlen(S);i++)
    {
        //se houver algum caractere invalido
        if (!((S[i]>='a'&&S[i]<='f')||(S[i]>='A'&&S[i]<='F')||(S[i]>='0'&&S[i]<='9')))
            //a booleana vira FALSE
            b=FALSE;
        //se nao houver nenhum caractere invalido
             //se tiver alguma letra minuscula
        else if (islower(S[i]))
            {
                //transformar em letra maiuscula
                S[i]=toupper(S[i]);
            }
    }
    //retorna a booleana
    return b;
}
//funcao que escreve a mensagem inicial na tela
void mensagem_inicial_na_tela ()
{
    printf ("Inicio do programa\n");
}
//funcao que escreve a mensagem final na tela e executa a pausa
void mensagem_final_na_tela_e_pausa ()
{
    printf ("Fim do programa\n");
    system ("pause");
}
int main ()
{
    //declaracao de variaveis
    //variaveis gerais
    int j=1;    //contador de numeros de ordem
    char lixo[100],
         palavra[100];
    //variaveis "juros"
    float quantia,
          porcent,
          Nmes,
          total;
    char type;
    //variaveis "media"
    float numero1,
          numero2,
          avg;  //average, media em ingles
    //variaveis "pmvs"
    int numero;
    //variaveis "hexa"
    char str[100];
    int tam;    //tamanho
    boolean EhHexa;

    //arquivos
    FILE*entrada;
    FILE*saida;

    //abrir arquivos de entrada e saida
    entrada=fopen("entrada9.txt","r");
    saida=fopen("Lab9_Levi_Gurgel_de_Lima.txt","w");

    //ecrever mensagem inicial na tela
    mensagem_inicial_na_tela();

    //escrever mensagem inicial no arquivo
    fprintf (saida, "Lab                  \n");
    fprintf (saida, "    de funcoes       \n");
    fprintf (saida, "               abaixo\n");
    fprintf (saida, "----------\n");

    //ler as 4 primeiras linhas e colocar na variavel "lixo"
    fgets (lixo, 100, entrada);
    fgets (lixo, 100, entrada);
    fgets (lixo, 100, entrada);
    fgets (lixo, 100, entrada);

    //enquanto o arquivo nao chegar ao fim, fazer
    while (!feof(entrada))
    {
        //ler a primeira palavra
        fscanf (entrada, "%s ", &palavra);
        //se a palavra for "juros"
        if (strcmp(palavra,"juros")==0)
        {
            //ler "R$" e colocar em lixo
            fscanf (entrada,"%s ", &lixo);
            //ler a quantia de dinheiro
            fscanf (entrada,"%f ", &quantia);
            //ler a porcentagem
            fscanf (entrada,"%f ", &porcent);
            //ler o sinal "%" e colocar em lixo
            fscanf (entrada,"%s ", &lixo);
            //ler numero de meses
            fscanf (entrada,"%f ", &Nmes);
            //ler o tipo do juros
            fscanf (entrada,"%c ", &type);
            //chamar a funcao juros e armazenar o retorno em total
            total=juros (quantia, porcent, Nmes, type);
            //escrever o valor total na tela precedido pelo numero de ordem
            fprintf (saida, "%2d: R$ %.2f\n",j, total);
        }
        //se a palavra for "media"
        if (strcmp(palavra,"media")==0)
        {
            //ler o primeiro numero
            fscanf (entrada,"%f ", &numero1);
            //ler o segundo numero
            fscanf (entrada,"%f ", &numero2);
            //chamar a funcao media e armazenar a media em avg
            avg=media(numero1,numero2);
            //escrever a media na tela precedido pelo numero de ordem
            fprintf (saida, "%2d: %.2f\n",j, avg);
        }
        //se a palavra for "pmvs"
        if (strcmp(palavra,"pmvs")==0)
        {
            //ler o numero
            fscanf (entrada,"%d ", &numero);
            //chamar a funcao pmvs, o resultado fica armazenado em "numero"
            pmvs(&numero);
            //escrever o proximo multiplo de 26 precedido pelo numero de ordem
            fprintf (saida, "%2d: %d\n",j, numero);
        }
        //se a aplavra for "hexa"
        if (strcmp(palavra,"hexa")==0)
        {
            //ler a string dada
            fscanf (entrada,"%s ", &str);
            //chamar a funcao hexa que retorna, na variavel EhHexa, 1 se o numero e' valido e 0 se nao for
            EhHexa=hexa(str);
            //se o numero e' valido em hexadecimal
            if (EhHexa)
                //escrever o numero, dizendo que e' valido, precedido pelo numero de ordem
                fprintf (saida, "%2d: %s em hexadecimal eh valida\n",j, str);
            //se o numero nao e' valido em hexadecimal
                 //escrever o numero, dizendo que nao e' valido, precedido pelo numero de ordem
            else fprintf (saida, "%2d: %s em hexadecimal nao eh valida\n",j, str);
        }
        //incremento no numero de ordem
        j++;
    }

    //fechar os arquivos de entrada e saida
    fclose (entrada);
    fclose (saida);

    //chamar a funcao que escreve a mensagem final na tela + pausa
    mensagem_final_na_tela_e_pausa();
    //finalizar
    return 0;
}
