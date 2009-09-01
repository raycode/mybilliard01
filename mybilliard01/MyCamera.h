#pragma once

class MyCamera : public CameraMatrix {
public: // from CameraMatrix
    virtual NxVec3 getPosition() OVERRIDE;
    virtual void setPosition( const NxVec3 & newPosition ) OVERRIDE;

    virtual NxVec3 getRightVector () OVERRIDE;
    virtual NxVec3 getUpVector () OVERRIDE;
    virtual NxVec3 getDirectionVector () OVERRIDE;

    virtual void setRotationMatrix( const NxMat33 & ) OVERRIDE;

    virtual RowMajorMatrix44f getProjectionMatrix() OVERRIDE;
    virtual RowMajorMatrix44f getViewMatrix() OVERRIDE;

    virtual void rotateClockWiseByZ( float angle ) OVERRIDE;

    virtual void pitchDown( float angle ) OVERRIDE;

    virtual void lookAt( const NxVec3 & whereToLookAt, const NxVec3 & requestedUp ) OVERRIDE;

public:
    MyCamera( Camera * colladaCamera, MyPhysX * phys, BilliardControl * billiardControl, NxVec3 initPosition, NxVec3 direction, bool bRightHand );

    void setAspect( float aspectRatio );

    void update( float elapsedTime );

    MyCameraState * getState();

public: // move
    void setMovingSpeed( float movingSpeed );
    float getMovingSpeed();

    bool isMovementConstrainedToHeight();
    void setMovementToFixedHeight( float height );
    void setMovementFreeFromHeightContrain();
    float getConstrainedHeight();

public: // looking at ball
    void moveClockWiseAroundPoint( float angle, const NxVec3 & location );

private: // update
    void updateAimPosition();
    void updateAimRotate( float elapsedTime );
    void updateAimLookAt();
    void updateMoveViewMove( float elapsedTime );
    void updateMoveViewRotate( float elapsedTime );

    NxU32 move( NxVec3 dispVector, NxReal elapsedTime );

private: // parameters
    float getAimDistance();
    float getAimRotateSensitivity();
    float getMoveSensitivity();
    float getMoveRotateSensitivity();
    float getMovePitchSensitivity();

private:
    Camera * colladaCamera_;
    bool bRightHand_;

private: // camera position , rotate
    NxController * controller_;
    MyControllerHitReport collisionReport_;

    NxMat33 rotate_;

private: // move
    float movingSpeed_;
    bool bConstrainMovementToHeight_;
    float height_;

private: // camera state
    MyCameraState state_;

    NxVec3 pos_;
};

