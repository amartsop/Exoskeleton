#pragma once

#include "AnalogPort.h"

class Sensor
{

public:
    Sensor(/* args */) {};
    
    // Initialize sensor
    void initialize(int sensor_id, bool sensor_type, int sensor_port,
        float analog_min, float analog_max, float angle_min, float angle_max);
    
    // Get port id 
    int get_port_id(void) { return m_sensor_port; }

    // Update sensor
    void update(const AnalogPort::AnalogPortValues& port_values);

    // Get angle value
    float get_angle_value(void) { return m_sensor_angle_value; }

    // Get angle value
    float get_analog_value(void) { return m_sensor_analog_value; }
    
private:
    // Sensor analog value
    float m_sensor_analog_value;

    // Sensor angle value
    float m_sensor_angle_value;

private: 
    // Sensor id
    int m_sensor_id;

    // Sensor type (Red: 0, Green: 1)
    bool m_sensor_type;

    // Sensor port (which port is the sensor connected to)
    int m_sensor_port;

    // Minimum analog value
    float m_analog_min;

    // Maximum analog value
    float m_analog_max;

    // Minimum angle value
    float m_angle_min;

    // Maximum angle value
    float m_angle_max;
};
