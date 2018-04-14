import requests

dht_info = {'H': '22.55', 'T': '22.44'}
r = requests.post("http://127.0.0.1:5000/dht", data=dht_info)

print (r.text)
