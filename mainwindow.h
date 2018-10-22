#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <datacharts.h>
#include <chartwindow.h>
#include <QDebug>
#include <qmath.h>
#include <QList>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ChartWindow *p_chart_window;

    QVector<double> chart_data;
    QList<DataCharts> chart_list;
    DataCharts *p_chart;
    DataCharts::st_parameters_series_t curr_param;

    void connectSignalSlot();

private slots:
    void openChartWindow();
    void readDataChart();
    void setCurrParameters(int i);
};

#endif // MAINWINDOW_H
