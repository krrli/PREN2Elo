import serial

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

while True:
    res1=s.read(1)
    res2=s.read(1)
    if res2==ERR_OK:
        str2=' (OK)    '
        res3=s.read(2)
        intres3=0
        for b in res:
            intres3=intres3*256+int(b)
    else:
    	str2=' (ERROR) '
        intres3=0
    print('Sensor '+str(int(res1))+str2+': '+str(intres3)+' mm')

