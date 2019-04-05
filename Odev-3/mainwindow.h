#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "balloon.h"
#include <QMainWindow>
#include<QPixmap>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    int missCount=0,catchCount=0,timer=0,balloonSize=7;
    bool flipFlop=false;
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
     QList<Balloon*> balloons;
     bool isFinished=false;
public slots:
    int randomPoint();
    void backGroundUpdate();
    void resizeEvent(QResizeEvent *event);
    void loop();
    void updateInformation();
    void balloonControlHigh();
    void updateTime();
    void UIUpdate();
    void createBalloon();
    void callEffect(Balloon *bal);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
