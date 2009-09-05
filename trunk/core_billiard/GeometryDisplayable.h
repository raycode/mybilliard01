#pragma once
namespace my_render {


MY_INTERFACE GeometryDisplayable {
    virtual ~GeometryDisplayable() {}

    virtual void display() PURE;
    virtual void display_positionOnly() PURE;

};

}