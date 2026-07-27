---
title: networking for hackers - Part 3
source: networking for hackers.md
category: development
---


This operating system is great! It is designed specifically for SDR, with most of the great
applications and all their dependencies. I like this OS so much I will be using it for all my SDR
projects, tutorials, and courses.

 Run dump1090

Now with DragonOS or the dump1090 software installed on another Linux machine, navigate to
the dump1090 directory.

kali > cd dump1090

Now, simply enter the command;

dragon> ./dump190

255 | P a g e

As you can see above, your RTL-SDR receiver and dump1090 software are providing you with
all the ADS-B data available in your area, including GPS coordinates, altitude, and ground
speed.

If we are looking for just the raw data without formatting, we can simply use the --raw switch.

dragon> ./dump1090 --raw

256 | P a g e

For a more interesting view of the data, we can use the --interactive switch like the one below.
Here dump1090 provides us with an interactive table of the flights in the area updated each
second.

dragon> ./dump1090 --interactive

Maybe the most graphically appealing view of the data sets is similar to radarbox, this data
overlaid on Google maps. In this way, we can actually watch the flights in real-time on a map of
our area.

To watch the graphical data on a map, simply enter the following;

./dump1090 --interactive --net

Then open your browser and navigate to localhost:8080

257 | P a g e

This should open an interactive map showing all the aircraft in your area (your map may appear
slightly different)

Every airplane sends out an ADS-B signal that can be used to track the position and altitude of
the flight. With some free software such as 1090dump and an inexpensive receiver such as the
RTL-SDR, we can follow all the flights within our receiving range (this depends upon many
factors, including your antenna).

This is just one more example of the power and importance of SDR for Hackers!

Spoofing your Global Position (GPS) to Hide Your Location

As you already know, it IS possible to spoof both your IP address and MAC address, but can you
spoof my global position (GPS)? The answer, of course, is YES! This is one of the beauties of
becoming conversant and skilled in Software Defined Radio (SDR).

There are a number of reasons you may not want your global position known. As most of you
know, I have been active in assisting Ukraine to repel the brutal aggression of its neighbor and
former colonial master, Russia. I think it goes without saying that Russia is the aggressor and
needs to be reminded that invading and killing your neighbors is wrong. In this war, global
positions are critical to finding and destroying the opposing side. In addition, early in the war, we
used GPS to geo-locate the yachts of the Russian oligarchs and had them seized by NATO
nations. Soon after that, the remaining yachts began to spoof their global position to evade our
detection.

258 | P a g e

What if the troops on the ground could send out a spoofed GPS signal to hide their location from
artillery and rockets? Most importantly, warships and aircraft send out a GPS signal that can be
tracked by missiles and other weapons. Wouldn't they gain stealth by sending out spoofed
positions? These are just a few  real-life examples of the value of spoofing a GPS signal.

In this tutorial, we will demonstrate how to spoof your GPS position using SDR and the
inexpensive HackRF One.

Install HackRF One

The first step is to purchase and install a HackRF One. The less expensive SDR receivers such as
SDR-RTL are exclusively receivers and are incapable of transmitting signal.

For more on setting up your HackRF One, see this article. (https://www.hackers-
arise.com/post/software-defined-radio-sdr-for-hackers-setting-up-your-hackrf-one)

259 | P a g e

Install GPS Spoof

Next, create a directory named GPS_SPOOF...

kali > mkdir GPS_SPOOF

....and then navigate to the new directory.

kali > cd GPS_SPOOF

Then, download the gps spoof software from github.com

kali > sudo git clone https://github.com/osqzss/gps-sdr-sim.git

260 | P a g e

Now, navigate to the new directory it created

kali > cd gps-sdr-sim

We need to compile the gpssim.c to a file named gps-sdr-sim, and in order to be able to use
motion files, we need to compile it with -DUSER_MOTION_SIZE=400 (this enables the GPS
spoof to appear to be moving rather than remaining static which would likely signal to a receiver
that it was false signal).

kali> sudo gcc gpssim.c -lm -O3 -o gps-sdr-sim -DUSER_MOTION_SIZE=4000

Where:

261 | P a g e

gcc is the GNU C compiler

