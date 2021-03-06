//----------------------------------------------
// MyCameraAimViewSMC_AutoGenerated.cpp
// FSM:       MyCameraAimViewSMC_AutoGenerated
// Context:   MyCameraAimViewSMC
// Version:   
// Generated: Sunday 08/30/2009 at 02:29:39 EDT
//


static char _versID[]  = "";

#include "MyCameraAimViewSMC_AutoGenerated.h"

namespace smc
{

//----------------------------------------------
// Definitions of static state objects

//----------------------------------------------
MyCameraAimViewSMC_AutoGeneratedAimRightState MyCameraAimViewSMC_AutoGenerated::AimRight;
MyCameraAimViewSMC_AutoGeneratedAimStopState MyCameraAimViewSMC_AutoGenerated::AimStop;
MyCameraAimViewSMC_AutoGeneratedAimLeftState MyCameraAimViewSMC_AutoGenerated::AimLeft;
MyCameraAimViewSMC_AutoGeneratedShootState MyCameraAimViewSMC_AutoGenerated::Shoot;

//----------------------------------------------
// Default Event Functions

//----------------------------------------------

void MyCameraAimViewSMC_AutoGeneratedState::endAimLeft(MyCameraAimViewSMC_AutoGenerated& s)
  { s.FSMError("endAimLeft", s.GetState().StateName()); }

void MyCameraAimViewSMC_AutoGeneratedState::beginAimLeft(MyCameraAimViewSMC_AutoGenerated& s)
  { s.FSMError("beginAimLeft", s.GetState().StateName()); }

void MyCameraAimViewSMC_AutoGeneratedState::endAimRight(MyCameraAimViewSMC_AutoGenerated& s)
  { s.FSMError("endAimRight", s.GetState().StateName()); }

void MyCameraAimViewSMC_AutoGeneratedState::beginShoot(MyCameraAimViewSMC_AutoGenerated& s)
  { s.FSMError("beginShoot", s.GetState().StateName()); }

void MyCameraAimViewSMC_AutoGeneratedState::beginAimRight(MyCameraAimViewSMC_AutoGenerated& s)
  { s.FSMError("beginAimRight", s.GetState().StateName()); }

void MyCameraAimViewSMC_AutoGeneratedState::endShoot(MyCameraAimViewSMC_AutoGenerated& s)
  { s.FSMError("endShoot", s.GetState().StateName()); }

//----------------------------------------------
// The States and their Transitions
//----------------------------------------------

//----------------------------------------------
// AimRight Actions and Transitions
//----------------------------------------------

// Starting State: AimRight
// Event:          endAimRight
//
void MyCameraAimViewSMC_AutoGeneratedAimRightState::endAimRight( MyCameraAimViewSMC_AutoGenerated& s )
{

    s.endAimRight_();

    // Change the state
    s.SetState(MyCameraAimViewSMC_AutoGenerated::AimStop);

    // Entry functions for: AimStop
    s.entryAimStop_();
}

//----------------------------------------------
// AimStop Actions and Transitions
//----------------------------------------------

// Starting State: AimStop
// Event:          beginAimRight
//
void MyCameraAimViewSMC_AutoGeneratedAimStopState::beginAimRight( MyCameraAimViewSMC_AutoGenerated& s )
{

    s.beginAimRight_();

    // Change the state
    s.SetState(MyCameraAimViewSMC_AutoGenerated::AimRight);
}

// Starting State: AimStop
// Event:          beginShoot
//
void MyCameraAimViewSMC_AutoGeneratedAimStopState::beginShoot( MyCameraAimViewSMC_AutoGenerated& s )
{

    s.beginShoot_();

    // Change the state
    s.SetState(MyCameraAimViewSMC_AutoGenerated::Shoot);
}

// Starting State: AimStop
// Event:          beginAimLeft
//
void MyCameraAimViewSMC_AutoGeneratedAimStopState::beginAimLeft( MyCameraAimViewSMC_AutoGenerated& s )
{

    s.beginAimLeft_();

    // Change the state
    s.SetState(MyCameraAimViewSMC_AutoGenerated::AimLeft);
}

//----------------------------------------------
// AimLeft Actions and Transitions
//----------------------------------------------

// Starting State: AimLeft
// Event:          endAimLeft
//
void MyCameraAimViewSMC_AutoGeneratedAimLeftState::endAimLeft( MyCameraAimViewSMC_AutoGenerated& s )
{

    s.endAimLeft_();

    // Change the state
    s.SetState(MyCameraAimViewSMC_AutoGenerated::AimStop);

    // Entry functions for: AimStop
    s.entryAimStop_();
}

//----------------------------------------------
// Shoot Actions and Transitions
//----------------------------------------------

// Starting State: Shoot
// Event:          endShoot
//
void MyCameraAimViewSMC_AutoGeneratedShootState::endShoot( MyCameraAimViewSMC_AutoGenerated& s )
{

    s.endShoot_();

    // Change the state
    s.SetState(MyCameraAimViewSMC_AutoGenerated::AimStop);

    // Entry functions for: AimStop
    s.entryAimStop_();
}

//----------------------------------------------
// State Machine Constructor: MyCameraAimViewSMC_AutoGenerated
//  set Initial State to: AimStop
//
//----------------------------------------------
MyCameraAimViewSMC_AutoGenerated::MyCameraAimViewSMC_AutoGenerated() : itsState(&AimStop)
{
    // Entry functions for: AimStop
    entryAimStop_();
}

//  Get version information
//
const char* MyCameraAimViewSMC_AutoGenerated::GetVersion() const
{ return _versID; }

}  // end namespace smc

