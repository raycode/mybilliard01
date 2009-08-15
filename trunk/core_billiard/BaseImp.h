#pragma once
namespace my_render_imp {


class BaseImp : IMPLEMENTS_( Base ) {
public: // from Base
    virtual const wchar_t * getID() OVERRIDE;
    virtual const wchar_t * getName() OVERRIDE;
    virtual const wchar_t * getURI() OVERRIDE;

public: // set
    void setID( wstring id );
    void setName( wstring name );
    void setURI( wstring uri );

private: // from Base
    wstring id_, name_, uri_;

};


}
