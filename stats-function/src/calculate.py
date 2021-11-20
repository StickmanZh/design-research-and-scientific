import numpy as np
import tkinter as tk
import math
import os

from classes import *

def render():
    window = tk.Tk()
    window.mainloop()

def findMean(dataSet: list) -> float:
    sum = 0

    for i in dataSet:
        sum += i

    mean = (sum / len(dataSet))
    return mean

def findMedian(dataSet: list) -> float:
    dataSet.sort()
    sum: float

    if(len(dataSet) % 2 != 0):
        median = dataSet[math.floor(len(dataSet) / 2)]
    else:
        sum += dataSet[math.floor(len(dataSet) / 2)]
        sum += dataSet[math.ceil(len(dataSet) / 2)]
        median = (sum / 2)
    
    return median

""" def findMode(hash) -> : """

def main():
    dataSet = reader.readline().split(' ')
    for i = 0 to len(dataSet):
        
        

    hashMap = HashMap()
    
    #Create hash map of data set
    for data in dataSet:
        if(hashMap.find(data)):
            hashMap.insert(data, hashMap.find(data).value + 1)
        else:
            hashMap.insert(data, 0)

    mean = findMean(dataSet)


if __name__ == "__main__":
    global reader, writer
    reader = open('stats-function/data/input.txt', 'r')
    writer = open('stats-function/data/output.txt', 'w')
    main()
    reader.close()
    writer.close()
