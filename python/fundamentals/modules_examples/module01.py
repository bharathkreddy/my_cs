#module01.py

print(f'---Running {__name__}---')
print('--------GLOBALS------')
d= globals().copy()
for k, v in d.items():
    print(f'{k}: {v}')
print(f'---End of {__name__}')


    
