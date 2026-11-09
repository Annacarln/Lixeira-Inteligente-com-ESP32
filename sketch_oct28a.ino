#include <ESP32Servo.h>
#include "BluetoothSerial.h"

// 1. CONFIGURAÇÃO DAS FERRAMENTAS
BluetoothSerial SerialBT; // Ativa a comunicação Bluetooth para o celular
Servo servoTampa;         // Cria o controlador virtual do micro servo motor

// Pinos do Sensor da Mão (Responsável por abrir a tampa)
const int trigMao = 5;    // Emite a onda de som
const int echoMao = 19;   // Ouve o retorno do som

// Pinos do Sensor do Lixo (Responsável por medir a profundidade interna)
const int trigLixo = 12;  // Emite a onda de som
const int echoLixo = 14;  // Ouve o retorno do som

// Pino do Motor da Tampa
const int pinoMotor = 18; // Envia o sinal elétrico para o fio laranja/amarelo

void setup() {
  // Inicia a comunicação com o computador para testes no Monitor Serial
  Serial.begin(115200);

  // Inicia o Bluetooth e define o nome que aparecerá no seu aplicativo terminal
  SerialBT.begin("Lixeira_Inteligente");

  // Configura a direção da energia de cada pino (OUTPUT = Sai, INPUT = Entra)
  pinMode(trigMao, OUTPUT);
  pinMode(echoMao, INPUT);
  pinMode(trigLixo, OUTPUT);
  pinMode(echoLixo, INPUT);

  // Conecta o motor ao pino D18 e força a tampa a iniciar fechada (ângulo 0)
  servoTampa.attach(pinoMotor);
  servoTampa.write(0);
}

// 2. FUNÇÃO INTELIGENTE DE LEITURA
// função para não termos de escrever o mesmo código duas vezes.
// emite o som, calcula o tempo e transforma em centímetros.
int medirDistancia(int pinoTrig, int pinoEcho) {
  // Dispara um pulso sonoro extremamente rápido
  digitalWrite(pinoTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(pinoTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinoTrig, LOW);

  // Conta o tempo que o som demorou para bater num objeto e voltar.
  // O limite de 30000 evita os falsos "-1" e impede o ESP32 de travar.
  long tempo = pulseIn(pinoEcho, HIGH, 30000);

  // Se o som se perder e não voltar (tempo = 0), regista -1 como erro.
  if (tempo == 0) {
    return -1;
  }

  // Fórmula matemática para converter a velocidade do som em centímetros
  int distancia = (tempo * 0.034) / 2;
  return distancia;
}

// 3. CICLO PRINCIPAL (O que a lixeira faz sem parar)
void loop() {
  // Usa a função criada acima para saber a distância da mão e o nível de lixo
  int distanciaMao = medirDistancia(trigMao, echoMao);
  int distanciaLixo = medirDistancia(trigLixo, echoLixo);

  // Imprime os valores no Monitor Serial do computador para monitorização
  Serial.print("Mao: ");
  Serial.print(distanciaMao);
  Serial.print(" cm | Lixo: ");
  Serial.print(distanciaLixo);
  Serial.println(" cm");

  // AÇÃO 1: ABRIR A TAMPA
  // Se a mão for detetada a uma distância válida entre 1 e 10 cm:
  if (distanciaMao > 0 && distanciaMao <= 10) {
    Serial.println(">>> ABRINDO TAMPA <<<");
    servoTampa.write(90);  // Gira o motor para a posição de 90 graus (Aberto)
    
    delay(10000);          // Pausa de 10.000 milissegundos (mantém aberto 10 segundos)
    
    servoTampa.write(0);   // Gira o motor de volta para 0 graus (Fechado)
    Serial.println("<<< FECHANDO TAMPA >>>");
  }

  // AÇÃO 2: AVISO DE LIXEIRA CHEIA
  // Se o volume de lixo crescer até ficar a menos de 10 cm do topo:
  if (distanciaLixo > 0 && distanciaLixo <= 10) {
    SerialBT.println("ALERTA: A lixeira está cheia!");
  }

  // Pequena pausa de meio segundo antes de recomeçar tudo, poupando energia da placa
  delay(500);
}