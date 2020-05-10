#include "ultrasonic.h"

// D1 //
ultrasonic::ultrasonic(PinName trigPin, PinName echoPin, float updateSpeed, float timeout):_trig(trigPin), _echo(echoPin)
{
    _updateSpeed = updateSpeed;
    _timeout = timeout;
}

ultrasonic::ultrasonic(PinName trigPin, PinName echoPin, float updateSpeed, float timeout, void onUpdate(int))
    :_trig(trigPin), _echo(echoPin)
{
    _onUpdateMethod=onUpdate;
    _updateSpeed = updateSpeed;
    _timeout = timeout;
    _t.start ();
}
void ultrasonic::_startT()
{
    if(_t.read()>600) {
        _t.reset ();
    }
    start = _t.read_us ();
}

void ultrasonic::_updateDist()
{
    end = _t.read_us ();
    done = 1;
    _distance = (end - start)/6;
    _tout.detach();
    _tout.attach(this,&ultrasonic::_startTrig, _updateSpeed);
}
void ultrasonic::_startTrig(void)
{
    _tout.detach();
    _trig=1;
    wait_us(10);
    done = 0;
    _echo.rise(this,&ultrasonic::_startT);
    _echo.fall(this,&ultrasonic::_updateDist);
    _echo.enable_irq ();
    _tout.attach(this,&ultrasonic::_startTrig,_timeout);
    _trig=0;
}

int ultrasonic::getCurrentDistance(void)
{
    return _distance;
}
void ultrasonic::pauseUpdates(void)
{
    _tout.detach();
    _echo.rise(NULL);
    _echo.fall(NULL);
}
void ultrasonic::startUpdates(void)
{
    _startTrig();
}
void ultrasonic::attachOnUpdate(void method(int))
{
    _onUpdateMethod = method;
}
void ultrasonic::changeUpdateSpeed(float updateSpeed)
{
    _updateSpeed = updateSpeed;
}
float ultrasonic::getUpdateSpeed()
{
    return _updateSpeed;
}
int ultrasonic::isUpdated(void)
{
    d=done;
    done = 0;
    return d;
}
void ultrasonic::checkDistance(void)
{
    if(isUpdated()) {
        (*_onUpdateMethod)(_distance);
    }
}

// D2 //
ultrasonic2::ultrasonic2(PinName trigPin2, PinName echoPin2, float updateSpeed2, float timeout2):_trig2(trigPin2), _echo2(echoPin2)
{
    _updateSpeed2 = updateSpeed2;
    _timeout2 = timeout2;
}

ultrasonic2::ultrasonic2(PinName trigPin2, PinName echoPin2, float updateSpeed2, float timeout2, void onUpdate2(int))
    :_trig2(trigPin2), _echo2(echoPin2)
{
    _onUpdateMethod2=onUpdate2;
    _updateSpeed2 = updateSpeed2;
    _timeout2 = timeout2;
    _t2.start ();
}
void ultrasonic2::_startT2()
{
    if(_t2.read()>600) {
        _t2.reset ();
    }
    start2 = _t2.read_us ();
}

void ultrasonic2::_updateDist2()
{
    end2 = _t2.read_us ();
    done2 = 1;
    _distance2 = (end2 - start2)/6;
    _tout2.detach();
    _tout2.attach(this,&ultrasonic2::_startTrig2, _updateSpeed2);
}
void ultrasonic2::_startTrig2(void)
{
    _tout2.detach();
    _trig2=1;
    wait_us(10);
    done2 = 0;
    _echo2.rise(this,&ultrasonic2::_startT2);
    _echo2.fall(this,&ultrasonic2::_updateDist2);
    _echo2.enable_irq ();
    _tout2.attach(this,&ultrasonic2::_startTrig2,_timeout2);
    _trig2=0;
}

int ultrasonic2::getCurrentDistance2(void)
{
    return _distance2;
}
void ultrasonic2::pauseUpdates2(void)
{
    _tout2.detach();
    _echo2.rise(NULL);
    _echo2.fall(NULL);
}
void ultrasonic2::startUpdates2(void)
{
    _startTrig2();
}
void ultrasonic2::attachOnUpdate2(void method2(int))
{
    _onUpdateMethod2 = method2;
}
void ultrasonic2::changeUpdateSpeed2(float updateSpeed2)
{
    _updateSpeed2 = updateSpeed2;
}
float ultrasonic2::getUpdateSpeed2()
{
    return _updateSpeed2;
}
int ultrasonic2::isUpdated2(void)
{
    d2=done2;
    done2 = 0;
    return d2;
}
void ultrasonic2::checkDistance2(void)
{
    if(isUpdated2()) {
        (*_onUpdateMethod2)(_distance2);
    }
}

// D3 //
ultrasonic3::ultrasonic3(PinName trigPin3, PinName echoPin3, float updateSpeed3, float timeout3):_trig3(trigPin3), _echo3(echoPin3)
{
    _updateSpeed3 = updateSpeed3;
    _timeout3 = timeout3;
}

ultrasonic3::ultrasonic3(PinName trigPin3, PinName echoPin3, float updateSpeed3, float timeout3, void onUpdate3(int))
    :_trig3(trigPin3), _echo3(echoPin3)
{
    _onUpdateMethod3=onUpdate3;
    _updateSpeed3 = updateSpeed3;
    _timeout3 = timeout3;
    _t3.start ();
}
void ultrasonic3::_startT3()
{
    if(_t3.read()>600) {
        _t3.reset ();
    }
    start3 = _t3.read_us ();
}

void ultrasonic3::_updateDist3()
{
    end3 = _t3.read_us ();
    done3 = 1;
    _distance3 = (end3 - start3)/6;
    _tout3.detach();
    _tout3.attach(this,&ultrasonic3::_startTrig3, _updateSpeed3);
}
void ultrasonic3::_startTrig3(void)
{
    _tout3.detach();
    _trig3=1;
    wait_us(10);
    done3 = 0;
    _echo3.rise(this,&ultrasonic3::_startT3);
    _echo3.fall(this,&ultrasonic3::_updateDist3);
    _echo3.enable_irq ();
    _tout3.attach(this,&ultrasonic3::_startTrig3,_timeout3);
    _trig3=0;
}

int ultrasonic3::getCurrentDistance3(void)
{
    return _distance3;
}
void ultrasonic3::pauseUpdates3(void)
{
    _tout3.detach();
    _echo3.rise(NULL);
    _echo3.fall(NULL);
}
void ultrasonic3::startUpdates3(void)
{
    _startTrig3();
}
void ultrasonic3::attachOnUpdate3(void method3(int))
{
    _onUpdateMethod3 = method3;
}
void ultrasonic3::changeUpdateSpeed3(float updateSpeed3)
{
    _updateSpeed3 = updateSpeed3;
}
float ultrasonic3::getUpdateSpeed3()
{
    return _updateSpeed3;
}
int ultrasonic3::isUpdated3(void)
{
    d3=done3;
    done3 = 0;
    return d3;
}
void ultrasonic3::checkDistance3(void)
{
    if(isUpdated3()) {
        (*_onUpdateMethod3)(_distance3);
    }
}