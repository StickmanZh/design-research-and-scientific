from typing import NamedTuple

class HashMap:
    def __init__(self):
        self.hashMap = []

    #Create key-value structure
    class KeyValuePair(NamedTuple):
        key: float
        value: int

    #Function to find the key inside of the list
    def find(self, key):

        for i in self.hashMap:
            if(i.key == float(key)):
                return i
        
        return False

    #Insert values into the list
    def insert(self, key, value):

        #If value exists, remove the value
        if(self.find(key)):
            self.hashMap.remove(self.KeyValuePair(self.find(key).key, self.find(key).value))

        self.hashMap.append(self.KeyValuePair(float(key), value))

    #Function to sort descending
    def sort(self):

        for i in range(len(self.hashMap)):
            for j in range(i, len(self.hashMap)):
                if(self.hashMap[i].value < self.hashMap[j].value):
                    temp = self.hashMap[i]
                    self.hashMap[i] = self.hashMap[j]
                    self.hashMap[j] = temp

class Mode:
    def __init__(self):
        self.modes = []
        self.timesItAppears = 0
        self.modeNum = 0

class Range:
    def __init__(self):
        self.largest = 0
        self.smallest = 0
        self.range = 0

class Deviation:
    def __init__(self):
        self.differencesFromMean = []
        self.differencesFromMeanSquared = []
        self.sumDifferencesFromMeanSquared = 0
        self.variance = 0
        self.standardDeviation = 0

class Pair:
    def __init__(self):
        self.first = 0
        self.second = 0
