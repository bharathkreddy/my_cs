import threading
from time import sleep, perf_counter


class Squares(threading.Thread):
    '''We never call .run() ourselves
    we call .start() to start a thread
    and .join() to start a blocking call.'''
    def __init__(self, n):
        print(f"init with {n} @ {perf_counter()}")
        super().__init__()
        self._n = n


    def run(self):
        print(f'running thread{self._n} @ {perf_counter()}.....')
        sleep(2)
        print(self._n **2)
        print(f'end @ {perf_counter()}')



