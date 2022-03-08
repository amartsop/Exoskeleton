#include "../include//Sensor.h"

/**
 * @brief This function initializes the sensor based on the configuration 
 * made by ExoHandler::initialize_sensors. It stores a local copy of all
 * the sensor's properties to it's local member variables.
 * @param sensor_id The ID of the sensor.
 * @param sensor_type The sensor type (0 for Red and 1 for Green).
 * @param sensor_port The port in which the sensor is connected.
 * @param analog_min The minimum analog value that the sensor reads (this 
 * can be deducted by testing).
 * @param analog_max The maximum analog value that the sensor reads (this 
 * can be deducted by testing).
 * @param angle_min The intended minimum angle that the sensor is supposed to 
 * read in degrees.
 * @param angle_max The intended maximum angle that the sensor is supposed to 
 * read in degrees.
 */
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

/**
 * @brief The function updates the snesor analog and angle values based on the 
 * incoming analog measurements and its color.The analog value is mapped to 
 * the angle value with the help of Arduino's built-in "map" function.
 * 
 * @param port_values The values read at the port in which the sensor is 
 * connected.
 */
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
