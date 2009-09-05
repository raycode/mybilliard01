#pragma once


class MyCamera : public CameraMatrixEffect
{
public: // from CameraMatrix
    virtual NxVec3 getPosition() OVERRIDE;
    virtual void setPosition( const NxVec3 & newPosition ) OVERRIDE;

public:
    MyCamera( Camera * colladaCamera, bool bRightHand, MyPhysX * phys, BilliardControl * billiardControl, NxVec3 initPosition, NxVec3 direction );

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

private: // camera position , rotate
    NxController * controller_;
    MyControllerHitReport collisionReport_;

private: // move
    float movingSpeed_;
    bool bConstrainMovementToHeight_;
    float height_;

private: // camera state
    MyCameraState state_;
};

