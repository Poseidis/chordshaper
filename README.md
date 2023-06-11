## ChordShaper
#### by Vincent Wei

The ChordShaper is a simple instrument designed as a songwriting/improvisation tool that maps parameterized input to chords built using an Arduino Uno and Max 8. The user controls a standard MIDI input that determines the tonic of the chord and 2 knobs: one selecting the type of chord, and one determining the voicing. Originally intended to be controlled by hand motion, last-minute technical difficulties resulted in a proof-of-concept model that uses 2 potentiometers.

![board_img](https://raw.githubusercontent.com/Poseidis/chordshaper/main/images/20230611_014229.jpg)

![keyboard](https://raw.githubusercontent.com/Poseidis/chordshaper/main/images/20230611_021712.jpg)
### Motivation
In 12-tone equal temperament music theory, finding a way to parameterize chord-making seemed like an interesting challenge, considering music and harmony is quite subjective. My first attempt at this was the ChordShaper, which egregiously encapsulates the possibility space of harmony down to 2 degrees of freedom: voicing and base chord, each of which alone can vary in countless ways.

### Control
To play, you use a MIDI input/piano keyboard input to select base note and press a button to toggle chord playback. Additionally, there are 2 analog (discrete) inputs:

- Chord type: a choice from a preset of customizable chords, with the arbitrary decision to organize roughly by the size of the interval between the notes.
	- For example, in the demo, I used a range from 1 to 5, with the chords designated as such:

|||
|-|-|
|1|dim7|
|2|min7|
|3|majb7|
|4|maj7|
|5|sus4|


- Chord inversion
	- from -3 to +3, indicating how many notes were to be incremented or decremented by an octave.

Notably, *changing parameters while a chord is playing does not change the current chord*. This was designed this way due to the sporadic nature of the input mechanisms, as well as providing time for the user to perform the transition.


The ChordShaper is not an intuitive instrument for traditional musicians to learn. It is not natural to intuit one's control over notes (or sound for that matter) using these controls. As stated previously, reducing both voicing and chord formation to one-dimensional spaces limits the user's choices significantly. Yet I think there exists a form of mastery of this instrument where the formation of chords is fluid and natural and where new intuitions about harmony arise. I found value in improvising with this instrument and experimenting with the arbitrary chord order I picked out, as it seemed to provide a new perspective on how chords interact with each other. 

### Code
Below is the Arduino code used to send serial data from the Arduino to Max for processing into audio output. All code is available on the [main github repo](https://github.com/Poseidis/chordshaper). 
```c++
const int sensorPins[] = {A0, A1};
int values[] = {0, 0};

void setup() {
	Serial.begin(38400);
}
void loop() {
	for (int i = 0; i < 2; i++) {
		values[i] = analogRead(sensorPins[i]);
		Serial.write(values[i] >> 3);
		Serial.write(values[i] & 7);
		Serial.write(255);
	}
	Serial.write(254);
}
```
Max Patch
![max_patch](https://raw.githubusercontent.com/Poseidis/chordshaper/main/images/maxcode.PNG)

### Example "Sheet Music":
Chord Progression 1
|Base Chord|Inversion|Chord No.|Duration (beats)|
|-|-|-|-|
|F4 maj7|0|3|1|
|E4 majb7|0|2|1|
|A4 min7|0|1|1|
|G4 min7|0|1|0.5|
|A4 majb7|0|2|0.5|

Chord Progression 2
|Base Chord|Inversion|Chord No.|Duration (beats)|
|-|-|-|-|
|C#5 min7|-2|1|1|
|G#4 min7|-1|1|1|
|F#4 min7|0|1|1.5|
|G#4 majb7|-1|2|0.5|
