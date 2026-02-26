#!/bin/bash
#SBATCH --job=otimiza
# Define o nome do job. Esse nome aparece nas listas de jobs e é útil para identificar o job.

#SBATCH --output=otimiza.out
# Especifica o arquivo onde a saída padrão (stdout) do job será salva.

#SBATCH --ntasks=1
# Define o número de tarefas que o job executará. Neste caso, o job executa uma única tarefa.

#SBATCH --time=00:20:00
# Define o tempo máximo de execução para o job. Neste caso, o job tem um tempo limite de 10 minutos. Se o job exceder esse tempo, ele será automaticamente encerrado.

#SBATCH --partition=gpu
# Especifica a partição (ou fila) onde o job será submetido. Aqui, o job será submetido a fila "normal".

for number in 9 10 11 13
do

echo " "
echo " "
echo "NUMERO = "$number
echo "========== SEM OTIMIZACAAAOOOO ========"
./otimiza $number

echo "========= OTIMIZACAO 02 ==============="
./otimiza_O2 $number

echo "======== OTIMIZACAO O3 ==============="
./otimiza_O3 $number

echo "=========== OFAST ESSA ==============="
./otimiza_Ofast $number

# Executa os binários dentro do nó de computação.
done