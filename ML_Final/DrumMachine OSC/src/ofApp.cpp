#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0);
    
    tempo = 2;
    
    // Set bpm
    timer.setTempo(120);
    timer.setTicksPerBeat(tempo);
    
    // Maximilian audio stuff
    int sampleRate = 44100;
    int bufferSize= 512;
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    
    // Setup ofSound
    ofSoundStreamSettings settings;
    settings.setOutListener(this);
    settings.sampleRate = sampleRate;
    settings.numOutputChannels = 2;
    settings.numInputChannels = 0;
    settings.bufferSize = bufferSize;
    soundStream.setup(settings);
    
    // load samples
    kick.load("/Users/alexhoggett/Desktop/Dev/OF 0.10.1/apps/myApps/Drum Machine/bin/data/kick.wav");
    snare.load("/Users/alexhoggett/Desktop/Dev/OF 0.10.1/apps/myApps/Drum Machine/bin/data/snare.wav");
    hiHat.load("/Users/alexhoggett/Desktop/Dev/OF 0.10.1/apps/myApps/Drum Machine/bin/data/hiHat.wav");
    
    // counter to iterate through beats
    counter = 0;
    
    thresh = 75;
    random = 0;
    
    // set button positions
    for (int i = 0; i < 16; i++){
        hiHatBeat[i].setPosition(i * 50, 0);
    } for (int i = 0; i < 16; i++){
        snareBeat[i].setPosition(i * 50, 50);
    } for (int i = 0; i < 16; i++){
        kickBeat[i].setPosition(i * 50, 100);
    }
    
    
    receiver.setup(PORT);
}

//--------------------------------------------------------------
void ofApp::update(){
    for (int i = 0; i < 16; i++){
        hiHatBeat[i].update();
        snareBeat[i].update();
        kickBeat[i].update();
    }
    
    while(receiver.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(&m);
        
        // check for mouse moved message
        if(m.getAddress() == "/wek/outputs"){
//            vx = m.getArgAsFloat(0);
//            vy = m.getArgAsFloat(1);
            cout << m.getArgAsInt(0) << endl;
            tempo = m.getArgAsInt(0);
        }
        else{
            // unrecognized message: display on the bottom of the screen
            string msg_string;
            msg_string = m.getAddress();
            msg_string += ": ";
            for(int i = 0; i < m.getNumArgs(); i++){
                // get the argument type
                msg_string += m.getArgTypeName(i);
                msg_string += ":";
                // display the argument - make sure we get the right type
                if(m.getArgType(i) == OFXOSC_TYPE_INT32){
                    msg_string += ofToString(m.getArgAsInt32(i));
                }
                else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
                    msg_string += ofToString(m.getArgAsFloat(i));
                }
                else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
                    msg_string += m.getArgAsString(i);
                }
                else{
                    msg_string += "unknown";
                }
            }
            cout << msg_string << endl;
        }
        
    }
    timer.setTicksPerBeat(tempo);
}

//--------------------------------------------------------------
void ofApp::draw(){
    // centre the buttons
    int translateX = (ofGetWindowWidth() - 800) / 2;
    int translateY = (ofGetWindowHeight() - 150) / 2;
    
    // update button positions incase the screen size changes
    for (int i = 0; i < 16; i++){
        hiHatBeat[i].setPosition(i * 50 + translateX, translateY);
    } for (int i = 0; i < 16; i++){
        snareBeat[i].setPosition(i * 50 + translateX, 50 + translateY);
    } for (int i = 0; i < 16; i++){
        kickBeat[i].setPosition(i * 50 + translateX, 100 + translateY);
    }
    
    for (int i = 0; i < 16; i++){
        hiHatBeat[i].draw();
        snareBeat[i].draw();
        kickBeat[i].draw();
    }
    
    // draw the 'ticker'
    ofSetColor(255, 255, 0);
    ofTranslate(translateX, translateY);
    ofDrawEllipse(25 + (counter * 50), -20, 10, 10);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    for (int i = 0; i < 16; i++){
        hiHatBeat[i].mouseClicked(x, y);
        snareBeat[i].mouseClicked(x, y);
        kickBeat[i].mouseClicked(x, y);
    }
}

//--------------------------------------------------------------
void ofApp::audioIn(ofSoundBuffer &input){
    
}

//--------------------------------------------------------------
void ofApp::audioOut(ofSoundBuffer& output){
    std::size_t outChannels = output.getNumChannels();
    
    for (int i = 0; i < output.getNumFrames(); ++i){
        timer.ticker();
        
        if (timer.tick){
            if (kickBeat[counter].getState()){
                random = 1 + rand() % 100;
                if (random <= thresh) {kick.trigger();}
            }
            if (snareBeat[counter].getState()){
                random = 1 + rand() % 100;
                if (random <= thresh) {snare.trigger();}
            }
            if (hiHatBeat[counter].getState()){
                random = 1 + rand() % 100;
                if (random <= thresh) {hiHat.trigger();}
            }
            counter ++;
        }
        if (counter == 16){counter = 0;}
        
        sampleOut=(snare.playOnce() * 0.5) + (kick.playOnce() * 1.5) + hiHat.playOnce();
        
        output[i * outChannels] = sampleOut;
        output[i * outChannels + 1] = output[i * outChannels];
    }
    
    //cout << counter << endl;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
