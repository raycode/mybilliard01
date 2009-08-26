#include "stdafx.h"
#include "test_dx9.h"
#include "RenderEventListenerDX9_DummyRenderListener.h"
//----------------------------------------------
// RenderListenerSMC.cpp
// FSM:       RenderListenerSMC
// Context:   DummyEventListener_RenderWin32DX9Imp
// Version:   
// Generated: Wednesday 08/12/2009 at 15:53:11 EDT
//


static char _versID[]  = "";

#include "RenderListenerSMC.h"

namespace smc
{

//----------------------------------------------
// Definitions of static state objects

//----------------------------------------------
RenderListenerSMCAfterInitState RenderListenerSMC::AfterInit;
RenderListenerSMCAfterResetState RenderListenerSMC::AfterReset;
RenderListenerSMCAfterLostState RenderListenerSMC::AfterLost;
RenderListenerSMCAfterDestroyState RenderListenerSMC::AfterDestroy;
RenderListenerSMCBeforeInitState RenderListenerSMC::BeforeInit;

//----------------------------------------------
// Default Event Functions

//----------------------------------------------

void RenderListenerSMCState::resetSMC(RenderListenerSMC& s)
  { s.FSMError("resetSMC", s.GetState().StateName()); }

void RenderListenerSMCState::initSMC(RenderListenerSMC& s)
  { s.FSMError("initSMC", s.GetState().StateName()); }

void RenderListenerSMCState::lostSMC(RenderListenerSMC& s)
  { s.FSMError("lostSMC", s.GetState().StateName()); }

void RenderListenerSMCState::displaySMC(RenderListenerSMC& s)
  { s.FSMError("displaySMC", s.GetState().StateName()); }

void RenderListenerSMCState::destroySMC(RenderListenerSMC& s)
  { s.FSMError("destroySMC", s.GetState().StateName()); }

void RenderListenerSMCState::updateSMC(RenderListenerSMC& s)
  { s.FSMError("updateSMC", s.GetState().StateName()); }

//----------------------------------------------
// The States and their Transitions
//----------------------------------------------

//----------------------------------------------
// AfterInit Actions and Transitions
//----------------------------------------------

// Starting State: AfterInit
// Event:          resetSMC
//
void RenderListenerSMCAfterInitState::resetSMC( RenderListenerSMC& s )
{

    // Change the state
    s.SetState(RenderListenerSMC::AfterReset);
}

//----------------------------------------------
// AfterReset Actions and Transitions
//----------------------------------------------

// Starting State: AfterReset
// Event:          displaySMC
//
void RenderListenerSMCAfterResetState::displaySMC( RenderListenerSMC& s )
{
}

// Starting State: AfterReset
// Event:          lostSMC
//
void RenderListenerSMCAfterResetState::lostSMC( RenderListenerSMC& s )
{

    // Change the state
    s.SetState(RenderListenerSMC::AfterLost);
}

// Starting State: AfterReset
// Event:          updateSMC
//
void RenderListenerSMCAfterResetState::updateSMC( RenderListenerSMC& s )
{
}

//----------------------------------------------
// AfterLost Actions and Transitions
//----------------------------------------------

// Starting State: AfterLost
// Event:          destroySMC
//
void RenderListenerSMCAfterLostState::destroySMC( RenderListenerSMC& s )
{

    // Change the state
    s.SetState(RenderListenerSMC::AfterDestroy);
}

// Starting State: AfterLost
// Event:          resetSMC
//
void RenderListenerSMCAfterLostState::resetSMC( RenderListenerSMC& s )
{

    // Change the state
    s.SetState(RenderListenerSMC::AfterReset);
}

//----------------------------------------------
// AfterDestroy Actions and Transitions
//----------------------------------------------

//----------------------------------------------
// BeforeInit Actions and Transitions
//----------------------------------------------

// Starting State: BeforeInit
// Event:          initSMC
//
void RenderListenerSMCBeforeInitState::initSMC( RenderListenerSMC& s )
{

    // Change the state
    s.SetState(RenderListenerSMC::AfterInit);
}

//----------------------------------------------
// State Machine Constructor: RenderListenerSMC
//  set Initial State to: BeforeInit
//
//----------------------------------------------
RenderListenerSMC::RenderListenerSMC() : itsState(&BeforeInit)
{
    // Entry functions for: BeforeInit
}

//  Get version information
//
const char* RenderListenerSMC::GetVersion() const
{ return _versID; }

}  // end namespace smc

