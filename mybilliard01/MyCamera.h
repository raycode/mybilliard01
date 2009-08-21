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

    NxU32 move( NxReal x, NxReal y, NxReal z, NxReal elapsedTime );

private:
    Camera * colladaCamera_;
    MyPhysX * phys_;
    bool bRightHand_;

    NxController * controller_;
    NxMat33 rotate_;
};