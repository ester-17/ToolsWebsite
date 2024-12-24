/*
//Programa: Conectando Sensor Ultrassonico HC-SR04 ao Arduino
//Autor: MakerHero
 
//Carrega a biblioteca do sensor ultrassonico
#include <Ultrasonic.h>
 
//Define os pinos para o trigger e echo
#define pino_trigger 4
#define pino_echo 5
 
//Inicializa o sensor nos pinos definidos acima
Ultrasonic ultrasonic(pino_trigger, pino_echo);
 
void setup()
{
  Serial.begin(9600);
  Serial.println("Lendo dados do sensor...");
}
 
void loop()
{
  //Le as informacoes do sensor, em cm e pol
  float cmMsec, inMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  inMsec = ultrasonic.convert(microsec, Ultrasonic::IN);
  //Exibe informacoes no serial monitor
  Serial.print("Distancia em cm: ");
  Serial.print(cmMsec);
  Serial.print(" - Distancia em polegadas: ");
  Serial.println(inMsec);
  delay(1000);
}
*/

#include <Servo.h>
#include <Ultrasonic.h>

//Define os pinos para o trigger e echo
Ultrasonic ultrasound1(4, 5);
Ultrasonic ultrasound2(6, 7);
Ultrasonic ultrasound3(8, 9);

Servo trava;
//DECLARAÇÕES DO PAQUÍMETRO==============================================================================================================
int paqLiberarBtn = 2; // BOTÃO LIBERAR 2
int paqSensorBtn = 4;  //SENSOR 4
int paqFecharBtn = 7;  // BOTÃO FECHAR 7

int paqLiberarLED = 11;	//LED LIBERAR
int paqSensorLED = 10;	//LED SENSOR
int paqFecharLED = 9;	//LED FECHAR
int paqTravaAbertaLED = 13;  //estado aberto da trava
int paqTravaFechadaLED = 12; //estado fechado da trava
int paqEstado_ferramentaLED = 1;  //estado da ferramenta
 
int paqCount = 0;

int paqAberto = 90;
int paqFechado = 0;

int paqContagemSeguranca;
int paqCountTrava = 0;
int paqCountSensor = 0;

bool paqLiberarLEDstate; // VARIÁVEL LIBERAR
bool paqFecharLEDstate = 1;	//VARIÁVEL FECHAR
bool paqTravaState;  //estado da trava
bool paqTravaAbertaLEDstate = 0; //estado do led da trava aberta
bool paqTravaFechadaLEDstate = 1;  //estado do led da trava fechada
bool paqEstado_ferramentaLEDstate = 0;  //ferramenta dentro da trava

//DECLARAÇÕES DO MISMATCH==================================================================================================================
int misLiberarBtn = 2; // BOTÃO LIBERAR 2
int misSensorBtn = 4;  //SENSOR 4
int misFecharBtn = 7;  // BOTÃO FECHAR 7

int misLiberarLED = 11;	//LED LIBERAR
int misSensorLED = 10;	//LED SENSOR
int misFecharLED = 9;	//LED FECHAR
int misTravaAbertaLED = 13;  //estado aberto da trava
int misTravaFechadaLED = 12; //estado fechado da trava
int misEstado_ferramentaLED = 1;  //estado da ferramenta
 
int misCount = 0;

int misAberto = 90;
int misFechado = 0;

int misContagemSeguranca;
int misCountTrava = 0;
int paqCountSensor = 0;

bool misLiberarLEDstate; // VARIÁVEL LIBERAR
bool misFecharLEDstate = 1;	//VARIÁVEL FECHAR
bool misTravaState;  //estado da trava
bool misTravaAbertaLEDstate = 0; //estado do led da trava aberta
bool misTravaFechadaLEDstate = 1;  //estado do led da trava fechada
bool misEstado_ferramentaLEDstate = 0;  //ferramenta dentro da trava

//DECLARAÇÕES DO CENTRALIZADOR==================================================================================================================
int cenLiberarBtn = 2; // BOTÃO LIBERAR 2
int cenSensorBtn = 4;  //SENSOR 4
int cenFecharBtn = 7;  // BOTÃO FECHAR 7

int cenLiberarLED = 11;	//LED LIBERAR
int cenSensorLED = 10;	//LED SENSOR
int cenFecharLED = 9;	//LED FECHAR
int cenTravaAbertaLED = 13;  //estado aberto da trava
int cenTravaFechadaLED = 12; //estado fechado da trava
int cenEstado_ferramentaLED = 1;  //estado da ferramenta
 
