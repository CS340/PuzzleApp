#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "flickcharm.h"
#include "layoutholder.h"

#include <QDir>
#include <QImageReader>
#include <QPushButton>
#include <QGridLayout>
#include <QScrollArea>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::display(int screenWidth, int screenHeight)
{
    //create GraphicsScene and GraphicsView
    QGraphicsScene *gScene = new QGraphicsScene(this);
    gView = new QGraphicsView(gScene);
    gView->setFixedSize(screenWidth, screenHeight);
    gScene->setBackgroundBrush(Qt::black);

    //create and setup overall layout
    QGridLayout *layout = new QGridLayout(gView);
    for(int i=0; i<5; i++)
        layout->setRowMinimumHeight(i, screenHeight/5);
    layout->setContentsMargins(0,0,0,0);
    gView->setLayout(layout);

    //create and set up scrollArea for pictures
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setBackgroundRole(QPalette::Window);
    //scrollArea->setWidgetResizable(true);
    layout->addWidget(scrollArea, 0, 0, 4, 1);

    //grid within the scrollArea
    QGridLayout *pics = new QGridLayout();
    pics->setContentsMargins(0,0,0,0);
    layoutHolder *holder = new layoutHolder(pics);
    holder->resize(screenWidth, screenHeight *4/5); //<<<<----------------------use this to resize the scrolling area somehow!
    scrollArea->setWidget(holder);

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

    //create buttons and put in grid
    for(int i=0; i<files.size()/3; i++){
        for(int j=0; j<3; j++){
            QImageReader reader(dir.absolutePath() + "/" + files[i*3+j]);
            reader.setScaledSize(QSize(screenWidth/3-1, screenHeight/5-1));
            QImage pic = reader.read();
            int picWidth = pic.width();
            int picHeight = pic.height();

            QPixmap pixmap = QPixmap::fromImage(pic);
            QIcon icon(pixmap);
            QPushButton *button = new QPushButton(icon, "");

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

    //cancel button
    QPushButton *cancel = new QPushButton("Cancel", gView);
    layout->addWidget(cancel, 4, 0);

    //FlickCharm charm;
    //charm.activateOn(scrollArea);

    gView->show();
}

void MainWindow::setOrientation(ScreenOrientation orientation)
{
    Qt::WidgetAttribute attribute;
    switch (orientation) {
#if QT_VERSION < 0x040702
    // Qt < 4.7.2 does not yet have the Qt::WA_*Orientation attributes
    case ScreenOrientationLockPortrait:
        attribute = static_cast<Qt::WidgetAttribute>(128);
        break;
    case ScreenOrientationLockLandscape:
        attribute = static_cast<Qt::WidgetAttribute>(129);
        break;
    default:
    case ScreenOrientationAuto:
        attribute = static_cast<Qt::WidgetAttribute>(130);
        break;
#else // QT_VERSION < 0x040702
    case ScreenOrientationLockPortrait:
        attribute = Qt::WA_LockPortraitOrientation;
        break;
    case ScreenOrientationLockLandscape:
        attribute = Qt::WA_LockLandscapeOrientation;
        break;
    default:
    case ScreenOrientationAuto:
        attribute = Qt::WA_AutoOrientation;
        break;
#endif // QT_VERSION < 0x040702
    };
    setAttribute(attribute, true);
}

void MainWindow::showExpanded()
{
#if defined(Q_WS_SIMULATOR)
    showFullScreen();
#elif defined(Q_WS_MAEMO_5)
    showMaximized();
#else
    show();
#endif
}
