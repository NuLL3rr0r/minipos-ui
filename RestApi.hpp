#ifndef MINIPOS_REST_API_HPP
#define MINIPOS_REST_API_HPP


#include <memory>
#include <QtCore/QObject>
class QString;

namespace MiniPos {
class RestApi;
}

class MiniPos::RestApi : public QObject
{
    Q_OBJECT

private:
    class Impl;
    std::unique_ptr<Impl> m_pimpl;

public:
    Q_INVOKABLE RestApi();
    virtual ~RestApi();
};


#endif /* MINIPOS_REST_API_HPP */

