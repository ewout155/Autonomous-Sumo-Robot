/* DXC volledige programma */
////////////////////////////////////////////////////////////////////////////////    LIBRARIES
#include "mbed.h"
#include "ultrasonic.h"
#include "pin_F303k8.h"
////////////////////////////////////////////////////////////////////////////////    PC
Serial pc(USBTX, USBRX);
////////////////////////////////////////////////////////////////////////////////    STATES DECLAREN
enum ROBOTstatus {
    WAIT, FORWARD, BACKWARD, T_LEFT, T_RIGHT, T_AROUND, ATTACK,ATTACK_CL, ATTACK_CR
};
ROBOTstatus state;
////////////////////////////////////////////////////////////////////////////////    PINOUTS
DigitalOut motorLA(Motor_Left_A);
DigitalOut motorLB(Motor_Left_B);
DigitalOut motorRA(Motor_Right_A);
DigitalOut motorRB(Motor_Right_B);
DigitalOut led(LED1);
PwmOut pwmL(Pwm_Left_Motor);
PwmOut pwmR(Pwm_Right_Motor);
AnalogIn IR_FL(IR_SENSOR_FL);
AnalogIn IR_FR(IR_SENSOR_FR);
AnalogIn IR_BL(IR_SENSOR_BL);
AnalogIn IR_BR(IR_SENSOR_BR);
InterruptIn ER(Enable_Robot, PullDown);
////////////////////////////////////////////////////////////////////////////////    VARIABELEN
bool RobotOn = 0, forloop = 1, w_action_f = 0, w_action_b = 0, d_action = 0,
     feedback = 1, feedback_state = 0, feedback_action = 1, feedback_IR = 1,
     feedback_US = 1;

int IR_value_FL = 30, IR_value_FR = 30, IR_value_BL = 30, IR_value_BR = 30,
    distance_FL = 1000, distance_FR = 1000, distance_B = 1000,
    white_value = 20, attack_d = 100;

float pwm_value = 0.80;
////////////////////////////////////////////////////////////////////////////////    TIMERS
Timer forloop_timer, action_timer, defend_timer, feedback_timer;
////////////////////////////////////////////////////////////////////////////////    SWITCHES
void checkER()
{
    wait(0.1f);
    if(RobotOn == 1) {
        forloop = 1;
        forloop_timer.stop();
        forloop_timer.reset();
        action_timer.stop();
        action_timer.reset();
        state = WAIT;
        RobotOn = 0;
    }

    if(RobotOn == 0) {
        RobotOn = 1;
    }
}
////////////////////////////////////////////////////////////////////////////////    IR SENSORS
void checkLine()
{
    IR_value_FL = IR_FL.read()*100;
    IR_value_FR = IR_FR.read()*100;
    IR_value_BL = IR_BL.read()*100;
    IR_value_BR = IR_BR.read()*100;

    if((IR_value_FL <= white_value || IR_value_FR <= white_value) && w_action_b == 0) {
        w_action_f = 1;
        forloop = 0;
    }
    if((IR_value_BL <= white_value || IR_value_BR <= white_value) && w_action_f == 0) {
        w_action_b = 1;
        forloop = 0;
    }
}
////////////////////////////////////////////////////////////////////////////////    US SENSORS
void dist(int distance)
{
    distance_FL = distance;
}
void dist2(int distance2)
{
    distance_FR = distance2;
}

void dist3(int distance3)
{
    distance_B = distance3;
}

