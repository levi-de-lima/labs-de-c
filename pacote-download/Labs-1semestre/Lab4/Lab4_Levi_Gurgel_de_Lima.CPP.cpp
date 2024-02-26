/*  Levi Gurgel de Lima                      */
/*  Turma 3                                  */
/*  Exercício 4: Contador de dias            */
/*                                           */
/*  Programa compilado com CodeBlocks 17.12  */
#include <stdio.h>
#include <stdlib.h>
int main ()
{
    //declaracao de variaveis
        //contadores
    int i,
        n,
        dias;
        //dia, mes e ano inicial e final
    int di, mi, ai,
        df, mf, af;

    FILE * entrada;
    FILE * saida;

    //ecrever mensagem inicial na tela
    printf ("Inicio do programa.\n");

    //abrir arquivos de entrada e saida
    entrada = fopen ("entrada4.txt", "r");
    saida = fopen ("saida4.txt", "w");

    //escrever mensagem inicial no arquivo
    fprintf (saida, "Arquivo de saida. Lab 4.\n");
    fprintf (saida, "    Contador de dias:   \n");
    fprintf (saida, "     Ele conta dias     \n");
    fprintf (saida, "------------------------\n");

    //ler a quantidade n de casos
    fscanf (entrada, "%d", &n);

    //para cada um dos casos, fazer:
    for (i=1; i<=n; i++)
    {
        // ler os dias, meses e anos inicial e final
        fscanf (entrada, "%d %d %d %d %d %d", &di, &mi, &ai, &df, &mf, &af);

        //atribuicao inical para o contador de dias
        dias = 0;

        //contador de dias
        while (di != df || mi != mf || ai != af)
        {
            //enquanto di != df, fazer:
            if (di < df)
            {
                //para igualar di e df
                di = di + 1;
                //para contar os dias
                dias = dias + 1;
            }
            if (di > df)
            {
                //para igualar di e df
                di = di - 1;
                //para contar os dias
                dias = dias - 1;
            }
            //quando di == df, fazer:
            if (di == df)
            {
                //enquanto mi != mf, fazer:
                if (mi < mf)
                {
                //algumas correcoes no contador dos meses:
                    //fevereiro tem 28 dias
                    if (mi == 2)
                    {
                        dias = dias - 2;
                        //em ano bissexto, fevereiro tem 29 dias
                        //um ano e' bissexto se for divisivel por 4,
                        if (ai%4 == 0)
                        {
                            //se nao for divisivel por 100,
                            if (ai%100 != 0)
                            {
                                dias = dias + 1;
                            }
                            //ou, se for divisivel por 100, deve ser por 400 tambem
                            else if (ai%400 == 0)
                            {
                                dias = dias + 1;
                            }
                        }
                    }
                    //janeiro, marco, maio, julho, agosto, outubro e dezembro tem 31 dias
                    if (mi == 1 || mi == 3 || mi == 5 || mi == 7 || mi == 8 || mi == 10 || mi == 12)
                    {
                        dias = dias + 1;
                    }
                    //para igualar mi e mf
                    mi = mi + 1;
                    //para contar os dias
                    dias = dias + 30;
                }
                if (mi > mf)
                {
                //no caso de igualar mi com mf regressivamente,
                //o mes que e' considerado e' o anterior (mi-1)

                //algumas correcoes no contador dos meses:
                    //fevereiro tem 28 dias
                    if (mi-1 == 2)
                    {
                        dias = dias + 2;
                        if (ai%4 == 0)
                        {
                            if (ai%100 != 0)
                            {
                                dias = dias - 1;
                            }
                            else if (ai%400 == 0)
                            {
                                dias = dias - 1;
                            }
                        }
                    }
                    //janeiro, marco, maio, julho, agosto, outubro e dezembro tem 31 dias
                    if (mi-1 == 1 || mi-1 == 3 || mi-1 == 5 || mi-1 == 7 || mi-1 == 8 || mi-1 == 10 || mi-1 == 12)
                    {
                        dias = dias - 1;
                    }
                    //para igualar mi e mf
                    mi = mi - 1;
                    //para contar os dias
                    dias = dias - 30;
                }
                //quando mi == mf, fazer:
                if (mi == mf)
                {
                    //enquanto ai != af
                    if (ai < af)
                    {
                    //correcao devido aos anos bissextos
                        //se o ano e bissexto ele tem 366 dias

                        //ao igualar mi e mf, se mi for janeiro ou fevereiro, fazer:
                        if (mi <= 2)
                        {
                            //se ai for bissexto, somar 1 ao contador de dias
                            if (ai%4 == 0)
                            {
                                if (ai%100 != 0)
                                {
                                    dias = dias + 1;
                                }
                                else if (ai%400 == 0)
                                {
                                    dias = dias + 1;
                                }
                            }
                        }
                        //se mi for outro mes, fazer:
                        if (mi > 2)
                        {
                            //se o proximo ano (ai+1) for bissexto, somar 1 ao contador de dias
                            if ((ai+1)%4 == 0)
                        {
                            if ((ai+1)%100 != 0)
                            {
                                dias = dias + 1;
                            }
                            else if ((ai+1)%400 == 0)
                            {
                                dias = dias + 1;
                            }
                        }
                        }
                        //para igualar ai e af
                        ai = ai + 1;
                        //para contar os dias
                        dias = dias + 365;
                    }
                }
            }
        }
        //escrever o numero de dias no arquivo de saida
        fprintf (saida, "%2d:%7d dias.\n", i, dias);
    }
    //fechar arquivos de entrada e saida
    fclose (entrada);
    fclose (saida);
    //mensagem final na tela + pausa
    printf ("Fim do pragama.\n");
    system ("pause");
    //finalizar:
    return 0;
}
