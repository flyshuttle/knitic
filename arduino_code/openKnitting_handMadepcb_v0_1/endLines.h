#ifndef ENDLINES_H_
#define ENDLINES_H_

#include "arduino.h"
#include "sound_alerts.h"
#include "defined_knitic.h"

class endLines{
private:
  soundAlerts* mySoundAlerts;
  encoders* myEncoders;
  int filterValueLeftMin;
  int filterValueRightMin;
  int filterValueLeftMax;
  int filterValueRightMax;

public:
  int valueEndLineLeft;
  int valueEndLineRight;
  int phase;
  endLines(){
  }
  ~endLines(){
  }

  void setup(){
    pinMode(endLineLeftAPin,INPUT);
    pinMode(endLineRightAPin,INPUT);
    filterValueLeftMin = FILTER_VALUE_LEFT_MIN;
    filterValueRightMin = FILTER_VALUE_RIGHT_MIN;
    filterValueLeftMax = FILTER_VALUE_LEFT_MAX;
    filterValueRightMax = FILTER_VALUE_RIGHT_MAX;
  }

  void setPosition(encoders* _myEncoders, soundAlerts* _mySoundAlerts){
    myEncoders = _myEncoders;
    mySoundAlerts = _mySoundAlerts;
  }

  void loop(){
    // Left end of line - looking change phase
    if( myEncoders->headDirection==-1){
      valueEndLineLeft  = analogRead(endLineLeftAPin);
      if( valueEndLineLeft <filterValueLeftMin || analogRead(endLineLeftAPin) >filterValueLeftMax){ 
        if(myEncoders->_8segmentEncoder){
          phase = 1;
        }
        else{
          phase = 0;
        }
      }
    }
    // Right end of line - looking change phase
    if( myEncoders->headDirection==1){ 
      valueEndLineRight = analogRead(endLineRightAPin);
      if( valueEndLineRight <filterValueRightMin || analogRead(endLineRightAPin) >filterValueRightMax){
        if(myEncoders->_8segmentEncoder){
          phase = 0;
        }
        else{
          phase = 1;
        }
      }
    }
  }

};
#endif

