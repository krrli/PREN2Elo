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
        #for b in res:
        #    intres3=intres3*256+int(b)
        intres3=res3[0]*256+res3[1]
    else:
        str2=' (ERROR) '
        s.read(2)
        intres3=0
    strprint1='Sensor '+str(int(res1[0]))+str2+': '+str(intres3)+' mm'
    #
    res1=s.read(1)
    res2=s.read(1)
    if res2==ERR_OK:
        str2=' (OK)    '
        res3=s.read(2)
        intres3=0
        #for b in res:
        #    intres3=intres3*256+int(b)
        intres3=res3[0]*256+res3[1]
    else:
        str2=' (ERROR) '
        s.read(2)
        intres3=0
    strprint2='Sensor '+str(int(res1[0]))+str2+': '+str(intres3)+' mm'
    # 
    res1=s.read(1)
    res2=s.read(1)
    if res2==ERR_OK:
        str2=' (OK)    '
        res3=s.read(2)
        intres3=0
        #for b in res:
        #    intres3=intres3*256+int(b)
        intres3=res3[0]*256+res3[1]
    else:
        str2=' (ERROR) '
        s.read(2)
        intres3=0
    strprint3='Sensor '+str(int(res1[0]))+str2+': '+str(intres3)+' mm'
    #
    res1=s.read(1)
    res2=s.read(1)
    if res2==ERR_OK:
        str2=' (OK)    '
        res3=s.read(2)
        intres3=0
        #for b in res:
        #    intres3=intres3*256+int(b)
        intres3=res3[0]*256+res3[1]
    else:
        str2=' (ERROR) '
        s.read(2)
        intres3=0
    strprint4='Sensor '+str(int(res1[0]))+str2+': '+str(intres3)+' mm'
    #
    res1=s.read(1)
    res2=s.read(1)
    if res2==ERR_OK:
        str2=' (OK)    '
        res3=s.read(2)
        intres3=0
        #for b in res:
        #    intres3=intres3*256+int(b)
        intres3=res3[0]*256+res3[1]
    else:
        str2=' (ERROR) '
        s.read(2)
        intres3=0
    strprint5='Sensor '+str(int(res1[0]))+str2+': '+str(intres3)+' mm'
    #
    print(strprint1+' '+strprint2+' '+strprint3+' '+strprint4+' '+strprint5)

