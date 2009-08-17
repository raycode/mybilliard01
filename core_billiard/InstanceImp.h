#pragma once
namespace my_render_imp {


class InstanceImp : IMPLEMENTS_INTERFACE( Instance ) {
public: // from Instance
    virtual Base * getInstanceOwner() OVERRIDE;
    virtual wstring getUrl() OVERRIDE;
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
