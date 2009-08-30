#pragma once
namespace smc {


class MyCameraMoveViewMoveSMC {
protected: MyCameraMoveViewMoveSMC() {}
public: virtual ~MyCameraMoveViewMoveSMC() {}
public:
    void FSMError( const char *, const char * );

public:
    void beginMoveForward_();
    void beginMoveLeft_();
    void beginMoveRight_();
    void beginMoveBackward_();
    void endMoveForward_();
    void endMoveLeft_();
    void endMoveRight_();
    void endMoveBackward_();

    void entryMoveStop_();
};

}
