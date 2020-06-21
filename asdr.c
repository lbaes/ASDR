/*  
    ASDR - Analisador Sintático Descendente Recursivo Preditivo

    Nós,

    Lucas Franchini Baes 31849202
    Zewu Chen            31808751

    declaramos que

    todas as respostas são fruto de nosso próprio trabalho,
    não copiamos respostas de colegas externos à equipe,
    não disponibilizamos nossas respostas para colegas externos à equipe e
    não realizamos quaisquer outras atividades desonestas para nos beneficiar ou prejudicar outros.


    Gramatica:

    E ::= TA
    A ::= +TA | lambda
    T ::= FB
    B ::= *FB | lambda
    F ::= (E) | num

    onde num = [0-9], ou seja, 0 | 1 | 2 | 3 | .. | 9

    Terminais    = {(, ), *, +, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
    ~N-Terminais = {E, A, T, B, F}

    FIRST(F) = {(, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
    FIRST(B) = {*, lambda}
    FIRST(A) = {+, lambda}
    FIRST(T) = {(, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
    FIRST(E) = {(, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}

    Exemplos de palavras reconhecidas
        (1*(2))
        (1+2)
        1*(2+3)

    
    Exemplos de palavras nao reconhecidas :
        (1*(2+3)
        1+(A))
        (7+7)*)3
        15+20
        15*56

*/

#include <stdio.h>
#include <stdlib.h>

void E(char **palavra);
void A(char **palavra);
void T(char **palavra);
void B(char **palavra);
void F(char **palavra);

int main(int argc, char *argv[])
{
    char *pstart;
    char *palavra;

    // Se nao recebeu uma palavra pelo argumento use a padrao
    if (argc < 2){
        //palavra = (1*(2));
        //palavra = (1+2);
        palavra = "1*(2+3)";
    }else{
        palavra = argv[1];
    }
    
    pstart = palavra;

    E(&palavra);
    if (*palavra == '\0')
    {
        printf("%s foi aceita\n", pstart);
    }
    else
    {
        printf("%s nao foi aceita, houve um erro\n", pstart);
    }
    return 0;
}

void F(char **palavra)
{
    switch (**palavra)
    {
    case '(':
        (*palavra)++;
        E(palavra);
        if (**palavra == ')')
        {
            (*palavra)++;
        }
        else
        {
            printf("ERRO!! Esperava um ) mas encontrei %c !!\n", **palavra);
            exit(EXIT_FAILURE);
        }
        break;
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        (*palavra)++;
        break;
    default:
        printf("ERRO!! Esperava um simbolo mas achei %c !!\n", **palavra);
        exit(EXIT_FAILURE);
    }
}

void B(char **palavra)
{
    switch (**palavra)
    {
    case '*':
        (*palavra)++;
        F(palavra);
        B(palavra);
        break;
    default:
        break;
    }
}

void T(char **palavra)
{
    switch (**palavra)
    {
    case '(':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        F(palavra);
        B(palavra);
        break;
    default:
        printf("ERRO!! Esperava um simbolo mas achei %c !!\n", **palavra);
        exit(EXIT_FAILURE);
    }
}

void A(char **palavra)
{
    switch (**palavra)
    {
    case '+':
        (*palavra)++;
        T(palavra);
        A(palavra);
        break;
    default:
        break;
    }
}

void E(char **palavra)
{
    switch (**palavra)
    {
    case '(':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        T(palavra);
        A(palavra);
        break;
    default:
        printf("ERRO!! Esperava um simbolo mas achei %c !!\n", **palavra);
        exit(EXIT_FAILURE);
    }
}
