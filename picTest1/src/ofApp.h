#pragma once

#include "ofMain.h"

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
    
    bool display;           //画面切り替え用
    ofImage haikei;         //適当な素材
    
    ofImage kariImage;      //一旦画像を入れておくところ
    
    vector<ofImage> img;    //以下動的配列に切り取る画像の場所や大きさなどを入れてimgに画像を格納する
    vector<int> lx;
    vector<int> ly;
    vector<int> ww;
    vector<int> hh;
    
    int mouseCount;
    
};
