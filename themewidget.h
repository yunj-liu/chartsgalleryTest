﻿#ifndef THEMEWIDGET_H
#define THEMEWIDGET_H

#include "contentwidget.h"
#include <QChart>
#include <QChartView>
typedef QPair<QPointF, QString> Data;
typedef QList<Data> DataList;
typedef QList<DataList> DataTable;

QT_FORWARD_DECLARE_CLASS(Ui_ThemeWidgetForm);  //the name 'ThemeWidgetForm' is pick up when design ui,*.ui open with plain editor can watch it


class ThemeWidget: public ContentWidget
{
    Q_OBJECT
public:
    explicit ThemeWidget(QWidget *parent = nullptr);
    ~ThemeWidget();

private slots:
    void updateUI();

private:
    DataTable generateRandomData(int listCount, int valueMax, int valueCount) const;
    void populateThemeBox();
    void populateAnimationBox();
    void populateLegendBox();
    void connectSignals();  //No implement, instead of use themewidget.ui
    QChart *createAreaChart() const;
    QChart *createBarChart(int valueCount) const;
    QChart *createPieChart() const;
    QChart *createLineChart() const;
    QChart *createSplineChart() const;
    QChart *createScatterChart() const;

private:
    int m_listCount;
    int m_valueMax;
    int m_valueCount;
    QList<QChartView *> m_charts;
    DataTable m_dataTable;

    Ui_ThemeWidgetForm *m_ui;
};

#endif // THEMEWIDGET_H
