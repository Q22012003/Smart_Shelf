#define ENA 9    // Chân PWM để điều khiển tốc độ động cơ
#define IN1 8    // Chân điều khiển chiều quay
#define IN2 7
#define ENCODER_A 2 // Chân tín hiệu A của encoder
#define ENCODER_B 3 // Chân tín hiệu B của encoder

volatile long encoderCount = 0; // Biến đếm xung từ encoder
int targetPosition = 1000;     // Vị trí mục tiêu (số xung)
int motorSpeed = 150;          // Tốc độ động cơ (PWM)

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENCODER_A, INPUT);
  pinMode(ENCODER_B, INPUT);

  // Cài đặt ngắt để đếm xung từ encoder
  attachInterrupt(digitalPinToInterrupt(ENCODER_A), readEncoder, CHANGE);
  
  Serial.begin(9600);
}

void loop() {
  long error = targetPosition - encoderCount; // Tính sai số

  if (abs(error) > 10) { // Nếu sai số lớn hơn ngưỡng
    if (error > 0) {
      moveMotor(motorSpeed, HIGH); // Quay tới
    } else {
      moveMotor(motorSpeed, LOW); // Quay ngược lại
    }
  } else {
    stopMotor(); // Dừng động cơ khi đạt vị trí
  }

  Serial.print("Encoder Count: ");
  Serial.println(encoderCount);
  delay(100);
}

void moveMotor(int speed, bool direction) {
  digitalWrite(IN1, direction);
  digitalWrite(IN2, !direction);
  analogWrite(ENA, speed);
}

void stopMotor() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
}

// Hàm đếm xung từ encoder
void readEncoder() {
  if (digitalRead(ENCODER_A) == digitalRead(ENCODER_B)) {
    encoderCount++;
  } else {
    encoderCount--;
  }
}
