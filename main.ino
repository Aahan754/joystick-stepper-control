/*
  Joystick Stepper Motor Control with Serial RPM Telemetry
  Board: Arduino UNO R3
*/

#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11
#define JOYSTICK_X A0

const int JOYSTICK_CENTER = 512;
const int DEADZONE = 50;

// 28BYJ-48 stepper motor has 2048 steps per full 360-degree revolution in full-step mode
const float STEPS_PER_REV = 2048.0;

const int stepSequence[4][4] = {
  {1, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 1},
  {1, 0, 0, 1}
};

int currentStep = 0;
unsigned long lastSerialPrint = 0;

void setup() {
  Serial.begin(9600);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  stopMotor();
  Serial.println("--- Stepper Motor Controller Online ---");
}

void loop() {
  int joystickVal = analogRead(JOYSTICK_X);
  int offset = joystickVal - JOYSTICK_CENTER;

  if (abs(offset) > DEADZONE) {
    // Map joystick displacement to step delay in milliseconds (20ms slow -> 2ms fast)
    int stepDelay = map(abs(offset), DEADZONE, 512, 20, 2);

    // Calculate actual calculated RPM: 
    // RPM = (60,000 ms / (stepDelay * STEPS_PER_REV))
    float calculatedRPM = 60000.0 / (stepDelay * STEPS_PER_REV);

    if (offset > 0) {
      currentStep = (currentStep + 1) % 4;
    } else {
      currentStep = (currentStep - 1 + 4) % 4;
    }

    applyStep(currentStep);

    // Print RPM telemetry every 200ms to keep output readable
    if (millis() - lastSerialPrint > 200) {
      Serial.print("Dir: ");
      Serial.print(offset > 0 ? "CW " : "CCW");
      Serial.print(" | Step Delay: ");
      Serial.print(stepDelay);
      Serial.print(" ms | Output Speed: ");
      Serial.print(calculatedRPM, 2);
      Serial.println(" RPM");
      lastSerialPrint = millis();
    }

    delay(stepDelay);

  } else {
    stopMotor();
    if (millis() - lastSerialPrint > 500) {
      Serial.println("State: IDLE | Speed: 0.00 RPM");
      lastSerialPrint = millis();
    }
  }
}

void applyStep(int step) {
  digitalWrite(IN1, stepSequence[step][0]);
  digitalWrite(IN2, stepSequence[step][1]);
  digitalWrite(IN3, stepSequence[step][2]);
  digitalWrite(IN4, stepSequence[step][3]);
}

void stopMotor() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
