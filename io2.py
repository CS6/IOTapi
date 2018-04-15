

import requests

dht_info = {'H': 'OFF', 'T': 'ON'}
r = requests.post("http://127.0.0.1:5000/dht", data=dht_info)

print (r.text)














