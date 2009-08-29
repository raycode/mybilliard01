#pragma once
namespace my_open_al_imp {


class MyOpenALImp : IMPLEMENTS_INTERFACE( MyOpenAL ) {
public:
    virtual SoundHandle * createSoundHandle( wstring filename ) OVERRIDE;
    virtual bool destroySoundHandle( SoundHandle * ) OVERRIDE;

public:
    MyOpenALImp();
    ~MyOpenALImp();

private:
    void setListenerValues();
    ALuint * createBufferFromWave( wstring filename );
    ALuint * createSource( ALuint * buffer );
    void clearErrorLog();

private:
    ALfloat sourcePos_[3];
    ALfloat sourceVel_[3];
    ALfloat listenerPos_[3];
    ALfloat listenerVel_[3];
    ALfloat listenerOri_[6];

private:
    MY_SMART_PTR( ALuint );
    typedef map< wstring, ALuintPtr > Buffers;
    Buffers buffers_;

    typedef list< ALuintPtr > Sources;
    Sources sources_;

    typedef list< SoundHandlePtr > SoundHandles;
    SoundHandles soundHandles_;

private:
    static struct BufferDestoryer {
        void operator()( ALuint * ptr ) {
            alDeleteBuffers( 1, ptr );
            delete ptr;
        }
    };

    static struct SourceDestoryer {
        void operator()( ALuint * ptr ) {
            alDeleteSources( 1, ptr );
            delete ptr;
        }

    };
};


}
