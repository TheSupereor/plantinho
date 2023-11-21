# include "U8glib.h"

int estado = 4;
const int humidPin = A0;
const int butPin = 3;
const int DispSCL = A4;
const int DispSCA = A5;

// plantas
int plantsValues[3][2] = {{50, 20}, {60, 30}, {80, 50}};
String plants[3] = { "cacto", "comum", "suculenta" };

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);

void draw() {
  switch (estado) {
    case 1:
      //AGUA IDEAL
      u8g.drawCircle(20, 20, 14);
      u8g.drawCircle(108, 20, 14);
      u8g.drawCircle(64, 32, 22, U8G_DRAW_LOWER_RIGHT);
      u8g.drawCircle(64, 32, 22, U8G_DRAW_LOWER_LEFT);
      break;
    case 2:
      //AGUA POUCA
      u8g.drawCircle(20, 20, 14);
      u8g.drawCircle(108, 20, 14);
      u8g.drawCircle(64, 40, 22, U8G_DRAW_UPPER_RIGHT);
      u8g.drawCircle(64, 40, 22, U8G_DRAW_UPPER_LEFT);
      break;
    case 3:
      //AGUA MUITO POUCA
      u8g.setFont(u8g_font_osb18);
      u8g.drawStr(20, 20, "X");
      u8g.drawStr(90, 20, "X");
      u8g.drawCircle(64, 40, 22, U8G_DRAW_UPPER_RIGHT);
      u8g.drawCircle(64, 40, 22, U8G_DRAW_UPPER_LEFT);
      // statements
      break;
    case 4:
      //AGUA DEMAIS
      u8g.drawDisc(20, 20, 14, U8G_DRAW_UPPER_RIGHT);
      u8g.drawDisc(20, 20, 14, U8G_DRAW_LOWER_LEFT);
      u8g.drawDisc(108, 20, 14, U8G_DRAW_UPPER_RIGHT);
      u8g.drawDisc(108, 20, 14, U8G_DRAW_LOWER_LEFT);

      u8g.drawCircle(24, 50, 10, U8G_DRAW_UPPER_RIGHT);
      u8g.drawCircle(24, 50, 10, U8G_DRAW_UPPER_LEFT);
      u8g.drawCircle(44, 50, 10, U8G_DRAW_LOWER_RIGHT);
      u8g.drawCircle(44, 50, 10, U8G_DRAW_LOWER_LEFT);
      u8g.drawCircle(64, 50, 10, U8G_DRAW_UPPER_RIGHT);
      u8g.drawCircle(64, 50, 10, U8G_DRAW_UPPER_LEFT);
      u8g.drawCircle(84, 50, 10, U8G_DRAW_LOWER_RIGHT);
      u8g.drawCircle(84, 50, 10, U8G_DRAW_LOWER_LEFT);
      u8g.drawCircle(104, 50, 10, U8G_DRAW_UPPER_RIGHT);
      u8g.drawCircle(104, 50, 10, U8G_DRAW_UPPER_LEFT);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(humidPin, INPUT);
  pinMode(pinoBotao, INPUT_PULLUP);
  int planta = 0;
}

void loop() {
  // mudar planta
  if(digitalRead(butPin) == HIGH && planta < 2){
    planta++;
    u8g.setFont(u8g_font_osb18);
    u8g.drawStr(20, 20, plants[planta]);
  }else if(digitalRead(butPin) == HIGH && planta = 2){
    planta = 0;
    u8g.setFont(u8g_font_osb18);
    u8g.drawStr(20, 20, plants[planta]);
  };
  
  u8g.firstPage();
  do {
    draw();
  } while (u8g.nextPage());
  delay(1000);

  int result = analogRead(humidPin);
  Serial.println("umidade");
  Serial.println(result);
  int hpercentage = map(result, 1023, 0, 0, 100);
  Serial.println("percent");
  Serial.println(hpercentage);

  if (hpercentage >= plantsValues[planta][0]) {
    estado = 4; // agua demais
  } else if (hpercentage < plantsValues[planta][0] && hpercentage >= plantsValues[planta][1]) {
    estado = 1; // ideal
  } else if (hpercentage < plantsValues[planta][1]) {
    estado = 2; // pouca
  }
}