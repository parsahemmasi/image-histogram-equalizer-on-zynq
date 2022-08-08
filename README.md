# Histogram Equalizer On Zynq
A real-time image histogram equalizer implemented on zedboard based on xilinx zynq.

## Introduction
Every grayscale picture consists of some pixels between 0 and 255 value.
0 value for a pixel represents that the pixel's color is totally black and 255 value represents that the pixel's color is totally white.

So, if the histogram of a picture is on the left side, the image is a dark image and if the histogram of a picture is on the right side the image is a bright image.

In this project, the module equalizes the histogram and reguralizes the contrast of the image.

## Theory
As we know, images are types of digital signals.
<img src = "https://raw.githubusercontent.com/parsahemmasi/image-histogram-equalizer-on-zynq/main/Images/system.png"/>
The module works based on the mathematical equation demonstrated below.
<img>

## Implementing With Python
<img>
We can see the image above is so dark, so first the histogram of the picture was drawn by matplotlib in python.
<img>
After that the mathematical equation was implemented on every single pixel of the picture.
<img>
Result:
<img>
Histogram of the output image:
<img>
It's clear, that the mathematical equation stretches the histogram.

## Implementing With HLS
2 IPCores was built in Vivado HLS that one of them calculates the histogram of the input image and the second one equalizes the histogram given by the first IPCore.
The testbench of the first IPCore created a plain text that contains the histogtam values of the input picture.
I found out the first IPCore works well by comparing the python result with the testbench resualt.
<img>
<img>
<img>

The image below demonstrates the output of the second IPCore.
<img>

## Block Design In Vivado
the figure below shows the entire block design of the project.
