//AUTHOR: Matt Dumford

#include "customimagebutton.h"

// the customImageButton is used the exact same way as a QPushButton, but it can keep track of the
// filepath for the image displayed. It sends a signal with this filepath when it is clicked.
customImageButton::customImageButton(QString p, const QIcon &icon, QWidget *parent) : QPushButton(icon, "", parent)
{
   qDebug("NEW_CUSTOMIMAGEBUTTON");
   path = p;

   //connect the QPushButton signal to the slot that sends the custom signal
   QObject::connect(this, SIGNAL(clicked()), this, SLOT(onClick()));
}

customImageButton::customImageButton()
{

}

customImageButton::~customImageButton()
{

}

QString customImageButton::getPath()
{
   return this->path;
}
