#pragma once
namespace my_render {

INTERFACE_ Node {
public:
    virtual Node * getParent() = 0;
    virtual Node * getNextSibling() = 0;
    virtual Node * getFirstChild() = 0;
    virtual size_t getNbChild() = 0;

public: virtual ~Node() {}
};

}