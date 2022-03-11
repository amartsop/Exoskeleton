# Three-finger Exoskeleton
This project presents a software solution for the three-finger exoskeleton 
project using the custom PCB SAMD21G18A. 
The software is responsible for reading the analog values produced by the Melexis sensors attached to the exoskeleton and printing them to the serial output for further processing.

<img src="./images/white_exoskeleton.svg" width="50%"/>

The board uses the SAMD21G18A QFN microcontroller, 
MCP3208 analogue to digital converters (ADCs). Each port on the microcontroller
(numbered 1-13 in Fig. 4b) allows receives two analog signals from the melexis sensors. These signals
are the sent from the ports to the 8 built-in analog pins of the microcontroller or to the analog pins
of the MCP3208. The mapping of the ports to the analog pins of the board or the ADCs is explained

<!-- ![This is the caption\label{mylabel}](./images/custom_board.svg) -->

<div class="row">
  <div class="column2">
    <img src="./images/custom_board.svg" style="width:100%">
  </div>
  <div class="column2">
    <img src="./images/custom_board.svg" style="width:100%">
  </div>
</div>

<style>
/* Three image containers (use 25% for four, and 50% for two, etc) */
.column2{
  float: left;
  width: 50.0%;
  padding: 5px;
}

/* Clear floats after image containers */
.row::after {
  content: "";
  clear: both;
  display: table;
}
</style>
