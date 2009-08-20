#pragma once

class MyCamera {
public:
    MyCamera( Camera *, NxActor * );

    void getViewMatrix44( float * returnMatrix44, bool bRightHand, bool bRowMajor );

    Camera * cameraCollada_;
    NxActor * cameraPhysX_;
};