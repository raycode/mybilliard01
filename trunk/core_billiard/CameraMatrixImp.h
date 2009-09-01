#pragma once
namespace my_render_imp {


class CameraMatrixImp : IMPLEMENTS_INTERFACE( CameraMatrix ) {
public: // from CameraMatrix
    virtual NxVec3 getPosition() OVERRIDE;
    virtual void setPosition( const NxVec3 & newPosition ) OVERRIDE;

    virtual NxVec3 getRightVector () OVERRIDE;
    virtual NxVec3 getUpVector () OVERRIDE;
    virtual NxVec3 getDirectionVector () OVERRIDE;

    virtual void setRightVector( const NxVec3 & ) OVERRIDE;
    virtual void setUpVector( const NxVec3 & ) OVERRIDE;
    virtual void setDirectionVector( const NxVec3 & ) OVERRIDE;

    virtual NxMat33 getRotationMatrix() OVERRIDE;
    virtual void setRotationMatrix( const NxMat33 & ) OVERRIDE;

    virtual RowMajorMatrix44f getProjectionMatrix() OVERRIDE;
    virtual RowMajorMatrix44f getViewMatrix() OVERRIDE;
    virtual RowMajorMatrix44f getProjectionViewMatrix() OVERRIDE;

    virtual void rotateCounterClockWiseByZ( float angle ) OVERRIDE;
    virtual void rotateClockWiseByZ( float angle ) OVERRIDE;

    virtual void pitchUp( float angle ) OVERRIDE;
    virtual void pitchDown( float angle ) OVERRIDE;

    virtual void lookAt( const NxVec3 & whereToLookAt, const NxVec3 & requestedUp ) OVERRIDE;

public:
    CameraMatrixImp( my_render::Camera *, bool bRightHand );

private:
    bool isRightHandSystem();

private:
    my_render::Camera * const projectionOnlyCamera_;
    const bool bRightHand_;

private:
    NxVec3 position_;
    NxMat33 rotation_;
};

}
