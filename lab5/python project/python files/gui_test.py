from tkinter import *
import tkinter.messagebox
from tkinter import filedialog
from PIL import Image,ImageTk
import numpy as np
import sys
import serial as ser
import time
import os

ACK = chr(6).encode()

MOUSE_X_OFFSET = 200
MOUSE_Y_OFFSET = 50
STATES = ["#0\n", "#1\n", "#2\n", "#3\n", "#4\n"]
DELAY = 0.001

USER = "YAKIR"
path = os.getcwd()
image = path +"\msp430.jpg"\


def Wait4ACK():
    while serial_comm.read(size=1) != ACK and serial_comm.in_waiting > 0:
        continue
    return

def transmit_data(data, delay=DELAY):
    # Writing the state and possibly the delay value.
    print("Transmitting :" + str(bytes(data, 'ascii')))
    serial_comm.write(bytes(data, 'ascii'))
    while serial_comm.out_waiting:  # while the output buffer isn't empty
        time.sleep(delay)  # delay for accurate read/write operations on both
#
# def receive_data_infintely_for_debug(serial_comm,delay=DELAY):
#     # Waiting until some data is received, after that happens we read the ecpected data according to
#     # state and then checking if the RX buffer is empty or we need to continue reading from it.
#     str = ""
#     while True:
#         if serial_comm.in_waiting:
#             x = serial_comm.read(size=1).decode("ascii")  # read 3 byte from the input buffer
#             time.sleep(delay)  # delay for accurate read/write operations on both ends
#             if x != '#':
#                 str += x
#             else:
#                 if str.isalnum():
#                     str = ""

def receive_angle_or_mode_change(serial_comm,delay=DELAY):
    # Waiting until some data is received, after that happens we read the ecpected data according to
    # state and then checking if the RX buffer is empty or we need to continue reading from it.
    str = ""
    while True:
        if serial_comm.in_waiting:
            x = serial_comm.read(size=1).decode("ascii")  # read 3 byte from the input buffer
            time.sleep(delay)  # delay for accurate read/write operations on both ends
            if x != '#':
                str += x
            else:
                if '$' in str:
                    return "$"
                if str.isalnum():
                    return str


class Paint(Toplevel):

    DEFAULT_PEN_SIZE = 5.0
    DEFAULT_COLOR = 'black'

    def __init__(self):
        self.root = Tk()
        self.root.geometry("600x600+{}+{}".format(MOUSE_X_OFFSET, MOUSE_Y_OFFSET))

        self.c = Canvas(self.root, bg='white', width=600, height=600)
        self.c.grid(row=1, columnspan=5)

        self.x_input      = 300
        self.y_input      = 300
        self.theta        = 0
        self.radius       = 5
        self.change_input = 0
        self.closing_app  = False
        self.draws_counter = 0
        self.radius_mode  = 0
        self.cursor_to_pen = False

        # serial_comm.reset_input_buffer()
        # serial_comm.reset_output_buffer()

        self.setup()
        self.root.protocol("WM_DELETE_WINDOW", self.on_closing)
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
        self.get_next_coordinate()

    def use_pen(self):
        self.cursor_mode   = False
        self.eraser_on     = False
        self.cursor_to_pen = False
        print("USING PEN\n"*10)

    def use_eraser(self):
        self.cursor_mode   = False
        self.eraser_on     = True
        self.cursor_to_pen = True
        print("USING ERASER\n"*10)

    def use_cursor(self):
        self.cursor_mode = True
        self.eraser_on   = False
        print("USING CURSOR\n"*10)

    def paint(self, theta):
        print(theta)
        if theta == 400:
            return
        if self.old_x == None:
            self.old_x = 300
            self.old_y = 300
            return
        x_offset = -int(self.radius*np.cos(theta*np.pi/180))
        y_offset = -int(self.radius*np.sin(theta*np.pi/180))
        x = x_offset + self.old_x
        y = y_offset + self.old_y
        if x<0:
            x=0
            print("problem")
        if x>600:
            x=600
            print("problem")
        if y<0:
            y=0
            print("problem")
        if y>600:
            y=600
            print("problem")


        paint_color = 'white' if self.eraser_on else self.color
        if not self.cursor_mode:
            if self.old_x and self.old_y:
                self.c.create_line(self.old_x, self.old_y, x, y,
                                   width=self.line_width, fill=paint_color,
                                   capstyle=ROUND, smooth=TRUE, splinesteps=36)
        else:
            move_mouse_to(MOUSE_X_OFFSET+x,MOUSE_Y_OFFSET+y)
        self.old_x = x
        self.old_y = y

    def get_next_input(self):
        test_bench_mode = False
        if test_bench_mode:
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
        else:
            input = receive_angle_or_mode_change(serial_comm)
            if input == "$":
                self.change_input = 1
            else:
                self.theta = int(input)


    def get_next_coordinate(self):
        if self.closing_app:
            return

        self.draws_counter += 1
        self.get_next_input()

        if self.change_input == 1:
            if self.cursor_mode:
                if self.cursor_to_pen:
                    self.use_pen()
                else:
                    self.use_eraser()
            elif self.eraser_on:
                self.use_cursor()
            else: # Pen mode
                self.use_cursor()
            self.change_input = 0
        else:
            self.paint(self.theta)
        root.after(1, self.get_next_coordinate)



