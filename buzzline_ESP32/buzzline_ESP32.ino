/*
 * =============================================================================
 *             -   BuzzLine ESP32  - Robô seguidor de linha    -
 * 
 * Para mais informações: https://www.instructables.com/Buzz-Line/
 * =============================================================================
*/

//------Sensores de linha------
const int pinoSensorEsquerdo = 3;
const int pinoSensorDireito = 4;

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

/* valores de PWMval dos motores. quando ligados eles vao atuar
  numa PWMval que vai de 0 a 255. uma PWMval muito alta 
   contribuira para o robo perder a linha uma vez que a inercia
   dos motores fica mais significativa, um valor muito baixo fara
   seu buzzline se dar mau na competicao*/
const int vel = 210;

int nivelSensorEsquerdo; 
int nivelSensorDireito; 

void setup() {
  /*Confuguracao dos pinos de entrada e saida */
  pinMode(pinoSensorEsquerdo, INPUT);
  pinMode(pinoSensorDireito, INPUT);
  pinMode(pinoMotorA_1, OUTPUT);
  pinMode(pinoMotorA_2, OUTPUT);
  pinMode(pinoMotorB_1 , OUTPUT);
  pinMode(pinoMotorB_2 , OUTPUT);
  
  /*como nessa abordagem nao petendemos girar nenhum motor para tras setamos
  os pinos de controle de giro reverso da ponte h para 0 (LOW)*/
  digitalWrite(pinoMotorA_2, LOW);
  digitalWrite(pinoMotorB_2 , LOW);
  
  /*Configuracao da porta serial para visualizar os dados no monitor - lupinha 
    la em cima*/
  Serial.begin(9600);

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
    /* Um temporizador para permitir que visualize as informacoes pela serial
       e tambem respeite a inercia do motor nas atuacoes, um valor muito alto 
       pode comprometer o desempenho do controle */   
    //delay(200); 
    nivelSensorEsquerdo = digitalRead(pinoSensorEsquerdo); 
    nivelSensorDireito = digitalRead(pinoSensorDireito); 

    Serial.print("Nivel Sensor Esquerdo => ");
    Serial.print(nivelSensorEsquerdo);
    Serial.print("/t");
    Serial.print("Nivel Sensor Direito => ");
    Serial.println(nivelSensorDireito);

    // Assumindo uma pista de chão branco e linha preta

    if (nivelSensorEsquerdo==0) {  // Detectou branco (sensor detecta chão fora da linha -> desejado)
      // Motor esquerdo permanece girando
      rodaEsquerda_frente(vel);
    }else if (nivelSensorEsquerdo>0){  // Detectou preto (sensor detecta linha -> indesejado)
         /* caso contrario o motor desliga mas como o outro motor devera estar ligado
         o robo vai virar e corrigir sua tragetoria*/
      rodaEsquerda_frente(0);
    }
    
    /* o mesmo para o outro sensor e motor */
    
    if (nivelSensorDireito==0) {
       rodaDireita_frente(vel);
    }else if(nivelSensorDireito>0){
       rodaDireita_frente(vel);
    }

}

//      -    Funções que controlam os motores/direção das rodas    -
// Obs: Note que a direção do motor para frente e ré dependerá da posição do motor
//      e de como ele está conectado com os fios. Você pode alterá o sentido horário e antihorário
//      antihorário do giro também na programação, trocando o pino que está em PWM/HIGH e 0/LOW.

void rodaDireita_frente(int PWMval) {
  ledcWrite(pwmChannelA_1, 0);
  ledcWrite(pwmChannelA_2, PWMval);
}

void rodaEsquerda_frente(int PWMval) {
  ledcWrite(pwmChannelB_1, PWMval);
  ledcWrite(pwmChannelB_2, 0);
}

void paraRodas() {
  ledcWrite(pwmChannelA_1, 0);
  ledcWrite(pwmChannelA_2, 0);
  ledcWrite(pwmChannelB_1, 0);
  ledcWrite(pwmChannelB_2, 0);
}
