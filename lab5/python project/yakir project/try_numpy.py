import tkinter as tk
from tkinter import *
import tkinter.messagebox
from tkinter.colorchooser import askcolor
from PIL import Image,ImageTk
import numpy as np
import sys
import serial as ser
import time


str = "adsff"
print("$")

def move_mouse_to(x, y):
    # Create a new temporary root
    temp_root = tk.Tk()
    # Move it to +0+0 and remove the title bar
    temp_root.overrideredirect(True)
    # Make sure the window appears on the screen and handles the `overrideredirect`
    temp_root.update()
    # Generate the event as @abarnert did
    temp_root.event_generate("<Motion>", warp=True, x=x, y=y)
    # Make sure that tcl handles the event
    temp_root.update()
    # Destroy the root
    temp_root.destroy()
