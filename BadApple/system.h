#pragma once
#include "arduboy2.h"

class System : public Arduboy2
{
	private:
		uint8_t videoBuffer[16];
		uint8_t *video;
		uint16_t frameOffset;
		uint16_t frame;
		uint8_t extraBytes;

	public:
		bool playing=true;
		uint8_t debug=0;

		void initVideo(const uint8_t * PF)
		{
			video = PF;
			frame = 0;
			extraBytes = 0;
			frameOffset = 0;
			bool playing = true;
		};

		void stepVideo()
		{		
			if (!playing)
				return;
			extraBytes = 0;
			uint8_t firstbyte,secondbyte;
			for(uint8_t row=0; row<8; ++row)	
			{
				firstbyte = pgm_read_byte(video + frameOffset + extraBytes);
				uint16_t seek = firstbyte >> 3;	//get 5 seek bytes
				if(seek==0)	//If line is uncompressed (0 seek), read next byte
				{
					extraBytes++;
					secondbyte = pgm_read_byte(video + frameOffset + extraBytes);
				}
				else	//otherwise, jump back to get byte
				{
					uint16_t pos = (video + frameOffset + extraBytes) - (seek);
					secondbyte = pgm_read_byte(pos);
				}
				extraBytes++;	

				if((debug==0) or (debug==1))	//If no debug, mask off screen
					firstbyte = firstbyte&B00000111;

				videoBuffer[(row*2)] = firstbyte;
				videoBuffer[(row*2)+1] = secondbyte;
			}
			frameOffset += extraBytes;
			frame++;

			//Reset once reached end
			if(frame>1752)
				initVideo(video);
		};

		void drawVideo()
		{		
			for(uint8_t offset=0; offset<128; ++offset)	
			{
				//Finds bit on playfield for current block on the screen.
				const uint8_t byte   = videoBuffer[(offset/8)];
				const uint8_t bit 	 = 7 - (offset % 8);
				const uint8_t buffer = bitRead(byte,bit)*0xFF;
				for(uint8_t y=0; y<8; ++y)	//repeats each line 8 times on y axis to draw a block
					this->sBuffer[(offset*8)+y] = buffer;	
			}
			if(debug==1)
			{
				setCursor(0,0);
				print(frame);
				setCursor(0,8);
				print(extraBytes);
				setCursor(0,16);
				print(frameOffset);
				setCursor(0,24);
				print(frame*16);
			}
		};
};