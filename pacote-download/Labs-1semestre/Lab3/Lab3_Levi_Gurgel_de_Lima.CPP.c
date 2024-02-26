/*  Levi Gurgel de Lima                      */
/*  Turma 3                                  */
/*  Exercício 3: Conversor de Medidas        */
/*                                           */
/*  Programa compilado com CodeBlocks 17.12  */
#include <stdio.h>
#include <stdlib.h>
int main ()
{
    // declaracao de variaveis
    float numeroBR;
    char letra;
    int i, k, c, m,
        n,
        numeroUS;
    int polegadas,
        pes,
        jardas,
        milhas;
    int MaiorM,
        MenorT;

    FILE * entrada;
    FILE * saida;

    // escrever mensagem inicial na tela
    printf ("Inicio do programa.\n");

    // atribuicao inicial para algumas variaveis
    k=0, c=0, m=0, i=0;
    MaiorM=0, MenorT=2147483647;

    // abrir arquivos de entrada e saida
    entrada = fopen ("entrada3.txt", "r");
    saida = fopen ("saida3.txt", "w");

    // escrever mensagem inicial no arquivo
    fprintf (saida, "-------------------------------------\n");
    fprintf (saida, "          PROGRAMA CONVERSOR         \n");
    fprintf (saida, "           Arquivo de saida          \n");
    fprintf (saida, "-------------------------------------\n");

    // ler a quantidade n de casos
    fscanf (entrada, "%d", &n);

    //para cada um dos casos, fazer:
    while (i < n)
    {
        // ler um float e um char com a unidade
        fscanf (entrada, "%f %c", &numeroBR, &letra);
        // se unidade m (metros)
        if (letra == 'm' || letra == 'M')
        {
            // converter distancia:
            numeroUS = numeroBR*100/2.54;
            polegadas = numeroUS%12;
            pes = (numeroUS/12)%3;
            jardas = ((numeroUS/12)/3)%1760;
            milhas = ((numeroUS/12)/3)/1760;

            fprintf (saida, "%.2f metros =\n", numeroBR);
            fprintf (saida, "     %4d milhas +\n", milhas);
            fprintf (saida, "     %4d jardas +\n", jardas);
            fprintf (saida, "     %4d pes +\n", pes);
            fprintf (saida, "     %4d polegadas\n\n", polegadas);
            // contador da distancia
            m=m+1;
        }
        // se unidade k (kilogramas)
        if (letra == 'k' || letra == 'K')
        {
            // converter massa
            numeroUS = numeroBR/0.453592;

            fprintf (saida, "%.2f kilogramas =\n", numeroBR);
            fprintf (saida, "     %4d libras\n\n", numeroUS);
            // contador da massa
            k=k+1;
            // verifica se eh a maior ate o momento
            if (numeroUS>=MaiorM)
                MaiorM = numeroUS;
        }
        // se unidade c (celsius)
        if (letra == 'c' || letra == 'C')
        {
            // converter temperatura
            numeroUS = 9*numeroBR/5 + 32;

            fprintf (saida, "%.2f graus Celsius =\n", numeroBR);
            fprintf (saida, "     %4d graus Farenheit\n\n", numeroUS);
            // contador da temperatura
            c=c+1;
            // verifica se eh a menor ate o momento:
            if (numeroUS<=MenorT)
                MenorT = numeroUS;
        }
        i = i + 1;
    }
    // Ao terminar o arquivo de entrada,
    // escrever as informacoes "acumuladas" (a), (b) e (c)
    // Letra (a)
    fprintf (saida, "\n-------------------------------------\n");
    fprintf (saida, "(a) Quantidade de casos de cada tipo:\n");
    fprintf (saida, "    Massa      : %d vezes.\n", k);
    fprintf (saida, "    Temperatura: %d vezes.\n", c);
    fprintf (saida, "    Distancia  : %d vezes.\n\n", m);
    // Letra (b)
    if (MaiorM != 0)
    {
    fprintf (saida, "(b) Qual a maior massa:\n");
    fprintf (saida, "    %d libras.\n\n", MaiorM);
    }
    else fprintf (saida, "(b) Nao ocorre.\n\n");
    // Letra (c)
    if (MenorT != 0)
    {
    fprintf (saida, "(c) Qual a menor temperatura:\n");
    fprintf (saida, "    %d graus Farenheit.\n\n", MenorT);
    }
    else fprintf (saida, "(c) Nao ocorre.\n\n");

    fprintf (saida, "-------------------------------------\n");
    fprintf (saida, "Fim do arquivo.");

    // fechar arquivos de entrada e saida
    fclose (entrada);
    fclose (saida);
    // mensagem final na tela + pausa:
    printf ("Fim do programa.\n");
    system ("pause");
    // finalizar:
    return 0;
}
