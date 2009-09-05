#include "stdafx.h"
#include "my_app.h"


MyCamera::MyCamera( Camera * cameraCollada, bool bRightHand,
                   MyPhysX * phys, BilliardControl * billiardControl, NxVec3 initPosition, NxVec3 direction )
: CameraRenderTarget( cameraCollada, bRightHand )
, bConstrainMovementToHeight_( false )
, state_( this, billiardControl )
{
    controller_ = phys->addCapsuleCharacter( initPosition, 1.f, 3.f, 0.02f, NX_Z, &collisionReport_ );

    direction.normalize();
    setDirectionVector( direction );

    NxVec3 up( 0., 0.f, 1.f );
    setUpVector( up );

    setRightVector( direction.cross( up ) );

    setMovingSpeed( 5.f );
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
    setPosition( newPos );
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
    const NxVec3 aimPoint = state_.getAimPoint();
    NxVec3 lookAtPoint = aimPoint;
    lookAtPoint.z += (getPosition() - aimPoint).magnitude() * 0.05f;
    lookAt( lookAtPoint, NxVec3( 0.f, 0.f, 1.f ) );
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

    NxVec3 newCameraPos;
    matObj.multiply( getPosition(), newCameraPos );
    newCameraPos += location;
    setPosition( newCameraPos );
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
    NxVec3 newPos = getPosition();
    newPos.z = height;
    NxExtendedVec3 newPosExt( (Extended) newPos.x, (Extended) newPos.y, (Extended) newPos.z );
    controller_->setPosition( newPosExt );
}
void MyCamera::setMovementFreeFromHeightContrain() {
    bConstrainMovementToHeight_ = false;
}
float MyCamera::getConstrainedHeight() {
    return height_;
}

NxVec3 MyCamera::getPosition() {
    NxExtendedVec3 posExt = controller_->getFilteredPosition();
    return NxVec3( (NxReal) posExt.x, (NxReal) posExt.y, (NxReal) posExt.z );
}
void MyCamera::setPosition( const NxVec3 & newPos ) {
    NxVec3 newPosition = newPos;
    if( isMovementConstrainedToHeight() )
        newPosition.z = getConstrainedHeight();
    NxExtendedVec3 newPosExt( (NxReal) newPosition.x, (NxReal) newPosition.y, (NxReal) newPosition.z );
    controller_->setPosition( newPosExt );
}


