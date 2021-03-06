#ifndef FSM_MyCameraSMC_AutoGenerated_08_30_2009_02_29_39_H
#define FSM_MyCameraSMC_AutoGenerated_08_30_2009_02_29_39_H
//----------------------------------------------
// MyCameraModeSMC_AutoGenerated.h
// FSM:       MyCameraSMC_AutoGenerated
// Context:   MyCameraModeSMC
// Version:   
// Generated: Sunday 08/30/2009 at 02:29:39 EDT
//


// Included header files

#include "MyCameraModeSMC_AutoGenerated.h"

namespace smc
{

// Forward Declarations

class MyCameraSMC_AutoGenerated;

//----------------------------------------------
// MyCameraSMC_AutoGeneratedState: The base state class
//----------------------------------------------
class MyCameraSMC_AutoGeneratedState
{
  public: 
    virtual const char* StateName() const = 0;
    virtual void changeToTopView( MyCameraSMC_AutoGenerated& );
    virtual void changeToMoveView( MyCameraSMC_AutoGenerated& );
    virtual void quit( MyCameraSMC_AutoGenerated& );
    virtual void changeToAimView( MyCameraSMC_AutoGenerated& );
};

//----------------------------------------------
// State: AimView
//----------------------------------------------
class MyCameraSMC_AutoGeneratedAimViewState : public MyCameraSMC_AutoGeneratedState
{
  public: 
    virtual const char* StateName() const
        { return "AimView"; }
    virtual void changeToMoveView( MyCameraSMC_AutoGenerated& );
    virtual void changeToAimView( MyCameraSMC_AutoGenerated& );
    virtual void changeToTopView( MyCameraSMC_AutoGenerated& );
    virtual void quit( MyCameraSMC_AutoGenerated& );
};
//----------------------------------------------
// State: MoveView
//----------------------------------------------
class MyCameraSMC_AutoGeneratedMoveViewState : public MyCameraSMC_AutoGeneratedState
{
  public: 
    virtual const char* StateName() const
        { return "MoveView"; }
    virtual void changeToMoveView( MyCameraSMC_AutoGenerated& );
    virtual void quit( MyCameraSMC_AutoGenerated& );
    virtual void changeToAimView( MyCameraSMC_AutoGenerated& );
    virtual void changeToTopView( MyCameraSMC_AutoGenerated& );
};
//----------------------------------------------
// State: TopView
//----------------------------------------------
class MyCameraSMC_AutoGeneratedTopViewState : public MyCameraSMC_AutoGeneratedState
{
  public: 
    virtual const char* StateName() const
        { return "TopView"; }
    virtual void changeToAimView( MyCameraSMC_AutoGenerated& );
    virtual void quit( MyCameraSMC_AutoGenerated& );
    virtual void changeToTopView( MyCameraSMC_AutoGenerated& );
    virtual void changeToMoveView( MyCameraSMC_AutoGenerated& );
};
//----------------------------------------------
// State: Quit
//----------------------------------------------
class MyCameraSMC_AutoGeneratedQuitState : public MyCameraSMC_AutoGeneratedState
{
  public: 
    virtual const char* StateName() const
        { return "Quit"; }
};
//----------------------------------------------
// MyCameraSMC_AutoGenerated: The Finite State Machine class
//----------------------------------------------
class MyCameraSMC_AutoGenerated: public MyCameraModeSMC
{
  public: 
    // Static State variables
    static MyCameraSMC_AutoGeneratedAimViewState AimView;
    static MyCameraSMC_AutoGeneratedMoveViewState MoveView;
    static MyCameraSMC_AutoGeneratedTopViewState TopView;
    static MyCameraSMC_AutoGeneratedQuitState Quit;

    MyCameraSMC_AutoGenerated(); // default Constructor

    // Event functions
    virtual void changeToTopView() { itsState->changeToTopView( *this ); }
    virtual void changeToMoveView() { itsState->changeToMoveView( *this ); }
    virtual void quit() { itsState->quit( *this ); }
    virtual void changeToAimView() { itsState->changeToAimView( *this ); }

    // State Accessor functions
    void SetState( MyCameraSMC_AutoGeneratedState& theState ) { itsState = &theState; }
    MyCameraSMC_AutoGeneratedState& GetState() const { return *itsState; }

    const char* GetCurrentStateName() const { return itsState->StateName(); }
    const char* GetVersion() const;

  private: 
    MyCameraSMC_AutoGeneratedState* itsState;
};

}  // end namespace smc

#endif /* FSM_MyCameraSMC_AutoGenerated_08_30_2009_02_29_39_H */
