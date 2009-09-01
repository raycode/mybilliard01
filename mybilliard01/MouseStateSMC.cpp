#include "StdAfx.h"
#include "my_app.h"
namespace smc {


MouseStateSMC::MouseStateSMC()
: myCamera_( NULL )
, billiardControl_( NULL )
{
}

void MouseStateSMC::FSMError( const char * msg1, const char * msg2 ) {
    OutputDebugStr( (convertString( msg1 ) + L" is called at " + convertString( msg2 ) + L"\n").c_str() );
}

void MouseStateSMC::setRotationSensitivity( float sensitivity )
{
    rotationSensitivity_ = sensitivity;
}

float MouseStateSMC::getRotationSensitivity()
{
    return rotationSensitivity_;
}

void MouseStateSMC::setPitchSensitivity( float sensitivity )
{
    pitchSensitivity_ = sensitivity;
}

float MouseStateSMC::getPitchSensitivity()
{
    return pitchSensitivity_;
}

void MouseStateSMC::setCamera( MyCamera * camera ) {
    myCamera_ = camera;
}

void MouseStateSMC::setBilliardControl( BilliardControl * billiardControl )
{
    billiardControl_ = billiardControl;
}

MyCamera * MouseStateSMC::getCamera() {
    return myCamera_;
}
MyCameraState * MouseStateSMC::getCameraState() {
    return getCamera()->getState();
}

void MouseStateSMC::buttonDown( HWND hWnd, int iMouseX, int iMouseY )
{
    previousX_ = iMouseX;
    previousY_ = iMouseY;
    SetCapture( hWnd );

    buttonDown();
}

void MouseStateSMC::move( int iMouseX, int iMouseY )
{
    moveDiffX_ = iMouseX - previousX_;
    moveDiffY_ = iMouseY - previousY_;
    previousX_ = iMouseX;
    previousY_ = iMouseY;

    move();
}

void MouseStateSMC::buttonUp_()
{
    ReleaseCapture();
}

void MouseStateSMC::click_()
{
}

void MouseStateSMC::onDrag_()
{
    if( getCameraState()->isMoveView() ) {
        getCamera()->rotateClockWiseByZ( moveDiffX_ * getRotationSensitivity() );
        getCamera()->pitchDown( moveDiffY_ * getPitchSensitivity() );
    }

    else if( getCameraState()->isAimView() )
    {
        const NxVec3 cueBallPos = billiardControl_->getCueBallPosition();
        getCamera()->moveClockWiseAroundPoint( moveDiffX_ * getRotationSensitivity(), cueBallPos );
        getCamera()->lookAt( cueBallPos, NxVec3( 0.f, 0.f, 1.f ) );
    }
}

void MouseStateSMC::beginDrag_()
{    
}
void MouseStateSMC::endDrag_()
{
}


void MouseStateSMC::captureReleased_()
{
    ReleaseCapture();
}


}