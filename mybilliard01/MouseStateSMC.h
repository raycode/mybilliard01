#pragma once
namespace smc {


class MouseStateSMC {
protected: MouseStateSMC();
public: virtual ~MouseStateSMC() {}

public:
    virtual void buttonDown() PURE;
    virtual void move() PURE;

    void buttonDown( HWND hWnd, int iMouseX, int iMouseY );
    void move( int iMouseX, int iMouseY );

public:
    void FSMError( const char *, const char * );

public:
    void buttonUp_();
    void click_();

    void onDrag_();
    void beginDrag_();
    void endDrag_();
    void captureReleased_();

public: // init
    void setCamera( MyCamera * );
    void setBilliardControl( BilliardControl * );
    void setRotationSensitivity( float sensitivity );
    void setPitchSensitivity( float sensitivity );

private:
    MyCamera * getCamera();
    MyCameraState * getCameraState();
    float getRotationSensitivity();
    float getPitchSensitivity();

private: // init
    MyCamera * myCamera_;
    BilliardControl * billiardControl_;
    float rotationSensitivity_, pitchSensitivity_;

private: // mouse coordinate
    int previousX_, previousY_;
    int moveDiffX_, moveDiffY_;
};


}