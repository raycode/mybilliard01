#pragma once
namespace my_render {


MY_INTERFACE Camera : EXTENDS_INTERFACE( Base ) {

    virtual bool isPerspective() PURE;
    virtual bool isOrthographic() PURE;

    virtual CameraPerspective * getPerspectiveCamera() PURE;
    virtual CameraOrthographic * getOrthographicCamera() PURE;

    virtual void getProjectionMatrix44( float * returnMatrix44, bool bRightHand, bool bRowMajor ) PURE;

};


}
