/********************************************
date:      "13.11.2022"
authors:      "DmitrijP1402 & Nico0123456"
filename:  "webserver_id_score.ino"
********************************************/


#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "insert network name";           // Enter the name of the network here
const char* password = "insert network password";   // Enter password from network here

WebServer server(80);

int ScoreOld = 0;  //Score
int ScoreNew = 0;

int idOld = 0;  //ID from player
int idNew = 1;

//String nameInput;     //Data Input
String pointsInput;

int bubbelsortCounterOne = 0;  //bubbelsort
int bubbelsortCounterTwo = 0;
int bubbelsortNumber = 0;

//String nameBubbelsort = "";

int dinoScoreArray[1000];  //Arrays that store data for the ranking list
int idArray[1000];
//String nameArray[1000];

void setup() {

  while (!Serial) {
    ;
  }

  Serial.begin(115200);
  delay(100);

  Serial.println("Connecting to ");  // Connect to the network
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) { //Check that the NodeMCU ESP32S is connected to the network
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");  //Output that the NodeMCU ESP32S is connected to the network
  Serial.println("WiFi connected..!");

  Serial.print("Got IP: ");  //Output IP address of NodeMCU ESP32S on serial monitor

  server.on("/", handle_OnConnect);  //Web server starts and can be reached via the IP address
  server.onNotFound(handle_NotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}

void handle_OnConnect() {

  while (Serial.available() > 0) {          //Enter points via the serial monitor
    char charactersInput = Serial.read();
    pointsInput += charactersInput;

    if (charactersInput == '\n') {
      ScoreNew = pointsInput.toInt();
      pointsInput = "";
      Serial.println(ScoreNew);
    }
  }

  if (ScoreNew != ScoreOld) {
    idNew = idOld + 1;                  //ID count up
    idOld = idNew;

    dinoScoreArray[idNew] = ScoreNew;  //Put values in arrays to store
    idArray[idNew] = idNew;
    //nameArray[idNew] = nameInput;
    //nameInput = "";

    for (bubbelsortCounterOne = 1; bubbelsortCounterOne < 1000; bubbelsortCounterOne++)  //BubbelSort (Sort) the ID, score and name
    {
      for (bubbelsortCounterTwo = bubbelsortCounterOne; bubbelsortCounterTwo < 1000; bubbelsortCounterTwo++) {
        if (dinoScoreArray[bubbelsortCounterTwo] > dinoScoreArray[bubbelsortCounterOne]) {
          bubbelsortNumber = dinoScoreArray[bubbelsortCounterOne];
          dinoScoreArray[bubbelsortCounterOne] = dinoScoreArray[bubbelsortCounterTwo];
          dinoScoreArray[bubbelsortCounterTwo] = bubbelsortNumber;

          bubbelsortNumber = idArray[bubbelsortCounterOne];
          idArray[bubbelsortCounterOne] = idArray[bubbelsortCounterTwo];
          idArray[bubbelsortCounterTwo] = bubbelsortNumber;

          /*nameBubbelsort = nameArray[bubbelsortCounterOne];
            nameArray[bubbelsortCounterOne] = nameArray[bubbelsortCounterTwo];
            nameArray[bubbelsortCounterTwo] = nameBubbelsort;*/
        }
      }
    }
    //Send data in the arrays to the web server
    server.send(200, "text/html", SendHTML(dinoScoreArray[1], idArray[1], dinoScoreArray[2], idArray[2], dinoScoreArray[3], idArray[3], dinoScoreArray[4], idArray[4], dinoScoreArray[5], idArray[5], dinoScoreArray[6], idArray[6], dinoScoreArray[7], idArray[7], dinoScoreArray[8], idArray[8], dinoScoreArray[9], idArray[9], dinoScoreArray[10], idArray[10])); //, nameArray[1], nameArray[2], nameArray[3], nameArray[4], nameArray[5], nameArray[6], nameArray[7], nameArray[8], nameArray[9], nameArray[10]
    ScoreOld = ScoreNew;
    ScoreNew = 0;
  } else {        //Send data in the arrays to the web server if there is no change in the score
    server.send(200, "text/html", SendHTML(dinoScoreArray[1], idArray[1], dinoScoreArray[2], idArray[2], dinoScoreArray[3], idArray[3], dinoScoreArray[4], idArray[4], dinoScoreArray[5], idArray[5], dinoScoreArray[6], idArray[6], dinoScoreArray[7], idArray[7], dinoScoreArray[8], idArray[8], dinoScoreArray[9], idArray[9], dinoScoreArray[10], idArray[10])); // ,nameArray[1], nameArray[2], nameArray[3], nameArray[4], nameArray[5], nameArray[6], nameArray[7], nameArray[8], nameArray[9], nameArray[10]
  }
}

void handle_NotFound() {                        //Server not working/not available
  server.send(404, "text/plain", "Not found");
}

// Web page with HTML and CSS with a tab & heading & data are displayed in the designated places

  String SendHTML(int scorePosition1, float IdPosition1, int scorePosition2, float IdPosition2, int scorePosition3, float IdPosition3, int scorePosition4, float IdPosition4, int scorePosition5, float IdPosition5, int scorePosition6, float IdPosition6, int scorePosition7, float IdPosition7, int scorePosition8, float IdPosition8, int scorePosition9, float IdPosition9, int scorePosition10, float IdPosition10) { //, String namePosition1, String namePosition2, String namePosition3, String namePosition4, String namePosition5, String namePosition6, String namePosition7, String namePosition8, String namePosition9, String namePosition10
  String  ptr = "<!DOCTYPE html> <html>\n";
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
  ptr += "<h1>headline of the web page</h1>\n";
  ptr += "<table align=center border=5 cellpadding=50><tr><th>Position</th><th>ID</th><th>Score</th></tr>\n"; //<th>Name</th>
  ptr += "<tr><td>1</td><td>\n";
  ptr += (int)IdPosition1;
  //ptr += "</td><td>\n";
  //ptr += (String)namePosition1;
  ptr += "</td><td>\n";
  ptr += (int)scorePosition1;
  ptr += "</td></tr>\n";
  ptr += "<tr><td>2</td><td>\n";
  ptr += (int)IdPosition2;
  //ptr += "</td><td>\n";
  //ptr += (String)namePosition2;
  ptr += "</td><td>\n";
  ptr += (int)scorePosition2;
  ptr += "<tr><td>3</td><td>\n";
  ptr += (int)IdPosition3;
  //ptr += "</td><td>\n";
  //ptr += (String)namePosition3;
  ptr += "</td><td>\n";
  ptr += (int)scorePosition3;
  ptr += "<tr><td>4</td><td>\n";
  ptr += (int)IdPosition4;
  //ptr += "</td><td>\n";
  //ptr += (String)namePosition4;
  ptr += "</td><td>\n";
  ptr += (int)scorePosition4;
  ptr += "<tr><td>5</td><td>\n";
  ptr += (int)IdPosition5;
  //ptr += "</td><td>\n";
  //ptr += (String)namePosition5;
  ptr += "</td><td>\n";
  ptr += (int)scorePosition5;
  ptr += "<tr><td>6</td><td>\n";
  ptr += (int)IdPosition6;
  //ptr += "</td><td>\n";
  //ptr += (String)namePosition6;
  ptr += "</td><td>\n";
  ptr += (int)scorePosition6;
  ptr += "<tr><td>7</td><td>\n";
  ptr += (int)IdPosition7;
  //ptr += "</td><td>\n";
  //ptr += (String)namePosition7;
  ptr += "</td><td>\n";
  ptr += (int)scorePosition7;
  ptr += "<tr><td>8</td><td>\n";
  ptr += (int)IdPosition8;
  //ptr += "</td><td>\n";
  //ptr += (String)namePosition8;
  ptr += "</td><td>\n";
  ptr += (int)scorePosition8;
  ptr += "<tr><td>9</td><td>\n";
  ptr += (int)IdPosition9;
  //ptr += "</td><td>\n";
  //ptr += (String)namePosition9;
  ptr += "</td><td>\n";
  ptr += (int)scorePosition9;
  ptr += "<tr><td>10</td><td>\n";
  ptr += (int)IdPosition10;
  //ptr += "</td><td>\n";
  //ptr += (String)namePosition10;
  ptr += "</td><td>\n";
  ptr += (int)scorePosition10;
  ptr += "</td></tr></table>\n";
  ptr += "</div>\n";
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}
