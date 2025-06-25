#include <WiFi.h>          // Librería para conexión WiFi
#include <HTTPClient.h>    // Librería para hacer peticiones HTTP
#include <TinyGPS.h>
#include <HX711.h>
#include <DHT.h>

// ---- CONFIGURACIÓN WiFi ----
const char* ssid = "Redmi";
const char* password = "10714983224";
const char* serverUrl = "http://192.168.254.204:1880/datos_sensores"; // IP de Node-RED

// ---- CONFIGURACIÓN GPS ----
#define RXD2 16
#define TXD2 17
HardwareSerial neogps(2);
TinyGPS gps;

// ---- CONFIGURACIÓN DHT22 ----
#define DHTPIN 23
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// ---- CONFIGURACIÓN HX711 ----
#define DOUT_PIN 18
#define SCK_PIN 19
HX711 BALANZA;

float LATITUD = -16.42317701;
float LONGITUD = -71.52181802;
unsigned long age;
float RAW_REF = 326600;
float PESO_REF = 0.500;
float REF = 0;
float PESO = 0;
float TEMPERATURA = 0;
int HUMEDAD = 0;
const long PERIODO = 2000;
long TIME_MILLIS = 0;

// ---- FUNCIÓN PARA CONECTAR O RECONEXIÓN WiFi ----
void conectarWiFi() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("🔄 Reconectando a WiFi...");
    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    int intentos = 0;
    while (WiFi.status() != WL_CONNECTED && intentos < 10) {
      delay(500);
      Serial.print(".");
      intentos++;
    }

    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("\n✅ WiFi Reconectado");
    } else {
      Serial.println("\n❌ No se pudo reconectar a WiFi");
    }
  }
}

void setup() {
  Serial.begin(115200);
  neogps.begin(9600, SERIAL_8N1, RXD2, TXD2);
  BALANZA.begin(DOUT_PIN, SCK_PIN);
  dht.begin();

  // Configurar la balanza
  REF = RAW_REF / PESO_REF;
  BALANZA.set_scale(REF);
  BALANZA.tare(20);
  delay(100);

  // Conectar a WiFi
  WiFi.mode(WIFI_STA);
  conectarWiFi();
}

void loop() {
  gps_loop();
  if ((millis() - TIME_MILLIS) >= PERIODO) {
    HUMEDAD = (int) dht.readHumidity();
    TEMPERATURA = dht.readTemperature();
    PESO = BALANZA.get_units(5);

    // Crear cadena de ubicación
    String ubicacion = String(LATITUD, 6) + "," + String(LONGITUD, 6);

    // Mostrar en consola todo junto
    Serial.println(String(TEMPERATURA) + "  " + String(HUMEDAD) + "  " + String(PESO) + "  " + ubicacion);

    // Enviar datos a Node-RED
    enviarDatosNodeRed(TEMPERATURA, HUMEDAD, PESO, LATITUD, LONGITUD);
    TIME_MILLIS = millis();
  }
}

void gps_loop() {
  bool DATO = false;
  unsigned long chars;
  unsigned short sentences, failed;
  for (unsigned long start = millis(); millis() - start < 2000;) {
    while (neogps.available()) {
      char c = neogps.read();
      if (gps.encode(c))
        DATO = true;
    }
  }
  if (DATO) {
    gps.f_get_position(&LATITUD, &LONGITUD, &age);
  }
  gps.stats(&chars, &sentences, &failed);
}

void enviarDatosNodeRed(float temp, int humedad, float peso, float lat, float lon) {
  conectarWiFi();

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    // Crear ubicación
    String ubicacion = String(lat, 6) + "," + String(lon, 6);

    // Crear JSON
    String jsonData = "{";
    jsonData += "\"temperatura\": " + String(temp, 2) + ",";
    jsonData += "\"humedad\": " + String(humedad) + ",";
    jsonData += "\"peso\": " + String(peso, 3) + ",";
    jsonData += "\"ubicacion\": \"" + ubicacion + "\"";
    jsonData += "}";

    Serial.println("📡 Enviando datos a Node-RED...");
    Serial.println(jsonData);

    int httpResponseCode = http.POST(jsonData);

    if (httpResponseCode > 0) {
      Serial.println("✅ Datos enviados correctamente");
      Serial.println(http.getString());
    } else {
      Serial.print("❌ Error en la petición: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("❌ Error: No conectado a WiFi");
  }
}

////////////////CALIBRAR///////////////////
//boot
// #include <HX711.h>

// #define DOUT_PIN 18
// #define SCK_PIN 19
// HX711 BALANZA;

// void setup() {
//   Serial.begin(115200);
//   BALANZA.begin(DOUT_PIN, SCK_PIN);
//   Serial.print("VALOR ADC:");
//   Serial.println(BALANZA.read());
//   Serial.println("No ponga ningún objeto sobre la balanza");
//   Serial.println("Destarando...");
//   BALANZA.set_scale();
//   BALANZA.tare(20);
//   Serial.println("Coloque un peso conocido:");
// }

// void loop() {
//   Serial.print("VALOR ADC: \t");
//   Serial.println(BALANZA.get_value(10),0);
//   delay(100);
// } 

