#include "layoutholder.h"

#include <QGridLayout>
#include <QWidget>

layoutHolder::layoutHolder(QGridLayout *layout) : QWidget()
{
    setLayout(layout);
}
