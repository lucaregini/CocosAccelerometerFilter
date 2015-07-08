//
//  AccelerometerFiler.cpp
//  FuguGame
//
//  Created by lucar on 06/07/15.
//
//

#include "AccelerometerFilter.h"




double Norm(double x, double y, double z)
{
    return sqrt(x * x + y * y + z * z);
}

double Clamp(double v, double min, double max)
{
    if(v > max)
        return max;
    else if(v < min)
        return min;
    else
        return v;
}

void AccelerometerFilter::setMinThreshold(double x,double y,double z)
{
    minThreshold.x=x;
    minThreshold.y=y;
    minThreshold.z=z;
}
void AccelerometerFilter::setMaxThreshold(double x,double y,double z)
{
    maxThreshold.x=x;
    maxThreshold.y=y;
    maxThreshold.z=z;
}

AccelerometerFilter::AccelerometerFilter(cocos2d::Node* mainScene,float freq)
{
    maxThreshold.x=maxThreshold.y=maxThreshold.z=1;
    minThreshold.x=minThreshold.y=minThreshold.z=0;
    adaptive=true;
	auto director = Director::getInstance();	
	double dt = director->getAnimationInterval();
    double RC = 1.0 / freq;
    filterConstant = dt / (dt + RC);
    
    Device::setAccelerometerEnabled(true);
    auto acclistener = EventListenerAcceleration::create(CC_CALLBACK_2(AccelerometerFilter::onAcceleration, this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(acclistener, mainScene);
}

#define kAccelerometerMinStep				0.02
#define kAccelerometerNoiseAttenuation		3.0



double clampAbsolute(double v, double min, double max)
{
    if(v>0)
    {
        if(v<min)
        {
            return 0;
            
        }
        else
            if(v>max)
            {
                return max;
                
            }
        return v;
    }
    
    //v<0
    if(v>-min)
    {
        return 0;
        
    }
    else
        if(v<-max)
        {
            return -max;
            
        }
    return v;
}

void AccelerometerFilter::onAcceleration(cocos2d::Acceleration *acc, cocos2d::Event *event)
{
    // See http://en.wikipedia.org/wiki/Low-pass_filter for details low pass filtering
    
    float alpha=filterConstant;
    
    if(adaptive)
    {
        double d = Clamp(fabs(Norm(filterAcc.x, filterAcc.y, filterAcc.z) - Norm(acc->x, acc->y, acc->z)) / kAccelerometerMinStep - 1.0, 0.0, 1.0);
        alpha = (1.0 - d) * filterConstant / kAccelerometerNoiseAttenuation + d * filterConstant;
    }
   
	filterAcc.x = acc->x * alpha + filterAcc.x * (1.0f - alpha);
	filterAcc.y = acc->y * alpha + filterAcc.y * (1.0f - alpha);
	filterAcc.z = acc->z * alpha + filterAcc.z * (1.0f - alpha);
    
    
    clampedAcc.x=clampAbsolute(filterAcc.x, minThreshold.x, maxThreshold.x);
    clampedAcc.y=clampAbsolute(filterAcc.y, minThreshold.y, maxThreshold.y);
    clampedAcc.z=clampAbsolute(filterAcc.z, minThreshold.z, maxThreshold.z);
}


