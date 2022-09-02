from contextlib import redirect_stdout
import os

dirname = os.path.dirname(__file__)

path   = os.path.join(dirname,"inputs/")
mandel = "mandelbrotX.in"
matrixFile = "matrixY.in"

mandelbrot = ("340","1000","4600") # no 1 thread isso da +- 64s
matrix = "2340" # no 1 thread isso da +- 54s
threads = [x for x in range(1,9)]

for t in threads:
    with open(path+mandel.replace("X", str(t)), 'w') as f:
        with redirect_stdout(f):
            print(mandelbrot[0])
            print(mandelbrot[1])
            print(mandelbrot[2])
            print(str(t))
    with open(path+matrixFile.replace("Y", str(t)), 'w') as f:
        with redirect_stdout(f):
            print(str(t)+" "+matrix)