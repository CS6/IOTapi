

from flask import Flask
from flask import request


app = Flask(__name__)

io='OFF'

@app.route('/postjson', methods = ['POST'])
def postJsonHandler():
    content = request.get_json()
    print (content)
    return ('Json Pass')




@app.route('/dht', methods=['POST'])
def dht():
    print (request.form['H'],request.form['T'])
    #return ('welcome')
    io=request.form['T']
    #time.sleep( 120 )
    return (request.form['T'])


@app.route('/about')
def about():
    num='AA'
    if  request.form["data"] != Null:
        print (request.form["data"])
        num=request.form["data"]
    return  num





if __name__ == '__main__':
   # app.run(debug=True)
    app.run(host='0.0.0.0')







