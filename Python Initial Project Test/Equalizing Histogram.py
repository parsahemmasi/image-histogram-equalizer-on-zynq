import cv2
import numpy as np
from os import path as pt

def strechHisto(imgIn):
    yMax = 255;
    xMin = np.min(imgIn)
    xMax = np.max(imgIn)

    imgOut = imgIn

    for idxx in range(np.size(myPic,0)):
        for idxy in range(np.size(myPic,1)):
            x = imgIn[idxx,idxy]
            imgOut[idxx,idxy] = (x - xMin) / (xMax - xMin) * yMax

    return imgOut

PictureLocation=pt.dirname(__file__)+'\ExamplePicture.jpg'
myPic=cv2.imread(PictureLocation,cv2.IMREAD_GRAYSCALE)

cv2.imshow('Orginal Picture',myPic)

myPic_2 = strechHisto(myPic)

cv2.imshow('Equalized Picture',myPic_2)

cv2.imwrite(pt.dirname(__file__)+'\ChangedPicture.jpg',myPic_2) 

cv2.waitKey();