#include "../include/AnalogPort.h"


// Initialize analog port
void AnalogPort::initialize(int port_id, int port_type, int green_port,
  int red_port, int adc_chip_select)
{
  // Store port configuration to member variables
  m_port_id = port_id;
  m_port_type = port_type;  
  m_red_port = red_port;
  m_green_port = green_port;
  m_adc_chip_select = adc_chip_select;
}

// Read port values
void AnalogPort::update_port_values(void)
{
  // Read analog values in case of an ADC chip input (port_type=1)
  if (m_port_type)
  {
    // Read green value
    m_analog_port_values.green_port_value = readADC(m_green_port,
      m_adc_chip_select);
  
    // Read red value
    m_analog_port_values.red_port_value = readADC(m_red_port,
      m_adc_chip_select);
  }
  else // Read values directly from the chip
  {
    // Read green value
    m_analog_port_values.green_port_value = analogRead(m_green_port);

    // Read red value
    m_analog_port_values.red_port_value = analogRead(m_red_port);
  }

}

/* Function to read the ADC, accepts the channel to be read and the ADC to
be used. */
int AnalogPort::readADC(int channel, int adcChipSelectPin)
{
  /* Sets default Primary ADC Address register B00000110, This is a default
  address setting, the third LSB is set to one to start the ADC. The second
  LSB is to set the ADC to single ended mode, the LSB is for D2 address bit,
  for this ADC its a "Don't Care" bit. */ 
  byte adcPrimaryRegister = 0b00000110;      

  // b00000111 Isolates the three LSB.
  byte adcPrimaryRegisterMask = 0b00000111;  

  // b00001111 isolates the 4 LSB for the value returned.
  byte adcPrimaryByteMask = 0b00001111;      
  byte adcD2Config = channel >> 2;

  /* Ensures the D2 bit of the primary register corresponds to the bit as
  determined by the channel. */
  byte adcPrimaryConfig = adcPrimaryRegister | adcD2Config ; 

  /* Ensures the adc register is limited to the mask and assembles the
  configuration byte to send to ADC. */
  adcPrimaryConfig &= adcPrimaryRegisterMask; 
  byte adcSecondaryConfig = channel << 6;

  // Disable interupts to prepare to send address data to the ADC.
  noInterrupts(); 

  // Take the Chip Select pin low to select the ADC.
  digitalWrite(adcChipSelectPin, LOW); 

  // Send in the primary configuration address byte to the ADC.
  SPI.transfer(adcPrimaryConfig); 

  // Read the primary byte, also sending in the secondary address byte.
  byte adcPrimaryByte = SPI.transfer(adcSecondaryConfig); 

  // Read the secondary byte, also sending 0 as this doesn't matter.
  byte adcSecondaryByte = SPI.transfer(0x00); 

  // Take the Chip Select pin high to de-select the ADC.
  digitalWrite(adcChipSelectPin, HIGH); 

  // Enable interupts.
  interrupts(); 

  // Limits the value of the primary byte to the 4 LSB:
  adcPrimaryByte &= adcPrimaryByteMask; 

  /* Shifts the 4 LSB of the primary byte to become the 4 MSB of the 12
  bit digital value, this is then ORed to the secondary byte value that
  holds the 8 LSB of the digital value. */
  int digitalValue = (adcPrimaryByte << 8) | adcSecondaryByte; 

  // Returns the value from the function
  return digitalValue;  
}