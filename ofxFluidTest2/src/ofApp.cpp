#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    
    ofEnableAlphaBlending();
    ofSetCircleResolution(100);
    
    width = 170;
    height = 800;
    
    ofSeedRandom();
    
    rad = 5.85;
    temp = 48.0;
    den = 17.35;
    
    pos = ofPoint(width * 0.5, height * 0.95);
    dir = ofPoint(0, -2);
    
    isDrawS = true;
    isPaused = false;
    isStatA = true;
    
    pTime = 600;
    pCount = 0;
    
    // Initial Allocation
    //
    fluid.allocate(width, height, 0.5);
    
    // Seting the gravity set up & injecting the background image
    //
    fluid.dissipation = 0.9638;
    fluid.velocityDissipation = 0.9758;
    
    
    fluid.setGravity(ofVec2f(0.0,-0.105));
    
    //  Set obstacle
    //
    fluid.begin();
    ofSetColor(0,0);
    ofSetColor(255);
    //ofCircle(width * 0.5,height, 5.0);
    fluid.end();
    fluid.setUseObstacles(false);
    
    // Adding constant forces
    //
    //fluid.addConstantForce(ofPoint(width * 0.5,height * 0.85), ofPoint(0,-2), ofFloatColor(0.5,0.1,0.0), 10.f);
    
    ofSetWindowShape(width + 58.0, height);

}
//--------------------------------------------------------------
void ofApp::update()
{
    
    // Adding temporal Force
    //
    /*
    ofPoint m = ofPoint(mouseX,mouseY);
    ofPoint d = (m - oldM) * 10.0;
    oldM = m;
    ofPoint c = ofPoint(640 * 0.5, 480 * 0.5) - m;
    c.normalize();
    */
    
    dir.x = ofRandomf() * 1.57;
    pos.x = (width / 2.0) + (ofRandomf() * 0.5);
    
    
    if(isDrawS && !isPaused)
        fluid.addTemporalForce(pos, dir, ofFloatColor(0.12, 0.09, 0.09), rad, temp, den);
    
    if(isPaused)
        pCount += ofGetFrameRate() / 60;
    if(pCount >= pTime)
    {
        pCount = 0;
        isPaused = false;
    }
    
    if(!isStatA)
        ofSetWindowShape(width, height);
    else
        ofSetWindowShape(width + 58.0, height);
    
    //  Update
    //
    fluid.update();
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackgroundGradient(ofColor::gray, ofColor::black, OF_GRADIENT_LINEAR);
    
    fluid.draw();
    
    if(isStatA)
    {
        ofSetColor(255, 255, 255, 255);
        ofDrawBitmapString("rad: " + ofToString(rad), width * 0.71, height * 0.79);
        ofDrawBitmapString("temp: " + ofToString(temp), width * 0.71, height * 0.81);
        ofDrawBitmapString("den: " + ofToString(den), width * 0.71, height * 0.83);
        ofDrawBitmapString("pos.x: " + ofToString(pos.x), width * 0.71, height * 0.85);
        ofDrawBitmapString("dir.x: " + ofToString(dir.x), width * 0.71, height * 0.87);
        ofDrawBitmapString("pCount: " + ofToString(pCount), width * 0.71, height * 0.89);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if( key == 'p')
        bPaint = !bPaint;
    if( key == 'o')
        bObstacle = !bObstacle;
    if( key == 'u')
        bBounding = !bBounding;
    if( key == 'i')
        bClear = !bClear;
    
    if( key == 'a')
        rad += 0.05;
    if( key == 'z')
        rad -= 0.05;
    if( key == 's')
        temp += 0.05;
    if( key == 'x')
        temp -= 0.05;
    if( key == 'd')
        den += 0.05;
    if( key == 'c')
        den -= 0.05;
    
    if(key == 'q')
        isDrawS = !isDrawS;
    if(key == 'w')
    {
        isPaused = !isPaused;
        pCount = 0;
    }
    if(key == 'e')
        isStatA = !isStatA;

    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{

    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{

    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{

    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{

    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{

    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{

    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{

    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{

    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{

    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
    
}


