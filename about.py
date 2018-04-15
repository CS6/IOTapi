

import requests

dht_info = {"data": ["OFF"]}
r = requests.get("http://monospace-iot.trunksys.com/about")


print (r.text)








