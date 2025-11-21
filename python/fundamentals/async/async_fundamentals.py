from time import perf_counter, sleep
import asyncio

## synchronous function

def fetch_data(fn_param):
    print(f'Do something with {fn_param}')
    sleep(fn_param)
    print(f'Done with {fn_param}')
    return f'Result of {fn_param}'

def synchronous_call():
    result1 = fetch_data(1)
    print('Fetch 1 fully complete')
    result2 = fetch_data(2)
    print('Fetch 2 fully complete')
    return result1, result2

t_start = perf_counter()
sync_result = synchronous_call()
print(f'Result: {sync_result}')
print(f'Elapsed: {perf_counter()-t_start:.2f}s\n\n')
   
## asych try 1
print("Trying Asych without tasks....\n")

async def fetch_data_async(fn_param):
    print(f'Do something with {fn_param}')
    await asyncio.sleep(fn_param)
    print(f'Done with {fn_param}')
    return f'Result of {fn_param}'

async def async_call():
    result1 = await fetch_data_async(1)
    print('Fetch 1 fully complete')
    result2 = await fetch_data_async(2)
    print('Fetch 2 fully complete')
    return result1, result2

t_start = perf_counter()
async_result = asyncio.run(async_call())
print(f'Result: {sync_result}')
print(f'Elapsed: {perf_counter()-t_start:.2f}s\n\n')

print("Reason for no gain is the keyword await causes suspension of main function and yields control to the event loop, which looks for any ready tasks. In our case there are not tasks for event loops looks for any co-routines. Once the co-routines are completed the control is passed back to the main loop. scheduling a co-routine and completion of the co-routine at same time. Co-routine is any async function.\n\n")


## correct way to do concurrency

print("Trying Asych with tasks....\n")

async def async_correct_call():
    task_1 = asyncio.create_task(fetch_data_async(1))
    task_2 = asyncio.create_task(fetch_data_async(2))
    
    result1 = await task_1
    print('Fetch 1 fully complete')
    result2 = await task_2
    print('Fetch 2 fully complete')
    return result1, result2

t_start = perf_counter()
async_result = asyncio.run(async_correct_call())
print(f'Result: {async_result}')
print(f'Elapsed: {perf_counter()-t_start:.2f}s\n\n')

print("creating tasks schedules these and await just gathers results when available. So tasks are created are in ready state in the event loop, when python sees await, the control is yielded to event loop which picks up first ready task i.e. task_1, and when in task_1 it sees await on sleep, the control again goes back to event loop which sees task_2 also in ready and starts with task_2 until it sees await sleep in task_2, at this point, once the task_1 is complete, it wakes up the main await on task_1 and returns the values. Same once task_2 is done.\n\n")

print('Another example.../n')
async def async_call2():
    task_1 = asyncio.create_task(fetch_data_async(1))
    task_2 = asyncio.create_task(fetch_data_async(2))
    
    result2 = await task_2
    print('Fetch 2 fully complete')
    result1 = await task_1
    print('Fetch 1 fully complete')
    return result1, result2


t_start = perf_counter()
async_result = asyncio.run(async_call2())
print(f'Result: {async_result}')
print(f'Elapsed: {perf_counter()-t_start:.2f}s\n\n')

print("await waits until completion, but tasks start as soon as they are ready. Await only causes the program in main to wait until completion before moving on.\n\n")



