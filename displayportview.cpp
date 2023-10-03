#include "displayportview.h"
#include "ui_displayportview.h"

DisplayPortView::DisplayPortView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DisplayPortView)
{
    ui->setupUi(this);
    ui->pb_close->setText("Закрыть программу");
    ui->pb_close->setStyleSheet("QPushButton {font-size: 18pt; font-weight: bold}");

    layout = new QGridLayout();

    axisX = new QValueAxis(this);
    axisY = new QValueAxis(this);

    axisX->setTitleText("Ось X (Время)");

    axisY->setTitleText("Ось Y (Значение)");

    chart = new QChart();
    chart->setTitle("Data Spline Chart");
    chart->legend()->setVisible(true);

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->viewport->setRenderHint(QPainter::Antialiasing);
    ui->viewport->setLayout(layout);
    layout->addWidget(chartView);
    chartView->show();
}

DisplayPortView::~DisplayPortView()
{
    delete ui;
    delete chart;
    delete chartView;
    delete layout;
}

void DisplayPortView::on_pb_close_clicked()
{
    shutdown();
}

// Definition for chart painting on signal get
void DisplayPortView::recieve_paint_graph(QSplineSeries * data, double min, double max)
{
    if (switchKey)
    {
        chart->removeSeries(data);

        data->detachAxis(axisX);
        data->detachAxis(axisY);
    }

    axisY->setMax(max);
    axisY->setMin(min);

    if (switchKey)
    {
        data->attachAxis(axisX);
        data->attachAxis(axisY);

        chart->addSeries(data);
    }

    if ( ! switchKey )
    {
        axisX->setMin(0);
        axisX->setMax(1000);
        data->attachAxis(axisX);
        data->attachAxis(axisY);
        chart->addSeries(data);
        switchKey = true;
    }

    emit axisY->maxChanged(max);
    emit axisY->minChanged(min);
    emit axisX->maxChanged(max);
    emit axisX->minChanged(min);

    // chart->update();
    chartView->update();
}

void DisplayPortView::recieve_add_value(double x, double y)
{
    ui->te_params->append("Point: " + QString::number(x) + ':' + QString::number(y));
}

void DisplayPortView::recieve_clear_value(QSplineSeries * data)
{
    ui->te_params->clear();
    data->clear();
}

void DisplayPortView::shutdown()
{
    emit signal_shutdown();
}
