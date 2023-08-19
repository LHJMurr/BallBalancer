import serial
import time

if __name__ == '__main__':
    # Initialze
    portStr = input("Enter serial port: ")
    try:
        baudRate = int(input("Enter baud rate: "))
    except:
        raise Exception("Inputted baud rate must be an integer.")
    ser = serial.Serial(portStr, baudRate, timeout = 1.0)
    ser.reset_input_buffer() # Clear incoming/outgoing signals
    ser.reset_output_buffer()
    time.sleep(3)

    LEDState = 0 # Off by default

    # Serial Loop
    try:
        while True:
            if (ser.in_waiting > 0):
                # Read serial information
                line = ser.readline()
                potStr = line.decode('utf-16').strip()
                potVal = int(potStr)
                print(f'REPR of decoded string: {repr(potStr)}   ||   Integer Value detected: {potVal}')
                # Publish LED state
                if (potVal > 500):
                    LEDState = 1
                else:
                    LEDState = 0
                sendStr = str(LEDState) + '\n'
                print(f'String to send: {repr(sendStr)}')
                ser.write(sendStr.encode('utf-8'))
    except Exception as e:
        print("Exception raised. Closing serial communications...")
        print(e)
        ser.close()
    finally:
        ser.close()