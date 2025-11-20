from time import sleep
from time import perf_counter
import threading
from datetime import datetime, timezone


# function we want to thread
def calc_squares(n):
    print(f'\tfunction{n} start: {datetime.now(timezone.utc)}')
    start_time = perf_counter()
    sleep(2)
    print(f'\tfunction took: {perf_counter()-start_time} s')


def main():
    
    # sequential call to the function
    start_time = perf_counter()
    for i in range(5):
        calc_squares(i)
    print(f'Sequential Elapsed: {perf_counter() - start_time}\n')

    # start all threads and block only after all of threads are done
    start_time = perf_counter()
    threads = []
    for i in range(5):
        t = threading.Thread(target=calc_squares, args=(i,))
        t.start()
        threads.append(t)

    for thread in threads:
        thread.join()

    print(f'Threaded Elapsed: {perf_counter() - start_time} s\n')


    # block each thread for it to complete before starting another thread
    start_time = perf_counter()
    for i in range(5):
        t = threading.Thread(target=calc_squares, args=(i,))
        t.start()
        t.join() # blocking, each thread has to finish before execution continues
    print(f'Threaded join elapsed: {perf_counter() - start_time} s\n')


# main function call
if __name__ == '__main__' :
    main()

