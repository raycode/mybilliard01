#include "StdAfx.h"
#include "my_app.h"
namespace smc {


void MyCameraAimViewSMC::FSMError( const char * msg1, const char * msg2 ) {
    OutputDebugStr( (convertString( msg1 ) + L" is called at " + convertString( msg2 ) + L"\n").c_str() );
}

void MyCameraAimViewSMC::setBilliardControl( BilliardControl * billiardControl )
{
    billiardControl_ = billiardControl;
}

MyCamera * MyCameraAimViewSMC::getCamera() {
    return billiardControl_->getActiveCamera();
}

void MyCameraAimViewSMC::beginAimLeft_() {
}
void MyCameraAimViewSMC::beginAimRight_() {
}
void MyCameraAimViewSMC::endAimLeft_() {
}
void MyCameraAimViewSMC::endAimRight_() {
}
void MyCameraAimViewSMC::beginShoot_() {
    billiardControl_->readyToHitCueBall();
}
void MyCameraAimViewSMC::endShoot_() {
    billiardControl_->hitCueBall();
}

NxVec3 MyCameraAimViewSMC::getAimPoint() {
    return billiardControl_->getCueBallPosition();
}

void MyCameraAimViewSMC::entryAimStop_() {
}


}