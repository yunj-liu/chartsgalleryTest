#ifndef CONTENTWIDGET_H
#define CONTENTWIDGET_H

#include <QWidget>
#include <QChart>  //without using QT_FORWARD_DECLARE_CLASS instead of using #include <QChart> replace
#include <QChartView>

class ContentWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ContentWidget(QWidget *parent = nullptr);
    void load();

protected:
    virtual bool doLoad();
    void resizeEvent(QResizeEvent *) override;
    void createDefaultChartView(QChart *chart);
    QChartView *defaultChartView() const { return m_defaultChartView; }
    void setDefaultChartView(QChartView *view);

    QString m_loadError;

private:
    QChartView *m_defaultChartView = nullptr;
    bool m_loaded = false;


signals:

};

#endif // CONTENTWIDGET_H
