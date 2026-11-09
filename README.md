# 🗑️ Lixeira Inteligente com ESP32 (Smart Trash Can)

Projeto de automação residencial e IoT desenvolvido por **Anna, Milena e Nathália** para a Semana da Computação da Universidade Veiga de Almeida (UVA). Trata-se de uma lixeira *touchless* com abertura automática por aproximação e monitorização de capacidade via Bluetooth.

## 📌 Funcionalidades
- **Abertura Touchless:** Abertura automática por aproximação da mão (sensor ultrassónico), mantendo a tampa aberta por 10 segundos.
- **Monitorização de Volume:** Medição contínua da capacidade interna do recipiente.
- **Alertas Bluetooth:** Envio de alertas em tempo real ("ALERTA: A lixeira está cheia!") para o smartphone.
- **Alimentação Isolada (Split-Rail):** Separação de linhas de energia (USB para ESP32 e fonte externa para o motor com GND comum), prevenindo surtos elétricos e resetting indesejado (*brownout*).

## 🛠️ Componentes Utilizados
- Microcontrolador **ESP32**
- 2x Sensores Ultrassónicos **HC-SR04**
- 1x Micro Servo Motor **SG90**
- Protoboard e Cabos Jumper
- Fonte externa 5V (Carregador) + Cabo USB

## 🔌 Esquema de Ligações (Pinout)

| Componente | Pino do Componente | Conexão no ESP32 / Protoboard |
| :--- | :--- | :--- |
| **Servo Motor** | Sinal (Laranja/Amarelo) | Pino D18 |
| **Sensor Mão** | TRIG / ECHO | Pino D5 / Pino D19 |
| **Sensor Lixo** | TRIG / ECHO | Pino D12 / Pino D14 |
| **Alimentação** | VCC Sensores / Motor | Trilha 5V Inferior / Trilha Superior (Fonte Externa) |
| **GND** | Todos os componentes | GND Comum (Trilha Azul Superior unida à Inferior) |

## 👥 Equipa
- Anna
- Milena
- Nathália

## 💻 Tecnologias
- C++ (Firmware Arduino/ESP32)
- Bluetooth Serial (SPP)
- Sistemas Embarcados & Eletrónica
