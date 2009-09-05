#pragma once
namespace my_render {


MY_INTERFACE Node : EXTENDS_INTERFACE( Base ), EXTENDS_INTERFACE( Displayable ) {

    virtual Node * getParent() PURE;
    virtual Node * getNextSibling() PURE;
    virtual Node * getFirstChild() PURE;
    virtual size_t getNbChild() PURE;
    virtual wstring getSID() PURE;

    virtual bool hasParent() PURE;
    virtual bool hasNextSibling() PURE;
    virtual bool hasFirstChild() PURE;

    virtual void display() PURE;
    virtual void display_positionOnly() PURE;

};

}