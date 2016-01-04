#include "main.h"

// a sample exported function
void DLL_EXPORT SomeFunction()
{

}
int DLL_EXPORT myVector::maximum(int distanceOfX,int distanceOfY,int distanceOfR,int distanceOfG,int distanceOfB)
{
    int ownDistance = max(distanceOfX, distanceOfY);
    ownDistance = max(distanceOfR,ownDistance);
    ownDistance = max(ownDistance,distanceOfG);
    ownDistance = max(ownDistance,distanceOfB);
    return ownDistance;
}

void DLL_EXPORT myVector::makeVector()
{
    colVector.clear();
    point current(first.getX()+ 0.5, first.getY() + 0.5);
    myColor colorOfPixel = first.getColor();
    int xDistance = abs(last.getX() - first.getX()) * 10;
    int yDistance = abs(last.getY() - first.getY()) * 10;
    int rDistance = (float)fabs(first.getColor().getR() - last.getColor().getR()) * 100;
    int gDistance = (float)fabs(first.getColor().getG() - last.getColor().getG()) * 100;
    int bDistance = (float)fabs(first.getColor().getB()- last.getColor().getB()) * 100;

    int ownDistance = maximum(xDistance,yDistance,rDistance,gDistance,bDistance);

    point stepForPoint(0,0);
    stepForPoint.setX((double)(last.getX() - first.getX()) / (double)ownDistance);
    stepForPoint.setY((double)(last.getY() - first.getY()) / (double)ownDistance);
    myColor stepForColor(0,0,0);
    stepForColor.setR(float(last.getColor().getR() - first.getColor().getR()) / (float)ownDistance);
    stepForColor.setG(float(last.getColor().getG() - first.getColor().getG()) / (float)ownDistance);
    stepForColor.setB(float(last.getColor().getB() - first.getColor().getB()) / (float)ownDistance);
    while (ownDistance--)
    {
        current.setX(current.getX() + stepForPoint.getX());
        current.setY(current.getY() + stepForPoint.getY());

        colorOfPixel.setR(colorOfPixel.getR() + stepForColor.getR());
        colorOfPixel.setG(colorOfPixel.getG() + stepForColor.getG());
        colorOfPixel.setB(colorOfPixel.getB() + stepForColor.getB());
        current.setColor(colorOfPixel);
        colVector.push_back(current);
    }
}

extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            // attach to process
            // return FALSE to fail DLL load
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
    }
    return TRUE; // succesful
}
