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

	ab.boot();
	ab.setFrameRate(4);

	ab.initVideo(imgFrames);
	while(1)
	{  
		if (ab.nextFrame())
		{
			ab.stepVideo();
			ab.drawVideo();
			ab.display();
		}
	}
}