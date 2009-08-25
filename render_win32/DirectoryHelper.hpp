#pragma once
namespace my_render_win32_imp {


    class DirectoryHelper {
    public:

        class ChangeDirectory {
        public:
            ChangeDirectory( wstring filename ) {
                ::GetCurrentDirectory( sizeof( previousDir_ ), previousDir_ );

                wchar_t newPathname[ MAX_PATH ];
                wchar_t * filePart;
                ::GetFullPathName( filename.c_str(), MAX_PATH, newPathname, & filePart );
                if( NULL != filePart ) filePart[ 0 ] = NULL;

                ::SetCurrentDirectory( newPathname );
            }
            ~ChangeDirectory() {
                ::SetCurrentDirectory( previousDir_ );
            }

        private:
            wchar_t previousDir_[ MAX_PATH ];
        };
    };
}