#ifndef DRAGABLE
#define DRAGABLE

#include <string>

enum DragType{
    DRAG_EMPTY,
    DRAG_CHANNEL_INDEX,
    DRAG_BEAT_ZONE_INDEX,
    DRAG_BEAT_ZONE_SCALE
};

class Dragable{
public:
    DragType dragType;
    std::string name;
    int value;

    void reset(){
        dragType = DRAG_EMPTY;
        name = std::string{"General Dragable"};
        value = -1;
    }

    void setup(DragType _type, std::string _name, int _value){
        dragType = _type;
        name = _name;
        value = _value;
    }

    DragType getDragType(){
        return dragType;
    }

    std::string getName(){
        return name;
    }

    int getValue(){
        return value;
    }
};

extern Dragable dragable;
#endif