

import requests

dht_info = {"data": ["AA"]}
r = requests.post("http://monospace-iot.trunksys.com/about", data=dht_info)


print (r.text)








