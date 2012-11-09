#ifndef LAYOUTHOLDER_H
#define LAYOUTHOLDER_H

#include <QGridLayout>
#include <QWidget>

class layoutHolder : public QWidget
{
    Q_OBJECT

public:
    explicit layoutHolder(QGridLayout *layout);
};

#endif // LAYOUTHOLDER_H
