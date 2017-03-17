# aBadApple
Arduboy port of Bad Apple!! <br/>
Requires the Arduboy2 library.

Bad Apple!! seems to be the Doom of software portable music videos, and I wanted to contribute another console to the mix.
Rendered at a glorious 16x8 at a mindblowing 8 frames per second. No audio either. 32KB of flash is rough.
You could technically cut out a couple of KB by removing the USB stuff, but that means you have to jam the reset switch to update the console again, and I fear doing that frequently would shear the switch off.

Encoding scheme!<br/>
Uncompressed, every line of the display is composed of 2 bytes, one for the left side of the screen, one for the right. 2 bytes gives you 16 bits of video width, but since the video is 11 pixels wide, we have 5bits unused. 5 bytes gives you 32 unique options to play with.
```
XXXXXPPP PPPPPPPP
```
X is compression, P is pixels<br/>
If the right hand byte can be matched with any of the previous 31 bytes in the sequence, XXXXX counts backwards towards that, and the right hand byte isn't stored. <br/>
Blame any visual anomalies on the encoder too, it needs work.<p/>

Otherwise, if the right byte is unique to the previous 31, XXXXX is set to 00000 and the right byte is stored in full.
<p/>
