"""A simple script to make a meArm robot dance a given song."""

import random
import sys

import librosa
import serial

from pygame import mixer
from threading import Thread

class Arduino:
    """A class to represent an Arduino board.

    Attributes:
        port: A string indicating the port to which the Arduino board is connected.
    """
    def __init__(self, port: str) -> None:
        """Inits Arduino with given port."""
        self.port = serial.Serial(port, 9600)

class Song:
    """A class to represent a song.

    Attributes:
        path: A string indicating the path of the audio file.
    """

    def __init__(self, path: str) -> None:
        """Inits Song with given path."""
        self.path = path
        self.song, self.sample_rate = librosa.load(self.path)
        self.tempo, self.beat_times = librosa.beat.beat_track(self.song, sr=self.sample_rate, units='time')
        self.n_moves = len(self.beat_times)

class Choreographer:

    def __init__(self, path: str) -> None:
        self.song = Song(path)

    def generate_move(self) -> str:
        """The function to generate a dance move"""
        servo_motors = ["1", "2"]

        servo = random.choices(population=servo_motors, weights=[0.8, 0.2], k=1)[0]

        if servo == "3":
            angle = str(random.randint(140, 150))

        elif servo == "2":
            angle = str(random.randint(30, 80))

        else:
            angle = str(random.randint(0, 180))

        return servo + " " + angle

    def generate_dance(self) -> None:
        """The function to generate  a sequence of moves based on the beat times 
        and send them to the Arduino board."""
        i = 0
        while True:
            song_time = round(mixer.music.get_pos()/1000, 1)
            current_beat_time = round(self.song.beat_times[i], 1)

            if (song_time == current_beat_time):
                move = self.generate_move()
                ME_ARM.write(move.encode())
                i += 3
    
    def run(self) -> None:
        Thread(target=self.generate_dance).start()

if __name__ == "__main__":
    ME_ARM = serial.Serial("COM13")
    
    mixer.init()
    mixer.music.load(sys.argv[1])

    choreographer = Choreographer(path=sys.argv[1])
    choreographer.run()

    mixer.music.play()