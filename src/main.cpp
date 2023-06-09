#include "main.h"
#include "pros/misc.h"
#include "pros/motors.hpp"
#include <string>
#include <vector>
#include <math.h>

#define maxfly 198
//testing code upload


bool rollerUp= false;
bool distancetrue = false; 
bool lookFoDisk = false;
int flywheelV = maxfly; //Max speed = 200 Medium = 120 Low = 60
int distance = 700;
int diskCheckVelocity = 20;
int v = 0;
int ymotion;
int xmotion;
int Vision;
int distread;
int intakeV = 200;
int reverseintakeV = -200;

void initialize(){

	pros::lcd::initialize();
	//pros::lcd::set_text(1, "Mohammed2");
	
	//pros::lcd::set_text(2, "Analog Sticks to Drive");
	//pros::lcd::set_text(3, "L1 - Slow down on turns");
	//pros::lcd::set_text(4, "R1 - Intake Motor");
	//pros::lcd::set_text(5, "R2 - Flywheel");
	//pros::lcd::set_text(6, "A - Shoot Disc");


}

pros::ADIDigitalOut piston ('A'); 
   // pros::Vision see(8);

    pros::Motor topbelt (2,true); //
    pros::Motor bottombelt(1,true); //
    pros::Motor flywheel (5, false); //flywheel
	pros::Motor flywheelbott (17, true);
	pros::Vision vision(16);
	pros::Distance dist(13);
	pros::Motor roller(15, false);
    //Wheel motor ports
    pros::Motor topleft(9, false);
	pros::Motor topright(11, true);	
	pros::Motor bottleft(8, true);
	pros::Motor bottright(12, false);

	    pros::Motor_Group left({12,11});
    pros::Motor_Group right({8,9});
	pros::Motor_Group belt({2,1});

	bool intake = false;


void Count() {

    int Disk_Count= 0; 

 
    while( Disk_Count < 3){
		//have the bot move to pick up discs
	//L.move_velocity(-300);
    //R.move_velocity(300);`
	belt.move_velocity(150);
    pros::vision_object_s_t color = vision.get_by_sig(0, 1);
	//vision_object_s_t rtn = vision.get_by_size(0);
    Vision = color.signature;
    pros::lcd::set_text(2, "Count: " + std::to_string(Disk_Count));
	dist.get();
	distread = dist.get();
  	pros::delay(1);
	

    if (distread < 130 && Vision == 1)
    {
     	Disk_Count ++;
        pros::lcd::set_text(2, "Count: " + std::to_string(Disk_Count));
        pros::delay(2000);


    }
    else
    {
	   
       pros::delay(1);

    }
    }

}



void autonomous()
{
	
//move roller while moving forward
roller.move_velocity(100);
topleft.move_velocity(-50);
topright.move_velocity(-50);
bottleft.move_velocity(50);
bottright.move_velocity(50);
pros::delay(1000);
topleft.move_velocity(0);
topright.move_velocity(0);
bottleft.move_velocity(0);
bottright.move_velocity(0);
roller.move_velocity(0);
pros::delay(500);



//clear position 
topleft.tare_position();
topright.tare_position();
bottleft.tare_position();
bottright.tare_position();

topleft.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
	pros::lcd::set_text(2, std::to_string(topleft.get_position()));
		pros::lcd::set_text(3,std::to_string(topright.get_position()));
		pros::lcd::set_text(4,std::to_string(bottleft.get_position()));
		pros::lcd::set_text(5,std::to_string(bottright.get_position()));

//3535 encoder clicks to CENTER
//Omni wheels are 4 inches in diameter: circumference is 12.566 inches, so 360 encoder clicks = 12.566 inches of movement (theoretically)

//move straight 
topleft.move_absolute(1827, 75);   
topright.move_absolute(1580, 75);
bottleft.move_absolute(-1816, 75);
bottright.move_absolute(-1546, 75);
pros::delay(2000);

//clear
topleft.tare_position();
topright.tare_position();
bottleft.tare_position();
bottright.tare_position();

//turn 
topleft.move_absolute(675, 75);   
topright.move_absolute(-488, 75);
bottleft.move_absolute(-682, 75);
bottright.move_absolute(557, 75);
pros::delay(2000);

//clear
topleft.tare_position();
topright.tare_position();
bottleft.tare_position();
bottright.tare_position();

//move backwards towards roller 
topleft.move_absolute(-1267, 75);   
topright.move_absolute(-1538, 75);
bottleft.move_absolute(1276, 75);
bottright.move_absolute(1521, 75);
pros::delay(2000);


//clear
topleft.tare_position();
topright.tare_position();
bottleft.tare_position();
bottright.tare_position();


//move roller while moving forward 
roller.move_velocity(100);
topleft.move_velocity(-50);
topright.move_velocity(-50);
bottleft.move_velocity(50);
bottright.move_velocity(50);
pros::delay(1000);
topleft.move_velocity(0);
topright.move_velocity(0);
bottleft.move_velocity(0);
bottright.move_velocity(0);
roller.move_velocity(0);
pros::delay(500);



	
	
	
	
	
	
	

//Get motors ready to shoot 
while(true)
{
	
belt.move_velocity(100);
pros::delay(500);
flywheel.move_velocity(flywheelV);
int velocity; 
velocity = flywheel.get_actual_velocity();
pros::delay(1000);
pros::lcd::set_text(6,"Velocity:" + std::to_string(velocity));
//pros::lcd::set_text(6,std::to_string(distread));
pros::delay(500);



if(velocity > 145 && velocity < 165 )   //range of speed for shooting 
{
{
	int diskCount = 0; 
	pros::lcd::set_text(3, "Count:" + std::to_string(diskCount));
 for (diskCount = 0; diskCount <= 3 ; diskCount ++)   //will count every time piston is released 
 {
piston.set_value(false);
pros::delay(500);
piston.set_value(true);
diskCount ++;
pros::lcd::set_text(3, "Count:" + std::to_string(diskCount));

 }
}
}
}

}



