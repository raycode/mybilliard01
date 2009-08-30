//----------------------------------------------
// MyCameraModeSMC_AutoGenerated.cpp
// FSM:       MyCameraSMC_AutoGenerated
// Context:   MyCameraModeSMC
// Version:   
// Generated: Sunday 08/30/2009 at 02:29:39 EDT
//


static char _versID[]  = "";

#include "MyCameraModeSMC_AutoGenerated.h"

namespace smc
{

//----------------------------------------------
// Definitions of static state objects

//----------------------------------------------
MyCameraSMC_AutoGeneratedAimViewState MyCameraSMC_AutoGenerated::AimView;
MyCameraSMC_AutoGeneratedMoveViewState MyCameraSMC_AutoGenerated::MoveView;
MyCameraSMC_AutoGeneratedTopViewState MyCameraSMC_AutoGenerated::TopView;
MyCameraSMC_AutoGeneratedQuitState MyCameraSMC_AutoGenerated::Quit;

//----------------------------------------------
// Default Event Functions

//----------------------------------------------

void MyCameraSMC_AutoGeneratedState::changeToTopView(MyCameraSMC_AutoGenerated& s)
  { s.FSMError("changeToTopView", s.GetState().StateName()); }

void MyCameraSMC_AutoGeneratedState::changeToMoveView(MyCameraSMC_AutoGenerated& s)
  { s.FSMError("changeToMoveView", s.GetState().StateName()); }

void MyCameraSMC_AutoGeneratedState::quit(MyCameraSMC_AutoGenerated& s)
  { s.FSMError("quit", s.GetState().StateName()); }

void MyCameraSMC_AutoGeneratedState::changeToAimView(MyCameraSMC_AutoGenerated& s)
  { s.FSMError("changeToAimView", s.GetState().StateName()); }

//----------------------------------------------
// The States and their Transitions
//----------------------------------------------

//----------------------------------------------
// AimView Actions and Transitions
//----------------------------------------------

// Starting State: AimView
// Event:          changeToMoveView
//
void MyCameraSMC_AutoGeneratedAimViewState::changeToMoveView( MyCameraSMC_AutoGenerated& s )
{

    s.changeToMoveView_();

    // Change the state
    s.SetState(MyCameraSMC_AutoGenerated::MoveView);
}

// Starting State: AimView
// Event:          changeToAimView
//
void MyCameraSMC_AutoGeneratedAimViewState::changeToAimView( MyCameraSMC_AutoGenerated& s )
{

    s.changeToAimView_();

    // Change the state
    s.SetState(MyCameraSMC_AutoGenerated::AimView);
}

// Starting State: AimView
// Event:          changeToTopView
//
void MyCameraSMC_AutoGeneratedAimViewState::changeToTopView( MyCameraSMC_AutoGenerated& s )
{

    s.changeToTopView_();

    // Change the state
    s.SetState(MyCameraSMC_AutoGenerated::TopView);
}

// Starting State: AimView
// Event:          quit
//
void MyCameraSMC_AutoGeneratedAimViewState::quit( MyCameraSMC_AutoGenerated& s )
{

    // Change the state
    s.SetState(MyCameraSMC_AutoGenerated::Quit);

    // Entry functions for: Quit
    s.quit_();
}

//----------------------------------------------
// MoveView Actions and Transitions
//----------------------------------------------

// Starting State: MoveView
// Event:          changeToMoveView
//
void MyCameraSMC_AutoGeneratedMoveViewState::changeToMoveView( MyCameraSMC_AutoGenerated& s )
{

    s.changeToMoveView_();

    // Change the state
    s.SetState(MyCameraSMC_AutoGenerated::MoveView);
}

// Starting State: MoveView
// Event:          quit
//
void MyCameraSMC_AutoGeneratedMoveViewState::quit( MyCameraSMC_AutoGenerated& s )
{

    // Change the state
    s.SetState(MyCameraSMC_AutoGenerated::Quit);

    // Entry functions for: Quit
    s.quit_();
}

// Starting State: MoveView
// Event:          changeToAimView
//
void MyCameraSMC_AutoGeneratedMoveViewState::changeToAimView( MyCameraSMC_AutoGenerated& s )
{

    s.changeToAimView_();

    // Change the state
    s.SetState(MyCameraSMC_AutoGenerated::AimView);
}

// Starting State: MoveView
// Event:          changeToTopView
//
void MyCameraSMC_AutoGeneratedMoveViewState::changeToTopView( MyCameraSMC_AutoGenerated& s )
{

    s.changeToTopView_();

    // Change the state
    s.SetState(MyCameraSMC_AutoGenerated::TopView);
}

//----------------------------------------------
// TopView Actions and Transitions
//----------------------------------------------

// Starting State: TopView
// Event:          changeToAimView
//
void MyCameraSMC_AutoGeneratedTopViewState::changeToAimView( MyCameraSMC_AutoGenerated& s )
{

    s.changeToAimView_();

    // Change the state
    s.SetState(MyCameraSMC_AutoGenerated::AimView);
}

// Starting State: TopView
// Event:          quit
//
void MyCameraSMC_AutoGeneratedTopViewState::quit( MyCameraSMC_AutoGenerated& s )
{

    // Change the state
    s.SetState(MyCameraSMC_AutoGenerated::Quit);

    // Entry functions for: Quit
    s.quit_();
}

// Starting State: TopView
// Event:          changeToTopView
//
void MyCameraSMC_AutoGeneratedTopViewState::changeToTopView( MyCameraSMC_AutoGenerated& s )
{

    s.changeToTopView_();

    // Change the state
    s.SetState(MyCameraSMC_AutoGenerated::TopView);
}

// Starting State: TopView
// Event:          changeToMoveView
//
void MyCameraSMC_AutoGeneratedTopViewState::changeToMoveView( MyCameraSMC_AutoGenerated& s )
{

    s.changeToMoveView_();

    // Change the state
    s.SetState(MyCameraSMC_AutoGenerated::MoveView);
}

//----------------------------------------------
// Quit Actions and Transitions
//----------------------------------------------

//----------------------------------------------
// State Machine Constructor: MyCameraSMC_AutoGenerated
//  set Initial State to: AimView
//
//----------------------------------------------
MyCameraSMC_AutoGenerated::MyCameraSMC_AutoGenerated() : itsState(&AimView)
{
    // Entry functions for: AimView
}

//  Get version information
//
const char* MyCameraSMC_AutoGenerated::GetVersion() const
{ return _versID; }

}  // end namespace smc

