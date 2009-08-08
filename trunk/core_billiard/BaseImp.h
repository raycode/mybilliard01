#pragma once
namespace my_render_imp {


class BaseImp : IMPLEMENTS_( Base ) {
public: // from Base
    virtual wstring getID();
    virtual wstring getName();

public: // set
    void setID( wstring id );
    void setName( wstring name );

private: // from Base
    wstring id_, name_;

};


}
