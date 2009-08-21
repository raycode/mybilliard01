#include "stdafx.h"
#include "my_app.h"

MyCamera::MyCamera( Camera * cameraCollada, MyPhysX * phys, NxVec3 initPosition )
: colladaCamera_( cameraCollada )
, phys_( phys )
{
    controller_ = phys_->addCapsuleCharacter( -initPosition, 0.1f, 0.2f, 0.001f, NX_Z );

    rotate_ = NxMat33( NxVec3( 0.f, 1.f, 0.f ), NxVec3( 0.f, 0.f, 1.f ), NxVec3( 1.f, 0.f, 0.f ) );
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


NxVec3 MyCamera::getRightVector () const {
    return rotate_.getRow( 0 );
}
NxVec3 MyCamera::getUpVector () const {
    return rotate_.getRow( 1 );
}
NxVec3 MyCamera::getDirectionVector () const {
    return rotate_.getRow( 2 );
}

void MyCamera::getViewMatrix44( float * returnMatrix44, bool bRightHand, bool bRowMajor )
{
    NxVec3 dir = getDirectionVector();
    dir.normalize();

    NxVec3 up = dir.cross( getRightVector() );
    up.normalize();

    NxVec3 right = up.cross( dir );
    right.normalize();

    NxVec3 trans;
    trans.x = (NxReal) - getPosition().dot( right );
    trans.y = (NxReal) - getPosition().dot( up );
    trans.z = (NxReal) - getPosition().dot( dir );

    NxMat34 view;
    view.M.setRow( 0, right );
    view.M.setRow( 1, up );
    view.M.setRow( 2, dir );
    view.t = trans;

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


