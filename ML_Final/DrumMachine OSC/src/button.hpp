#ifndef button_hpp
#define button_hpp

#include <stdio.h>
#include <ofMain.h>

class Button{
public:
    Button();
    void draw();
    void update();
    void mouseClicked(float mX, float mY);
    void setPosition(float x, float y);
    void setSize(float w, float h);
    void setState(int i);
    int getState();
    
private:
    float animationState;

protected:
    float width;
    float height;
    float xPos;
    float yPos;
    int state;
};
#endif /* button_hpp */
