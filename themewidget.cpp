#include "themewidget.h"
#include "ui_themewidget.h"  //name 'themewidget' is the *.ui name

#include <QRandomGenerator>

ThemeWidget::ThemeWidget(QWidget *parent):
    ContentWidget(parent),  //contentwidget.h have been included in themewidget.h
    m_listCount(3),
    m_valueMax(10),
    m_valueCount(7),
    m_dataTable(generateRandomData(m_listCount, m_valueMax, m_valueCount)),
    m_ui(new Ui_ThemeWidgetForm)
{
    m_ui->setupUi(this);
    populateThemeBox();
    populateAnimationBox();
    populateLegendBox();

    //create charts

    QChartView *chartView;

    chartView = new QChartView(createAreaChart(), this);
    m_ui->gridLayout->addWidget(chartView, 1, 0);  //add Layout property for Widget in ui designer
    m_charts << chartView;

    chartView = new QChartView(createPieChart(), this);
    // Funny things happen if the pie slice labels do not fit the screen, so we ignore size policy
    chartView->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    m_ui->gridLayout->addWidget(chartView, 1, 1);
    m_charts << chartView;
}

ThemeWidget::~ThemeWidget()
{
    delete m_ui;
}

DataTable ThemeWidget::generateRandomData(int listCount, int valueMax, int valueCount) const
{
    DataTable dataTable;

    // generate random data
    for (int i(0); i < listCount; i++) {  //the default value of listCount is 3, valueMax is 10, valueCout is 7
        DataList dataList;
        qreal yValue(0);
        for (int j(0); j < valueCount; j++) { //double QRandomGenerator::bounded(double highest), Generates one random double in the range between 0 (inclusive) and highest (exclusive).This function is equivalent to and is implemented as: return generateDouble() * highest;
            yValue = yValue + QRandomGenerator::global()->bounded(valueMax / (qreal) valueCount);  //double QRandomGenerator::generateDouble(), Generates one random qreal in the canonical range [0, 1) (that is, inclusive of zero and exclusive of 1).
            QPointF value((j + QRandomGenerator::global()->generateDouble()) * ((qreal) m_valueMax / (qreal) valueCount),
                          yValue);
            QString label = "Slice " + QString::number(i) + ":" + QString::number(j);
            dataList << Data(value, label);
        }
        dataTable << dataList;
    }

    return dataTable;
}
