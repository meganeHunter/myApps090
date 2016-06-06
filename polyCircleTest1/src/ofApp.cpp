#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    //âÊñ ÇÃäÓñ{ê›íË
    ofBackground(0, 0, 0);
    ofEnableAlphaBlending();
    ofSetFrameRate(60);
    ofEnableSmoothing();
    ofEnableAntiAliasing();
    ofEnableAlphaBlending();
    ofSetPolyMode(OF_POLY_WINDING_ODD);
    
    windowS.x = ofGetWidth();
    windowS.y = ofGetHeight();
    
    wCenter = windowS / 2;
    
    nCircles = 24;
    
    ccCol = ofColor(255,255,255);
    
    cRes = 255;
    
    ofSetCircleResolution(cRes);
    
    for(i=0; i < nCircles; i++)
    {
        currentC.x = (int)ofRandom(wCenter.x - 12, wCenter.x + 12);
        currentC.y = (int)ofRandom(wCenter.y - 12, wCenter.y + 12);
        
        circlesC.push_back(currentC);
        
        currentCol.r = (int)ofRandom(158, 255);
        currentCol.g = (int)ofRandom(0, 120);
        currentCol.b = (int)ofRandom(0, 120);
        
        cCol.push_back(currentCol);
        
        currentRad = ofRandom(85.0, 365.0);
        
        cRad.push_back(currentRad);
        
        currentWidth = ofRandom(0.1, 10.0);
        
        clWidth.push_back(currentWidth);
        
    }
    
}

//--------------------------------------------------------------
void ofApp::update()
{
    currentCol.r = (int)ofRandom(150, 255);
    currentCol.g = (int)ofRandom(0, 120);
    currentCol.b = (int)ofRandom(0, 120);
    
    cCol[(int)ofRandom(0, nCircles - 1)] = currentCol;

}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofPushStyle();
    ofNoFill();
    
    for (i = 0; i < nCircles; i++)
    {
        //ofSetLineWidth(clWidth[i]);
        glLineWidth(clWidth[i]);
        ofSetColor(cCol[i]);
        ofDrawCircle(circlesC[i], cRad[i]);
        
    }
    
    ofFill();
    
    ofSetColor(ccCol);
    ofDrawCircle(wCenter.x, wCenter.y, 50);
    
    ofPopStyle();
    
    ofSetColor(255, 255, 255);
    ofDrawBitmapString("FPS: " + ofToString(ofGetFrameRate()), windowS.x - 320, 65);
    ofDrawBitmapString("Number of Circles: " + ofToString(nCircles), windowS.x - 320, 80);
    ofDrawBitmapString("Current Colors: r: " + ofToString((int)currentCol.r), windowS.x - 320, 95);
    ofDrawBitmapString("Current Colors: g: " + ofToString((int)currentCol.g), windowS.x - 320, 110);
    ofDrawBitmapString("Current Colors: b: " + ofToString((int)currentCol.b), windowS.x - 320, 125);
    ofDrawBitmapString("Current Resolution: " + ofToString(cRes), windowS.x - 320, 140);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    switch (key)
    {
        case 'x':
            
            ccCol.r = (int)ofRandom(150, 255);
            ccCol.g = (int)ofRandom(150, 255);
            ccCol.b = (int)ofRandom(150, 255);
            
            break;
            
        case 'q':
            cRes++;
            ofSetCircleResolution(cRes);
            
            break;
            
        case 'w':
            cRes--;
            ofSetCircleResolution(cRes);
            
            break;
            
        default:
            break;
    }
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
