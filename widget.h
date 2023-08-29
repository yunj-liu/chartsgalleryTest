#ifndef WIDGET_H
#define WIDGET_H

#include <QHash>
#include <QWidget>

#include <QListView>  // without using QT_FORWARD_DECLARE_CLASS instead of using #include
#include <QStringListModel>

#include "contentwidget.h"  //without using 'class ContentWidget', it's equivalent to QT_FORWARD_DECLARE_CLASS

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void resizeEvent(QResizeEvent *) override;

private:
    enum Example{
        //BoxPlotChart,
        //ChartThemes,
        //LineChart,
        //SplineChart
        LineChart
    };

    void setActiveExample(Example example);

    QListView *m_listView = nullptr;
    QStringListModel *m_listModel = nullptr;
    QWidget *m_contentArea = nullptr;
    ContentWidget *m_activeWidget = nullptr;
    QHash<QString, Example> m_exampleMap;

};
#endif // WIDGET_H
