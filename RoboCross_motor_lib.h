/*
    Program : RoboCross movement functions

    Author  : Sauhaarda Chowdhuri
    
    Version : 5.0
*/

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Select which 'port' M1, M2, M3 or M4 are connected which wheel motor
Adafruit_DCMotor *motorLF = AFMS.getMotor(1);
Adafruit_DCMotor *motorLB = AFMS.getMotor(2);
Adafruit_DCMotor *motorRB = AFMS.getMotor(3);
Adafruit_DCMotor *motorRF = AFMS.getMotor(4);

short epsilon    = 10;
short tmepsilon  = 100;
float steering   = 2;
int   pos        = 127;

short state = 0;
int tmIndex = 0;

const short stopped = 0;
const short forward = 1;
const short backward = 2;
const short lturn = 3;
const short rturn = 4;
const int tweenMove[]={50,50,50,60,70,90,110,140};
const int tweenStop[]={130,120,110,100,90,80,60,40,20};
const short tweenDelay = 25;

void wheel_stop() {
    /*if(state==forward){
      motorLF->setSpeed(tweenStop[tmIndex]);
      motorLB->setSpeed(tweenStop[tmIndex]);
      motorRF->setSpeed(tweenStop[tmIndex]);
      motorRB->setSpeed(tweenStop[tmIndex]);
      motorLF->run(FORWARD);
      motorRF->run(FORWARD);
      motorLB->run(FORWARD);
      motorRB->run(FORWARD);
      delay((tweenDelay/3)*2);
      if (tmIndex==((sizeof(tweenStop)/sizeof(tweenStop[0]))-1)) {
		tmIndex=-1;
                state=stopped;
      }
      tmIndex++;
    }else{*/
    motorLF->setSpeed(0);
    motorLB->setSpeed(0);
    motorRF->setSpeed(0);
    motorRB->setSpeed(0);
    motorLF->run(RELEASE);
    motorLB->run(RELEASE);
    motorRF->run(RELEASE);
    motorRB->run(RELEASE); 
    state = stopped;
    //}
}
void move_fwd() {
    short movespeed=150;
    motorLF->setSpeed(movespeed);
    motorLB->setSpeed(movespeed);
    motorRF->setSpeed(movespeed);
    motorRB->setSpeed(movespeed);
    
    motorLF->run(FORWARD);
    motorRF->run(FORWARD);
    motorLB->run(FORWARD);
    motorRB->run(FORWARD);
    state = forward;
}
void move_bck() {
    short movespeed=150;
   /* if(state==stopped||state==forward){
      motorLF->setSpeed(tweenMove[tmIndex]);
      motorLB->setSpeed(tweenMove[tmIndex]);
      motorRF->setSpeed(tweenMove[tmIndex]);
      motorRB->setSpeed(tweenMove[tmIndex]);
      motorLF->run(BACKWARD);
      motorRF->run(BACKWARD);
      motorLB->run(BACKWARD);
      motorRB->run(BACKWARD);
      delay(tweenDelay);
      if (tmIndex==((sizeof(tweenMove)/sizeof(tweenMove[0]))-1)) {
		tmIndex=-1;
                state=backward;
      }
      tmIndex++;
    }else{*/
    motorLF->setSpeed(movespeed);
    motorLB->setSpeed(movespeed);
    motorRF->setSpeed(movespeed);
    motorRB->setSpeed(movespeed);
    
    motorLF->run(BACKWARD);
    motorRF->run(BACKWARD);
    motorLB->run(BACKWARD);
    motorRB->run(BACKWARD);
    state = backward;
    //}
}
void move_fwd_slow() {
    short movespeed=50;
    motorLF->setSpeed(movespeed);
    motorLB->setSpeed(movespeed);
    motorRF->setSpeed(movespeed);
    motorRB->setSpeed(movespeed);
    
    motorLF->run(FORWARD);
    motorRF->run(FORWARD);
    motorLB->run(FORWARD);
    motorRB->run(FORWARD);
    state = forward;
}
void move_bck_slow() {
    short movespeed=50;
    motorLF->setSpeed(movespeed);
    motorLB->setSpeed(movespeed);
    motorRF->setSpeed(movespeed);
    motorRB->setSpeed(movespeed);
    
    motorLF->run(BACKWARD);
    motorRF->run(BACKWARD);
    motorLB->run(BACKWARD);
    motorRB->run(BACKWARD);
    state = backward;
}
void move_fwd_fast() {
    short movespeed=255;
    motorLF->setSpeed(movespeed);
    motorLB->setSpeed(movespeed);
    motorRF->setSpeed(movespeed);
    motorRB->setSpeed(movespeed);
    
    motorLF->run(FORWARD);
    motorRF->run(FORWARD);
    motorLB->run(FORWARD);
    motorRB->run(FORWARD);
    state = forward;
}
void move_bck_fast() {
    short movespeed=255;
    motorLF->setSpeed(movespeed);
    motorLB->setSpeed(movespeed);
    motorRF->setSpeed(movespeed);
    motorRB->setSpeed(movespeed);
    
    motorLF->run(BACKWARD);
    motorRF->run(BACKWARD);
    motorLB->run(BACKWARD);
    motorRB->run(BACKWARD);
    state = backward;
}

