#ifndef OBJECTS_CLASSIFICATION_H_
#define OBJECTS_CLASSIFICATION_H_

#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "menu/pages.h"
#include "display/lcd.h"

#define BUFFER_SIZE            4000 //size of circular buffer that holds accelerometer samples
#define WINDOW_SIZE            3000 //size of sample window tested for fall
#define DATASET_SIZE            100 //size of the entire model with adl and fall sample windows
#define LOWER_THRESHOLD         0.3 //threshold under which the knn algorithm is applied to the sample window
#define UPPER_THRESHOLD         2.7 //threshold over which the knn algorithm is applied to the sample window
#define ACC_OFFSET             1.65 //constant accelerometer offset used for raw to acceleration data conversion
#define ACC_SENSITIVITY        0.66 //accelerometer sensitivity used for raw to acceleration data conversion
#define ADC_REF_VOLTAGE         3.3 //adc reference voltage
#define ADC_INPUT_RANGE  pow(2, 14) //adc range to compute voltage steps
#define DEF_SHORTEST_DIST     10000 //default shortest distance for knn (k near neighbours)
#define NEAREST_NEIGHBOURS        5 //number of neighbours to find in knn algorithm

/* movement class and execution state*/
enum Class {ADL, FALL}; // ADL = Activities of Daily Living
enum State {SEARCHING_FOR_PEAK, FILLING_PEAK_WINDOW, CLASSIFYING_PEAK_WINDOW};
extern enum State currentState;
extern enum State nextState;

/* variable used to know when a fall is detected so that the program doesn't keep on reading accelerometer data */
extern bool canClassify;

/* accelerometer reading */
typedef struct{
    float x;
    float y;
    float z;
} Sample;

/* features data */
typedef struct{
    Sample stdDev;
    Sample accMean;
    float lpv;  // lower peak value
    float upv;  // upper peak value
} Features;

/* movement stored in the dataset with it's features and class */
typedef struct{
    Features movFeatures;
    enum Class movClass;
    bool toSkip;
} Movement;

/* dataset that holds different types of ADL's and fall features */
extern Movement dataset[DATASET_SIZE];
/* circular array that continuously stores accelerometer samples */
extern Sample circularBuffer[BUFFER_SIZE];
/* circular buffer index */
extern int bufferIndex;
/* samples needed to fill right half of peak window and window extremes */
extern int missingSamples;
extern int startIndex;
extern int stopIndex;

/* after a knn run, reset toSkip values to false for next classifications */
extern void resetDataset();
/* finds euclidean distance between 2 feature sets */
extern float euclideanDistance(Features, Features);
/* finds dataset's nearest neighbour to peak window features */
extern enum Class classifyMovement(Features, Movement []);
/* compute features for window starting at index start and ending at index stop */
extern Features computeWindowFeatures(int, int);
/* compute acceleration of last sample converted and check if it is a peak */
extern bool isPeak(Sample);
/* stores adc raw data into sample */
extern Sample getRawSample();
/* convert raw adc data into acceleration data */
extern Sample convertRawSample(Sample);
/* get raw sample and convert it, then stores it into buffer */
extern void storeNewSample();
/* compute start and stop indexes for peak window */
extern void computeWindowRange();
/* updates index depending on current value and buffer size */
extern void updateIndex();
/* updates current state to be next state in the next adc conversion */
extern void updateProgramState();
/* finite state machine program */
extern void doProgramState();

#endif /* OBJECTS_CLASSIFICATION_H_ */
