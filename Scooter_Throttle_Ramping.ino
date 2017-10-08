
/*
  ME2 DMF Scooter Project
  Throttle ramping
  Attempt 2.1
  04Dec13
 */

#include <Servo.h>

#define THR_MIN 178
#define THR_MAX 870
#define PWM_MIN 1000
#define PWM_MAX 2000

#define SPEED_LIMIT 0.5 // fraction of full speed - value can be changed
#define RAMP_LIMIT 0.13 // fraction of full speed per second - value can be changed

Servo myservo;

float pwm_f = (float) PWM_MIN;

void setup()
{
pinMode(9, OUTPUT);
myservo.attach(9);
myservo.writeMicroseconds(PWM_MIN); // set servo fully counter-clockwise, i.e. ESC to zero
//myservo.writeMicroseconds(PWM_MAX);
delay(5000); // 5 second delay to allow motor to go through set-up 
Serial.begin(9600);
}

void loop()
{
signed int thr = THR_MIN;
float thr_f = (float) thr; // approximate continuous values 
float pwm_target = (float) PWM_MIN;   
unsigned int pwm_i = PWM_MIN;;

thr = analogRead(0); // read signal from throttle 

thr_f = (float)(thr - THR_MIN) / (float)(THR_MAX - THR_MIN); // throttle position as pecentge of useful range
pwm_target = thr_f * SPEED_LIMIT * (float)(PWM_MAX - PWM_MIN) + (float) PWM_MIN; // servo (ESC) position 

if(pwm_target > pwm_f)
{
pwm_f += RAMP_LIMIT * (float)(PWM_MAX - PWM_MIN) * 0.05; // soft ramp if demand from throttle greater than signal
}
else
{
pwm_f = pwm_target; 
}

pwm_i = (unsigned int) pwm_f;
myservo.writeMicroseconds(pwm_i); // write to servo (ESC) 

Serial.println(pwm_f);

delay(50);
}
