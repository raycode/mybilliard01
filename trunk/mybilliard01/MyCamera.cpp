#include "stdafx.h"
#include "my_app.h"


MyCamera::MyCamera( Camera * cameraCollada, MyPhysX * phys,
                   NxVec3 initPosition, NxVec3 direction, bool bRightHand )
: colladaCamera_( cameraCollada )
, phys_( phys )
, bRightHand_( bRightHand )
, bConstrainMovementToHeight_( false )
{
    controller_ = phys_->addCapsuleCharacter( initPosition, 0.1f, 0.2f, 0.001f, NX_Z );

    direction.normalize();
    NxVec3 up = NxVec3( 0.f, 0.f, 1.f );
    NxVec3 right = ( bRightHand ? up.cross( direction ) : direction.cross( up ) );
    rotate_ = NxMat33( right, up, direction );

    for( size_t i = 0; i < SIZE_OF_MOVE_DIRECTION; ++i )
        moveTo_[ i ] = false;
    for( size_t i = 0; i < SIZE_OF_ROTATE_AXIS; ++i )
        rotateTo_[ i ] = false;

    movingSpeed_ = 5.f;
}

void MyCamera::update( float elapsedTime )
{
    NxVec3 dir( 0.f, 0.f, 0.f );
    if( moveTo_[ EMOVE_FORWARD ] ) dir.add( dir, getDirectionVector() );
    if( moveTo_[ EMOVE_LEFT ] ) dir.add( dir, -getRightVector() );
    if( moveTo_[ EMOVE_RIGHT ] ) dir.add( dir, getRightVector() );
    if( moveTo_[ EMOVE_BACKWARD ] ) dir.add( dir, -getDirectionVector() );
    move( dir, elapsedTime );

    if( rotateTo_[ EROTATE_Z_CW ] ) rotateClockWiseByZ( 2.f * elapsedTime );
    if( rotateTo_[ EROTATE_Z_CCW ] ) rotateClockWiseByZ( -2.f * elapsedTime );
    if( rotateTo_[ EROTATE_PITCH_UP ] ) pitchDown( -10.f * elapsedTime );
    if( rotateTo_[ EROTATE_PITCH_DOWN ] ) pitchDown( 10.f * elapsedTime );

    phys_->UpdateControllers();
}

void MyCamera::rotateClockWiseByZ( float angle )
{
    NxMat33 rotateZ;
    rotateZ.rotZ( angle );
    rotate_.multiply( rotate_, rotateZ );
}
void MyCamera::pitchDown( float angle )
{
    NxVec3 right = getRightVector();
    NxQuat q;
    q.fromAngleAxis( angle, right );
    NxMat33 rotateByRight;
    rotateByRight.fromQuat( q );
    rotate_.multiply( rotate_, rotateByRight );
}

void MyCamera::rotateClockWiseByZ( float angle, const NxVec3 & location )
{
    NxMat34 transNegObj;
    transNegObj.M.id();
    transNegObj.t = - location;

    NxMat34 rotateZ;
    rotateZ.M.rotZ( angle );
    rotateZ.t.zero();

    NxMat34 matObj;
    matObj.multiply( rotateZ, transNegObj );

    const NxExtendedVec3 cameraPosExt = getPosition();
    const NxVec3 cameraPos( NxReal( cameraPosExt.x ), NxReal( cameraPosExt.y ), NxReal( cameraPosExt.z ) );

    NxVec3 newCameraPos;
    matObj.multiply( cameraPos, newCameraPos );
    newCameraPos += location;

    const NxExtendedVec3 newCameraPosExt( (Extended) newCameraPos.x, (Extended) newCameraPos.y, (Extended) newCameraPos.z );
    setPosition( newCameraPosExt );

    NxVec3 dir = location - newCameraPos;
    dir.normalize();
    rotate_.setRow( 2, dir );

    NxVec3 up( 0.f, 0.f, 1.f );

    NxVec3 right;
    right = dir.cross( up );
    right.normalize();
    rotate_.setRow( 0, right );

    up = right.cross( up );
    up.normalize();
    rotate_.setRow( 1, up );

    //const NxVec3 diff = location - cameraPos;
    //NxMat34 trans2;
    //trans2.M.id();
    //trans2.t = diff;

    //float tmp[ 16 ];
    //getViewMatrix44( tmp, true );
    //NxMat34 viewMat, viewMatInv;
    //viewMat.getRowMajor44( tmp );
    //viewMat.getInverse( viewMatInv );

    //NxMat34 rst;
    //rst.multiply( rotateZ, trans2 );
    //rst.multiply( rotateView, rst );
    //rst.multiply( trans2, rst );
    //rst.multiply( viewMatInv, rst );
    //rotate_ = rst.M; // rotation is done

    //NxMat34 rotOnly;
    //rotOnly.M = rst.M;
    //rotOnly.t.zero();
    //NxMat34 rotInv;
    //rotOnly.getInverse( rotInv );

    //rst.multiply( rotInv, rst );
    //const NxExtendedVec3 newCameraPos3( (Extended) rst.t.x, (Extended) rst.t.y, (Extended) rst.t.z );
}

