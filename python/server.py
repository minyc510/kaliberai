from flask import Flask, request, Response
import subprocess
from subprocess import Popen, PIPE
from os import path
from logging import FileHandler, WARNING

app = Flask(__name__)

file_handler = FileHandler('errorlog.txt')
file_handler.setLevel(WARNING)

app.logger.addHandler(file_handler)

@app.route('/video/<video_name>', methods=['POST'])
def video(video_name):
    uri = '../media/' + video_name
    print(uri)
    if path.exists(uri):
        p = subprocess.Popen(['../cpp/KaliberChallenge', uri], stdout=PIPE)
        return 'Request received, processing started.'
    else:
        return Response("{'message':'File not found.'}", status=400, mimetype='application/json')