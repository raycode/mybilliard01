#pragma once
namespace my_open_al_imp {


class SoundHandleImp : IMPLEMENTS_INTERFACE( SoundHandle ) {
public: // from SoundHandle
    virtual void playSound() OVERRIDE;
    virtual void stopSound() OVERRIDE;
    virtual void pauseSound() OVERRIDE;

public:
    SoundHandleImp( ALuint * source );

private:
    ALuint * source_;

};

}