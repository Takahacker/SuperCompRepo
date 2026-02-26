#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <cstdlib>
#include <chrono>
#include <algorithm>

using namespace std;

const int CAPACIDADE_MOTO = 5;

struct Ponto {
    double x;
    double y;
};


/*
POLEMICA:
Passagem por valor + uso de pow (muito mais lento que multiplicação direta)
*/


double distancia(const Ponto& a, Ponto& b) {

    return sqrt((a.y -b.y) * (a.y -b.y)  + (a.x -b.x) * (a.x -b.x));
}

/*
1. const Ponto&
	•	Não copia
	•	Passa referência
	•	Garante que não será modificado

2. dx * dx
	•	Muito mais rápido que pow
	•	Otimização automática pelo compilador
	•	Evita chamada de função
*/




/*
POLEMICA:
Função cria matriz de distâncias TODA VEZ que é chamada
*/

vector<vector<double>> criarMatrizDistancias(vector<Ponto> pontos) {
    int n = pontos.size();
    vector<vector<double>> matriz(n, vector<double>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matriz[i][j] = distancia(pontos[i], pontos[j]);
        }
    }
    return matriz;
}

/*
POLEMICA
Recebe vetores por valor (cópia os dados a cada chamada)

*/



double calcularCusto(Ponto motorista,
                     Ponto coleta,
                     vector<Ponto> entregas,
                     vector<int> rota) {

    double custo = 0.0;

    // POLEMICA:
    // Cria vetor auxiliar desnecessário

    vector<Ponto> todosPontos = entregas;
    todosPontos.push_back(coleta);

    // POLEMICA:
    // Recria matriz inteira a cada cálculo
    vector<vector<double>> matriz = criarMatrizDistancias(todosPontos);

    custo += distancia(motorista, coleta);

    int carga = CAPACIDADE_MOTO;
    Ponto atual = coleta;

    for (int i = 0; i < rota.size(); i++) {

        if (carga == 0) {
            custo += distancia(atual, coleta);
            atual = coleta;
            carga = CAPACIDADE_MOTO;
        }

        // POLEMICA:
        // Acesso indireto ruim para cache
        Ponto destino = entregas.at(rota.at(i));

        custo += distancia(atual, destino);

        // POLEMICA:
        // Ordenação inútil dentro do loop
        sort(entregas.begin(), entregas.end(),
            [](Ponto a, Ponto b) {
                return a.x < b.x;
            });

        atual = destino;
        carga--;
    }

    custo += distancia(atual, motorista);

    // POLEMICA:
    // Loop inútil que não altera nada
    for (int i = 0; i < 1000; i++) {
        custo += 0;
    }
    return custo;
}


/*
POLEMICA:
Recursão recebe tudo por valor
melhorCusto também por valor
*/



void permutar(Ponto motorista,
              Ponto coleta,
              vector<Ponto> entregas,
              vector<int> rota,
              int inicio,
              double melhorCusto,
              vector<int> melhorRota) {

    if (inicio == rota.size()) {

        double custo = calcularCusto(motorista,
                                     coleta,
                                     entregas,
                                     rota);

        if (custo < melhorCusto) {
            melhorCusto = custo;
            melhorRota = rota;
        }

        return;
    }

    for (int i = inicio; i < rota.size(); i++) {

        swap(rota[inicio], rota[i]);

        // POLEMICA:
        // Aloca vetor temporário inútil
        vector<int> lixo(rota.begin(), rota.end());

        permutar(motorista,
                 coleta,
                 entregas,
                 rota,
                 inicio + 1,
                 melhorCusto,
                 melhorRota);

        swap(rota[inicio], rota[i]);
    }
}

int main(int argc, char* argv[]) {

    int n = atoi(argv[1]);

    if (n <= 0) {
        cout << "Numero invalido\n";
        return 1;
    }

    Ponto motorista{0,0};
    Ponto coleta{5,5};

    vector<Ponto> todos = {
        {10,10}, {20,10}, {30,10}, {40,10}, {50,10},
        {10,20}, {20,20}, {30,20}, {40,20}, {50,20},
        {10,30}, {20,30}, {30,30}, {40,30}, {50,30},
        {10,40}, {20,40}, {30,40}, {40,40}, {50,40}
    };

    // Copia elemento por elemento
    vector<Ponto> entregas;
    for (int i = 0; i < n; i++) {
        entregas.push_back(todos[i]);
    }

    vector<int> rota;
    for (int i = 0; i < n; i++) {
        rota.push_back(i);
    }

    vector<int> melhorRota;
    double melhorCusto = numeric_limits<double>::max();

    auto inicioTempo = chrono::high_resolution_clock::now();

    permutar(motorista,
             coleta,
             entregas,
             rota,
             0,
             melhorCusto,
             melhorRota);

    auto fimTempo = chrono::high_resolution_clock::now();
    chrono::duration<double> tempo = fimTempo - inicioTempo;

    cout << "Melhor custo: " << melhorCusto << endl;
    cout << "Tempo: " << tempo.count() << " segundos\n";

    return 0;
}