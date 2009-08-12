#pragma once


class DummyKeyboardListener_ApplicationWin32Imp : IMPLEMENTS_( KeyboardEventListener ) {
private:

    class EachKey {
    public:
        EachKey( unsigned char key, bool down, bool alt );
        bool operator==( const EachKey& rhs ) const;
    private:
        bool bAlt;
        bool bDown;
        unsigned char whichKey;
    };

public:
    virtual void keyDown( unsigned int key, bool bAlt ) OVERRIDE;
    virtual void keyUp( unsigned int key, bool bAlt ) OVERRIDE;

public:
    void appendExpectingKey( unsigned char key, bool bDown, bool bAlt );
    bool isAllKeyRecieved();

private:
    typedef deque< EachKey > Keys;
    Keys keys_;
};

