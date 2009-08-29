#include "StdAfx.h"
#include "my_open_al_imp.h"
namespace my_open_al_imp {

#pragma warning ( disable : 4996 )


MyOpenALImp::MyOpenALImp()
{
    sourcePos_[0] = 0.0;
    sourcePos_[1] = 0.0;
    sourcePos_[2] = 0.0;

    sourceVel_[0] = 0.0;
    sourceVel_[1] = 0.0;
    sourceVel_[2] = 0.0;

    listenerPos_[0] = 0.0;
    listenerPos_[1] = 0.0;
    listenerPos_[2] = 0.0;

    listenerVel_[0] = 0.0;
    listenerVel_[1] = 0.0;
    listenerVel_[2] = 0.0;

    // "at" and "up"
    listenerOri_[0] = 0.0;
    listenerOri_[1] = 0.0;
    listenerOri_[2] = -1.0;
    listenerOri_[3] = 0.0;
    listenerOri_[4] = 0.0;
    listenerOri_[5] = 1.0;

    int tmpArgc = 1;
    char *tmpArgv[] = {""};
    alutInit( &tmpArgc, tmpArgv );
    alGetError();

    setListenerValues();
}

MyOpenALImp::~MyOpenALImp()
{
    alutExit();
}

void MyOpenALImp::setListenerValues()
{
    alListenerfv( AL_POSITION,    listenerPos_ );
    alListenerfv( AL_VELOCITY,    listenerVel_ );
    alListenerfv( AL_ORIENTATION, listenerOri_ );
}

SoundHandle * MyOpenALImp::createSoundHandle( wstring filename )
{
    ALuint * const newBuffer = createBufferFromWave( filename );
    if( NULL == newBuffer ) return NULL;

    ALuint * const newSource = createSource( newBuffer );
    if( NULL == newSource ) return NULL;

    SoundHandlePtr newSoundHandle = SoundHandlePtr( new SoundHandleImp( newSource, filename ) );
    if( NULL == newSoundHandle ) return NULL;

    soundHandles_.push_back( newSoundHandle );
    return newSoundHandle.get();
}

bool MyOpenALImp::destroySoundHandle( SoundHandle * victim ) {
    return remove_only_one_pointer( soundHandles_, victim );
}

ALuint * MyOpenALImp::createBufferFromWave( wstring filename )
{
    Buffers::const_iterator iter = buffers_.find( filename );
    if( buffers_.end() != iter ) return iter->second.get();

    ALuintPtr newBuffer = ALuintPtr( new ALuint(), BufferDestoryer() );

    clearErrorLog();
    const ALsizei sizeOfArray = 1;
    alGenBuffers( sizeOfArray, newBuffer.get() );
    if (alGetError() != AL_NO_ERROR) return NULL;
    assert( NULL != *newBuffer );

    ALenum format;
    ALsizei size;
    ALvoid* data;
    ALsizei freq;
    ALboolean loop;

    alutLoadWAVFile( (ALbyte*) convertString( filename ).c_str(), &format, &data, &size, &freq, &loop);
    alBufferData( *newBuffer, format, data, size, freq );
    alutUnloadWAV( format, data, size, freq );

    buffers_.insert( Buffers::value_type( filename, newBuffer ) );
    return newBuffer.get();
}

ALuint * MyOpenALImp::createSource( ALuint * buffer )
{
    // Bind buffer with a source.
    ALuintPtr source = ALuintPtr( new ALuint(), SourceDestoryer() );

    clearErrorLog();
    const ALsizei sizeOfArray = 1;
    alGenSources( sizeOfArray, source.get() );
    if( alGetError() != AL_NO_ERROR ) return NULL;
    assert( NULL != *source );

    clearErrorLog();
    alSourcei ( *source, AL_BUFFER,   *buffer   );
    alSourcef ( *source, AL_PITCH,    1.0f      );
    alSourcef ( *source, AL_GAIN,     1.0f      );
    alSourcefv( *source, AL_POSITION, sourcePos_);
    alSourcefv( *source, AL_VELOCITY, sourceVel_);
    alSourcei ( *source, AL_LOOPING,  false      );
    //alSourcei ( *source, AL_LOOPING,  loop      );
    if (alGetError() != AL_NO_ERROR)
        return NULL;

    sources_.push_back( source );
    return source.get();
}

void MyOpenALImp::clearErrorLog() {
    alGetError();
}

}
