from multiprocessing import Pool, cpu_count
from time import perf_counter
import math

def is_prime(n):
    if n < 2:
        return False
    for i in range(2, n-1):
        if n % i == 0:
            return False
    return True

def sequential():
    print('Running sequential.....')
    start_time = perf_counter()
    result = [is_prime(x) for x in range(1, 100_000)]
    print(f'Total pimes between 1-100K: {sum(result)}')
    print(f'Time elapsed: {perf_counter()-start_time}s')

def poolrun():

    print('\n\nWith pool now.......')

    start_time = perf_counter()
    with Pool(cpu_count()-2) as mp_pool:
        result = mp_pool.map(is_prime, range(1, 100_000))
          
    print(f'Total pimes between 1-100K: {sum(result)}')
    print(f'Time elapsed: {perf_counter()-start_time}s')

if __name__ == '__main__':
    sequential()
    poolrun()


