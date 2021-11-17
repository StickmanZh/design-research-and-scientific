#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>
using namespace std;

ifstream fin("data.in");
ofstream fout("data.out");

double findMean(vector<double> dataSet) {
    double sum = 0, n = dataSet.size();

    for(int i = 0; i < dataSet.size(); i++) {
        sum += dataSet[i];
    }

    double mean = (sum / n);
    return mean;
}

double findMedian(vector<double> dataSet) {
    sort(dataSet.begin(), dataSet.end());

    double sum = 0, median;

    if(dataSet.size() %2 != 0) {
        median = dataSet[floor(dataSet.size() / 2)];
    } else {
        sum += dataSet[floor(dataSet.size() / 2)];
        sum += dataSet[ceil(dataSet.size() / 2)];
        median = (sum / 2);
    }

    return median;
}

struct Modal {
    vector<double> modes;
    int timesItAppears;
    int modeNum;
};

Modal findMode(map<double, int> hash) {
    pair<double, int> largest;
    largest.second = 0;
    Modal newModal;
    newModal.modeNum = 0;

    map<double, int>::iterator mit;
    for(mit = hash.begin(); mit != hash.end(); mit++) {
        if(mit->second > largest.second) {
            largest.first = mit->first;
            largest.second = mit->second;
        }
    }

    newModal.timesItAppears = mit->second;

    for(mit = hash.begin(); mit != hash.end(); mit++) {
        if(mit->second == largest.second) {
            newModal.modes.push_back(mit->first);
            newModal.modeNum++;
        }
    }

    return newModal;
}

struct Deviations {
    double mean;
    vector<double> differenceFromMean;

    double sumDifferenceFromMeanSquared;
    vector<double> differenceFromMeanSquared;

    double variance;
    double standardDeviation;
};

Deviations findStandardDeviation(vector<double> dataSet, double mean) {
    Deviations newDeviation;
    newDeviation.sumDifferenceFromMeanSquared = 0;

    for(int i = 0; i < dataSet.size(); i++) {
        newDeviation.differenceFromMean.push_back(dataSet[i] - mean);
        newDeviation.differenceFromMeanSquared.push_back(pow(newDeviation.differenceFromMean[i], 2));
        newDeviation.sumDifferenceFromMeanSquared += newDeviation.differenceFromMeanSquared[i];
    }

    newDeviation.variance = (newDeviation.sumDifferenceFromMeanSquared / (dataSet.size() - 1));
    newDeviation.standardDeviation = sqrt(newDeviation.variance);

    return newDeviation;
}

void displayValues(vector<double> dataSet, double mean, double median, Modal newModal, Deviations newDeviation) {
    //Display the data set
    fout << "The data set is: ";
    for(int i = 0; i < dataSet.size() - 1; i++) {
        fout << dataSet[i] << ", ";
    }
    fout << dataSet[dataSet.size() - 1] << "\n\n";

    //Display the mean
    fout << "The mean is: " << mean << "\n\n";

    //Display the median
    fout << "The median is: " << median << "\n\n";

    //Display the mode
    

    //Display the deviations;
    fout << "The standard deviation is: " << newDeviation.standardDeviation << "\n";
    fout << "The variance is: " << newDeviation.variance << "\n";
    fout << newDeviation.sumDifferenceFromMeanSquared;
}

int main() {
    vector<double> dataSet;
    map<double, int> dataSetHash;
    double value;

    while(fin >> value) {
        dataSet.push_back(value);

        if(dataSetHash.find(value) == dataSetHash.end()) {
            dataSetHash[value] = 1;
        } else {
            dataSetHash[value]++;
        }
    }

    double mean, median;
    Modal newModal;
    Deviations newDeviation;

    mean = findMean(dataSet);
    median = findMedian(dataSet);
    newModal = findMode(dataSetHash);
    newDeviation = findStandardDeviation(dataSet, findMean(dataSet));

    displayValues(dataSet, mean, median, newModal, newDeviation);
}