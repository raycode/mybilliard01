#include "StdAfx.h"
#include "my_app.h"

#define KEY_UP_ARROW 38
#define KEY_LEFT_ARROW 37
#define KEY_RIGHT_ARROW 39
#define KEY_DOWN_ARROW 40

MyInputListenerImp::MyInputListenerImp( MyRenderEventListenerImp * renderListener )
: m_bDrag( false )
{
    renderListener_ = renderListener;
    D3DXQuaternionIdentity( &m_qDown );
    D3DXQuaternionIdentity( &m_qNow );
    m_vDownPt = D3DXVECTOR3( 0, 0, 0 );
    m_vCurrentPt = D3DXVECTOR3( 0, 0, 0 );
}

void MyInputListenerImp::keyDown( unsigned int key, bool bAlt ) {
    //wchar_t tmp[256];
    //_snwprintf_s( tmp, 256, L"key = %d\n", key );
    //OutputDebugStr( tmp );
    switch( key ) {
        case KEY_UP_ARROW: // up arrow
            beginMoveForward();
            break;
        case KEY_LEFT_ARROW: // left arrow
            beginMoveLeft();
            break;
        case KEY_RIGHT_ARROW: // right arrow
            beginMoveRight();
            break;
        case KEY_DOWN_ARROW: // down arrow
            beginMoveBackward();
            break;
    }
}

void MyInputListenerImp::keyUp( unsigned int key, bool bAlt )
{
    switch( key ) {
        case KEY_UP_ARROW: // up arrow
            endMoveForward();
            break;
        case KEY_LEFT_ARROW: // left arrow
            endMoveLeft();
            break;
        case KEY_RIGHT_ARROW: // right arrow
            endMoveRight();
        case KEY_DOWN_ARROW: // down arrow
            endMoveBackward();
            break;
    }
}

void MyInputListenerImp::onMouseEvent(
        int xPos,
        int yPos,
        bool bLeftButton,
        bool bRightButton, 
        bool bMiddleButton, 
        bool bSideButton1, 
        bool bSideButton2, 
        int nMouseWheelDelta ) 
{
    if( bRightButton ) rotateCamera( xPos, yPos );
    if( bLeftButton ) selectBall( xPos, yPos );
}

void MyInputListenerImp::beginMoveForward() {
    getCamera()->beginMoveForward();
}
void MyInputListenerImp::beginMoveLeft() {
    getCamera()->beginMoveLeft();
}
void MyInputListenerImp::beginMoveRight() {
    getCamera()->beginMoveRight();
}
void MyInputListenerImp::beginMoveBackward() {
    getCamera()->beginMoveBackward();
}
void MyInputListenerImp::endMoveForward() {
    getCamera()->endMoveForward();
}
void MyInputListenerImp::endMoveLeft() {
    getCamera()->endMoveLeft();
}
void MyInputListenerImp::endMoveRight() {
    getCamera()->endMoveRight();
}
void MyInputListenerImp::endMoveBackward() {
    getCamera()->endMoveBackward();
}


bool MyInputListenerImp::MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
#ifdef AAA
    // Current mouse position
    int iMouseX = ( short )LOWORD( lParam );
    int iMouseY = ( short )HIWORD( lParam );

    switch( uMsg )
    {
    case WM_LBUTTONDOWN:
    case WM_LBUTTONDBLCLK:
        SetCapture( hWnd );
        OnBegin( iMouseX, iMouseY );
        return TRUE;

    case WM_LBUTTONUP:
        ReleaseCapture();
        OnEnd();
        return TRUE;
    case WM_CAPTURECHANGED:
        if( ( HWND )lParam != hWnd )
        {
            ReleaseCapture();
            OnEnd();
        }
        return TRUE;

    case WM_MOUSEMOVE:
        if( MK_LBUTTON & wParam )
        {
            OnMove( iMouseX, iMouseY );
        }
        return TRUE;
    }
#endif
    return true;
}

void MyInputListenerImp::OnBegin( int nX, int nY )
{
    m_bDrag = true;
    m_qDown = m_qNow;
    m_vDownPt = ScreenToVector( ( float )nX, ( float )nY );
}

void MyInputListenerImp::OnMove( int nX, int nY )
{
    if( m_bDrag )
    {
        m_vCurrentPt = ScreenToVector( ( float )nX, ( float )nY );
        //m_qNow = m_qDown * QuatFromBallPoints( m_vDownPt, m_vCurrentPt );
    }
}

void MyInputListenerImp::OnEnd()
{
    m_bDrag = false;
}

D3DXVECTOR3 MyInputListenerImp::ScreenToVector( float fScreenPtX, float fScreenPtY )
{
    // Scale to screen
    FLOAT x = -( fScreenPtX - m_Offset.x - m_nWidth / 2 ) / ( m_fRadius * m_nWidth / 2 );
    FLOAT y = ( fScreenPtY - m_Offset.y - m_nHeight / 2 ) / ( m_fRadius * m_nHeight / 2 );

    FLOAT z = 0.0f;
    FLOAT mag = x * x + y * y;

    if( mag > 1.0f )
    {
        FLOAT scale = 1.0f / sqrtf( mag );
        x *= scale;
        y *= scale;
    }
    else
        z = sqrtf( 1.0f - mag );

    // Return vector
    return D3DXVECTOR3( x, y, z );
}

//D3DXQUATERNION CD3DArcBall::QuatFromBallPoints( const D3DXVECTOR3& vFrom, const D3DXVECTOR3& vTo )
//{
//    D3DXVECTOR3 vPart;
//    float fDot = D3DXVec3Dot( &vFrom, &vTo );
//    D3DXVec3Cross( &vPart, &vFrom, &vTo );
//
//    return D3DXQUATERNION( vPart.x, vPart.y, vPart.z, fDot );
//}

MyCamera * MyInputListenerImp::getCamera()
{
    return renderListener_->getMyCamera();
}

void MyInputListenerImp::rotateCamera( int xPos, int yPos )
{

}

void MyInputListenerImp::selectBall( int xPos, int yPos )
{

}

