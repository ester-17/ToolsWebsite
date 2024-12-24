#include <Servo.h>

/*#define estado_liberar 13
#define estado_fechar 12*/

Servo trava;
int liberarBtn = 2; // BOTÃO LIBERAR 2
int sensorBtn = 4;  //SENSOR 4
int fecharBtn = 7;  // BOTÃO FECHAR 7

int liberarLED = 11;	//LED LIBERAR
int sensorLED = 10;	//LED SENSOR
int fecharLED = 9;	//LED FECHAR
int travaAbertaLED = 13;  //estado aberto da trava
int travaFechadaLED = 12; //estado fechado da trava
int estado_ferramentaLED = 1;  //estado da ferramenta
 
int count = 0;

int aberto = 90;
int fechado = 0;

int contagemSeguranca;
int countTrava = 0;
int countSensor = 0;

//int delay_seguranca = 1000;	//DECLARA O DELAY DE SEGURANÇA COMO 10S 
bool liberarLEDstate; // VARIÁVEL LIBERAR
bool sensorLEDstate = 0;	//VARIÁVEL SENSOR
bool fecharLEDstate = 1;	//VARIÁVEL FECHAR
bool travaState;  //estado da trava
bool travaAbertaLEDstate = 0; //estado do led da trava aberta
bool travaFechadaLEDstate = 1;  //estado do led da trava fechada
bool estado_ferramentaLEDstate = 0;  //ferramenta dentro da trava

/* ou posso usar 
bool travaState = fechado;*/
  
void setup()
{
  Serial.begin(9600);
  
  trava.write(fechado);
  travaState = 0;
  
  pinMode(liberarBtn, INPUT_PULLUP); // define o pino do botao como entrada
  pinMode(sensorBtn, INPUT_PULLUP);
  pinMode(fecharBtn, INPUT_PULLUP);
  pinMode(liberarLED, OUTPUT);// define LED como saida
  pinMode(sensorLED, OUTPUT);
  pinMode(fecharLED, OUTPUT);
  pinMode(travaAbertaLED, OUTPUT);
  pinMode(travaFechadaLED, OUTPUT);
  pinMode(estado_ferramentaLED, OUTPUT);  //define LED como saída
  
  trava.attach(8);
}
void loop()
{
  contagemSeguranca = 0;  
  trava.write(fechado);
  travaState = 0;
  liberarLEDstate = 0;
  fecharLEDstate = 1;
  travaAbertaLEDstate = 0;
  travaFechadaLEDstate = 1;
  //estado_ferramentaLEDstate = 0;
  //BOTÃO LIBERAR
  if (digitalRead(liberarBtn) == LOW) // Se o botão for pressionado
  {
    fecharLEDstate =! fecharLEDstate;	//fechar = 0
    digitalWrite(fecharLED, fecharLEDstate);	//desligar fecharLED

    /*travaFechadaLEDstate != travaFechadaLEDstate; //travaFechada = 0
    digitalWrite(travaFechadaLED, travaFechadaLEDstate);  //desligar travaFechadaLED*/

    liberarLEDstate =! liberarLEDstate; // liberar = 1
    digitalWrite(liberarLED, liberarLEDstate);  //liga o liberarLED

    travaAbertaLEDstate != travaAbertaLEDstate;
    digitalWrite(travaAbertaLED, travaAbertaLED);

    delay(100);
  }

  if (liberarLEDstate == 1)
  {
    //liberarLEDstate =! liberarLEDstate;
    trava.write(aberto);
    travaState = 1; //trava aberta
    delay(100);    //ESPERAR 1S PARA LEITURA DO SENSOR P/ Ñ DAR ERRO

    //============================ contagem ======================================
    contagem(10);  //começa a contagem regressiva
    Serial.print("Eu voltei para o liberarLEDstate, de onde eu vim.\n");
    delay(100);
  }

  if (digitalRead(sensorBtn) == LOW)
    {      
      count++;
      //loop pra saber se é a primeira vez q a pessoa clica
      if (count == 1)
      {
        Serial.print("A ferramenta está presente.\n");
      }
      sensorLEDstate =! sensorLEDstate; //sensor = 1
      digitalWrite(sensorLED, sensorLEDstate);  //liga o sensorLED
      /*estado_ferramentaLEDstate != estado_ferramentaLEDstate;   //estado_ferramenta = 1 
      digitalWrite(estado_ferramentaLED, estado_ferramentaLEDstate); //liga o estado_ferramentaLED*/
      delay(100);
    }    
}

