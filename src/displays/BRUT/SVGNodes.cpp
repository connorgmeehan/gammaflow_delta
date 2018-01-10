#ifndef SVG_NODES
#define SVG_NODES

#include "ofMain.h"
#include "globals.h"
#include "Channel.h"

enum NodeType{
    SVG_NODE_CIRCLE,
    SVG_NODE_SQUARE  
};

class SvgNode{
    vector<SvgNode*> children;
    NodeType type;
    
};

class SvgNodes : public Channel {

};

#endif