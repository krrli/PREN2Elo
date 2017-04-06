import serial

# Constants
NUMBER_OF_SENSORS=6

ERR_OK=b'\x00'
ERR_RANGE=b'\x02'
ERR_VALUE=b'\x03'

# Serial Interface
s=serial.Serial(
        port='/dev/ttyACM0',
        baudrate=9600,
        parity=serial.PARITY_EVEN,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS
)

s.isOpen()

# Start Test
res=s.read(1)
if res==ERR_OK:
	print('OK:    INIT')
else:
	print('ERROR: INIT')

#for i in range(0,NUMBER_OF_SENSORS-1):
res=s.read(1)
#print('Testing Sensor '+str(int.from_bytes(res,byteorder='little'))+':')
print('Testing Sensor '+str(int(res))+':')
res=s.read(1)
if res==ERR_OK:
    print('OK:    READ')
else:
	print('ERROR: READ')
res=s.read(2)
#print('Distance: '+str(int.from_bytes(res,byteorder='little'))+' mm')
intres=0
for b in res:
    res=res*256+int(b)
print('Distance: '+str(intres)+' mm')

