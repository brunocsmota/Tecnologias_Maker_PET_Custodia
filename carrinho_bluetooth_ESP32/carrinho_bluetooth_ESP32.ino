/*
 * =============================================================================
 * - Carro ESP32 de duas rodas - Controle via app "Bluetooth RC Controller" -
 * =============================================================================
*/

//------------------Bibliotecas------------------
#include <BluetoothSerial.h>

//------Motor A------
const int pinoMotorA_1 = 14; 
const int pinoMotorA_2 = 13; 

//-----Motor B-------
const int pinoMotorB_1 = 23; 
const int pinoMotorB_2 = 19; 

//----Propriedades do PWM----
const int freq = 500;
const int pwmChannelA_1 = 0;
const int pwmChannelA_2 = 1;
const int pwmChannelB_1 = 3;
const int pwmChannelB_2 = 4;
const int resolution = 8;

//----Configurações da biblioteca BluetoothSerial (não alterar)----
BluetoothSerial SerialBT;
//Checa se o bluetooth está configurado corretamente
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

//------------------Declaração de Variáveis------------------
char rec = 'S';                               // lê o caracter recebido de direção mandado pelo app Bluetooth RC Controller
int vel = 0;                                   // controla a PWMval da roda (dutyCycle)

void setup() 
{       
  // Inicialização da comunicação serial
  Serial.begin(9600);
  // Inicialização do Bluetooth com o nome "ESP32" (nome pode ser alterado)
  SerialBT.begin("Moxoto");
  
  // Configuração dos pinos do motor
  pinMode(pinoMotorA_1, OUTPUT);
  pinMode(pinoMotorA_2, OUTPUT);
  pinMode(pinoMotorB_1, OUTPUT);
  pinMode(pinoMotorB_2, OUTPUT);
  
  // Configuração das funcionalidades do PWM
  ledcSetup(pwmChannelA_1, freq, resolution);
  ledcSetup(pwmChannelA_2, freq, resolution);
  ledcSetup(pwmChannelB_1, freq, resolution);
  ledcSetup(pwmChannelB_2, freq, resolution);
  
  // Atribuição dos canais aos pinos GPIO do ESP32 que controlam o PWM
  ledcAttachPin(pinoMotorA_1, pwmChannelA_1);
  ledcAttachPin(pinoMotorA_2, pwmChannelA_2);
  ledcAttachPin(pinoMotorB_1, pwmChannelB_1);
  ledcAttachPin(pinoMotorB_2, pwmChannelB_2);
}

void loop()
{ 

    if(SerialBT.available()) 
  {
    rec = SerialBT.read();  // capta o caracter enviada pelo app e armazena em 'rec'
        if (rec == 'F') // Frente
        {     
          rodaEsquerda_frente(vel);
          rodaDireita_frente(vel);
          Serial.println("F");          
        }  
        else if (rec == 'B') // Ré
        { 
          rodaEsquerda_retrocede(vel);
          rodaDireita_retrocede(vel);
          Serial.println("B");  
        }
        else if (rec == 'L') // Esquerda
        { 
          rodaEsquerda_frente(vel);
          Serial.println("L"); 
        }
        else if (rec == 'R') // Direita
        { 
          rodaDireita_frente(vel);
          Serial.println("R"); 
        }  
        else if (rec == 'G') // Frente esquerda
        { 
          rodaEsquerda_frente(vel-70);
          rodaDireita_frente(vel);
          Serial.println("G");
        }
          else if (rec == 'I')  // Frente direita
        { 
          rodaEsquerda_frente(vel);
          rodaDireita_frente(vel-70);
          Serial.println("I"); 
        }
        else if (rec == 'H')  // Ré esquerda
        { 
          rodaEsquerda_retrocede(vel-70);
          rodaDireita_retrocede(vel);
          Serial.println("H"); 
        }
        else if (rec == 'J')  // Ré direita
        { 
          rodaEsquerda_retrocede(vel);
          rodaDireita_retrocede(vel-70);
          Serial.println("J"); 
        }
        else if (rec == 'S') 
        {
          paraRodas();  
          Serial.println("S"); 
        }
        else if (rec == '0') // Valores controlam a PWMval pelo app
        {
          vel = 0;
          Serial.println("Vel: 0");
        }
        else if (rec == '1') 
        {
          vel = 25;
          Serial.println("Vel: 1");
        }
        else if (rec == '2') 
        {
          vel = 50;
          Serial.println("Vel: 2");
        }
        else if (rec == '3') 
        {
          vel = 75;
          Serial.println("Vel: 3");
        }
        else if (rec == '4') 
        {
          vel = 100;
          Serial.println("Vel: 4");
        }
        else if (rec == '5') 
        {
          vel = 125;
          Serial.println("Vel: 5");
        }
        else if (rec == '6') 
        {
          vel = 150;
          Serial.println("Vel: 6");
        }
        else if (rec == '7') 
        {
          vel = 175;
          Serial.println("Vel: 7");
        }
        else if (rec == '8') 
        {
          vel = 200;
          Serial.println("Vel: 8");
        }
        else if (rec == '9') 
        {
          vel = 225;
          Serial.println("Vel: 9");
        }
        else if (rec == 'q') 
        {
          vel = 255;
          Serial.println("Vel: q");
        }
    }
      
}

// Funções que controlam os motores/direção das rodas
// Obs: Note que a direção do motor para frente e ré dependerá da posição do motor
//      e de como ele está conectado com os fios. Você pode alterá o sentido horário e antihorário
//      antihorário do giro também na programação, trocando o pino que está em PWM/HIGH e 0/LOW.

void rodaDireita_frente(int PWMval) {
  ledcWrite(pwmChannelA_1, 0);
  ledcWrite(pwmChannelA_2, PWMval);
}

void rodaDireita_retrocede(int PWMval) {
  ledcWrite(pwmChannelA_1, PWMval);
  ledcWrite(pwmChannelA_2, 0);
}

void rodaEsquerda_frente(int PWMval) {
  ledcWrite(pwmChannelB_1, PWMval);
  ledcWrite(pwmChannelB_2, 0);
}

void rodaEsquerda_retrocede(int PWMval) {
  ledcWrite(pwmChannelB_1, 0);
  ledcWrite(pwmChannelB_2, PWMval);
}

void paraRodas() {
  ledcWrite(pwmChannelA_1, 0);
  ledcWrite(pwmChannelA_2, 0);
  ledcWrite(pwmChannelB_1, 0);
  ledcWrite(pwmChannelB_2, 0);
}
