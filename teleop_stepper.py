import time
import serial
from pynput import keyboard

PORT = "COM3"      
BAUD = 115200

tt = 0  
sh = 0  
el = 0  

def send(ser):
    ser.write(f"T{tt}S{sh}E{el}\n".encode())

def on_press(key):
    global tt, sh, el
    changed = False

    if key == keyboard.Key.right:
        if tt != 1: tt = 1; changed = True
    elif key == keyboard.Key.left:
        if tt != -1: tt = -1; changed = True
    elif key == keyboard.Key.up:
        if sh != 1: sh = 1; changed = True
    elif key == keyboard.Key.down:
        if sh != -1: sh = -1; changed = True
    else:
        try:
            if key.char in ('w', 'W'):
                if el != 1: el = 1; changed = True
            elif key.char in ('s', 'S'):
                if el != -1: el = -1; changed = True
        except:
            pass

    if changed:
        send(ser)

def on_release(key):
    global tt, sh, el
    changed = False

    if key == keyboard.Key.right and tt == 1:
        tt = 0; changed = True
    elif key == keyboard.Key.left and tt == -1:
        tt = 0; changed = True
    elif key == keyboard.Key.up and sh == 1:
        sh = 0; changed = True
    elif key == keyboard.Key.down and sh == -1:
        sh = 0; changed = True
    else:
        try:
            if key.char in ('w','W') and el == 1:
                el = 0; changed = True
            elif key.char in ('s','S') and el == -1:
                el = 0; changed = True
        except:
            pass

    if changed:
        send(ser)

    if key == keyboard.Key.esc:
        return False

if __name__ == "__main__":
    ser = serial.Serial(PORT, BAUD, timeout=0)
    time.sleep(2)  # Arduino reset
    send(ser)

    listener = keyboard.Listener(
        on_press=lambda k: on_press(k),
        on_release=on_release
    )
    listener.start()

    try:
        while listener.is_alive():
            time.sleep(0.2)
            send(ser)
    finally:
        tt = sh = el = 0
        send(ser)
        ser.close()
