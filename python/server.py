from flask import Flask
from flask import request
import os.path
from os import path

app = Flask(__name__)

@app.route('/')
def hello_world():
    return 'Hello, World!'

@app.route('/video/<video_name>', methods=['POST'])
def video(video_name):
    if path.exists(video_name):
        print('File exists cool I guess now lets figure out how to call our C++ executable here')
        return 'Exists'
    else:
        print('File aint here chief')
        return 'DNE'