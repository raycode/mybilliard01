#pragma once
namespace smc {


class MyCameraMoveViewRotateSMC {
protected: MyCameraMoveViewRotateSMC() {}
public: virtual ~MyCameraMoveViewRotateSMC() {}
public:
    void FSMError( const char *, const char * );

public:
    void beginRotateClockWiseByZ_();
    void beginRotateCounterClockWiseByZ_();
    void endRotateClockWiseByZ_();
    void endRotateCounterClockWiseByZ_();

    void beginPitchDown_();
    void beginPitchUp_();
    void endPitchDown_();
    void endPitchUp_();

    void entryRotateStop_();

};

}
