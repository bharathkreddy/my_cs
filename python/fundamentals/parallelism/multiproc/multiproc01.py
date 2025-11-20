import threading
from time import perf_counter

def check_inclusion(reference_list):
    for i in range(10**8):
        i in reference_list


number_threads = 4
comparision_list = [1, 2, 3, 4]

start_time = perf_counter()

threads = [threading.Thread(target=check_inclusion, args=(comparision_list, )) for _ in range(number_threads)]


for t in threads:
    t.start()

for idx, t in enumerate(threads):
    print(f'Thread{idx} alive: {t.is_alive()}')

for t in threads:
    t.join()

for idx, t in enumerate(threads):
    print(f'Thread{idx} alive: {t.is_alive()}')

print(f'Elapsed time: {perf_counter()-start_time}s')


