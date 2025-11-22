import requests
from time import perf_counter, sleep
import os
from PIL import Image
import asyncio
import re
from concurrent.futures import ProcessPoolExecutor

## PROFILER ###
# uv run -m scalene --html --outfile profile_report.html async_example01.py
# output: 
# Sequenctial download: 25.54s, Process: 18.42s
# Parallel download: 2.80s, Process: 5.19s


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

original_pics_dir = 'originalpics'
process_pics_dir = 'afterpics'

def download_single_image(url):
    match = re.search(r"(photo-\d+)", url)
    file_name = f'{match.group(1)}.jpg'
    save_path = original_pics_dir
    os.makedirs(save_path, exist_ok = True)
    r = requests.get(url)
    r.raise_for_status() 
    with open (os.path.join(save_path, file_name), 'wb') as f:
        f.write(r.content)
    sleep(2)


async def async_download():
    tasks = [asyncio.create_task(asyncio.to_thread(download_single_image, image_url)) for image_url in IMAGE_URLS]
    results = asyncio.gather(*tasks, return_exceptions=True)
    return results


def process_single_image(image_path):
    with Image.open(image_path) as img:
        data = list(img.getdata())
        width, height = img.size
        new_data = []

        for i in range(len(data)):
            current_r, current_g, current_b = data[i]

            total_diff = 0
            neighbor_count = 0

            for dx, dy in [(1, 0), (0, 1)]:
                x = (i % width) + dx
                y = (i // width) + dy

                if 0 <= x < width and 0 <= y < height:
                    neighbor_r, neighbor_g, neighbor_b = data[y * width + x]
                    diff = (
                        abs(current_r - neighbor_r)
                        + abs(current_g - neighbor_g)
                        + abs(current_b - neighbor_b)
                    )
                    total_diff += diff
                    neighbor_count += 1

            edge_strength = total_diff // neighbor_count if neighbor_count else 0
            new_data.append((255,255,255) if edge_strength > 30 else (0,0,0))

        edge_img = Image.new("RGB", (width, height))
        edge_img.putdata(new_data)

        save_path = "afterpics"
        os.makedirs(save_path, exist_ok=True)

        fname = os.path.basename(image_path)
        edge_img.save(os.path.join(save_path, fname))


if __name__ == '__main__':
    for filename in os.listdir(original_pics_dir):
        file_path = os.path.join(original_pics_dir, filename)
        # Only remove files
        if os.path.isfile(file_path):
            os.remove(file_path)

    start_time_download = perf_counter()
    for url in IMAGE_URLS:
        download_single_image(url) 
    end_time_download = perf_counter()
    
    for filename in os.listdir(process_pics_dir):
        file_path = os.path.join(process_pics_dir, filename)
        # Only remove files
        if os.path.isfile(file_path):
            os.remove(file_path)

    start_time_process = perf_counter()
    for f in os.listdir(original_pics_dir):
        process_single_image(os.path.join(original_pics_dir, f))
    end_time_process = perf_counter()
    
    print(f'Sequenctial download: {end_time_download - start_time_download:.2f}s, Process: {end_time_process - start_time_process:.2f}s\n')

    
    for filename in os.listdir(original_pics_dir):
        file_path = os.path.join(original_pics_dir, filename)
        # Only remove files
        if os.path.isfile(file_path):
            os.remove(file_path)

    start_time_download = perf_counter()
    results = asyncio.run(async_download()) 
    end_time_download = perf_counter()

    for filename in os.listdir(process_pics_dir):
        file_path = os.path.join(process_pics_dir, filename)
        # Only remove files
        if os.path.isfile(file_path):
            os.remove(file_path)

    start_time_process = perf_counter()
    
    file_list = [os.path.join(original_pics_dir, f) for f in os.listdir(original_pics_dir)]

    with ProcessPoolExecutor(max_workers=10) as ex:
        ex.map(process_single_image, file_list)

    end_time_process = perf_counter()
    
    print(f'Parallel download: {end_time_download - start_time_download:.2f}s, Process: {end_time_process - start_time_process:.2f}s\n')
    
