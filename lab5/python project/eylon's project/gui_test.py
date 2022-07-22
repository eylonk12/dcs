from tkinter import *
import tkinter.messagebox
from tkinter.colorchooser import askcolor
from PIL import Image,ImageTk
import numpy as np
import sys
import serial as ser
import time


class Paint(Toplevel):

    DEFAULT_PEN_SIZE = 5.0
    DEFAULT_COLOR = 'black'

    def __init__(self):
        self.root = Tk()

        # self.pen_button = Button(self.root, text='pen', command=self.use_pen)
        # self.pen_button.grid(row=0, column=0)
        #
        # self.eraser_button = Button(self.root, text='eraser', command=self.use_eraser)
        # self.eraser_button.grid(row=0, column=3)

        self.c = Canvas(self.root, bg='white', width=600, height=600)
        self.c.grid(row=1, columnspan=5)

        self.x_input      = 300
        self.y_input      = 300
        self.theta        = 0
        self.radius       = 1
        self.change_input = 0
        self.closing_app  = False
        self.draws_counter = 0
        self.radius_mode  = 0

        # serial_comm.reset_input_buffer()
        # serial_comm.reset_output_buffer()

        self.setup()
        self.root.protocol("WM_DELETE_WINDOW", self.on_closing)
        self.get_next_coordinate()
        self.root.mainloop()

    def on_closing(self):
        self.closing_app = True
        self.root.destroy()

    def setup(self):
        self.old_x = None
        self.old_y = None
        self.line_width = 4
        self.color = self.DEFAULT_COLOR
        self.eraser_on = False
        self.cursor_mode = False
        # self.active_button = self.pen_button
        # self.c.bind('<B1-Motion>', self.paint)
        # self.c.bind('<ButtonRelease-1>', self.reset)

    def use_pen(self):
        self.cursor_mode = False
        self.eraser_on   = False
        # self.activate_button(self.pen_button)

    def use_eraser(self):
        self.cursor_mode = False
        self.eraser_on   = True
        # self.activate_button(self.eraser_button, eraser_mode=True)

    def use_cursor(self):
        self.old_x, self.old_y = None, None
        self.cursor_mode = True
        self.eraser_on   = False

    def paint(self, theta):
        if self.old_x == None:
            self.old_x = 300
            self.old_y = 300
            return
        x_offset = int(self.radius*np.cos(theta))
        y_offset = int(self.radius*np.sin(theta))
        x = x_offset + self.old_x
        y = y_offset + self.old_y

        paint_color = 'white' if self.eraser_on else self.color
        if not self.cursor_mode:
            if self.old_x and self.old_y:
                self.c.create_line(self.old_x, self.old_y, x, y,
                                   width=self.line_width, fill=paint_color,
                                   capstyle=ROUND, smooth=TRUE, splinesteps=36)
        else:
            move_mouse_to(x,y)
        self.old_x = x
        self.old_y = y



    # def reset(self, event):
    #     self.old_x, self.old_y = None, None
    def reset(self):
        self.old_x, self.old_y = None, None

    def get_next_input(self):
        self.theta  = self.draws_counter/10
        if self.radius_mode == 0:
            self.radius += 0.1
        else:
            self.radius -= 1
        if self.radius > 10:
            self.radius_mode = 1
        if self.radius <= 0.1:
            self.radius_mode = 0
        if self.draws_counter % 50 == 0:
            self.change_input = 1
        else:
            self.change_input = 0


    def get_next_coordinate(self):
        if self.closing_app:
            return

        self.draws_counter += 1
        self.get_next_input()
        # self.theta = int(np.arctan2(self.x_input, self.y_input))

        if self.change_input == 1:
            if self.cursor_mode:
                self.use_pen()
            elif self.eraser_on:
                self.use_cursor()
            else: # Pen mode
                self.use_eraser()
            self.reset()
        # self.paint(self.x_input, self.y_input)
        self.paint(self.theta)
        root.after(10, self.get_next_coordinate)

        # while True:
        #     if serial_comm.in_waiting:
        #         menu = serial_comm.read_until('\r').decode("ascii")
        #
        #     else:
        #         pot = serial_comm.read(size=5).decode("ascii")  # read 3 byte from the input buffer
        #         pot = pot.replace('\0', '')
        #
        #         if not serial_comm.in_waiting:
        #             return


# serial_comm = ser.Serial('COM5', baudrate=9600, bytesize=ser.EIGHTBITS,
#                          parity=ser.PARITY_NONE, stopbits=ser.STOPBITS_ONE,
#                          timeout=1)
# serial_comm.reset_input_buffer()
# serial_comm.reset_output_buffer()

root = Tk()

root.geometry("1200x900")
root.title("Final project")

imge = Image.open("C:/Users/eylonk/dcs/lab5/python project/eylon's project/msp430.jpg")
photo=ImageTk.PhotoImage(imge)

lab=Label(image=photo)
lab.pack()


menu = Menu(root)
root.config(menu=menu)

subm1=Menu(menu)
menu.add_cascade(label="File", menu=subm1)
subm1.add_command(label="Exit")

subm2=Menu(menu)
menu.add_cascade(label="Option", menu=subm2)
subm2.add_command(label="About")


fn = StringVar()
ln = StringVar()

def manual_control_of_motor_based_machine():
    tkinter.messagebox.showinfo("manual control of motor based machine",'now the joystick controlling the pointer on the motor')


def Joystick_based_PC_painter():
    Paint()

def stepper_motor_calibration():
    tkinter.messagebox.showinfo("Stepper Motor Calibration",'the pointer are going to 0 degree \n the number on steps is: 2050\n every step angle is: 0.1756 degree')

def script_mode():
    exit()

def exit1():
    exit()


label_0 = Label(root,text="Final project",relief="solid",width=20,font=("arial",19,"bold"))
label_0.pack()



b1 = Button(root,text="Manual control of motor based machine",width=30,bg='brown',fg='white',command=manual_control_of_motor_based_machine)
b1.place(x=100,y=200)

b2 = Button(root,text="Joystick based PC painter",width=30,bg='brown',fg='white',command=Joystick_based_PC_painter)
b2.place(x=400,y=200)

b3 = Button(root,text="Stepper Motor Calibration",width=20,bg='brown',fg='white',command=stepper_motor_calibration)
b3.place(x=750,y=200)

b4 = Button(root,text="Script mode",width=12,bg='brown',fg='white',command=exit1)
b4.place(x=1000,y=200)

var=StringVar()
script_list = ['Script1','Script2','Script3']
droplist=OptionMenu(root,var,*script_list)
var.set("Select script")
droplist.config(width=15)
droplist.place(x=1000,y=300)




def move_mouse_to(x, y):
    # Create a new temporary root
    temp_root = tkinter.Tk()
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











root.mainloop()










# label_1 = Label(root,text="FirstName :",width=20,font=("arial",10,"bold"))
# label_1.place(x=80,y=200)
#
# entry_1 = Entry(root,textvar=fn)
# entry_1.place(x=300,y=200)
#
# label_2 = Label(root,text="LastName :",width=20,font=("arial",10,"bold"))
# label_2.place(x=80,y=300)
#
# entry_2 = Entry(root,textvar=ln)
# entry_2.place(x=300,y=300)
#
