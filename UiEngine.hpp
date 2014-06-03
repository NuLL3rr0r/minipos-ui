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

};


#endif // MINIPOS_UIENGINE_HPP

