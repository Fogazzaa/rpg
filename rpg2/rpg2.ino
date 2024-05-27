// Declaração de estatísticas do herói e vilão
int vidaheroi = 100;
int vidavilao = 100;

int ataqueheroi = 5;
int ataquevilao = 5;

int defesaheroi = 5;
int defesavilao = 5;

int dadovilao = 0;
int dadoheroi = 0;

int valordadoheroi = 0;

// Controle da condição do botão
bool controledvermelho = false;
bool controledamarelo = false;
bool controledverde = false;

// Definição dos pinos do tinkercad
#define ledvermelho 4
#define ledamarelo 3
#define ledverde 2
#define botaovermelho 5
#define botaoamarelo 6
#define botaoverde 7
#define buzzer 11

// Função do Número Aleatório
long randNumber;

// Declaração dos contadores
int contadorvermelho = 0;
int contadoramarelo = 0;
int contadorverde = 0;
int mensagemerro = 0;

// Declaração das mensagens do jogo
bool mensageminicialexibida = false;
bool mensagemselecaoheroi = false;
bool mensagemselecaovilao = false;
bool heroiselecionado = false;
bool mensagemrolamento1 = false;

// Definição das Notas da música do Início
#define NOTE_B4  494
#define NOTE_B5  988
#define NOTE_FS5 740
#define NOTE_DS5 622
#define NOTE_C5  523
#define NOTE_C6  1047
#define NOTE_G6  1568
#define NOTE_E6  1319
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880

// Início da função da música

int tempo = 105;

int melodia[] = {
  NOTE_B4, 16, NOTE_B5, 16, NOTE_FS5, 16, NOTE_DS5, 16, 
  NOTE_B5, 32, NOTE_FS5, -16, NOTE_DS5, 8, NOTE_C5, 16,
  NOTE_C6, 16, NOTE_G6, 16, NOTE_E6, 16, NOTE_C6, 32, NOTE_G6, -16, NOTE_E6, 8,
  NOTE_B4, 16,  NOTE_B5, 16,  NOTE_FS5, 16,   NOTE_DS5, 16,  NOTE_B5, 32,  
  NOTE_FS5, -16, NOTE_DS5, 8,  NOTE_DS5, 32, NOTE_E5, 32,  NOTE_F5, 32,
  NOTE_F5, 32,  NOTE_FS5, 32,  NOTE_G5, 32,  NOTE_G5, 32, NOTE_GS5, 32,  NOTE_A5, 16, NOTE_B5, 8
};

int notas = sizeof(melodia) / sizeof(melodia[0]) / 2;
int semibreve = (60000 * 4) / tempo;

// Função da música
void playPacmanIntro() {
  for (int estaNota = 0; estaNota < notas * 2; estaNota += 2) {
    int divisor = melodia[estaNota + 1];
    int duracaoNota = (divisor > 0) ? (semibreve / divisor) : (semibreve / abs(divisor) * 1.5);
    tone(buzzer, melodia[estaNota], duracaoNota * 0.9);
    delay(duracaoNota);
    noTone(buzzer);
  }
}

// Função para rolar os dados


void setup() {
  randomSeed(analogRead(0));

  // Declaração dos tipos de cada Eletrônico
  pinMode(botaovermelho, INPUT);
  pinMode(botaoamarelo, INPUT);
  pinMode(botaoverde, INPUT);
  pinMode(ledvermelho, OUTPUT);
  pinMode(ledamarelo, OUTPUT);
  pinMode(ledverde, OUTPUT);
  pinMode(buzzer, OUTPUT);
  randomSeed(analogRead(0));

  Serial.begin(9600);

  delay(1000);

  // Mensagem do início do jogo
  Serial.println("+======================================+\n"
                 "| Bem vindo ao meu jogo. Inicie o jogo |\n"
                 "|   apertando o botao central. Entao   |\n"
                 "|  escolha seu player, Heroi (Verde)   |\n"
                 "|  e Vilao (Vermelho), Boa Sorte !!!   |\n"
                 "+======================================+");
  digitalWrite(ledamarelo, HIGH);

  playPacmanIntro();
}

