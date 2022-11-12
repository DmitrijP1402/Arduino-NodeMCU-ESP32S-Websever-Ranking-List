#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "ESP 32S";          // Hier den Namen des Netzwerk eingeben (Hier im Code Hotspot von meinem Handy)
const char* password = "187=):-)";  // Hier Passwort vom Netzwerk eingeben

WebServer server(80);

#define RXp2 16
#define TXp2 17

int dinoScoreOld = 0;  //Punktzahl
int dinoScoreNew = 0;

int idAlt = 0;  //ID des Spielers
int idNeu = 1;

//String eingabeName;
String eingabePunkte; 

int bubbelsortZaehler = 0;  //bubbelsort
int bubbelsortZaehler1 = 0;
int zahlBubbelsort = 0;

//String nameBubbelsort = "";

int dinoScoreArray[1000];  //Arrays die Daten speichern für die Rangliste
int idArray[1000];
//String nameArray[1000];

void setup() {

  while (!Serial) {
    ;
  }

  Serial.begin(115200);
  delay(100);

  Serial.println("Connecting to ");  // Zum oben angegeben Netwerk verbinden
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {  //überürüfen ob eine Verbindung zum Netwerk besteht oder nicht
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");  //Ausgeben das der NodeMCUESP32S mit dem NEtzwerk verbunden ist
  Serial.println("WiFi connected..!");

  Serial.print("Got IP: ");  //IP Adresse vom NodeMCUESP32S ausgeben
  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect);  //Webserver startet und kann über die IP Adresse erreicht werden
  server.onNotFound(handle_NotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}

void handle_OnConnect() {

  while (Serial.available() > 0)  //Eingabe des Namen über den Seriellen Monitor
  {
    char Zeichen = Serial.read();
    eingabePunkte += Zeichen;

    if (Zeichen == '\n') {            //Punkte über den Seriellen Monitor eingeben
      Serial.print(eingabePunkte);        
      dinoScoreNew = eingabePunkte.toInt();
      eingabePunkte = "";
      Serial.print(dinoScoreNew);
    }
  }

  if (dinoScoreNew != dinoScoreOld) {
    idNeu = idAlt + 1;                  //ID hochzählen
    idAlt = idNeu;

    dinoScoreArray[idNeu] = dinoScoreNew;  //Werte in Arrays legen zum speichern
    idArray[idNeu] = idNeu;
    //nameArray[idNeu] = eingabeName;
    //eingabeName = "";

    for (bubbelsortZaehler = 1; bubbelsortZaehler < 1000; bubbelsortZaehler++)  //BubbelSort (Sortieren) von der ID, Punktzahl und dem Namen
    {
      for (bubbelsortZaehler1 = bubbelsortZaehler; bubbelsortZaehler1 < 1000; bubbelsortZaehler1++) {
        if (dinoScoreArray[bubbelsortZaehler1] > dinoScoreArray[bubbelsortZaehler]) {
          zahlBubbelsort = dinoScoreArray[bubbelsortZaehler];
          dinoScoreArray[bubbelsortZaehler] = dinoScoreArray[bubbelsortZaehler1];
          dinoScoreArray[bubbelsortZaehler1] = zahlBubbelsort;

          zahlBubbelsort = idArray[bubbelsortZaehler];
          idArray[bubbelsortZaehler] = idArray[bubbelsortZaehler1];
          idArray[bubbelsortZaehler1] = zahlBubbelsort;

          /*nameBubbelsort = nameArray[bubbelsortZaehler];
          nameArray[bubbelsortZaehler] = nameArray[bubbelsortZaehler1];
          nameArray[bubbelsortZaehler1] = nameBubbelsort;*/
        }
      }
    }
    //Daten in den Arrays an den Webserver senden
    server.send(200, "text/html", SendHTML(dinoScoreArray[1], idArray[1], dinoScoreArray[2], idArray[2], dinoScoreArray[3], idArray[3], dinoScoreArray[4], idArray[4], dinoScoreArray[5], idArray[5], dinoScoreArray[6], idArray[6], dinoScoreArray[7], idArray[7], dinoScoreArray[8], idArray[8], dinoScoreArray[9], idArray[9], dinoScoreArray[10], idArray[10])); //, nameArray[1], nameArray[2], nameArray[3], nameArray[4], nameArray[5], nameArray[6], nameArray[7], nameArray[8], nameArray[9], nameArray[10]
    dinoScoreOld = dinoScoreNew;
    dinoScoreNew = 0;
  } else {  //Daten in den Arrays an den Webserver senden falls sich nichts an der Punktzahl aendert
    server.send(200, "text/html", SendHTML(dinoScoreArray[1], idArray[1], dinoScoreArray[2], idArray[2], dinoScoreArray[3], idArray[3], dinoScoreArray[4], idArray[4], dinoScoreArray[5], idArray[5], dinoScoreArray[6], idArray[6], dinoScoreArray[7], idArray[7], dinoScoreArray[8], idArray[8], dinoScoreArray[9], idArray[9], dinoScoreArray[10], idArray[10])); // ,nameArray[1], nameArray[2], nameArray[3], nameArray[4], nameArray[5], nameArray[6], nameArray[7], nameArray[8], nameArray[9], nameArray[10]
  }
}

void handle_NotFound() {  //Server funktioniert nicht/nicht aufrubar
  server.send(404, "text/plain", "Not found");
}

// Webseite mit HTML und CSS mit einer Tabbelle & Überschrift &  Daten werden an den vorgesehenen Stellen angezeigt
String SendHTML(int punktzahl1, float id1, int punktzahl2, float id2, int punktzahl3, float id3, int punktzahl4, float id4, int punktzahl5, float id5, int punktzahl6, float id6, int punktzahl7, float id7, int punktzahl8, float id8, int punktzahl9, float id9, int punktzahl10, float id10) { //, String name1, String name2, String name3, String name4, String name5, String name6, String name7, String name8, String name9, String name10
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>ESP32 Webserver Dino Co. Ltd.</title>\n";
  ptr += "<style>html {font-family: Calibri; display: inline-block; margin: 0px auto; text-align: center;background-color: black;font-size: 30px;color: white;}\n";
  ptr += "body{margin-top: 30px;}\n";
  ptr += "h1 {color: white;margin: 20px auto 30px;}\n";
  ptr += "p {color: white;margin-bottom: 10px;}\n";
  ptr += "table {bordercolor:white; text-align: center;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<div id=\"webpage\">\n";
  ptr += "<h1>Dino Co. Ltd.</h1>\n";
  ptr += "<table align=center border=5 cellpadding=50><tr><th>Platz</th><th>ID</th><th>Punktzahl</th></tr>\n"; //<th>Name</th>
  ptr += "<tr><td>1</td><td>\n";
  ptr += (int)id1;
  //ptr += "</td><td>\n";
  //ptr += (String)name1;
  ptr += "</td><td>\n";
  ptr += (int)punktzahl1;
  ptr += "</td></tr>\n";
  ptr += "<tr><td>2</td><td>\n";
  ptr += (int)id2;
  //ptr += "</td><td>\n";
  //ptr += (String)name2;
  ptr += "</td><td>\n";
  ptr += (int)punktzahl2;
  ptr += "<tr><td>3</td><td>\n";
  ptr += (int)id3;
  //ptr += "</td><td>\n";
  //ptr += (String)name3;
  ptr += "</td><td>\n";
  ptr += (int)punktzahl3;
  ptr += "<tr><td>4</td><td>\n";
  ptr += (int)id4;
  //ptr += "</td><td>\n";
  //ptr += (String)name4;
  ptr += "</td><td>\n";
  ptr += (int)punktzahl4;
  ptr += "<tr><td>5</td><td>\n";
  ptr += (int)id5;
  //ptr += "</td><td>\n";
  //ptr += (String)name5;
  ptr += "</td><td>\n";
  ptr += (int)punktzahl5;
  ptr += "<tr><td>6</td><td>\n";
  ptr += (int)id6;
  //ptr += "</td><td>\n";
  //ptr += (String)name6;
  ptr += "</td><td>\n";
  ptr += (int)punktzahl6;
  ptr += "<tr><td>7</td><td>\n";
  ptr += (int)id7;
  //ptr += "</td><td>\n";
  //ptr += (String)name7;
  ptr += "</td><td>\n";
  ptr += (int)punktzahl7;
  ptr += "<tr><td>8</td><td>\n";
  ptr += (int)id8;
  //ptr += "</td><td>\n";
  //ptr += (String)name8;
  ptr += "</td><td>\n";
  ptr += (int)punktzahl8;
  ptr += "<tr><td>9</td><td>\n";
  ptr += (int)id9;
  //ptr += "</td><td>\n";
  //ptr += (String)name9;
  ptr += "</td><td>\n";
  ptr += (int)punktzahl9;
  ptr += "<tr><td>10</td><td>\n";
  ptr += (int)id10;
  //ptr += "</td><td>\n";
  //ptr += (String)name10;
  ptr += "</td><td>\n";
  ptr += (int)punktzahl10;
  ptr += "</td></tr></table>\n";
  ptr += "</div>\n";
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}