void turn_rht_slow() {
    short movespeed=50;
    motorLF->setSpeed(movespeed);
    motorLB->setSpeed(movespeed);
    motorRF->setSpeed(movespeed);
    motorRB->setSpeed(movespeed);
    
    motorLF->run(FORWARD);
    motorRF->run(BACKWARD);
    motorLB->run(FORWARD);
    motorRB->run(BACKWARD);
}
void turn_lft_slow() {
    short movespeed=50;
    motorLF->setSpeed(movespeed);
    motorLB->setSpeed(movespeed);
    motorRF->setSpeed(movespeed);
    motorRB->setSpeed(movespeed);
    
    motorLF->run(BACKWARD);
    motorRF->run(FORWARD);
    motorLB->run(BACKWARD);
    motorRB->run(FORWARD);
}

void turn_rht() {
    short movespeed=100;
    motorLF->setSpeed(movespeed);
    motorLB->setSpeed(movespeed);
    motorRF->setSpeed(movespeed);
    motorRB->setSpeed(movespeed);
    
    motorLF->run(FORWARD);
    motorRF->run(BACKWARD);
    motorLB->run(FORWARD);
    motorRB->run(BACKWARD);
}
void turn_lft() {
    short movespeed=100;
    motorLF->setSpeed(movespeed);
    motorLB->setSpeed(movespeed);
    motorRF->setSpeed(movespeed);
    motorRB->setSpeed(movespeed);
    
    motorLF->run(BACKWARD);
    motorRF->run(FORWARD);
    motorLB->run(BACKWARD);
    motorRB->run(FORWARD);
}

