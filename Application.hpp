#ifndef MINIPOS_APPLICATION_HPP
#define MINIPOS_APPLICATION_HPP


#include <memory>
#include <QtWidgets/QApplication>

namespace MiniPos {
class Application;
}

class MiniPos::Application : public QApplication
{
    Q_OBJECT

private:
    struct Impl;
    std::unique_ptr<Impl> m_pimpl;

public:
    Application(int &argc, char **argv);
    virtual ~Application();

signals:

public slots:

public slots:
    void OnEnglishMenuItemPressed();
    void OnFarsiMenuItemPressed();

public:
    void InitializeDatabase();
    void SetupUi();
};

#endif /* APPLICATION_HPP */
