#include "StdAfx.h"
#include "my_app.h"
namespace smc {


void MyCameraMoveViewRotateSMC::FSMError( const char * msg1, const char * msg2 ) {
    OutputDebugStr( (convertString( msg1 ) + L" is called at " + convertString( msg2 ) + L"\n").c_str() );
}

void MyCameraMoveViewRotateSMC::beginRotateCounterClockWiseByZ_() {
}
void MyCameraMoveViewRotateSMC::beginRotateClockWiseByZ_() {
}
void MyCameraMoveViewRotateSMC::endRotateCounterClockWiseByZ_() {
}
void MyCameraMoveViewRotateSMC::endRotateClockWiseByZ_() {
}

void MyCameraMoveViewRotateSMC::beginPitchDown_() {
}
void MyCameraMoveViewRotateSMC::beginPitchUp_() {
}
void MyCameraMoveViewRotateSMC::endPitchDown_() {
}
void MyCameraMoveViewRotateSMC::endPitchUp_() {
}
void MyCameraMoveViewRotateSMC::entryRotateStop_() {
}


}