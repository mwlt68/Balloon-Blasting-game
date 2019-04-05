#include "balloon.h"
static QImage img("C:\\Users\\asus\\Documents\\QT\\Odev-3\\balloon.png");
Balloon::Balloon(QWidget *parent):QLabel(parent)
{
    setFrameShape(QFrame ::Box);
    setScaledContents(true);
    setFrameStyle(QFrame::NoFrame);
    setPixmap(QPixmap ::fromImage(img));
    show();

}
void Balloon::mousePressEvent(QMouseEvent * ev){
    this->isBombed=true;
}
