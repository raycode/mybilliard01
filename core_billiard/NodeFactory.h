#pragma once
namespace my_render {


MY_INTERFACE NodeFactory {
    virtual ~NodeFactory() {}

    virtual Node * createVisualScene( domVisual_sceneRef ) = 0;
    virtual Node * find( wstring id ) = 0;
    virtual void release( Node * ) = 0;

};

}
