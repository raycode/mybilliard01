#pragma once
namespace my_render_win32_imp {


    class FileSystemHelper {
    public:

        static wstring getFullPathnameWithoutFilename( wstring fullname );
        static wstring getFullname( wstring filename );
        static bool isFileExist( wstring filename );

    public:
        class ChangeDirectory {
        public:
            ChangeDirectory( wstring filename ) {
                ::GetCurrentDirectory( sizeof( previousDir_ ), previousDir_ );
                ::SetCurrentDirectory( getFullPathnameWithoutFilename( filename ).c_str() );
            }
            ~ChangeDirectory() {
                ::SetCurrentDirectory( previousDir_ );
            }

        private:
            wchar_t previousDir_[ MAX_PATH ];
        };

    };
}