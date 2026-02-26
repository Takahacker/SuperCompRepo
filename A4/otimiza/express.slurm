#!/bin/bash
#SBATCH --job-name=otimiza_express
#SBATCH --output=otimiza_express.out
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=1
#SBATCH --time=00:05:00
#SBATCH --partition=express
#SBATCH --mem=4G

echo "Início: $(date)"
echo "Nó: $(hostname)"
echo "============================"

./otimizado_Ofast 13

echo "============================"
echo "Fim: $(date)"