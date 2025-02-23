#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <AM2302-Sensor.h>

// Inisialisasi LCD I2C dengan alamat 0x27 (bisa 0x3F tergantung modul)
LiquidCrystal_I2C lcd(0x27, 16, 2);

constexpr unsigned int SENSOR_PIN {6U};
AM2302::AM2302_Sensor am2302{SENSOR_PIN};

void setup() {
    Serial.begin(115200);
    while (!Serial) {
        yield();
    }
    Serial.print(F("\n >>> AM2302-Sensor_Example <<<\n\n"));

    lcd.begin();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Initializing...");
    delay(2000);
    lcd.clear();

    if (am2302.begin()) {
        delay(3000);
    } else {
        while (true) {
            Serial.println("Error: sensor check. => Please check sensor connection!");
            lcd.setCursor(0, 0);
            lcd.print("Sensor Error");
            delay(10000);
        }
    }
}

void loop() {
    auto status = am2302.read();
    Serial.print("\n\nstatus of sensor read(): ");
    Serial.println(status);

    float suhu = am2302.get_Temperature();
    float kelembaban = am2302.get_Humidity();

    Serial.print("Temperature: ");
    Serial.println(suhu);
    Serial.print("Humidity:    ");
    Serial.println(kelembaban);

    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(suhu);
    lcd.print((char)223);
    lcd.print("C");
    
    lcd.setCursor(0, 1);
    lcd.print("Humidity: ");
    lcd.print(kelembaban);
    lcd.print("%");

    delay(5000);
}
