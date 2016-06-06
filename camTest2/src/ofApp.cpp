#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    //画面の基本設定
    ofBackground(0, 0, 0);
    ofEnableAlphaBlending();
    ofSetFrameRate(60);
    
    vids = vidGrabber.listDevices();
    devID = 0;
    vidGrabber.setDeviceID(devID);
    //カメラ使用の場合
#ifdef _USE_LIVE_VIDEO
    //カメラから映像を取り込んで表示
    vidGrabber.setVerbose(true);
    vidGrabber.initGrabber(320,240);
#else
    //カメラ不使用の場合ムービーファイルを読み込んで再生
    vidPlayer.loadMovie("fingers.mov");
    vidPlayer.play();
#endif
    
    //使用する画像の領域を確保
    colorImg.allocate(320,240);
    grayImage.allocate(320,240);
    grayBg.allocate(320,240);
    grayDiff.allocate(320,240);
    
    //変数の初期化
    bLearnBakground = true;
    showCvAnalysis = false;
    threshold = 20;
    videoMode = 0;
    
    windowS.x = ofGetWidth();
    windowS.y = ofGetHeight();
    
    sacredA1E = ofPoint(350, 350);
    sacredA1S = ofPoint(150, 150);
    
    //sacredA2E = ofPoint((windowS.x / 2) + 150, (windowS.y / 2) + 150);
    //sacredA2S = ofPoint((windowS.x / 2) - 70, (windowS.y / 2) - 70);

}

//--------------------------------------------------------------
void ofApp::update()
{
    //新規フレームの取り込みをリセット
    bool bNewFrame = false;
    
#ifdef _USE_LIVE_VIDEO
    //カメラ使用の場合はカメラから新規フレーム取り込み
    vidGrabber.update();
    //新規にフレームが切り替わったか判定
    bNewFrame = vidGrabber.isFrameNew();
#else
    //カメラ不使用の場合は、ビデオプレーヤーから新規フレーム取り込み
    vidPlayer.idleMovie();
    //新規にフレームが切り替わったか判定
    bNewFrame = vidPlayer.isFrameNew();
#endif
    
    //フレームが切り替わった際のみ画像を解析
    if (bNewFrame)
    {
#ifdef _USE_LIVE_VIDEO
        //取り込んだフレームを画像としてキャプチャ
        colorImg.setFromPixels(vidGrabber.getPixels(), 320,240);
        //左右反転
        colorImg.mirror(false, true);
#else
        //取り込んだフレームを画像としてキャプチャ
        colorImg.setFromPixels(vidPlayer.getPixels(), 320,240);
#endif
        
        //カラーのイメージをグレースケールに変換
        grayImage = colorImg;
        
        //まだ背景画像が記録されていなければ、現在のフレームを背景画像とする
        if (bLearnBakground == true)
        {
            grayBg = grayImage;
            bLearnBakground = false;
        }
        
        //グレースケールのイメージと取り込んだ背景画像との差分を算出
        grayDiff.absDiff(grayBg, grayImage);
        //画像を2値化(白と黒だけに)する
        grayDiff.threshold(threshold);
        //2値化した画像から輪郭を抽出する
        contourFinder.findContours(grayDiff, 25, grayDiff.width * grayDiff.height, 10, false, false);
        
    }
}

