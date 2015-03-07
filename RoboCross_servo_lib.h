/*
	Program : RoboCross servo Control
	Author  : Sauhaarda Chowdhuri

	Version : 5.0
*/
Servo lFlapServo;
Servo rFlapServo;
int   flapPos                    = 0;
int   flapEnableLoopCount        = -1;
int   FLAP_ENABLE_MAX_LOOP_COUNT = 30;
int   L_FLAP_SERVO_PIN           = 11;
int   R_FLAP_SERVO_PIN           = 12;
int   FLAPPER_MIN                = 40;
int   FLAPPER_MAX                = 160;

Servo lShoulderServo;
Servo rShoulderServo;
int   L_SHHLDR_SERVO_PIN         = 2;
int   R_SHHLDR_SERVO_PIN         = 3;
int   shoulderPos                = -1;
int   SHOULDER_LOW_LIMIT         = 25;

Servo L_tiltServo;
Servo R_tiltServo;
int   L_TILT_SERVO_PIN           = 5;
int   R_TILT_SERVO_PIN           = 13;
int   tiltPos                    = -1;
int   TILT_DEFAULT               = 130;

Servo sideServo;
int SIDE_SERVO_PIN=10; // insert servo pin here
int sideServoArray[] = {170,80}; // insert servo positions here
int curSideIndex = 0;


int  SHOULDER_STEP               = 10;

int SHOULDER_LIMIT_LO[10] = {
	30,
	41,
	52,
	60,
	69,
	83,
	90,
	100,
	110,
	120
};

int  TILT_LO_LIMIT[10] = { 
	95,
	50,
	40,
	30,
	0,
	0,
	0,
	0,
	0
};

int  TILT_HOR_LIMIT[10] = { 
	130,
	130,
	130,
	130,
	130,
	120,
	110,
	100,
	90
};


int  TILT_HI_LIMIT[10] = {
	130,
	150,
	140,
	135,
	120,
	115,
	110,
	105,
	95,
	90
};

//getters

int getShoulder() {
	return shoulderPos;
}
int getTilt() {
	return tiltPos;
}

//side servo functions
void initSide(){
	sideServo.attach(SIDE_SERVO_PIN);
	sideServo.write(sideServoArray[0]);
}
int nextSideVal() {
	if (curSideIndex==((sizeof(sideServoArray)/sizeof(sideServoArray[0]))-1)) {
		curSideIndex = 0;
	} else {
		curSideIndex++;
	}
	sideServo.write(sideServoArray[curSideIndex]);
}

// Flapper functions
void setFlapperPos(int pos) {
	if (flapEnableLoopCount<0) {
		lFlapServo.attach(L_FLAP_SERVO_PIN);
		rFlapServo.attach(R_FLAP_SERVO_PIN);
	}
	if ((pos!=flapPos)||(flapEnableLoopCount<0)) {
		lFlapServo.write(pos);
		rFlapServo.write(180-pos);
		Serial.print("Setting flapper pos to ");
		Serial.println(pos);
	}

	flapEnableLoopCount=FLAP_ENABLE_MAX_LOOP_COUNT*(1+abs(pos-flapPos)/45);
	flapPos = pos;
}
void checkFlapperState(void) {
	if (flapEnableLoopCount>0) {
		flapEnableLoopCount--;
		return;
	}
	if (flapEnableLoopCount<0) {
		return;
	}
	flapEnableLoopCount--;
	lFlapServo.detach();
	rFlapServo.detach();
}
void upFlapper(int degree) {
	if (flapPos+degree<FLAPPER_MAX)
	setFlapperPos((flapPos+degree));
	else
	setFlapperPos(FLAPPER_MAX);
}
void downFlapper(int degree) {
	if ((flapPos-degree)>FLAPPER_MIN)
	setFlapperPos((flapPos-degree));
	else
	setFlapperPos(FLAPPER_MIN);
}
void bamFlapperDown(void) {
  if(curSideIndex==0){
	setFlapperPos(FLAPPER_MIN);
  }else{
      downFlapper(1);
  }
}
void bamFlapperUp(void) {
  if(curSideIndex==0){
	setFlapperPos(FLAPPER_MAX);
  }else{
      upFlapper(1);
  }
}

//Tilt servo functions
void setTiltPos(int pos) {
	Serial.println("Going to set tilt -> ");
	if (pos !=tiltPos) {
		L_tiltServo.write(180-pos);
		R_tiltServo.write(pos);
		tiltPos=pos;
		Serial.print("Setting tilt pos to ");
		Serial.println(pos);
	}
}
void engageTilt(void) {
	L_tiltServo.attach(L_TILT_SERVO_PIN);
	R_tiltServo.attach(R_TILT_SERVO_PIN);
	L_tiltServo.write(180-TILT_DEFAULT);
	R_tiltServo.write(TILT_DEFAULT);
	tiltPos = TILT_DEFAULT;
}

