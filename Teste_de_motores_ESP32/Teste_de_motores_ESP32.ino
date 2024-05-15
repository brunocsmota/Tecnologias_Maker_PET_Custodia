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


void setup() {
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

void loop() {
  //Parado
  ledcWrite(pwmChannelA_1, 0);
  ledcWrite(pwmChannelA_2, 0);
  ledcWrite(pwmChannelB_1, 0);
  ledcWrite(pwmChannelB_2, 0);
  delay(1000);

  //Esquerda
 // digitalWrite(pinoMotorA_1, LOW);
  ledcWrite(pwmChannelA_1, 150);
  ledcWrite(pwmChannelA_2, 0);
  delay(2000);

  //Parado
  ledcWrite(pwmChannelA_1, 0);
  ledcWrite(pwmChannelA_2, 0);
  ledcWrite(pwmChannelB_1, 0);
  ledcWrite(pwmChannelB_2, 0);
  delay(1000);
  
  //Direita
  ledcWrite(pwmChannelB_1, 150);
  ledcWrite(pwmChannelB_2, 0);
  delay(2000);

  
  //Parado
  ledcWrite(pwmChannelB_1, 0);
  ledcWrite(pwmChannelA_1, 0);
  ledcWrite(pwmChannelA_2, 0);
  ledcWrite(pwmChannelB_1, 0);
  ledcWrite(pwmChannelB_2, 0);
  delay(1000);

  //Frente
  ledcWrite(pwmChannelA_1, 0);
  ledcWrite(pwmChannelA_2, 200);
  ledcWrite(pwmChannelB_1, 0);
  ledcWrite(pwmChannelB_2, 200);
  delay(3000);
  
  delay(10);
}
