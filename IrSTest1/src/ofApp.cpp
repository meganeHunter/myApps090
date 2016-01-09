#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    potValue = "IRS:";
    
    ard.connect("/dev/cu.usbmodem1411", 57600);
    
    ofAddListener(ard.EInitialized, this, &ofApp::setupArduino);
    bSetupArduino = false;
    
    ofBackground(0, 0, 0);

}

//--------------------------------------------------------------
void ofApp::update()
{
    updateArduino();

}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofSetColor(255, 255, 255);
    if(!bSetupArduino)
    {
        ofDrawBitmapString("arduino not ready...\n", 515, 40);
    }
    else
    {
       ofDrawBitmapString("IRS: " + ofToString(ard.getAnalog(5)) +"\n" , 515, 40);
        
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{


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

//--------------------------------------------------------------
