#ifndef __MAIN_H__
#define __MAIN_H__

#include <windows.h>

/*  To use this exported function of dll, include this header
 *  in your project.
 */

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif

#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <string>
#include <vector>
#include <queue>
#include <cmath>

using  namespace std;

class DLL_EXPORT myColor
{
public:
    myColor(float r,float g,float b):R(r),B(b),G(g){};
    myColor(){R = 0;G = 0; B = 0;}
    float getR(){return R;}
    float getG(){return G;}
    float getB(){return B;}
    void setR(float r){R = r;}
    void setG(float g){G = g;}
    void setB(float b){B = b;}
    ~myColor(){}
private:
    float R;
    float G;
    float B;
};
class DLL_EXPORT point
{
private:
    double x;
    double y;
    myColor color;
public:
    point(double newX,double newY):x(newX),y(newY){};
    point(){x = 0.0;y = 0.0;}
    void setX(double newX){x = newX;}
    void setY(double newY){y = newY;}
    void setColor(myColor col){color = col;}
    double getX(){return x;}
    double getY(){return y;}
    myColor getColor(){return color;}

};


class DLL_EXPORT myVector
{
    point first;
    point last;
    bool havePoints;
    bool haveFirst;
    vector <point> colVector;
public:
    myVector(){havePoints = false;haveFirst = false;}
    bool haveFirstPoint(){return haveFirst;}
    void putFirst(point newPoint){first = newPoint;haveFirst = true;havePoints = false;}
    void putLast(point newPoint)
    {
        havePoints = true;
        last = newPoint;
        makeVector();
        haveFirst = false;
    }
    bool canDraw(){return havePoints;}
    vector <point> getVector(){return colVector;}
private:

    void DLL_EXPORT makeVector();
    int DLL_EXPORT maximum(int,int,int,int,int);
};


#ifdef __cplusplus
extern "C"
{
#endif

void DLL_EXPORT SomeFunction();

#ifdef __cplusplus
}
#endif

#endif // __MAIN_H__
