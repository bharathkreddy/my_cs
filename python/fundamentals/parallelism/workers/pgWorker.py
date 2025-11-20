import os
from dotenv import load_dotenv
from supabase import create_client, Client
import threading

load_dotenv('../.env')

class PgWorker(threading.Thread):
    def __init__(self, url, key, input_queue):
        self._url = url 
        self._key = key 
        self._input_queue = input_queue
        super().__init__()

    def create_client(self):
        return create_client(self._url, self._key)
    
    def run(self):
        supabase = self.create_client()
        while True:
            payload = self._input_queue.get()
            if payload == 'DONE':
                print('thread DONE')
                break
            response = (
                supabase.table("snp")
                .insert(payload)
                .execute()
            )
            print(response)

