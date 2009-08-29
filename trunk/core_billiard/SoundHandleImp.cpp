#include "stdafx.h"
#include "my_open_al_imp.h"
namespace my_open_al_imp {


SoundHandleImp::SoundHandleImp( ALuint * source, wstring filename )
: source_( source )
, filename_( filename )
{}

void SoundHandleImp::playSound() {
    alSourcePlay( *source_ );
}

void SoundHandleImp::stopSound() {
    alSourceStop( *source_ );
}

void SoundHandleImp::pauseSound() {
    alSourcePause( *source_ );
}

}