gpssim.c is the C file that we need to compile

-lm is a link to the math.c library

-O3 optimizes the compilation to higher level

-o places the output into a file named gps-sdr-sim

Locate the Satellite

The next step is to locate the GPS satellite. This is done through the use of the GPS broadcast
ephemeris file. The archive of the daily file can be downloaded here (you must register).

https://cddis.nasa.gov/archive/gnss/data/daily/

These files are then used to generate a simulated pseudo-range and Doppler for the satellites in
your range. This data is then used to create simulated range data to generate digitized I/Q
samples for the GPS signal. Make certain you download the most recent daily file.

https://cddis.nasa.gov/archive/gnss/data/daily/2022/brdc/

262 | P a g e

Next, select a location you want to spoof. In my case, I want to appear to be in Moscow,
specifically the Kremlin. You can go to Google maps to get the GPS coordinates.

263 | P a g e

264 | P a g e

Now, to start your GPS spoof, simply enter the following command with the ephemeris file and
the GPS coordinates such as;

kali > sudo ./gps-sdr-sim -b 8 -e brdc0010.22n -l 55.75911686948662, 37.616404140886715,
100

265 | P a g e

This creates a simulation file named gpssim.bin

Now, to send out a spoofed GPS signal that simulates my position in the Kremlin, I can simply
enter;

kali > sudo hackrf_transfer -t gpssim.bin -f 1575420000 -s 2600000 -a 1 -x 0

266 | P a g e

Success! Now anyone tracking my GPS signal believes that I am in the Kremlin!

Radio Frequency hacking is one of the most important and least appreciated cybersecurity fields.
There really are so many devices and systems that send and receive radio signals that are
vulnerable to exploitation. One of those ubiquitous radio signals is the global positioning system
or GPS. While it is a wonderful tool for finding our way around the world, it can also be used
maliciously to track our every step. By spoofing the GPS, we can hide our position and avoid
tracking by governments and other malicious actors.

Exercises

Install the HDSDR software

1.
2. Listen to your local airport air traffic control communication
3. Use Your RTL-SDR to capture aircraft location and speed data with dump1090

267 | P a g e

Appendix A

Cyber Warrior Wisdom of

Master OTW

Hacking is the new martial art of the 21st century. To become a master hacker, you
must think strategically and analytically. Master OTW offers some of his strategic
wisdom for novice hackers that every cyberwwwarrior should arm themselves with
before going to battle.

1.

2.

3.

4.

5.

6.

7.

8.

Fools talk. The wise listen.

Hacking is a process, not a technology or collection of tools.

Hacking is the ultimate martial art

If a service is free, you are not the customer; you are the product.

Only the fool goes to battle without adequate reconnaissance of their enemy.

"Listen" closely and intently to your enemy; they will tell you everything you
need to know to defeat them.

If you believe in nothing, you can be led to believe anything.

Every adversary--no matter how strong and powerful--always has a weakness.
Find the weakness and exploit it.

268 | P a g e

9.

A great offense might win the battle, but an impregnable defense wins the war.

10.

Turn the power and strength of your opponent against them.

11.

The battle often goes NOT to the strongest but to the most persistent.

12.

There is ALWAYS opportunity in chaos.

13.

Avoid your adversary's strengths and attack their weaknesses.

14.

Never become predictable.

15.  When faced with an adversary of overwhelming power and strength, do not
face them head-on. Strike only when you have the element of surprise.

16.

Understanding human psychology, motivation, and behavior is one of the
hacker's most important tools.

17.

A series of persistent, small wins will defeat your opponent.

18.

Create confusion and dissension within the ranks of your opponent.

19.

At times, it can be advantageous to retreat to lure your opponent into a
vulnerable and indefensible position.

20.

People on social media are much  less than they appear

21.

 In cyber war, industrial facilities can be both a target and a weapon

22.   To  remain safe and anonymous on  the Internet, you must have a thorough and

deep understanding of digital forensics

269 | P a g e

22.  Humility makes you stronger; hubris makes you vulnerable

23.

Unless you believe that civilization and culture reached their zenith during your
youth, then nostalgia for "the good old days" is just the foolishness of the
myopic and old.

270 | P a g e

