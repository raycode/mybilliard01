#pragma once

class MyCamera {
public:
    MyCamera( Camera * colladaCamera, MyPhysX * phys, NxVec3 initPosition );

    void setAspect( float aspectRatio );
    void getProjectionMatrix44( float * returnMatrix44, bool bRightHand, bool bRowMajor );
    void getViewMatrix44( float * returnMatrix44, bool bRightHand, bool bRowMajor );

    const NxExtendedVec3 & getPosition();
    NxU32 move( NxReal x, NxReal y, NxReal z, NxReal elapsedTime );
    void rotateX( NxReal angle );
    void rotateY( NxReal angle );
    void rotateZ( NxReal angle );

private:
    Camera * colladaCamera_;
    MyPhysX * phys_;

    NxController * controller_;
    NxMat33 rotate_;
};