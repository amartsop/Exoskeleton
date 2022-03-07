#pragma once

#include <SPI.h>

/** This class defines the the ports that are placed on the BoardPCB. Each
port has one unique ID (X1, ... X12), a type (0: Direct communication to the 
chip, 1: Indirect comminication (through the ADC).
*/

class AnalogPort
{
public:

    AnalogPort(/* args */) {};

    // This struct stores the values for the red and green analog pins
    struct AnalogPortValues 
    {
        // Analog value for green port
        int green_port_value;
        
        // Analog value for red port
        int red_port_value;
    };

    /* Initialize analog port. port_id is the unique id of the port.
    The port_type defines if there is a direct or
    inderect communication with the chip (0: Direct communication to
    the chip, 1: Indirect comminication (through the ADC). Port numbers for
    green and red port define the analog pin, while adc_chip_select is the 
    selection pin for the ADC circuit */
    void initialize(int port_id, int port_type, int green_port, int red_port, 
        int adc_chip_select = 0);

    // Read port values
    void update_port_values(void);

    // Get port values
    AnalogPortValues get_port_values(void) { return m_analog_port_values; }

private:

    // Port ID 
    int m_port_id;

    // Port type
    int m_port_type;

    // Port number for the green chip
    int m_green_port;

    // Port number for the red chip
    int m_red_port;

    // ADC chip select
    int m_adc_chip_select;

    // Analog port values
    AnalogPortValues m_analog_port_values;

public:
    /* Function to read the ADC, accepts the channel to be read and
    the ADC to be used. */
    static int readADC(int channel, int adcChipSelectPin);

};