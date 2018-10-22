#ifndef DATACHARTS_H
#define DATACHARTS_H

#include <QVector>
#include <QString>
#include <QDebug>


class DataCharts
{

public:
    typedef struct {
        double avg_speed;
        double rounds;
        double kp;
        double ki;
        double kpr;
        double i;
        double rpm;
        double period;
        double duty;
        double speed_min;
        double stall_on_start;
        double stall_when_run;
    } st_parameters_series_t;

    DataCharts();
    DataCharts(const QVector<double> &x, const QVector<double> &y);
    ~DataCharts();
    void setSeriesNo(int no);
    void setAllParameters(st_parameters_series_t *param_in);
    void setAvgSpeed(double data);
    void setRounds(double data);
    void setKp(double data);
    void setKi(double data);
    void setKpr(double data);
    void setI(double data);
    void setRpm(double data);
    void setPeriod(double data);
    void setDuty(double data);
    void setSpeedMin(double data);
    void setStallOnStart(double data);
    void setStallWhenRun(double data);
    void setPoint(double x, double y);
    int getSeriesNo();
    st_parameters_series_t getAllParameters();
    QString getAvgSpeed() const;
    QString getRounds() const;
    QString getKp() const;
    QString getKi() const;
    QString getKpr() const;
    QString getI() const;
    QString getRpm() const;
    QString getPeriod() const;
    QString getDuty()const;
    QString getSpeedMin() const;
    QString getStallOnStart() const;
    QString getStallWhenRun() const;
    QVector<double> getVecPointsX() const;
    QVector<double> getVecPointsY() const;

private:
    QVector<double> data_x, data_y;
    st_parameters_series_t st_param;
    int series_no;
};

#endif // DATACHARTS_H
