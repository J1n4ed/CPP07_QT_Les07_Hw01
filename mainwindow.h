#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDataStream>
#include <QMessageBox>
#include <QtGlobal>
#include <QtConcurrent>
#include <algorithm>

///Подключаем все что нужно для графиков
#include <QLineSeries>
#include <QtCharts>
#include <QChartView>

#include "displayportview.h"

#define FD 1000.0 //частота дискретизации

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //Метод считывает данные из исходного файла
    QVector<uint32_t> ReadFile(QString path, uint8_t numberChannel);
    //Метод преобразует данные физические величины, В?
    QVector<double> ProcessFile(QVector<uint32_t> dataFile);
    //Метод ищет Максимумы
    QVector<double> FindMax(QVector<double> resultData);
    //Метод ищет минимумы
    QVector<double> FindMin(QVector<double> resultData);
    //Метод отображает результаты
    void DisplayResult(QVector<double> mins, QVector<double> maxs);

private slots:
    void on_pb_path_clicked();
    void on_pb_start_clicked();

signals:

    void signal_paint_chart(QSplineSeries * data, double, double);
    void signal_add_value(double, double);
    void signal_clear_value(QSplineSeries * data);

public slots:

    void recieve_shutdown();

private:
    Ui::MainWindow *ui;
    DisplayPortView *display;
    QString pathToFile = "";
    uint8_t numberSelectChannel = 0xEA;
    QSplineSeries *series;


    QVector<uint32_t> readData;
    QVector<double> procesData;
    QVector<double> mins, maxs;

    void paint_chart(QSplineSeries * data, double, double);
    void add_value(double, double);
    void clear_value(QSplineSeries * data);

};
#endif // MAINWINDOW_H
