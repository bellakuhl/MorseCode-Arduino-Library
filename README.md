<h1>Drawingbot Morse Code Library For Use with Arduino and Servo</h1>

<p>This is a library for generating <a href="http://en.wikipedia.org/wiki/Morse_code">Morse code</a> for a specified letter. It uses a servo library to control a pen attached to a servo on a drawing bot to drive straight while spelling out morse code. It can also be used with an LED or a buzzer to transmit the morse code.</p>

<h2>Authorship and License</h2>

<a rel="license" href="http://creativecommons.org/licenses/by/3.0/"><img alt="Creative Commons License" id="license" src="http://i.creativecommons.org/l/by/3.0/80x15.png" /></a>

<p>This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by/3.0/">Creative Commons Attribution 3.0 Unported License</a>; it is written by Isabella Kuhl.</a></p>

<h2>Installation</h2>

<p>See "Contributed Libraries" on <a href="http://www.arduino.cc/en/Reference/Libraries">arduino.cc Libraries reference</a>. Briefly, place these files in a <code>morse</code> subdirectory in your sketchbook directory. You will also need to have the servo library installed as well.</p>

<h2>Character Support</h2>

<p>All uppercase and lowercase letters are supported</p>

<h2>Motivation</h2>

<p>This was written to be used with a WiFi enabled robot that has had a pen and servo mount added to it to enable it to draw. The pen is securely attached to the servo and as the robot moves forward the morse code corresponding to the characters inputted will be drawn out. The robot uses encoders on both wheels to track how far each tire has rotated and the power of each motor is adjusted accordingly to keep the bot driving straight. The library also has the ability to transmit Morse code using an LED or a buzzer if the pen isn't being used.</p>
