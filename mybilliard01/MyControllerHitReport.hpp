#pragma once


class MyControllerHitReport : public NxUserControllerHitReport
{
public:
    virtual NxControllerAction  onShapeHit(const NxControllerShapeHit& hit)
    {
        OutputDebugStr( L"ShapeHit\n" );
        return NX_ACTION_PUSH;
    }

    virtual NxControllerAction  onControllerHit(const NxControllersHit& hit)
    {
        OutputDebugStr( L"ControllerHit\n" );
        return NX_ACTION_PUSH;
    }

};
