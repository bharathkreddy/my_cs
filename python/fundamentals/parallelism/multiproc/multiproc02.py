from  multiprocessing import Process
from time import perf_counter

def check_inclusion(reference_list):
    for i in range(10**8):
        i in reference_list

def main():

    number_processes = 4
    comparision_list = [1, 2, 3, 4]

    start_time = perf_counter()

    processes = [Process(target=check_inclusion, args=(comparision_list, )) for _ in range(number_processes)]


    for t in processes:
        t.start()

    for idx, t in enumerate(processes):
        print(f'Process{idx} alive: {t.is_alive()}')

    for t in processes:
        t.join()

    for idx, t in enumerate(processes):
        print(f'Process{idx} alive: {t.is_alive()}')

    print(f'Elapsed time: {perf_counter()-start_time}s')

if __name__ == '__main__':
    main()
