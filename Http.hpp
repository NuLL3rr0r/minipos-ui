/**
 * @author  Mohammad S. Babaei <info@babaei.net>
 */


#ifndef MINIPOS_HTTP_HPP
#define MINIPOS_HTTP_HPP


#include <memory>
#include <QtCore/QObject>

namespace MiniPos {
class Http;
}

class MiniPos::Http : public QObject
{
    Q_OBJECT

private:
    class Impl;
    std::unique_ptr<Impl> m_pimpl;

public:
    Http();
    virtual ~Http();

signals:
    void Signal_Error(const QString &);
    void Signal_Finished(const QString &);

public:
    void Delete(const QString &url);
    void Get(const QString &url);
    void Post(const QString &url, const QByteArray &data);
    void Put(const QString &url, const QByteArray &data);
};


#endif /* MINIPOS_HTTP_HPP */

