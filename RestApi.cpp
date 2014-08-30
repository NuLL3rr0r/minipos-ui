#include <sstream>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <QtCore/QByteArray>
#include <QtCore/QDebug>
#include <QtCore/QUrlQuery>
#include "make_unique.hpp"
#include "RestApi.hpp"
#include "Crypto.hpp"
#include "Http.hpp"
#include "Pool.hpp"

using namespace std;
using namespace MiniPos;

class RestApi::Impl : public QObject
{
    Q_OBJECT
private:
    RestApi *m_parent;

public:
    typedef std::unique_ptr<Http> Http_t;

public:
    Impl(RestApi *parent);
};

#include "RestApi.moc" // this is a necessitas to QObject-based-Impl

RestApi::RestApi()
    : QObject(),
      m_pimpl(std::make_unique<RestApi::Impl>(this))
{

}

RestApi::~RestApi() = default;

RestApi::Impl::Impl(RestApi *parent) :
    m_parent(parent)
{

}

