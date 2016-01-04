#ifndef SHADOW_H_INCLUDED
#define SHADOW_H_INCLUDED

#define red	    0
#define blue	1
#define black	2

const float materialColor[3][4] =
{
  {0.75, 0.0, 0.0, 0.0},
  {0.0, 0.0, 0.75, 0.0},
  {0.0, 0.0, 0.01, 1.0},
};

float lightPos[4] = {-2.0, 2.0, 2.0, 1.0};
float lightAmb[4] = {0.15, 0.15, 0.15, 1.0};
float lightDiff[4] = {0.75, 0.75, 0.75, 1.0};
float lightSpec[4] = {0.25, 0.25, 0.25, 1.0};

float backPlane[4] = {0.0, 0.0, 1.0, 0.899};

class myClock{
private:
    int clock;
    bool incClock;
public:
    int getClock(){return clock;}
    myClock(){clock = 0; incClock = true;}
    ~myClock(){}
    //changes the clocks value
    void changeClock()
    {
        if (incClock) clock++;
        else clock --;
        if (clock <= 0) incClock = true;
        if(clock >= 360) {incClock = false;clock--;}
    }
};

#endif // SHADOW_H_INCLUDED
