#ifndef MINIPOS_UIENGINE_HPP
#define MINIPOS_UIENGINE_HPP


#include <memory>
#include <QQmlApplicationEngine>

namespace MiniPos {
class UiEngine;
}

class MiniPos::UiEngine : public QQmlApplicationEngine
{
    Q_OBJECT

private:
    struct Impl;
    std::unique_ptr<Impl> m_pimpl;

public:
    explicit UiEngine(QObject *parent = 0);
    UiEngine(const QUrl &url, QObject *parent = 0);
    UiEngine(const QString &filePath, QObject *parent = 0);
    virtual ~UiEngine();

signals:

public slots:

public:
    Q_INVOKABLE bool notify(const QString &title, const QString &text, const int id = 0) const;
    Q_INVOKABLE bool showToast(const QString &text, const int duration = 8000) const;
};


#endif /* MINIPOS_UIENGINE_HPP */

