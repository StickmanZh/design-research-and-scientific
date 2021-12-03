#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include <string>
using namespace std;

ifstream fin("are-female-hurricanes-deadlier-than-male-hurricanes/data/data.in");
ofstream fout("are-female-hurricanes-deadlier-than-male-hurricanes/data/data.out");

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
        sum += dataSet[dataSet.size() / 2];
        sum += dataSet[(dataSet.size() / 2) - 1];
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

    for(mit = hash.begin(); mit != hash.end(); mit++) {
        if(mit->second == largest.second) {
            newModal.modes.push_back(mit->first);
            newModal.modeNum++;
        }
    }
    newModal.timesItAppears = largest.second;

    return newModal;
}

struct Range {
    double largest, smallest, range;
};

Range findRange(vector<double> dataSet) {
    Range newRange;

    sort(dataSet.begin(), dataSet.end());
    newRange.range = dataSet[dataSet.size() - 1] - dataSet[0];
    newRange.largest = dataSet[dataSet.size() - 1];
    newRange.smallest = dataSet[0];

    return newRange;
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

void displayModal(Modal newModal, vector<double> dataSet) {
    if(newModal.modeNum == dataSet.size()) {
        fout << "There are no modes.\n\n";
        return;
    }

    if(newModal.modeNum > 1) {
        fout << "There are " << newModal.modeNum << " modes: ";
        for(int i = 0; i < newModal.modes.size() - 1; i++) {
            fout << newModal.modes[i] << ", ";
        }
        fout << newModal.modes[newModal.modes.size() - 1] << " they appear " << newModal.timesItAppears << " time(s) \n\n";
    } else {
        fout << "The mode is: " << newModal.modes[0] << ", it appears " << newModal.timesItAppears << " time(s) \n\n";
    }
}

void displayStandardDeviation(Deviations newDeviation) {
    fout << "The standard deviation is: " << newDeviation.standardDeviation << "\n";
    fout << "The variance is: " << newDeviation.variance << "\n";
    fout << "The sum of (difference from the mean)^2 is: " << newDeviation.sumDifferenceFromMeanSquared << "\n";
    
    fout << "The differences from the mean are: ";
    for(int i = 0; i < newDeviation.differenceFromMean.size() - 1; i++) {
        fout << newDeviation.differenceFromMean[i] << ", ";
    }
    fout << newDeviation.differenceFromMean[newDeviation.differenceFromMean.size() - 1] << "\n";

    fout << "The differences from the mean^2 are: ";
    for(int i = 0; i < newDeviation.differenceFromMeanSquared.size() - 1; i++) {
        fout << newDeviation.differenceFromMeanSquared[i] << ", ";
    }
    fout << newDeviation.differenceFromMeanSquared[newDeviation.differenceFromMeanSquared.size() - 1] << "\n\n";
}

void displayValues(vector<double> dataSet, double mean, double median, Modal newModal, Range newRange, Deviations newDeviation) {
    //Display the data set
    fout << "The data set is: ";
    for(int i = 0; i < dataSet.size() - 1; i++) {
        fout << dataSet[i] << ", ";
    }
    fout << dataSet[dataSet.size() - 1] << "\n";
    fout << "There are " << dataSet.size() << " values\n\n";

    //Display the mean
    fout << "The mean is: " << mean << "\n\n";

    //Display the median
    fout << "The median is: " << median << "\n\n";

    //Display the mode
    displayModal(newModal, dataSet);

    //Display the range
    fout << "The range is: " << newRange.range << "\n";
    fout << "The largest value is: " << newRange.largest << ", the smallest value is: " << newRange.smallest << "\n\n";

    //Display the deviations;
    displayStandardDeviation(newDeviation);
}

int main() {
    vector<double> dataSet;
    map<double, int> dataSetHash;
    double value;
    char line[256];
    string year = "", deaths = "";

    for(int i = 0; i < 256; i++) {
        line[i] = 0;
    }

    while(fin.getline(line, 256)) {
        for(int i = 0; i < 256; i++) {
            if(line[i] != 'F') {
                continue;
            } else if(line[i] == 'F' && line[i - 1] == ' ' && line[i + 1] == ' ') {

                deaths += line[i + 7];

                if(line[i + 8] == '0' || line[i + 8] == '1' || line[i + 8] == '2' || line[i + 8] == '3' || line[i + 8] == '4' || line[i + 8] == '5' || line[i + 8] == '6' || line[i + 8] == '7' || line[i + 8] == '8' || line[i + 8] == '9') {
                    deaths += line[i + 8];
                }

                if(line[i + 9] == '0' || line[i + 9] ==  '1' || line[i + 9] == '2' || line[i + 9] == '3' || line[i + 9] == '4' || line[i + 9] == '5' || line[i + 9] == '6' || line[i + 9] == '7' || line[i + 9] ==  '8' || line[i + 9] == '9') {
                    deaths += line[i + 9];
                }

                if(line[i + 10] == '0' || line[i + 10] ==  '1' || line[i + 10] == '2' || line[i + 10] == '3' || line[i + 10] == '4' || line[i + 10] == '5' || line[i + 10] == '6' || line[i + 10] == '7' || line[i + 10] ==  '8' || line[i + 10] == '9') {
                    deaths += line[i + 10];
                }

                //fout << deaths << endl;

                value = stod(deaths);

                dataSet.push_back(value);

                if(dataSetHash.find(value) == dataSetHash.end()) {
                    dataSetHash[value] = 1;
                } else {
                    dataSetHash[value]++;
                }

                break;
            }
        }

        for(int i = 0; i < 256; i++) {
            line[i] = 0;
        }

        deaths = "";
    }

    double mean, median;
    Modal newModal;
    Range newRange;
    Deviations newDeviation;

    mean = findMean(dataSet);
    median = findMedian(dataSet);
    newModal = findMode(dataSetHash);
    newRange = findRange(dataSet);
    newDeviation = findStandardDeviation(dataSet, mean);

    displayValues(dataSet, mean, median, newModal, newRange, newDeviation);
}