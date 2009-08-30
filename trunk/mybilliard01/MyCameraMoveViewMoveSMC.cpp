#include "StdAfx.h"
#include "my_app.h"
namespace smc {


void MyCameraMoveViewMoveSMC::FSMError( const char * msg1, const char * msg2 ) {
    OutputDebugStr( (convertString( msg1 ) + L" is called at " + convertString( msg2 ) + L"\n").c_str() );
}

void MyCameraMoveViewMoveSMC::beginMoveForward_() {
}

void MyCameraMoveViewMoveSMC::beginMoveLeft_() {
}
void MyCameraMoveViewMoveSMC::beginMoveRight_() {
}
void MyCameraMoveViewMoveSMC::beginMoveBackward_() {
}
void MyCameraMoveViewMoveSMC::endMoveForward_() {
}
void MyCameraMoveViewMoveSMC::endMoveLeft_() {
}
void MyCameraMoveViewMoveSMC::endMoveRight_() {
}
void MyCameraMoveViewMoveSMC::endMoveBackward_() {
}
void MyCameraMoveViewMoveSMC::entryMoveStop_() {
}



}