#ifndef MBED_ULTRASONIC_H
#define MBED_ULTRASONIC_H

#include "mbed.h"

class ultrasonic
{
public:

    ultrasonic(PinName trigPin, PinName echoPin, float updateSpeed, float timeout);
    ultrasonic(PinName trigPin, PinName echoPin, float updateSpeed, float timeout, void onUpdate(int));
    int getCurrentDistance(void);
    void pauseUpdates(void);
    void startUpdates(void);
    void attachOnUpdate(void method(int));
    void changeUpdateSpeed(float updateSpeed);
    int isUpdated(void);
    float getUpdateSpeed(void);
    void checkDistance(void);
private:
    DigitalOut _trig;
    InterruptIn _echo;
    Timer _t;
    Timeout _tout;
    int _distance;
    float _updateSpeed;
    int start;
    int end;
    volatile int done;
    void (*_onUpdateMethod)(int);
    void _startT(void);
    void _updateDist(void);
    void _startTrig(void);
    float _timeout;
    int d;
};

class ultrasonic2
{
public:

    ultrasonic2(PinName trigPin2, PinName echoPin2, float updateSpeed2, float timeout2);
    ultrasonic2(PinName trigPin2, PinName echoPin2, float updateSpeed2, float timeout2, void onUpdate2(int));
    int getCurrentDistance2(void);
    void pauseUpdates2(void);
    void startUpdates2(void);
    void attachOnUpdate2(void method2(int));
    void changeUpdateSpeed2(float updateSpeed2);
    int isUpdated2(void);
    float getUpdateSpeed2(void);
    void checkDistance2(void);
private:
    DigitalOut _trig2;
    InterruptIn _echo2;
    Timer _t2;
    Timeout _tout2;
    int _distance2;
    float _updateSpeed2;
    int start2;
    int end2;
    volatile int done2;
    void (*_onUpdateMethod2)(int);
    void _startT2(void);
    void _updateDist2(void);
    void _startTrig2(void);
    float _timeout2;
    int d2;
};

class ultrasonic3
{
public:

    ultrasonic3(PinName trigPin3, PinName echoPin3, float updateSpeed3, float timeout3);
    ultrasonic3(PinName trigPin3, PinName echoPin3, float updateSpeed3, float timeout3, void onUpdate3(int));
    int getCurrentDistance3(void);
    void pauseUpdates3(void);
    void startUpdates3(void);
    void attachOnUpdate3(void method3(int));
    void changeUpdateSpeed3(float updateSpeed3);
    int isUpdated3(void);
    float getUpdateSpeed3(void);
    void checkDistance3(void);
private:
    DigitalOut _trig3;
    InterruptIn _echo3;
    Timer _t3;
    Timeout _tout3;
    int _distance3;
    float _updateSpeed3;
    int start3;
    int end3;
    volatile int done3;
    void (*_onUpdateMethod3)(int);
    void _startT3(void);
    void _updateDist3(void);
    void _startTrig3(void);
    float _timeout3;
    int d3;
};
#endif