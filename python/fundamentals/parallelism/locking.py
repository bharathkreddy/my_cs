import threading
from time import sleep

counter = 0

def incrementer():
    global counter
    for _ in range(5):
        temp = counter
        sleep(0.000001)
        counter = temp+1

threads = [threading.Thread(target=incrementer) for _ in range(10)]

for t in threads:
    t.start()

for t in threads:
    t.join()

print(f'Increment: {counter}')
print('second run of same ')


counter = 0
threads = [threading.Thread(target=incrementer) for _ in range(10)]

for t in threads:
    t.start()

for t in threads:
    t.join()

print(f'Increment: {counter}\n\n')


lock = threading.Lock()

counter = 0
def locked_counter():
    global counter
    for _ in range(5):
        with lock:
            temp = counter
            sleep(0.000001)
            counter = temp+1

threads = [threading.Thread(target=locked_counter) for _ in range(10)]

for t in threads:
    t.start()

for t in threads:
    t.join()

print(f'Locked_Increment: {counter}')

print('second run of same ')


counter = 0
threads = [threading.Thread(target=locked_counter) for _ in range(10)]

for t in threads:
    t.start()

for t in threads:
    t.join()

print(f'locked_Increment: {counter}')

