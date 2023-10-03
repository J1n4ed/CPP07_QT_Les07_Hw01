#ifndef DISPLAYPORTVIEW_H
#define DISPLAYPORTVIEW_H

#include <QDialog>
#include <QWidget>
#include <QtCharts>
#include <QChartView>

namespace Ui {
class DisplayPortView;
}

class DisplayPortView : public QDialog
{
    Q_OBJECT

public:
    explicit DisplayPortView(QWidget *parent = nullptr);
    ~DisplayPortView();

private slots:

    void on_pb_close_clicked();

public slots:

    void recieve_paint_graph(QSplineSeries * data, double, double);
    void recieve_add_value(double, double);
    void recieve_clear_value(QSplineSeries * data);

signals:

    void signal_shutdown();

private:
    Ui::DisplayPortView *ui;
    QChartView *chartView;
    QChart *chart;
    QGridLayout *layout;
    QValueAxis *axisX;
    QValueAxis *axisY;
    bool switchKey = false;

    void shutdown();
};

#endif // DISPLAYPORTVIEW_H
