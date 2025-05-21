#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h> // Make sure to include this for JSON handling

int rows[3] = {12, 13, 21};  // GPIO pins for rows
int cols[6] = {14, 15, 16, 17, 18, 19}; // GPIO pins for columns
int matrix[3][6] = {{0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0}};
                    
int lastState[3][6] = {{0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0}};

//WiFi credentials
const char* ssid = "un's";
const char* password = "12345678";

Endpoint URL
const char* endpoint = "https://ap-southeast-1.aws.data.mongodb-api.com/app/application-0-pdtrfvc/endpoint/quocquidulieu";

// Timer variables
unsigned long previousMillis = 0;
const long interval = 10000; // 10 seconds
const int debounceDelay = 100; //  Debounce delay in milliseconds
unsigned long lastDebounceTime[3][6]; // Store debounce time for each button

void connectToWiFi() { 
  Serial.print("Connecting to ");
  Serial.println(ssid);       
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  // WiFi setup
  Serial.begin(9600);
 // connectToWiFi();

  // Configure GPIO for rows (output)
  for (int i = 0; i < 3; i++) {
    pinMode(rows[i], OUTPUT);
    digitalWrite(rows[i], HIGH); // Set row to inactive state (HIGH)
  }
  // Configure GPIO for columns (input with pull-up)
  for (int i = 0; i < 6; i++) {
    pinMode(cols[i], INPUT_PULLUP);
  }
}

void loop() {
  // Reset trạng thái matrix trước mỗi lần quét
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 6; j++) {
      matrix[i][j] = 0;
    }
  }

  // Quét trạng thái nút nhấn
  for (int i = 0; i < 3; i++) {
    // Đặt tất cả các hàng không kích hoạt
    for (int k = 0; k < 3; k++) {
      digitalWrite(rows[k], HIGH);
    }

    // Chỉ kích hoạt hàng i
    digitalWrite(rows[i], LOW);

    // Đọc trạng thái cột
    for (int j = 0; j < 6; j++) {
      int currentState = digitalRead(cols[j]) == LOW ? 1 : 0; // Đọc trạng thái cột

      // Kiểm tra debounce
      if (currentState != lastState[i][j]) {
        lastDebounceTime[i][j] = millis(); // Cập nhật thời gian debounce
      }

      // Xác nhận trạng thái nếu đã qua thời gian debounce
      if ((millis() - lastDebounceTime[i][j]) > debounceDelay) {
        if (currentState != matrix[i][j]) {
          matrix[i][j] = currentState; // Cập nhật trạng thái nút nhấn
        }
      }

      lastState[i][j] = currentState; // Lưu trạng thái trước đó
    }
  }

  // Hiển thị trạng thái ma trận lên Serial Monitor
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 6; j++) {
      Serial.print(matrix[i][j]);
      Serial.print(" ");
    }
    Serial.println();
  }

  // Gửi dữ liệu POST mỗi 10 giây
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    post();
  }

  delay(300); // Tùy chỉnh độ trễ để giảm tải CPU
}

void post() {
  if (WiFi.status() == WL_CONNECTED) { // Check WiFi connection
    HTTPClient http;
    http.begin(endpoint); // Connect to endpoint
    http.addHeader("Content-Type", "application/json");

    // Create JSON document
    StaticJsonDocument<200> doc;

    // Gửi dữ liệu từ matrix lên server
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 6; j++) {
        String key = "slot_" + String(10 + i * 6 + j); // Ví dụ: slot_1, slot_2,...
        doc[key] = matrix[i][j];
      }
    }

    String jsonString;
    serializeJson(doc, jsonString);

    int httpResponseCode = http.POST(jsonString); // Send JSON data
    if (httpResponseCode > 0) {
      String payload = http.getString(); // Get the response payload
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      Serial.print("Response: ");
      Serial.println(payload);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }

    http.end(); // End connection
  } else {
    Serial.println("Error: WiFi not connected");
  }
}