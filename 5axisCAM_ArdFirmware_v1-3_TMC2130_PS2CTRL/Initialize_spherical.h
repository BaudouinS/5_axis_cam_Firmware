/*
  Initialize_spherical - 
  Created by B Saintyves, April 4, 2020.
*/

#ifndef Initialize_spherical_h
#define Initialize_spherical_h


///////execute init mode= go to X=0;Y=R;Z=0;
 while (Init==1){
          // lcd.setCursor(0,3);
         //  lcd.print("Init in progress");
           
           Y_stepper.enableOutputs();  
           Y_stepper.setSpeed(-1000);
           Y_stepper.runSpeed();
           if (Y_stepper.currentPosition()==-1*R){
             Init=0;
             Y_stepper.setSpeed(0);
             Y_stepper.runSpeed();
             Y_stepper.disableOutputs();  
             Serial1.println("C03-Ready;");
             Serial.print("Spherical intitialization completed: ");Serial.print("Init= "); Serial.println(Init);
             //lcd.setCursor(0,3); lcd.print("Init done       ");
             } 
           }

#endif
