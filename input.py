import serial

ard = serial.Serial('COM3',9600)
x=(input("enter x:"))
y=(input("enter y:"))
while True:
    ard.write(x.encode('utf-8'))
    ard.write(y.encode('utf-8'))
