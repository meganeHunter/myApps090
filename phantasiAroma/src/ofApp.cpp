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
    
    ofSetWindowShape(width + 85.0, height);
    
    irsVal = 620.0;
    
    ard.connect("/dev/cu.usbmodem1411", 57600);
    
    ofAddListener(ard.EInitialized, this, &ofApp::setupArduino);
    bSetupArduino = false;
    
}
//--------------------------------------------------------------
void ofApp::update()
{
    
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
        ofSetWindowShape(width + 85.0, height);
    
    //  Update
    //
    fluid.update();
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    updateArduino();
    
    if(!isPaused)
    {
        
        irsVal = (float)ard.getAnalog(5);
    }
    
    
    if(irsVal < 590.0)
    {
        isPaused = true;
    }
    else
    {
        isPaused = false;
    }
    

}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackgroundGradient(ofColor::gray, ofColor::black, OF_GRADIENT_LINEAR);
    
    fluid.draw();
    
    if(isStatA)
    {
        ofSetColor(255, 255, 255, 255);
        ofDrawBitmapString("isPaused: " + ofToString(isPaused), width * 0.71, height * 0.75);
        ofDrawBitmapString("rad: " + ofToString(rad), width * 0.71, height * 0.79);
        ofDrawBitmapString("temp: " + ofToString(temp), width * 0.71, height * 0.81);
        ofDrawBitmapString("den: " + ofToString(den), width * 0.71, height * 0.83);
        ofDrawBitmapString("pos.x: " + ofToString(pos.x), width * 0.71, height * 0.85);
        ofDrawBitmapString("dir.x: " + ofToString(dir.x), width * 0.71, height * 0.87);
        ofDrawBitmapString("pCount: " + ofToString(pCount), width * 0.71, height * 0.89);
        if(!bSetupArduino)
        {
            ofDrawBitmapString("arduino not ready...", width * 0.71, height * 0.73);
        }
        else
        {
            ofDrawBitmapString("IRS: " + ofToString(irsVal, 5), width * 0.71, height * 0.73);
            
        }

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

//--------------------------------------------------------------
void ofApp::setupArduino(const int & version)
{
    // remove listener because we don't need it anymore
    ofRemoveListener(ard.EInitialized, this, &ofApp::setupArduino);
    
    
    // print firmware name and version to the console
    ofLogNotice() << ard.getFirmwareName();
    ofLogNotice() << "firmata v" << ard.getMajorFirmwareVersion() << "." << ard.getMinorFirmwareVersion();
    
    // Note: pins A0 - A5 can be used as digital input and output.
    // Refer to them as pins 14 - 19 if using StandardFirmata from Arduino 1.0.
    // If using Arduino 0022 or older, then use 16 - 21.
    // Firmata pin numbering changed in version 2.3 (which is included in Arduino 1.0)
    
    for(int i = 0; i < 6; i++)
    {
        ard.sendAnalogPinReporting(i, ARD_ANALOG);
        
    }
    
    
    // it is now safe to send commands to the Arduino
    bSetupArduino = true;
    
}
//--------------------------------------------------------------
void ofApp::updateArduino()
{
    
    // update the arduino, get any data or messages.
    // the call to ard.update() is required
    ard.update();
    
    
}


