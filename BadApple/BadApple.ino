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
	ab.setFrameRate(8);

	ab.initVideo(imgFrames);
	while(1)
	{  
		if (ab.nextFrame())
		{
			ab.pollButtons();
			if(ab.justPressed(A_BUTTON))
				ab.playing = !ab.playing;
			if(ab.justPressed(B_BUTTON))
				ab.masking = !ab.masking;

			ab.stepVideo();
			ab.drawVideo();
			ab.display();
		}
	}
}