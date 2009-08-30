#pragma once
namespace smc {


class MyCameraAimViewSMC {
protected: MyCameraAimViewSMC() {}
public: virtual ~MyCameraAimViewSMC() {}
public:
    void FSMError( const char *, const char * );

public:
    void beginAimLeft_();
    void beginAimRight_();
    void endAimLeft_();
    void endAimRight_();
    void beginShoot_();
    void endShoot_();

    void entryAimStop_();

public: // init
    void setBilliardControl( BilliardControl * );

public:
    NxVec3 getAimPoint();

private:
    MyCamera * getCamera();
    BilliardControl * billiardControl_;
};

}