void disengageTilt(void) {
	L_tiltServo.write(180-TILT_DEFAULT);
	R_tiltServo.write(TILT_DEFAULT);
	tiltPos = TILT_DEFAULT;
	delay(250);
	L_tiltServo.detach();
	R_tiltServo.detach();
}
int checkAllowedTilt(int tilt) {
	int i;
	for (i=0;i<SHOULDER_STEP;i++) {
		if (shoulderPos < SHOULDER_LIMIT_LO[i])
		break;
	}
	if(i>0)
	i--;
	if (tilt < TILT_LO_LIMIT[i])
	tilt = TILT_LO_LIMIT[i];
	if (tilt > TILT_HI_LIMIT[i])
	tilt = TILT_HI_LIMIT[i];
	
	return tilt;
}
int checkAllowedHorTilt(int tilt) {
	int i;
	for (i=0;i<SHOULDER_STEP;i++) {
		if (shoulderPos < SHOULDER_LIMIT_LO[i])
		break;
	}
	if(i>0)
	i--;
	return TILT_HOR_LIMIT[i];
}
void upTilt(int degree) {
	setTiltPos(checkAllowedTilt(tiltPos-degree));
}
void downTilt(int degree) {
	setTiltPos(checkAllowedTilt(tiltPos+degree));
}
// Shoulder servo functions
void initShoulder(void) {
	lShoulderServo.attach(L_SHHLDR_SERVO_PIN);
	rShoulderServo.attach(R_SHHLDR_SERVO_PIN);

	L_tiltServo.attach(L_TILT_SERVO_PIN);
	R_tiltServo.attach(R_TILT_SERVO_PIN);
	
	rShoulderServo.write(SHOULDER_LOW_LIMIT);
	lShoulderServo.write(180-SHOULDER_LOW_LIMIT);

	delay(150);
	L_tiltServo.write(180-TILT_DEFAULT);
	R_tiltServo.write(TILT_DEFAULT);
	delay(1000);

	lShoulderServo.detach();
	rShoulderServo.detach();

	L_tiltServo.detach();
	R_tiltServo.detach();
	
	shoulderPos = SHOULDER_LOW_LIMIT;
}
void setShoulderPos(int pos) {
	if(pos>120)
	pos=120;
	if(pos<SHOULDER_LOW_LIMIT)
	pos = SHOULDER_LOW_LIMIT;
	if ((shoulderPos==SHOULDER_LOW_LIMIT) && (pos>SHOULDER_LOW_LIMIT)) {
		lShoulderServo.attach(L_SHHLDR_SERVO_PIN);
		rShoulderServo.attach(R_SHHLDR_SERVO_PIN);

		engageTilt();
	} else if ((shoulderPos!=SHOULDER_LOW_LIMIT) && (pos==SHOULDER_LOW_LIMIT)) {
		rShoulderServo.write(pos);
		lShoulderServo.write(180-pos);
		delay(250);
		lShoulderServo.detach();
		rShoulderServo.detach();
		disengageTilt();
		shoulderPos=pos;
		return;
	}

	if (pos!=shoulderPos) {
		shoulderPos = pos;
		setTiltPos(checkAllowedTilt(tiltPos));

		rShoulderServo.write(pos);
		lShoulderServo.write(180-pos);
		Serial.print("Setting Shoulder pos to ");
		Serial.println(pos);
	}
}
void setShoulderPosHor(int pos) {
	if(pos>120)
	pos=120;
	if ((shoulderPos==SHOULDER_LOW_LIMIT) && (pos>SHOULDER_LOW_LIMIT)) {
		lShoulderServo.attach(L_SHHLDR_SERVO_PIN);
		rShoulderServo.attach(R_SHHLDR_SERVO_PIN);

		engageTilt();
	} else if ((shoulderPos!=SHOULDER_LOW_LIMIT) && (pos==SHOULDER_LOW_LIMIT)) {
		rShoulderServo.write(pos);
		lShoulderServo.write(180-pos);
		delay(250);
		lShoulderServo.detach();
		rShoulderServo.detach();
		disengageTilt();
		shoulderPos=pos;
		return;
	}

	if (pos!=shoulderPos) {
		shoulderPos = pos;
		setTiltPos(checkAllowedHorTilt(tiltPos));

		rShoulderServo.write(pos);
		lShoulderServo.write(180-pos);
		Serial.print("Setting Shoulder pos to ");
		Serial.println(pos);
	}
}
void upShoulder(int degree) {
	if (shoulderPos+degree<(180 - SHOULDER_LOW_LIMIT)) {
		setShoulderPos((shoulderPos+degree));
	} else {
		setShoulderPos(180-SHOULDER_LOW_LIMIT);
	}
}
void downShoulder(int degree) {
	if ((shoulderPos-degree)>SHOULDER_LOW_LIMIT) {
		setShoulderPos((shoulderPos-degree));
	} else {
		setShoulderPos(SHOULDER_LOW_LIMIT);
	}
}
void scoreSet(){
	bamFlapperDown();
	for(int i=shoulderPos;i<=105;i+=5){
		setShoulderPosHor(i);
		delay(50);
	}
	setShoulderPosHor(105);
        delay(75);
        R_tiltServo.detach();
}
void goHome(){
	for(int i=shoulderPos;i>=SHOULDER_LOW_LIMIT;i-=5){
		setShoulderPosHor(i);
		delay(50);
	}
	setShoulderPosHor(SHOULDER_LOW_LIMIT);
	bamFlapperDown();
        R_tiltServo.attach();
}
