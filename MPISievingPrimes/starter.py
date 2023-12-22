import os

N_list=[1,2,3,4,5]
ver_list=[0,1,2,3]
n=10000000000
# n=10000

os.system("module load mpich-3.2.1")
os.system("make")
if os.path.exists("main"):
    os.system("mkdir sh2")
    for N in N_list:
        for ver in ver_list:
            f=open("sh2/sieve"+str(ver)+"_"+str(N)+".sh","w")
            f.write("#!/bin/bash\n")
            f.write("#SBATCH -o sieve"+str(ver)+"_"+str(N)+".o\n")
            f.write("#SBATCH -e sieve"+str(ver)+"_"+str(N)+".err\n")
            f.write("#SBATCH -J sieve"+str(ver)+"_"+str(N)+"\n")
            f.write("#SBATCH -N "+str(N)+"\n")
            f.write("#SBATCH -t 00:10:00\n")
            f.write("\n")
            f.write("module load mpich-3.2.1\n")
            f.write("mpirun -np "+str(N*24)+" ../main sieve"+str(ver)+" "+str(n))
            f.close()
    os.chdir("sh2")
    for N in N_list:
        for ver in ver_list:
            print("sbatch sieve"+str(ver)+"_"+str(N)+".sh")
            os.system("sbatch sieve"+str(ver)+"_"+str(N)+".sh")
            print("-"*20)
