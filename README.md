---


---

<h2 id="chordshaper">ChordShaper</h2>
<h4 id="by-vincent-wei">by Vincent Wei</h4>
<p>The ChordShaper is a simple instrument designed as a songwriting/improvisation tool that maps parameterized input to chords built using an Arduino Uno and Max 8. The user controls a standard MIDI input that determines the tonic of the chord and 2 knobs: one selecting the type of chord, and one determining the voicing. Originally intended to be controlled by hand motion, last-minute technical difficulties resulted in a proof-of-concept model that uses 2 potentiometers.</p>
<p><img src="https://raw.githubusercontent.com/Poseidis/chordshaper/main/images/20230611_014229.jpg" alt="board_img"></p>
<p><img src="https://raw.githubusercontent.com/Poseidis/chordshaper/main/images/20230611_021712.jpg" alt="keyboard"></p>
<h3 id="motivation">Motivation</h3>
<p>In 12-tone equal temperament music theory, finding a way to parameterize chord-making seemed like an interesting challenge, considering music and harmony is quite subjective. My first attempt at this was the ChordShaper, which egregiously encapsulates the possibility space of harmony down to 2 degrees of freedom: voicing and base chord, each of which alone can vary in countless ways.</p>
<h3 id="control">Control</h3>
<p>To play, you use a MIDI input/piano keyboard input to select base note and press a button to toggle chord playback. Additionally, there are 2 analog (discrete) inputs:</p>
<ul>
<li>Chord type: a choice from a preset of customizable chords, with the arbitrary decision to organize roughly by the size of the interval between the notes.
<ul>
<li>For example, in the demo, I used a range from 1 to 5, with the chords designated as such:</li>
</ul>
</li>
</ul>

<table>
<thead>
<tr>
<th></th>
<th></th>
</tr>
</thead>
<tbody>
<tr>
<td>1</td>
<td>dim7</td>
</tr>
<tr>
<td>2</td>
<td>min7</td>
</tr>
<tr>
<td>3</td>
<td>majb7</td>
</tr>
<tr>
<td>4</td>
<td>maj7</td>
</tr>
<tr>
<td>5</td>
<td>sus4</td>
</tr>
</tbody>
</table><ul>
<li>Chord inversion
<ul>
<li>from -3 to +3, indicating how many notes were to be incremented or decremented by an octave.</li>
</ul>
</li>
</ul>
<p>Notably, <em>changing parameters while a chord is playing does not change the current chord</em>. This was designed this way due to the sporadic nature of the input mechanisms, as well as providing time for the user to perform the transition.</p>
<p>The ChordShaper is not an intuitive instrument for traditional musicians to learn. It is not natural to intuit one’s control over notes (or sound for that matter) using these controls. As stated previously, reducing both voicing and chord formation to one-dimensional spaces limits the user’s choices significantly. Yet I think there exists a form of mastery of this instrument where the formation of chords is fluid and natural and where new intuitions about harmony arise. I found value in improvising with this instrument and experimenting with the arbitrary chord order I picked out, as it seemed to provide a new perspective on how chords interact with each other.</p>
<h3 id="code">Code</h3>
<p>Below is the Arduino code used to send serial data from the Arduino to Max for processing into audio output. All code is available on the <a href="https://github.com/Poseidis/chordshaper">main github repo</a>.</p>
<pre class=" language-c"><code class="prism ++ language-c"><span class="token keyword">const</span> <span class="token keyword">int</span> sensorPins<span class="token punctuation">[</span><span class="token punctuation">]</span> <span class="token operator">=</span> <span class="token punctuation">{</span>A0<span class="token punctuation">,</span> A1<span class="token punctuation">}</span><span class="token punctuation">;</span>
<span class="token keyword">int</span> values<span class="token punctuation">[</span><span class="token punctuation">]</span> <span class="token operator">=</span> <span class="token punctuation">{</span><span class="token number">0</span><span class="token punctuation">,</span> <span class="token number">0</span><span class="token punctuation">}</span><span class="token punctuation">;</span>

