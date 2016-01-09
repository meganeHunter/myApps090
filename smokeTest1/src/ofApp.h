#pragma once

#include "ofMain.h"

int WIDTH = 200;
int HEIGHT = 200;
int SMOKE_X = WIDTH / 2;
int SMOKE_Y = HEIGHT - 100;
int SMOKE_NUM = 2;




class ofApp : public ofBaseApp{
    public:
        void setup();
        void update();
        void draw();
		
        void keyPressed(int key);
        void keyReleased(int key);
        void mouseMoved(int x, int y);
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void mouseEntered(int x, int y);
        void mouseExited(int x, int y);
        void windowResized(int w, int h);
        void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);
};


class SmokeParticle
{
    float x;
    float y;
    float c;
    float phase;
    float initPhase;
    float dPhase;
    
    
    SmokeParticle(float _y, float _initialPhase,float _c, float _dPhase)
    {
        initPhase = _initialPhase;
        dPhase = _dPhase;
        c = _c;
        y = _y;
        phase = SMOKE_Y - 0.1 * y + initPhase;
        x = SMOKE_X + c * (1 - exp(-0.01 * (y))) * sin(phase);
    }
    
    public:
    
    SmokeParticle()
    {
    
    }
    
    public:
    
    void setParticle(float _y, float _initialPhase,float _c, float _dPhase)
    {
        initPhase = _initialPhase;
        dPhase = _dPhase;
        c = _c;
        y = _y;
        phase = SMOKE_Y - 0.1 * y + initPhase;
        x = SMOKE_X + c * (1 - exp(-0.01 * (y))) * sin(phase);
    }
    
    void drawParticle()
    {
        phase += dPhase;
        
        x = SMOKE_X + c * (1 - exp(-0.001 * (SMOKE_Y - y))) * sin(phase);
        ofSetColor(64);
        ofFill();
        ofEllipse(x,y,1.0,1.0);
    }
};



class smoke
{
    SmokeParticle* smokeP = new SmokeParticle[SMOKE_Y + 1];
    
    float initPhase;
    float dPhase;
    float c;

    smoke()
    {
        initPhase = ofRandom(0, PI);
        dPhase = TWO_PI - ofRandom(0.001, 0.2);
        c = ofRandom(10, 50);
        
        for(int i=0; i < SMOKE_Y + 1; i++)
        {
            smokeP[i].setParticle(i, initPhase, c, dPhase);
        }
    }
    
    public:
    
    void draw()
    {
        for(int i=0; i<SMOKE_Y + 1; i++)
        {
            if(ofRandom(-1, 1 ) > 0)
            {
                c++;
            }
            else
            {
                c--;
            }
            
            smokeP[i].drawParticle();
        }    
    }
    
    private:
    
    ~smoke()
    {
        delete[] smokeP;
    }
    
};
