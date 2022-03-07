#pragma once

#include <Arduino.h>
#include <SPI.h>
#include "AnalogPort.h"
#include "Sensor.h"

class ExoHandler
{
public:
    ExoHandler(/* args */) {};

    // Initialize exohandler
    void initialize(void);

    // Get test pin
    int get_test_pin(void) { return m_test_pin; }

    // Update measurements
    void update_measurements(void);

    // Print measurements
    void print_measurements(void);

    
public:
    /*********************** Debug functions *************************/

    // Print analog sensor value
    void print_analog_value(int sensor_id);

    // Print angle sensor value
    void print_angle_value(int sensor_id);

public:
    // Number of angles
    static const int angles_num = 13;

    // Angle values
    float angles[angles_num];

public:
    // Number of sensors
    static const int sensors_num = 18;

    // Sensors container (stored in struct to avoid passing array pointers around)
    struct SensorsContainer
    {
        Sensor sensor[sensors_num];
    };

public:
    // Number of AnalogPorts
    static const int analog_ports_num = 12;

    // Analog ports container
    struct AnalogPortsContainer
    {
        AnalogPort port[analog_ports_num];
    };

private:

    // Initialize analog ports
    void initialize_analog_ports(void);


    // Initialize sensors
    void initialize_sensors(void);
private:

    // ADC chip select pins
    const int m_adc_chip_select_pin1 = 4;
    const int m_adc_chip_select_pin2 = 2;

    const int m_test_pin = 3;
    const int m_adc_test_pin = 16;

    const int m_baudrate = 115200;

    // Analog port container
    AnalogPortsContainer m_analog_ports_container;

    // Sensors container
    SensorsContainer m_sensors_container;

    // Sensor type
    bool m_red = 0;
    bool m_green = 1;
    
};