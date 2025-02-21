#include <WiFi.h>
#include <WebServer.h>

// WiFi credentials
const char* ssid = "Airtel_asif_7645";
const char* password = "4thfloor@vrmeadows";


// GPIO Pins (excluding reserved ones)
const int pins[] = {2, 4, 5, 12, 13, 14, 15, 16, 17, 18, 19, 21, 22, 23, 25, 26, 27, 32, 33};
const int pinCount = sizeof(pins) / sizeof(pins[0]);

WebServer server(80);

// WiFi connection function
void setupWiFi() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");

    unsigned long startAttemptTime = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) {
        delay(500);
        Serial.print(".");
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nConnected to WiFi!");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println("\nFailed to connect to WiFi!");
    }
}

// Get GPIO status in JSON format
String getPinStatus() {
    String json = "{";
    for (int i = 0; i < pinCount; i++) {
        json += "\"" + String(pins[i]) + "\": ";
        json += digitalRead(pins[i]) ? "1" : "0";
        if (i < pinCount - 1) json += ", ";
    }
    json += "}";
    return json;
}

// Serve GPIO status
void handleStatus() {
    server.send(200, "application/json", getPinStatus());
}

// Toggle a GPIO pin
void handleToggle() {
    if (!server.hasArg("pin")) {
        server.send(400, "text/plain", "Missing 'pin' parameter");
        return;
    }

    int pin = server.arg("pin").toInt();
    bool validPin = false;
    for (int i = 0; i < pinCount; i++) {
        if (pins[i] == pin) {
            validPin = true;
            break;
        }
    }

    if (!validPin) {
        server.send(400, "text/plain", "Invalid pin number");
        return;
    }

    Serial.printf("Toggling pin: %d\n", pin);
    digitalWrite(pin, !digitalRead(pin));

    server.send(200, "application/json", getPinStatus());
}

void setup() {
    Serial.begin(115200);
    delay(1000); // Small delay for stability

    setupWiFi();

    // Initialize GPIOs
    for (int i = 0; i < pinCount; i++) {
        pinMode(pins[i], OUTPUT);
        digitalWrite(pins[i], LOW);
    }

    // Define API routes
    server.on("/status", HTTP_GET, handleStatus);
    server.on("/toggle", HTTP_GET, handleToggle);

    server.begin();
}

void loop() {
    server.handleClient(); // Process HTTP requests
}
