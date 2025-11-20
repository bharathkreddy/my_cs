from workers.wikiScraper import WikiScraper
from workers.yahooWorker import YahooFinancePriceScheduler
from workers.pgWorker import PgWorker
from multiprocessing import Queue
import os
from dotenv import load_dotenv

load_dotenv()
supabase_url = os.environ.get("SUPABASE_URL")
supabase_key = os.environ.get("SUPABASE_KEY")

def main():
    url_ = 'https://en.wikipedia.org/wiki/List_of_S%26P_500_companies'
    threads = []
    pg_threads = []
    symbol_queue = Queue()
    pg_queue = Queue()
    num_yahoo_workers = 10
    num_pg_workers = 7

    try:
        for idx, symbol in enumerate(WikiScraper(url_).scrape()):
            if idx == 30:
                break
            print(f'symbol_queue: {idx}:{symbol}')
            symbol_queue.put(symbol)

    except Exception as er:
        print(er)
    finally:
        for _ in range(num_yahoo_workers):
            symbol_queue.put('DONE')

    for _ in range(num_yahoo_workers):
        threads.append(YahooFinancePriceScheduler(symbol_queue, pg_queue))

    for t in threads:
        t.start()

    for t in threads:
        t.join()
    
    for _ in range(num_pg_workers):
        pg_queue.put('DONE')
        pg_threads.append(PgWorker(supabase_url, supabase_key, pg_queue))
    
    for t in pg_threads:
        t.start()

    for t in pg_threads:
        t.join()

if __name__ == '__main__':
    main()
