#include "StdAfx.h"
#include "my_app.h"
namespace smc {


void MyCameraTopViewSMC::FSMError( const char * msg1, const char * msg2 ) {
    OutputDebugStr( (convertString( msg1 ) + L" is called at " + convertString( msg2 ) + L"\n").c_str() );
}

void MyCameraTopViewSMC::setBilliardControl( BilliardControl * billiardControl )
{
    billiardControl_ = billiardControl;
}

MyCamera * MyCameraTopViewSMC::getCamera() {
    return billiardControl_->getActiveCamera();
}

void MyCameraTopViewSMC::beginRotateLeft_() {
}
void MyCameraTopViewSMC::beginRotateRight_() {
}
void MyCameraTopViewSMC::endRotateLeft_() {
}
void MyCameraTopViewSMC::endRotateRight_() {
}


}