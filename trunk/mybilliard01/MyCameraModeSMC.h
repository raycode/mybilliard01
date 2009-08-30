#pragma once
namespace smc {


class MyCameraModeSMC {
protected: MyCameraModeSMC();
public: virtual ~MyCameraModeSMC() {}
public:
    void FSMError( const char *, const char * );

public:
    void changeToTopView_();
    void changeToAimView_();
    void changeToMoveView_();
    void quit_();

public:
    void setBilliardControl( BilliardControl * );

private:
    MyCamera * getCamera();
    void restoreCameraPosition();

private:
    BilliardControl * billiardControl_;

    bool bNeedToBeRestored_;
    NxExtendedVec3 position_;
    NxMat33 rotate_;
};

}
