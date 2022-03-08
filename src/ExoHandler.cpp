#include "../include/ExoHandler.h"

/**
 * @brief This function configures the pins for the ADCs, sets the SPI communication
 * and setups the sensors and the analog ports.
 */
void ExoHandler::initialize(void)
{
    // Intialize chip selct pins
    pinMode(m_adc_chip_select_pin1, OUTPUT);
    pinMode(m_adc_chip_select_pin2, OUTPUT);
    pinMode(m_adc_test_pin, m_test_pin);

    // Set the select pins high initially:
    digitalWrite(m_adc_chip_select_pin1, HIGH);
    digitalWrite(m_adc_chip_select_pin2, HIGH);

    // Initialise SPI:
    SPI.begin();
    SPI.setBitOrder(MSBFIRST); // Not strictly needed but just to be sure.
    SPI.setDataMode(SPI_MODE0); // Not strictly needed but just to be sure.

    /* Set SPI clock divider to 16, therfore a 1 MhZ signal due
    to the maximum frequency of the ADC. */
    SPI.setClockDivider(SPI_CLOCK_DIV16);

    // Initialize SerialUSB communication
    SerialUSB.begin(m_baudrate);

    // Initialize analog ports
    initialize_analog_ports();

    // Initialize sensors
    initialize_sensors();
}

/**
 * @brief This method updates reads the analog port values for each 
 * port of the analog ports container and updats all the sensors.
 */
void ExoHandler::update_measurements(void)
{
    // Update analog inputs 
    for (size_t i = 0; i < analog_ports_num; i++)
    {
        m_analog_ports_container.port[i].update_port_values();
    }
    
    // Update sensors 
    for (size_t i = 0; i < sensors_num; i++)
    {
        // Get port id for sensor i    
        int port_id = m_sensors_container.sensor[i].get_port_id();

        // Get port values for port id 
        AnalogPort::AnalogPortValues analog_values =
            m_analog_ports_container.port[port_id - 1].get_port_values();
        
        // Update sensor 
        m_sensors_container.sensor[i].update(analog_values);
    }
}

/**
 * @brief This method set's all the results to the angles array and then 
 * prints them to the serial monitor. Calculations regarding MCP are 
 * performed here. The printing configuration is standarlized and should not 
 * be changed.
 */
void ExoHandler::print_measurements(void)
{
    // Angle theta_i_1
    angles[0] = 0.0;

    // Angle theta_i_2 (mcp)
    angles[1] = 90.0 + m_sensors_container.sensor[4].get_angle_value() - 
        (180-m_sensors_container.sensor[3].get_angle_value()) - 
        m_sensors_container.sensor[2].get_angle_value();

    // Angle theta_i_3
    angles[2] = m_sensors_container.sensor[1].get_angle_value();

    // Angle theta_i_3
    angles[3] = m_sensors_container.sensor[0].get_angle_value();

    // Angle theta_m_1
    angles[4] = 0.0;

    // Angle theta_m_2
    angles[5] = 0.0;

    // Angle theta_m_3
    angles[6] = 0.0;

    // Angle theta_m_4
    angles[7] = 0.0;

    // Angle theta_t_1
    angles[8] = 0.0;

    // Angle theta_t_2
    angles[9] = 0.0;

    // Angle theta_t_3
    angles[10] = 0.0;

    // Angle theta_t_4
    angles[11] = 0.0;

    // Angle theta_t_5
    angles[12] = 0.0;

    // Print angles
    for (int i = 0; i < angles_num; i++)
    {
        
        // Print angles
        SerialUSB.print(angles[i]);

        if (i == angles_num-1)
        {
            SerialUSB.println("");
        }
        else 
        {
            SerialUSB.print(",");
        }
    }
}

/**
 * @brief This is debugging function. It prints the analog value of a 
 * specific sensor.
 * @param sensor_id That's the sensor of which we want to print the values.
 */
void ExoHandler::print_analog_value(int sensor_id)
{
    float analog_val = m_sensors_container.sensor[sensor_id-1].get_analog_value();
    SerialUSB.print(analog_val);
    SerialUSB.println("");
}

/**
 * @brief This is debugging function. It prints the angle value of a 
 * specific sensor (in degrees).
 * @param sensor_id That's the sensor of which we want to print the values.
 */
void ExoHandler::print_angle_value(int sensor_id)
{
    float angle_val = m_sensors_container.sensor[sensor_id-1].get_angle_value();
    SerialUSB.print(angle_val);
    SerialUSB.println("");
}

/**
 * @brief This function initializes the senors one by one. To understand 
 * the inputs of the sensor initialization procedure, please refer 
 * to Sensor::initialize. As you can see the arguments of the sensor.initialize 
 * function are hardcoded. The user needs to adjust these values for 
 * every new exoskeleton, as the minimum and maximum analog values and the 
 * associated angles will change depending on the sensor's calibration.
 * The function seems a bit redundant due to the
 * "manual" initialization of each sensor. It can be done with the help of 
 * an external file, but this means that we need to store a file inside the 
 * microcontroller. 
 */
