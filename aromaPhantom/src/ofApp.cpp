#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    //画面の基本設定
    ofBackground(0, 0, 0);
    ofEnableAlphaBlending();
    ofSetFrameRate(60);
    
    vidSize = ofPoint();
    
    vids = vidGrabber.listDevices();
    devID = 1;
    vidGrabber.setDeviceID(devID);

    //カメラから映像を取り込んで表示
    vidGrabber.setVerbose(true);
    vidGrabber.initGrabber(35,24);
    
    
    //使用する画像の領域を確保
    colorImg.allocate(35,24);
    grayImage.allocate(35,24);
    grayBg.allocate(35,24);
    grayDiff.allocate(35,24);
    
    //変数の初期化
    bLearnBakground = true;
    showCvAnalysis = false;
    threshold = 20;
    videoMode = 5;
    
    windowS.x = ofGetWidth();
    windowS.y = ofGetHeight();
    
    sacredA1E = ofPoint(350, 350);
    sacredA1S = ofPoint(150, 150);
    
    
    isStatS = true;
    
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
        
        currentRad = ofRandom(105.0, 315.0);
        
        cRad.push_back(currentRad);
        
        currentWidth = ofRandom(0.1, 10.0);
        
        clWidth.push_back(currentWidth);
        
    }
    
    sounf.load("BBTB3.mp3");
    sounf.setSpeed(0.7);    //original speed : 1.0
    sounf.setVolume(1.0);   // 0.0-1.0
    
    
}

//--------------------------------------------------------------
void ofApp::update()
{
    //新規フレームの取り込みをリセット
    bool bNewFrame = false;
    
    //カメラ使用の場合はカメラから新規フレーム取り込み
    vidGrabber.update();
    //新規にフレームが切り替わったか判定
    bNewFrame = vidGrabber.isFrameNew();
    
    
    //フレームが切り替わった際のみ画像を解析
    if (bNewFrame)
    {
        
        
        //取り込んだフレームを画像としてキャプチャ
        colorImg.setFromPixels(vidGrabber.getPixels(), 35,24);
        //左右反転
        colorImg.mirror(false, true);
        
        
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
        
        //vidPix = vidGrabber.getPixels();
    }
    
    
    ofSoundUpdate();
    
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
    float ratioX = ofGetWidth() / 35;
    float ratioY = ofGetHeight() / 24;
    
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
                //ON
                
                ofPushStyle();
                ofNoFill();
                ofSetColor(255, 0, 0);
                
                if(isStatS)
                {
                    ofDrawBitmapString("ON", windowS.x - 35, 225);
                }
                
                ofPopStyle();
                
                ccCol.r = (int)ofRandom(150, 255);
                ccCol.g = (int)ofRandom(150, 255);
                ccCol.b = (int)ofRandom(150, 255);
                
                sounf.play();
                
                
            }
        }
        else
        {
            //OFF
            
            ofPushStyle();
            ofSetColor(255, 0, 0);
            
            if(isStatS)
            {
                ofDrawBitmapString("OFF", windowS.x - 35, 225);
            }
            
            ofPopStyle();
            
            ccCol.r = 0;
            ccCol.g = 0;
            ccCol.b = 0;
            
            //sounf.stop();
            
        }
        
    }
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
    
//    pixCord.x = ofRandom(0, 35);
//    pixCord.y = ofRandom(0, 24);
//    
//    vidCol = vidPix.getColor(pixCord.x, pixCord.y);
    
    currentCol.r = (int)ofRandom(150, 255);
    currentCol.g = (int)ofRandom(120, 150);
    currentCol.b = (int)ofRandom(120, 150);
    
    cCol[(int)ofRandom(0, nCircles - 1)] = currentCol;
    
    
    if (isStatS)
    {
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
                           ofToString(vids[0].id, 2), windowS.x - 35, 65);
        ofDrawBitmapString("device1: " + vids[1].deviceName + " " +
                           ofToString(vids[1].id, 2), windowS.x - 35, 80);
        
        ofDrawBitmapString("cam: " + ofToString(vids[devID].deviceName,1), windowS.x - 35, 140);
        ofDrawBitmapString("bC: x: " + ofToString(bC.x,1), windowS.x - 35, 165);
        ofDrawBitmapString("bC: y: " + ofToString(bC.y,1), windowS.x - 35, 180);
        ofDrawBitmapString("SacredA1: x: " + ofToString(sacredA1S.x,1)
                           + " - " + ofToString(sacredA1E.x,1), windowS.x - 35, 195);
        ofDrawBitmapString("SacredA1: y: " + ofToString(sacredA1S.y,1)
                           + " - " + ofToString(sacredA1E.y,1), windowS.x - 35, 210);
        ofDrawBitmapString("SounfLoaded: " + ofToString(sounf.isLoaded(),1), windowS.x - 35, 24);
        ofDrawBitmapString("SounfPlaying: " + ofToString(sounf.isPlaying(),1), windowS.x - 35, 255);
        ofPopStyle();
        
    }
    
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
            //映像表示
            videoMode = 5;
            break;
            
        case 'a':
            //解析結果の表示の on / off
            showCvAnalysis ? showCvAnalysis=false : showCvAnalysis=true;
            break;
            
        case 's':
            //ステータス表示
            isStatS ? isStatS = false : isStatS = true;
            break;
            
        case 'f':
            //フルスクリーンに
            ofSetFullscreen(true);
            break;
            
        case 'g':
            //フルスクリーン解除
            ofSetFullscreen(false);
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
