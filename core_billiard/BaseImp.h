#pragma once
namespace my_render_imp {


class BaseImp : IMPLEMENTS_( Base ) {
public: // from Base
    virtual wstring getID();
    virtual wstring getName();
    virtual wstring getURI();

public: // set
    void setID( wstring id );
    void setName( wstring name );
    void setURI( wstring uri );

private: // from Base
    wstring id_, name_, uri_;

};


}
