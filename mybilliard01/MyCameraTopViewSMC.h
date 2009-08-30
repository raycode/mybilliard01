#pragma once
namespace smc {


class MyCameraTopViewSMC {
protected: MyCameraTopViewSMC() {}
public: virtual ~MyCameraTopViewSMC() {}
public:
    void FSMError( const char *, const char * );

public:
    void beginRotateLeft_();
    void beginRotateRight_();
    void endRotateLeft_();
    void endRotateRight_();

public: // init
    void setBilliardControl( BilliardControl * );

private:
    MyCamera * getCamera();
    BilliardControl * billiardControl_;
};

}
