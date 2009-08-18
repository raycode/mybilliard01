#pragma once
namespace my_render {


MY_INTERFACE NodeFactory {
    virtual ~NodeFactory() {}

    virtual Node * createVisualScene( domVisual_sceneRef ) PURE;
    virtual Node * find( wstring id ) PURE;
    virtual bool destroyNode( Node * ) PURE;

};

}