void contagem(int tempo_contagem)
{
  contagemSeguranca = tempo_contagem;
   //ENQUANTO CONTAGEM NÃO ACABAR
   while(contagemSeguranca>0)
    {
      Serial.print(contagemSeguranca);
      Serial.print("\n");
      //SE CLICAR FECHAR
      // Ir para uma função int e executar tudo, desde o ligamento/desligamento dos leds até fechar a trava. 
      for(int i=10;i>=0;i--)
      {
        if (digitalRead(fecharBtn) == LOW) 
        {
        fecharLEDstate =! fecharLEDstate; // fechar = 1
        digitalWrite(fecharLED, fecharLEDstate); //liga o fecharLED
        fechar(0, 0);
  	    } 
        delay(100);
      }
      contagemSeguranca--;
      Serial.print("Dentro do while =====================.\n");
      //SE A CONTAGEM ACABAR
      if (contagemSeguranca == 0)
      {
        //mudar a ordem da conta da contagem, fazer condicionais primeiro, para n dar erro de ele começar a ler novamente e aparecer o primeiro número da contagem
        Serial.print("Tempo finalizado.\n");
        delay(200);
        fechar(0, 0); 
        Serial.print("Dentro da contagemSeguranca igual a 1 =================\n");
        delay(100);
        
      }     
      if(travaState == 0)
      {
        break;
      }
     //SE SENSOR FOR DESATIVADO
    if (digitalRead(sensorBtn) == LOW)
    {
      sensorLEDstate =! sensorLEDstate;
      digitalWrite(sensorLED, sensorLEDstate);
      estado_ferramentaLEDstate =! estado_ferramentaLEDstate;   //estado_ferramenta = 1 
      digitalWrite(estado_ferramentaLED, estado_ferramentaLEDstate); //liga o estado_ferramentaLED
      delay(100);
      count = 0;
      sensor(0);
    }
      
   }
  Serial.print("Dentro do void contagem =====================.\n");
  contagemSeguranca = 0;
}
void fechar(int estado_trava, int trava_State)
{
  Serial.print("Fechando trava...\n");
  trava.write(estado_trava);
  travaState = trava_State;  
  /*fecharLEDstate =! fecharLEDstate; // fechar = 1  
  digitalWrite(fecharLED, fecharLEDstate); //liga o fecharLED*/
  travaFechadaLEDstate != travaFechadaLEDstate; //travaFechada = 1
  digitalWrite(travaFechadaLED, travaFechadaLED); //liga travaFechadaLED
  liberarLEDstate =! liberarLEDstate; //liberar = 0
  digitalWrite(liberarLED, liberarLEDstate);  //desliga liberarLED
  travaAbertaLEDstate != travaAbertaLEDstate; //travaAberta = 0
  digitalWrite(travaAbertaLED, travaAbertaLEDstate);  //desliga travaAbertaLED
  delay(500);
  Serial.print("Trava fechada.\n");
  delay(500);
  Serial.print("=============================================.\n");
  
}
void sensor(int sensorID)
{
  int count = 0;
  count++;
  //loop pra saber se é a primeira vez q a pessoa clica
  if (count == 1)
  {
    Serial.print("A ferramenta está presente.");
  }
  estado_ferramentaLEDstate == sensorID;
  digitalWrite(estado_ferramentaLED, estado_ferramentaLEDstate); //desliga o led do estado da ferramenta
  Serial.print("A ferramenta foi retirada. \n");
  delay(100);
}



/* Fazer o led de sinalização do sensor (estado da ferramenta) acender quando a pessoa ativa/desativa o sensor
*/







/*
- fazer um int, para ele rodar somente uma vez e voltar para a origem (ele volta para a origem?)

- fazer ele verificar se o sensor mudou de estado durante a contagem regressiva
e ligar led de estado da ferramenta
*/