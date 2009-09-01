#pragma once
namespace my_render {


MY_INTERFACE CameraMatrix {
    virtual ~CameraMatrix() {}

    virtual NxVec3 getPosition() PURE;
    virtual void setPosition( const NxVec3 & newPosition ) PURE;

    virtual NxVec3 getRightVector () PURE;
    virtual NxVec3 getUpVector () PURE;
    virtual NxVec3 getDirectionVector () PURE;

    virtual void setRightVector( const NxVec3 & ) PURE;
    virtual void setUpVector( const NxVec3 & ) PURE;
    virtual void setDirectionVector( const NxVec3 & ) PURE;

    virtual NxMat33 getRotationMatrix() PURE;
    virtual void setRotationMatrix( const NxMat33 & ) PURE;

    virtual RowMajorMatrix44f getProjectionMatrix() PURE;
    virtual RowMajorMatrix44f getViewMatrix() PURE;
    virtual RowMajorMatrix44f getProjectionViewMatrix() PURE;

    virtual void rotateCounterClockWiseByZ( float angle ) PURE;
    virtual void rotateClockWiseByZ( float angle ) PURE;

    virtual void pitchUp( float angle ) PURE;
    virtual void pitchDown( float angle ) PURE;

    virtual void lookAt( const NxVec3 & whereToLookAt, const NxVec3 & requestedUp ) PURE;

};

}
