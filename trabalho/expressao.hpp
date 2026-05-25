// aqui vai ser o arquivo pra ajudar a manipular a expressao que o usuario mandou, numeros e variaveis -> fila,
// operadores -> pilha

// esse arquivo vai usar bastante os utilitarios pra verificação
#ifndef EXPRESSAO_HPP
#define EXPRESSAO_HPP
#include <iostream>
#include "./utilitarios.hpp"
// #include "../pilhas/pilhadinamica.hpp"
// #include "../filas/filadinamica.hpp"
 #include "../pilhas/pilhaestatica.hpp"
 #include "../filas/filaestatica.hpp"
// #include "../filas/filacircular.hpp"
using namespace std;

// o usuario digitou uma expressao -> string
// pegar todos os elementos na expressao ? fazer verificacoes o ordenar ela pra podermos ter um retorno que vai ser em notação polonesa.
bool verificarSintaxe(string &expressao)
{
    // Verifica se expressao nao esta vazia
    if (expressao.empty())
        return false;

    Pilha<char> pilha;
    inicializar(pilha);

    int tamanhoExpressao = expressao.length();
    bool esperaOperando = true; // no inicio, esperamos um operando ou abretura
    bool temOperando = false; // verificar se temos pelo menos um operando

    for (int i = 0; i < tamanhoExpressao; i++)
    {
        char caracter = expressao[i];

        if (verificarEspaco(caracter))
            continue;

        if (verificarAbrir(caracter))
        {
            if (!esperaOperando)
            {
                liberar(pilha);
                return false; // abertura depois de operando sem operador
            }
            push(pilha, caracter);
        }
        else if (verificarFechar(caracter))
        {
            if (vazia(pilha))
            {
                liberar(pilha);
                return false; // fechamento sem abertura
            }
            if (esperaOperando)
            {
                liberar(pilha);
                return false; // fechamento sem operando
            }
            char topo;
            top(pilha, topo);

            if (!corresponde(topo, caracter))
            {
                liberar(pilha);
                return false; // delimitadores nao correspondem
            }
            char esquece;
            pop(pilha, esquece); // se passou todos os ifs podemos dar um pop pra deixar a pilha vazia
        }
        else if (verificarOperador(caracter))
        {
            if (esperaOperando)
            {
                liberar(pilha);
                return false; // operador no comeco ou apos outro operador
            }
            esperaOperando = true;
        }
        else if (verificarNumero(caracter))
        {
            if (!esperaOperando)
            {
                liberar(pilha);
                return false; // operando apos operando
            }
            // acumular todos os dígitos
            while (i < tamanhoExpressao && verificarNumero(expressao[i])) // usamos o mesmo i do for 
            {
                i++;
            }
            i--; // voltar um passo pois o for ja vai incrementar dnv
            esperaOperando = false;
            temOperando = true;
            
            // Verificar se próximo é variável para multiplicação implícita (ex: 3a)
            int j = i + 1;
            while (j < tamanhoExpressao && verificarEspaco(expressao[j]))
                j++;
            if (j < tamanhoExpressao && verificarVariavel(expressao[j]))
            {
                esperaOperando = true; // permite que a variável seja lida como operando
            }
        }
        else if (verificarVariavel(caracter))
        {
            if (!esperaOperando)
            {
                liberar(pilha);
                return false; // operando apos operando
            }
            esperaOperando = false;
            temOperando = true;
            
            // Verificar se próximo é número para multiplicação implícita (ex: a5)
            int j = i + 1;
            while (j < tamanhoExpressao && verificarEspaco(expressao[j]))
                j++;
            if (j < tamanhoExpressao && verificarNumero(expressao[j]))
            {
                esperaOperando = true; // permite que o número seja lido como operando
            }
        }
    }

    bool resultadoDelimitadores = vazia(pilha);
    bool resultadoSeq = !esperaOperando && temOperando; // nao pode terminar com operador

    liberar(pilha);
    return resultadoDelimitadores && resultadoSeq;
}

// N -> numero
// V -> variavel
// O -> operador
// A -> abrir
// F -> fechar
struct Token
{
    char tipo;
    string valor;
};