//--------------------------------------------------------------
void ofApp::draw()
{
    //現在のモードに応じて、表示する映像を切り替え
    switch (videoMode)
    {
            
        case 1:
            //グレースケール映像
            grayImage.draw(0, 0, ofGetWidth(), ofGetHeight());
            break;
            
        case 2:
            //背景画像
            grayBg.draw(0, 0, ofGetWidth(), ofGetHeight());
            break;
            
        case 3:
            //2値化された差分映像
            grayDiff.draw(0, 0, ofGetWidth(), ofGetHeight());
            break;
            
        case 0:
            //カラー映像
            colorImg.draw(0, 0, ofGetWidth(), ofGetHeight());
            break;
            
        default:
            break;
    }
    
    //画面に対する映像の比率を計算
    float ratioX = ofGetWidth() / 320;
    float ratioY = ofGetHeight() / 240;
    
    //解析結果を表示する場合
    if (showCvAnalysis)
    {
        //検出した解析結果を表示
        for (int i = 0; i < contourFinder.nBlobs; i++)
        {
            ofPushMatrix();
            //画面サイズいっぱいに表示されるようリスケール
            glScalef((float)ofGetWidth() / (float)grayDiff.width,
                     (float)ofGetHeight() / (float)grayDiff.height, 1.0f);
            
            contourFinder.blobs[i].draw(0,0);
            ofFill();
            ofSetColor(255, 255, 255);
            ofDrawEllipse(contourFinder.blobs[i].centroid.x, contourFinder.blobs[i].centroid.y, 4, 4);
            ofPopMatrix();
        }
    }
    
    for (i = 0; i < contourFinder.nBlobs; i++)
    {
        bC = ofPoint(contourFinder.blobs[i].centroid.x,
                     contourFinder.blobs[i].centroid.y);
        
        if(sacredA1S.x< bC.x && bC.x < sacredA1E.x)
        {
            if(sacredA1S.y< bC.y && bC.y < sacredA1E.y)
            {
                //on
                ofPushStyle();
                ofNoFill();
                ofSetColor(255, 0, 0);
                ofDrawBitmapString("ON", windowS.x / 2, windowS.y / 2);
                ofSetLineWidth(5.0);
                ofDrawCircle(windowS.x / 2, windowS.y / 2, 50);
                ofPopStyle();
            }
        }
//        else if(sacredA2S.x< bC.x && bC.x < sacredA2E.x)
//        {
//            if(sacredA2S.y< bC.y && bC.y < sacredA2E.y)
//            {
//                //on
//                ofPushStyle();
//                ofNoFill();
//                ofSetColor(255, 0, 0);
//                ofDrawBitmapString("ON", windowS.x / 2, windowS.y / 2);
//                ofSetLineWidth(5.0);
//                ofDrawCircle(windowS.x / 2, windowS.y / 2, 50);
//                ofPopStyle();
//            }
//        }
        else
        {
            ofPushStyle();
            ofSetColor(255, 0, 0);
            ofDrawBitmapString("OFF", windowS.x / 2, windowS.y / 2);
            ofPopStyle();
        }
        
    }
    
    
    ofPushStyle();
    ofNoFill();
    ofSetColor(255, 0, 0);
    ofSetLineWidth(5.0);
    ofDrawRectangle(sacredA1S.x, sacredA1S.y, sacredA1E.x - sacredA1S.x, sacredA1E.y - sacredA1S.y);
    //ofDrawRectangle(sacredA2S.x, sacredA2S.y, sacredA2S.x - sacredA2E.x, sacredA2S.y - sacredA2E.y);
    ofPopStyle();
    
    
    //ログと操作説明を表示
    ofPushStyle();
    ofSetColor(255, 0, 0);
    ofDrawBitmapString("FPS: "+ofToString(ofGetFrameRate()), 20, 20);
    ofDrawBitmapString("Threshold: "+ofToString(threshold), 20, 35);
    ofDrawBitmapString("Number of Blobs: "+ofToString(contourFinder.nBlobs), 20, 50);
    ofDrawBitmapString("[0] Show original video", 20, 65);
    ofDrawBitmapString("[1] Show grayscale video", 20, 80);
    ofDrawBitmapString("[2] Show captured background", 20, 95);
    ofDrawBitmapString("[3] Show difference from background", 20, 110);
    ofDrawBitmapString("[space] Captuer background", 20, 125);
    ofDrawBitmapString("[a] Analysis on / off", 20, 140);
    
    ofDrawBitmapString("device0: " + vids[0].deviceName + " " +
                       ofToString(vids[0].id, 2), windowS.x - 320, 65);
    ofDrawBitmapString("device1: " + vids[1].deviceName + " " +
                       ofToString(vids[1].id, 2), windowS.x - 320, 80);
//    ofDrawBitmapString("device2: " + vids[2].deviceName + ofToString(vids[2].id, 1), windowS.x - 20, 95);
//    ofDrawBitmapString("device3: " + vids[3].deviceName + ofToString(vids[3].id, 1), windowS.x - 20, 110);
//    ofDrawBitmapString("device4: " + vids[4].deviceName + ofToString(vids[4].id, 1), windowS.x - 20, 125);

    ofDrawBitmapString("cam: " + ofToString(vids[devID].deviceName,1), windowS.x - 320, 140);
    ofDrawBitmapString("bC: x: " + ofToString(bC.x,1), windowS.x - 320, 165);
    ofDrawBitmapString("bC: y: " + ofToString(bC.y,1), windowS.x - 320, 180);
    ofDrawBitmapString("SacredA1: x: " + ofToString(sacredA1S.x,1)
                       + " - " + ofToString(sacredA1E.x,1), windowS.x - 320, 195);
    ofDrawBitmapString("SacredA1: y: " + ofToString(sacredA1S.y,1)
                       + " - " + ofToString(sacredA1E.y,1), windowS.x - 320, 210);
    //ofDrawBitmapString("SacredA2: x: " + ofToString(sacredA2S.x,1)
    //                   + " - " + ofToString(sacredA2E.x,1), windowS.x - 320, 225);
    //ofDrawBitmapString("SacredA2: y: " + ofToString(sacredA2S.y,1)
    //                   + " - " + ofToString(sacredA2E.y,1), windowS.x - 320, 240);
    
    ofPopStyle();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    //キー入力でモード切り替え
    switch (key)
    {
        case '0':
            //カラー映像表示
            videoMode = 0;
            break;
            
        case '1':
            //グレースケール映像表示
            videoMode = 1;
            break;
            
        case '2':
            //背景画像表示
            videoMode = 2;
            break;
            
        case '3':
            //2値化した差分映像
            videoMode = 3;
            break;
            
        case 'x':
            //2値化した差分映像
            videoMode = 5;
            break;
            
        case 'a':
            //解析結果の表示の on / off
            showCvAnalysis ? showCvAnalysis=false : showCvAnalysis=true;
            break;
            
        case 'f':
            //フルスクリーンに
            ofSetFullscreen(true);
            break;
            
        case ' ':
            //背景画像を新規に取り込む
            bLearnBakground = true;
            break;
            
        case '+':
            //2値化の閾値を増加
            threshold ++;
            if (threshold > 255) threshold = 255;
                break;
            
        case '-':
            //2値化の閾値を減少
            threshold --;
            if (threshold < 0) threshold = 0;
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
