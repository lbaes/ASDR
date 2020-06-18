/*  
    ASDR - Analisador Sintático Descendente Recursivo Preditivo

    Entrega de trabalho - Nome do trabalho

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

    palavras = "((1 + 2) + 3) => F => (E) => (TA) => (FBA) => ((E)BA) => ((TA)BA) 
                =>((FBA)BA) => ((1+TA)BA) => ((1+FBA)BA) => ((1+2BA)BA) => 
                ((1+2A)BA) => ((1+2)BA) => 
                ((1+2)+TA) => ((1+2)+FBA) => 
                ((1+2)+3BA) => ((1+2)+3A) => ((1+2)+3)
    
    p2 = "(15+2)" => F (E) => (TA) => (FBA) => (1BA) => (1A) => (1)
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

    if (argc < 2){
        //palavra = "((1+2)*(3*4)+5+6)";    //ok
        //palavra = "((1+2)*3)";            //ok
        //palavra = "(1+2+3+4+5+6+7+8+9)";  //ok
        palavra = "1*2+3";
    }else{
        palavra = argv[1];
    }
    
    pstart = palavra;

    E(&palavra);
    if (*palavra == '\0')
    {
        printf("%s aceita..\n", pstart);
    }
    else
    {
        printf("%s houve um erro..\n", pstart);
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
            printf("Expected ) but found %c !!\n", **palavra);
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
        printf("Expected symbol but found <empty> !!\n");
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
        printf("Expected a symbol but found <empty> !!\n");
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
        printf("Expected a symbol but found <empty> !!\n");
        exit(EXIT_FAILURE);
    }
}
