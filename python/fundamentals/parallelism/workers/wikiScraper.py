from bs4 import BeautifulSoup
import requests

class WikiScraper:
    def __init__(self, url):
        self._url = url
        
    @staticmethod    
    def get_table(html_doc):
        soup = BeautifulSoup(html_doc, 'html.parser')
        table = soup.find(id="constituents")
        if not table:
            print("no table found")

        rows = table.find_all("tr")
        for row in rows[1:]:
            symbol = row.find('td').text.strip('\n')
            yield symbol

    def scrape(self):
        headers = {
                "User-Agent": "MyWikiReader/1.0(brk@gmail.com)"
                }
        r = requests.get(self._url, headers=headers)
        if r.status_code != 200:
            print("Couldnt get responce.")
            r.raise_for_status()

        yield from self.get_table(r.text) 

