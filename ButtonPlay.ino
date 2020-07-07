  boolean currentState1 = LOW;//storage for current button state
  boolean lastState1 = LOW;//storage for last button state
  int counter = 0;             // Variable de compteur

 
void setup() 
{ 

  Serial.begin(9600); 
}

void loop() 
{ 
  //--------------Button normal
  BUTTONPlay(1,5,4);
  BUTTONPlay(2,6,5);
 

}

//--------------------------------CLASSES

void MIDImessage(byte command, byte data1, byte data2) //pass values out through standard Midi Command
{
   Serial.write(command);
   Serial.write(data1);
   Serial.write(data2);
}

void BUTTONPlay (int buttonNumber, int buttonPin, int channel) { //button is ON when push and OFF when repush

  currentState.buttonNumber = digitalRead(buttonPin); // Interrogation du bouton-poussoir
  
  // La valeur précédente du bouton-poussoir est-elle différente de la valeur actuelle ?
  // if it is, the buttonState is HIGH:
  if (currentStatebuttonNumber  != lastStatebuttonNumber ) { 
    if(currentStatebuttonNumber  == HIGH){
      counter++; // Incrémentation du compteur(+1)
    }
    lastStatebuttonNumber  = currentStatebuttonNumber ; // Sauvegarde de la valeur actuelle du bouton-poussoir
   if(counter%2 == 0)                 // La variable du compteur est-elle un nombre pair ?
      MIDImessage(176,channel,1);
   else
      MIDImessage(176,channel,0);
   }

  delay(15);     
}