int cenCount = 0;

int cenAberto = 90;
int cenFechado = 0;

int cenContagemSeguranca;
int cenCountTrava = 0;
int cenCountSensor = 0;

bool cenLiberarLEDstate; // VARIÁVEL LIBERAR
bool cenFecharLEDstate = 1;	//VARIÁVEL FECHAR
bool cenTravaState;  //estado da trava
bool cenTravaAbertaLEDstate = 0; //estado do led da trava aberta
bool cenTravaFechadaLEDstate = 1;  //estado do led da trava fechada
bool cenEstado_ferramentaLEDstate = 0;  //ferramenta dentro da trava
//======================================================================================================================================================


//Inicializa o sensor nos pinos definidos acima
Ultrasonic ultrasonic(pino_trigger, pino_echo);
 
void setup()
{
  Serial.begin(9600);
  //Declara o estado da trava
  trava.write(paqFechado);
  paqTravaState = 0;

  trava.write(misFechado);
  misTravaState = 0;

  trava.write(cenFechado);
  cenTravaState = 0;
//DECLARA PAQUIMETRO
  pinMode(paqLiberarBtn, INPUT_PULLUP); // define o pino do botao como entrada
  pinMode(paqFecharBtn, INPUT_PULLUP);
  pinMode(paqLiberarLED, OUTPUT);// define LED como saida
  pinMode(paqSensorLED, OUTPUT);
  pinMode(paqFecharLED, OUTPUT);
  pinMode(paqTravaAbertaLED, OUTPUT);
  pinMode(paqTravaFechadaLED, OUTPUT);
  pinMode(paqEstado_ferramentaLED, OUTPUT);  //define LED como saída
//DECLARA MISMATCH
  pinMode(misLiberarBtn, INPUT_PULLUP); // define o pino do botao como entrada
  pinMode(misFecharBtn, INPUT_PULLUP);
  pinMode(misLiberarLED, OUTPUT);// define LED como saida
  pinMode(misSensorLED, OUTPUT);
  pinMode(misFecharLED, OUTPUT);
  pinMode(misTravaAbertaLED, OUTPUT);
  pinMode(misTravaFechadaLED, OUTPUT);
  pinMode(misEstado_ferramentaLED, OUTPUT);  //define LED como saída
//DECLARA CENTRALIZADOR
  pinMode(cenLiberarBtn, INPUT_PULLUP); // define o pino do botao como entrada
  pinMode(cenFecharBtn, INPUT_PULLUP);
  pinMode(cenLiberarLED, OUTPUT);// define LED como saida
  pinMode(cenSensorLED, OUTPUT);
  pinMode(cenFecharLED, OUTPUT);
  pinMode(cenTravaAbertaLED, OUTPUT);
  pinMode(cenTravaFechadaLED, OUTPUT);
  pinMode(cenEstado_ferramentaLED, OUTPUT);  //define LED como saída
  
  trava.attach(8);
}
 
