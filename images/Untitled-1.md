## 🌊 Aqua Guard: Seu Escudo Contra Enchentes! 🛡️

Bem-vindo ao repositório do sistema de monitoramento de nível de água da Aqua Guard, a solução inteligente que antecipa o perigo das enchentes e protege vidas e patrimônios!

### 📝 Descrição Completa do Problema
As enchentes são uma realidade devastadora no Brasil, afetando milhões de pessoas e causando prejuízos bilionários anualmente. Principais desafios:
- Alertas tardios que não permitem evacuação segura
- Falta de monitoramento localizado em pontos críticos
- Dificuldade de acesso à informação em tempo real
- Danos materiais e riscos à saúde pública

---

## ✨ Visão Geral do Projeto (IoT para Prevenção de Enchentes)
Este projeto de Arduino representa um nó de sensoriamento local crucial para a plataforma Aqua Guard. Ele é projetado para monitorar o nível da água em áreas críticas, como bueiros ou pontos de escoamento em ruas, e fornecer alertas imediatos no local.

![Protótipo Real](./images/prototipo.png)

### 🎯 Nosso Foco
Alagamento de ruas em um bairro específico – um problema real que causa grandes transtornos e perdas.

---

## 🛠️ Componentes Utilizados (Hardware Essencial)


O sistema é construído com componentes acessíveis e eficazes para um monitoramento preciso:

Arduino Uno: O cérebro do nosso sistema, processando dados e controlando os alertas.
Módulo Display LCD I2C (16x2): Exibe o nível da água, temperatura e umidade em tempo real.
LEDs Indicadores:
🟢 LED Verde (Pino 13): Nível de água normal, tudo sob controle.
🟡 LED Amarelo (Pino 9): Atenção! Possível elevação do nível ou umidade alta.
🔴 LED Vermelho (Pino 8): Perigo! Risco de alagamento ou enchente iminente.
Buzzer (Pino 7): Alerta sonoro para situações críticas.
Sensor DHT22 (Pino 2): Monitora a temperatura e a umidade do ambiente, indicando condições climáticas que favorecem enchentes.
Sensor Ultrassônico HC-SR04: Mede a distância até a superfície da água para determinar o nível.

![Sensor Ultrassônico](./images/SensorUltrassonico.png)

---

## 🧠 Como o Sistema Funciona


1. **Coleta de Dados**: Sensores capturam nível da água e condições climáticas
2. **Processamento**: Arduino analisa os dados em tempo real
3. **Alertas**: Sistema aciona indicadores visuais e sonoros
4. **Visualização**: LCD exibe informações detalhadas

---

## 🔌 Diagrama do Circuito

Visualize a montagem do nosso sistema no simulador:

![Imagem Simulador](./images/Simulador.png)

Conexões Principais:

Arduino Uno:
Sensor Ultrassônico HC-SR04: TRIG_PIN ao D11, ECHO_PIN ao D10.
Módulo Display LCD I2C: SDA ao A4, SCL ao A5.
LED Verde: D13.
LED Amarelo: D9.
LED Vermelho: D8.
Buzzer: D7.
Sensor DHT22: D2.

---

## 🚀 Guia Rápido para Simular o Projeto
## Quer ver a Aqua Guard em ação? Siga estes passos simples:

Acesse o Simulador: Utilize o Wokwi.
Crie um Novo Projeto: Inicie um projeto de Arduino.
Monte o Circuito: Adicione os componentes listados e faça as conexões conforme o diagrama acima.
Carregue o Código: Copie o conteúdo do arquivo codigoArduino.c para o editor de código do simulador.
Inicie a Simulação: Pressione "Start Simulation".
Interaja: Altere o nível da água no sensor ultrassônico e os valores do DHT22 para observar as respostas dos LEDs, do buzzer e do display LCD.

---

## 🌐 Links Importantes

Link para o Projeto no Simulador (Wokwi/Tinkercad): Adicione seu link aqui! Ex: https://wokwi.com/projects/432046816230275073

Link para o Vídeo Demonstrativo no YouTube: https://youtu.be/QZQBXhrrQ6o?si=-_fZSq1FECrdQu21

---

## ⚠️ Observações Cruciais para o Sucesso

Calibração é Essencial: Os valores de distância e umidade no código (100, 200 para distância; 70, 85 para umidade) são exemplos. Eles devem ser ajustados e calibrados com base nas características específicas do ambiente onde o sistema será implementado (altura do bueiro, níveis de umidade típicos da região, etc.). Realize testes para otimizar a precisão.
Bibliotecas: Certifique-se de que as bibliotecas Wire.h, LiquidCrystal_I2C.h, Adafruit_Sensor.h e DHT.h (e DHT_U.h) estejam instaladas no seu ambiente de desenvolvimento Arduino IDE ou disponíveis no simulador.
Endereço I2C do LCD: O endereço 0x27 é o mais comum, mas verifique o endereço correto do seu módulo LCD se ele não iniciar.

---

## 🤝 Equipe: Aqua Guard

[<img src="https://avatars.githubusercontent.com/u/203848085?v=4" width="80px;" alt="Foto de Perfil do GitHub de Gabriel Akira"/><br /><sub>**Gabriel Akira**</sub>](https://github.com/Gakira06)

Gabriel Akira Borges - RM: 565191

[<img src="https://avatars.githubusercontent.com/u/205759608?v=4" width="80px;" alt="Foto de Perfil do GitHub de Gustavo Santos"/><br /><sub>**Gustavo Santos**</sub>](https://github.com/gugasantos24)

Gustavo Francisco Santos - RM: 561820
