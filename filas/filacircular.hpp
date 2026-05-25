#ifndef TAM
#define TAM 50
#endif

template <typename T>
struct Fila{
    T vetor[TAM];
    int comeco, fim;
    int cont;
};

template <typename T>
void inicializar(Fila <T> &f){
    f.comeco = 0;
    f.fim = -1;
    f.cont = 0;
}

template <typename T>
bool vazia(Fila <T> f){
    return (f.cont == 0) ? true : false;
}

template <typename T>
bool cheia(Fila <T> f){
    return (f.cont == TAM) ? true : false;
}

template <typename T>
bool queue(Fila <T> &f, T valor){
    if( cheia(f) ) return false;
    f.fim++;
    if( f.fim == TAM ) f.fim = 0;
    f.cont++;
    f.vetor[f.fim] = valor;
    return true;
}

template <typename T>
bool dequeue(Fila <T> &f, T &valor){
    if( vazia(f) ) return false;
    valor = f.vetor[f.comeco];
    f.comeco = (f.comeco == TAM-1) ? 0 : f.comeco+1;
    f.cont--;
    return true;
}

template <typename T>
void liberar(Fila <T> f){
}
