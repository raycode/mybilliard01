#pragma once
namespace my_render {


MY_INTERFACE Camera : EXTENDS_INTERFACE( Base ) {

    virtual void setViewMatrix( const NxMat34 & ) PURE;
    virtual const NxMat34 & getViewMatrix() PURE;

};


}
