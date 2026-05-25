#ifndef EXPRESSAO_HPP
#define EXPRESSAO_HPP
#include <iostream>
#include "./utilitarios.hpp"
using namespace std;

// Repare que adicionamos o 'template' antes da função para aceitar QUALQUER Pilha
template <typename TPilha>
bool verificarSintaxe(string &expressao)
{
    if (expressao.empty()) return false;

    TPilha pilha; // Cria a pilha do tipo que o main escolheu
    inicializar(pilha);

    int tamanhoExpressao = expressao.length();
    bool esperaOperando = true;
    bool temOperando = false;

    for (int i = 0; i < tamanhoExpressao; i++)
    {
        char caracter = expressao[i];
        if (verificarEspaco(caracter)) continue;

        if (verificarAbrir(caracter)) {
            if (!esperaOperando) { liberar(pilha); return false; }
            push(pilha, caracter);
        }
        else if (verificarFechar(caracter)) {
            if (vazia(pilha)) { liberar(pilha); return false; }
            if (esperaOperando) { liberar(pilha); return false; }
            char topo;
            top(pilha, topo);
            if (!corresponde(topo, caracter)) { liberar(pilha); return false; }
            char esquece; pop(pilha, esquece);
        }
        else if (verificarOperador(caracter)) {
            if (esperaOperando) { liberar(pilha); return false; }
            esperaOperando = true;
        }
        else if (verificarNumero(caracter)) {
            if (!esperaOperando) { liberar(pilha); return false; }
            while (i < tamanhoExpressao && verificarNumero(expressao[i])) { i++; }
            i--;
            esperaOperando = false;
            temOperando = true;
        }
        else if (verificarVariavel(caracter)) {
            if (!esperaOperando) { liberar(pilha); return false; }
            esperaOperando = false;
            temOperando = true;
        }
    }
    bool resultadoDelimitadores = vazia(pilha);
    bool resultadoSeq = !esperaOperando && temOperando;
    liberar(pilha);
    return resultadoDelimitadores && resultadoSeq;
}

struct Token {
    char tipo;
    string valor;
};

// Aceita QUALQUER tipo de Fila de Tokens
template <typename TFila>
void tiraTokens(string &expressao, TFila &tokens)
{
    int tamanhoExpressao = expressao.length();
    for (int i = 0; i < tamanhoExpressao; i++)
    {
        char caracter = expressao[i];
        if (verificarEspaco(caracter)) continue;

        Token token;
        if (verificarNumero(caracter)) {
            string numero = "";
            while (i < tamanhoExpressao && verificarNumero(expressao[i])) {
                numero += expressao[i];
                i++;
            }
            i--;
            token.tipo = 'N'; token.valor = numero;
            queue(tokens, token);
        }
        else if (verificarVariavel(caracter)) {
            token.tipo = 'V'; token.valor = caracter;
            queue(tokens, token);
        }
        else if (verificarOperador(caracter)) {
            token.tipo = 'O'; token.valor = caracter;
            queue(tokens, token);
        }
        else if (verificarAbrir(caracter)) {
            token.tipo = 'A'; token.valor = caracter;
            queue(tokens, token);
        }
        else if (verificarFechar(caracter)) {
            token.tipo = 'F'; token.valor = caracter;
            queue(tokens, token);
        }
    }
}

// Passamos por Template a Pilha e Fila escolhidas no main
template <typename TPilha, typename TFila>
string converterPraPolenesa(string &expressao)
{
    if (!verificarSintaxe<TPilha>(expressao)) // Repassa o tipo de pilha
        return "Expressao incorreta ";

    TPilha operadores;
    inicializar(operadores);

    TFila tokens;
    inicializar(tokens);

    tiraTokens(expressao, tokens);

    string resultado = "";
    while (!vazia(tokens))
    {
        Token token;
        dequeue(tokens, token);

        if (token.tipo == 'N' || token.tipo == 'V') {
            resultado += token.valor + " ";
        }
        else if (token.tipo == 'O') {
            while (!vazia(operadores)) {
                char topo;
                top(operadores, topo);
                if (!(verificarAbrir(topo)) && (prioridade(topo) > prioridade(token.valor[0]) || (prioridade(topo) == prioridade(token.valor[0]) && token.valor[0] != '^'))) {
                    resultado += topo; resultado += " ";
                    char esquece; pop(operadores, esquece);
                } else {
                    break;
                }
            }
            push(operadores, token.valor[0]);
        }
        else if (token.tipo == 'A') {
            push(operadores, token.valor[0]);
        }
        else if (token.tipo == 'F') {
            while (!vazia(operadores)) {
                char topo; top(operadores, topo);
                if (verificarAbrir(topo)) {
                    if (corresponde(topo, token.valor[0])) {
                        char esquece; pop(operadores, esquece);
                        break;
                    } else {
                        liberar(operadores); liberar(tokens);
                        return "Erro: delimitadores incompativeis";
                    }
                }
                resultado += topo; resultado += " ";
                char esqueca; pop(operadores, esqueca);
            }
        }
    }

    while (!vazia(operadores)) {
        char topo; top(operadores, topo);
        resultado += topo; resultado += " ";
        char esquecer; pop(operadores, esquecer);
    }

    liberar(operadores); liberar(tokens);
    if (!resultado.empty()) resultado.pop_back();
    return resultado;
}

template <typename TPilha>
double calcular(string &expressaoPolonesa, char variaveis[], double valores[], int tamanho)
{
    TPilha pilha;
    inicializar(pilha);
    string token = "";
    int tamanhoExpressao = expressaoPolonesa.length();

    for (int i = 0; i <= tamanhoExpressao; i++)
    {
        char caracter = (i < tamanhoExpressao) ? expressaoPolonesa[i] : ' ';
        if (caracter == ' ') {
            if (!token.empty()) {
                if (verificarNumero(token[0])) {
                    push(pilha, stod(token));
                }
                else if (verificarVariavel(token[0])) {
                    double valor = 0;
                    for (int j = 0; j < tamanho; j++) {
                        if (variaveis[j] == token[0]) { valor = valores[j]; break; }
                    }
                    push(pilha, valor);
                }
                else if (verificarOperador(token[0])) {
                    double b, a;
                    pop(pilha, b); pop(pilha, a);
                    double res = 0;
                    if (token[0] == '+') res = a + b;
                    else if (token[0] == '-') res = a - b;
                    else if (token[0] == '*') res = a * b;
                    else if (token[0] == '/') { if (b == 0) { liberar(pilha); return 0; } res = a / b; }
                    else if (token[0] == '^') res = potencia(a, b);
                    push(pilha, res);
                }
                token = "";
            }
        } else {
            token += caracter;
        }
    }
    double resultado = 0; pop(pilha, resultado); liberar(pilha);
    return resultado;
}

void tiraVariaveis(string &expressao, string &vars); // assinatura mantida
#endif
