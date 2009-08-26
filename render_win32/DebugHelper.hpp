#pragma once
namespace my_render_win32_imp {


    class DebugHelper {
    public:

        static wstring getStringFromInt( int val ) {
            wchar_t tmp[256];
            _snwprintf_s( tmp, sizeof( tmp ), L"%d", val );
            return tmp;
        }
    };

}