import serial

# Constants
NUMBER_OF_MOTORS=4

ERR_OK=b'\x00'
ERR_RANG=b'\x02'
ERR_VALUE=b'\x03'

# Serial Interface
s=serial.Serial(
        port='/dev/ttyACM0',
        baudrate=9600,
        parity=serial.PARITY_NONE,
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

for i in range(0,NUMBER_OF_MOTORS-1):
	res=s.read(1)
	print('Testing Sensor '+res+':')
	res=s.read(1)
	if res==ERR_OK:
		print('OK:    SET DIRECTION')
	else:
		print('ERROR: SET DIRECTION')
	res=s.read(1)
	if res==ERR_OK:
		print('OK:    SET SPEED')
	else:
		print('ERROR: SET SPEED')

