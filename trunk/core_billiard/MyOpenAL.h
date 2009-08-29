#pragma once
namespace my_open_al {


MY_INTERFACE MyOpenAL {
    virtual ~MyOpenAL() {}

    virtual SoundHandle * createSoundHandle( wstring filename ) PURE;
    virtual bool destroySoundHandle( SoundHandle * ) PURE;

public:
    struct Destroyer {
        void operator()( SoundHandle * soundHandle ) {
            owner_->destroySoundHandle( soundHandle );
        }

        Destroyer( MyOpenAL * owner ) : owner_( owner ) {}

    private:
        MyOpenAL * const owner_;
    };
};

}