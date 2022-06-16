import sys
import serial as ser
import time

state = '7'
j = 0


def receive_data(serial_comm, enableTX, delay=0.25):
    global state, first_time
    # RX
    while serial_comm.in_waiting:  # while the input buffer isn't empty
        if state == '7':
            menu = serial_comm.read_until('\r').decode("ascii")
            print(menu)
            enableTX = True
            first_time = False
        elif state == '5':
            pot = serial_comm.read(size=5).decode("ascii")  # read 3 byte from the input buffer
            pot = pot.replace('\0', '')
            volt = str(3.3 * int(pot) / 1024)
            print("Potentiometer value: " + volt[:5] + " [Volt]")

            state = '8'
            enableTX = False

        time.sleep(delay)  # delay for accurate read/write operations on both ends
    return enableTX


def transmit_data(serial_comm, enableTX, delay=1):
    while serial_comm.out_waiting or enableTX:  # while the output buffer isn't empty
        global state, first_time
        # state = input("Please enter your function choice: ")
        serial_comm.write(bytes(state, 'ascii'))
        time.sleep(delay)  # delay for accurate read/write operations on both
        if state == '1':
            print("-----------------Blinking RGB LED------------------")
        elif state == '2':
            print("----------------   Counting Up   ------------------")
        elif state == '3':
            print("----------------  Counting Down  ------------------")
        elif state == '4':
            print("-----------------Getting New Delay------------------")
            x = input("Please enter new delay: ")
            serial_comm.write(bytes(x + '\0', 'ascii'))
            time.sleep(delay)  # delay for accurate read/write operations on both ends
        elif state == '5':
            print("----------------- Potentiometer -----------------")
        elif state == '6':
            print("----------------- Clear LCD screen -----------------")
        elif state == '8':
            print("----------------- Sleeping Mode -----------------")
        # if state != '5':
        #     print("Please Push PB0 to display menu.")

        if serial_comm.out_waiting == 0:

            return False
    return enableTX


def start_communication():
    global state,first_time
    serial_comm = ser.Serial('COM3', baudrate=9600, bytesize=ser.EIGHTBITS,
                             parity=ser.PARITY_NONE, stopbits=ser.STOPBITS_ONE,
                             timeout=1)
    serial_comm.reset_input_buffer()
    serial_comm.reset_output_buffer()
    enableTX = False
    first_time = True
    # print_art()
    # print("Please Push PB0 to display menu.")
    while 1:
        if first_time is False and state != '5':
            state = input("Please enter your function choice: ")
            enableTX = True
        # TX
        enableTX = transmit_data(serial_comm, enableTX)
        # RX
        enableTX = receive_data(serial_comm, enableTX)


def main():
    start_communication()


if __name__ == "__main__":
    main()
