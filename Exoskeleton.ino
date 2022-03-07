#include "./include/ExoHandler.h"

// Define exoskeleton handler
ExoHandler exo_handler;

// Debugging parameters
bool debug_mode = 0;
bool measurement_mode = 0;

// Start setup function:
void setup() {

  // Initialize exoskeleton handler  
  exo_handler.initialize();
} 

// Start loop function:
void loop() {

  // Update measurements
  exo_handler.update_measurements();
  

  // Debugging
  if (debug_mode)
  {
    // Define id of the sensor to be read
    int sensor_id = 2;

    // Type of debugging (angle or analog value)
    measurement_mode ? exo_handler.print_analog_value(sensor_id) : 
      exo_handler.print_angle_value(sensor_id);
  }
  else{
    // Print angles 
    exo_handler.print_measurements();
  }

  // Write to test pin
  digitalWrite(exo_handler.get_test_pin(),
    !digitalRead(exo_handler.get_test_pin()));
}

