#pragma once
namespace my_render_imp {


class InstanceImp : IMPLEMENTS_( Instance ) {
public: // from Instance
    virtual Base * getInstanceOwner() OVERRIDE;
    virtual const wchar_t * getUrl() OVERRIDE;
    virtual Base * getResolvedReferrence() OVERRIDE;

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
