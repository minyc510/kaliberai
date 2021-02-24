from flask import Flask, request
import subprocess
from subprocess import Popen, PIPE
import os.path
from os import path

app = Flask(__name__)

@app.route('/')
def hello_world():
    return 'Hello, World!'

@app.route('/video/<video_name>', methods=['POST'])
def video(video_name):
    uri = '../media/' + video_name
    if path.exists(uri):
        p = subprocess.Popen(['../cpp/KaliberChallenge', uri], stdout=PIPE)
        print('File exists cool I guess now lets figure out how to call our C++ executable here')
        return 'Exists'
    else:
        print('File aint here chief')
        return 'DNE'