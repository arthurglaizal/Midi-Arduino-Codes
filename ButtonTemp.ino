  boolean currentState = LOW;//stroage for current button state
  boolean lastState = LOW;//storage for last button state

void setup() 
{ 

  Serial.begin(9600); 
}

void loop() 
{ 
  //--------------Button normal
  BUTTONtemp(5,4);
  
 

}

//--------------------------------CLASSES

void MIDImessage(byte command, byte data1, byte data2) //pass values out through standard Midi Command
{
   Serial.write(command);
   Serial.write(data1);
   Serial.write(data2);
}

void BUTTONtemp ( int buttonPin, int channel) { //button is ON when push and OFF after (after delay= 15 ms)

  currentState = digitalRead(buttonPin); // Interrogation du bouton-poussoir
  
  // La valeur précédente du bouton-poussoir est-elle différente de la valeur actuelle ?
  // if it is, the buttonState is HIGH:
  if (currentState == LOW && lastState == HIGH) { 
      
     MIDImessage(176,channel,0); 
  
  }
  else if (currentState == HIGH && lastState == LOW) { 
           MIDImessage(176,channel,1); 
          
            delay(15);
           MIDImessage(176,channel,0); 
   }
  
  lastState = currentState;      
}


