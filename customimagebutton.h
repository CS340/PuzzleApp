#ifndef CUSTOMIMAGEBUTTON_H
#define CUSTOMIMAGEBUTTON_H

#include <QPushButton>

class customImageButton : public QPushButton
{

Q_OBJECT

public:
   explicit customImageButton(QString p, const QIcon &icon, QWidget *parent = 0);
   explicit customImageButton();
   virtual ~customImageButton();
   QString getPath();

private:
   QString path;

signals:
   void customImageButtonClicked(QString);

private slots:
   void onClick(){
       //qDebug("CUSTOMIMAGEBUTTON_CLICK");
       emit customImageButtonClicked(path);
   }
};

#endif // CUSTOMIMAGEBUTTON_H
