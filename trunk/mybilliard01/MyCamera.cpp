#include "stdafx.h"
#include "my_app.h"


MyCamera::MyCamera( Camera * cameraCollada, MyPhysX * phys, BilliardControl * billiardControl,
                   NxVec3 initPosition, NxVec3 direction, bool bRightHand )
: colladaCamera_( cameraCollada )
, bRightHand_( bRightHand )
, bConstrainMovementToHeight_( false )
, state_( this, billiardControl )
{
    controller_ = phys->addCapsuleCharacter( initPosition, 1.f, 3.f, 0.02f, NX_Z, &collisionReport_ );

    direction.normalize();
    NxVec3 up = NxVec3( 0.f, 0.f, 1.f );
    NxVec3 right = ( bRightHand ? up.cross( direction ) : direction.cross( up ) );
    rotate_ = NxMat33( right, up, direction );

    movingSpeed_ = 5.f;
}

void MyCamera::update( float elapsedTime )
{
    if( state_.isAimView() )
    {
        //if( state_.isBallMoving() )
        {
            updateAimPosition();
            updateAimRotate( elapsedTime );
        }

        updateAimLookAt();

    } else if( state_.isMoveView() )
    {
        updateMoveViewMove( elapsedTime );
        updateMoveViewRotate( elapsedTime );
    }
    else if( state_.isTopView() )
    {}
    
}

void MyCamera::updateAimPosition() {
    NxVec3 dir = getDirectionVector();
    dir.z = -0.3f;
    const NxVec3 aimPoint = state_.getAimPoint();
    const NxVec3 newPos = aimPoint - dir * getAimDistance();
    setPosition( NxExtendedVec3( (Extended) newPos.x, (Extended) newPos.y, (Extended) newPos.z ) );
}

void MyCamera::updateAimRotate( float elapsedTime )
{
    const bool bCCW = state_.isAimLeft();
    const bool bCW = state_.isAimRight();
    if( false == bCCW && false == bCW ) return;

    const NxVec3 aimPoint = state_.getAimPoint();
    const float angle = (bCCW ? -1.f : 1.f) * elapsedTime * getAimRotateSensitivity();
    moveClockWiseAroundPoint( angle, aimPoint );
}

void MyCamera::updateAimLookAt()
{
    const NxExtendedVec3 cameraPosExt = getPosition();
    const NxVec3 cameraPos( (NxReal) cameraPosExt.x, (NxReal) cameraPosExt.y, (NxReal) cameraPosExt.z );
    const NxVec3 aimPoint = state_.getAimPoint();
    NxVec3 lookAtPoint = aimPoint;
    lookAtPoint.z += (cameraPos - aimPoint).magnitude() * 0.05f;
    lookAt( lookAtPoint );
}

void MyCamera::updateMoveViewMove( float elapsedTime )
{
    NxVec3 dir( 0.f, 0.f, 0.f );

    const bool bLeft = (state_.isMoveLeft()
        || state_.isMoveForwardLeft()
        || state_.isMoveBackwardLeft());
    const bool bRight = (state_.isMoveRight()
        || state_.isMoveForwardRight()
        || state_.isMoveBackwardRight() );
    const bool bForward = ( state_.isMoveForward()
        || state_.isMoveForwardLeft()
        || state_.isMoveForwardRight() );
    const bool bBackward = ( state_.isMoveBackward()
        || state_.isMoveBackwardLeft()
        || state_.isMoveBackwardRight() );

    if( bLeft ) dir.add( dir, -getRightVector() );
    if( bRight ) dir.add( dir, getRightVector() );
    if( bForward ) dir.add( dir, getDirectionVector() );
    if( bBackward ) dir.add( dir, -getDirectionVector() );

    move( dir, elapsedTime * getMoveSensitivity() );
}

void MyCamera::updateMoveViewRotate( float elapsedTime )
{
    const bool bCW = (state_.isRotateClockWiseByZ()
        || state_.isRotateClockWiseByZ_PitchDown()
        || state_.isRotateClockWiseByZ_PitchUp() );
    const bool bCCW = (state_.isRotateCounterClockWiseByZ()
        || state_.isRotateCounterClockWiseByZ_PitchDown()
        || state_.isRotateCounterClockWiseByZ_PitchUp());
    const bool bPitchUp = ( state_.isPitchUp()
        || state_.isRotateClockWiseByZ_PitchUp()
        || state_.isRotateCounterClockWiseByZ_PitchUp() );
    const bool bPitchDown = ( state_.isPitchDown()
        || state_.isRotateClockWiseByZ_PitchDown()
        || state_.isRotateCounterClockWiseByZ_PitchDown() );

    if( bCW ) rotateClockWiseByZ( elapsedTime * getMoveRotateSensitivity() );
    if( bCCW ) rotateClockWiseByZ( -elapsedTime * getMoveRotateSensitivity() );
    if( bPitchUp ) pitchDown( -elapsedTime * getMovePitchSensitivity() );
    if( bPitchDown ) pitchDown( elapsedTime * getMovePitchSensitivity() );
}

float MyCamera::getAimDistance() {
    return 30.f;
}
float MyCamera::getAimRotateSensitivity() {
    return 2.f;
}
float MyCamera::getMoveSensitivity() {
    return 2.f;
}
float MyCamera::getMoveRotateSensitivity() {
    return 2.f;
}
float MyCamera::getMovePitchSensitivity() {
    return 10.f;
}
MyCameraState * MyCamera::getState()
{
    return & state_;
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

void MyCamera::moveClockWiseAroundPoint( float angle, const NxVec3 & location )
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
}

void MyCamera::lookAt( const NxVec3 & locationOfBall )
{
    const NxExtendedVec3 cameraPosExt = getPosition();
    const NxVec3 cameraPos( NxReal( cameraPosExt.x ), NxReal( cameraPosExt.y ), NxReal( cameraPosExt.z ) );
    NxVec3 dir = locationOfBall - cameraPos;
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
}

NxU32 MyCamera::move( NxVec3 dispVector, NxReal elapsedTime )
{
    NxU32 collisionGroups = 0u;//COLLIDABLE_MASK;

    //	NxF32 sharpness = 0.1f;
    const NxF32 sharpness = 1.0f;
    NxVec3 d = dispVector * elapsedTime * movingSpeed_;
    if( isMovementConstrainedToHeight() ) d.z = 0.f;

    NxU32 collisionFlags;
    controller_->move( d, collisionGroups, 0.01f, collisionFlags, sharpness);
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
void MyCamera::setRotationMatrix( const NxMat33 & rotate ) {
    rotate_ = rotate;
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
void MyCamera::setPosition( NxExtendedVec3 newPosition ) {
    if( isMovementConstrainedToHeight() )
        newPosition.z = getConstrainedHeight();
    controller_->setPosition( newPosition );
}


