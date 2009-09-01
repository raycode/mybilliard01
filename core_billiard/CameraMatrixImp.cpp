#include "StdAfx.h"
#include "my_render_imp.h"
namespace my_render_imp {


CameraMatrixImp::CameraMatrixImp( my_render::Camera * camera, bool bRightHand )
: projectionOnlyCamera_( camera )
, bRightHand_( bRightHand )
{
}

NxVec3 CameraMatrixImp::getPosition() {
    return position_;
}
void CameraMatrixImp::setPosition( const NxVec3 & newPosition ) {
    position_ = newPosition;
}

NxVec3 CameraMatrixImp::getRightVector () {
    return getRotationMatrix().getRow( 0 );
}
NxVec3 CameraMatrixImp::getUpVector () {
    return getRotationMatrix().getRow( 1 );
}
NxVec3 CameraMatrixImp::getDirectionVector () {
    return getRotationMatrix().getRow( 2 );
}

void CameraMatrixImp::setRightVector( const NxVec3 & right ) {
    NxVec3 normalizedRight = right;
    normalizedRight.normalize();
    rotation_.setRow( 0, normalizedRight );
}
void CameraMatrixImp::setUpVector( const NxVec3 & up ) {
    NxVec3 normalizedUp = up;
    normalizedUp.normalize();
    rotation_.setRow( 1, normalizedUp );
}
void CameraMatrixImp::setDirectionVector( const NxVec3 & dir ) {
    NxVec3 normalizedDirection = dir;
    normalizedDirection.normalize();
    rotation_.setRow( 2, normalizedDirection );
}

NxMat33 CameraMatrixImp::getRotationMatrix() {
    return rotation_;
}
void CameraMatrixImp::setRotationMatrix( const NxMat33 & rotation ) {
    rotation_ = rotation;
}

RowMajorMatrix44f CameraMatrixImp::getProjectionMatrix() {
    RowMajorMatrix44f matProjection;
    projectionOnlyCamera_->getProjectionMatrix44( matProjection, isRightHandSystem(), true );
    return matProjection;
}

RowMajorMatrix44f CameraMatrixImp::getViewMatrix() {
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

    RowMajorMatrix44f matView;
    for( size_t i = 0; i < 3 ; ++i )
    {
        matView[ 0 ][ i ] = right.get()[ i ];
        matView[ 1 ][ i ] = up.get()[ i ];
        matView[ 2 ][ i ] = dir.get()[ i ];
        matView[ i ][ 3 ] = trans.get()[ i ];
    }
    return matView;
}
RowMajorMatrix44f CameraMatrixImp::getProjectionViewMatrix() {
    return getProjectionMatrix() * getViewMatrix();
}

void CameraMatrixImp::rotateClockWiseByZ( float angle ) {
    NxMat33 rotateZ;
    rotateZ.rotZ( angle );

    NxMat33 newRotation;
    newRotation.multiply( getRotationMatrix(), rotateZ );
    setRotationMatrix( newRotation );
}
void CameraMatrixImp::pitchDown( float angle ) {
    NxQuat q;
    q.fromAngleAxis( angle, getRightVector() );
 
    NxMat33 rotateByRight;
    rotateByRight.fromQuat( q );

    NxMat33 newRotation;
    newRotation.multiply( getRotationMatrix(), rotateByRight );
    setRotationMatrix( newRotation );
}
void CameraMatrixImp::rotateCounterClockWiseByZ( float angle ) {
    return rotateClockWiseByZ( -angle );
}
void CameraMatrixImp::pitchUp( float angle ) {
    return pitchDown( -angle );
}

void CameraMatrixImp::lookAt( const NxVec3 & whereToLookAt, const NxVec3 & requestedUp ) {
    NxVec3 newDir = whereToLookAt - getPosition();
    newDir.normalize();
    setDirectionVector( newDir );

    NxVec3 newRight = getDirectionVector().cross( requestedUp );
    newRight.normalize();
    setRightVector( newRight );

    NxVec3 newUp = getRightVector().cross( getDirectionVector() );
    newUp.normalize();
    setUpVector( newUp );
}

bool CameraMatrixImp::isRightHandSystem() {
    return bRightHand_;
}

}
