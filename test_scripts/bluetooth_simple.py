import serial
import threading

s=serial.Serial(
        port='/dev/rfcomm0',
        baudrate=9600,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS
)

s.isOpen()

def writeByteToSerial(data):
    s.write(data)

def printByte():
    while True:
        print('FD: '+str(s.read(1)))

t=threading.Thread(target=printByte)
t.daemon=True
t.start()

# Start with:
#python -i <name.py> # -> python3

# Example:
#writeByteToSerial(b'\x80')

