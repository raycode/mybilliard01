#pragma once
namespace my_open_al {


MY_INTERFACE SoundHandle {
    virtual ~SoundHandle() {}

    virtual void playSound() PURE;
    virtual void stopSound() PURE;
    virtual void pauseSound() PURE;

};

}