#ifndef LINEWIDGET_H
#define LINEWIDGET_H

#include "contentwidget.h"

class LineWidget : public ContentWidget
{
    Q_OBJECT
public:
    explicit LineWidget(QWidget *parent = nullptr);
};

#endif // LINEWIDGET_H
