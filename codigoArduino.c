#include <Wire.h> // Biblioteca para comunicação I2C
#include <LiquidCrystal_I2C.h> // Biblioteca para display LCD 20x4 via I2C

#define col 16 // Número de colunas do display
#define lin  2 // Número de linhas do display
#define ende  0x27 // Endereço I2C do display LCD

// Pinos A4 e A5 do Arduino devem ser ligados ao display I2C

LiquidCrystal_I2C lcd(ende, col, lin); // Instancia o objeto do display LCD

#include <Adafruit_Sensor.h> // Biblioteca base para sensores Adafruit
#include <DHT.h>             // Biblioteca para sensores DHT
#include <DHT_U.h>           // Biblioteca unificada para sensores DHT

//#define DHTTYPE    DHT11   // Descomente para usar o DHT11
#define DHTTYPE    DHT22     // Tipo do sensor DHT (DHT22 ou AM2302)
#define DHTPIN 2             // Pino do Arduino conectado ao pino Data do DHT

DHT_Unified dht(DHTPIN, DHTTYPE); // Instancia o objeto do sensor DHT
uint32_t delayMS;                 // Variável para atraso entre leituras

// Definição dos pinos dos LEDs e buzzer
int ledPinVerd = 13; // LED verde
int ledPinAm = 9;    // LED amarelo (mudar para 12 depois, se necessário)
int ledPinVer = 8;   // LED vermelho
int valorluz = 0;    // Valor do sensor de luz (não utilizado no código atual)
int buzzer = 7;      // Pino do buzzer

// Definição dos pinos do sensor ultrassônico
#define TRIG_PIN 11  // Pino trigger do sensor ultrassônico
#define ECHO_PIN 10  // Pino echo do sensor ultrassônico

void setup(){
    // Inicialização do display LCD
    lcd.init();         // Inicia comunicação com o display
    lcd.backlight();    // Liga a luz de fundo do display
    lcd.clear();        // Limpa o display
    lcd.setCursor(0, 1);// Move o cursor para a segunda linha

    // Configuração dos pinos dos LEDs como saída
    pinMode(ledPinVerd, OUTPUT); 
    pinMode(ledPinAm, OUTPUT);   
    pinMode(ledPinVer, OUTPUT);  

    // Inicialização do sensor de temperatura e umidade
    Serial.begin(9600); // Inicia comunicação serial
    dht.begin();        // Inicializa o sensor DHT
    Serial.println("Usando o Sensor DHT");
    sensor_t sensor;
    dht.temperature().getSensor(&sensor); // Obtém informações do sensor de temperatura
    Serial.println("------------------------------------");
    Serial.println("Temperatura");
    Serial.print  ("Sensor:       "); Serial.println(sensor.name);
    Serial.print  ("Valor max:    "); Serial.print(sensor.max_value); Serial.println(" *C");
    Serial.print  ("Valor min:    "); Serial.print(sensor.min_value); Serial.println(" *C");
    Serial.print  ("Resolucao:   "); Serial.print(sensor.resolution); Serial.println(" *C");
    Serial.println("------------------------------------");
    dht.humidity().getSensor(&sensor); // Obtém informações do sensor de umidade
    Serial.println("------------------------------------");
    Serial.println("Umidade");
    Serial.print  ("Sensor:       "); Serial.println(sensor.name);
    Serial.print  ("Valor max:    "); Serial.print(sensor.max_value); Serial.println("%");
    Serial.print  ("Valor min:    "); Serial.print(sensor.min_value); Serial.println("%");
    Serial.print  ("Resolucao:   "); Serial.print(sensor.resolution); Serial.println("%");
    Serial.println("------------------------------------");
    delayMS = sensor.min_delay / 1000; // Define atraso mínimo entre leituras

    // Configuração dos pinos do sensor ultrassônico
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    // Mensagens iniciais no display LCD
    lcd.begin(col, lin);
    lcd.print("MONITORAMENTO");
    lcd.setCursor(0,1);
    lcd.print("NIVEL AGUA");
    delay(2000);
    lcd.clear();
    lcd.print("UMIDADE");
    lcd.setCursor(0,1);
    lcd.print("TEMPATURA");
    delay(2000);
    lcd.clear();
}

