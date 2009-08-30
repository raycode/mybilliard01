#include "StdAfx.h"
#include "my_app.h"
namespace smc {


MyCameraModeSMC::MyCameraModeSMC()
    : bNeedToBeRestored_( false )
{
}

void MyCameraModeSMC::FSMError( const char * msg1, const char * msg2 ) {
    OutputDebugStr( (convertString( msg1 ) + L" is called at " + convertString( msg2 ) + L"\n").c_str() );
}

void MyCameraModeSMC::setBilliardControl( BilliardControl * billiardControl ) {
    billiardControl_ = billiardControl;
}

MyCamera * MyCameraModeSMC::getCamera() {
    return billiardControl_->getActiveCamera();
}

void MyCameraModeSMC::changeToTopView_()
{
    position_ = getCamera()->getPosition();
    rotate_.setRow( 0, getCamera()->getRightVector() );
    rotate_.setRow( 1, getCamera()->getUpVector() );
    rotate_.setRow( 2, getCamera()->getDirectionVector() );
    bNeedToBeRestored_ = true;

    getCamera()->setMovementFreeFromHeightContrain();
    getCamera()->setPosition( NxExtendedVec3( -13., -10., 140. ) );
    getCamera()->lookAt( NxVec3( -13.f, 0.f, 30.f ) );
}
void MyCameraModeSMC::changeToAimView_()
{
    if( bNeedToBeRestored_ ) restoreCameraPosition();
    getCamera()->setMovementToFixedHeight( 35.f );
    getCamera()->lookAt( billiardControl_->getCueBallPosition() );
}
void MyCameraModeSMC::changeToMoveView_()
{
    if( bNeedToBeRestored_ ) restoreCameraPosition();
    getCamera()->setMovementToFixedHeight( 45.f );
    getCamera()->lookAt( NxVec3( -13.f, 0.f, 30.f ) );
}
void MyCameraModeSMC::quit_()
{
}

void MyCameraModeSMC::restoreCameraPosition() {
    getCamera()->setPosition( position_ );
    getCamera()->setRotationMatrix( rotate_ );
}


}