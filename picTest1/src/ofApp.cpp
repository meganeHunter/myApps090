#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofBackground(255, 255, 255);
    ofSetFrameRate( 60 );
    ofSetVerticalSync( true );
    ofEnableSmoothing();
    
    display = false;
    haikei.loadImage("TER.png");
    
}

//--------------------------------------------------------------
void ofApp::update()
{
    
}

//--------------------------------------------------------------
void ofApp::draw()
{
    //適当な描画
    ofBackground(255);
    ofSetColor(255, 255, 255);
    haikei.draw(0, 0, ofGetWidth(), ofGetHeight());
    ofEllipse(300*sin(ofGetElapsedTimef())+ofGetWidth()/2, ofGetHeight()/2, 20, 20);
    //ここまで
    
    ofSetColor(100);
    ofNoFill();
    for (int i=0; i<img.size(); i++)
    {
        img[i].grabScreen(lx[i], ly[i], ww[i], hh[i]);
        ofRect(lx[i], ly[i], ww[i], hh[i]);
    }
    
    ofSetColor(255, 255, 255);
    
    if (display) {
        ofBackground(0, 0, 0);
        
        for (int i=0; i<img.size(); i++)
        {
            img[i].draw(lx[i], ly[i], ww[i], hh[i]);
        }
    }
    

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if( key == 'a' )
    {
        if (display)
        {
            display = false;
        }
        else
        {
            display = true;
        }
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
    if (mouseCount % 3 == 0)
    {                          //一回目のクリック(切り取る基準の場所指定)
        lx.push_back(x);
        ly.push_back(y);
        ww.push_back(0);
        hh.push_back(0);
    }
    else if(mouseCount % 3 == 1)
    {                      //二回目のクリック(画像の幅を決める)
        ww[mouseCount/3] = x - lx[mouseCount/3];
        if (x - lx[mouseCount/3] < 0)
        {
            lx[mouseCount/3] += ww[mouseCount/3];
            ww[mouseCount/3] *= -1;
        }
    }
    else{                                              //三回目のクリック(画像の高さを決めた後、イメージを切り取りofImageを作る)
        hh[mouseCount/3] = y - ly[mouseCount/3];
        if (y - ly[mouseCount/3] < 0)
        {
            ly[mouseCount/3] += hh[mouseCount/3];
            hh[mouseCount/3] *= -1;
        }
        
        kariImage.grabScreen(lx[mouseCount/3], ly[mouseCount/3], ww[mouseCount/3], hh[mouseCount/3]);
        img.push_back(kariImage);
        
    }
    mouseCount++;
    
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
