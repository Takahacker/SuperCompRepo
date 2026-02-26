# Otimizações aplicadas em `otimizado1.cpp`

Este documento resume as **polêmicas** do código original e o que foi otimizado em `A4/otimiza/otimizado1.cpp`.

## Polêmicas encontradas e correções

1. **Passagem por valor em pontos e vetores**
- Problema: cópias desnecessárias em funções chamadas muitas vezes.
- Otimização: uso de `const Ponto&`, `const vector<Ponto>&` e referências onde necessário.

2. **Uso de `pow` para quadrado**
- Problema: `pow(x, 2)` é mais custoso que multiplicação direta.
- Otimização: troca para `dx * dx + dy * dy`.

3. **Matriz de distâncias recriada repetidamente**
- Problema: a matriz era calculada várias vezes sem necessidade.
- Otimização: matriz calculada uma única vez e reutilizada durante toda a busca.

4. **Ordenação inútil dentro do loop principal**
- Problema: `sort` era executado a cada entrega, sem contribuir para o resultado.
- Otimização: remoção completa da ordenação no loop.

5. **Recursão com cópias e sem atualização real do melhor resultado**
- Problema: `melhorCusto` e `melhorRota` eram passados por valor; o melhor custo não persistia.
- Otimização: passagem por referência para atualizar o ótimo global corretamente.

6. **Recalcular custo completo em cada permutação**
- Problema: custo total era recalculado do zero em cada folha da recursão.
- Otimização: cálculo incremental de custo na recursão (`custoAtual`) + poda quando `custoAtual >= melhorCusto`.

7. **Alocação temporária inútil na permutação**
- Problema: criação de vetor `lixo` em toda iteração da busca.
- Otimização: remoção da alocação desnecessária.

8. **Loop inútil ao final do cálculo**
- Problema: loop com `custo += 0` não alterava nada e consumia CPU.
- Otimização: remoção do loop.

9. **Falta de validação de entrada**
- Problema: acesso a `argv[1]` sem checar `argc` e ausência de limite para `n`.
- Otimização: validação de argumentos e limite máximo de entregas.

## Resultado das otimizações

- Código com menos cópias e menos alocações.
- Menor custo por chamada de função.
- Busca de permutações com poda (menos estados explorados na prática).
- Correção funcional no cálculo de `melhorCusto`.

## Compilação e execução

```bash
g++ -O2 -std=c++17 A4/otimiza/otimizado1.cpp -o otimizado1
./otimizado1 6
```
