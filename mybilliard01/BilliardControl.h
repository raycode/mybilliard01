#pragma once

MY_INTERFACE BilliardControl {
    virtual ~BilliardControl() {}

    virtual MyCamera * getActiveCamera() PURE;
    virtual NxVec3 getCueBallPosition() PURE;

    virtual void readyToHitCueBall() PURE;
    virtual float getHowMuchPowerIsCharged() PURE;
    virtual void hitCueBall() PURE;

    virtual void bringCueBallBack() PURE;
    virtual void restart() PURE;

    virtual void pause( bool ) PURE;
    virtual bool isPaused() PURE;

    virtual NxActor * getCueBall() PURE;

    virtual bool isBallMoving() PURE;

};