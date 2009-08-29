#include "stdafx.h"
#include "my_open_al_imp.h"
namespace my_open_al_imp {


SoundHandleImp::SoundHandleImp( ALuint * source )
: source_( source )
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