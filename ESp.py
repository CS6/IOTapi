import requests

dht_info = {"data": [[48.75608,2.302038],[0,0]]}
r = requests.post("http://monospace-iot.trunksys.com/postjson", data=dht_info)

print (r.text)