void loop()
{
  //LE AS DISTÂNCIAS
  int paqDistancia;
  int misDistancia;
  int cenDistancia;
//PAQUIMETRO
  int paqPresente = 1;
  int paqAusente = 0;
  bool paqFerramenta;
//MISMATCH
  int misPresente = 1;
  int misAusente = 0;
  bool misFerramenta;
//CENTRALIZADOR
  int cenPresente = 1;
  int cenAusente = 0;
  bool cenFerramenta;
  //EXIBE DISTÂNCIAS NO SERIAL
  Serial.print("Distancia em cm: ");
  Serial.printn(paqDistancia);
  Serial.printn(misDistancia);
  Serial.print(cenDistancia);
  delay(1000);
  //====================================================================//====================================================================//====================================================================
//PAQUIMETRO
  paqContagemSeguranca = 0;  
  trava.write(paqFechado);
  paqTravaState = 0;
  paqLiberarLEDstate = 0;
  paqFecharLEDstate = 1;
  paqTravaAbertaLEDstate = 0;
  paqTravaFechadaLEDstate = 1;
//MISMATCH
  misContagemSeguranca = 0;  
  trava.write(misFechado);
  misTravaState = 0;
  misLiberarLEDstate = 0;
  misFecharLEDstate = 1;
  misTravaAbertaLEDstate = 0;
  misTravaFechadaLEDstate = 1;
//CENTRALIZADOR
  cenContagemSeguranca = 0;  
  trava.write(cenFechado);
  cenTravaState = 0;
  cenLiberarLEDstate = 0;
  cenFecharLEDstate = 1;
  cenTravaAbertaLEDstate = 0;
  cenTravaFechadaLEDstate = 1;

//PAQUIMETRO
  if (digitalRead(paqLiberarBtn) == LOW) // Se o botão for pressionado
  {
    paqFecharLEDstate =! paqFecharLEDstate;	//fechar = 0
    digitalWrite(paqFecharLED, paqFecharLEDstate);	//desligar fecharLED

    paqLiberarLEDstate =! paqLiberarLEDstate; // liberar = 1
    digitalWrite(paqliberarLED, paqliberarLEDstate);  //liga o liberarLED

    paqTravaAbertaLEDstate != paqTravaAbertaLEDstate;
    digitalWrite(paqTravaAbertaLED, paqTravaAbertaLED);

    delay(100);
  }

  if (paqLiberarLEDstate == 1)
  {
    trava.write(paqAberto);
    paqTravaState = 1; //trava aberta
    delay(100);    //ESPERAR 1S PARA LEITURA DO SENSOR P/ Ñ DAR ERRO

    //============================ contagem ======================================
    paqContagem(10);  //começa a contagem regressiva
    Serial.print("Eu voltei para o liberarLEDstate, de onde eu vim.\n");
    delay(100);
  }
  if(paqDistancia >= 250)
    {
      Serial.print("A ferramenta está ausente.\n");
      paqFerramenta = paqAusente;
    }
    else
    {
      Serial.print("A ferramenta está presente.\n");
      paqFerramenta = paqPresente;
    }
    delay(100);
  }

//MISMATCH
if (digitalRead(misLiberarBtn) == LOW) // Se o botão for pressionado
  {
    misFecharLEDstate =! misFecharLEDstate;	//fechar = 0
    digitalWrite(misFecharLED, misFecharLEDstate);	//desligar fecharLED

    misLiberarLEDstate =! misLiberarLEDstate; // liberar = 1
    digitalWrite(paqliberarLED, paqliberarLEDstate);  //liga o liberarLED

    misTravaAbertaLEDstate != misTravaAbertaLEDstate;
    digitalWrite(misTravaAbertaLED, misTravaAbertaLED);

    delay(100);
  }

  if (misLiberarLEDstate == 1)
  {
    trava.write(pmisAberto);
    misTravaState = 1; //trava aberta
    delay(100);    //ESPERAR 1S PARA LEITURA DO SENSOR P/ Ñ DAR ERRO

    //============================ contagem ======================================
    misContagem(10);  //começa a contagem regressiva
    Serial.print("Eu voltei para o liberarLEDstate, de onde eu vim.\n");
    delay(100);
  }
  if(misDistancia >= 250)
    {
      Serial.print("A ferramenta está ausente.\n");
      misFerramenta = misAusente;
    }
    else
    {
      Serial.print("A ferramenta está presente.\n");
      misFerramenta = misPresente;
    }
    delay(100);
  }