//Control


void R2_Flywheel()
{

        flywheel.move_velocity(flywheelV); //Changes flywheel velocity
        flywheelbott.move_velocity(flywheelV);
		pros::lcd::set_text(5, std::to_string(flywheel.get_actual_velocity()));
		pros::lcd::set_text(6, std::to_string(flywheelbott.get_actual_velocity()));
}


void A_Piston()
{
		piston.set_value(false);
		pros::delay(500);
		piston.set_value(true);
}

void L1_Slowdown()
{
	

			int right = (-xmotion + ymotion)/3; //-power + turn
			int left = (xmotion + ymotion)/3; //power + turn

			topleft.move(left);
			bottleft.move(left);
			bottright.move(right);
			topright.move(right);

			intakeV = 100;
			

}

void UP_Flywheel()
{
	 
		if (flywheelV == 150) {
      pros::delay(500);
			flywheelV = maxfly;
      
  
		}

		else if (flywheelV == 90) {
       pros::delay(500);
			flywheelV = 150;
     
      
		}
     pros::delay(10);

}



void DOWN_Flywheel()
{
	
		
		if (flywheelV == maxfly) {
			      flywheelV = 150;
      		pros::delay(1000);
			

		} 

		else if (flywheelV == 150) {
			
			pros::delay(500);
			flywheelV = 90;
   
		}

}










void opcontrol() {
    //DEFINITIONS
  	

   
	roller.tare_position();
    int ymotion;
	int xmotion;

    while(true){
		pros::lcd::set_text(2, std::to_string(topleft.get_position()));

 	pros::Controller master(pros::E_CONTROLLER_MASTER);
    //driving control code
    ymotion = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X); //ik this looks wrong, but it works
	xmotion = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);

	int right = -xmotion + ymotion; //-power + turn
	int left = xmotion + ymotion; //power + turn

	topleft.move(left); //Swap negatives if you want the bot to drive in the other direction
	bottleft.move(-left);
	bottright.move(right);
	topright.move(-right);
	pros::delay(1);
	////

	if(master.get_digital(DIGITAL_R1)){ //intake 
		topbelt.move_velocity(intakeV);
        bottombelt.move_velocity(intakeV);

    } else{
		topbelt.move_velocity(0);
        bottombelt.move_velocity(0);}



	if(master.get_digital(DIGITAL_R2)){ //runs flywheel while holding R2 down
      R2_Flywheel();
		} else {
			flywheel.move_velocity(0);
			flywheelbott.move_velocity(0);
	}


	if(master.get_digital(DIGITAL_A)) { //piston
		A_Piston();
	}


	// Slowdown feature (Cuts robots speed in half while holding down L1 on controller)
	if(master.get_digital(DIGITAL_L1)) { 
	L1_Slowdown();
		} else { intakeV = 200;}


 if(master.get_digital(DIGITAL_UP)) {
      pros::lcd::set_text(6, std::to_string(flywheelV));
		UP_Flywheel();
		}


if(master.get_digital(DIGITAL_DOWN)) {        //flywheel
    pros::lcd::set_text(6, std::to_string(flywheelV));
		DOWN_Flywheel();
	}


if(master.get_digital(DIGITAL_LEFT))  //reverse intake 
	{
		topbelt.move_velocity(reverseintakeV);
        bottombelt.move_velocity(reverseintakeV);
	}


if(master.get_digital(DIGITAL_B)) {   //forwards roller
		
		roller.move_velocity(400);

		} else {
			roller.move_velocity(0);
		}


}
}
