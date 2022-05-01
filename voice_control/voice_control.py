"""A simple script to control meArm robot using your own voice"""
import re
import sys
import time

import serial
import speech_recognition as sr

class ArduinoUno:
    """The class to represent an Arduino Uno board.

    Params:
        port: The port to which the board is connected.
    """

    def __init__(self, port: str) -> None:
        """Inits ArduinoUno with given port"""
        self.port = serial.Serial(port, 9600)

    def send_to_arduino(self, input: str):
        """Sends data to Arduino Uno.

        Args:
          input: data to send as a string.
        """
        self.port.write(input.encode())

def parse_and_send(input: str):
    """The function to parse the words spoken and convert 
    them into commands to send to the Arduino board.

    Args:
      input: The string to parse.
    """

    input = input.replace("uno","1").replace("due","2").replace("tre","3").replace("quattro","4")

    commands = re.findall(r"(\w+) (\d+) (\w+) (\d+)", input)

    if commands == []:
        return

    for i in range(len(commands)):
        cmd = commands[i][1] + " " + commands[i][3]
        ME_ARM.send_to_arduino(cmd)
        time.sleep(0.05)
        
def get_audio(lang: str) -> str:
    """Get audio from microphone and convert it to text.

    Returns:
      A string object containing the words spoken.
    """
    
    print("Listening")

    r = sr.Recognizer()

    with sr.Microphone() as source:
        audio = r.listen(source)

    said = ""

    try:
        print("Elaborating...")
        said = r.recognize_google(audio, language=lang)

    except Exception as e:
        print("Exception: " + str(e))

    print(said)
    return said.lower()

if __name__ == "__main__":
    ME_ARM = ArduinoUno(port="COM13")

    user_language = sys.argv[1]
    
    while True:
        input = get_audio(lang=user_language)
        parse_and_send(input)