//define the pin for push button and the LED (in this case, we are using built-in LED)
//we are declaring the pin numbers as contants with the data-type unsigned 8-bit integer
//using unsigned 8-bit integer ensures that the constant occupies only 1-byte of memory which is sufficient for pin number when resources are limited
//using unsigned 8-bit integer as data type ensures that the value is between 0 and 255
const uint8_t BTN_PIN = 2;
const uint8_t LED_PIN = 13;

// Declare buttonPrevState and ledState variables as volatile.
// The 'volatile' keyword indicates to the compiler that these variables may be modified
// asynchronously outside the normal program flow, such as within interrupt service routines (ISRs).
// By declaring them as volatile, we ensure that the compiler always accesses their latest
// values from memory, even if they are modified by interrupts or other external events.
volatile uint8_t buttonPrevState = LOW;
volatile uint8_t ledState = LOW;

//using the setup function to perform tasks that need to be executed once at the beginning of the program
void setup() 
{
  //configure the BTN_PIN as input pin with pullup resistor enabled which ensures that the button is in a high state until it is not driven LOW actively
  //INPUT_PULLUP mode overrides the default state of the pin (set as LOW) and configures it to HIGH by default
  pinMode(BTN_PIN, INPUT_PULLUP);
  //Configure the LED_PIN as an output pin
  pinMode(LED_PIN, OUTPUT);
  //initialize serial communication with a baud rate of 9600 bits per second 
  //sets up a serial communication channel allowing the micrcontroller to communicate with an external device (eg. laptop)
  Serial.begin(9600);

  // Attach an interrupt to the button pin (BTN_PIN) to handle button events.
  // When the state of the button pin changes (from LOW to HIGH or HIGH to LOW),
  // the function handleButtonInterrupt() will be automatically called.
  // The digitalPinToInterrupt() function converts the pin number to the corresponding interrupt number.
  attachInterrupt(digitalPinToInterrupt(BTN_PIN), handleButtonInterrupt, CHANGE);
}

void loop() {
  // loop function remains empty since we're using interrupts for button handling
}

// Define an interrupt service routine (ISR) named handleButtonInterrupt().
// Within this ISR, read the current state of the button pin (BTN_PIN) using digitalRead().
// The button state is stored in the local variable buttonState of type uint8_t.
void handleButtonInterrupt() {
  uint8_t buttonState = digitalRead(BTN_PIN);

//print the ASCII value of variables buttonState, buttonPrevState and ledState on the serial monitor
//Serial.print() is used to send data from the microcontroller to the computer for monitoring or debugging purposes
  Serial.print(buttonState);
  Serial.print(buttonPrevState);
  Serial.print(ledState);
  Serial.println("");

//if statement to toggle the LED based on the state of the button
//if the current button state is not equal to the previous button state i.e. either the button has been turned OFF or ON, the if statement is executed
  if (buttonState != buttonPrevState) 
  {
    //toggles the LED 
    //if the led was in a LOW state, it will be turned HIGH
    //if the led was in a HIGH state, it will be turned LOW
    ledState = !ledState;
    //write the value of the ledState to the LED_PIN to turn it ON or OFF according to the status of the ledState variable
    digitalWrite(LED_PIN, ledState);
  }

  // Update the previous state of the button (buttonPrevState) with the current state of the button (buttonState).
  // This statement ensures that the previous state of the button is synchronized with the current state,
  // allowing for comparison in the next iteration of the loop or interrupt service routine.
  buttonPrevState = buttonState;
}
