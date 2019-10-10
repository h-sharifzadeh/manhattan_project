#ifndef PID_H
#define PID_H

#include <cmath>

class PID {
public:
    explicit PID(double _kp = 0.0, double _ki = 0.0, double _kd = 0.0, double _maxSum = 10.0, double _minErr = 0.1)
    : kp(_kp), ki(_ki), kd(_kd), maxSum(_maxSum), minErr(_minErr), sum(0.0), last(0.0), lastOut(0.0) {
        sum = 0;
        last = 0;
    }

    ~PID() = default;;

    double execute(double err) {
        if(std::fabs(err) < minErr) sum = 0;
        else if( sum <= maxSum || maxSum == 0) sum += err;
        else sum = maxSum;
        lastOut = (kp * err) + (ki * sum) + (kd * (err - last));
        last = err;
        return lastOut;
    }
    double lastOut;
    double kp, ki, kd;
private:

    double sum;
    double last;
    const double maxSum, minErr;

};


#endif
