

import requests

dht_info = {"data": ["OFF"]}
r = requests.post("http://monospace-iot.trunksys.com/about", data=dht_info)


print (r.text)