serial_comm = ser.Serial('COM5', baudrate=9600, bytesize=ser.EIGHTBITS,
                         parity=ser.PARITY_NONE, stopbits=ser.STOPBITS_ONE,
                         timeout=1)
serial_comm.reset_input_buffer()
serial_comm.reset_output_buffer()

root = Tk()

root.geometry("1200x900")
root.title("Final project")

imge = Image.open(image)

photo=ImageTk.PhotoImage(imge)

lab = Label(image=photo)
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
    transmit_data(STATES[1])
    print("before ACK")
    Wait4ACK()
    print("after ACK")



def Joystick_based_PC_painter():
    transmit_data(STATES[2])
    print("before ACK")
    Wait4ACK()
    print("after ACK")
    #receive_data_infintely_for_debug(serial_comm)
    Paint()


def stepper_motor_calibration():
    transmit_data(STATES[3])
    print("before ACK")
    Wait4ACK()
    print("after ACK")
    tkinter.messagebox.showinfo("Stepper Motor Calibration",'the pointer are going to 0 degree \n the number on steps is: 2050\n every step angle is: 0.1756 degree')


def script_mode():
    transmit_data(STATES[4])
    print("before ACK")
    Wait4ACK()
    print("after ACK")



def sleep():
    transmit_data(STATES[0])
    print("before ACK")
    Wait4ACK()
    print("after ACK")


# Function for opening the
# file explorer window
def browseFiles(idx):
    filename = filedialog.askopenfilename(initialdir="/",
                                          title="Select a File",
                                          filetypes=(("Text files",
                                                      "*.txt*"),
                                                     ("all files",

                                                      "*.*")))
    script_name = filename.split('/')[-1]
    with open(filename, "r") as f:
        script_content = f.read()
    if idx == 1:
        script1_pb.config(text=script_name)
        Send_script(idx, script_name, script_content)
    elif idx == 2:
        script2_pb.config(text=script_name)
        Send_script(idx, script_name, script_content)
    elif idx == 3:
        script3_pb.config(text=script_name)
        Send_script(idx, script_name, script_content)


def Send_script(script_idx, script_name, script_content):
    ''' sends name and size of a script to MCU.
        sends the script content to MCU. '''
    script_content2send = '!' + script_content + '!'

    send_name = '$' + script_name + '\n'
    send_idx  = '%' + str(script_idx) + '\n'
    send_size = '@' + str(len(script_content2send)) + '\n'

    transmit_data(send_name)
    #print("Before ACK - name")
    Wait4ACK()
    #print("After ACK - name")

    transmit_data(send_idx)
    #print("Before ACK - idx")
    Wait4ACK()
    #print("After ACK - idx")

    transmit_data(send_size)
    #print("Before ACK - size")
    Wait4ACK()
    #print("After ACK - size")

    transmit_data(script_content2send)
    #print("Before ACK - content")
    Wait4ACK()
    #print("After ACK - content")


label_0 = Label(root,text="Final project",relief="solid",width=20,font=("arial",19,"bold"))
label_0.pack()



b1 = Button(root,text="Manual control of motor based machine",width=30,bg='brown',fg='white',command=manual_control_of_motor_based_machine)
b1.place(x=100,y=200)

b2 = Button(root,text="Joystick based PC painter",width=30,bg='brown',fg='white',command=Joystick_based_PC_painter)
b2.place(x=400,y=200)

b3 = Button(root,text="Stepper Motor Calibration",width=20,bg='brown',fg='white',command=stepper_motor_calibration)
b3.place(x=750,y=200)

b4 = Button(root,text="Script mode",width=12,bg='brown',fg='white',command=script_mode)
b4.place(x=1000,y=200)

b0 = Button(root,text="sleep",width=12,bg='brown',fg='white',command=sleep)
b0.place(x=100,y=100)

# var=StringVar()
# script_list = ['Script1','Script2','Script3']
# droplist=OptionMenu(root,var,*script_list)
# var.set("Select script")
# droplist.config(width=15)
# droplist.place(x=1000,y=300)

script1_pb = Button(root,text="Empty",width=12,bg='blue',fg='white',command=lambda idx=1: browseFiles(idx))
script1_pb.place(x=1000,y=350)
script2_pb = Button(root,text="Empty",width=12,bg='blue',fg='white',command=lambda idx=2: browseFiles(idx))
script2_pb.place(x=1000,y=400)
script3_pb = Button(root,text="Empty",width=12,bg='blue',fg='white',command=lambda idx=3: browseFiles(idx))
script3_pb.place(x=1000,y=450)



start_script1 = Button(root,text="Start script 1 run",width=12,bg='brown',fg='white',command=Joystick_based_PC_painter)
start_script1.place(x=900,y=350)

start_script2 = Button(root,text="Start script 2 run",width=12,bg='brown',fg='white',command=Joystick_based_PC_painter)
start_script2.place(x=900,y=400)

start_script3 = Button(root,text="Start script 3 run",width=12,bg='brown',fg='white',command=Joystick_based_PC_painter)
start_script3.place(x=900,y=450)

stop_script = Button(root,text="Stop script run",width=40,bg='brown',fg='white',command=Joystick_based_PC_painter)
stop_script.place(x=800,y=300)

root.mainloop()

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
