#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <chartwindow.h>
#include <QDebug>


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

    QByteArray chart_data;

    void connectSignalSlot();

public slots:
    void openChartWindow();
private slots:
    void on_btnReadChart_clicked();
};

#endif // MAINWINDOW_H
