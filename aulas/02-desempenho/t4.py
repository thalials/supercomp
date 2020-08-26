import numpy as np
import numpy.random
import sys

n = int(input())
arr = np.random.rand(n)
print(10)
print('\n'.join([str(a) for a in arr]))

print(f'{np.mean(arr):0.9f}', f'{np.var(arr):0.9f}', file=sys.stderr)
