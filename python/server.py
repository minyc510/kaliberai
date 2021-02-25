from flask import Flask, request, Response
import subprocess
from subprocess import Popen, PIPE
import os.path
from os import path

app = Flask(__name__)

@app.route('/video/<video_name>', methods=['POST'])
def video(video_name):
    uri = '../media/' + video_name
    if path.exists(uri):
        p = subprocess.Popen(['../cpp/KaliberChallenge', uri], stdout=PIPE)
        return 'Request received, processing started.'
    else:
        return Response("{'message':'File not found.'}", status=400, mimetype='application/json')