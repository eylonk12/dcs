from tkinter import *
import tkinter.messagebox

from PIL import Image,ImageTk

root = Tk()
root.geometry("1200x900")
root.title("Final project")

imge = Image.open("C:/Users/Mesilati/PycharmProjects/test/msp430.jpg")
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
    tkinter.messagebox.showinfo("Stepper Motor Calibration",'the number on steps is: 2050\n every step angle is: 0.1756 degree')

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
