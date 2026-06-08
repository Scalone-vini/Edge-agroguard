#include <DHT.h>
#include <LiquidCrystal.h>

// ─── Pinos ────────────────────────────────────────────────
#define DHTPIN        2
#define DHTTYPE       DHT22
#define SOLO_PIN      A0
#define LED_VERMELHO  8
#define LED_VERDE     9
#define BUZZER_PIN    10

LiquidCrystal lcd(12, 11, 5, 4, 3, 6);
DHT dht(DHTPIN, DHTTYPE);

// ─── Limiares ─────────────────────────────────────────────
const float TEMP_MAX    = 35.0;
const float UMID_AR_MIN = 30.0;

// ─── Buzzer não-bloqueante ────────────────────────────────
unsigned long tempoBuzzer = 0;
bool estadoBuzzer = false;
const long INTERVALO_BUZZER = 400;

void atualizarBuzzer(bool ligar) {
  if (!ligar) {
    digitalWrite(BUZZER_PIN, LOW);
    estadoBuzzer = false;
    return;
  }
  unsigned long agora = millis();
  if (agora - tempoBuzzer >= INTERVALO_BUZZER) {
    tempoBuzzer = agora;
    estadoBuzzer = !estadoBuzzer;
    digitalWrite(BUZZER_PIN, estadoBuzzer ? HIGH : LOW);
  }
}

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.begin(16, 2);

  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_VERDE,    OUTPUT);
  pinMode(BUZZER_PIN,   OUTPUT);

  lcd.print("AgriGuard v1.0");
  lcd.setCursor(0, 1);
  lcd.print("Iniciando...");
  delay(2000);
  lcd.clear();
}

void loop() {
  float temperatura = dht.readTemperature();
  float umidadeAr   = dht.readHumidity();
  int   umidadeSolo = map(analogRead(SOLO_PIN), 0, 1023, 100, 0);

  if (isnan(temperatura) || isnan(umidadeAr)) {
    lcd.setCursor(0, 0);
    lcd.print("Erro no sensor! ");
    Serial.println("[ERRO] DHT22 nao responde.");
    atualizarBuzzer(false);
    delay(2000);
    return;
  }

  // ── Risco: qualquer condição fora do normal ───────────
  bool tempAlta   = temperatura > TEMP_MAX;
  bool umidBaixa  = umidadeAr   < UMID_AR_MIN;
  bool riscoAlto  = tempAlta || umidBaixa;

  // ── LEDs ──────────────────────────────────────────────
  digitalWrite(LED_VERMELHO, riscoAlto ? HIGH : LOW);
  digitalWrite(LED_VERDE,    riscoAlto ? LOW  : HIGH);

  // ── Buzzer não-bloqueante ─────────────────────────────
  atualizarBuzzer(riscoAlto);

  // ── LCD linha 1: temperatura e umidade do ar ──────────
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temperatura, 1);
  lcd.print(tempAlta ? "C!" : "C ");
  lcd.print(" U:");
  lcd.print((int)umidadeAr);
  lcd.print(umidBaixa ? "%!" : "%  ");

  // ── LCD linha 2: solo e status ────────────────────────
  lcd.setCursor(0, 1);
  lcd.print("Solo:");
  lcd.print(umidadeSolo);
  lcd.print("% ");
  lcd.print(riscoAlto ? "RISCO! " : "SEGURO ");

  // ── Serial ────────────────────────────────────────────
  Serial.print("[DADOS] T=");      Serial.print(temperatura);
  Serial.print("C | Ar=");         Serial.print(umidadeAr);
  Serial.print("% | Solo=");       Serial.print(umidadeSolo);
  Serial.print("% | TempAlta=");   Serial.print(tempAlta);
  Serial.print(" | UmidBaixa=");   Serial.print(umidBaixa);
  Serial.print(" | Status=");      Serial.println(riscoAlto ? "RISCO" : "OK");

  delay(500);
}
