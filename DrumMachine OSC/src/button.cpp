#include "button.hpp"
Button::Button(){
    this->setPosition(0, 0);
    this->setSize(50, 50);
    this->setState(0);
}

void Button::setSize(float w, float h){
    this->width = w;
    this->height = h;
}

void Button::setPosition(float x, float y){
    this->xPos = x;
    this->yPos = y;
}

void Button::mouseClicked(float mX, float mY){
    if (mX > this->xPos && mX < (this->xPos + this->width) && mY > this->yPos && mY < (this->yPos) + this->height){
        
        if (this->getState()){
            this->setState(0);
        } else {
            this->setState(1);
        }
        
        this->animationState = 0.3;
    }
}

void Button::update(){
    if (this->animationState < 1){
        this->animationState += 0.01;
    }
}

void Button::draw(){
    ofSetColor(255);
    ofDrawRectangle(this->xPos, this->yPos, this->width, this->height);
    
    if (this->getState()){
        ofSetColor(ofColor(255, 0, 0) * animationState);
    } else {
        ofSetColor(0);
    }
    
    ofDrawRectangle(this->xPos+2, this->yPos+2, this->width-4, this->height-4);
}

void Button::setState(int i){
    this->state = i;
}

int Button::getState(){
    return state;
}
