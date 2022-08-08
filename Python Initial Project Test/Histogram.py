import cv2
import numpy as np 
from matplotlib import pyplot as mt
from os import path as pt

PictureLocation=pt.dirname(__file__)+'\ExamplePicture.jpg'
myPic=cv2.imread(PictureLocation,cv2.IMREAD_GRAYSCALE)
cv2.imshow('My Picture',myPic)

histr=cv2.calcHist([myPic],[0],None,[256],[0,256])   
mt.plot(histr)                                         
mt.xlim([0,256])                                              

mt.show()
