

void help() {
  Serial.println("stopDemo(): Stoppt den Hardware-Timer und somit die Ausführung beider zuvor definierten Demos.");
  Serial.println("clearDisplay(): Löscht den Pufferspeicher und aktualisiert die Darstellung des LC-Displays.");
  Serial.println("runRotatingBarDemo(): eine Funktion, die auf dem Display (zentriert) einen sich rotierenden Balken produziert.");
  Serial.println("runStudentIdDemo():  Funktion zur abwechselnden Darstellung der Daten aller Teilnehmer der Gruppe. Wechselt die Daten alle 5 Sekunden aus.");
  Serial.println("setContrast(<value>): Funktion zur Einstellung des Kontrastes des LC-Displays. 〈value〉 hat einen Wertebereich von 0.0 - 1.0.");
}

void stopDemo() {
  
}

void clearDisplay() {
  
}

void runRotatingBarDemo() {
  
}

void runStudentIdDemo() {
  
}

void setContrast(String input) {
  double contrast = input.substring(12,15).toDouble();
  
}


boolean checkInput(String input) {
  //help
   if(input.substring(0,6) == "help()") {
    Serial.println("Hilfe Modus");
    help();
   }
   //stopDemo
   else if(input.substring(0,10) == "stopDemo()") {
    Serial.println("Stoppe Demo");
    stopDemo();
   }
   //clearDisplay
   else if(input.substring(0,14) == "clearDisplay()") {
    Serial.println("Aktualisiere das Display");
    clearDisplay();
   }
   //RotatingBarDemo
   else if(input.substring(0,20) == "runRotatingBarDemo()") {
    Serial.println("Zeige rotierenden Balken");
    runRotatingBarDemo();
   }
   //StudentDemo
   else if(input.substring(0,18) == "runStudentIdDemo()") {
    Serial.println("Student Id");
    runStudentIdDemo();
   }
   //Contrast
   //Bsp: setContrast(1.0), setContrast(0.5) 
   else if(input.substring(0,12) == "setContrast(") {
    if(input.substring(13,14) == ",") {
      Serial.println("Falsches Zahlenformat");
    }
    else if(input.length() < 15) {
      Serial.println("Falscher Parameter"); 
    }
    else {
      Serial.println("Stelle Contrast ein");
      setContrast(input);
    }
   }
   //Sonst
   else {
    Serial.print("Eingabe: ");
    Serial.println(input);
    Serial.println("Kein gültiger Befehl");
   }
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  while (Serial.available() > 0) {
    String input = Serial.readString();
    checkInput(input);
  }
}
