#include "stdafx.h"
#include "my_app.h"

MyCamera::MyCamera( Camera * cameraCollada, MyPhysX * phys, NxVec3 initPosition )
: colladaCamera_( cameraCollada )
, phys_( phys )
{
    controller_ = phys_->addCapsuleCharacter( -initPosition, 0.1f, 0.2f, 0.001f, NX_Z );

    rotate_ = NxMat33( NxVec3( 1.f, 0.f, 0.f ), NxVec3( 0.f, 1.f, 0.f ), NxVec3( 0.f, 0.f, 1.f ) );
}

void MyCamera::setAspect( float aspectRatio )
{
    colladaCamera_->getPerspectiveCamera()->setAspect( aspectRatio );
}

void MyCamera::getProjectionMatrix44( float * returnMatrix44, bool bRightHand, bool bRowMajor ) {
    colladaCamera_->getProjectionMatrix44( returnMatrix44, bRightHand, bRowMajor );
}

const NxExtendedVec3 & MyCamera::getPosition()
{
    return controller_->getFilteredPosition();
}


void MyCamera::getViewMatrix44( float * returnMatrix44, bool bRightHand, bool bRowMajor )
{
    NxMat34 view;
    view.M = rotate_;
    view.t.x = (NxReal) getPosition().x;
    view.t.y = (NxReal) getPosition().y;
    view.t.z = (NxReal) getPosition().z;

    if( bRowMajor ) {
        view.getRowMajor44( returnMatrix44 );

    } else {
        view.getColumnMajor44( returnMatrix44 );
    }

}

NxU32 MyCamera::move( NxReal x, NxReal y, NxReal z, NxReal elapsedTime )
{
    NxU32 collisionGroups = 0u;//COLLIDABLE_MASK;
    NxVec3 dispVector( x, y, z );

    //	NxF32 sharpness = 0.1f;
    NxF32 sharpness = 1.0f;

    const NxVec3 d = dispVector * elapsedTime;

    NxU32 collisionFlags;
    controller_->move( -d, collisionGroups, 0.000001f, collisionFlags, sharpness);
    return collisionFlags;
}

void MyCamera::rotateX( NxReal angle ) {

}

void MyCamera::rotateY( NxReal angle ) {

}

void MyCamera::rotateZ( NxReal angle ) {

}


