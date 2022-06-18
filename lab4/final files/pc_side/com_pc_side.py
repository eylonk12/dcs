import sys
import serial as ser
import time


def transmit_data(serial_comm, state, delay=1):
    # Writing the state and possibly the delay value.
    serial_comm.write(bytes(state, 'ascii'))
    while serial_comm.out_waiting:  # while the output buffer isn't empty
        time.sleep(delay)  # delay for accurate read/write operations on both
    if state == '1':
        print("-----------------Blinking RGB LED------------------")
    elif state == '2':
        print("----------------   Counting Up   ------------------")
    elif state == '3':
        print("----------------  Counting Down  ------------------")
    elif state == '4':
        print("-----------------Getting New Delay------------------")
        msp_delay = input("Please enter new delay: ")
        serial_comm.write(bytes(msp_delay + '\0', 'ascii'))
        while serial_comm.out_waiting:  # while the output buffer isn't empty
            time.sleep(delay)  # delay for accurate read/write operations on both ends
    elif state == '5':
        print("----------------- Potentiometer -----------------")
    elif state == '6':
        print("----------------- Clear LCD screen -----------------")
    elif state == '8':
        print("----------------- Sleeping Mode -----------------")
    else:
        if state != '7':
            print(10 * " ERROR : unexpected value for state when waiting to receive data, expected 5/7 actual : {}\n".format(state))

    return


def receive_data(serial_comm, state, delay=0.25):
    # Waiting until some data is received, after that happens we read the ecpected data according to
    # state and then checking if the RX buffer is empty or we need to continue reading from it.
    while True:
        if serial_comm.in_waiting:
            if state == '7':
                menu = serial_comm.read_until('\r').decode("ascii")
                print(menu)
            elif state == '5':
                pot = serial_comm.read(size=5).decode("ascii")  # read 3 byte from the input buffer
                pot = pot.replace('\0', '')
                volt = str(3.3 * int(pot) / 1024)
                print("Potentiometer value: " + volt[:5] + " [Volt]")

            time.sleep(delay)  # delay for accurate read/write operations on both ends
            if not serial_comm.in_waiting:
                return


def main():
    # Using pyserial library, defining an UART serial communicaton object through the USB port.
    serial_comm = ser.Serial('COM5', baudrate=9600, bytesize=ser.EIGHTBITS,
                             parity=ser.PARITY_NONE, stopbits=ser.STOPBITS_ONE,
                             timeout=1)
    serial_comm.reset_input_buffer()
    serial_comm.reset_output_buffer()

    # To synchronize with the microprocessor, waiting at the start until receiving the menu.
    receive_data(serial_comm, state='7')

    while True:
        state = input("Please enter your function choice: ")
        transmit_data(serial_comm, state)
        # Waiting to receive values only in these states.
        if state == '5' or state == '7':
            receive_data(serial_comm, state)


if __name__ == "__main__":
    main()
