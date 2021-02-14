#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "button.hpp"
#include "ofxOsc.h"

// listen on port 12000
#define PORT 12000

class ofApp : public ofBaseApp{
    
public:
    void setup() override;
    void update() override;
    void draw() override;
    
    void keyPressed(int key) override;
    void keyReleased(int key) override;
    void mouseMoved(int x, int y ) override;
    void mouseDragged(int x, int y, int button) override;
    void mousePressed(int x, int y, int button) override;
    void mouseReleased(int x, int y, int button)override;
    void mouseEntered(int x, int y) override;
    void mouseExited(int x, int y) override;
    void windowResized(int w, int h) override;
    void dragEvent(ofDragInfo dragInfo) override;
    void gotMessage(ofMessage msg) override;
    
    maxiClock timer;
    maxiSample kick, snare, hiHat;
    
    double sampleOut = 0;
    int counter, sampleRate, bufferSize, thresh, random;
    
    Button kickBeat[16], snareBeat[16], hiHatBeat[16];
    
    ofSoundStream soundStream;
    //rofxSlider slider;
    
    int tempo;
    
    /* ofxMaxi*/
    void audioIn(ofSoundBuffer& input) override;
    void audioOut(ofSoundBuffer& output) override;
    
    // OSC
    ofxOscReceiver receiver;
    
};
