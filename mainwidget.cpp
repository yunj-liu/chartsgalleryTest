#include "mainwidget.h"
#include "linewidget.h"

#include <QApplication>  //qApp need this include
#include <QHBoxLayout>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , m_listView(new QListView(this))
    , m_listModel(new QStringListModel(this))
    , m_contentArea(new QWidget(this))
{
    //m_exampleMap.insert(tr("Box Plot Chart"), BoxPlotChart);
    m_exampleMap.insert(tr("Chart Themes"), ChartThemes);
    m_exampleMap.insert(tr("Line Chart"), LineChart);  //tr return type is QString
    //m_exampleMap.insert(tr("Spline Chart"), SplineChart);

    QStringList examples = m_exampleMap.keys();  //QStringList is QList<QString>, m_exampleMap type is QHash<QString, Example>
    std::sort(examples.begin(), examples.end());
    m_listModel->setStringList(examples);  //Sets the model's internal string list to strings. The model will notify any attached views that its underlying data has changed.

    m_listView->setMaximumWidth(220);  //the QListView in left of window, width is 220
    m_listView->setModel(m_listModel); //set the model for the view to present. model & it's attached view
    m_listView->setCurrentIndex(m_listModel->index(0));  //the param's type is QModelIndex
    m_listView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    setMinimumSize(800, 400);  // MainWidget's minimum width and height
    resize(1200, 600);  // the MainWidget's init width and height in program startup

    auto layout = new QHBoxLayout(this);
    layout->addWidget(m_listView);  //QHBoxLayout, horizontal. m_listView is QListView.
    layout->addWidget(m_contentArea);  // two part, left and right in horizon. m_contentArea is QWidget
    setLayout(layout); //MainWidget->layout: include m_listView(QListView) & m_contentArea(QWidget)

    /*
    connect proto:
    template<typename PointerToMemberFunction>
    static QMetaObject::Connection connect(const QObject *sender, PointerToMemberFunction signal, const QObject *receiver, PointerToMemberFunction method, Qt::ConnectionType type = Qt::AutoConnection);

    template<typename PointerToMemberFunction, typename Functor>
    static QMetaObject::Connection connect(const QObject *sender, PointerToMemberFunction signal, Functor functor);

    template<typename PointerToMemberFunction, typename Functor>
    static QMetaObject::Connection connect(const QObject *sender, PointerToMemberFunction signal, const QObject *context, Functor functor, Qt::ConnectionType type = Qt::AutoConnection);

    The purpose of this function is to associate the signal in the sender object with the member slot function in the receiver.
    The parameters of the signal function are passed directly to the slot function.
    The number of parameters of the signal function must be greater than the number of parameters of the slot function,
    and the parameters of the signal function are passed in order

    m_listView->selectionModel() type is QItemSelectionModel *
    the signal function currentChanged has two parameters: void currentChanged(const QModelIndex &current, const QModelIndex &previous);
    the 2nd parameter of function connect is pointer, so use reference &QItemSelectionModel::currentChanged

    Lambda function :
    [capture](parameters)->return-type{body}
    [capture](parameters){body}
    [this](const QModelIndex &index) is Lambda function, it's slot function, has one parameter. it will receive signal function's first parameter.
    [this] —— means capture this pointer, you can use this->setActiveExample, this->m_exampleMap, this->m_listModel, the below is omit this->
    */
    connect(m_listView->selectionModel(), &QItemSelectionModel::currentChanged, this,
            [this](const QModelIndex &index) {
                setActiveExample(m_exampleMap[m_listModel->data(index).toString()]);  //data is QVariant type, m_listModel is QStringListModel
            }); //param of setActiveExample is Example

    setActiveExample(m_exampleMap[examples[0]]);  //examples is QStringList, m_exampleMap is QHash<QString, Example>

    setMouseTracking(true);

    qApp->setApplicationDisplayName(tr("Qt Charts Example Gallery"));
    qApp->setWindowIcon(QIcon(":/main.ico"));  //icon in topleft of main window. the icon file in the qrc

}

void MainWidget::resizeEvent(QResizeEvent *)
{
    m_activeWidget->resize(m_contentArea->size());
}

void MainWidget::setActiveExample(Example example) //constructor call once, and being slot function waiting for CurrentChanged signal
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
    case ChartThemes:
        m_activeWidget = new ThemeWidget(m_contentArea);
        break;
    case LineChart:  //m_contentArea is QWidget, being the parent passing to the LineWidget
        m_activeWidget = new LineWidget(m_contentArea);  //m_activeWidget is ContentWidget, LineWidget derived from ContentWidget
        break;               //parent: m_contentArea(QWidget)->m_contentArea(ConetentWidget)->m_activeWidget(LineWidget)
//    case SplineChart:
//        m_activeWidget = new SplineWidget(m_contentArea);
//        break;
    }

    m_activeWidget->load();
    m_activeWidget->resize(m_contentArea->size());
    m_activeWidget->setVisible(true);
}


MainWidget::~MainWidget()
{
}

