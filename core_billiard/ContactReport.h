#pragma once
namespace my_phys {


MY_INTERFACE ContactReport : public NxUserContactReport {  // NxUserContactModify 

    virtual NxContactPairFlag getContactReportFlags() PURE;

};

}