import os

os.environ["LD_LIBRARY_PATH"]="/act/opt/intel/composer_xe_2013.3.163/mkl/lib/intel64:"+os.environ.get("LD_LIBRARY_PATH","")
os.system("make")
# os.system("./main lapack 4096")
# os.system("./main my 4096")
os.system("./main lapack 1000")
os.system("./main my 1000")
os.system("./main lapack 2000")
os.system("./main my 2000")
os.system("./main lapack 3000")
os.system("./main my 3000")
os.system("./main lapack 4000")
os.system("./main my 4000")
os.system("./main lapack 5000")
os.system("./main my 5000")
