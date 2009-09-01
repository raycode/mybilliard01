#pragma once

class MyCamera {
public:
    MyCamera( Camera * colladaCamera, MyPhysX * phys, BilliardControl * billiardControl, NxVec3 initPosition, NxVec3 direction, bool bRightHand );

    void setAspect( float aspectRatio );
    RowMajorMatrix44f getProjectionMatrix();
    RowMajorMatrix44f getViewMatrix();

    const NxVec3 & getPosition();
    void setPosition( NxVec3 newPosition );

    NxVec3 getRightVector () const;
    NxVec3 getUpVector () const;
    NxVec3 getDirectionVector () const;
    void setRotationMatrix( const NxMat33 & );

    void update( float elapsedTime );

    MyCameraState * getState();

public: // move
    void setMovingSpeed( float movingSpeed );
    float getMovingSpeed();

    bool isMovementConstrainedToHeight();
    void setMovementToFixedHeight( float height );
    void setMovementFreeFromHeightContrain();
    float getConstrainedHeight();

public: // rotate
    void rotateClockWiseByZ( float angle );
    void pitchDown( float angle );

public: // looking at ball
    void lookAt( const NxVec3 & locationOfBall, NxVec3 up );
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

