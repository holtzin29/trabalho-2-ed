/*
UNIVALI
Disciplina: Estrutura de Dados
Trabalho 2 
Alunos:
Renan Felipe de Andrade
Arthur Soares Silva
Mauro Grippa Junior
*/
#include <iostream>

// #include "../pilhas/pilhaestatica.hpp"
// #include "../filas/filaestatica.hpp"
// #include "../filas/filacircular.hpp"
#include "../pilhas/pilhadinamica.hpp"
#include "../filas/filadinamica.hpp"

#include "expressao.hpp"
#include "utilitarios.hpp"

using namespace std;

void limparTela()
{
    system("cls");
    system("clear");
}

void menu()
{
    limparTela();

    int op = 1;

    string expressao;
    string resultado;
    string expressaoPolonesa;

    bool temA = false;
    bool temB = false;
    bool temC = false;

    float a = 0;
    float b = 0;
    float c = 0;

    while (op != 0)
    {
        cout << "----NOTAÇÃO POLONESA INVERSA----" << endl;
        cout << "Escolha uma das opções abaixo: " << endl;
        cout << "1) Inserir expressao" << endl;
        cout << "2) Inserir valores das variáveis" << endl;
        cout << "3) Mostrar valores das variáveis" << endl;
        cout << "4) Mostrar expressao" << endl;
        cout << "5) Mostrar resultado" << endl;
        cout << "6) Converter para NPI" << endl;
        cout << "0) sair" << endl;

        cin >> op;

        switch (op)
        {

        case 1:

            cout << "Digite a expressao: " << endl;

            cin.ignore();
            getline(cin, expressao);

            verificarVariaveis(expressao, temA, temB, temC);

            if (verificarSintaxe(expressao))
            {
                cout << "Expressao valida!" << endl;
            }
            else
            {
                cout << "Erro de sintaxe!" << endl;
            }

            break;

        case 2:

            if (temA == true)
            {
                cout << "Insira o valor de a: " << endl;
                cin >> a;
            }

            if (temB == true)
            {
                cout << "Insira o valor de b: " << endl;
                cin >> b;
            }

            if (temC == true)
            {
                cout << "Insira o valor de c: " << endl;
                cin >> c;
            }

            break;

        case 3:

            if (temA == true)
            {
                cout << "valor de a = " << a << endl;
            }

            if (temB == true)
            {
                cout << "valor de b = " << b << endl;
            }

            if (temC == true)
            {
                cout << "valor de c = " << c << endl;
            }

            break;

        case 4:

            cout << "Expressao digitada: " << endl;
            cout << expressao << endl;

            break;

        case 5:

            if (expressaoPolonesa != "")
            {
                char variaveis[3] = {'a', 'b', 'c'};
                double valores[3] = {a, b, c};

                float valorFinal = calcular(
                    expressaoPolonesa,
                    variaveis,
                    valores,
                    3);

                cout << "Resultado: " << valorFinal << endl;
            }
            else
            {
                cout << "Converta a expressao primeiro!" << endl;
            }

            break;

        case 6:

            expressaoPolonesa = converterPraPolenesa(expressao);

            cout << "Expressao em NPI: " << endl;
            cout << expressaoPolonesa << endl;

            break;

        case 0:

            cout << "Encerrando..." << endl;
            break;

        default:

            cout << "Opcao invalida!" << endl;
            break;
        }

        cout << endl;
    }
}

int main()
{

    Pilha<char> pilhaChar;
    Fila<char> filaChar;

    inicializar(pilhaChar);
    inicializar(filaChar);

    menu();

    liberar(pilhaChar);
    liberar(filaChar);

    return 0;
}