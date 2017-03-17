
# aBadApple
Arduboy port of the [Bad Apple!!](https://www.youtube.com/watch?v=G3C-VevI36s) music video <br/>
Requires the Arduboy2 library.

Bad Apple!! seems to be the Doom of software portable music videos, and I wanted to contribute another console to the mix.
Rendered at a glorious 16x8 at a mindblowing 8 frames per second. No audio either. 32KB of flash is rough. I guess if you want to hear the music you can sync it up with a computer playing it at the same time, I've been careful to keep the video in time with the original.
You could technically cut out a couple of KB by removing the USB stuff, but that means you have to jam the reset switch to update the console again, and I fear doing that frequently would shear the switch off.

A button pauses/unpauses the video
B button cycles debug modes 

Debug readouts are;
- Current frame
- Bytes for current frame
- Screen lines rendered
- Uncompressed lines rendered

The other debug mode shows the control bits used to decompress the video. It's kinda pretty, I guess.

Encoding scheme!<br/>
Uncompressed, every line of the display is composed of 2 bytes, one for the left side of the screen, one for the right. 2 bytes gives you 16 bits of video width, but since the video is 11 pixels wide, we have 5bits unused. 5 bytes gives you 32 unique options to play with.
```
XXXXXPPP PPPPPPPP
```
X is compression, P is pixels<br/>
If the right hand byte can be matched with any of the previous 31 bytes in the sequence, XXXXX counts backwards towards that, and the right hand byte isn't stored. 
Otherwise, if the right byte is unique to the previous 31, XXXXX is set to 00000 and the right byte is stored in full.
<br/> Since the video has plenty of repeated frames, blank frames and samey looking bits, the compression is quite high at 63.16%. For reference, a video full of only black pixels compresses at 51.67% As it only has to occasionally inject a new string of 00000000's in. <p/>
Blame any visual anomalies on the encoding, it needs work.<br/>I feel 10fps should be possible as long as the compression rate stays relatively steady, I just haven't tried it as my encoder tool keeps crashing. <p/>

Todo:
- Centre the screen. 
- Add seek controls
- Contact someone who can sort out the music