void tiraTokens(string &expressao, Fila<Token> &tokens)
{
    int tamanhoExpressao = expressao.length();
    Token ultimoToken;
    ultimoToken.tipo = '\0'; // inicializa como vazio

    for (int i = 0; i < tamanhoExpressao; i++)
    {
        char caracter = expressao[i];

        if (verificarEspaco(caracter))
            continue;

        Token token;
        bool precisaInserirMultiplicacao = false;

        // Verifica se precisa inserir multiplicação implícita
        if ((ultimoToken.tipo == 'N' || ultimoToken.tipo == 'V') && (verificarNumero(caracter) || verificarVariavel(caracter)))
        {
            precisaInserirMultiplicacao = true;
        }
        else if (ultimoToken.tipo == 'F' && (verificarNumero(caracter) || verificarVariavel(caracter) || verificarAbrir(caracter)))
        {
            precisaInserirMultiplicacao = true;
        }
        else if ((ultimoToken.tipo == 'N' || ultimoToken.tipo == 'V') && verificarAbrir(caracter))
        {
            precisaInserirMultiplicacao = true;
        }

        if (precisaInserirMultiplicacao)
        {
            Token multiplicacao;
            multiplicacao.tipo = 'O';
            multiplicacao.valor = '*';
            queue(tokens, multiplicacao);
        }

        if (verificarNumero(caracter))
        {
            string numero = "";
            while (i < tamanhoExpressao && verificarNumero(expressao[i]))
            {
                numero += expressao[i];
                i++;
            }
            i--;
            token.tipo = 'N'; // numero
            token.valor = numero;
            queue(tokens, token);
            ultimoToken = token;
        }
        else if (verificarVariavel(caracter))
        {
            token.tipo = 'V';
            token.valor = caracter;
            queue(tokens, token);
            ultimoToken = token;
        }
        else if (verificarOperador(caracter))
        {
            token.tipo = 'O'; // +, -, *, /
            token.valor = caracter;
            queue(tokens, token);
            ultimoToken = token;
        }
        else if (verificarAbrir(caracter))
        {
            token.tipo = 'A'; // parenteses, colchetes, chaves
            token.valor = caracter;
            queue(tokens, token);
            ultimoToken = token;
        }
        else if (verificarFechar(caracter))
        {
            token.tipo = 'F'; // parenteses, colchetes, chaves
            token.valor = caracter;
            queue(tokens, token);
            ultimoToken = token;
        }
    }
}
string converterPraPolenesa(string &expressao)
{
    if (!verificarSintaxe(expressao))
        return "Expressao incorreta ";

    Pilha<char> operadores;
    inicializar(operadores);

    Fila<Token> tokens;
    inicializar(tokens);

    tiraTokens(expressao, tokens); // todos os tokens da expressao pra uma fila de tokens para organizacao

    string resultado = ""; // inicializamos resultado

    while (!vazia(tokens))
    {
        Token token; // dequeue pede pra um valor T por referencia entao colocamos um aqui e token recebe o valor do inicio
        dequeue(tokens, token);

        if (token.tipo == 'N' || token.tipo == 'V')
        {
            resultado += token.valor; // se o tipo for numero ou variavel so colocamos
            resultado += " ";
        }
        else if (token.tipo == 'O')
        { // se for operador
            while (!vazia(operadores))
            {
                char topo;
                top(operadores, topo);
                // esse if gigante aqui e pra prioridade dos operadores ^ (expoente) que tem prioridade pela direita ->
                if (!(verificarAbrir(topo)) && (prioridade(topo) > prioridade(token.valor[0]) || (prioridade(topo) == prioridade(token.valor[0]) && token.valor[0] != '^')))
                {
                    resultado += topo;
                    resultado += " ";

                    char esquece;
                    pop(operadores, esquece);
                }
                else
                {
                    break;
                }
            }
            push(operadores, token.valor[0]);
        }
        else if (token.tipo == 'A')
        {
            push(operadores, token.valor[0]);
        }
        else if (token.tipo == 'F')
        { // operador de fechamento
            while (!vazia(operadores))
            {
                char topo;
                top(operadores, topo);

                if (verificarAbrir(topo))
                {
                    if (corresponde(topo, token.valor[0]))
                    {
                        char esquece;
                        pop(operadores, esquece);
                        break;
                    }
                    else
                    {
                        liberar(operadores);
                        liberar(tokens);
                        return "Erro: delimitadores incompativeis";
                    }
                }
                resultado += topo;
                resultado += " ";
                char esqueca;
                pop(operadores, esqueca);
            }
        }
    }

    while (!vazia(operadores))
    {
        char topo;
        top(operadores, topo);
        resultado += topo;
        resultado += " ";
        char esquecer;
        pop(operadores, esquecer);
    }

    liberar(operadores);
    liberar(tokens);

    bool resultadoVazio = resultado.empty();

    if (!resultadoVazio) {
        resultado.pop_back(); // aqui e pra remover o ultimo espaço da expressao
    }
    return resultado;
}

void tiraVariaveis(string &expressao, string &vars)
{
    string variaveis = "";

    int tamanhoExpressao = expressao.length();
    for (int i = 0; i < tamanhoExpressao; i++)
    {
        char caracter = expressao[i];
        if (verificarVariavel(caracter))
        {
            bool jaExiste = false;
            int tamanhoVariaveis = variaveis.length();
            for (int j = 0; j < tamanhoVariaveis; j++)
            {
                if (variaveis[j] == caracter)
                {
                    jaExiste = true;
                    break;
                }
            }
            if (!jaExiste)
                variaveis += caracter;
        }
    }
    vars = variaveis;
}

double calcular(string &expressaoPolonesa, char variaveis[], double valores[], int tamanho)
{
    Pilha<double> pilha;
    inicializar(pilha);

    string token = "";
    int tamanhoExpressao = expressaoPolonesa.length();

    for (int i = 0; i <= tamanhoExpressao; i++)
    {
        char caracter = (i < tamanhoExpressao) ? expressaoPolonesa[i] : ' ';

        if (caracter == ' ')
        {
            bool vazio = token.empty();
            if (!vazio)
            {
                if (verificarNumero(token[0]))
                {
                    double valor = stod(token);
                    push(pilha, valor);
                }
                else if (verificarVariavel(token[0]))
                {
                    double valor = 0;
                    for (int j = 0; j < tamanho; j++)
                    {
                        if (variaveis[j] == token[0])
                        {
                            valor = valores[j];
                            break;
                        }
                    }
                    push(pilha, valor);
                }
                else if (verificarOperador(token[0]))
                {
                    double b, a;
                    pop(pilha, b);
                    pop(pilha, a);

                    double resultado = 0;
                    if (token[0] == '+')
                        resultado = a + b;
                    else if (token[0] == '-')
                        resultado = a - b;
                    else if (token[0] == '*')
                        resultado = a * b;
                    else if (token[0] == '/')
                    {
                        if (b == 0)
                        {
                            liberar(pilha);
                            return 0;
                        }
                        resultado = a / b;
                    }
                    else if (token[0] == '^')
                        resultado = potencia(a, b);

                    push(pilha, resultado);
                }
                token = "";
            }
        }
        else
        {
            token += caracter;
        }
    }

    double resultado = 0;
    pop(pilha, resultado);
    liberar(pilha);
    return resultado;
}
#endif
