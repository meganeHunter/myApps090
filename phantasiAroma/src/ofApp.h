#pragma once

#include "ofMain.h"
#include "ofxFluid.h"


class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofArduino	ard;
    bool	bSetupArduino;
    
    float irsVal;
    
    ofxFluid fluid;
    
    ofVec2f oldM;
    int     width, height;
    bool    bPaint, bObstacle, bBounding, bClear;
    
    int pCount, pTime;
    float rad, temp, den;
    bool isDrawS, isPaused;
    bool isStatA;
    
    ofPoint pos;
    ofPoint dir;
    
private:
    void setupArduino(const int & version);
    void updateArduino();

    
};
