#include "win_menu.h"
#include "mainmenu.h"

#include <QSize>
#include <QFont>
#include <QPushButton>
#include <QDebug>

win_menu::win_menu(MainWindow *mainWindow, QWidget *parent) : QWidget(parent)
{
    this->mainWindow = mainWindow;
}

void win_menu::display (int sw, int sh)
{
    screen_height = sh;
    screen_width = sw;

    QSize size(screen_width, screen_width);
    //QMovie is required for animated pic
    QMovie *win_movie = new QMovie(":/animated-fireworks.gif");
    win_movie->setScaledSize(size);

    //Sets up the moving pic into the label
    QLabel *win_pic = new QLabel(this);
    win_pic->setMovie(win_movie);
    win_pic->resize(size);
    win_movie->start();

    QLabel *you_win_label = new QLabel("Congratulations, \nyou win!");
    you_win_label->setFixedWidth(screen_width);
    QFont you_win_font("Helvectica", 16, QFont::Bold);
    you_win_label->setFont(you_win_font);
    you_win_label->setAlignment(Qt::AlignCenter);

    QFont buttonFont("Helvetica", 13);
    QPushButton *main_menu = new QPushButton("Main Menu");
    main_menu->setFont(buttonFont);
    QPushButton *quit = new QPushButton("Quit");
    quit->setFont(buttonFont);

    //Puts all the label into a layout
    QGridLayout *win_layout = new QGridLayout;
    win_layout->addWidget(win_pic, 0, 0, 1, 2);
    win_layout->addWidget(you_win_label, 1, 0, 1, 2);
    win_layout->addWidget(main_menu, 2, 0, 1, 1);
    win_layout->addWidget(quit, 2, 1, 1, 1);

    //Puts the layout into a widget for future use
    QWidget *win_widget = new QWidget;
    win_widget->setLayout(win_layout);

    //connect buttons
    connect(main_menu, SIGNAL(clicked()), this, SLOT(mainMenuClicked()));
    connect(quit, SIGNAL(clicked()), this, SLOT(quitClicked()));

    win_widget->show();
    win_widget->raise();
}

void win_menu::mainMenuClicked()
{
    qDebug() << "main menu clicked.";
    MainMenu *mm = new MainMenu(mainWindow, mainWindow);
    mm->display(screen_width, screen_height);
}

void win_menu::quitClicked()
{
    qDebug() << "quit clicked.";
    exit(EXIT_FAILURE);
}

void win_menu::restart()
{

}
