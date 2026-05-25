// aqui vai ser os utilitarios (verificar colchete aberto nao fechado, verificar sintaxe, verificar prioridade de operadores)

// prioridade 
// + ou - é 1
// * ou / é 2
// ^ é 3.
#ifndef UTILITARIOS_HPP
#define UTILITARIOS_HPP
#include <iostream>
using namespace std;
int prioridade(char operador) {
    if (operador == '+' || operador == '-') {
        return 1;
    }
    if (operador == '*' || operador == '/') {
        return 2;
    }
    if (operador == '^') {
        return 3;
    }
    return 0;  // caso default
}

// verifica se um caracter e um operador
// na string (que e um vetor de char) usaremos essa função pra ver se o elemento da string (que e um char) é um operador, se for, verificamos prioridade e ordenamos.
bool verificarOperador(char caracter) {
    return 
    caracter == '+' ||
    caracter == '-' ||
    caracter == '*' ||
    caracter == '/' ||
    caracter == '^';
} 

// verifica se o caractere na string que o usuario colocou (expressao) é uma abertura de delimitadores " ( , [ ou { "
bool verificarAbrir(char caracter) {
    
    return 
    caracter == '(' || 
    caracter == '[' || 
    caracter == '{';
    
}

bool corresponde(char abrir, char fechar) {
    return (abrir == '(' && fechar == ')') ||
           (abrir == '[' && fechar == ']') ||
           (abrir == '{' && fechar == '}');
}


// verifica se o caractere na string que o usuario colocou (expressao) é um fechamento de delimitadores " ) , ] ou } "
bool verificarFechar(char caracter) {
    
    return caracter == ')' || caracter == ']' || caracter == '}';
}// bora fazer lista dinamica, depois testa aas outra :)

bool verificarEspaco(char caracter) {
    return caracter == ' ';
}

void verificarVariaveis(string expressao, bool &temA, bool &temB, bool &temC) {

    temA = false;
    temB = false;
    temC = false;

    for (int i = 0; i < expressao.length(); i++) {

        if (expressao[i] == 'a' || expressao[i] == 'A') {
            temA = true;
        }

        if (expressao[i] == 'b' || expressao[i] == 'B') {
            temB = true;
        }

        if (expressao[i] == 'c' || expressao[i] == 'C') {
            temC = true;
        }
    }
}

// numeros de 0 a 9
bool verificarNumero(char caracter) {
    return caracter >= '0' && caracter <= '9';
}

// letras do alfabeto
bool verificarVariavel(char caracter) {
    return (caracter >= 'a' && caracter <= 'z') || (caracter >= 'A' && caracter <= 'Z');
}

double potencia(double base, double expoente) {
    if (expoente == 0) return 1;
    return base * potencia(base, expoente - 1);
}

#endif