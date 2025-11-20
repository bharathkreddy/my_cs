from workers.squarer import Squares

def main():
    threads = [Squares(x) for x in range(5)]

    # start all threads in parallel
    print('starting threads in parallel...')
    for t in threads:
        t.start()

    # wait for all threads to finish and join to main thread
    for t in threads:
        t.join()

if __name__ == '__main__':
    main()


