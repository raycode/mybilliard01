#include "stdafx.h"
namespace my_phys_x {

NxAssertResponse ErrorStream::reportAssertViolation(const char* message, const char* file, int line)
{
    switch (MessageBox(0, convertString< string, wstring >( message ).c_str(),
        L"AssertViolation.", MB_ABORTRETRYIGNORE))
    {
    case IDRETRY:
        return NX_AR_CONTINUE;
    case IDIGNORE:
        return NX_AR_IGNORE;
    case IDABORT:
    default:
        return NX_AR_BREAKPOINT;
    }


}
}