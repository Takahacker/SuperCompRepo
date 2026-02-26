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

double distancia(const Ponto& a, const Ponto& b) {
    const double dx = a.x - b.x;
    const double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

vector<vector<double>> criarMatrizDistancias(const vector<Ponto>& pontos) {
    const int n = static_cast<int>(pontos.size());
    vector<vector<double>> matriz(n, vector<double>(n, 0.0));

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            const double d = distancia(pontos[i], pontos[j]);
            matriz[i][j] = d;
            matriz[j][i] = d;
        }
    }

    return matriz;
}

void permutarOtimizado(
    vector<int>& rota,
    int inicio,
    int carga,
    int pontoAtualIdx,
    double custoAtual,
    double& melhorCusto,
    vector<int>& melhorRota,
    const vector<vector<double>>& distancias
) {
    if (custoAtual >= melhorCusto) {
        return;
    }

    if (inicio == static_cast<int>(rota.size())) {
        const double custoTotal = custoAtual + distancias[pontoAtualIdx][0];
        if (custoTotal < melhorCusto) {
            melhorCusto = custoTotal;
            melhorRota = rota;
        }
        return;
    }

    for (int i = inicio; i < static_cast<int>(rota.size()); i++) {
        swap(rota[inicio], rota[i]);

        int cargaAtual = carga;
        int atual = pontoAtualIdx;
        double incremento = 0.0;

        if (cargaAtual == 0) {
            incremento += distancias[atual][1];
            atual = 1;
            cargaAtual = CAPACIDADE_MOTO;
        }

        const int destinoEntrega = 2 + rota[inicio];
        incremento += distancias[atual][destinoEntrega];

        permutarOtimizado(
            rota,
            inicio + 1,
            cargaAtual - 1,
            destinoEntrega,
            custoAtual + incremento,
            melhorCusto,
            melhorRota,
            distancias
        );

        swap(rota[inicio], rota[i]);
    }
}

int main(int argc, char* argv[]) {

    if (argc < 2) {
        cout << "Uso: " << argv[0] << " <n>\n";
        return 1;
    }

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

    if (n > static_cast<int>(todos.size())) {
        cout << "Numero invalido: maximo permitido = " << todos.size() << "\n";
        return 1;
    }

    vector<Ponto> entregas;
    entregas.reserve(n);
    for (int i = 0; i < n; i++) {
        entregas.push_back(todos[i]);
    }

    vector<int> rota(n);
    for (int i = 0; i < n; i++) {
        rota[i] = i;
    }

    vector<Ponto> pontos;
    pontos.reserve(n + 2);
    pontos.push_back(motorista); // idx 0
    pontos.push_back(coleta);    // idx 1
    for (const Ponto& p : entregas) {
        pontos.push_back(p);     // idx 2..n+1
    }
    const vector<vector<double>> distancias = criarMatrizDistancias(pontos);

    vector<int> melhorRota;
    double melhorCusto = numeric_limits<double>::max();

    auto inicioTempo = chrono::high_resolution_clock::now();

    permutarOtimizado(
        rota,
        0,
        CAPACIDADE_MOTO,
        1,
        distancias[0][1],
        melhorCusto,
        melhorRota,
        distancias
    );

    auto fimTempo = chrono::high_resolution_clock::now();
    chrono::duration<double> tempo = fimTempo - inicioTempo;

    cout << "Melhor custo: " << melhorCusto << endl;
    cout << "Tempo: " << tempo.count() << " segundos\n";

    return 0;
}
