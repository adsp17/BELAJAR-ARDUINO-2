#define buttonPin 7  // Pin tempat pushbutton terhubung
#define ledPin 13   // Pin untuk LED
int buttonState;          // Status tombol
int lastButtonState = HIGH;
int count = 0;           // Variabel untuk menyimpan jumlah tekan tombol

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);  // Gunakan internal pull-up resistor
  pinMode(ledPin, OUTPUT);           // Set LED sebagai output
  Serial.begin(9600); // Memulai komunikasi serial
}

void loop() {
  buttonState = digitalRead(buttonPin);
  
  // Deteksi perubahan dari HIGH ke LOW (tombol ditekan)
  if (lastButtonState == HIGH && buttonState == LOW) {
    count++;
    Serial.print("Count: ");
    Serial.println(count);
    digitalWrite(ledPin, HIGH); // Nyalakan LED saat tombol ditekan
    delay(200); // Debounce sederhana
  } else {
    digitalWrite(ledPin, LOW); // Matikan LED saat tombol tidak ditekan
  }
  
  lastButtonState = buttonState; // Simpan status tombol terakhir
}
