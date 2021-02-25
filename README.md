# kaliberai

`git clone https://github.com/minyc510/kaliberai.git`

`cd kaliberai`

### READ ME

These are some notes about this challenge I'd like to place. Firstly I felt I did not get as far as I wanted to with this. My time management skills were definetely not on point with this. 

The biggest glaring issue I think you'll notice when making a request to the python server there's some issue when running the cpp executable, **basically it does not really work**. Running the cpp executable through the terminal works fine however.

Some logging to the python server would definitely have been nice.

### Thoughts I had on the C++ portion

I spent the most time on the C++ portion as that's what I thought was most interesting (despite the prompt saying to focus on the python). I felt like my whole thought process was worth 
explaining. Sorry for the long text.
---

Initially, I started by iterating each frame of the input video, and simply counting the frequency of each color, and then taking the maximum frequency and seeing if it exceeded 75% of the total pixel count for that frame. If it did, then exclude it in the output video.

After I ran that against the full input video given I noticed 0 frames were removed. That's when I noticed it was because of the "lens" of the video. I would describe it as looking through a peep hole, but  a large portion of the video is the black around the peephole. 

So I gave it some thought about how I can ignore the irrelevant pixels and focus on the inside of the "lens". At first I took a single frame, photoshopped the inside of the lens to be blank, and counted every black pixel. Then I could use that number and exclude them on the calculation.

But that felt too hard-codey and hacky.

So I took my dog, a 4.5lb Yorkshire Terrier, on a walk to think about this. I decided a better way would be to check each row and determine whats inside of the lens for that particular row. Imagine a row looks like this:

`BBBBBBBBBBBB[GGGGRGGGG]BBBBBBBBBBBBB`

Basically, some green and red surrounded by black. So I should scan the row and stop at the first non-black pixel. Then scan the row in reverse and also stop at the first non-black pixel. These two points would count as "inside the lens". 

Here's a crude render of an entire frame to show what I'm talking about.
```
BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBB[G]BBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBB[RRR]BBBBBBBBBBBBBBBBB
BBBBBBBBBBBBB[RRRGGGG]BBBBBBBBBBBBBBB
BBBBBBBBBBBBBBB[RRR]BBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBB[G]BBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
```

It's not a perfect algorithm but I felt like it was good enough for a 3 day assessment. I ran this against the full input and to my dismay, still 0 frames were removed! I went over my code a few times and I spent a lot of time trying to figure out what was wrong. I had tested each of my util functions separately and everything seemed to be fine. Then I remembered I had spent too much time here and had some python to write. 

Anyway so that's the full story. I've never worked with opencv or Flask before and I can't say I want to do anything in Flask again (it's not that interesting) but I think I'll look into opencv on my own time.


## Build and run C++

`cd cpp`

`make`

`./KaliberChallenge input-short.mp4`

Here you should see some output to console and when completed the file will be output to the `processed-media` directory.

## Run Python server
`cd python`

Set up and activate virtual env, install flask

`python3 -m venv venv`

`. venv/bin/activate`

`pip install Flask`

Run Flask

`Export FLASK_APP=server.py`

`flask run`

I used postman to send requests to this local server.