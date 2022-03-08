#pragma once

#include <Arduino.h>
#include <SPI.h>
#include "AnalogPort.h"
#include "Sensor.h"

/// Class ExoHandler
/**
 * This class handles both the sensors and the analog ports of the custom 
 * PCB. It incorporates functionality for the initialization of both and 
 * for handling and mapping the incoming analog measurements.
*/
class ExoHandler
{
public:
    /// Empty constructor.
    ExoHandler() {};

    /// Initialize exoskeleton handler.
    void initialize(void);

    /**
     * @brief Get the test pin. 
     * 
     * @return int Test pin.
     */
    int get_test_pin(void) { return m_test_pin; }

    /// Update measurements.
    void update_measurements(void);

    /// Print measurements
    void print_measurements(void);

public:
    /*********************** Debug functions *************************/

    /// Print analog sensor value.
    void print_analog_value(int sensor_id);

    /// Print angle sensor value.
    void print_angle_value(int sensor_id);

public:
    /// The total number of angles (or degrees of freedom) of the exoskeleton.
    static const int angles_num = 13;

    // Array containing the values of the angles (in degrees).
    float angles[angles_num];

public:
    /// The total number of sensors of the exoskeleton. 
    static const int sensors_num = 18;

    /// Sensors container (stored in struct to avoid passing array pointers around).
    /// It contains the sensor objects, defined in Sensor::.
    struct SensorsContainer
    {
        Sensor sensor[sensors_num];
    };

public:

    /// The total number of analog ports (we exclude port 13).
    static const int analog_ports_num = 12;

    /// Analog ports container. It contains the analog port objects, defined in
    ///AnalogPort::.
    struct AnalogPortsContainer
    {
        AnalogPort port[analog_ports_num];
    };

private:

    /// Initialize analog ports.
    void initialize_analog_ports(void);

    /// Initialize sensors.
    void initialize_sensors(void);

private:

    /// ADC chip select pin 1.
    const int m_adc_chip_select_pin1 = 4;

    /// ADC chip select pin 2.
    const int m_adc_chip_select_pin2 = 2;

    /// Test pin.
    const int m_test_pin = 3;

    /// ADC test pin.
    const int m_adc_test_pin = 16;

    /// Baudrate for serial communication.
    const int m_baudrate = 115200;

    /// Analog port container.
    AnalogPortsContainer m_analog_ports_container;

    // Sensors container.
    SensorsContainer m_sensors_container;

    /// Red sensor type boolean. See Sensor::initialize.
    bool m_red = 0;

    /// Green sensor type boolean. See Sensor::initialize.
    bool m_green = 1;
};