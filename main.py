import serial
import time

def parseInt(input):
    intStr = ''
    for i in input:
        if i in [1, 2, 3, 4, 5, 6, 7, 8, 9, 0]:
             intStr = intStr + i
    return int(intStr)

if __name__ == '__main__':
    # Initialze
    portStr = input("Enter serial port: ")
    try:
        baudRate = int(input("Enter baud rate: "))
    except:
        raise Exception("Inputted baud rate must be an integer.")
    ser = serial.Serial(portStr, baudRate)
    ser.reset_input_buffer() # Clear incoming/outgoing signals
    ser.reset_output_buffer()
    time.sleep(3) # Allow arduino to reboot

    LEDState = 0 # Off by default

    # Serial Loop
    while True:
        try:
            if (ser.in_waiting > 0):
                # Read serial information
                line = ser.readline()
                potStr = line.decode('utf-8')
                print(potStr)
                potVal = 501
                # Publish LED state
                if (potVal > 500):
                    LEDState = 1
                else:
                    LEDState = 0
                sendStr = str(LEDState) + '\n'
                ser.write(sendStr.encode('utf-8'))
        except Exception as e:
            print("Exception raised. Closing serial communications. Exception details: ")
            print(e)
            ser.close()
            break