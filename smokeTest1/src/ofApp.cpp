#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    smoke smoke;
    
    ofSetWindowShape(WIDTH, HEIGHT);
    ofSetBackgroundColor(0);
    
    smoke = new smoke[SMOKE_NUM];
    
    for(int i = 0; i < SMOKE_NUM; i++)
    {
        smoke[i] = new class smoke();
    }
}

//--------------------------------------------------------------
void ofApp::update()
{

}

//--------------------------------------------------------------
void ofApp::draw()
{
    for(int i = 0; i < SMOKE_NUM; i++)
    {
        smoke[i].smokeDraw();
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
void ofApp::mouseMoved(int x, int y)
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