ultrasonic mu(D10, D9, .1, 1, &dist);
ultrasonic2 mu2(D10, D2, .1, 1, &dist2);
ultrasonic3 mu3(D10, D3, .1, 1, &dist3);
////////////////////////////////////////////////////////////////////////////////    MAIN LOOP
int main(void)
{
    pc.baud(9600);
    mu.startUpdates();
    mu2.startUpdates2();
    mu3.startUpdates3();
    ER.rise(checkER);
    pwmL.period_us(1600);
    pwmR.period_us(1600);
////////////////////////////////////////////////////////////////////////////////    WHILE LOOP
    while(true) {
        checkLine();
        mu.checkDistance();
        mu2.checkDistance2();
        mu3.checkDistance3();
////////////////////////////////////////////////////////////////////////////////    FEEDBACK BEPALEN
        if(feedback == 1 && RobotOn == 1) {

            feedback_timer.start();

            if(feedback_timer > 1) {
                if(feedback_US == 1) {
                    pc.printf("US_FL:%dmm\n\rUS_FR:%dmm\n\rUS_B:%dmm\n\r",
                              distance_FL, distance_FR, distance_B);
                }

                if(feedback_IR == 1) {
                    pc.printf("IR_FL:%d%%\n\rIR_FR:%d%%\n\rIR_BL:%d%%\n\rIR_BR:%d%%\n\r",
                              IR_value_FL, IR_value_FR, IR_value_BL, IR_value_BR);
                }

                if(feedback_state == 1) {
                    pc.printf("robot state:%d\n\r", state);
                }

                if(feedback_action == 1) {

                    if(d_action == 1) {
                        pc.printf("defend action\n\r");
                    }

                    if(w_action_f == 1) {
                        pc.printf("white line action front\n\r");
                    }

                    if(w_action_b == 1) {
                        pc.printf("white line action back\n\r");
                    }

                    if(forloop == 1 && state != WAIT) {
                        pc.printf("for loop\n\r");
                    }

                    if(forloop == 0) {
                        pc.printf("normal loop\n\r");
                    }
                }
            }

            if(feedback_timer > 1 && RobotOn == 0) {
                pc.printf("Robot off\n\r");

            }

            if(feedback_timer > 1.005f) {
                feedback_timer.reset();
            }
        }
////////////////////////////////////////////////////////////////////////////////    WITTE LIJN ACTIES
        if(RobotOn == 1) {

            if(w_action_f == 1) {
                action_timer.start();

                if(action_timer < 1.5f) {
                    state = BACKWARD;
                }

                if(action_timer >= 1.5f && action_timer < 3.3f) {
                    state = T_AROUND;
                }

                if(action_timer >= 3.3f) {
                    action_timer.stop();
                    action_timer.reset();
                    w_action_f = 0;
                }
            }

            if(w_action_b == 1) {
                action_timer.start();

                if(action_timer < 1.5f) {
                    state = FORWARD;
                }

                if(action_timer >= 1.5f && action_timer < 3.3f) {
                    state = T_AROUND;
                }

                if(action_timer >= 3.3f) {
                    action_timer.stop();
                    action_timer.reset();
                    w_action_b = 0;
                }
            }
////////////////////////////////////////////////////////////////////////////////    ZWARTE LIJN ACTIES
            if(w_action_f == 0 && w_action_b == 0) {

                if(forloop ==  1) {
                    forloop_timer.start();
                    led = 1;
                    if(forloop_timer <= 5) {
                        state = FORWARD;
                    }

                    if(forloop_timer > 5) {
                        forloop_timer.stop();
                        forloop_timer.reset();
                        forloop = 0;
                    }
                }

                if(forloop == 0) {
                    led = 0;
                    if(d_action == 1) {
                        defend_timer.start();

                        if(defend_timer <= 3) {
                            state = FORWARD;
                        }
                        if(defend_timer > 3 && defend_timer <= 6) {
                            state = T_AROUND;
                        }

                        if(defend_timer > 6) {
                            defend_timer.stop();
                            defend_timer.reset();
                            d_action = 0;
                        }
                    }

                    if(d_action == 0) {
                        if(distance_FL < attack_d || distance_FR < attack_d) {

                            if(distance_FL < attack_d && distance_FR > attack_d) {
                                state = ATTACK_CR;
                            }

                            if(distance_FL > attack_d && distance_FR < attack_d) {
                                state = ATTACK_CL;
                            }

                            if(distance_FL < attack_d && distance_FR < attack_d) {
                                state = ATTACK;
                            }
                        }

                        if(distance_B < attack_d) {
                            d_action = 1;
                        }

                        if(distance_FL > attack_d && distance_FR > attack_d && distance_B > attack_d) {
                            state = FORWARD;
                        }
                    }
                }
            }
        }
////////////////////////////////////////////////////////////////////////////////    STATES
        switch(state) {

            case WAIT:
                motorLA = 0;
                motorLB = 0;
                motorRA = 0;
                motorRB = 0;
                pwmL.write(0);
                pwmR.write(0);
                break;

            case FORWARD:
                motorLA = 1;
                motorLB = 0;
                motorRA = 1;
                motorRB = 0;
                pwmL.write(pwm_value);
                pwmR.write(pwm_value);
                break;

            case BACKWARD:
                motorLA = 0;
                motorLB = 1;
                motorRA = 0;
                motorRB = 1;
                pwmL.write(pwm_value);
                pwmR.write(pwm_value);
                break;

            case T_LEFT:
                break;

            case T_RIGHT:
                break;

            case T_AROUND:
                motorLA = 1;
                motorLB = 0;
                motorRA = 0;
                motorRB = 1;
                pwmL.write(pwm_value);
                pwmR.write(pwm_value);
                break;

            case ATTACK:
                motorLA = 1;
                motorLB = 0;
                motorRA = 1;
                motorRB = 0;
                pwmL.write(pwm_value);
                pwmR.write(pwm_value);
                break;

            case ATTACK_CL:
                motorLA = 1;
                motorLB = 0;
                motorRA = 1;
                motorRB = 0;
                pwmL.write(0.9);
                pwmR.write(0.7);
                break;

            case ATTACK_CR:
                motorLA = 1;
                motorLB = 0;
                motorRA = 1;
                motorRB = 0;
                pwmL.write(0.7);
                pwmR.write(0.9);
                break;
        }
////////////////////////////////////////////////////////////////////////////////
    }
}