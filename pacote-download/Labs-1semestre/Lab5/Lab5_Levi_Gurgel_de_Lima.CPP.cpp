/*  Levi Gurgel de Lima                      */
/*  Turma 3                                  */
/*  Exercício 4: Sobremesa                   */
/*                                           */
/*  Programa compilado com CodeBlocks 17.12  */
#include <stdio.h>
#include <stdlib.h>
int main ()
{
    //declaracao de variaveis
    //bolos, gelatinas, frutas e sorvetes
    int b,g,f,s;

    FILE * entrada;
    FILE * saida;

    //abrir arquivos de entrada e saida
    entrada = fopen ("entrada5.txt","r");
    saida = fopen ("saida5.txt","w");

    //ecrever mensagem inicial na tela
    printf ("Inicio do programa\n");

    //escrever mensagem inicial no arquivo
    fprintf (saida, "Confeitaria da Mariazinha\n");
    fprintf (saida, "Panela boa e' que faz comida velha\n");
    fprintf (saida, "Os pedidos dos clientes foram:\n");
    fprintf (saida, "-----\n");

    //enquanto o arquivo nao chegar ao fim, fazer
    while (!feof(entrada)){
    fscanf (entrada, "%d %d %d %d ", &b, &g, &f, &s);
    //se bolos maior que zero
    if (b!=0){
        //escrever "b bolo" no arquivo
        fprintf (saida, "%d bolo", b);
        //adicionar plural
        if (b!=1)
            fprintf (saida, "s");

        //adicionar "continuacao"
        //se os 3 são nulos
        if (f==0 && g==0 && s==0)
            fprintf (saida, ".");
        //se 1 ou nenhum e' nulo
        else if (f*s!=0 || g*s!=0 || f*g!=0)
            fprintf (saida, ", ");
        //se apenas 1 e' nao nulo
        else fprintf (saida, " e ");
    }
    //se gelatinas maior que zero
    if (g!=0){
        //escrever "g gelatina" no arquivo
        fprintf (saida, "%d gelatina", g);
        //adicionar plural
        if (g!=1)
            fprintf (saida, "s");

        //adicionar "continuacao"
        //se os dois são nulos
        if (f==0 && s==0)
            fprintf (saida, ".");
        //se os dois são não nulos
        else if (f*s!=0)
            fprintf (saida, ", ");
        //se um dos dois e' nulo
        else fprintf (saida, " e ");
    }
    //se frutas maior que zero
    if (f!=0){
        //escrever "f fruta" no arquivo
        fprintf (saida, "%d fruta", f);
        //adiconar plural
        if (f!=1)
            fprintf (saida, "s");

        //adicionar "continuacao"
        //se s for nulo
        if (s==0)
            fprintf (saida, ".");
        //se s não nulo
        else fprintf (saida, " e ");
    }
    //se sorvetes maior que zero
    if (s!=0){
        //escrever "s sorvete" no arquivo
        fprintf (saida, "%d sorvete", s);
        //adicionar plural
        if (s!=1)
            fprintf (saida, "s");

        //em qualquer caso, escrever o ponto final
        fprintf (saida, ".");
    }
    //adicionar ENTER
    fprintf (saida, "\n");
    }
    //fechar arquivos de entrada e saida
    fclose (entrada);
    fclose (saida);
    //mensagem final na tela + pausa
    printf ("Fim do programa.\n");
    system ("pause");
    //finalizar
    return 0;
}
