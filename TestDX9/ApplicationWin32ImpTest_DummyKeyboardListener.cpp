#include "Stdafx.h"
#include "ApplicationWin32ImpTest_DummyKeyboardListener.h"

DummyKeyboardListener_ApplicationWin32Imp::EachKey::EachKey( unsigned char key, bool down, bool alt )
: whichKey( key ), bDown( down ), bAlt( alt )
{}

bool DummyKeyboardListener_ApplicationWin32Imp::EachKey::operator==( const EachKey& rhs ) const
{
    return bAlt == rhs.bAlt && bDown == rhs.bDown && whichKey == rhs.whichKey;
}


void DummyKeyboardListener_ApplicationWin32Imp::keyDown( unsigned int key, bool bAlt )
{
    if( keys_.empty() ) return;
    if( EachKey( (unsigned char) key, true, bAlt ) == *(keys_.begin()) )
        keys_.pop_front();
}

void DummyKeyboardListener_ApplicationWin32Imp::keyUp( unsigned int key, bool bAlt )
{
    if( keys_.empty() ) return;
    if( EachKey( (unsigned char) key, false, bAlt ) == *(keys_.begin()) )
        keys_.pop_front();
}

void DummyKeyboardListener_ApplicationWin32Imp::appendExpectingKey( unsigned char key, bool bDown, bool bAlt ) {
    EachKey expectingKey( key, bDown, bAlt );
    keys_.push_back( expectingKey );
}

bool DummyKeyboardListener_ApplicationWin32Imp::isAllKeyRecieved() {
    return keys_.empty();
}

