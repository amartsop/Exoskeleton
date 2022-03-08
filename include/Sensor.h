#pragma once

#include "AnalogPort.h"

/// Class Sensor
/**
 * This class handles the models the Sensor object and creates the interface
 * for the translating raw sensor values to joint angles.
*/

class Sensor
{

public:
    /// Empty constructor.
    Sensor() {};
    
    /// Initialize sensor.
    void initialize(int sensor_id, bool sensor_type, int sensor_port,
        float analog_min, float analog_max, float angle_min, float angle_max);
    
    /**
     * @brief Returns the ID of the port in which the sensor is connected.
     * 
     * @return int The port's ID.
     */
    int get_port_id(void) { return m_sensor_port; }

    /// Update sensor.
    void update(const AnalogPort::AnalogPortValues& port_values);

    /**
     * @brief Returns the angle value of the sensor in degrees.
     * 
     * @return float Angle value in degrees.
     */
    float get_angle_value(void) { return m_sensor_angle_value; }

    /**
     * @brief Returns the analog value of the sensor.
     * 
     * @return float The analog value of the sensor.
     */
    float get_analog_value(void) { return m_sensor_analog_value; }
    
private:
    /// Sensor analog value.
    float m_sensor_analog_value;

    /// Sensor angle value.
    float m_sensor_angle_value;

private: 
    /// Sensor id.
    int m_sensor_id;

    /// Sensor type (Red: 0, Green: 1).
    bool m_sensor_type;

    /// Sensor port (which port is the sensor connected to)
    int m_sensor_port;

    /// Minimum analog value.
    float m_analog_min;

    /// Maximum analog value.
    float m_analog_max;

    /// Minimum angle value.
    float m_angle_min;

    /// Maximum angle value
    float m_angle_max;
};