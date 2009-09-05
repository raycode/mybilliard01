#pragma once
namespace my_render {


MY_INTERFACE Displayable {
    virtual ~Displayable() {}

    virtual void display() PURE;
    virtual void display_positionOnly() PURE;

};

}