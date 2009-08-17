#pragma once
namespace my_render {


MY_INTERFACE Camera : EXTENDS_INTERFACE( Base ) {

    virtual void setViewMatrix( const NxMat34 & ) = 0;
    virtual const NxMat34 & getViewMatrix() = 0;

};


}
