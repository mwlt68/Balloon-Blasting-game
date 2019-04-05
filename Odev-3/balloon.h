#ifndef BALLOON_H
#define BALLOON_H
#include<QLabel>
#include<QMessageBox>

class Balloon:public QLabel
{
public:
    Balloon();
    int id;
    bool isBombed=false,isCatched=false,isFalling=false;
public slots:
    Balloon(QWidget *parent);
    void mousePressEvent(QMouseEvent *ev);
};

#endif // BALLOON_H
