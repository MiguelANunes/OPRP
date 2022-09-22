from contextlib import redirect_stdout
import os

dirname = os.path.dirname(__file__)

path   = os.path.join(dirname,"inputs/")
mandel = "mandelbrotX.in"

mandelbrot = ("340","1000","4600") # no 1 thread isso da +- 64s
threads = [x for x in range(1,9)]

for t in threads:
    with open(path+mandel.replace("X", str(t)), 'w') as f:
        with redirect_stdout(f):
            print(mandelbrot[0])
            print(mandelbrot[1])
            print(mandelbrot[2])
            print(str(t))