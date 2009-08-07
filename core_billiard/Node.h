#pragma once
namespace my_render {

INTERFACE_ Node : public Base {
public:
    virtual Node * getParent() = 0;
    virtual Node * getNextSibling() = 0;
    virtual Node * getFirstChild() = 0;
    virtual size_t getNbChild() = 0;

    virtual void update( float time ) = 0;
    virtual void render( Render * render ) = 0;

public: virtual ~Node() {}
};

}