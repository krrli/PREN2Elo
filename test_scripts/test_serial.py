import serial

# Constants
START=b'\x80'
ROMAN_NUMBER_REQUEST=b'\x40'
CURVE=b'\x08'
PAUSE=b'\xB0'
RESUME=b'\x70'
ACKNOWLEDGE=b'\x20'
ERROR=b'\x10'
BUTTON1=b'\x01'
BUTTON2=b'\x02'
BUTTON3=b'\x03'
BUTTON4=b'\x04'
BUTTON5=b'\x05'
WRONG1=b'\x06'
WRONG2=b'\x07'
WRONG3=b'\x09'
WRONG4=b'\x0A'
WRONG5=b'\x0B'
WRONG6=b'\x0C'
WRONG7=b'\x0D'
WRONG8=b'\x0E'
WRONG9=b'\x0F'
WRONG10=b'\xC3'
WRONG11=b'\xDA'
WRONG12=b'\x56'
WRONG13=b'\x77'
WRONG14=b'\x13'
WRONG15=b'\x95'
WRONG16=b'\xFF'

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
s.write(START)
res=s.read(1)
if res==ACKNOWLEDGE:
	print('OK:    START')
else:
	print('ERROR: START')

s.write(PAUSE)
res=s.read(1)
if res==ACKNOWLEDGE:
	print('OK:    PAUSE')
else:
	print('ERROR: PAUSE')

s.write(RESUME)
res=s.read(1)
if res==ACKNOWLEDGE:
	print('OK:    RESUME')
else:
	print('ERROR: RESUME')

s.write(ERROR)
res=s.read(1)
if res==ACKNOWLEDGE:
	s.write(WRONG1) # returns error
	res=s.read(1)
	s.write(ERROR)
	res=s.read(1)
	if res==ERROR:
		print('OK:    ERROR')
	else:
		print('ERROR: ERROR')
else:
	print('ERROR: ERROR')

s.write(ROMAN_NUMBER_REQUEST)
res=s.read(1)
if res==ERROR:
	print('OK:    ROMAN_NUMBER_REQUEST')
else:
	print('ERROR: ROMAN_NUMBER_REQUEST')

s.write(CURVE)
res=s.read(1)
if res==ERROR:
	print('OK:    CURVE')
else:
	print('ERROR: CURVE')

s.write(BUTTON1)
res=s.read(1)
if res==ERROR:
	print('OK:    BUTTON1')
else:
	print('ERROR: BUTTON1')

s.write(BUTTON2)
res=s.read(1)
if res==ERROR:
	print('OK:    BUTTON2')
else:
	print('ERROR: BUTTON2')

s.write(BUTTON3)
res=s.read(1)
if res==ERROR:
	print('OK:    BUTTON3')
else:
	print('ERROR: BUTTON3')

s.write(BUTTON4)
res=s.read(1)
if res==ERROR:
	print('OK:    BUTTON4')
else:
	print('ERROR: BUTTON4')

s.write(BUTTON5)
res=s.read(1)
if res==ERROR:
	print('OK:    BUTTON5')
else:
	print('ERROR: BUTTON5')

# wrong commands
s.write(WRONG1)
res=s.read(1)
if res==ERROR:
	print('OK:    WRONG1')
else:
	print('ERROR: WRONG1')

s.write(WRONG2)
res=s.read(1)
if res==ERROR:
	print('OK:    WRONG2')
else:
	print('ERROR: WRONG2')

s.write(WRONG3)
res=s.read(1)
if res==ERROR:
	print('OK:    WRONG3')
else:
	print('ERROR: WRONG3')

s.write(WRONG4)
res=s.read(1)
if res==ERROR:
	print('OK:    WRONG4')
else:
	print('ERROR: WRONG4')

s.write(WRONG5)
res=s.read(1)
if res==ERROR:
	print('OK:    WRONG5')
else:
	print('ERROR: WRONG5')

s.write(WRONG6)
res=s.read(1)
if res==ERROR:
	print('OK:    WRONG6')
else:
	print('ERROR: WRONG6')

s.write(WRONG7)
res=s.read(1)
if res==ERROR:
	print('OK:    WRONG7')
else:
	print('ERROR: WRONG7')

s.write(WRONG8)
res=s.read(1)
if res==ERROR:
	print('OK:    WRONG8')
else:
	print('ERROR: WRONG8')

s.write(WRONG9)
res=s.read(1)
if res==ERROR:
	print('OK:    WRONG9')
else:
	print('ERROR: WRONG9')

s.write(WRONG10)
res=s.read(1)
if res==ERROR:
	print('OK:    WRONG10')
else:
	print('ERROR: WRONG10')

s.write(WRONG11)
res=s.read(1)
if res==ERROR:
	print('OK:    WRONG11')
else:
	print('ERROR: WRONG11')

s.write(WRONG12)
res=s.read(1)
if res==ERROR:
	print('OK:    WRONG12')
else:
	print('ERROR: WRONG12')

s.write(WRONG13)
res=s.read(1)
if res==ERROR:
	print('OK:    WRONG13')
else:
	print('ERROR: WRONG13')

s.write(WRONG14)
res=s.read(1)
if res==ERROR:
	print('OK:    WRONG14')
else:
	print('ERROR: WRONG14')

s.write(WRONG15)
res=s.read(1)
if res==ERROR:
	print('OK:    WRONG15')
else:
	print('ERROR: WRONG15')

s.write(WRONG16)
res=s.read(1)
if res==ERROR:
	print('OK:    WRONG16')
else:
	print('ERROR: WRONG16')

# wait for curve
res=s.read(1)
if res==CURVE:
	print('OK:    CURVE')
else:
	print('ERROR: CURVE')

# wait for rom. num. req.
res=s.read(1)
if res==ROMAN_NUMBER_REQUEST:
	print('OK:    ROMAN_NUMBER_REQUEST')
else:
	print('ERROR: ROMAN_NUMBER_REQUEST')

