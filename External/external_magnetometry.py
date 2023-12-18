import serial

ser = serial.Serial('COM7', 9600)
line = ser.readline()
f = open('data.csv', 'w')

while True:
    line = ser.readline().decode('utf-8')
    f.write(line.replace(' ',','))
