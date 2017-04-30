import serial

DEBUG_ERROR_INIT_MOTOR=b'\xC1'
DEBUG_ERROR_INIT_SERVO=b'\xC2'
DEBUG_ERROR_INIT_TOF=b'\xC3'
DEBUG_ERROR_END_LOOP_REACHED=b'\xC4'
DEBUG_ERROR_SET_MOTOR_SPEED=b'\xC5'
DEBUG_ERROR_SET_MOTOR_DIRECTION=b'\xC6'
DEBUG_ERROR_SET_BRUSHLESS=b'\xC7'
DEBUG_ERROR_SET_SERVO=b'\xC8'
DEBUG_ERROR_GET_TOF_VALUE=b'\xC9'
DEBUG_ERROR_WRONG_BUTTON_NUMBER=b'\xCA'

ACKNOWLEDGE=b'\x20'
ERROR=b'\x10'
BUTTON1=b'\x01'
BUTTON2=b'\x02'
BUTTON3=b'\x03'
BUTTON4=b'\x04'
BUTTON5=b'\x05'

START=b'\x80'
ROMAN_NUMERAL_REQUEST=b'\x40'
CURVE=b'\x08'
PAUSE=b'\xB0'
RESUME=b'\x70'

s=serial.Serial(
        port='/dev/rfcomm0',
        baudrate=9600,
        parity=serial.PARITY_EVEN,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS
)

s.isOpen()

def getError():
    while True:
        res=s.read(1)
        if res==DEBUG_ERROR_INIT_MOTOR:
        	print('DEBUG_ERROR_INIT_MOTOR')
        elif res==DEBUG_ERROR_INIT_SERVO:
        	print('DEBUG_ERROR_INIT_SERVO')
        elif res==DEBUG_ERROR_INIT_TOF:
        	print('DEBUG_ERROR_INIT_TOF')
        elif res==DEBUG_ERROR_END_LOOP_REACHED:
        	print('DEBUG_ERROR_END_LOOP_REACHED')
        elif res==DEBUG_ERROR_SET_MOTOR_SPEED:
        	print('DEBUG_ERROR_SET_MOTOR_SPEED')
        elif res==DEBUG_ERROR_SET_MOTOR_DIRECTION:
        	print('DEBUG_ERROR_SET_MOTOR_DIRECTION')
        elif res==DEBUG_ERROR_SET_BRUSHLESS:
        	print('DEBUG_ERROR_SET_BRUSHLESS')
        elif res==DEBUG_ERROR_SET_SERVO:
        	print('DEBUG_ERROR_SET_SERVO')
        elif res==DEBUG_ERROR_GET_TOF_VALUE:
        	print('DEBUG_ERROR_GET_TOF_VALUE')
        elif res==DEBUG_ERROR_WRONG_BUTTON_NUMBER:
        	print('DEBUG_ERROR_WRONG_BUTTON_NUMBER')
        elif res==ACKNOWLEDGE:
        	print('ACKNOWLEDGE')
        elif res==ERROR:
        	print('ERROR')
        elif res==BUTTON1:
        	print('BUTTON1')
        elif res==BUTTON2:
        	print('BUTTON2')
        elif res==BUTTON3:
        	print('BUTTON3')
        elif res==BUTTON4:
        	print('BUTTON4')
        elif res==BUTTON5:
        	print('BUTTON5')
        elif res==START:
        	print('START')
        elif res==ROMAN_NUMERAL_REQUEST:
        	print('ROMAN_NUMERAL_REQUEST')
        elif res==CURVE:
        	print('CURVE')
        elif res==PAUSE:
        	print('PAUSE')
        elif res==RESUME:
        	print('RESUME')
        else:
        	print('unknown code: '+str(res))

getError()
