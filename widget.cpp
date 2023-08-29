#include "widget.h"
#include "linewidget.h"

#include <QApplication>
#include <QHBoxLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , m_listView(new QListView(this))
    , m_listModel(new QStringListModel(this))
    , m_contentArea(new QWidget(this))
{
    //m_exampleMap.insert(tr("Box Plot Chart"), BoxPlotChart);
    //m_exampleMap.insert(tr("Chart Themes"), ChartThemes);
    m_exampleMap.insert(tr("Line Chart"), LineChart);
    //m_exampleMap.insert(tr("Spline Chart"), SplineChart);

    QStringList examples = m_exampleMap.keys();
    std::sort(examples.begin(), examples.end());
    m_listModel->setStringList(examples);

    m_listView->setMaximumWidth(220);
    m_listView->setModel(m_listModel);
    m_listView->setCurrentIndex(m_listModel->index(0));
    m_listView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    setMinimumSize(800, 400);
    resize(1200, 600);

    auto layout = new QHBoxLayout(this);
    layout->addWidget(m_listView);
    layout->addWidget(m_contentArea);
    setLayout(layout);

    connect(m_listView->selectionModel(), &QItemSelectionModel::currentChanged, this,
            [this](const QModelIndex &index) {
                setActiveExample(m_exampleMap[m_listModel->data(index).toString()]);
            });

    setActiveExample(m_exampleMap[examples[0]]);

    setMouseTracking(true);

    qApp->setApplicationDisplayName(tr("Qt Charts Example Gallery"));
}

void Widget::resizeEvent(QResizeEvent *)
{
    m_activeWidget->resize(m_contentArea->size());
}

void Widget::setActiveExample(Example example)
{
    // We only keep one example alive at the time to save resources.
    // This also allows resetting the example by switching to another example and back.
    if (m_activeWidget) {
        m_activeWidget->setVisible(false);
        m_activeWidget->deleteLater();
    }

    switch (example) {
//    case BoxPlotChart:
//        m_activeWidget = new BoxPlotWidget(m_contentArea);
//        break;
//    case ChartThemes:
//        m_activeWidget = new ThemeWidget(m_contentArea);
//        break;
    case LineChart:
        m_activeWidget = new LineWidget(m_contentArea);
        break;
//    case SplineChart:
//        m_activeWidget = new SplineWidget(m_contentArea);
//        break;
    }

    m_activeWidget->load();
    m_activeWidget->resize(m_contentArea->size());
    m_activeWidget->setVisible(true);
}



Widget::~Widget()
{
}

