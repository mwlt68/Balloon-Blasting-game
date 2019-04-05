#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "balloon.h"

#include <QTime>
#include <QTimer>

static QImage imgFall("C:\\Users\\asus\\Documents\\QT\\Odev-3\\bombFall.png");
static QImage bombNow("C:\\Users\\asus\\Documents\\QT\\Odev-3\\bombNow.png");
bool flip=false;
static int odd=1;
static int callSpeed=100;
static int speed=7;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand(time(nullptr));
    ui->missLabel->setStyleSheet("QLabel{color:red;}");
    ui->catchLabel->setStyleSheet("QLabel{color:green;}");
    backGroundUpdate();
    for (int i=0;i<balloonSize;i++) {
        createBalloon();
    }
    QTimer * timer =new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateTime()));
    timer->start(1000);
    QTimer * timer2 =new QTimer(this);
    connect(timer2,SIGNAL(timeout()),this,SLOT(loop()));
    timer2->start(callSpeed);



}
void MainWindow :: createBalloon(){
    Balloon *balloon=new  Balloon(this);
    balloon->setGeometry(randomPoint()-70,this->geometry().height()+balloon->height(),50,70);
//       QMessageBox :: information(this,"inf",QString :: number(balloon->geometry().x()));
    balloons.append(balloon);
}
void MainWindow :: updateTime (){
        ui->timeLabel->setText(QString :: number(timer++));
}
void MainWindow :: UIUpdate(){
    ui->missLabel->setText(QString :: number(missCount));
    ui->catchLabel->setText(QString :: number(catchCount));
}
void MainWindow :: loop(){


        if(catchCount < missCount)
        {
            if(!flip){
              QMessageBox :: information(this,"Inf","You lose !");
              flip=true;
            }
            return;
        }
        if(timer % 10==0){
            speed+=timer/15;
            callSpeed-=10;
        }
        foreach(Balloon *bal, balloons){
           if(bal->isBombed){
                if(!bal->isFalling){
                    catchCount++;
                    callEffect(bal);
                    bal->isFalling=true;
                }
                else if(bal->geometry().y()>this->geometry().height())
                {
                    bal->hide();
                    delete bal;
                    balloons.removeOne(bal);
                }
                else {
                    bal->setPixmap(QPixmap ::fromImage(imgFall));
                    bal->setGeometry(bal->geometry().x(),bal->geometry().y()+speed,bal->geometry().width(),bal->geometry().height());
                }

            }
            else if(bal->isCatched){
                  missCount++;
                  bal->hide();
                  delete bal;
                  balloons.removeOne(bal);
            }
            else {

                bal->setGeometry(bal->geometry().x(),bal->geometry().y()-speed,bal->geometry().width(),bal->geometry().height());
            }
        }
        balloonControlHigh();
        if(balloons.count() <balloonSize){
            createBalloon();
        }
        UIUpdate();

}
void MainWindow :: callEffect(Balloon *bal){

    bal->setPixmap(QPixmap ::fromImage(bombNow));
}
void MainWindow :: balloonControlHigh(){
    foreach (Balloon *bal, balloons) {
        if(bal->geometry().y()+bal->geometry().height() < 0){
            bal->isCatched=true;
        }
    }
}
void MainWindow :: updateInformation(){

}
void MainWindow :: resizeEvent(QResizeEvent *event){
    backGroundUpdate();
}
void MainWindow::backGroundUpdate(){
    QPixmap bkgnd("C:\\Users\\asus\\Documents\\QT\\Odev-3\\sky.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    ui->missLabel->setGeometry(ui->missLabel->height()/2,this->geometry().height()-ui->missLabel->height(),ui->missLabel->width(),ui->missLabel->height());
    ui->catchLabel->setGeometry(this->geometry().width()-ui->catchLabel->width(),this->geometry().height()-ui->catchLabel->height(),ui->catchLabel->width(),ui->catchLabel->height());
}
int MainWindow:: randomPoint(){

     int formX=this->geometry().width();
     int rnd;
     if(odd==0)
        rnd=(formX)-((rand()%(formX/100))*100);
     else
         rnd=(formX)-((rand()%(formX/100))*50);
     odd=1-odd;
     if(rnd<0)
         rnd*=-1;
     return rnd;
}
MainWindow::~MainWindow()
{
    delete ui;
}
