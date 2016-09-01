#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    
    ofSetBackgroundColor(0, 0, 0);
    
    devs = vid.listDevices();
    
    windowS.x = ofGetWidth();
    windowS.y = ofGetHeight();
    
    wCenter = windowS / 2;
    
    
}

//--------------------------------------------------------------
void ofApp::update()
{

}

//--------------------------------------------------------------
void ofApp::draw()
{
    
    ofSetColor(255, 255, 255);
    
    i = 0;
    iEdn = devs.end();
    for (iter = devs.begin(); iter != iEdn; ++iter)
    {
        ofDrawBitmapString("device" + ofToString(i,1) + ": " + (*iter).deviceName + " " +
                       ofToString((*iter).id, 2), windowS.x, 65 + (15 * i));
        i++;
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
