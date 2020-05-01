
/**************************************************************************/
/*!
 * Pulse Oximeter testing sketch
 *
 * More notes here: https://twitter.com/josecastillo/status/1255629761897996293
 * 
 * currently running on the sensor cap with a hacky version of the 
 * Trinket M0 core, hence the very off the wall pin numbers.
 * Will eventually make a proper Sensor Cap Arduino variant.
*/
/**************************************************************************/

#define BTN_1 26

#define RED_PIN 7
#define IR_PIN 12

#define OPTO A3

#define NUM_SAMPLES 50

void setup() {
  Serial.begin(115200);
  pinMode(RED_PIN, OUTPUT);
  pinMode(IR_PIN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(OPTO, INPUT);
  pinMode(BTN_1, INPUT_PULLUP);
}

float minimum = 1024;
float maximum = 0;
float buf_ox[NUM_SAMPLES] = {0};
int pos = 0;

int pulseMode = false;

void loop() {
  float ir_reading = 0;
  float red_reading = 0;

  for(int i = 0; i < 5; i++) {
    digitalWrite(RED_PIN, LOW);
    digitalWrite(IR_PIN, HIGH);
    delay(10);
    ir_reading += analogRead(OPTO);
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(IR_PIN, LOW);
    delay(10);
    red_reading += analogRead(OPTO);
  }
  float ir_average = ir_reading / 5;
  float red_average = red_reading / 5;

  Serial.print(ir_average);
  Serial.print(",");
  Serial.print(red_average);
  Serial.print(",");
  float ratio = (red_reading / ir_reading) * 1000;

  buf_ox[pos] = ratio;
  pos = (pos + 1) % NUM_SAMPLES;
  float total = 0;
  for(int i = 0; i < NUM_SAMPLES; i++) total += buf_ox[i];  
  float average = total / NUM_SAMPLES;
  
  Serial.print(average);
  Serial.print(",");
  Serial.print(ratio);

  // button for note taking during a run
  if (digitalRead(BTN_1) == LOW) Serial.print(",800");
  else Serial.print(",700");

  Serial.print("\n");
}
