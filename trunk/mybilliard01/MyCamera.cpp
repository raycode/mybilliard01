#include "stdafx.h"
#include "my_app.h"


MyCamera::MyCamera( Camera * cameraCollada, MyPhysX * phys,
                   NxVec3 initPosition, NxVec3 direction, bool bRightHand )
: colladaCamera_( cameraCollada )
, phys_( phys )
, bRightHand_( bRightHand )
{
    controller_ = phys_->addCapsuleCharacter( initPosition, 0.1f, 0.2f, 0.001f, NX_Z );

    NxVec3 up = NxVec3( 0.f, 0.f, 1.f );
    NxVec3 right = ( bRightHand ? up.cross( direction ) : direction.cross( up ) );
    rotate_ = NxMat33( right, up, direction );
}

NxU32 MyCamera::move( NxReal x, NxReal y, NxReal z, NxReal elapsedTime )
{
    NxU32 collisionGroups = 0u;//COLLIDABLE_MASK;
    NxVec3 dispVector( x, y, z );

    //	NxF32 sharpness = 0.1f;
    NxF32 sharpness = 1.0f;

    const NxVec3 d = dispVector * elapsedTime;

    NxU32 collisionFlags;
    controller_->move( d, collisionGroups, 0.000001f, collisionFlags, sharpness);
    return collisionFlags;
}

void MyCamera::getViewMatrix44( float * returnMatrix44, bool bRowMajor )
{
    NxVec3 dir = getDirectionVector();
    dir.normalize();

    NxVec3 up = getRightVector().cross( dir );
    up.normalize();

    NxVec3 right = dir.cross( up );
    right.normalize();

    NxVec3 trans;
    trans.x = (NxReal) - getPosition().dot( right );
    trans.y = (NxReal) - getPosition().dot( up );
    trans.z = (NxReal) - getPosition().dot( dir );

    NxMat34 rowMajorView;
    rowMajorView.M.setRow( 0, right );
    rowMajorView.M.setRow( 1, up );
    rowMajorView.M.setRow( 2, dir );
    rowMajorView.t = trans;

    if( bRowMajor ) {
        rowMajorView.getRowMajor44( returnMatrix44 );

    } else {
        rowMajorView.getColumnMajor44( returnMatrix44 );
    }
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


