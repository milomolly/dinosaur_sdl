#ifndef WARRIOR_H
#define WARRIOR_H

#include "Character.h"
#include <string>
#include "Vector2D.h"

#define JUMP_TIME 25.0f
// time for 1 jump
#define JUMP_FORCE 12.0f
// force of 1 jump
#define FLOATING_TIME 7.0f

#define SHOOT_DELAY 10.0f

class Warrior : public Character
{
	public:
		Warrior(Properties* prop);
		// just create not init. init in Warrior.cpp
		virtual void Draw();
		virtual void Update(float dt);
		virtual void Clean();
		void ChangeStage(int id);
		void SetSize(int w, int h);
		int stage;
		int last_stage;
	private:
		bool Jumping; // to know player is jumping and set animation jumping for player
		bool Grounded; // make sure player can jump (2 and 1 is can jump)
										//reset when go back to base

		float JumpTime, JumpForce, FloatingTime, ShootDelay;

//		string id_map = "6"; // currently here

};

#endif // WARRIOR_H
