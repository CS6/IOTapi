

from flask import Flask
from flask import request

global  io

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


@app.route('/about', methods=['POST'] )
def about():
    print (request.headers)
    print (request.form)
    print (request.form['data'])
    return  (request.form['data'])
    io == request.form['data']

@app.route('/about')
def aboutGet():
    return  (io)








if __name__ == '__main__':
   # app.run(debug=True)
    app.run(debug=True,host='0.0.0.0')