void MyCamera::pitchDown( float angle, const NxVec3 & location )
{
    //NxVec3 right = getRightVector();
    //NxQuat q;
    //q.fromAngleAxis( angle, right );
    //NxMat33 rotateByRight;
    //rotateByRight.fromQuat( q );
    //rotate_.multiply( rotate_, rotateByRight );
}

NxU32 MyCamera::move( NxVec3 dispVector, NxReal elapsedTime )
{
    NxU32 collisionGroups = 0u;//COLLIDABLE_MASK;

    //	NxF32 sharpness = 0.1f;
    const NxF32 sharpness = 1.0f;
    NxVec3 d = dispVector * elapsedTime * movingSpeed_;
    if( isMovementConstrainedToHeight() ) d.z = 0.f;

    NxU32 collisionFlags;
    controller_->move( d, collisionGroups, 0.000001f, collisionFlags, sharpness);
    return collisionFlags;
}

void MyCamera::setMovingSpeed( float movingSpeed ) {
    movingSpeed_ = movingSpeed;
}
float MyCamera::getMovingSpeed() {
    return movingSpeed_;
}
bool MyCamera::isMovementConstrainedToHeight() {
    return bConstrainMovementToHeight_;
}
void MyCamera::setMovementToFixedHeight( float height ) {
    bConstrainMovementToHeight_ = true;
    height_ = height;
    NxExtendedVec3 newPos = getPosition();
    newPos.z = height;
    controller_->setPosition( newPos );
}
void MyCamera::setMovementFreeFromHeightContrain() {
    bConstrainMovementToHeight_ = false;
}
float MyCamera::getConstrainedHeight() {
    return height_;
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

const NxExtendedVec3 & MyCamera::getPosition() {
    return controller_->getFilteredPosition();
}
void MyCamera::setPosition( const NxExtendedVec3 & newPosition ) {
    controller_->setPosition( newPosition );
}

void MyCamera::beginMoveForward() {
    moveTo_[ EMOVE_FORWARD ] = true;
}
void MyCamera::beginMoveLeft() {
    moveTo_[ EMOVE_LEFT ] = true;
}
void MyCamera::beginMoveRight() {
    moveTo_[ EMOVE_RIGHT ] = true;
}
void MyCamera::beginMoveBackward() {
    moveTo_[ EMOVE_BACKWARD ] = true;
}
void MyCamera::endMoveForward() {
    moveTo_[ EMOVE_FORWARD ] = false;
}
void MyCamera::endMoveLeft() {
    moveTo_[ EMOVE_LEFT ] = false;
}
void MyCamera::endMoveRight() {
    moveTo_[ EMOVE_RIGHT ] = false;
}
void MyCamera::endMoveBackward() {
    moveTo_[ EMOVE_BACKWARD ] = false;
}

void MyCamera::beginRotateClockWiseByZ() {
    rotateTo_[ EROTATE_Z_CW ] = true;
}
void MyCamera::beginRotateCounterClockWiseByZ() {
    rotateTo_[ EROTATE_Z_CCW ] = true;
}
void MyCamera::endRotateClockWiseByZ() {
    rotateTo_[ EROTATE_Z_CW ] = false;
}
void MyCamera::endRotateCounterClockWiseByZ() {
    rotateTo_[ EROTATE_Z_CCW ] = false;
}

void MyCamera::beginPitchDown() {
    rotateTo_[ EROTATE_PITCH_DOWN ] = true;
}
void MyCamera::beginPitchUp() {
    rotateTo_[ EROTATE_PITCH_UP ] = true;
}
void MyCamera::endPitchDown() {
    rotateTo_[ EROTATE_PITCH_DOWN ] = false;
}
void MyCamera::endPitchUp() {
    rotateTo_[ EROTATE_PITCH_UP ] = false;
}