void loop() {
    float somaTemp = 0;           // Soma das leituras de temperatura
    float somaUmid = 0;           // Soma das leituras de umidade
    int leiturasValidasTemp = 0;  // Contador de leituras válidas de temperatura
    int leiturasValidasUmid = 0;  // Contador de leituras válidas de umidade

    // Realiza 5 leituras dos sensores para média
    for (int i = 0; i < 5; i++) {
        sensors_event_t event;

        // Leitura da temperatura
        dht.temperature().getEvent(&event);
        float temp = isnan(event.temperature) ? -999 : event.temperature;
        if (temp != -999) {
            somaTemp += temp;
            leiturasValidasTemp++;
        }

        // Leitura da umidade
        dht.humidity().getEvent(&event);
        float umid = isnan(event.relative_humidity) ? -1 : event.relative_humidity;
        if (umid != -1) {
            somaUmid += umid;
            leiturasValidasUmid++;
        }

        delay(200); // Pequeno atraso entre leituras para estabilidade
    }
    // Calcula médias das leituras válidas
    float temperatura = (leiturasValidasTemp > 0) ? (somaTemp / leiturasValidasTemp) : -999;
    float umidade = (leiturasValidasUmid > 0) ? (somaUmid / leiturasValidasUmid) : -1;

    // Variável para indicar condição crítica (aciona buzzer)
    bool condicaoCritica = false;

    // Controle dos LEDs e buzzer conforme umidade
    // LED amarelo: alerta de umidade alta
    if (umidade != -1 && (umidade > 70 && umidade < 85)) {
        digitalWrite(ledPinAm, HIGH); // Liga LED amarelo
    }
    // LED vermelho: alerta crítico de umidade
    if (umidade != -1 && umidade > 85) {
        digitalWrite(ledPinVer, HIGH); // Liga LED vermelho
        condicaoCritica = true;        // Seta condição crítica
    }

    // Exibição no LCD - Temperatura
    lcd.clear(); // Limpa display
    if(temperatura == -999) {
        lcd.print("Erro temp!"); // Erro de leitura de temperatura
    } else{
        lcd.print("Temp: ");
    }
    lcd.setCursor(0, 1); // Vai para segunda linha
    if(temperatura != -999) {
        lcd.print(temperatura); // Mostra valor da temperatura
        lcd.print("*C");
    }
    delay(2000); // Aguarda 2 segundos

    // Exibição no LCD - Umidade
    lcd.clear(); // Limpa display
    if(umidade == -1) {
        lcd.print("Erro umidade!"); // Erro de leitura de umidade
    } else if (umidade <= 70){
        lcd.print("Umidade Normal"); // Umidade dentro do normal
    } else if(umidade <= 85) {
        lcd.print("Possivel chuva"); // Alerta de possível chuva
    } else {
        lcd.print("Risco de enchente"); // Alerta de risco de enchente
    }
    lcd.setCursor(0, 1); // Vai para segunda linha
    if(umidade != -1) {
        lcd.print(umidade); // Mostra valor da umidade
        lcd.print("%");
    }
    delay(2000); // Aguarda 2 segundos

    // Leitura do sensor ultrassônico para nível da água
    int distance = getDistance();
    lcd.clear(); // Limpa display
    if(distance <= 100)
    {
        lcd.print("Nvl da Agua: ");
        lcd.print(distance);
        lcd.setCursor(0, 1); // Vai para segunda linha
        lcd.print("Perigoso"); // Nível perigoso
        digitalWrite(ledPinVer, HIGH);   // Liga LED vermelho
        digitalWrite(ledPinAm, LOW);     // Desliga LED amarelo
        digitalWrite(ledPinVerd, LOW);   // Desliga LED verde
        delay(2000);
        condicaoCritica = true;          // Seta condição crítica
    }
    else if (distance < 200)
    {
        lcd.print("Nvl da Agua: ");
        lcd.print(distance);
        lcd.setCursor(0, 1); // Vai para segunda linha
        lcd.print("Normal"); // Nível normal
        digitalWrite(ledPinVer, LOW);    // Desliga LED vermelho
        digitalWrite(ledPinAm, HIGH);    // Liga LED amarelo
        digitalWrite(ledPinVerd, LOW);   // Desliga LED verde
        delay(2000);
        condicaoCritica = false;         // Não é condição crítica
    }
    else
    {
        lcd.print("Nvl da Agua: ");
        lcd.print(distance);
        lcd.setCursor(0, 1); // Vai para segunda linha
        lcd.print("Baixa"); // Nível baixo
        digitalWrite(ledPinVer, LOW);    // Desliga LED vermelho
        digitalWrite(ledPinAm, LOW);     // Desliga LED amarelo
        digitalWrite(ledPinVerd, HIGH);  // Liga LED verde
        delay(2000);
        condicaoCritica = false;         // Não é condição crítica
    }

    // Ativa buzzer se qualquer condição crítica for atendida
    if (condicaoCritica) {
        tone(buzzer, 1000); // Aciona buzzer em 1kHz
    } else {
        noTone(buzzer);     // Desliga buzzer
    }
}

// Função para obter distância do sensor ultrassônico (em cm)
int getDistance() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    long duration = pulseIn(ECHO_PIN, HIGH); // Mede o tempo do pulso
    int distance = (duration * 0.0343) / 2;  // Calcula a distância em cm

    return distance;
}
