#pragma once
namespace my_render {


MY_INTERFACE CameraPerspective : EXTENDS_INTERFACE( CameraCommon ) {

    virtual float	getXFov() PURE;
    virtual float	getYFov() PURE;

    virtual void	setXFov(float fovx) PURE;
    virtual void 	setYFov(float fovf) PURE;

};


}