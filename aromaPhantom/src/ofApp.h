#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"


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

    
    //ライブカメラを使用する際には、カメラ入力を準備
    ofVideoGrabber 		vidGrabber;

    ofxCvColorImage colorImg; //オリジナルのカラー映像
    ofxCvGrayscaleImage grayImage; //グレースケールに変換後
    ofxCvGrayscaleImage grayBg; //キャプチャーした背景画像
    ofxCvGrayscaleImage grayDiff; //現在の画像と背景との差分
    ofxCvContourFinder contourFinder; //輪郭抽出のためのクラス
    
    bool bLearnBakground; //背景画像を登録したか否か
    bool showCvAnalysis; //解析結果を表示するか
    int threshold; //2値化の際の敷居値
    int videoMode; //表示する画像を選択
    
    vector<ofVideoDevice> vids;
    
    int devID;
    ofPoint windowS;
    
    int i;
    
    bool isStatS;
    
    ofPoint sacredA1S, sacredA1E;
    ofPoint sacredA2S, sacredA2E;
    ofPoint bC;
    
    int nCircles;
    int cRes;
    
    ofPoint wCenter;
    ofPoint currentC;
    
    ofColor currentCol;
    ofColor ccCol;
    
    float currentRad;
    float currentWidth;
    
    vector<ofPoint> circlesC;
    vector<ofColor> cCol;
    vector<float> cRad;
    vector<float> clWidth;
    
    //ofPixels& vidPix;
    //ofColor& vidCol;
    
    ofPoint pixCord;
    
    ofSoundPlayer sounf;
    
    ofPoint vidSize;


};
