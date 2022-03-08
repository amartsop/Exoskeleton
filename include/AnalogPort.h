#pragma once

#include <SPI.h>

/// Class AnalogPort
/** This class defines the the ports that are placed on the custom PCB. Each
port has one unique ID (X1, ... X12), a type (0: Direct communication to the 
chip, 1: Indirect comminication (through the ADC).
*/
class AnalogPort
{
public:

    /// Empth constructor
    AnalogPort() {};

    /// This is a custom struct that stores the analog values coming
    /// to each port through the sensors. Since each port has 
    /// two channels (a Red and a Green), the struct stores the values 
    /// for both.
    struct AnalogPortValues 
    {
        /// Analog value for green port.
        int green_port_value;
        
        /// Analog value for red port.
        int red_port_value;
    };

    /* Initialize analog port. port_id is the unique id of the port.
    The port_type defines if there is a direct or
    inderect communication with the chip (0: Direct communication to
    the chip, 1: Indirect comminication (through the ADC). Port numbers for
    green and red port define the analog pin, while adc_chip_select is the 
    selection pin for the ADC circuit */
    /// Initialize the port object.
    void initialize(int port_id, int port_type, int green_port, int red_port, 
        int adc_chip_select = 0);

    /// Read port values.
    void update_port_values(void);

    /**
     * @brief Get the port values reaching the port.
     * 
     * @return AnalogPortValues Custom struct that contains the values at 
     * both channels.
     */
    AnalogPortValues get_port_values(void) { return m_analog_port_values; }

private:

    /// Port ID (1-12).
    int m_port_id;

    /// Port type.
    int m_port_type;

    /// Port number for the green chip.
    int m_green_port;

    // Port number for the red chip.
    int m_red_port;

    // ADC chip select.
    int m_adc_chip_select;

    // Analog port values.
    AnalogPortValues m_analog_port_values;

public:
    /* Function to read the ADC, accepts the channel to be read and
    the ADC to be used. */
    
    /// Read the ADC signal.
    static int readADC(int channel, int adcChipSelectPin);

};