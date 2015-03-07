/*
	Program : RoboCross Arduino Control
Author  : Sauhaarda Chowdhuri

Version : 4.0

History : (1) Now using AdaFruit V2 motor shield
(2) Removed servo functions
(3) Removed right boost variable
(4) Added flapper action
(5) Added shoulder action
*/
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"
#include <Servo.h>
#include <PS2X_lib.h>





#include "RoboCross_PS2_lib.h"
#include "RoboCross_motor_lib.h"
#include "RoboCross_servo_lib.h"

void getready(){
	bamFlapperUp();
	tm_fl_fast();
	delay(500);
	move_fwd_fast();
	delay(700);
	wheel_stop();
	bamFlapperDown();
}
void setup() {
	// Open serial port for debugging
	Serial.begin(57600);

	// Connect to the PS2 controller
	game_pad_init();

	// Initialize motor shield
	AFMS.begin();
	wheel_stop();

	// Set initial flapper position
	setFlapperPos(FLAPPER_MIN);
	initShoulder();
	initSide();
	//initTilt(90);
}


void loop() {
	//If error in connecting to game pad return
	if (error == 1)
	return;

	//Read game pad
	ps2x.read_gamepad(false, vibrate);

	// Take actions based on game pad key states
	if(ps2x.ButtonReleased(PSB_PAD_DOWN)){
		nextSideVal();
	}
	
	
	if(ps2x.ButtonReleased(PSB_PAD_UP)){
		getready();
	}else{
		// Wheel action
		//basic move fwd back
		if (ps2x.Analog(PSS_RY)<0+epsilon) {
			if (ps2x.Button(PSB_R1)){
				move_fwd_fast();
				Serial.println("FWDFAST");
			}
			else if(ps2x.Button(PSB_L1))
			move_fwd_slow();
			else
			move_fwd();
		} 
		else if (ps2x.Analog(PSS_RY)>255-epsilon) {
			if (ps2x.Button(PSB_R1))
			move_bck_fast();
			else if(ps2x.Button(PSB_L1))
			move_bck_slow();
			else
			move_bck();
		}
		//basic move lft rht
		else if (ps2x.Analog(PSS_RX)>255-epsilon) {
			if (ps2x.Button(PSB_R1))
			turn_rht_fast();
			else if(ps2x.Button(PSB_L1))
			turn_rht_slow();
			else
			turn_rht();
		} 
		else if (ps2x.Analog(PSS_RX)<0+epsilon) {
			if (ps2x.Button(PSB_R1))
			turn_lft_fast();
			else if(ps2x.Button(PSB_L1))
			turn_lft_slow();
			else
			turn_lft();
		}
		//turnmove
		else if (ps2x.Analog(PSS_LY)<0+15) {
			if (ps2x.Analog(PSS_LX)>255-20){
				if (ps2x.Button(PSB_R1))
				tm_fr_fast();
				else
				tm_fr();
			}
			else if (ps2x.Analog(PSS_LX)<tmepsilon){
				if (ps2x.Button(PSB_R1))
				tm_fl_fast();
				else
				tm_fl();
			}
			else{
				if (ps2x.Button(PSB_R1)){
					move_fwd_fast();
				}
				else if(ps2x.Button(PSB_L1))
				move_fwd_slow();
				else
				move_fwd();
			}
		} 
		else if (ps2x.Analog(PSS_LY)>255-15) {
			if (ps2x.Analog(PSS_LX)>255-20)
			if (ps2x.Button(PSB_R1))
			tm_br_fast();
			else
			tm_br();
			else if (ps2x.Analog(PSS_LX)<tmepsilon)
			if (ps2x.Button(PSB_R1))
			tm_bl_fast();
			else
			tm_bl();
			else{
				if (ps2x.Button(PSB_R1))
				move_bck_fast();
				else if(ps2x.Button(PSB_L1))
				move_bck_slow();
				else
				move_bck();
			}
		} 
		else
		wheel_stop();
		checkFlapperState();

		//Shoulder Action
		if(ps2x.Button(PSB_GREEN)){
			if(ps2x.Button(PSB_R1)){
				scoreSet();
			}
			else{
				upShoulder(1);
			}
		}
		else if(ps2x.Button(PSB_BLUE)){
			if(ps2x.Button(PSB_R1))
			goHome();
			else
			downShoulder(1);
		}
		if(ps2x.ButtonReleased(PSB_GREEN)||ps2x.ButtonReleased(PSB_BLUE)){
			Serial.print("Shoulder At ");
			Serial.println(getShoulder());
		}
		//Tilt Action
		if(ps2x.Button(PSB_R2)){ 
			upTilt(1);
			//Serial.println(tiltPos);
		}
		else if(ps2x.Button(PSB_L2)){
			downTilt(1);
			//Serial.println(tiltPos);  
		}
		if(ps2x.Button(PSB_RED)){
			if(ps2x.Button(PSB_R1))
			downFlapper(1);
			else
			bamFlapperDown();
			
		}else if(ps2x.Button(PSB_PINK)){
			if(ps2x.Button(PSB_R1))
			upFlapper(1);
			else
			bamFlapperUp();
		}
		
		delay(10);
	}
}