void ExoHandler::initialize_sensors(void)
{
    // Sensor 1
    m_sensors_container.sensor[0].initialize(1, m_red, 2, 1023, 4, 0, 90);

    // Sensor 2
    m_sensors_container.sensor[1].initialize(2, m_green, 1, 1023, 4, 0, 90);

    // Sensor 3
    m_sensors_container.sensor[2].initialize(3, m_red, 1, 770, 4, 0, 90);

    // Sensor 4
    m_sensors_container.sensor[3].initialize(4, m_green, 2, 4, 720, 0, 90);

    // Sensor 5
    m_sensors_container.sensor[4].initialize(5, m_green, 3, 570, 4, 0, 90);

    // Sensor 6
    m_sensors_container.sensor[5].initialize(6, m_green, 3, 1023, 4, 0, 90);

    // Sensor 7
    m_sensors_container.sensor[6].initialize(7, m_red, 5, 1023, 4, 0, 90);

    // Sensor 8
    m_sensors_container.sensor[7].initialize(8, m_green, 5, 1023, 4, 0, 90);

    // Sensor 9
    m_sensors_container.sensor[8].initialize(9, m_red, 6, 1023, 4, 0, 90);

    // Sensor 10
    m_sensors_container.sensor[9].initialize(10, m_green, 6, 1023, 4, 0, 90);

    // Sensor 11
    m_sensors_container.sensor[10].initialize(11, m_red, 7, 1023, 4, 0, 90);

    // Sensor 12
    m_sensors_container.sensor[11].initialize(12, m_green, 7, 1023, 4, 0, 90);

    // Sensor 13
    m_sensors_container.sensor[12].initialize(13, m_red, 9, 1023, 4, 0, 90);

    // Sensor 14
    m_sensors_container.sensor[13].initialize(14, m_green, 9, 1023, 4, 0, 90);

    // Sensor 15
    m_sensors_container.sensor[14].initialize(15, m_red, 10, 1023, 4, 0, 90);

    // Sensor 16
    m_sensors_container.sensor[15].initialize(16, m_green, 10, 1023, 4, 0, 90);

    // Sensor 17
    m_sensors_container.sensor[16].initialize(17, m_red, 11, 1023, 4, 0, 90);

    // Sensor 18
    m_sensors_container.sensor[17].initialize(18, m_green, 11, 1023, 4, 0, 90);
}

/**
 * @brief This function initializes the ports of the board one by 
 * one. To understand the inputs of the analog port initialization
 * procedure, please refer to AnalogPort::initialize.
 * Even though the function is hardcoded, it should not change as long as the 
 * custom board's wiring remains the same.
 * The function seems a bit redundant due to the
 * "manual" initialization of each port. It can be done with the help of 
 * an external file, but this means that we need to store a file inside the 
 * microcontroller. The arguments of the analog ports initialize functions 
 * are based on the table below
 *   \image html ports_mapping.png width=600px
 */
void ExoHandler::initialize_analog_ports(void)
{
    // Analog port x1 
    m_analog_ports_container.port[0].initialize(1, 0, (int) A0, (int) A1);

    // Analog port x2 
    m_analog_ports_container.port[1].initialize(2, 0, (int) A2, (int) A3);

    // Analog port x3 
    m_analog_ports_container.port[2].initialize(3, 0, (int) A4, (int) A5);

    /* Analog port x4
    ********************** Note ***********************
    A6 and A7 must be defined for the specific chip. For now
    know we DON'T USE them. Just give the values of x1 again. */
    m_analog_ports_container.port[3].initialize(4, 0, (int) A0, (int) A1);

    // Analog port x5
    m_analog_ports_container.port[4].initialize(5, 1, 0, 1, m_adc_chip_select_pin1);

    // Analog port x6
    m_analog_ports_container.port[5].initialize(6, 1, 2, 3, m_adc_chip_select_pin1);

    // Analog port x7
    m_analog_ports_container.port[6].initialize(7, 1, 4, 5, m_adc_chip_select_pin1);

    // Analog port x8 (green channel not working)
    m_analog_ports_container.port[7].initialize(8, 1, 6, 7, m_adc_chip_select_pin1);

    // Analog port x9
    m_analog_ports_container.port[8].initialize(9, 1, 0, 1, m_adc_chip_select_pin2);
    
    // Analog port x10
    m_analog_ports_container.port[9].initialize(10, 1, 2, 3, m_adc_chip_select_pin2);

    // Analog port x11
    m_analog_ports_container.port[10].initialize(11, 1, 4, 5, m_adc_chip_select_pin2);

    // Analog port x12
    m_analog_ports_container.port[11].initialize(12, 1, 6, 7, m_adc_chip_select_pin2);
}