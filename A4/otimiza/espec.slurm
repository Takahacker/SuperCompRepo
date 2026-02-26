#!/bin/bash
#SBATCH --job-name=otimiza_espec
#SBATCH --output=otimiza_espec.out
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=1
#SBATCH --time=00:20:00
#SBATCH --partition=espec
#SBATCH --mem=4G

echo "Job iniciado em $(date)"
echo "Rodando no nó: $(hostname)"
echo "===================================="

for number in 13
do
    echo ""
    echo "NUMERO = $number"
    echo "=========== Otimizado OFAST ==============="
    ./otimizado_Ofast $number
done

echo "===================================="
echo "Job finalizado em $(date)"