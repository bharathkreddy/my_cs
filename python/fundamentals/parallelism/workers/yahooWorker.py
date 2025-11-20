import requests
from bs4 import BeautifulSoup
import threading
from pydantic import BaseModel, field_serializer
from datetime import datetime, timezone

class Record(BaseModel):
    created_at: datetime
    ticker: str
    price: float

    @field_serializer("created_at", when_used='always')
    def serialize_dt(self, value):
        return value.isoformat()

class YahooFinancePriceScheduler(threading.Thread):
    def __init__(self, ticker_queue, output_queue):
        super().__init__()
        self._ticker_queue = ticker_queue
        self._output_queue = output_queue

    def run(self):
        while True:
            ticker = self._ticker_queue.get()

            if ticker == 'DONE':
                print('Thread seen DONE')
                break

            yahooWorker = YahooWorker(ticker)
            price = yahooWorker.get_price()
            r = Record(created_at=datetime.now(timezone.utc), ticker=ticker, price=price)
            payload = r.model_dump()
            self._output_queue.put(payload)
            print(f'adding to price_queue:{payload}')


class YahooWorker():
    def __init__(self, symbol):
        self._symbol = str(symbol).strip()
        self._url = f'https://finance.yahoo.com/quote/{self._symbol}'
        self._header = {"User-Agent": (
                "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) "
                "AppleWebKit/537.36 (KHTML, like Gecko) "
                "Chrome/123.0.0.0 Safari/537.36"
            )}

        
    @staticmethod
    def extract_price(html_doc):
        soup = BeautifulSoup(html_doc, 'html.parser')
        price_span = soup.find('span', {"class":"yf-ipw1h0 base"})
        if price_span:
            return price_span.get_text(strip=True)

    def get_price(self):
        try:
            r = requests.get(self._url, headers=self._header)
            if r.status_code == 404:
                print(f"Symbol {self._symbol} not found (404)")
                return -99
            if r.status_code != 200:
                print(f"HTTP {r.status_code} for {self._symbol}")
                return -99

            price = self.extract_price(r.text)

            if not price:
                print(f"Price not found for {self._symbol}")
            return float(price.replace(',', '_'))

        except requests.exceptions.RequestException as e:
            print(f"Request failed for {self._symbol}: {e}")
            return -99


