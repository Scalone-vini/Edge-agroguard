# 🌾 AgriGuard — Estação de Monitoramento de Solo com Arduino

> Solução de edge computing para detecção de risco de queimadas no campo, utilizando sensores físicos simulados no Wokwi.

---

## 📋 Descrição do Projeto

O **AgriGuard** é uma estação de monitoramento agrícola embarcada em Arduino Uno que lê em tempo real a temperatura do ambiente, a umidade do ar e a umidade do solo. Os dados são processados localmente (na borda — *edge*) para acionar alertas visuais e sonoros imediatos, sem depender de conectividade com a nuvem para a tomada de decisão crítica.

O projeto simula o sensor físico que um agricultor teria instalado no campo, enviando dados e emitindo alertas locais de risco de incêndio ou ressecamento do solo.

---

## 🎯 Objetivo da Solução

- Monitorar continuamente temperatura, umidade do ar e umidade do solo
- Identificar condições de **alto risco de queimada** (temperatura > 35 °C **e** umidade do ar < 30 %)
- Alertar o agricultor localmente via LED vermelho e buzzer (padrão de 3 bipes)
- Exibir todos os dados em tempo real no display LCD 16×2
- Demonstrar o conceito de **edge computing**: decisão tomada no próprio dispositivo, sem latência de rede

---

## 🔧 Componentes Utilizados

| Componente | Quantidade | Função |
|---|---|---|
| Arduino Uno | 1 | Microcontrolador principal |
| Sensor DHT22 | 1 | Temperatura e umidade do ar |
| Potenciômetro (10 kΩ) | 1 | Simula sensor de umidade do solo |
| Display LCD 16×2 | 1 | Exibição dos dados em tempo real |
| LED Vermelho (5 mm) | 1 | Alerta visual — RISCO ALTO |
| LED Verde (5 mm) | 1 | Indicador visual — SEGURO |
| Buzzer passivo | 1 | Alerta sonoro em emergência |
| Resistor 220 Ω | 2 | Limitadores de corrente para os LEDs |
| Protoboard | 1 | Montagem do circuito |
| Jumpers | — | Conexões entre componentes |

---

## ⚙️ Como Funciona

1. A cada **2 segundos**, o Arduino lê os três sensores
2. O **DHT22** fornece temperatura (°C) e umidade relativa do ar (%)
3. O **potenciômetro** simula o sensor de solo: o valor analógico (0–1023) é mapeado para 0–100 % de umidade
4. A lógica de risco avalia:
   - Se `temperatura > 35 °C` **E** `umidade do ar < 30 %` → **RISCO ALTO**
     - LED vermelho acende
     - Buzzer emite 3 bipes (1000 Hz, 200 ms cada)
     - LCD exibe `RISCO!`
   - Caso contrário → **SEGURO**
     - LED verde acende
     - Buzzer silencioso
     - LCD exibe `SEGURO`
5. Todos os dados são também enviados pela porta Serial para debug

---

## 🔌 Estrutura do Circuito

```
Arduino Uno
│
├── Pino 2       → DHT22 (DATA)
├── Pino 12      → LCD RS
├── Pino 11      → LCD EN
├── Pinos 5,4,3,6 → LCD D4, D5, D6, D7
├── Pino 8       → LED Vermelho (+ resistor 220 Ω → GND)
├── Pino 9       → LED Verde    (+ resistor 220 Ω → GND)
├── Pino 10      → Buzzer (–) → GND
├── A0           → Potenciômetro (cursor)
├── 5V           → DHT22 VCC, LCD VCC, Potenciômetro extremo +
└── GND          → Todos os GNDs
```

> **DHT22**: VCC → 5 V | DATA → Pino 2 (com pull-up 10 kΩ para 5 V) | GND → GND  
> **LCD**: Contraste (V0) via resistor de 1 kΩ para GND; backlight (A/K) → 5 V/GND

---

## ▶️ Instruções de Execução

### Simulação no Wokwi (recomendado)

1. Acesse o link do projeto no Wokwi: **[🔗https://wokwi.com/projects/466286503832636417]**
2. Clique em **"Play"** (▶) para iniciar a simulação
3. Gire o potenciômetro para simular diferentes umidades do solo
4. O DHT22 virtual pode ser ajustado pelo painel de propriedades do componente
5. Observe o LCD, os LEDs e o buzzer reagindo em tempo real

### Execução Local (opcional)

```bash
# 1. Clone o repositório
git clone https://github.com/SEU_USUARIO/agriguard-arduino.git
cd agriguard-arduino

# 2. Abra o arquivo no Arduino IDE
# Arquivo > Abrir > estacao_solo.ino

# 3. Instale as bibliotecas necessárias
# Ferramentas > Gerenciar Bibliotecas:
#   - DHT sensor library (Adafruit)
#   - LiquidCrystal (built-in)

# 4. Selecione a placa: Arduino Uno
# 5. Selecione a porta COM correta
# 6. Clique em Carregar (→)
```

---

## 📁 Estrutura do Repositório

```
agriguard-arduino/
├── estacao_solo.ino   # Código-fonte principal (Arduino/C++)
├── README.md          # Este arquivo
└── /docs
    └── circuito.png   # Diagrama do circuito (opcional)
```

---

## 👥 Integrantes do Grupo

| Nome | RM |
|---|---|
| Vinicius Scalone | 573783 |
| Rafael de Souza | 568777 |

---

## 📚 Disciplina

**Edge Computing & Computer Systems** — FIAP  
Simulador: [Wokwi](https://wokwi.com)
