#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

class HomeWidget;
class WriteWidget;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWidget;
}
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

    void setPages();
    void setSignalRelay();

private:
    Ui::MainWidget *ui;

    HomeWidget *homeWidget;
    WriteWidget *writeWidget;
};
#endif // MAINWIDGET_H
