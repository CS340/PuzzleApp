#include "customimagescreen.h"
#include "customimagebutton.h"
#include "mainmenu.h"

#include <QDir>
#include <QImageReader>
#include <QPushButton>
#include <QGridLayout>
#include <QScrollArea>
#include <QLabel>
#include <QDebug>

CustomImageScreen::CustomImageScreen(MainMenu *mm, MainWindow *mainWindow, QWidget *parent) : QWidget(parent)
{
    mainMenu = mm;
    this->mainWindow = mainWindow;
}

void CustomImageScreen::display(int screenWidth, int screenHeight)
{
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;

    //create GraphicsScene and GraphicsView
    QGraphicsScene *gScene = new QGraphicsScene(this);
    gView = new QGraphicsView(gScene);
    gView->setFixedSize(screenWidth, screenHeight);
    gScene->setBackgroundBrush(Qt::black);

    //create and setup overall layout
    QGridLayout *layout = new QGridLayout(gView);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    layout->setAlignment(Qt::AlignCenter);
    gView->setLayout(layout);

    //open directory to pictures folder
    QDir dir  = QDir(QDir::rootPath());
    dir.cd("sdcard");
    if(!dir.entryList().contains("Puzzle Pictures"))
        dir.mkdir("Puzzle Pictures");
    dir.cd("Puzzle Pictures");

    //get list of images in pictures folder
    QStringList files = dir.entryList();
    files.removeAt(0);
    files.removeAt(0);
    for(int i=0;i<files.size();i++)
        if(!(files[i].endsWith(".jpg") || files[i].endsWith(".jpeg") || files[i].endsWith(".png") || files[i].endsWith(".gif") || files[i].endsWith(".svg")))
            files.removeAt(i);

    if(files.size()>0)
    {
        //create and set up scrollArea for pictures
        QScrollArea *scrollArea = new QScrollArea();
        scrollArea->setBackgroundRole(QPalette::Window);
        layout->addWidget(scrollArea, 0, 0, 4, 1);

        //grid within the scrollArea
        QGridLayout *pics = new QGridLayout();
        pics->setContentsMargins(0,0,0,0);
        QWidget *holder = new QWidget();
        holder->setLayout(pics);
        scrollArea->setWidget(holder);

        //create buttons and put in grid
        for(int i=0; i<files.size()/3; i++){
            for(int j=0; j<3; j++){
                QString path(dir.absolutePath() + "/" + files[i*3+j]);
                QImageReader reader(path);
                reader.setScaledSize(QSize(screenWidth/3-1, screenHeight/5-1));
                QImage pic = reader.read();
                int picWidth = pic.width();
                int picHeight = pic.height();

                QPixmap pixmap = QPixmap::fromImage(pic);
                QIcon icon(pixmap);
                customImageButton *button = new customImageButton(path, icon);
                connect(button, SIGNAL(customImageButtonClicked(QString)), this, SLOT(customImageChosen(QString)));

                button->setIconSize(QSize(picWidth, picHeight));
                pics->addWidget(button,i,j);
            }
        }

        //set column/row sizes for pics
        for(int i=0;i<pics->rowCount();i++){
            if(i<pics->columnCount())
                pics->setColumnMinimumWidth(i,screenWidth/3);
            pics->setRowMinimumHeight(i,screenHeight/5);
        }

        //resize scroll area holder
        holder->resize(screenWidth*5.1/5.4, files.size()/3 *screenHeight *1/5);

    }

    else
    {
        QLabel *noPicWarning = new QLabel("No Pictures Detected\nTo use custom images, add them to\n \"/sdcard/Puzzle Pictures\"");
        layout->addWidget(noPicWarning,0,0);

    }

    for(int i=0; i<5; i++)
        layout->setRowMinimumHeight(i, screenHeight/5);


    //cancel button
    QPushButton *cancel = new QPushButton("Cancel", gView);
    layout->addWidget(cancel, 4, 0);
    connect(cancel, SIGNAL(clicked()), mainMenu, SLOT(cancel()));

    gView->show();
    this->show();
}

void CustomImageScreen::customImageChosen(QString path)
{
    qDebug() << "custom image chosen";
    MainMenu *mm = new MainMenu(path, mainWindow, mainWindow);
    mm->display(screenWidth, screenHeight);
}
