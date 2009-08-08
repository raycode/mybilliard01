#pragma once
namespace my_render_imp {


class InstanceImp : IMPLEMENTS_( Instance ) {
public: // from Instance
    virtual Base * getInstanceOwner();
    virtual wstring getUrl();
    virtual Base * getResolvedReferrence();

public:
    InstanceImp( InstanceResolver * resolver );

    void setInstanceOwner( Base * owner );
    void setUrl( wstring url );

private:
    InstanceResolver * resolver_;

    Base * instanceOwner_;
    wstring url_;
};


}
