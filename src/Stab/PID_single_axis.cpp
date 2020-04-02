#include "PID_single_axis.h"

void PID_Single_Axis::integralWindup()
{
    for (int i = 0; i < 3; i++)
    {
        if (error_i > max_integral)
        {
            error_i = max_integral;
        }
        else if (error_i < -max_integral)
        {
            error_i = -max_integral;
        }
    }
}

void PID_Single_Axis::doFilter()
{
    float error_d_last = 0;
    error_d = (error_d_last * w0Te + error_d) / (w0Te + 1);

    // apply a windup on derivative filter to prevent excesive reaction
    if (error_d > max_integral)
    {
        error_d = max_integral;
    }
    else if (error_d < -max_integral)
    {
        error_d = -max_integral;
    }
}

float PID_Single_Axis::mapValue(float in_val, float in_min, float in_max, float out_min, float out_max)
{
    float out_val = (out_max - out_min) / (in_max - in_min) * (in_val - in_min) + out_min;
    return out_val;
}

PID_Single_Axis::PID_Single_Axis()
{
    cout << "[ PID Single Axis ] : Initialized\n";
}

void PID_Single_Axis::setPID(float in_G, float in_Kp, float in_Kd, float in_Ki)
{
    /// G, Kp, Kd, Ki
    G = in_G;
    Ki = in_Ki;
    Kp = in_Kp;
    Kd = in_Kd;
}

void PID_Single_Axis::setK(int kp, int kd, int ki)
{
    bool enabled = false;
    if (enabled)
    {
        Kp = mapValue(kp, 922, 2077, 0, 4);
        Kd = mapValue(kd, 922, 2077, 0, 1);
        Ki = mapValue(ki, 921, 2077, 0, 1);
    }
    //  Kp[1] = mapValue(kp, 1000, 2000, 0, 100);
    //  Kd[1] = mapValue(kd, 1000, 2000, 0, 100);
    //  Ki[1] = mapValue(ki, 1000, 2000, 0, 100);
}

float PID_Single_Axis::update(float command, float feedback, float dt, float *pid_debug)
{
    float output = 0;

    error_p = command - feedback;
    error_d = (error_p - error_p_last) / dt;
    error_i += error_p * dt;

    //integralWindup();  // integral windup of i term
    //  doFilter(); // filter in derrivative term

    error_p_last = error_p;

    pid_debug[0] = G * Kp * error_p;
    pid_debug[1] = G * Kd * error_d;
    pid_debug[2] = G * Ki * error_i;

    output = G * (Kp * error_p) + (Kd * error_d) + (Ki * error_i);
    return output;
}

float PID_Single_Axis::update(float command, float feedback, float dt)
{
    float output = 0;

    error_p = command - feedback;
    error_d = (error_p - error_p_last) / dt;
    error_i += error_p * dt;

    //integralWindup();  // integral windup of i term
    //  doFilter(); // filter in derrivative term

    error_p_last = error_p;

    output = G * (Kp * error_p) + (Kd * error_d) + (Ki * error_i);
    return output;
}

void PID_Single_Axis::displayK()
{
    cout << "kp : " << Kp << " " << Kd << " " << Ki << "\n";
}