//CENTRALIZADOR
if (digitalRead(cenLiberarBtn) == LOW) // Se o botão for pressionado
  {
    cenFecharLEDstate =! cenFecharLEDstate;	//fechar = 0
    digitalWrite(cenFecharLED, cenFecharLEDstate);	//desligar fecharLED

    cenLiberarLEDstate =! cenLiberarLEDstate; // liberar = 1
    digitalWrite(cenliberarLED, cenliberarLEDstate);  //liga o liberarLED

    cenTravaAbertaLEDstate != cenTravaAbertaLEDstate;
    digitalWrite(cenTravaAbertaLED, cenTravaAbertaLED);

    delay(100);
  }

  if (cenLiberarLEDstate == 1)
  {
    trava.write(cenAberto);
    cenTravaState = 1; //trava aberta
    delay(100);    //ESPERAR 1S PARA LEITURA DO SENSOR P/ Ñ DAR ERRO

    //============================ contagem ======================================
    cenContagem(10);  //começa a contagem regressiva
    Serial.print("Eu voltei para o liberarLEDstate, de onde eu vim.\n");
    delay(100);
  }
  if(cenDistancia >= 250)
    {
      Serial.print("A ferramenta está ausente.\n");
      cenFerramenta = cenAusente;
    }
    else
    {
      Serial.print("A ferramenta está presente.\n");
      cenFerramenta = cenPresente;
    }
    delay(100);
  }

  //====================================================================//====================================================================//====================================================================
}
//=========================================================== PAQUIMETRO ===========================================================
void paqContagem(int paq_tempo_contagem)
{
  paqContagemSeguranca = paq_tempo_contagem;
  //ENQUANTO CONTAGEM NÃO ACABAR
  while(paqContagemSeguranca>0)
  {
    Serial.print(paqContagemSeguranca);
    Serial.print("\n");
    //SE CLICAR FECHAR
    // Ir para uma função int e executar tudo, desde o ligamento/desligamento dos leds até fechar a trava. 
    for(int i=10;i>=0;i--)
    {
      if (digitalRead(paqFecharBtn) == LOW) 
      {
      paqFecharLEDstate =! paqFecharLEDstate; // fechar = 1
      digitalWrite(paqFecharLED, paqFecharLEDstate); //liga o fecharLED
      paqFechar(0, 0);
      } 
      delay(100);
    }
    paqContagemSeguranca--;
    Serial.print("Dentro do while =====================.\n");
    //SE A CONTAGEM ACABAR
    if (paqContagemSeguranca == 0)
    {
      //mudar a ordem da conta da contagem, fazer condicionais primeiro, para n dar erro de ele começar a ler novamente e aparecer o primeiro número da contagem
      Serial.print("Tempo finalizado.\n");
      delay(200);
      paqFechar(0, 0); 
      Serial.print("Dentro da contagemSeguranca igual a 1 =================\n");
      delay(100);
      
    }     
    if(paqTravaState == 0)
    {
      break;
    }
    //SE SENSOR FOR DESATIVADO
    if(paqDistancia >= 250)
    {
      Serial.print("A ferramenta está ausente.\n");
      paqFerramenta = paqAusente;
    }
    else
    {
      Serial.print("A ferramenta está presente.\n");
      paqFerramenta = paqPresente;
    }
    delay(100);
  }
  Serial.print("Dentro do void contagem =====================.\n");
  paqContagemSeguranca = 0;
}
void paqFechar(int paqEstado_trava, int paqTrava_State)
{
  Serial.print("Fechando trava...\n");
  trava.write(paqEstado_trava);
  paqTravaState = paqTrava_State;  
  paqTravaFechadaLEDstate != paqTravaFechadaLEDstate; //travaFechada = 1
  digitalWrite(paqTravaFechadaLED, paqTravaFechadaLED); //liga travaFechadaLED
  paqLiberarLEDstate =! paqLiberarLEDstate; //liberar = 0
  digitalWrite(paqLiberarLED, paqLiberarLEDstate);  //desliga liberarLED
  paqTravaAbertaLEDstate != paqTravaAbertaLEDstate; //travaAberta = 0
  digitalWrite(paqTravaAbertaLED, paqTravaAbertaLEDstate);  //desliga travaAbertaLED
  delay(500);
  Serial.print("Trava fechada.\n");
  delay(500);
  Serial.print("=============================================.\n");
  
}
//=========================================================== MISMATCH ===========================================================
void misContagem(int mis_tempo_contagem)
{
  misContagemSeguranca = mis_tempo_contagem;
  //ENQUANTO CONTAGEM NÃO ACABAR
  while(misContagemSeguranca>0)
  {
    Serial.print(misContagemSeguranca);
    Serial.print("\n");
    //SE CLICAR FECHAR
    // Ir para uma função int e executar tudo, desde o ligamento/desligamento dos leds até fechar a trava. 
    for(int i=10;i>=0;i--)
    {
      if (digitalRead(misFecharBtn) == LOW) 
      {
      misFecharLEDstate =! misFecharLEDstate; // fechar = 1
      digitalWrite(misFecharLED, misFecharLEDstate); //liga o fecharLED
      misFechar(0, 0);
      } 
      delay(100);
    }
    misContagemSeguranca--;
    Serial.print("Dentro do while =====================.\n");
    //SE A CONTAGEM ACABAR
    if (misContagemSeguranca == 0)
    {
      //mudar a ordem da conta da contagem, fazer condicionais primeiro, para n dar erro de ele começar a ler novamente e aparecer o primeiro número da contagem
      Serial.print("Tempo finalizado.\n");
      delay(200);
      misFechar(0, 0); 
      Serial.print("Dentro da contagemSeguranca igual a 1 =================\n");
      delay(100);
      
    }     
    if(misTravaState == 0)
    {
      break;
    }
    //SE SENSOR FOR DESATIVADO
    if(misDistancia >= 250)
    {
      Serial.print("A ferramenta está ausente.\n");
      misFerramenta = misAusente;
    }
    else
    {
      Serial.print("A ferramenta está presente.\n");
      misFerramenta = misPresente;
    }
    delay(100);
  }
  Serial.print("Dentro do void contagem =====================.\n");
  misContagemSeguranca = 0;
}
void misFechar(int misEstado_trava, int misTrava_State)
{
  Serial.print("Fechando trava...\n");
  trava.write(misEstado_trava);
  misTravaState = misTrava_State;  
  misTravaFechadaLEDstate != misTravaFechadaLEDstate; //travaFechada = 1
  digitalWrite(misTravaFechadaLED, misTravaFechadaLED); //liga travaFechadaLED
  misLiberarLEDstate =! misLiberarLEDstate; //liberar = 0
  digitalWrite(misLiberarLED, misLiberarLEDstate);  //desliga liberarLED
  misTravaAbertaLEDstate != misTravaAbertaLEDstate; //travaAberta = 0
  digitalWrite(misTravaAbertaLED, misTravaAbertaLEDstate);  //desliga travaAbertaLED
  delay(500);
  Serial.print("Trava fechada.\n");
  delay(500);
  Serial.print("=============================================.\n");


//=========================================================== CENTRALIZADOR ===========================================================
void cenContagem(int cen_tempo_contagem)
{
  cenContagemSeguranca = cen_tempo_contagem;
  //ENQUANTO CONTAGEM NÃO ACABAR
  while(cenContagemSeguranca>0)
  {
    Serial.print(cenContagemSeguranca);
    Serial.print("\n");
    //SE CLICAR FECHAR
    // Ir para uma função int e executar tudo, desde o ligamento/desligamento dos leds até fechar a trava. 
    for(int i=10;i>=0;i--)
    {
      if (digitalRead(cenFecharBtn) == LOW) 
      {
      cenFecharLEDstate =! cenFecharLEDstate; // fechar = 1
      digitalWrite(cenFecharLED, FecharLEDstate); //liga o fecharLED
      misFechar(0, 0);
      } 
      delay(100);
    }
    misContagemSeguranca--;
    Serial.print("Dentro do while =====================.\n");
    //SE A CONTAGEM ACABAR
    if (cenContagemSeguranca == 0)
    {
      //mudar a ordem da conta da contagem, fazer condicionais primeiro, para n dar erro de ele começar a ler novamente e aparecer o primeiro número da contagem
      Serial.print("Tempo finalizado.\n");
      delay(200);
      cenFechar(0, 0); 
      Serial.print("Dentro da contagemSeguranca igual a 1 =================\n");
      delay(100);
      
    }     
    if(cenTravaState == 0)
    {
      break;
    }
    //SE SENSOR FOR DESATIVADO
    if(cenDistancia >= 250)
    {
      Serial.print("A ferramenta está ausente.\n");
      cenFerramenta = cenAusente;
    }
    else
    {
      Serial.print("A ferramenta está presente.\n");
      cenFerramenta = cenPresente;
    }
    delay(100);
  }
  Serial.print("Dentro do void contagem =====================.\n");
  cenContagemSeguranca = 0;
}
void cenFechar(int cenEstado_trava, int cenTrava_State)
{
  Serial.print("Fechando trava...\n");
  trava.write(cenEstado_trava);
  cenTravaState = cenTrava_State;  
  cenTravaFechadaLEDstate != cenTravaFechadaLEDstate; //travaFechada = 1
  digitalWrite(cenTravaFechadaLED, cenTravaFechadaLED); //liga travaFechadaLED
  cenLiberarLEDstate =! cenLiberarLEDstate; //liberar = 0
  digitalWrite(cenLiberarLED, cenLiberarLEDstate);  //desliga liberarLED
  cenTravaAbertaLEDstate != cenTravaAbertaLEDstate; //travaAberta = 0
  digitalWrite(cenTravaAbertaLED, cenTravaAbertaLEDstate);  //desliga travaAbertaLED
  delay(500);
  Serial.print("Trava fechada.\n");
  delay(500);
  Serial.print("=============================================.\n");
}
