#pragma once
namespace my_render {


MY_INTERFACE Texture {
    virtual ~Texture() {}

    virtual bool isFromFile() PURE;
    virtual wstring getFilename() PURE;

    virtual size_t getWidth() PURE;
    virtual size_t getHeight() PURE;

};


}