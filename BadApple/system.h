#pragma once
#include "arduboy2.h"

class System : public Arduboy2
{
	public:
		void drawPlayfield(const uint8_t * PF)
		{		
			for(uint8_t offset=0; offset<128; ++offset)	
			{
				//Finds bit on playfield for current block on the screen.
				const uint8_t byte   = pgm_read_byte(PF+(offset/8));
				const uint8_t bit 	 = 7 - (offset % 8);
				const uint8_t buffer = bitRead(byte,bit)*0xFF;
				for(uint8_t y=0; y<8; ++y)	//repeats each line 8 times on y axis to draw a block
					this->sBuffer[(offset*8)+y] = buffer;	
			}
		}
};