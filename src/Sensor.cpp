#include "../include//Sensor.h"

// Initialize sensor
void Sensor::initialize(int sensor_id, bool sensor_type, int sensor_port,
    float analog_min, float analog_max, float angle_min, float angle_max)
{
    // Get sensor_id
    m_sensor_id = sensor_id;
    
    // Get sensor type
    m_sensor_type = sensor_type;
    
    // Get sensor port
    m_sensor_port = sensor_port;
    
    // Get analog min
    m_analog_min = analog_min;
    
    // Get analog max
    m_analog_max = analog_max;
    
    // Get angle min
    m_angle_min = angle_min;

    // Get angle max
    m_angle_max = angle_max;
}

void Sensor::update(const AnalogPort::AnalogPortValues& port_values)
{
    // Get sensor value depending on its color
    if (m_sensor_type)
    {
        m_sensor_analog_value = (float) port_values.green_port_value;
    }
    else
    {
        m_sensor_analog_value = (float) port_values.red_port_value;     
    }

    // Convert sensor value to degrees
    m_sensor_angle_value = map(m_sensor_analog_value, m_analog_min,
        m_analog_max, m_angle_min, m_angle_max);
}
