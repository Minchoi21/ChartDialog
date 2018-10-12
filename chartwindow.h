#ifndef CHARTWINDOW_H
#define CHARTWINDOW_H

#include <QDialog>
#include <QTimer>
#include "qcustomplot.h"

namespace Ui {
class ChartWindow;
}

class ChartWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ChartWindow(QWidget *parent = 0);
    ~ChartWindow();
    void setupChart();

private slots:
    void on_btnCloseChart_clicked();

private:
    Ui::ChartWindow *ui;
    void drawSpeedRotationChart(QCustomPlot *customPlot);
};

#endif // CHARTWINDOW_H