<span class="token keyword">void</span> <span class="token function">setup</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token punctuation">{</span>
	Serial<span class="token punctuation">.</span><span class="token function">begin</span><span class="token punctuation">(</span><span class="token number">38400</span><span class="token punctuation">)</span><span class="token punctuation">;</span>
<span class="token punctuation">}</span>
<span class="token keyword">void</span> <span class="token function">loop</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token punctuation">{</span>
	<span class="token keyword">for</span> <span class="token punctuation">(</span><span class="token keyword">int</span> i <span class="token operator">=</span> <span class="token number">0</span><span class="token punctuation">;</span> i <span class="token operator">&lt;</span> <span class="token number">2</span><span class="token punctuation">;</span> i<span class="token operator">++</span><span class="token punctuation">)</span> <span class="token punctuation">{</span>
		values<span class="token punctuation">[</span>i<span class="token punctuation">]</span> <span class="token operator">=</span> <span class="token function">analogRead</span><span class="token punctuation">(</span>sensorPins<span class="token punctuation">[</span>i<span class="token punctuation">]</span><span class="token punctuation">)</span><span class="token punctuation">;</span>
		Serial<span class="token punctuation">.</span><span class="token function">write</span><span class="token punctuation">(</span>values<span class="token punctuation">[</span>i<span class="token punctuation">]</span> <span class="token operator">&gt;&gt;</span> <span class="token number">3</span><span class="token punctuation">)</span><span class="token punctuation">;</span>
		Serial<span class="token punctuation">.</span><span class="token function">write</span><span class="token punctuation">(</span>values<span class="token punctuation">[</span>i<span class="token punctuation">]</span> <span class="token operator">&amp;</span> <span class="token number">7</span><span class="token punctuation">)</span><span class="token punctuation">;</span>
		Serial<span class="token punctuation">.</span><span class="token function">write</span><span class="token punctuation">(</span><span class="token number">255</span><span class="token punctuation">)</span><span class="token punctuation">;</span>
	<span class="token punctuation">}</span>
	Serial<span class="token punctuation">.</span><span class="token function">write</span><span class="token punctuation">(</span><span class="token number">254</span><span class="token punctuation">)</span><span class="token punctuation">;</span>
<span class="token punctuation">}</span>
</code></pre>
<p>Max Patch<br>
<img src="https://raw.githubusercontent.com/Poseidis/chordshaper/main/images/maxcode.PNG" alt="max_patch"></p>
<h3 id="example-sheet-music">Example “Sheet Music”:</h3>
<p>Chord Progression 1</p>

<table>
<thead>
<tr>
<th>Base Chord</th>
<th>Inversion</th>
<th>Chord No.</th>
<th>Duration (beats)</th>
</tr>
</thead>
<tbody>
<tr>
<td>F4 maj7</td>
<td>0</td>
<td>3</td>
<td>1</td>
</tr>
<tr>
<td>E4 majb7</td>
<td>0</td>
<td>2</td>
<td>1</td>
</tr>
<tr>
<td>A4 min7</td>
<td>0</td>
<td>1</td>
<td>1</td>
</tr>
<tr>
<td>G4 min7</td>
<td>0</td>
<td>1</td>
<td>0.5</td>
</tr>
<tr>
<td>A4 majb7</td>
<td>0</td>
<td>2</td>
<td>0.5</td>
</tr>
</tbody>
</table><p>Chord Progression 2</p>

<table>
<thead>
<tr>
<th>Base Chord</th>
<th>Inversion</th>
<th>Chord No.</th>
<th>Duration (beats)</th>
</tr>
</thead>
<tbody>
<tr>
<td>C#5 min7</td>
<td>-2</td>
<td>1</td>
<td>1</td>
</tr>
<tr>
<td>G#4 min7</td>
<td>-1</td>
<td>1</td>
<td>1</td>
</tr>
<tr>
<td>F#4 min7</td>
<td>0</td>
<td>1</td>
<td>1.5</td>
</tr>
<tr>
<td>G#4 majb7</td>
<td>-1</td>
<td>2</td>
<td>0.5</td>
</tr>
</tbody>
</table>
