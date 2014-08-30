#ifndef MINIPOS_HTTP_STATUS_HPP
#define MINIPOS_HTTP_STATUS_HPP


#include <string>

namespace MiniPos {
class HttpStatus;
}

class MiniPos::HttpStatus
{
public:
    enum class HttpStatusCode : unsigned char {
        HTTP_100,
        HTTP_101,
        HTTP_200,
        HTTP_201,
        HTTP_202,
        HTTP_203,
        HTTP_204,
        HTTP_205,
        HTTP_206,
        HTTP_300,
        HTTP_301,
        HTTP_302,
        HTTP_303,
        HTTP_304,
        HTTP_305,
        HTTP_307,
        HTTP_400,
        HTTP_401,
        HTTP_402,
        HTTP_403,
        HTTP_404,
        HTTP_405,
        HTTP_406,
        HTTP_407,
        HTTP_408,
        HTTP_409,
        HTTP_410,
        HTTP_411,
        HTTP_412,
        HTTP_413,
        HTTP_414,
        HTTP_415,
        HTTP_416,
        HTTP_417,
        HTTP_500,
        HTTP_501,
        HTTP_502,
        HTTP_503,
        HTTP_504,
        HTTP_505
    };

private:
    struct Impl;
    static std::unique_ptr<Impl> s_pimpl;

public:
    static std::wstring GetHttpResponse(const HttpStatusCode &code);
};


#endif /* MINIPOS_HTTP_STATUS_HPP */

