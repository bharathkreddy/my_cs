import asyncio
from time import sleep, perf_counter

async def do_work(fn_param):
    await asyncio.sleep(fn_param)
    return f'finished sleep {fn_param}s'

async def main():
    # create tasks manually
    print('Manual tasks')
    start_time = perf_counter()

    task1 = asyncio.create_task(do_work(1))
    task2 = asyncio.create_task(do_work(2))

    result1 = await task1
    result2 = await task2

    print(f'Result: {result1, result2}, Elapsed: {perf_counter()-start_time:.2f}\n') 
    
    # gather co-routines

    start_time = perf_counter()

    coroutines = [do_work(x) for x in range(1, 3)]
    results = await asyncio.gather(*coroutines, return_exceptions=True)    
    print(f'coroutine results: {results}, Elapsed: {perf_counter()-start_time:.2f}\n')

    # gather tasks
    start_time = perf_counter()
    
    # each task is independent and has indepent result, use tasks over co-routines if you want to interact with tasks before they complete to monitor, cancel etc.
    tasks = [asyncio.create_task(do_work(x)) for x in range(1, 3)]
    results = await asyncio.gather(*tasks, return_exceptions=True)    
    print(f'tasks results: {results}, Elapsed: {perf_counter()-start_time:.2f}\n')

    # task groups
    start_time = perf_counter()

    # all tasks fail even if one fails, all succeed or fail together
    async with asyncio.TaskGroup() as tg:
        results = [tg.create_task(do_work(x)) for x in range(1, 3)]
        # all tasks are awaiting with taskgroup context exits
    
    print(f'task_group results: {results}, Elapsed: {perf_counter()-start_time:.2f}\n')
    
    
    

if __name__ == '__main__':
    asyncio.run(main())



