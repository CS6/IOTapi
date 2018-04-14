from flask import Flask, request
import time

app = Flask(__name__)

@app.route('/')
def hello_world():
    return ('hello world')

@app.route('/register', methods=['POST'])
def register():
    print (request.headers)
    print (request.form)
    print (request.form['name'])
    print (request.form.get('name'))
    print (request.form.getlist('name'))
    print (request.form.get('nickname', default='little apple'))
    return ('welcome')



@app.route('/login', methods=['POST'])
def login():
    print (request.headers)
    print (request.form)
    print (request.form['name'])
    print (request.form.get('name'))
    print (request.form.getlist('name'))
    print (request.form.get('nickname', default='little apple'))
    return ('welcome')

@app.route('/dht', methods=['POST'])
def dht():
    print (request.headers)
    print (request.form)
    print (request.form['H'])
    print (request.form.get('H'))
    print (request.form.getlist('H'))
    print (request.form['T'])
    print (request.form.get('T'))
    print (request.form.getlist('T'))
    print (request.form['H'],request.form['T'])
    #return ('welcome')
    time.sleep( 120 )
    return (request.form['T'])









if __name__ == '__main__':
    app.run(debug=True)
