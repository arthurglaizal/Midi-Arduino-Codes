/* Utilisation du capteur Ultrason HC-SR04 */

// -------définition des broches utilisées 
int trig = 4; 
int echo = 3; 
int buttonpin = 5; 
int pot1 = 0;
//----------------
int val = 0; //Our initial pot values. We need one for the first value and a second to test if there has been a change made. This needs to be done for all 3 pots.
int lastVal = 0; 
int minsr = 3;
int maxsr = 15;
int distancesecure = 10;
int convdistmidi = 8; //  127/maxsr = 8
long lecture_echo; 
long cm;

void setup() 
{ 
  pinMode(trig, OUTPUT); 
  digitalWrite(trig, LOW); 
  pinMode(echo, INPUT); 
  Serial.begin(9600); 
}

void loop() 
{ 
  //--------------Button cue
    val = digitalRead(buttonpin);  // read input value
  if (val == HIGH) {         // 
       MIDImessage(176,2,1); // 
  } else {
       MIDImessage(176,2,0);  // 
  }  
  //--------------Button normal
  BUTTONnorm(6,4);
 
  //--------------Potentiometre
    val = analogRead(pot1)/8;   // Divide by 8 to get range of 0-127 for midi
   if (val != lastVal) // If the value does not = the last value the following command is made. This is because the pot has been turned. Otherwise the pot remains the same and no midi message is output.
   {
   MIDImessage(176,1,val);}         // 176 = CC command (channel 1 control change), 1 = Which Control, val = value read from Potentionmeter 1 NOTE THIS SAYS VAL not VA1 (lowercase of course)
   lastVal = val;
   

  //--------------SR04
  digitalWrite(trig, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trig, LOW); 
  lecture_echo = pulseIn(echo, HIGH); 
  cm = lecture_echo / 58; 

  if ((minsr<cm) &&(cm<maxsr+distancesecure)) {
       if ((cm-minsr)>maxsr)       MIDImessage(176,3,127);
       else MIDImessage(176,3,(cm-minsr)*convdistmidi); 
       
  }
  else {
       MIDImessage(176,3,0);  // 
  }

  delay(10); 
}

//--------------------------------CLASSES
void BUTTONnorm ( int buttonPin, int channel) {
  int counter = 0;             // Variable de compteur
  int buttonValue = 0;         // Variable pour enregistrer l'état du bouton-poussoir
  int previousButtonValue = 0; // Variable pour enregistrer l'ancien état du bouton-poussoir
  buttonValue = digitalRead(buttonPin); // Interrogation du bouton-poussoir
  // La valeur précédente du bouton-poussoir est-elle différente de la valeur actuelle ?
  if(previousButtonValue != buttonValue){
    if(buttonValue == HIGH){
      counter++; // Incrémentation du compteur(+1)
    }
  }
  previousButtonValue = buttonValue; // Sauvegarde de la valeur actuelle du bouton-poussoir
  if(counter%2 == 0)                 // La variable du compteur est-elle un nombre pair ?
    MIDImessage(176,channel,1); 
  else
    MIDImessage(176,channel,0);  
}


void MIDImessage(byte command, byte data1, byte data2) //pass values out through standard Midi Command
{
   Serial.write(command);
   Serial.write(data1);
   Serial.write(data2);
}
