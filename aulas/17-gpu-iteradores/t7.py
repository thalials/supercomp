import numpy as np
import sys

stocks_ms = []
stocks_aapl = []
while (True):
    try:
        ms, aapl = [float(f) for f in input().split()]
        stocks_ms.append(ms)
        stocks_aapl.append(aapl)
    except EOFError:
        break

stocks_ms = np.array(stocks_ms)
stocks_aapl = np.array(stocks_aapl)

print(sum(stocks_ms - stocks_aapl)/len(stocks_ms))
print(np.var(stocks_ms - stocks_aapl))