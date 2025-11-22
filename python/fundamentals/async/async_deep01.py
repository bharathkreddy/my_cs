### Running synchronous functions in event loop

from time import sleep, perf_counter
import asyncio
from concurrent.futures import ProcessPoolExecutor

def do_work(fn_param):
    print(f'starting {fn_param}', flush=True) # flush to not buffer print
    sleep(fn_param)  # time.sleep is a blocking code, unlike asychio.sleep
    print(f'Done with {fn_param}', flush=True)
    return f'Result of: {fn_param}'


async def main():
    # run in threads - to_thread wraps a synchronous fn into an awaitable. 
    task1 = asyncio.create_task(asyncio.to_thread(do_work, 1))
    task2 = asyncio.create_task(asyncio.to_thread(do_work, 2))
    
    result1 = await task1
    print('Thread 1 complete.', flush=True)

    result2 = await task2
    print('Thread 2 complete.', flush=True)
    
    return result1, result2
    
async def main2():
    # run in processPool
    
    loop = asyncio.get_running_loop()

    with ProcessPoolExecutor() as executor:
        task1 = loop.run_in_executor(executor, do_work, 1) 
        task2 = loop.run_in_executor(executor, do_work, 2) 
    
        result1 = await task1
        print('Thread 1 complete.')
        result2 = await task2
        print('Thread 2 complete.')
    
    return result1, result2


# we have to do __name__ == '__main__' whenever we use multiprocessing to not get into infinite loop
if __name__ == '__main__':
    print('Running in threads......\n')
    s_time = perf_counter()
    result = asyncio.run(main())
    print(f'{result}, took {perf_counter()-s_time:.2f}s')
    
    print('\n\n')
    print('Running in process pools......\n')
    s_time = perf_counter()
    result = asyncio.run(main2())
    print(f'{result}, took {perf_counter()-s_time:.2f}s')