void turn_rht_fast() {
    short movespeed=170;
    motorLF->setSpeed(movespeed);
    motorLB->setSpeed(movespeed);
    motorRF->setSpeed(movespeed);
    motorRB->setSpeed(movespeed);
    
    motorLF->run(FORWARD);
    motorRF->run(BACKWARD);
    motorLB->run(FORWARD);
    motorRB->run(BACKWARD);
}
void turn_lft_fast() {
    short movespeed=170;
    motorLF->setSpeed(movespeed);
    motorLB->setSpeed(movespeed);
    motorRF->setSpeed(movespeed);
    motorRB->setSpeed(movespeed);
    
    motorLF->run(BACKWARD);
    motorRF->run(FORWARD);
    motorLB->run(BACKWARD);
    motorRB->run(FORWARD);
}
void tm_bl() {
    short movespeed=150;
    motorLF->setSpeed(movespeed/steering);
    motorLB->setSpeed(movespeed/steering);
    motorRF->setSpeed(movespeed);
    motorRB->setSpeed(movespeed);
    
    motorLF->run(BACKWARD);
    motorRF->run(BACKWARD);
    motorLB->run(BACKWARD);
    motorRB->run(BACKWARD);
}
void tm_br() {
    short movespeed=150;
    motorLF->setSpeed(movespeed);
    motorLB->setSpeed(movespeed);
    motorRF->setSpeed(movespeed/steering);
    motorRB->setSpeed(movespeed/steering);
    
    motorLF->run(BACKWARD);
    motorRF->run(BACKWARD);
    motorLB->run(BACKWARD);
    motorRB->run(BACKWARD);
}
void tm_fl() {
    short movespeed=150;
    motorLF->setSpeed(movespeed/steering);
    motorLB->setSpeed(movespeed/steering);
    motorRF->setSpeed(movespeed);
    motorRB->setSpeed(movespeed);
    
    motorLF->run(FORWARD);
    motorRF->run(FORWARD);
    motorLB->run(FORWARD);
    motorRB->run(FORWARD);
}
void tm_fr() {
    short movespeed=150;
    motorLF->setSpeed(movespeed);
    motorLB->setSpeed(movespeed);
    motorRF->setSpeed(movespeed/steering);
    motorRB->setSpeed(movespeed/steering);
    
    motorLF->run(FORWARD);
    motorRF->run(FORWARD);
    motorLB->run(FORWARD);
    motorRB->run(FORWARD);
}
//fast turn move
void tm_bl_fast() {
    short movespeed=255;
    motorLF->setSpeed(movespeed/steering);
    motorLB->setSpeed(movespeed/steering);
    motorRF->setSpeed(movespeed);
    motorRB->setSpeed(movespeed);
    
    motorLF->run(BACKWARD);
    motorRF->run(BACKWARD);
    motorLB->run(BACKWARD);
    motorRB->run(BACKWARD);
}
void tm_br_fast() {
    short movespeed=255;
    motorLF->setSpeed(movespeed);
    motorLB->setSpeed(movespeed);
    motorRF->setSpeed(movespeed/steering);
    motorRB->setSpeed(movespeed/steering);
    
    motorLF->run(BACKWARD);
    motorRF->run(BACKWARD);
    motorLB->run(BACKWARD);
    motorRB->run(BACKWARD);
}
void tm_fl_fast() {
    short movespeed=255;
    motorLF->setSpeed(movespeed/steering);
    motorLB->setSpeed(movespeed/steering);
    motorRF->setSpeed(movespeed);
    motorRB->setSpeed(movespeed);
    
    motorLF->run(FORWARD);
    motorRF->run(FORWARD);
    motorLB->run(FORWARD);
    motorRB->run(FORWARD);
}
void tm_fr_fast() {
    short movespeed=255;
    motorLF->setSpeed(movespeed);
    motorLB->setSpeed(movespeed);
    motorRF->setSpeed(movespeed/steering);
    motorRB->setSpeed(movespeed/steering);
    
    motorLF->run(FORWARD);
    motorRF->run(FORWARD);
    motorLB->run(FORWARD);
    motorRB->run(FORWARD);
}
void tm_bl_slow() {
    short movespeed=80;
    motorLF->setSpeed(movespeed/steering);
    motorLB->setSpeed(movespeed/steering);
    motorRF->setSpeed(movespeed);
    motorRB->setSpeed(movespeed);
    
    motorLF->run(BACKWARD);
    motorRF->run(BACKWARD);
    motorLB->run(BACKWARD);
    motorRB->run(BACKWARD);
}
void tm_br_slow() {
    short movespeed=80;
    motorLF->setSpeed(movespeed);
    motorLB->setSpeed(movespeed);
    motorRF->setSpeed(movespeed/steering);
    motorRB->setSpeed(movespeed/steering);
    
    motorLF->run(BACKWARD);
    motorRF->run(BACKWARD);
    motorLB->run(BACKWARD);
    motorRB->run(BACKWARD);
}
void tm_fl_slow() {
    short movespeed=80;
    motorLF->setSpeed(movespeed/steering);
    motorLB->setSpeed(movespeed/steering);
    motorRF->setSpeed(movespeed);
    motorRB->setSpeed(movespeed);
    
    motorLF->run(FORWARD);
    motorRF->run(FORWARD);
    motorLB->run(FORWARD);
    motorRB->run(FORWARD);
}
void tm_fr_slow() {
    short movespeed=80;
    motorLF->setSpeed(movespeed);
    motorLB->setSpeed(movespeed);
    motorRF->setSpeed(movespeed/steering);
    motorRB->setSpeed(movespeed/steering);
    
    motorLF->run(FORWARD);
    motorRF->run(FORWARD);
    motorLB->run(FORWARD);
    motorRB->run(FORWARD);
}
