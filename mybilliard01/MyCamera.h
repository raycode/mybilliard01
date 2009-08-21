#pragma once

class MyCamera {
public:
    MyCamera( Camera * colladaCamera, MyPhysX * phys, NxVec3 initPosition, NxVec3 direction, bool bRightHand );

    void setAspect( float aspectRatio );
    void getProjectionMatrix44( float * returnMatrix44, bool bRightHand, bool bRowMajor );
    void getViewMatrix44( float * returnMatrix44, bool bRowMajor );

    const NxExtendedVec3 & getPosition();
    NxVec3 getRightVector () const;
    NxVec3 getUpVector () const;
    NxVec3 getDirectionVector () const;

    void update( float elapsedTime );

    NxU32 move( NxVec3 dispVector, NxReal elapsedTime );

    void setMovingSpeed( float movingSpeed );
    float getMovingSpeed();

    bool isMovementConstrainedToHeight();
    void setMovementToFixedHeight( float height );
    void setMovementFreeFromHeightContrain();
    float getConstrainedHeight();

    void beginMoveForward();
    void beginMoveLeft();
    void beginMoveRight();
    void beginMoveBackward();
    void endMoveForward();
    void endMoveLeft();
    void endMoveRight();
    void endMoveBackward();

    void rotateClockWiseByZ( float angle );
    void pitchDown( float angle );

    void beginRotateClockWiseByZ();
    void beginRotateCounterClockWiseByZ();
    void endRotateClockWiseByZ();
    void endRotateCounterClockWiseByZ();

    void beginPitchDown();
    void beginPitchUp();
    void endPitchDown();
    void endPitchUp();

private:
    Camera * colladaCamera_;
    MyPhysX * phys_;
    bool bRightHand_;

    NxController * controller_;
    NxMat33 rotate_;

    enum { EMOVE_FORWARD, EMOVE_LEFT, EMOVE_RIGHT, EMOVE_BACKWARD, SIZE_OF_MOVE_DIRECTION };
    bool moveTo_[ SIZE_OF_MOVE_DIRECTION ];

    float movingSpeed_;
    bool bConstrainMovementToHeight_;
    float height_;

    enum { EROTATE_Z_CW, EROTATE_Z_CCW, EROTATE_PITCH_UP, EROTATE_PITCH_DOWN, SIZE_OF_ROTATE_AXIS };
    bool rotateTo_[ SIZE_OF_ROTATE_AXIS ];
};

