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
    mean = round(mean, 3)
    return mean

def findMedian(dataSetSorted: list) -> float:
    sum: float

    if(len(dataSetSorted) % 2 != 0):
        median = dataSetSorted[math.floor(len(dataSetSorted) / 2)]
    else:
        sum += dataSetSorted[len(dataSetSorted) / 2]
        sum += dataSetSorted[(len(dataSetSorted) / 2) - 1]
        median = (sum / 2)
    
    median = round(median, 3)
    return median

def findMode(hashMap: HashMap) -> Mode:
    largest = Pair()
    mode = Mode()

    for i in hashMap.hashMap:
        if(i.value > largest.second):
            largest.first = i.key
            largest.second = i.value

    for i in hashMap.hashMap:
        if(largest.second == i.value):
            mode.modes.append(i.key)
            mode.modeNum += 1

    mode.timesItAppears = largest.second

    return mode

def findRange(dataSetSorted: list) -> Range:
    newRange = Range()

    newRange.range = dataSetSorted[len(dataSetSorted) - 1] - dataSetSorted[0]
    newRange.largest = dataSetSorted[len(dataSetSorted) - 1]
    newRange.smallest = dataSetSorted[0]

    return newRange

def findDeviation(dataSet: list, mean: float) -> Deviation:
    deviation = Deviation()

    for i in range(len(dataSet)):
        deviation.differencesFromMean.append(dataSet[i] - mean)
        deviation.differencesFromMean[i] = round(deviation.differencesFromMean[i], 3)

        deviation.differencesFromMeanSquared.append(math.pow(deviation.differencesFromMean[i], 2))
        deviation.differencesFromMeanSquared[i] = round(deviation.differencesFromMeanSquared[i], 3)

        deviation.sumDifferencesFromMeanSquared += deviation.differencesFromMeanSquared[i]
    
    deviation.sumDifferencesFromMeanSquared = round(deviation.sumDifferencesFromMeanSquared, 3)

    deviation.variance = (deviation.sumDifferencesFromMeanSquared / (len(dataSet) - 1))
    deviation.variance = round(deviation.variance, 3)

    deviation.standardDeviation = math.sqrt(deviation.variance)
    deviation.standardDeviation = round(deviation.standardDeviation, 3)

    return deviation

def printMode(mode: Mode, dataSet: list) -> None:

    #If there are no modes
    if(mode.modeNum == len(dataSet)):
        print("There are no modes \n")
        return

    if(mode.modeNum > 1):

        #If more than one mode
        print("There are ", mode.modeNum , end = " modes: ")
        for i in range(len(mode.modes) - 1):
            print(i, end = ", ")
        print(mode.modes[len(mode.modes) - 1], " they appear ", mode.timesItAppears, " time(s) \n")
    else:

        #If one mode
        print("The mode is: ", mode.modes[0], " it appears ", mode.timesItAppears, " time(s) \n")

def printDeviation(deviation: Deviation) -> None:
    print("The standard deviation is: ", deviation.standardDeviation)
    print("The variance is: ", deviation.variance)
    print("The sum of (difference from mean)^2 is: ", deviation.sumDifferencesFromMeanSquared, "\n")

    print(end = "The differences from the mean are: ")
    for i in range(len(deviation.differencesFromMean) - 1):
        print(deviation.differencesFromMean[i], end = ", ")
    print(deviation.differencesFromMean[len(deviation.differencesFromMean) - 1], "\n")

    print(end = "The (differences from the mean)^2 are: ")
    for i in range(len(deviation.differencesFromMeanSquared) - 1):
        print(deviation.differencesFromMeanSquared[i], end = ", ")
    print(deviation.differencesFromMeanSquared[len(deviation.differencesFromMeanSquared) - 1])

def printValues(dataSet: list, dataSetSorted: list, mean: float, median: float, mode: Mode, newRange: Range, deviation: Deviation) -> None:
    
    #Print original data set
    print(end = "The data set is: ")
    for i in range(len(dataSet) - 1):
        print(dataSet[i], end = ", ")
    print(dataSet[len(dataSet) - 1])

    print("There are ", len(dataSet), " values \n")

    #Print the mean
    print("The mean is: ", mean, "\n")

    #Print the median
    print("The median is: ", median, "\n")

    #Display the mode
    printMode(mode, dataSet)

    #Display the standard deviation
    printDeviation(deviation)

def main():
    dataSetSorted = reader.readline().split(' ')

    
    dataSetSorted = list(map(float, dataSetSorted))
    dataSet = dataSetSorted
    dataSetSorted.sort()

    hashMap = HashMap()
    
    #Create hash map of data set
    for data in dataSet:
        if(hashMap.find(data)):
            hashMap.insert(data, hashMap.find(data).value + 1)
        else:
            hashMap.insert(data, 0)

    mean = findMean(dataSet)
    median = findMedian(dataSetSorted)
    mode = findMode(hashMap)
    newRange = findRange(dataSetSorted)
    deviation = findDeviation(dataSet, mean)

    printValues(dataSet, dataSetSorted, mean, median, mode, newRange, deviation)

if __name__ == "__main__":
    global reader, writer
    reader = open('are-female-hurricanes-deadlier-than-male-hurricanes\data\data.txt', 'r')
    writer = open('stats-function/data/output.txt', 'w')
    main()
    reader.close()
    writer.close()