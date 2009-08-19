#pragma once
namespace my_render {


MY_INTERFACE CameraFactory {
    virtual ~CameraFactory() {}

    virtual Camera * createCamera( domCameraRef ) PURE;
    virtual Camera * find( wstring id ) PURE;
    virtual bool destroyCamera( Camera * ) PURE;

};


}
