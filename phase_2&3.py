import numpy as np
import cv2
import serial

video=cv2.VideoCapture(0)
while True :
    check , frame=video.read()
    gray=cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)
    cv2.imshow("cap",gray)
    key =cv2.waitKey(1)
    if key== ord('q'):
        break
    elif key== ord('z'):

        cv2.imwrite("image.jpeg",frame)


video.release()
cv2.destroyAllWindows()

img=cv2.imread(r"C:\Users\sivvani\PycharmProjects\untitled\image.jpeg")
kernel = np.ones((5, 5), np.uint8)
image=cv2.dilate(img, kernel, iterations=2)
gray=cv2.cvtColor(image,cv2.COLOR_BGR2GRAY)
_,thresh= cv2.threshold(gray,240,255,cv2.THRESH_TOZERO)
contours,_=cv2.findContours(thresh,cv2.RETR_TREE,cv2.CHAIN_APPROX_NONE)
cv2.drawContours(image,contours,-1,(0,0,255),5)
cv2.imshow("im",image)
print("no. of con :",len(contours))
contour=contours[1]
approx=cv2.approxPolyDP(contour,0.01*cv2.arcLength(contour,True),True)
if len(approx)==3:
    x=2;
    print("triangle")

elif len(approx)==4:
    x,y,w,h=cv2.boundingRect(approx)
    ratio=float(w)/h
    print(ratio)
    if ratio >=0.95 and ratio <=1.05:
        x=3;
        print("square")
    else:
        x=4;
        print("rectangle")

elif len(approx)==9 or len(approx)==10:
    x=1;
    print("semi circle")

else:
    x=0;
    print("circle")

cnt1=contours[-1]
per=cv2.arcLength(cnt1,True)
epsilon=0.01*cv2.arcLength(cnt1,True)
approx1=cv2.approxPolyDP(cnt1,epsilon,True)
if len(approx1)==3:
    y=2;
    print("triangle")

elif len(approx1)==4:
    x,y,w,h=cv2.boundingRect(approx1)
    ratio=float(w)/h
    print(ratio)
    if ratio >=0.95 and ratio <=1.05:
        y=3;
        print("square")
    else:
        y=4;
        print("rectangle")

elif len(approx1)==9 or len(approx1)==10:
    y=1;
    print("semi circle")

else:
    y=0;
    print("circle")
print(x,y)
cv2.waitKey()
cv2.destroyAllWindows()

ard = serial.Serial('COM3',9600)

while True:
    ard.write(x.encode('utf-8'))
    ard.write(y.encode('utf-8'))