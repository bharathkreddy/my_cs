import httpx
import aiofiles
import os
import re
import asyncio

DOWNLOAD_IMAGE_PATH = 'originalpics'
PROCESS_IMAGE_PATH = 'afterpics'

IMAGE_URLS = [
    "https://images.unsplash.com/photo-1516117172878-fd2c41f4a759?w=1920&h=1080&fit=crop",
    "https://images.unsplash.com/photo-1532009324734-20a7a5813719?w=1920&h=1080&fit=crop",
    "https://images.unsplash.com/photo-1524429656589-6633a470097c?w=1920&h=1080&fit=crop",
    "https://images.unsplash.com/photo-1530224264768-7ff8c1789d79?w=1920&h=1080&fit=crop",
    "https://images.unsplash.com/photo-1564135624576-c5c88640f235?w=1920&h=1080&fit=crop",
    "https://images.unsplash.com/photo-1541698444083-023c97d3f4b6?w=1920&h=1080&fit=crop",
    "https://images.unsplash.com/photo-1522364723953-452d3431c267?w=1920&h=1080&fit=crop",
    "https://images.unsplash.com/photo-1493976040374-85c8e12f0c0e?w=1920&h=1080&fit=crop",
    "https://images.unsplash.com/photo-1530122037265-a5f1f91d3b99?w=1920&h=1080&fit=crop",
    "https://images.unsplash.com/photo-1516972810927-80185027ca84?w=1920&h=1080&fit=crop",
    "https://images.unsplash.com/photo-1550439062-609e1531270e?w=1920&h=1080&fit=crop",
    "https://images.unsplash.com/photo-1549692520-acc6669e2f0c?w=1920&h=1080&fit=crop",
]


def delete_files(file_path):
    files_ = [os.path.join(file_path, f) for f in os.listdir(file_path)]
    for file in files_:
        os.remove(file)

async def download_single_image(client, url):
    match = re.search(r"(photo-\d+)", url)
    file_name = f'{match.group(1)}.jpg'
    file_path = os.path.join(DOWNLOAD_IMAGE_PATH, file_name)
    r = await client.get(url)
    r.raise_for_status()
    async with aiofiles.open(file_path, mode='wb') as f:
        await f.write(r.content)

    print(f'{file_name} saved.')

## NOTES
# 1. we dont need to create threads for asych functions!
# 2. other tasks are picked be same worker when a tasks waits
# 3. anyways due to GIL only one thread runs at a time on the CPU.

async def download_all_images(image_urls):
    async with httpx.AsyncClient() as client:
        tasks = [download_single_image(client, url) for url in image_urls]
        await asyncio.gather(*tasks)



if __name__ == '__main__':
    delete_files(DOWNLOAD_IMAGE_PATH)
    asyncio.run(download_all_images(IMAGE_URLS))
    
    
