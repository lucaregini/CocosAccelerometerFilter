//
//  AccelerometerManager.h
//  FuguGame
//
//  Created by lucar on 06/07/15.
//
//

#ifndef __FuguGame__AccelerometerFilter__
#define __FuguGame__AccelerometerFilter__

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;

double clampAbsolute(double v, double min, double max);

class AccelerometerFilter:public cocos2d::Node

{
public:
    AccelerometerFilter(cocos2d::Node* mainScen,float cutOffFreq=5.0f);
    void onAcceleration(cocos2d::Acceleration *acc, cocos2d::Event *event);
	const cocos2d::Acceleration& getAcceleration(void) { return clampedAcc; };
    void setAdaptive(bool val){adaptive=val;}
    
    void setMinThreshold(double x,double y,double z);
    void setMaxThreshold(double x,double y,double z);
    
    const cocos2d::Acceleration& getMinThreshold(void) {return minThreshold;}
    const cocos2d::Acceleration& getMaxThreshold(void) {return maxThreshold;}
    
private:
    cocos2d::Acceleration minThreshold;
    cocos2d::Acceleration maxThreshold;
    bool adaptive;
    cocos2d::Acceleration filterAcc;
	cocos2d::Acceleration clampedAcc;
    float filterConstant;
    
};


#endif /* defined(__FuguGame__AccelerometerManager__) */
