#pragma once
namespace my_render {

INTERFACE_ NodeFactory {
public:
    virtual Node * createVisualScene( domVisual_sceneRef ) = 0;
    virtual Node * find( wstring id ) = 0;
    virtual void release( Node * ) = 0;

public: virtual ~NodeFactory() {}
};

}
