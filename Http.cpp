#include <memory>
#include <QtCore/QDebug>
#include <QtCore/QString>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkConfigurationManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include "make_unique.hpp"
#include "Http.hpp"

using namespace std;
using namespace MiniPos;

class Http::Impl : public QObject
{
    Q_OBJECT

public:
    typedef std::unique_ptr<QNetworkAccessManager> QNetworkAccessManager_t;

public:
    QNetworkAccessManager_t DeleteNetworkAccessManager;
    QNetworkAccessManager_t GetNetworkAccessManager;
    QNetworkAccessManager_t PostNetworkAccessManager;
    QNetworkAccessManager_t PutNetworkAccessManager;

private:
    Http *m_parent;

public:
    Impl(Http *parent);

public slots:
    void AuthenticationRequired(QNetworkReply * reply, QAuthenticator * authenticator);
    void Encrypted(QNetworkReply * reply);
    void Finished(QNetworkReply * reply);
    void NetworkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility accessible);
    void ProxyAuthenticationRequired(const QNetworkProxy & proxy, QAuthenticator * authenticator);
    void SslErrors(QNetworkReply * reply, const QList<QSslError> & errors);

public:
    bool IsConnected();
    void SetupRequest(QNetworkRequest &request);
    void SetupEvents(QNetworkAccessManager *networkAccessManager);
};

#include "Http.moc" // this is a necessitas to QObject-based-Impl

Http::Http()
    : QObject(),
      m_pimpl(std::make_unique<Http::Impl>(this))
{

}

Http::~Http() = default;

void Http::Delete(const QString &url)
{
    if (!m_pimpl->IsConnected()) {
        emit Signal_Error(tr("CONNECTION_FAILED"));
        return;
    }

    m_pimpl->DeleteNetworkAccessManager.reset(new QNetworkAccessManager());
    QNetworkRequest request { QUrl(url) };

    m_pimpl->SetupRequest(request);
    m_pimpl->SetupEvents(m_pimpl->DeleteNetworkAccessManager.get());

    m_pimpl->DeleteNetworkAccessManager->deleteResource(request);
}

void Http::Get(const QString &url)
{
    if (!m_pimpl->IsConnected()) {
        emit Signal_Error(tr("CONNECTION_FAILED"));
        return;
    }

    m_pimpl->GetNetworkAccessManager.reset(new QNetworkAccessManager());
    QNetworkRequest request { QUrl(url) };

    m_pimpl->SetupRequest(request);
    m_pimpl->SetupEvents(m_pimpl->GetNetworkAccessManager.get());

    m_pimpl->GetNetworkAccessManager->get(request);
}

void Http::Post(const QString &url, const QByteArray &data)
{
    if (!m_pimpl->IsConnected()) {
        emit Signal_Error(tr("CONNECTION_FAILED"));
        return;
    }

    m_pimpl->PostNetworkAccessManager.reset(new QNetworkAccessManager());
    QNetworkRequest request { QUrl(url) };

    m_pimpl->SetupRequest(request);
    m_pimpl->SetupEvents(m_pimpl->PostNetworkAccessManager.get());

    m_pimpl->PostNetworkAccessManager->post(request, data);
}

void Http::Put(const QString &url, const QByteArray &data)
{
    if (!m_pimpl->IsConnected()) {
        emit Signal_Error(tr("CONNECTION_FAILED"));
        return;
    }

    m_pimpl->PutNetworkAccessManager.reset(new QNetworkAccessManager());
    QNetworkRequest request { QUrl(url) };

    m_pimpl->SetupRequest(request);
    m_pimpl->SetupEvents(m_pimpl->PutNetworkAccessManager.get());

    m_pimpl->PutNetworkAccessManager->put(request, data);
}

Http::Impl::Impl(Http *parent) :
    m_parent(parent)
{

}

void Http::Impl::AuthenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator)
{
    (void)authenticator;
    emit m_parent->Signal_Error(tr("AUTHENTICATION_REQUIRED: %1").arg(QString(reply->readAll())));
    reply->deleteLater();
}

void Http::Impl::Encrypted(QNetworkReply *reply)
{
    emit m_parent->Signal_Error(reply->readAll());
    reply->deleteLater();
}

void Http::Impl::Finished(QNetworkReply *reply)
{
    emit m_parent->Signal_Finished(reply->readAll());
    reply->deleteLater();
}

void Http::Impl::NetworkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility accessible)
{
    if (accessible != QNetworkAccessManager::Accessible) {
        emit m_parent->Signal_Error(tr("NO_NETWORK_ACCESS"));
    }
}

void Http::Impl::ProxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator)
{
    (void)proxy;
    (void)authenticator;
    emit m_parent->Signal_Error(tr("PROXY_AUTHENTICATION_REQUIRED"));
}

void Http::Impl::SslErrors(QNetworkReply *reply, const QList<QSslError> &errors)
{
    (void)errors;
    emit m_parent->Signal_Error(reply->readAll());
    reply->deleteLater();
}

bool Http::Impl::IsConnected()
{
    QNetworkConfigurationManager configurationManager;

    if (!configurationManager.isOnline()) {
        configurationManager.deleteLater();
        return false;
    }

    return true;
}

void Http::Impl::SetupRequest(QNetworkRequest &request)
{
    QSslConfiguration sslConfiguration(QSslConfiguration::defaultConfiguration());
    request.setSslConfiguration(sslConfiguration);

    request.setRawHeader("Accept", "application/json");
    request.setRawHeader("Accept-Charset", "utf-8");
    request.setRawHeader("Content-Type", "application/json");
}

void Http::Impl::SetupEvents(QNetworkAccessManager *networkAccessManager)
{
    connect(networkAccessManager, SIGNAL(authenticationRequired(QNetworkReply *, QAuthenticator *)),
            this, SLOT(AuthenticationRequired(QNetworkReply *, QAuthenticator *)));
    connect(networkAccessManager, SIGNAL(encrypted(QNetworkReply *)),
            this, SLOT(Encrypted(QNetworkReply *)));
    connect(networkAccessManager, SIGNAL(finished(QNetworkReply *)),
            this, SLOT(Finished(QNetworkReply *)));
    connect(networkAccessManager, SIGNAL(networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility)),
            this, SLOT(NetworkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility)));
    connect(networkAccessManager, SIGNAL(proxyAuthenticationRequired(const QNetworkProxy &, QAuthenticator *)),
            this, SLOT(ProxyAuthenticationRequired(const QNetworkProxy &, QAuthenticator *)));
    connect(networkAccessManager, SIGNAL(sslErrors(QNetworkReply *, const QList<QSslError> &)),
            this, SLOT(SslErrors(QNetworkReply *, const QList<QSslError> &)));
}

