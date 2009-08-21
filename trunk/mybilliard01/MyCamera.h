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
    void beginMoveForward();
    void beginMoveLeft();
    void beginMoveRight();
    void beginMoveBackward();
    void endMoveForward();
    void endMoveLeft();
    void endMoveRight();
    void endMoveBackward();

    void yawFromLeftToRight( float angle );
    void pitchFromDownToUp( float angle );

private:
    Camera * colladaCamera_;
    MyPhysX * phys_;
    bool bRightHand_;

    NxController * controller_;
    NxMat33 rotate_;

    enum { EMOVE_FORWARD, EMOVE_LEFT, EMOVE_RIGHT, EMOVE_BACKWARD, SIZE_OF_MOVE_DIRECTION };
    bool moveTo_[ SIZE_OF_MOVE_DIRECTION ];
};