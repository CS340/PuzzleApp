#include "customimagebutton.h"

customImageButton::customImageButton(QString p, const QIcon &icon, QWidget *parent) : QPushButton(icon, "", parent)
{
   qDebug("NEW_CUSTOMIMAGEBUTTON");
   path = p;
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
