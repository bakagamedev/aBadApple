/*

*/
#include <Arduboy2.h>
#include "system.h"
#include "frames.h"


int main(void)
{
	init();
	#ifdef USBCON
    	USBDevice.attach();
	#endif

	System ab = System();
	uint16_t frame = 0; 

	ab.boot();
	ab.setFrameRate(4);
	while(1)
	{  
		if (ab.nextFrame())
		{
			ab.drawPlayfield(imgFrames + (frame*16));
			ab.display();

			frame++;
			if(frame > 1296)
			{
				frame = 0;
			}
		}
	}
}