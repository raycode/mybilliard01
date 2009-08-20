#pragma once
namespace my_render {


MY_INTERFACE CameraCommon {
    virtual ~CameraCommon() {}

    virtual float	getZNear() PURE;
    virtual float	getZFar() PURE;
    virtual float	getAspect() PURE;

    virtual void 	setZNear(float nearf) PURE;
    virtual void	setZFar(float farf) PURE;
    virtual void	setAspect(float aspect) PURE;

    virtual void getProjectionMatrix44( float * returnMatrix44, bool bRightHand, bool bRowMajor ) PURE;

};


}