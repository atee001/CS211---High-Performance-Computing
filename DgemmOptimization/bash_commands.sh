#!/bin/bash -l

#SBATCH --nodes=1 # Allocate *at least* 1 node to this job.
#SBATCH --ntasks=1 # Allocate *at most* 1 task for job steps in the job
#SBATCH --cpus-per-task=1 # Each task needs only one CPU
#SBATCH --mem=12G # This particular job won't need much memory
#SBATCH --time=0-00:50:00 # 50 minutes
#SBATCH --job-name="batch job test"
#SBATCH -p batch # You could pick other partitions for other jobs
#SBATCH --wait-all-nodes=1 # Run once all resources are available
#SBATCH --output=output_%j-%N.txt # logging per job and per host in the

python3 starter.py
