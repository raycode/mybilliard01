#pragma once
namespace my_render {


MY_INTERFACE CameraOrthographic : EXTENDS_INTERFACE( CameraCommon ) {

    virtual float	getXMag() PURE;
    virtual float	getYMag() PURE;

    virtual void	setXMag(float magx) PURE;
    virtual void 	setYMag(float magy) PURE;

};


}