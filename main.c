#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define TOK_NUM 0
#define TOK_OP 1
#define TOK_PONT 2

#define SOMA 0 
#define SUB 1
#define MULT 2
#define DIV 3
#define DIVINT 4

#define PARESQ 0
#define PARDIR 1
#define CHAESQ 2
#define CHADIR 3
#define COLESQ 4
#define COLDIR 5

char *codigo;
int tamanho; 
int pos;

const char *ops = "+-*/\\";
const char *pts = "(){}[]";

typedef struct {
    int tipo;
    int valor;
} Token;

void inicializa_analise(char *prog)
{
    codigo = prog;
    tamanho = strlen(codigo);
    pos = 0;
}

char *operador_str(int op) {
    char *res;
    
    switch (op) {
        case SOMA:
            res = "SOMA";
            break;
        case SUB:
            res = "SUB";
            break;
        case MULT:
            res = "MULT";
            break;
        case DIV:
            res = "DIV";
            break;
        case DIVINT:
            res = "DIVINT";
            break;
        default:
            res = "NENHUM";
    }
    
    return res;
}

char *pontuacao_str(int pt) {
    char *res;
    
    switch (pt) {
        case PARESQ:
            res = "PARESQ";
            break;
        case PARDIR:
            res = "PARDIR";
            break;
        case CHAESQ:
            res = "CHAESQ";
            break;
        case CHADIR:
            res = "CHADIR";
            break;
        case COLESQ:
            res = "COLESQ";
            break;
        case COLDIR:
            res = "COLDIR";
            break;
        default:
            res = "NENHUM";
    }
    
    return res;
}

void imprime_token(Token *tok)
{
    printf("Tipo: ");
    switch (tok->tipo) {
        case TOK_NUM:
            printf("Numero\t -- Valor: %d\n", tok->valor);
            break;
        case TOK_OP:
            printf("Operador\t -- Valor: %s\n", operador_str(tok->valor));
            break;
        case TOK_PONT:
            printf("Pontuação\t -- Valor: %s\n", pontuacao_str(tok->valor));
            break;
        default:
            printf("TIPO DE TOKEN DESCONHECIDO\n");
    }
}

int operador(char c)
{
    int res;
    
    switch(c) {
        case '+':
            res = SOMA;
            break;
        case '-':
            res = SUB;
            break;
        case '*':
            res = MULT;
            break;
        case '/':
            res = DIV;
            break;
        case '\\':
            res = DIVINT;
            break;
        default:
            res = -1;
    }
    
    return res;
}

int pontuacao(char c)
{
    int res;
    
    switch(c) {
        case '(':
            res = PARESQ;
            break;
        case ')':
            res = PARDIR;
            break;
        case '{':
            res = CHAESQ;
            break;
        case '}':
            res = CHADIR;
            break;
        case '[':
            res = COLESQ;
            break;
        case ']':
            res = COLDIR;
            break;
        default:
            res = -1;
    }
    
    return res;
}

char le_caractere(void)
{
    char c;
    
    if (pos < tamanho) {
        c = codigo[pos];
        pos++;
    } else {
        c = -1;
    }
    
    return c;
}

Token *proximo_token(Token *tok)
{
    char c;
    char valor[200];
    int vpos = 0;
    
    c = le_caractere();
    
    while (isspace(c)) {
        c = le_caractere();
    }
    
    if (isdigit(c)) {
        tok->tipo = TOK_NUM;
        valor[vpos++] = c;
        c = le_caractere();
        while (isdigit(c)) {
            valor[vpos++] = c;
            c = le_caractere();
        }
        pos--;
        valor[vpos] = '\0';
        tok->valor = atoi(valor);
    } else if (strchr(ops, c) != NULL) {
        tok->tipo = TOK_OP;
        tok->valor = operador(c);
    } else if (strchr(pts, c) != NULL) {
        tok->tipo = TOK_PONT;
        tok->valor = pontuacao(c);
    } else {
        return NULL;
    }
    
    return tok;
}

int main()
{
    char entrada[200];
    Token tok;
    
    printf("Analise Lexica para Expressoes\n");
    
    printf("Expressao: ");
    fgets(entrada, 200, stdin);
    
    inicializa_analise(entrada);
    
    printf("\n --- Analise ---\n");
    
    while(proximo_token(&tok) != NULL) {
        imprime_token(&tok);
    }
    
    printf("\n");
    
    return 0;
}