void loop() {
  // Controle da condição do botão, e quantidade de clicadas
  if (digitalRead(botaovermelho) == HIGH && controledvermelho == false) {
    controledvermelho = true;
    contadorvermelho += 1;
  } else if (digitalRead(botaovermelho) == HIGH && controledvermelho == true) {
    controledvermelho = false;
  }

  if (digitalRead(botaoamarelo) == HIGH && controledamarelo == false) {
    controledamarelo = true;
    contadoramarelo += 1;
  } else if (digitalRead(botaoamarelo) == HIGH && controledamarelo == true) {
    controledamarelo = false;
  }

  if (digitalRead(botaoverde) == HIGH && controledverde == false) {
    controledverde = true;
    contadorverde += 1;
  } else if (digitalRead(botaoverde) == HIGH && controledverde == true) {
    controledverde = false;
  }

  if (controledamarelo == true && contadoramarelo == 1 && mensageminicialexibida == false) {
    Serial.println("+======================================+\n"
                   "| O jogo comecou, o botao esquerdo     |\n"
                   "| escolhe o vilao (led vermelho), e o  |\n"
                   "| direito escolhe o heroi (led verde). |\n"
                   "|       Faca uma boa escolha !!!       |\n"
                   "+======================================+");
    mensageminicialexibida = true;
    digitalWrite(ledamarelo, LOW);
  }

  if (controledverde == true && contadorverde == 1 && mensagemselecaoheroi == false && contadoramarelo == 1) {
    // Mensagem de seleção do herói, e liga led verde
    digitalWrite(ledverde, HIGH);
    Serial.println("+======================================+\n"
                   "| Voce escolheu o heroi !!!            |\n"
                   "| Vida : 100                           |\n"
                   "| Ataque : 5                           |\n"
                   "| Defesa : 5                           |\n"
                   "| Clique no botao central para         |\n"
                   "| rolar o dado !!!                     |\n"
                   "+======================================+");
    mensagemselecaoheroi = true;
  }

  if (controledvermelho == true && contadoramarelo == 1 && contadorverde >= 1 && heroiselecionado == false) {
    digitalWrite(ledvermelho, HIGH);
    Serial.println("+======================================+\n"
                   "| Voce ja selecionou o heroi, a escolha|\n"
                   "| do vilao nao esta disponivel         |\n"
                   "+======================================+");
    delay(1000);
    heroiselecionado = true;
    digitalWrite(ledvermelho, LOW);
  }

  if (controledvermelho == true && contadorvermelho == 1 && mensagemselecaovilao == false && contadoramarelo == 1 && heroiselecionado == false) {
    digitalWrite(ledvermelho, HIGH);
    Serial.println("+======================================+\n"
                   "| Voce escolheu o vilao !!!            |\n"
                   "| Vida : 100                           |\n"
                   "| Ataque : 5                           |\n"
                   "| Defesa : 5                           |\n"
                   "| Clique no botao central para         |\n"
                   "| rolar o dado !!!                     |\n"
                   "+======================================+");
    mensagemselecaovilao = true;
  }

  if (controledverde == true && mensagemselecaoheroi == false && contadoramarelo == 1 && mensagemerro == 0) {
    Serial.println("+======================================+\n"
                   "| Voce escolheu o botao errado !!!     |\n"
                   "| Selecione ou o heroi ou o vilao !    |\n"
                   "+======================================+");
    mensagemerro += 1;
  }

  if (contadoramarelo == 2 && controledamarelo == true && contadorverde == 1 && mensagemrolamento1 == false) {
   Serial.println("+======================================+\n"
                   "| O dado foi rolado !!!                |\n"
                   "| Dado do Vilão:                       |\n"
                   "| Dado do Heroi:                       |\n"
                   "+======================================+");

  }
}
