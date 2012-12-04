#ifndef CUSTOMIMAGEBUTTON_H
#define CUSTOMIMAGEBUTTON_H

//AUTHORS: Matt Dumford

#include <QPushButton>

// the customImageButton is used the exact same way as a QPushButton, but it can keep track of the
// filepath for the image displayed. It sends a signal with this filepath when it is clicked.
class customImageButton : public QPushButton
{

Q_OBJECT

public:
   explicit customImageButton(QString p, const QIcon &icon, QWidget *parent = 0);
   explicit customImageButton();
   virtual ~customImageButton();
   QString getPath(); //getter for the filepath

private:
   QString path; //the filepath for the image displayed on the button

signals:
   void customImageButtonClicked(QString); //sends the filepath for the image for this button

private slots:
   //detects its own signal from qpushbutton and sends its own custom signal
   void onClick(){
       emit customImageButtonClicked(path);
   }
};

#endif // CUSTOMIMAGEBUTTON_H
