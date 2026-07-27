---
title: Principles of information systems ( etc.) (Z-Library) - Part 4
source: Principles of information systems ( etc.) (Z-Library).md
category: development
---

logic unit (alu) component of the cpu does what it is instructed to do, making either an arith-
metic computation or a logical comparison. (4) The results are then stored in the registers or 
in memory. The instruction and execution phases together make up one machine cycle.
Processing device
Registers
Control unit
ALU
Memory
(2) Decode
(3) Execute
(1) Fetch
(4) Store
I-Time
E-Time
Copyright 2021 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

## Page 136

part 2 • Technology Infrastructure
114
Processor
A multicore processor has two or more independent processing units, called 
cores, that are capable of sequencing and executing instructions. A processor 
with two cores is called a dual-core processor and one with four cores is called 
a quad-core processor. Personal computer processors are available with two, 
four, six, and eight cores. The more cores a processor has, the more sets of 
instructions the processor can receive and process at the same time enabling 
it to complete more work per unit of time.
Each processor produces a series of electronic pulses at a predetermined 
rate, called the clock speed, which governs the speed at which these steps 
are completed. Clock speed is measured in gigahertz (GHz), which is a unit 
of frequency that is equal to one billion cycles per second. Most of today’s 
personal computers operate in the 1–4 GHz range. The higher the clock speed, 
the shorter the interval between pulses and the faster instructions can be 
completed.
Unfortunately, the faster the clock speed of the processor, the more heat 
the processor generates. This heat must be dissipated to avoid corrupting 
the data and instructions the computer is trying to process. Thus, processors 
that run at higher temperatures need bigger heat sinks (a device or sub-
stance for absorbing excessive heat), fans, and other components to elim-
inate the excess heat. This increases the size and weight of the ­computing 
device.
Manufacturing Processors
An integrated circuit (IC)—or chip—is a set of electronic circuits on one small 
piece of semiconductor material, normally silicon. ICs can be made extremely 
small with up to several billion electronic components packed into an area the 
size of a fingernail. Processors and memory chips are examples of integrated 
circuits.
A semiconductor fabrication plant (also called a fab or foundry) is a 
factory where integrated circuits are manufactured. Extreme ultraviolet lithog-
raphy (EUVL) is a highly complex process used in manufacturing computer 
chips with feature sizes that are extremely small—measured in nanometers 
(nm) or billionths of a meter. EUVL involves directing a laser beam at xeon 
gas to heat it up and eject electrons to etch the tiny components of the chip. 
The entire process must occur in a vacuum. Intel is able to create chips with 
features that measure as small as 10 nm across. AMD is expected to achieve 
7 nm lithography, a form of printing, by 2020. For perspective, a molecule of 
water is about 0.5 nm across.
Intel, Samsung, and STMicroelectronics design and manufacture their chips 
in their own fab plants. Some organizations operate a semiconductor fab for the 
purpose of fabricating the designs of other companies. Such organizations are 
known as foundry companies. Apple, Qualcomm, Nvidia, and AMD are exam-
ples of fabless manufacturers; they outsource their manufacturing to foundry 
companies who fabricate the design.
Fabs are extremely expensive to set up and require many expensive devices 
to function. Intel plans to complete the Intel Fab 42 semiconductor factory in 
Chandler, Arizona at a cost of more than $7 billion by 2021. When fully opera-
tional, the factory will employ about 3,000 process engineers, equipment tech-
nicians, and facilities-support engineers and technicians. The fab will produce 
advanced 7 nanometer chips.1
multicore processor:  A processor 
that has two or more independent 
processing units, called cores, that are 
capable of sequencing and executing 
instructions.
clock speed:  A series of electronic 
pulses produced at a predetermined 
rate that affects machine cycle time.
gigahertz (GHz):  A unit of 
frequency that is equal to one billion 
cycles per second; a measure of clock 
speed.
integrated circuit (ic):  A set of 
electronic circuits on one small piece 
of semiconductor material, normally 
silicon.
semiconductor fabrication 
plant:  A factory where integrated 
circuits are manufactured; also called a 
fab or a foundry.
Copyright 2021 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

## Page 137

Chapter 4 • Hardware and Software
115
Multiprocessing
Multiprocessing involves the simultaneous execution of two or more instruc-
tions at the same time. One form of multiprocessing uses coprocessors. A 
coprocessor speeds processing by executing specific types of instructions 
while the CPU works on another processing activity. Coprocessors can be 
internal or external to the CPU and can have different clock speeds than the 
CPU. Each type of coprocessor performs a specific function. For example, a 
math coprocessor chip speeds mathematical calculations, while a graphics 
coprocessor chip decreases the time it takes to manipulate graphics.
The first computer processor was the Intel 4004 with a single 740 kHz pro-
cessor capable of processing roughly 92,000 instructions per second. Today’s 
processors are multicore GHz processors capable of processing over 100 billion 
instructions per second. All computers are multicore processors these days; 
even the iPhone 4s has two cores.
Parallel Processing
Parallel processing is the simultaneous execution of the same task on multi-
ple processors to obtain results more quickly. Systems with thousands of such 
processors are known as massively parallel processing systems, a form of 
multiprocessing that speeds processing by linking hundreds or even thousands 
of processors to operate at the same time, or in parallel, with each processor 
having its own bus, memory, disks, copy of the operating system, and appli-
cations. The processors might communicate with one another to coordinate 
when executing a computer program, or they might run independently of one 
another under the direction of another processor that distributes the work to 
the various processors and collects their results.
The most frequent uses for parallel processing include modelling, simula-
tion, and analyzing large amounts of data. For example, parallel processing is 
used in medicine to develop new imaging systems that complete ultrasound 
scans in less time and with greater accuracy, enabling doctors to provide better, 
more timely diagnoses to patients. Instead of building physical models of new 
products, engineers can create virtual models and use parallel computing to 
test how the products work and then change design elements and materials 
as needed.
Over the past quarter century, scientists have made rapid progress in 
using DNA, the molecule of life, to perform computer-like computations 
within living cells. DNA molecules can take on an astronomical number of 
potential sequences providing the opportunity to perform many computa-
tional operations at the same time. In the future, DNA computing may be 
capable of working inside living cells and combining with their existing 
biochemistry to provide new methods of disease detection and treatment 
possible.
Grid computing is the use of a collection of computers, often owned by 
multiple individuals or organizations, that work in a coordinated manner to 
solve a common problem. Grid computing is a low-cost approach to paral-
lel processing. The grid can include dozens, hundreds, or even thousands of 
computers that run collectively to solve extremely large processing problems. 
Key to the success of grid computing is a central server that acts as the grid 
leader and traffic monitor. This controlling server divides the computing task 
into subtasks and assigns the work to computers on the grid that have (at 
least temporarily) surplus processing power. The central server also monitors 
the processing, and if a member of the grid fails to complete a subtask, the 
multiprocessing:  The 
simultaneous execution of two or more 
instructions at the same time.
coprocessor:  The part of the 
computer that speeds processing by 
executing specific types of instructions 
while the CPU works on another 
processing activity.
parallel processing:  The 
simultaneous execution of the same 
task on multiple processors to obtain 
results faster.
massively parallel processing 
systems:  A system that speeds 
processing by linking hundreds or 
thousands of processors to operate at 
the same time, or in parallel, with each 
processor having its own bus, memory, 
disks, copy of the operating system, 
and applications.
grid computing:  The use of a 
collection of computers, often owned 
by multiple individuals or organizations, 
that work in a coordinated manner to 
solve a common problem.
Copyright 2021 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

## Page 138

part 2 • Technology Infrastructure
116
server restarts or reassigns the task. When all the subtasks are completed, the 
controlling server combines the results and advances to the next task until the 
whole job is completed.
Some 650,000 individuals and 460 organizations have donated their com-
puting device’s unused capacity to the World Community Grid to support 
over two dozen research projects related to health, poverty, and sustainability. 
These include such projects as identifying new drug candidates to combat the 
childhood cancer neuroblastoma, discovering innovative ways to provide clean 
water to millions, and finding novel materials for capturing solar power more 
efficiently. Donors choose a research area of interest to them, download and 
install a toolkit called BOINC, and join the thousands of volunteers allowing 
their device to perform research calculations when it would otherwise be idle, 
thus helping scientists get results in months instead of decades.2
Main Memory
Main memory provides the CPU with a working storage area for program 
instructions and data. The chief function of memory is to rapidly provide data 
and instructions to the CPU. In order for their systems to run efficiently, orga-
nizations must invest in a sufficient amount of main memory. Organizations 
also need large amounts of secondary storage to hold the huge quantities of 
data that cannot fit within the limits of main memory.
Like the CPU, memory devices contain thousands of circuits imprinted on 
silicon chips. Each circuit is either conducting electrical current (on) or not 
conducting current (off). Data is stored in memory as a combination of on or 
off circuit states. Usually, 8 bits are used to represent a character, such as the 
letter A. Eight bits together form a byte (B). In most cases, storage capacity is 
measured in bytes, with 1 byte equivalent to one character of data. The con-
tents of the Library of Congress, with over 126 million items and 530 miles of 
bookshelves, would require about 20 petabytes of digital storage. Table 4.1 lists 
units for measuring computer storage.
main memory:  The component of 
a computer that provides the CPU with 
a working storage area for program 
instructions and data.
byte (b):  Eight bits that together 
represent a single character of data.
Name
Abbreviation
Number of Bytes
Byte
B
1
Kilobyte
KB
1,000
Megabyte
MB
1,0002
Gigabyte
GB
1,0003
Terabyte
TB
1,0004
Petabyte
PB
1,0005
Exabyte
EB
1,0006
Zettabyte
ZB
1,0007
Yottabyte
YB
1,0008
Tab l e 4.1  Computer storage units
RAM and Cache
Computer memory can take several forms. Instructions or data can be tempo-
rarily stored in and read from random access memory (RAM). As currently 
designed, RAM chips are volatile storage devices, meaning they lose their 
contents if the current is turned off or disrupted, which can be caused by a 
random access memory 
(ram):  A form of memory in which 
instructions or data can be temporarily 
stored.
Copyright 2021 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

## Page 139

Chapter 4 • Hardware and Software
117
power surge, a brownout, or electrical noise generated by lightning or nearby 
machines. RAM chips are mounted directly on the computer’s main circuit 
board or in other chips mounted on peripheral cards that plug into the main 
circuit board. These RAM chips consist of millions of switches that are sensitive 
to changes in electric current.
RAM comes in many varieties: Static random access memory (SRAM) is 
byte-addressable storage used for high-speed registers and caches; dynamic 
random access memory (DRAM) is byte-addressable storage used for the 
main memory in a computer; and double data rate synchronous dynamic 
random access memory (DDR SDRAM) is an improved form of DRAM that 
effectively doubles the rate at which data can be moved in and out of main 
memory. DDR has been superseded by second-, third-, and fourth-generation 
DDR called DDR2, DDR3, and DDR4, respectively. DDR3 requires 1.5 volts 
of electrical power to operate, while DDR4 needs just 1.2 volts. DDR4 also 
supports a deep power-down mode, which allows the host device to go into 
standby without needing to refresh its memory—reducing standby power 
consumption by up to 50 percent. Thus, DDR4 reduces the energy required 
to run portable devices and servers. This means longer battery life for por-
table computer users and lower electric bills for organizations that operate 
server farms.3
Although microprocessor speed has roughly doubled every 24 months over 
the past several decades, memory performance has not kept pace. In effect, 
memory has become the principal bottleneck to system performance. Cache 
memory is a type of high-speed memory that a processor can access more 
rapidly than main memory to help ease this bottleneck. Frequently used data 
is stored in easily accessible cache memory instead of slower memory, such as 
RAM. Because cache memory holds less data, the CPU can access the desired 
data and instructions more quickly than when selecting from the larger set in 
primary storage. Thus, the CPU can execute instructions faster, improving the 
overall performance of the computer system. Cache memory is available in 
three forms. The level 1 (L1) cache is on the CPU chip. The level 2 (L2) cache 
memory can be accessed by the CPU over a high-speed dedicated interface. 
The latest processors go a step further, placing the L2 cache directly on the 
CPU chip itself and providing high-speed support for a tertiary level 3 (L3) 
external cache.
Read-only memory (ROM), another type of memory, is nonvolatile, mean-
ing that its contents are not lost if the power is turned off or interrupted. ROM 
provides permanent storage for data and instructions that do not change, such 
as programs and data from the computer manufacturer, including the instruc-
tions that tell the computer how to start up when power is turned on. ROM 
memory also comes in a couple varieties. Programmable read-only memory 
(PROM) is used to hold data and instructions that can never be changed. Elec-
trically erasable programmable read-only memory (EEPROM) is user-­modifiable 
read-only memory that can be erased and reprogrammed repeatedly through 
the application of higher-than-normal electrical voltage.
Secondary Storage
Storing data safely and effectively is critical to an organization’s success. Driven 
by many factors—such as needing to retain more data longer to meet govern-
ment regulatory concerns, storing new forms of digital data such as audio and 
video, and keeping systems running under the onslaught of increasing volumes 
of email—the world’s information is more than doubling every two years. 
Nearly 6 zettabytes (6
1021
3
 bytes) of information was created and stored in 
2013 alone.4 It is mainly unstructured digital content such as video, audio, and 
image objects that is fueling this growth.
cache memory:  A type of high-
speed memory that a processor 
can access more rapidly than main 
memory.
read-only memory (rom):  A 
nonvolatile form of memory.
Copyright 2021 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

## Page 140

part 2 • Technology Infrastructure
118
For most organizations, the best overall data storage solution is likely a com-
bination of different secondary storage options that can store large amounts of 
data, instructions, and information more permanently than allowed with main 
memory. Compared with memory, secondary storage offers the advantages of 
nonvolatility, greater capacity, and greater economy. On a cost-per-megabyte 
basis, secondary storage is considerably less expensive than primary memory. 
The selection of secondary storage media and devices requires understanding 
their primary characteristics: access method, capacity, and portability.
As with other computer system components, the access methods, storage 
capacities, and portability required of secondary storage media are determined 
by the business requirements that must be met. An objective of a credit card 
company might be to rapidly retrieve stored customer data to approve con-
sumer purchases. In this case, a fast access method is critical. In other cases, 
such as equipping the Coca-Cola field salesforce with smartphones, portability 
and ruggedness might be major considerations in selecting and using second-
ary storage media and devices.
In addition to cost, capacity, portability, and ruggedness, organizations 
must address security issues so that only authorized people are allowed access 
to sensitive data and critical programs. Because the data and programs kept 
on secondary storage devices are so critical to most organizations, all of these 
issues merit careful consideration.
Secondary data storage is not directly accessible by the CPU. Instead, com-
puters usually use input/output channels to access secondary storage and then 
transfer the desired data using intermediate areas in primary storage. The most 
common forms of secondary storage devices are magnetic, optical, and solid 
state.
Secondary Storage Devices
Magnetic storage uses tape or disk devices covered with a thin magnetic coat-
ing that enables data to be stored as magnetic particles. Magnetic tape is a type 
of secondary storage medium, which is frequently used for storing backups of 
critical organizational data in the event of a disaster. Examples of tape storage 
devices include cassettes and cartridges measuring a few millimeters in diame-
ter, requiring very little storage space. Magnetic tape has been used as storage 
media since the time of the earliest computers, such as the 1951 Univac com-
puter.5 Continuing advancements have kept magnetic tape as a viable storage 
medium. The High-End Computing Capability (HECC) Project at NASA offers 
scientists and engineers access to supercomputing systems services that are 
backed up by a 132-petabyte tape storage system.6 Many such supercomputers, 
including those deployed at the National Center for Atmospheric Research, use 
robotic tape backup systems. See Figure 4.3.
A hard disk drive (HDD) is a direct access storage device used to store 
and retrieve data from rapidly rotating disks coated with magnetic material. 
A hard disk represents bits of data with small magnetized areas and uses a 
read/write head to go directly to the desired piece of data. Because direct 
access allows fast data retrieval, this type of storage is used by organizations 
that need to respond quickly to customer requests, such as airlines and credit 
card firms. For example, information on the credit history of a customer or 
the seat availability on a particular flight would likely be stored on a direct 
access hard disk drive so that a customer service representative or manager 
could obtain that data in seconds. Hard disk drives vary widely in capacity and 
portability.
Putting an organization’s data online involves a serious business risk—the 
loss of critical data can put a corporation out of business. The concern is that 
the most critical mechanical components inside a HDD storage device—the 
disk drives, the fans, and read/write heads—can fail. Thus, organizations 
now require that their data storage devices be fault tolerant, that is, they can 
secondary storage:  A device 
that stores large amounts of data, 
instructions, and information more 
permanently than allowed with main 
memory.
magnetic tape:  A type of 
sequential secondary storage medium, 
now used primarily for storing backups 
of critical organizational data in the 
event of a disaster.
hard disk drive (hdd):  A direct 
access storage device used to store 
and retrieve data from rapidly rotating 
disks coated with magnetic material.
Copyright 2021 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

## Page 141

Chapter 4 • Hardware and Software
119
continue with little or no loss of performance if one or more key compo-
nents fail. In response, disk manufacturers are continually developing new 
technologies that will improve the performance and reliability of their hard 
disk drives.
A redundant array of independent/inexpensive disks (RAID) is a 
method of storing data that generates extra bits of data from existing data, 
allowing the system to create a “reconstruction map” so that if a hard drive 
fails, it can rebuild lost data. With this approach, data can be split and stored 
on different physical disk drives, using a technique called striping that evenly 
distributes the data. RAID technology has been applied to storage systems to 
improve system performance and reliability.
RAID can be implemented in several ways. RAID 1 subsystems duplicate 
data on the hard drives. This process, called “disk mirroring,” provides an exact 
copy that protects users fully in the event of data loss. However, to keep com-
plete duplicates of current backups, organizations need to double the amount 
of their storage capacity. Other RAID methods are less expensive because they 
duplicate only part of the data, allowing storage managers to minimize the 
amount of extra disk space they must purchase to protect data.
Virtual tape is a storage technology suitable for less frequently needed 
data. With virtual tape systems, data appears to be stored entirely on tape 
cartridges, although some parts might actually be located on faster hard disks. 
The software associated with a virtual tape system is sometimes called a virtual 
tape server. Virtual tape can be used with a sophisticated storage-management 
system that moves data to slower but less costly forms of storage media as 
people use the data less often. Virtual tape technology can decrease data access 
time, lower the total cost of ownership, and reduce the amount of floor space 
consumed by tape operations.
Solid State Secondary Storage Devices
A solid state storage device (SSD) stores data in memory chips rather than 
on hard disk drives or optical media. These memory chips require less power 
and provide much faster data access than magnetic data storage devices. In 
addition, SSDs have no moving parts, so they are less fragile than hard disk 
drives. All these factors make the SSD a preferred choice over hard disk drives 
for portable computers.
redundant array of 
independent/inexpensive disks 
(raid):  A method of storing data 
that generates extra bits of data from 
existing data, allowing the system to 
create a “reconstruction map” so that 
if a hard drive fails, the system can 
rebuild lost data.
virtual tape:  A storage device for 
less frequently needed data. With 
virtual tape systems, data appears to 
be stored entirely on tape cartridges, 
although some parts of it might 
actually be located on faster hard 
disks.
solid state storage device 
(ssd):  A storage device that stores 
data in memory chips rather than on 
hard disk drives or optical media.
Figure 4.3
Robotic tape backup system
The national center for atmospheric 
research uses a robotic tape 
backup system to back up a fleet 
of supercomputers that solve the 
world’s most computationally inten-
sive climate-modeling problems.
U.S Department of Energy
Copyright 2021 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

## Page 142

part 2 • Technology Infrastructure
120
A universal serial bus (USB) flash drive is one example of a commonly 
used SSD. USB flash drives are external to the computer and are removable 
and rewritable. Most weigh less than an ounce and can provide a wide range 
of storage capacity.
Input/Output Devices
Input and output devices are the gateways to the computer system—you use 
them to provide data and instructions to the computer and receive results from 
it. Input and output devices are part of a computer’s user interface, which 
includes other hardware devices and software that allow you to interact with 
a computer system.
In general, businesses want input devices that let them accurately and 
rapidly enter data into a computer system, and they want output devices that 
let them produce timely results. Some organizations have very specific needs 
for input and output, requiring devices that perform specific functions. The 
more specialized the application, the more specialized the associated system 
input and output devices.
Getting data into a computer—input—often requires transferring 
human-readable data, such as a sales order, into a computer system. 
“Human-readable data” means data that people can read and understand. The 
temperature registered on a thermometer is an example of human-readable 
data. An example of machine-readable data is the universal bar code on many 
grocery and retail items that indicates the stock-keeping identification number 
for that item. To the human eye, the universal bar code is unintelligible and 
looks like a series of vertical bars of varying thicknesses. Some data, such as 
magnetic ink on bank checks, can be read by people and machines. Usually, 
people begin the input process by organizing human-readable data and trans-
forming it into machine-readable data. Every keystroke on a keyboard, for 
example, turns a letter symbol of a human language into a digital code that 
the machine can manipulate.
Data entry and input devices come in many forms. They range from special-­
purpose devices that capture specific types of data to more general-purpose 
input devices. Some of the special-purpose data entry and input devices are 
discussed later in this chapter. First, we focus on devices used to enter and 
input general types of data, including text, audio, images, and video for per-
sonal computers.
Common Personal Computer Input Devices
A keyboard and a computer mouse are common devices used for entry and 
input of data, such as characters, text, and basic commands. Some companies 
manufacture keyboards that are more comfortable, more easily adjusted, and 
faster to use than standard keyboards. These ergonomic keyboards, such as the 
split keyboard, are designed to help users avoid wrist and hand injuries caused 
by hours of typing. Other keyboards include touch pads, which let you enter 
sketches on the touch pad while still using keys to enter text. See Figure 4.4. 
A mouse is used to point to and click symbols, icons, menus, and commands 
on the screen. The computer takes a number of actions in response, such as 
entering data into the computer system. Many mice and keyboards are now 
wireless, helping to keep a physical desktop free from clutter.
Optical Data Readers
Individuals and organizations can also use a special scanning device called 
an optical data reader to scan documents. The two categories of optical data 
readers are optical mark recognition (OMR) and optical character recognition 
(OCR). OMR readers are used for tasks such as grading tests and scanning 
forms. With this technology, pencils are used to fill in bubbles or check boxes 
Copyright 2021 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

## Page 143

Chapter 4 • Hardware and Software
121
on OMR paper, which is also called a “mark sense form.” OMR systems are 
used in standardized tests, including the SAT and GMAT tests, and to record 
votes in elections.
In contrast, most OCR readers use reflected light to recognize and scan 
various machine-generated characters. With special software, OCR readers can 
also convert handwritten or typed documents into digital data. After data is 
entered, it can be shared, modified, and distributed over computer networks 
to hundreds or thousands of people. Previously, the use of OCR technology 
required a special scanner device that creates an image of the characters 
to be converted. Expensive OCR software was then required to convert that 
image into text. However, it is now possible to complete this process using 
the camera in an Android smartphone or tablet. Once the image is stored on 
the camera or tablet, you use the Google Drive app for Android to copy the 
image to Google Drive, where Google’s software and servers will do the OCR 
conversion at no cost.
Bar-Code Scanners
A bar-code scanner employs a laser scanner to read a bar-coded label and pass 
the data to a computer. The bar-code reader may be stationary or handheld 
to support a wide variety of uses. This form of input is used widely in-store 
checkouts and warehouse inventory control. Bar codes are also used in hos-
pitals, where a nurse scans a patient’s wristband and then a bar code on the 
medication about to be administered to prevent medication errors.
Several companies have created applications that convert a cell phone cam-
era into a bar-code reader. You can scan a bar code from a print ad, packaging, 
or label to launch Web sites and buy items with a few clicks.
Radio Frequency Identification (RFID) Devices
Radio frequency identification (RFID) is a technology that employs a micro-
chip with an antenna to broadcast its unique identifier and location to receiv-
ers. The purpose of an RFID system is to transmit data by a mobile device, 
called a tag (see Figure 4.5), which is read by an RFID reader and processed 
according to the needs of a computer program. One popular application of 
RFID is to place microchips on retail items and install in-store readers that 
track the inventory on the shelves to determine when shelves should be 
restocked. The RFID tag chip includes a special form of EPROM memory that 
holds data about the item to which the tag is attached. A radio frequency 
signal can update this memory as the status of the item changes. The data 
transmitted by the tag might provide identification, location information, or 
details about the product tagged, such as date of manufacture, retail price, 
color, or date of purchase.
radio frequency identification 
(rfid):  A technology that employs 
a microchip with an antenna to 
broadcast its unique identifier and 
location to receivers.
Figure 4.4
Drawing pad and integrated 
keyboard
A drawing pad and integrated 
keyboard can replace a traditional 
keyboard and mouse for input.
Slobodan Vasic/E+/Getty Images
Copyright 2021 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

## Page 144

part 2 • Technology Infrastructure
122
Pen Input Devices
By touching the screen with a pen input device, you can activate a com-
mand or cause the computer to perform a task, enter handwritten notes, and 
draw objects and figures. Pen input requires special software and hardware. 
­Handwriting-recognition software, for example, converts onscreen handwriting 
into text. Many tablet computers can transform handwriting into typed text and 
store the “digital ink” just the way a person writes it. People can use a pen to 
write and send email, add comments to documents, mark up presentations, 
and even hand draw charts in a document. The data can then be moved, high-
lighted, searched, and converted into text. If perfected, this interface is likely 
to become widely used. Pen input is especially attractive to people who are 
uncomfortable using a keyboard. The success of pen input depends on how 
accurately and at what cost handwriting can be read and translated into digital 
form.
Touch Screens
Advances in screen technology allow display screens to function as input as 
well as output devices. By touching certain parts of a touch-sensitive screen, 
you can start a program or trigger other types of action. Touch screens can 
remove the need for a keyboard, which conserves space and increases porta-
bility. Touch screens are frequently used at gas stations to allow customers to 
select grades of gas and request a receipt; on photocopy machines for selecting 
options; at fast-food restaurants for entering customer choices; at information 
centers for finding facts about local eating and drinking establishments; and 
at amusement parks to provide directions to patrons. They also are used in 
kiosks at airports and department stores. Touch screens are also being used 
for gathering votes in elections.
As touch screens get smaller, the user’s fingers begin to block the infor-
mation on the display. Nanotouch technology is being explored as a means of 
overcoming this problem. With this technology, users control the touch screen 
from its backside so that fingers do not block the display. As the user’s finger 
moves on the back of the display, a tiny graphical finger is projected onto the 
touch screen. Such displays are useful for mobile audio players that are about 
the size of a coin.
Application developers are busy trying to find ways to take advantage 
of Apple’s 3D Touch feature, which the company introduced in the fall of 
2015 with its iPhone 6s smartphone. 3D Touch uses a pressure-sensitive touch 
screen that measures how forcefully you press down on the screen. The new 
feature adds “peek” and “pop” gestures to the tap, swipe, and pinch gestures 
with which most smartphone users are familiar. 3D Touch is designed to bring 
a new dimension of functionality to the iPhone, allowing users to both see 
and feel what a press can do. OpenTable, an online restaurant-reservation 
Figure 4.5
RFID tag
An rfid tag is small compared with 
current bar-code labels used to 
identify items.
iStock.com/albin
Copyright 2021 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

## Page 145

Chapter 4 • Hardware and Software
123
and review service, has included 3D Touch features in the latest version of 
its iPhone apps. Users can 3D Touch the app’s icon to quickly view favorite 
restaurants and upcoming reservations. Within the app, users can “peek” at a 
restaurant’s details by pressing lightly on the name of the restaurant in a list 
of search results. Swiping up offers the ability to instantly see available reser-
vation times, and pressing harder on a restaurant name “pops” a user to the 
restaurant’s full profile.7
Output Devices
Computer systems provide output to decision makers at all levels of an orga-
nization so they can solve a business problem or capitalize on a competitive 
opportunity. In addition, output from one computer system can provide input 
into another computer system. The desired form of this output might be visual, 
audio, or even digital. Whatever the output’s content or form, output devices 
are designed to provide the right information to the right person in the right 
format at the right time.
Display Screens
The display screen is a device used to show the output from the computer. 
Today a variety of flat-panel display screens are far lighter and thinner than 
the early cathode-ray tubes (CRTs) associated with early computers. Table 4.2 
compares types of flat-panel display screens.
Type
Description
Noteworthy Feature
Liquid crystal display (LCD)
Uses several layers of charged liquid 
crystals placed between clear plates 
that are lit from behind by a fluorescent 
light to create light and images
The viewing angle tends to be worse 
than that of plasma displays
Light-emitting diode (LED)
An LCD display that uses light-emitting 
diodes (LEDs) as backlight on the 
screen rather than a fluorescent lamp
Provides better contrast and lower 
energy consumption than LCDs
Organic light-emitting diode 
(OLED)
Functions by exciting organic 
compounds with electric current to 
produce bright, sharp images
Does not employ a backlight, which 
enables improved contrast and lower 
power consumption than LCD and LED 
LCD displays
Plasma
Uses electricity to excite gas atoms to 
light up appropriate phosphors on the 
screen to emit light and color
Performs well in dark conditions but 
not as well in well-lit rooms
Ta b l e 4.2  Various types of flat-panel displays
With today’s wide selection of display screens, price and overall quality can 
vary tremendously. The quality of a screen image is largely determined by the 
number of horizontal and vertical pixels used to create it. The images shown 
on your display device are composed of a million or more pixels. Resolution is 
the total number of pixels contained in the display; the more pixels, the clearer 
and sharper the image. A common resolution is 2,040 horizontal pixels × 
1,536 vertical pixels. The size of the display monitor also affects the quality of 
the viewing. The same pixel resolution on a small screen is sharper than on a 
larger screen, where the same number of pixels is spread out over a larger area.
The computer graphics card takes binary data from the CPU and trans-
lates it into an image you see on your display device. It is the computer 
graphics card that controls the quality of the image and determines how many 
computer graphics card:  A 
component of a computer that 
takes binary data from the CPU and 
translates it into an image you see on 
your display device.
Copyright 2021 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

## Page 146

part 2 • Technology Infrastructure
124
display devices can be attached to the computer. The computer graphics card 
holds the graphics processing unit (GPU), a powerful processing chip that 
renders images on the display screen. After the computer graphics card takes 
binary data from the CPU, the GPU decides what to do with each pixel on 
the screen to create the image. As the GPU creates images, it uses RAM on 
the graphics card (called video RAM or VRAM) to store data about each pixel, 
including its color and location on the screen. One measure of a video card’s 
performance is how many complete images the card can display per second, 
which is called the frame rate. The human eye can process roughly 25 frames 
per second; however, many video games require a frame rate of at least 60 
frames per second to provide a good user experience.
Because many users leave their computers on for hours at a time, power 
usage is an important factor when deciding which type of display to purchase. 
Although power usage varies from model to model, OLED displays are the most 
energy efficient, with LCD monitors generally consuming between 35 and 50 
percent less power than plasma screens.
Aspect ratio and screen size describe the size of the display screen. Aspect 
ratio is the ratio of the width of the display to its height. The aspect ratio of 
width to height of 4:3 or 5:4 is good for people who use their computer to 
view or create Web pages or documents. Widescreen displays typically have an 
aspect ratio of 16:10 or 16:9 to allow improved viewing of movies and video 
games.
Printers and Plotters
One of the most useful and common forms of output is called hard copy, which 
is simply paper output from a printer. The two main types of printers are laser 
printers and inkjet printers, and they are available with different speeds, fea-
tures, and capabilities. Some can be set up to accommodate paper forms, such 
as blank check forms and invoice forms. Newer printers allow businesses to 
create full-color, customized, and individualized printed output using standard 
paper and data input. Ticket-receipt printers, such as those used in restaurants, 
ATMs, and point-of-sale systems are in wide-scale use.
The speed of a printer is typically measured by the number of pages 
printed per minute (ppm). Similar to a display screen, the quality, or res-
olution, of a printer’s output depends on the number of dots printed per 
inch (dpi). A 600-dpi printer prints more clearly than a 300-dpi printer. 
A recurring cost of using a printer is the inkjet or laser cartridge that must be 
replaced ­periodically—every few thousand pages for laser printers and every 
500–900 pages for inkjet printers.
Inkjet printers that can print 10–40 ppm for black and white output and 
5–20 ppm for color output are available for less than $175. With an initial cost 
much less than color laser printers, inkjet printers can print vivid hues and 
can produce high-quality banners, graphics, greeting cards, letters, text, and 
photo prints.
Laser printers are generally faster than inkjet printers and can handle a 
heavier print load volume. A monochrome laser printer can print 25–45 ppm 
and cost anywhere from $150 to $700. Color laser printers can print color pages 
at a rate of 10–35 ppm and are available in a wide range of prices—from $300 
to more than $3,500 for a high-quality color laser printer.
A number of manufacturers offer multiple-function printers that can copy, 
print (in color or black and white), fax, and scan. Such multifunctional devices 
are often used when people need to do a relatively low volume of copying, 
printing, faxing, and scanning. Typical prices for multifunction printers range 
from $100 to $500, depending on features and capabilities. Because these 
devices take the place of more than one piece of equipment, they are less 
expensive to acquire and maintain than a stand-alone fax plus a stand-alone 
printer, copier, and so on. Also, eliminating equipment that was once located 
graphics processing unit 
(gpu):  A powerful processing chip 
that renders images on the screen 
display.
Copyright 2021 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

## Page 147

Chapter 4 • Hardware and Software
125
on a countertop or desktop clears a workspace for other work-related activities. 
As a result, such devices are popular in homes and small office settings.
Mobile print solutions enable users to wirelessly send documents, email 
messages and attachments, presentations, and even boarding passes from any 
smartphone, tablet, or laptop to any mobile-enabled printer in the world. For 
example, PrinterOn Enterprise enables any print requests from any mobile or 
fixed device to be routed to any of over 10,000 printers worldwide that are 
configured with the PrinterOn Enterprise service. Mobile users who use the 
service only need to access a directory of PrinterOn printers and locations and 
then send an email with the attachment to be printed to the email address of 
the printer. American Airlines Admiral Club, Delta Sky Club, Embassy Suites, 
and DoubleTree by Hilton have installed PrinterOn printers at many of their 
locations.
Plotters are a type of hard-copy output device used for general design 
work. Businesses typically use plotters to generate paper or acetate blueprints, 
schematics, and drawings of buildings or new products. Standard plot widths 
are 24 inches and 36 inches, and the length can be whatever meets the need—
from a few inches to many feet.
3D Printers
3D printers have created a major breakthrough in how many items will be “man-
ufactured.” See Figure 4.6. 3D printing technology takes a three-­dimensional 
model of an object stored on a computer and sends it to a 3D printer to create 
the object using strands of a plastic filament or synthetic powder. The filament 
comes in spools of various colors and is fed through a heated extruder that 
moves in several directions to place super thin layers on top of each other. The 
stacks are then bonded together, often using ultraviolet light, to create a 3D 
object. 3D printers come with a wide range of capabilities in terms of how fast 
they can build objects and how large of an object they can build. 3D printers 
for home use typically run $1,000 and up, while commercial 3D printers can 
cost tens of thousands of dollars.
Figure 4.6
3D printer
3D print technology is making it 
possible to print objects ranging 
from everyday objects to houses.
Kyrylo Glivin/Shutterstock.com
3D printing is commonly used by aerospace firms, auto manufacturers, 
and other design-intensive companies. It is especially valuable during the con-
ceptual stage of engineering design when the exact dimensions and material 
strength of the prototype are not critical. Some architectural design firms are 
using 3D printers to create full-color models of their projects to show clients. 
Cincinnati Children’s Hospital uses 3D printing to create models of patients’ 
hearts so that physicians can plan their surgery.8
Copyright 2021 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

## Page 148

part 2 • Technology Infrastructure
126
The automotive, electronics, and toy industries are early adopters of 
using 3D printing to improve upon traditional manufacturing processes. Ford 
Motor Company uses 3D printing to design the new engine cover of its next-­
generation Mustang. Following traditional methods, an engineer would first 
create a computer model and then wait for about four months for a prototype 
to be produced, at a cost of $500,000. Using 3D printing, Ford can print the 
prototype in just four days at a cost of only $3,000.9
3D printing can cut costs and reduce the waste and carbon footprint associ-
ated with traditional manufacturing. With 3D printing, production and assembly 
can be local, with no need to ship products thousands of miles to their desti-
nation. Only the raw materials needed to create the object—be it carbon fiber, 
metal powder, plastic filament, or some other substance—are used. Product 
parts can be replaced using parts manufactured with 3D printing so the entire 
product doesn’t have to be disposed of and replaced each time it malfunctions.
Biomedical engineers are exploring a process called bioprinting, which 
uses 3D printers to build human parts and organs from actual human cells. For 
example, bioprinting is being used to create custom breast implants and grafts 
for cancer patients using the recipient’s own fat and skin cells.10 Regenerative 
medicine pioneer Organovo is able to build blood vessels and cardiac tissue 
via a 3D printer that dispenses cells instead of ink. The firm plans to begin 
selling 3D printed liver tissue.11
Time to Upgrade Your Computer
 Technology Agility
You are shopping to significantly upgrade your current personal laptop computer 
and printer. You are heavy into gaming, film editing, and photo shopping. You need 
a laptop with a powerful CPU and high-quality screen plus a fast, high-quality, color 
printer. You have a budget of $2,500 for the hardware.
Review Questions
1.	 What features and specifications can you use to evaluate various laptops includ-
ing the CPU and screen?
2.	 What features and specifications can you use to evaluate various printers?
Critical Thinking Questions
1.	 Either go online or visit your local computer shop to identify and price one or 
two computers that best meet your needs and stay within your budget.
2.	 Do the same to identify and price one or two printers that best meet your needs.
	 Computer System Classes
In general, computers can be classified as either special-purpose or general-­
purpose. Special-purpose computers are used for limited applications, for 
example, by military, government, and scientific research groups such as the 
CIA and NASA. Other applications include specialized processors found in 
appliances, cars, and other products. For example, automobile repair shops 
connect special-purpose computers to your car’s engine to identify specific per-
formance problems. As another example, IBM is developing a new generation 
of computer chips to develop so-called cognitive computers that are designed 
to mimic the way the human brain works. Rather than being programmed as 
today’s computers are, cognitive computers, such as IBM’s Watson computer, 
are able to learn through experiences and outcomes and mimic human learn-
ing patterns.
bioprinting:  The use of 3D printers 
to build human parts and organs from 
actual human cells.
Critical 
Thinking 
Exercise
Copyright 2021 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

## Page 149

Chapter 4 • Hardware and Software
127
General-purpose computers are used for a variety of applications, includ-
ing the business applications you encounter at work and in college. General-­
purpose computer systems can be divided into three primary classes: portable 
computers used by one user at a time, nonportable computers used by one per-
son at a time, and systems used by multiple concurrent users. Table 4.3 shows 
the general ranges of capabilities for various classes of computer systems.
Single-User Portable Computers: Used to run personal productivity software, access the Internet, read and prepare email 
and instant messages, play games, listen to music, watch videos, access corporate applications and databases, and enter 
data at the point of contact.
Factor
Smartphone
Laptop
Notebook
Tablet
Cost
$120–$1,000
$300–$2,500
$300–$800
$75–$1,500
Weight (pounds)
<0.5
<8
<6
<2
Screen size (inches)
2–5.5
<20
<12
<13
Single-User Nonportable Computers: Meet a wide range of personal computing needs from simply entering data and 
accessing applications via the Internet to running productivity software to performing computer intensive engineering, 
­computer-aided design, and software development functions.
Factor
Thin Client
Desktop
Nettop
Workstation
Cost
$200–$500
$500–$3,000
$150–$550
$1,500–$9,500
Weight (pounds)
<3
20–30
<4
>20
Multiple-User Computers: Meet the computing needs of an organization by supporting key functions such as email, 
printing, security, providing massive data storage and retrieval, and running applications that perform intensive data 
calculations.
Ta b l e 4.3  Classes of computers
Factor
Server
Mainframe
Supercomputer
Cost
>$500
>$75,000
>$250,000
Weight (pounds)
>25
>100
>100
Portable Computers
Many computer manufacturers offer a variety of portable computers, which 
are small enough to carry easily. Portable computers include smartphones, 
laptops, notebooks, and tablets.
Smartphones
While features and capabilities vary from model to model and manufacturer to 
manufacturer, with most smartphones you can place calls, download and run 
apps (e.g., games, contact or to do list manager, and personal and business 
finance managers), send and receive text messages and email, view documents 
and files, take and send photos and videos, get driving directions via GPS, 
browse Web sites, and create a playlist of digital tunes. Smartphones employ 
a combination chipset called a “system on a chip,” which includes processor 
cores, RAM (random access memory) and ROM (read-only memory), interface 
controllers, and voltage regulators, as shown in Figure 4.7. With system on a 
chip, all the critical components of the smartphone are confined to a relatively 
small area, making the device faster and more energy efficient and reducing 
assembly costs.
portable computers:  A computer 
small enough to carry easily.
Copyright 2021 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

## Page 150

part 2 • Technology Infrastructure
128
Laptop
A laptop is a personal computer designed for use by mobile users; it is small 
and light enough to sit comfortably on a user’s lap. Laptops use a variety of 
flat-panel technologies to produce lightweight and thin display screens with 
good resolution. In terms of computing power, laptops can match most desk-
top computers as they come with powerful CPUs as well as large-capacity 
primary memory and disk storage. This type of computer is highly popular 
among students and mobile workers who carry their laptops on trips and to 
meetings and classes. Many personal computer users now prefer a laptop over 
a desktop because of its portability, lower energy usage, and smaller space 
requirements.
Notebooks
Numerous portable computers are smaller than the typical laptop and have 
various names, including notebook and the even smaller ultrabook. Technically 
and traditionally, the difference between the laptop, notebook, and ultrabook 
computer was a matter of size and weight. Technology advances have resulted 
in much smaller and lighter components so differences in size and weight are 
no longer as significant. Today, the difference between a laptop, notebook, and 
ultrabook is mainly what the manufacturer chooses to call its product.
Tablets
A tablet is a portable, lightweight computer that can come with or without a 
keyboard and allows you to roam the office, home, or factory floor, carrying 
the device like a clipboard. You can enter text with a writing stylus directly on 
the screen, thanks to built-in handwriting-recognition software. Other input 
methods include an onscreen keyboard and speech recognition.
Tablets that support input only via a writing stylus are called slate com-
puters. The convertible tablet PC comes with a swivel screen and can be used 
as a traditional notebook or as a pen-based tablet PC. Most new tablets come 
with a front-facing camera for videoconferencing and a second camera for 
snapshot photos and video. Tablets are especially popular with students and 
gamers. They are also frequently used in the healthcare, retail, insurance, and 
manufacturing industries because of their versatility. A tablet computer that 
comes with a removable keyboard is also called a 2-in-1 tablet/PC.
The Apple iPad is a tablet capable of running the same software that runs 
on the Apple iPhone and iPod touch devices, giving it a library of well over a 
million applications. It also runs software developed specifically for the iPad. 
The device supports Internet access over both wireless and cellular networks, 
and it includes an onscreen keypad, although a physical keyboard can also be 
attached. Apple offers a variety of iPad models, ranging from the iPad mini, 
which weighs 0.73 pounds and has a 7.9-inch screen, up to the iPad Pro, which 
weighs 1.5 pounds and has a 12.9-inch screen.
A number of computer companies offer tablets to compete with Apple’s 
iPad, including the Amazon Fire, the Inspiron and Venue by Dell, the Nexus 
7 and Pixel 2 from Google, the Tab 4 and Yoga 920 from Lenovo, the Surface 
laptop:  A personal computer 
designed for use by mobile users, 
being small and light enough to sit 
comfortably on a user’s lap.
tablet:  A portable, lightweight 
computer with no keyboard that allows 
you to roam the office, home, or 
factory floor carrying the device like a 
clipboard.
Figure 4.7
Anatomy of a smartphone
Smartphones employ a combination 
chipset called a “system on a chip,” 
which includes processor cores, 
ram and rom memory, interface 
controllers, and voltage regulators.
System on a chip
Memory
Modem
User Input/output
Keyboard
Display
Microphone
Speaker
GPS
Camera
Copyright 2021 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

## Page 151

Chapter 4 • Hardware and Software
129
Pro from Microsoft, the Shield from Nvidia, the Tablet S and Xperia X72 from 
Sony, and the Encore 2 and Excite by Toshiba.
Nonportable, Single-User Computers
Nonportable single-user computers include thin client computers, desktop 
computers, nettop, and workstations. This class of computer is used to meet the 
unique data processing needs of the individual end users in an organization.
Thin Clients
A thin client is a low-cost, centrally managed computer with no internal or 
external attached drives for data storage. These computers have limited capabil-
ities and perform only essential applications, so they remain “thin” in terms of 
the client applications they include. As stripped-down computers, they do not 
have the storage capacity or computing power of typical desktop computers, 
nor do they need it for the role they play. With no hard disk, they never pick 
up viruses or suffer a hard disk crash. Unlike personal computers, thin clients 
download data and software from a network when needed, making support, 
distribution, and updating of software applications much easier and less expen-
sive. Thin clients work well in a cloud-computing environment to enable users 
to access the computing and data resources available within the cloud. The 
Chromebook, which runs the Chrome OS operating system, is a highly porta-
ble device, is widely used in many schools, and is an example of a thin client.
Since its founding, Certainty Home Loans has helped over 200,000 families 
finance their homes. Headquartered in Plano, Texas, the company offers home 
purchase, refinance, and renovation loans with offices in ten southern and 
southwestern states. The company employs thin clients that are inexpensive, 
energy efficient, and easy to manage. Data is never stored at the device itself, 
so if a device goes bad, the solution is simple: unplug it, replace it with another 
thin client, and send the original device back to headquarters for evaluation 
or replacement.12
Desktop Computers
Desktop computers are single-user computer systems that are highly versatile 
and can provide sufficient computing power, memory, and storage for most 
business computing tasks.
The Apple iMac is a family of Macintosh desktop computers first intro-
duced in 1998 in which all the components (including the CPU and the disk 
drives) fit behind the display screen. Core i5, i7, and i9 is a family of Intel 
desktop computers with a wide range in number of cores, amount of cache 
memory, and processor speeds.
Nettop Computer
Nettop computers are a very small, inexpensive desktop computer typically 
used for Internet access, email, accessing Web-based applications, document 
processing, and audio/video playback. A key feature of nettop computers is 
that they require perhaps one-tenth the amount of power to operate as a typical 
desktop computer.
Workstations
Workstations are more powerful than personal computers but still small 
enough to fit on a desktop. They are used to support engineering and technical 
users who perform heavy mathematical computing, computer-assisted design 
(CAD), video editing, and other applications requiring a high-end processor. 
Such users need very powerful CPUs, large amounts of main memory, and 
extremely high-resolution graphic displays. Workstations are typically more 
expensive than the average desktop computer. Some computer manufacturers 
thin client:  A low-cost, centrally 
managed computer with no internal 
or external attached drives for data 
storage.
desktop computers:  A 
nonportable computer that fits on a 
desktop and can provide sufficient 
computing power, memory, and 
storage for most business computing 
tasks.
nettop computers:  A very small, 
inexpensive desktop computer typically 
used for Internet access, email, 
accessing Web-based applications, 
document processing, and audio/video 
playback.
workstations:  A more powerful 
personal computer used for 
mathematical computing, computer-
assisted design, and other high-end 
processing but still small enough to fit 
on a desktop.
Copyright 2021 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

## Page 152

part 2 • Technology Infrastructure
130
are now providing laptop versions of their powerful desktop workstations. The 
Mac Pro is a series of workstation and server computers based on the high-­
performance Intel Xeon processor.
Area Sq is a UK-based company that provides expertise in office design, 
refurbishment, and workplace services. Its space planning consultants create 
innovative and inspiring office interiors and use powerful Dell workstations to 
run Autodesk AutoCAD and related software. Area Sq needs high-performance 
computing to meet the challenging demands of creating 3D models and then 
rendering those models to put design options in front of clients. If the com-
puter hardware runs slowly, then designers must wait for drawings to regen-
erate when changes are made and this eats into design time. Reliability is also 
critical. Rendering can take hours on many projects and a hardware failure can 
mean losing a full day’s worth of work.13
Servers, Mainframes, and Supercomputers
Servers, mainframes, and supercomputers are designed to support workgroups 
from a small department of two or three workers to large organizations with 
tens of thousands of employees and millions of customers. This class of com-
puter meets the heavy data processing needs of an organization.
Server
A server is a computer employed by many users to perform a specific task, 
such as running network or Internet applications. While almost any computer 
can run a server operating system and server applications, a server computer 
usually has special features that make it more suitable for operating in a mul-
tiuser environment. These features include greater memory and storage capac-
ities, faster and more efficient communications abilities, and reliable backup 
capabilities. A Web server is one specifically designed to handle Internet traffic 
and communications. An enterprise server stores and provides access to pro-
grams that meet the needs of an entire organization. A file server stores and 
coordinates program and data files. Server systems consist of multiuser com-
puters, including supercomputers, mainframes, and other servers.
Servers are frequently kept in a rack containing multiple servers stacked 
one above the other simplifying cabling among components and minimizing 
the required floor space. A rack unit is a unit of measure used to describe 
the height of a server mounted in a rack. One rack unit is 44.45 mm or 1.75 
inches high. A 42U rack would have an internal rack unit height dimension of 
73.5 inches (1.8669 m). However, each 42U rack manufacturer’s server rack 
external dimensions will vary. In an equipment rack filled with servers, a spe-
cial cooling system is needed to prevent excessive heat buildup that would 
otherwise occur from so many power-dissipating devices that are confined in 
a small space.
Servers offer great scalability, the ability to increase the processing capa-
bility of a computer system so that it can handle more users, more data, or more 
transactions in a given period. Scalability is achieved by adding more, or more 
powerful, processors. Scaling up adds more powerful processors, and scaling 
out adds many processors to increase the total data-processing capacity. Most 
new servers include onboard diagnostic capabilities that enable the server to 
alert the IS operations group to potential problems, a capability that used to 
be only available for high-end, mainframe computers.
Mainframe Computer
A mainframe computer is a large, powerful computer shared by dozens or 
even hundreds of concurrent users connected to the machine over a network. 
These refrigerator-sized computers helped NASA put astronauts on the moon 
and are still widely used in large organizations and government agencies. They 
server:  A computer employed by 
many users to perform a specific task, 
such as running network or Internet 
applications.
scalability:  The ability to increase 
the processing capability of a 
computer system so that it can handle 
more users, more data, or more 
transactions in a given period.
mainframe computer:  A large, 
powerful computer often shared by 
hundreds of concurrent users connected 
to the machine over a network.
Copyright 2021 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

## Page 153

Chapter 4 • Hardware and Software
131
can support thousands of users simultaneously and can handle all of the core 
functions of a corporation. Mainframe computers provide the data-processing 
power and data storage capacity that enables banks and brokerage firms to 
deliver new mobile services, credit card companies to detect identity theft, and 
government agencies to better serve citizens. It is estimated that mainframe 
computers store 80 percent of the world’s corporate data and handle $6 trillion 
in annual credit card transactions.14
A key feature of mainframe computers is backward compatibility or the 
ability of current mainframes to run software created decades ago. Many orga-
nizations such as airlines, banks, and brokerage firms are reluctant to change 
their basic transaction processing software. If forced to rewrite this code each 
time they upgraded to newer, faster hardware they would incur considerable 
software development costs and raise the risk that the new software may not 
be as reliable as the old software. Personal computers and cellphones are not 
considered to have backward compatibility and it is often impossible to run 
apps that are even a few years old.
IBM’s latest mainframe computer, the IBM Z, is capable of running more 
than 12 billion encrypted transactions per day. The mainframe uses transaction 
encryption technology to counter cyberattacks against personal and financial 
data that could cost firms a total of $8 trillion by 2022.15 The IBM Z is not 
cheap; it comes with a $500,000 starting price.
Supercomputer
Supercomputers are the most powerful computers with the fastest processing 
speed and highest performance. They are special-purpose machines designed 
for applications that require extensive and rapid computational capabilities. 
Originally, supercomputers were used primarily by government agencies to 
perform the high-speed number crunching needed in weather forecasting, 
earthquake simulations, climate modelling, nuclear research, study of the ori-
gin of matter and the universe, and weapons development and testing. They 
are now used more broadly for commercial purposes in the life sciences and 
the manufacture of drugs and new materials. For example, Procter & Gamble 
uses supercomputers in the research and development of many of its leading 
commercial brands, such as Tide and Pampers, to help develop detergent with 
more soapsuds and improve the quality of its diapers.
Supercomputers are also used to help establish the safety ratings for vehi-
cles sold in the United States. The ratings are based on sophisticated computer 
simulations, during which supercomputers crunch equations involving many 
different variables. These computer-generated simulations are combined with 
data taken from actual crash tests and analyzed to determine safety ratings that 
many consumers use as one factor in determining which car to buy.
Most new supercomputers are based on a recent architecture that employs 
graphics processing unit (GPU) chips in addition to traditional central process-
ing unit (CPU) chips to perform high-speed processing. The CPU is designed 
for sequential serial processing while the GPU is designed to handle multiple 
tasks in parallel. With GPU-accelerated computing, sequential calculations are 
performed in the CPU and highly complicated calculations are performed in 
parallel in the GPU thus providing far superior processing speeds for applica-
tions like artificial intelligence, complex simulations, computer-aided design, 
medical imaging, video editing, and medical imaging.
The speed of supercomputers is measured in petaflops or   
1
1015
3
 floating 
point operations per second (FLOPS). For perspective, one petaflop is roughly 
a million times faster than the typical consumer laptop computer. The fastest 
supercomputer in the world as of June 2018 is the Summit supercomputer 
deployed at the Oak Ridge National Laboratory in Oak Ridge, TN. Table 4.4 
lists the five most powerful supercomputers in use as of June 2018.
backward compatibility:  The 
ability of current mainframes to run 
software created decades ago.
supercomputers:  One of the most 
powerful computer systems with the 
fastest processing speeds.
Copyright 2021 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

## Page 154

part 2 • Technology Infrastructure
132
Quantum Computers
Classical computers, which are the types of computers we have discussed up 
until now, encode information in bits with each bit representing the value of 
1 or 0. These 1s and 0s represent data and act as on/off switches that control 
how the computer functions. Quantum computers, in contrast, are based on 
qubits, which operate according to two key principles of quantum physics: 
superposition and entanglement.
Superposition is a principle of quantum mechanics that says instead of 
thinking about a particle being in one state or changing between a variety of 
states, particles are thought of as existing across all the possible states at the 
same time. Thus, with superposition each qubit can represent both a 1 and 
a 0 at the same time. Entanglement means that qubits in a superposition can 
be interrelated with each other; that is, the state of one qubit (whether it is 
a 1 or a 0) can depend on the state of another. As a result, qubits can act as 
far more sophisticated switches, enabling quantum computers to function in 
ways that allow them to solve difficult problems that are impossible to solve 
using classical computers or that would take them an exceedingly long time 
to solve.16
As of 2018, researchers have built fully programmable five-qubit quantum 
computers but such machines have limited capabilities. A near term goal is to 
build a 50-qubit computer that would achieve quantum supremacy—such a 
quantum computer would provide a computing capacity beyond that of any 
current or possible future classical supercomputer. Such systems are likely to 
be commercially available as early as 2022. By the end of the next decade, 
quantum computers on the order of 100,000-qubit systems will be available.17 
These computers will provide prodigious amounts of computer capacity and 
may be applied in the following ways:
• Enable advancements in the materials, chemistry, and drug industries by 
making accurate molecular-scale models possible for the discovery of 
new materials and drugs
• Model the behavior of atoms and particles at unusual conditions (for 
example, very high energies that can be only created in the Large 
Hadron Collider) without actually having to create those unusual 
conditions
• Improve weather forecasting by allowing for more detailed and accurate 
models
Rank
Name
Where Deployed
Location
Speed (Petaflops)
1
Summit
Oak Ridge National Labora-
tory (ORNL)
Oak Ridge, TN, United States
122.3
2
Sunway TaihuLight
National Supercomputing 
Center
Wuxi, China
93
3
Sierra
Lawrence Livermore National 
Laboratory
Livermore, CA, United States
71.6
4
Tianhe-2A
National Supercomputer 
Center
Guangzho, China
33.9
5
AI Bridging Cloud 
Infrastructure (ABCI)
National Institute of 
Advanced Industrial Science 
and Technology (AIST)
University at Shinagawa, 
Tokyo, Japan,
19.9
SOURCE: “Top 500 the List,” June 2018, https://www.top500.org/lists/2018/06/
Ta b le 4.4  Five most powerful operational supercomputers (June 2018)
Copyright 2021 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

## Page 155

Chapter 4 • Hardware and Software
133
• Analyze the huge amounts of data gathered by satellites and surveillance 
cameras
• Enhance and analyze telescopic images to help astronomers spot more 
exoplanets, and help quickly identify which ones have the most potential 
to harbor life
One major concern is that quantum computers will be so powerful that 
they will be able to decrypt and read secret messages communicated over the 
Internet using the current encryption technologies. New encryption process 
will need to be designed and implemented.
Justifying Investment in Supercomputers
 Analytical Thinking
You have been appointed to a committee tasked with lobbying the state and federal 
government for $25 million in public funds to build and install a new supercom-
puter and associated hardware to support research performed by the university.
Review Questions
1.	 What capabilities does a supercomputer provide that other classes of computers 
cannot?
2.	 What hardware in addition to the supercomputer may be necessary to support 
the research?
Critical Thinking Questions
1.	 What advantages does use of a supercomputer have over creating a grid com-
puting network?
2.	 In a single sentence each, briefly describe three different research projects that 
would require the power of a supercomputer.
	 Server Farm, Data Centers, and Green Computing
This section will cover three topics that provide a good overview of what the 
computer industry and various organizations are doing to meet their computing 
needs in a more efficient and environmentally friendly manner.
Server Farms
Often, an organization will house a large number of servers in the same room, 
where access to the machines can be controlled and authorized support per-
sonnel can more easily manage and maintain the servers. Such a facility is 
called a server farm. Apple, Google, Microsoft, the U.S. government, and many 
other organizations have built billion-dollar server farms in small rural commu-
nities where both land and electricity are cheap.
Server manufacturers are competing heavily to reduce the power required 
to operate their servers and are making “performance per watt” a key part of 
their product differentiation strategy. Low power usage is a critical factor for 
organizations that run server farms made up of hundreds or even thousands of 
servers. Typical servers draw up to 220 watts, although new servers based on 
Intel’s Atom microprocessor draw 8 or fewer watts. The annual power savings 
from such low-energy usage servers can amount to tens of thousands of dollars 
for operators of a large server farm. Server farm operators are also looking 
for low-cost, clean, renewable energy sources. For example, Google purchases 
renewable energy from wind and solar farms.18
Critical 
Thinking 
Exercise
server farm:  A facility that houses 
a large number of servers in the same 
room, where access to the machines 
can be controlled and authorized 
support personnel can more easily 
manage and maintain the servers.
Copyright 2021 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

## Page 156

part 2 • Technology Infrastructure
134
A blade server houses many computer motherboards that include one or 
more processors, computer memory, computer storage, and computer network 
connections. These all share a common power supply and air-cooling source 
within a single chassis. By placing many blades into a single chassis, and then 
mounting multiple chassis in a single rack, the blade server is more powerful 
but less expensive than traditional systems based on mainframes or server 
farms of individual computers. In addition, the blade server approach requires 
much less physical space than traditional server farms.
Data Center
A data center is a climate-and-access-controlled building or a set of buildings 
that houses the computer hardware that delivers an organization’s data and 
information services.
Switch is a Las Vegas-based technology infrastructure organization whose 
core business is the design, construction, and operation of advanced data cen-
ters. Switch is the largest data center provider in Las Vegas with over 2 million 
square feet and whose facilities can generate 315 Megawatts of power. This 
is sufficient energy to power over 200,000 homes. The firm is known for its 
proprietary data center design and futuristic interiors. Switch customers include 
Amazon Web services, eBay, Hulu, and NASA.
Traditional data centers consist of warehouse-size buildings filled with 
row upon row of server racks and powerful air-conditioning systems designed 
to remove dust and humidity from the air and offset the heat generated by 
the processors. Such data centers can use as much energy as a small city and 
run up a power bill of millions of dollars per year. Indeed, energy costs can 
amount to 25 percent of the total cost of operating a data center, with hardware 
expenses and labor costs the other 75 percent. Businesses and technology ven-
dors are working to develop data centers that run more efficiently and require 
less energy for processing and cooling.
About half the energy usage of a traditional data center goes to operate its 
computers. The other half goes to cooling the computers, removing dust and 
humidity from the air, and lighting the facility, along with other systems that sus-
tain the data center. Such a data center has a power usage effectiveness (PUE) 
of 2.0. 
 5 
(PUE
total power consumed/power required to run the computers). The 
ideal goal is a PUE of 1.0, which would indicate that all the power goes to 
running the computers. Google has been able to build data centers that operate 
with a PUE of 1.09.19
In a further attempt to lower ongoing operating costs, many organizations 
are locating their data centers in areas with milder climates and lower energy 
rates and land costs. For organizations in the United States, this translates to 
rural locations in the south and the northwest. Apple, Google, and Facebook 
all operate major data centers in rural North Carolina.
The ability to absorb the impact of a disaster (e.g., hurricane, earthquake, 
terrorism attack, or war) and quickly restore services is a critical concern when 
it comes to the planning for new data centers. As a result, data centers of large 
information systems service organizations are often distributed among multiple 
locations in different areas of the country or even different countries to ensure 
continuous operations in the event of a disaster. If one data center in such an 
arrangement is affected by a disaster, its work load could be redirected to one 
or more of the distributed data centers not affected. Google has distributed its 
data centers with 8 in North America, 1 in South America, 2 in Asia, and 4 in 
Europe.20
blade server:  A server that 
houses many individual computer 
motherboards that include one or 
more processors, computer memory, 
computer storage, and computer 
network connections.
data center:  A climate-and-access-
controlled building or a set of buildings 
that houses the computer hardware 
that delivers an organization’s data and 
information services.
Copyright 2021 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

## Page 157

Chapter 4 • Hardware and Software
135
Electric power is essential to the operation of a data center to run not 
only the servers and computers but also data storage devices, fire protection 
systems, physical security systems, and the HVAC (heating, ventilation, and 
air conditioning) system that controls the ambient environment (temperature, 
humidity, air flow, and air filtering) necessary for the safe operation of all the 
hardware. Power outages are not uncommon and can result from bad weather, 
natural disasters, acts of terrorism, equipment failure, power line damage, and 
other causes. An organization can incur significant financial losses and loss 
of customer goodwill if they are unable to conduct business for an extended 
length of time. As a result, most data centers employ battery operated uninter-
ruptible power sources (UPS) that can provide several hours to a few days of 
backup power. Organizations needing guaranteed backup power longer than 
this will employ backup power generators to ensure that their critical systems 
can continue to run indefinitely even if the utility company cannot deliver 
power.
The Uptime Institute is a U.S. advisory group that has defined four 
tiers of data center classification to enable organizations to quantify and 
qualify their ability to provide a predictable level of performance based on 
expected annual downtime, fault tolerance, and power outage protection. 
These parameters are summarized in Table 4.5.21 Tiers 1 and 2 may be appro-
priate for small organizations where a business disruption of several hours 
to a few days would not have a serious business impact and critical activities 
could be managed manually without computer assistance. Tiers 3 and 4 are 
needed by large organizations where a business disruption of a few hours 
would have serious financial consequences due to the inability to process 
customer orders, plan product shipments, manage manufacturing operations, 
and perform other critical activities. Tier 3 and 4 data centers employ redun-
dant hardware, powerrelated devices, and alternate power sources. If cost 
were not a factor, organizations would implement a tier 3 or 4 data center; 
however, this should only be done when the cost of downtime associated 
with a tier 1 or 2 data center exceeds the cost of upgrading to a tier 3 or 4 
data center.
four tiers of data center 
classification:  A system that 
enables organizations to quantify 
and qualify their ability to provide a 
predictable level of performance.
Feature
Tier 1
Tier 2
Tier 3
Tier 4
Expected annual 
downtime
28.8 hours
22 hours
1.6 hours
26.3 minutes
Fault tolerance
No redundancy
Partial
N+1
2N+1
Power outage 
protection
None
A few hours
72 hours
96 hours
Tab l e 4.5  Classification of data centers by tiers
Green Computing
Electronic devices such as computers and smartphones contain hundreds—or 
even thousands—of components, which are, in turn, composed of many dif-
ferent materials, including some [such as beryllium, cadmium, lead, mercury, 
brominated flame retardants (BFRs), selenium, and polyvinyl chloride] that are 
known to be potentially harmful to humans and the environment. Electronics 
manufacturing employees and suppliers at all steps along the supply chain 
and manufacturing process are at risk of unhealthy exposure to these raw 
Copyright 2021 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

## Page 158

part 2 • Technology Infrastructure
136
materials. Users of these products can also be exposed to these materials when 
using poorly designed or improperly manufactured devices. Care must also be 
taken when recycling or destroying these devices to avoid contaminating the 
environment.
Green computing is concerned with the efficient and environmentally 
responsible design, manufacture, operation, and disposal of IT-related prod-
ucts, including all types of computing devices (from smartphones to super-
computers), printers, printer materials such as cartridges and toner, and 
storage devices. Green computing has three goals: (1) reduce the use of 
hazardous material, (2) allow companies to lower their power-related costs, 
and (3) enable the safe disposal or recycling of computers and computer-re-
lated equipment. Many business organizations recognize that going green is 
in their best interests in terms of public relations, employee safety, and the 
community at large. These organizations also recognize that green computing 
presents an opportunity to substantially reduce total costs over the life cycle 
of their IT equipment.
The United States generates more e-waste (includes discarded cell phones, 
computers, copiers, DVD players, fax machines, monitors, printers, TVs, VCRs) 
than any other country in the world—9.4 million tons/year. Only about 12.5 
percent of this is recycled.22 E-waste is the fastest growing municipal waste 
stream in the United States, according to the EPA. Because it is impossible for 
manufacturers to ensure safe recycling or disposal, the best practice would be 
for them to eliminate the use of toxic substances, particularly since recycling of 
used computers, monitors, and printers has raised concerns about toxicity and 
carcinogenicity of some of the substances. However, until manufacturers stop 
using these toxic substances, safe disposal and reclamation operations must be 
carried out carefully to avoid exposure in recycling operations and leaching of 
materials, such as heavy metals, from landfills and incinerator ashes. In many 
cases, recycling companies export large quantities of used electronics to com-
panies in undeveloped countries. Unfortunately, many of these countries do 
not have strong environmental laws, and they sometimes fail to recognize the 
potential dangers of dealing with hazardous materials. In their defense, these 
countries point out that the United States and other first-world countries were 
allowed to develop robust economies and rise up out of poverty without the 
restrictions of strict environmental policies.
Electronic Product Environmental Assessment Tool (EPEAT) is a system 
that enables purchasers to evaluate, compare, and select electronic products 
based on a total of 51 environmental criteria. Products are ranked in EPEAT 
according to three tiers of environmental performance: Bronze (meets all 23 
required criteria), Silver (meets all 23 of the required criteria plus at least 50 
percent of the optional criteria), and Gold (meets all 23 required criteria plus 
at least 75 percent of the optional criteria), as shown in Table 4.6. EPEAT was 
first implemented in 2006 with Computer and Displays (IEEE 1680.1 standard) 
and has now expanded to Imaging Equipment, under the IEEE 1680.2 standard 
from January 2013. EPEAT is managed by the Green Electronics Council and 
currently evaluates more than 4,400 products from more than 60 manufacturers 
across 43 countries.23
Individual purchasers as well as corporate purchasers of computers, print-
ers, scanners, and multifunction devices can use the EPEAT website (www 
.epeat.net) to screen manufacturers and models based on environmental attri-
butes. Since 2007, U.S. Federal agency purchasers have been directed to meet 
an annual commitment of 95 percent or higher EPEAT purchasing in all covered 
product categories, first by Presidential Executive Order and then by regulatory 
requirement.24
green computing:  Concerned 
with the efficient and environmentally 
responsible design, manufacture, 
operation, and disposal of IT-related 
products, including all types of 
computing devices (from smartphones 
to supercomputers), printers, printer 
materials such as cartridges and toner, 
and storage devices.
electronic product 
environmental assessment tool 
(epeat):  A system that enables 
purchasers to evaluate, compare, and 
select electronic products based on a 
total of 51 environmental criteria.
Copyright 2021 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

## Page 159

Chapter 4 • Hardware and Software
137
The European Union’s Restriction of Hazardous Substances Directive, 
which took effect in 2006, restricts the use of many hazardous materials in com-
puter manufacturing. The directive also requires manufacturers to use at least 
65 percent reusable or recyclable components, implement a plan to manage 
products at the end of their life cycle in an environmentally safe manner, and 
reduce or eliminate toxic material in their packaging. The state of California 
has passed a similar law, called the Electronic Waste Recycling Act. Because of 
these two acts, manufacturers had a strong motivation to remove brominated 
flame retardants from their PC casings.
Lenovo is a Chinese manufacturer of personal computers, tablets, smart-
phones, workstations, servers, electronic storage devices, and printers. Since 
2007, the company’s product development teams have been using increasing 
amounts of recycled plastics to meet new customer requirements, satisfy cor-
porate environmental objectives and targets, and achieve EPEAT Gold registra-
tions for its products. The company’s efforts have resulted in the avoidance of 
up to 248 million pounds of CO2 emissions since 2007.25
Cost/Benefits of Green Computing
 Social Responsibility
Your organization wants to update the four-year-old laptop computers carried by 
its 200 sales and customer service reps to the latest technology. As a member of 
the sales organization, you have been asked to participate in choosing the portable 
computing device to be used. The committee spent considerable time defining the 
requirements the replacement device must meet and has narrowed its choice down 
to two contenders. They are both 2-in-1 tablets with dual processor CPUs each 
running at over 2.4 MHz. Both have screens that are about 12.3 inches, and both 
come with SSD and 128 GB of storage capacity. In other words, both devices are 
almost identical in terms of hardware specifications. However, one device meets all 
the EPEAT requirements to be rated as a gold product and costs $150 more than 
the other choice that is rated a bronze product.
Review Questions
1.	 Why might the committee decide that 2-in-1 tablets versus just a regular tablet 
or laptop are necessary for the sales and customer service reps?
2.	 Should the committee consider tablets with touch screens or a screen that can 
interact with ink enabled pens? Why or why not?
Critical Thinking Questions
1.	 What additional steps should the committee take before reaching a final decision?
2.	 Should the committee choose more expensive device at an additional cost of 
$30,000 to the company? If so, how can they justify this choice?
Critical 
Thinking 
Exercise
Tier
Number of Required ­Criteria 
That Must Be Met
Number of Optional ­Criteria 
That Must Be Met 
Bronze
All 23
None
Silver
All 23
At least 50%
Gold
All 23
At least 75%
Source: “EPEAT Criteria,” EPEAT, www.epeat.net/resources/criteria-2, accessed March 17, 2018.
Ta bl e 4.6  EPEAT product tiers for computers
Copyright 2021 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

## Page 160

part 2 • Technology Infrastructure
138
	 System Software
Software consists of computer programs that control the workings of com-
puter hardware. Software can be divided into two types: systems software and 
application software. System software includes operating systems, utilities, 
and middleware that coordinate the activities and functions of the hardware 
and other programs throughout the computer system. Application software 
consists of programs that help users solve computing problems. Examples 
include a spreadsheet program or a program that captures and displays data 
that enables monitoring of a manufacturing process.
The effective use of software can have a profound impact on individu-
als and organizations. It can make the difference between profits and losses 
and between financial health and bankruptcy. Gartner estimates that around 
$421 billion will be spent worldwide on enterprise software (excluding con-
sumer spending) in 2019.26 This is far different from when computers first 
were available; software was given away and customers paid only for the 
hardware. Indeed, the software industry was born in 1969 when IBM decided 
to unbundle—and charge customers separately for—its software and services. 
Although business computers had been in use since the mid-1950s, hardware 
manufacturers had previously bundled software with their hardware without 
charging separately for it.
The primary role of system software is to control the operations of com-
puter hardware. System software also supports the problem-solving capabili-
ties of application programs. System software can be divided into three types: 
operating systems, utility programs, and middleware.
Operating Systems
An operating system (OS) is a set of programs that controls a computer’s 
hardware and acts as an interface with application software; see Figure 4.8. The 
kernel, as its name suggests, is the heart of the OS and controls its most criti-
cal processes. The kernel ties all OS components together and regulates other 
programs. An operating system can control one or more computers, or it can 
system software:  Software that 
includes operating systems, utilities, 
and middleware that coordinate the 
activities and functions of the hardware 
and other programs throughout the 
computer system.
application software:  Programs 
that help users solve particular 
computing problems.
operating system (os):  A set of 
computer programs that controls the 
computer hardware and acts as an 
interface to application software.
kernel:  The heart of the operating 
system that controls the most critical 
processes of the OS.
Figure 4.8
Role of operating systems
The role of the operating system 
is to act as an interface between 
application software and hardware.
User interface
Application program interface
Operating system kernel and utilities
Hardware drivers
Hardware
Copyright 2021 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

## Page 161

Chapter 4 • Hardware and Software
139
allow multiple users to interact with one computer. The various combinations 
of OSs, computers, and users include the following:
• Single computer with a single user. This system is commonly used in 
personal computers, tablets, and smartphones that support one user at a 
time. Examples of OSs for this setup include Microsoft Windows, macOS, 
and Google Android.
• Single computer with multiple simultaneous users. This type of system is 
used in larger server or mainframe computers that support hundreds or 
thousands of people, all using the computer at the same time. Examples 
of OSs that support this kind of system include UNIX, z/OS, and HP-UX.
• Multiple computers with multiple users. This type of system is used in 
computer networks, including home networks with several computers 
attached as well as large computer networks with hundreds of computers 
attached, supporting many users, who may be located around the world. 
Network server OSs include Red Hat Enterprise Linux Server, Windows 
Server, and Mac OS X Server.
• Special-purpose computers. This type of system is typical of a number of 
computers with specialized functions, such as those that control sophisti-
cated military aircraft, digital cameras, or home appliances. Examples of 
OSs designed for these purposes include Windows Embedded, Symbian, 
and some distributions of Linux.
Functions Performed by the Operating System
The programs that make up the OS perform a variety of activities, including 
the following:
• Control common computer hardware functions such as accepting input 
from the keyboard, retrieving data from a storage device, and displaying 
data on the screen.
• Provide a user interface and manage input/output operations.
• Provide a degree of hardware independence so that a software program 
can run on multiple computers, without concern for the specific underly-
ing hardware.
• Manage memory is accessed, maximizing the use of available memory 
and storage to provide optimum efficiency.
• Manage processing tasks
• Provide networking capabilities so that computers can join together in a 
network to send and receive data and share computing resources
• Control access to system resources to provide a high level of security 
against unauthorized access to the users’ data and programs as well as 
record who is using the system and for how long.
• Manage files to ensure that files are available when needed and that they 
are protected from access by unauthorized users.
Some operating systems provide sight interfaces that enable a computer 
to perform different commands or operations depending on where a person is 
looking on the screen. Some companies, including Neuralink backed by Elon 
Musk, are experimenting with sensors attached to the human brain to create 
interfaces that can detect brain waves and control a computer as a result. Sight 
and brain interfaces can be very helpful to disabled individuals.27
Task Management
Operating systems use the following five approaches to task management to 
increase the amount of processing that can be accomplished in a given amount 
of time:
• Multiuser. Enables two or more users to run programs at the same time 
on the same computer. Some operating systems permit hundreds or even 
Copyright 2021 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

## Page 162

part 2 • Technology Infrastructure
140
thousands of concurrent users. The ability of the computer to handle an 
increasing number of concurrent users smoothly is called scalability.
• Multiprocessing. Supports running a program on more than one CPU.
• Multitasking. Enables more than one program to run concurrently.
• Multithreading. Enables different threads of a single program to run con-
currently. A thread is a set of instructions within an application that is 
independent of other threads. For example, in a spreadsheet program, 
the thread to open the workbook is separate from the thread to sum a 
column of figures.
• Real-time. Responds to input instantly. To do this, the operating system 
task scheduler can stop any task at any point in its execution if it deter-
mines that another higher priority task needs to run immediately. Real-
time operating systems are used to control the operation of jet engines, 
the deployment of air bags, and the operation of antilock braking 
­systems—among other uses.
Not all operating systems employ all these approaches to task manage-
ment. For example, the general-purpose operating systems with which we are 
most familiar (e.g., Windows and Mac OS) cannot support real-time processing.
Current Operating Systems
Today’s operating systems incorporate sophisticated features and capabilities. 
Table 4.7 classifies a few current operating systems by sphere of influence.
Personal
Workgroup
Enterprise
Microsoft Windows
Microsoft Windows 
Server
Microsoft Windows 
Server
Mac OS X, iOS
Mac OS X Server
—
Linux
Linux
Linux
Google Android, 
Chrome OS
UNIX
UNIX
HP webOS
IBM i and z/OS
IBM i and z/OS
—
HP-UX
HP-UX
Tab l e 4.7  Operating systems by sphere of influence
From time to time, software manufacturers drop support for older operat-
ing systems—meaning that although computers and software running under 
these operating systems will continue to run, the operating system manufac-
turer will no longer provide security fixes and updates. Without such patches, 
the users’ computers are more susceptible to being infected by viruses and 
malware. For example, Google dropped support for Windows XP and Vista 
users running on its Chrome browser.28
Discontinuance of support is a strong reason to upgrade to new software. 
However, many organizations take the approach that “if it ain’t broke, don’t fix 
it.” In their view, other projects take priority over updating software that is still 
functioning. However, this approach can lead to interruptions in key systems. 
For example, planes were grounded for several hours at Paris’ busy Orly air-
port when a computer that links air traffic control systems with France’s main 
weather bureau stopped working. The computer was running on Windows 
3.1, a 25-year-old operating system dropped from support by Microsoft over a 
dozen years ago.29
Copyright 2021 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

## Page 163

Chapter 4 • Hardware and Software
141
Microsoft PC Operating Systems
In 1980, executives from IBM approached Microsoft’s Bill Gates regarding the 
creation of an operating system for IBM’s first personal computer. That oper-
ating system, which was ultimately called Microsoft Disk Operating System 
(MS-DOS), was based on Microsoft’s purchase of the Quick and Dirty Oper-
ating System (QDOS) written by Tim Paterson of Seattle Computer Products. 
Microsoft bought the rights to QDOS for $50,000. QDOS, in turn, was based 
on Gary Kildall’s Control Program for Microcomputers (CP/M).
As part of its agreement with Microsoft, IBM allowed Microsoft to retain 
the rights to MS-DOS and to market MS-DOS separately from the IBM per-
sonal computer. The rest is history, with Gates and Microsoft earning a fortune 
from the licensing of MS-DOS and its descendants.30 MS-DOS, which had a 
command-­based interface that was difficult to learn and use, gave way to the 
more user-friendly Windows 1.0 operating system in 1985. This was Microsoft’s 
first true attempt at a graphical user interface and it relied heavily on use of a 
mouse before the mouse was a common computer input device.
With its launch of Windows 10, Microsoft announced that it is moving 
away from its usual practice of releasing major new versions of its Windows 
operating system every few years. Instead, the company provides ongoing, 
incremental upgrades and improvements, rolled out automatically, a few times 
each year. Unless users change the automatic update setting, they receive these 
updates as soon as they come out. Organizations, whose information systems 
professionals desire minimal change in order to ensure reliable operations of 
corporate applications, may elect to opt out of such frequent updates. Microsoft 
hopes that the automatic, rapid update cycle will force users to stay current so 
that all hardware devices work as intended, new features are added to existing 
software, and ensure that the latest security patches are installed for users’ 
safety.
The Windows 10 operating system is built on a single, common kernel 
called OneCore that works across a variety of devices, from phones, tablets, 
personal computers, large-screen displays, the Xbox, and even the HoloLens 
(the Microsoft headband that enables users to view holograms). This means 
that application developers working with Windows 10 can target the same 
core environment for their apps, and such apps will work across a range of 
screen sizes and devices including computers, tablets, and smartphones. This 
represents the achievement of a goal that Microsoft has had for more than 20 
years: Windows Everywhere with a potential market of one billion users.31
Apple Computer Operating Systems
In July 2001, Mac OS X was released as an entirely new operating system 
for the Mac. Based on the UNIX operating system, Mac OS X included a new 
user interface with luminous and semi-transparent elements, such as buttons, 
scroll bars, and windows along with fluid animation to enhance the user’s 
experience.
Since its first operating system release, Mac OS X 10.0 in 2001, Apple 
has upgraded OS X almost every year. The first eight versions of the OS were 
named after big cats, the latest are named after places in California. OS X 10.13, 
also known as macOS High Sierra, is Apple’s latest operating system. macOS 
Sierra offers many updates to provide improved security and performance as 
well as longer battery life.32
Because macOS runs on Intel processors, Mac users can set up their com-
puters to run both Windows and macOS and select the platform they want 
to work with when they boot their computers. Such an arrangement is called 
dual booting. While Macs can dual boot into Windows, the opposite is not true. 
macOS cannot be run on any machine other than an Apple device. However, 
Windows PCs can dual boot with Linux and other OSs.
Copyright 2021 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

## Page 164

part 2 • Technology Infrastructure
142
Linux
Linux is an OS developed in 1991 by Linus Torvalds as a student in Finland. 
The OS is distributed under the GNU General Public License, and its source 
code is freely available to everyone. It is, therefore, called an open-source 
operating system.
Individuals and organizations can use the open-source Linux code to create 
their own distribution (flavor) of Linux. A distribution consists of the Linux 
kernel (the core of the operating system)—which controls the hardware, man-
ages files, separates processes, and performs other basic functions—along with 
other software. This other software defines the terminal interface and available 
commands, produces the graphical user interface, and provides other useful 
utility programs. A Linux distributor takes all the code for these programs and 
combines it into a single operating system that can be installed on a computer. 
The distributor may also add finishing touches that determine how the desktop 
looks, what color schemes and character sets are displayed, and what browser 
and other optional software are included with the operating system. Typically, 
the distribution is “optimized” to perform in a particular environment, such as 
for a desktop computer, server, or TV cable box controller.
Hundreds of distributions of Linux have been created. Many distributions 
are available as free downloads. Three of the most widely used distributions 
come from software companies Red Hat, SUSE, and Canonical. Although the 
Linux kernel is free software, both Red Hat and SUSE produce retail versions of 
the operating system that earn them revenues through distribution and service 
of the software. openSUSE is the distribution sponsored by SUSE.
Paddy Power Betfair is a large online betting company based in Dublin, 
Ireland that must handle 130 million transactions each day in a fast and secure 
manner. Its systems must operate reliably in a 24 × 7 environment that provides 
for updates and maintenance without affecting customers. The firm selected 
the Red Hat Enterprise Linux operating system to provide a stable and secure 
platform to support its data center.33
Google Android and Apple iOS
Smartphones now employ full-fledged personal computer operating systems 
such as the Google Android and Apple iOS that determine the functionality of 
your phone and the applications that you can run. These operating systems 
have software development kits that allow developers to design thousands of 
apps providing a myriad of mobile services. When it comes to smart phone 
operating systems, Google Android has achieved over 80 percent of the world-
wide market share and there are over 3.3 million apps available. Apple iOS 
holds the remaining share of the market and there are over 2.2 million apps 
available.34,35,36 For tablet operating systems, Android has a 65 percent world-
wide market share and iOS has a 33 percent market share.37
Windows Server
Microsoft designed the Windows Server workgroup operating system to per-
form a host of tasks that are vital for Web sites and corporate Web applications. 
For example, Microsoft Windows Server can be used to coordinate and man-
age large data centers. Windows Server delivers benefits such as a powerful 
Web server management system, virtualization tools that allow various oper-
ating systems to run on a single server, advanced security features, and robust 
administrative support. Windows Home Server allows individuals to connect 
multiple PCs, storage devices, printers, and other devices into a home network. 
Windows Home Servers provides a convenient way for home users to store 
and manage photos, video, music, and other digital content. It also provides 
backup and data recovery functions.
Copyright 2021 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

## Page 165

Chapter 4 • Hardware and Software
143
UNIX
UNIX is a powerful OS originally developed by AT&T for minicomputers—the 
predecessors of servers, which were larger and more powerful than PCs but 
smaller and less powerful than mainframes. UNIX can be used on many com-
puter system types and platforms, including workstations, servers, and main-
frame computers. UNIX also makes it easy to move programs and data among 
computers or to connect mainframes and workstations to share resources. There 
are many variants of UNIX, including HP-UX from Hewlett-Packard Enterprise, 
AIX from IBM, and Solaris from Oracle. The UNIX platform (a computer capa-
ble of running the UNIX operating system plus the operating system itself) is 
considered a high-cost platform compared to Linux and Windows Server.
The Credit Information Bureau India Limited (CIBIL) collects consumer 
financial data to create credit reports and scores that are provided to lenders 
to help them evaluate applications for loans. This is a very high-volume busi-
ness with millions of reports generated each day. CIBIL employs blade servers 
running the HP-UX operating system to meet this demand.38
Mac OS X Server
The Mac OS X Server is the first modern server OS from Apple Computer, and 
it is based on the UNIX OS. Designed for OS X and iOS, OS X Server makes it 
easy to collaborate, develop software, host Web sites and wikis, configure Mac 
and iOS devices, and remotely access a network. Smartphone users running 
iOS can now open, edit, and save documents on OS X Server.
Running Multiple Operating Systems with Server Virtualization
During the 1990s, organizations used to dedicate one server to each applica-
tion. This allowed easy, although expensive backup in the event of a server 
failure. The application would simply be moved to a standby server. It also 
avoided software incompatibility issues between the operating system running 
on the server and the operating system on which the application could run. 
The one and only one operating system running on the server would be one 
on which the application could run. With advances in the speed and computing 
power of servers, the individual applications were only using 25 percent or less 
of the server hardware capacity—very wasteful.
Server virtualization is an approach to improving hardware utilization by 
logically dividing the resources of a single physical server to create multiple 
logical servers called virtual machines. Each virtual machine acts as its own 
dedicated machine. The server on which one or more virtual machines are 
running is called the host server. Each virtual machine includes its own guest 
operating system to manage the user interface and control how the virtual 
machine uses the host server’s hardware. Thus, several different operating 
systems can run on a virtualized server.
The hypervisor is a virtual server program that controls the host processor 
and resources, allocates the necessary resources to each virtual machine, and 
ensures that they do not disrupt each other. VMware from Dell Technologies 
and Microsoft Hyper-V are the two dominant hypervisor vendors. Over three-
fourths of organizations employ virtualization.39 Figure 4.9 depicts the server 
virtualization environment.
With server virtualization, the server can run several server applications 
concurrently and operate at much higher level of total capacity—perhaps 80 
percent or more. As a result, a data center with say 400 physical servers could 
be converted to a virtualized environment with perhaps as few as 24 virtual-
ized servers. There would be a huge savings in capital costs for hardware and 
because there are fewer servers, there would be additional ongoing savings in 
energy costs to power the servers and cool the data center. Also, fewer soft-
ware licenses are required for fewer physical machines and fewer personnel 
server virtualization:  A method 
of logically dividing the resources 
of a single physical server to create 
multiple logical servers, each acting as 
its own dedicated machine.
hypervisor:  A virtual server program 
that controls the host processor and 
resources, allocates the necessary 
resources to each virtual system, and 
ensures that they do not disrupt each 
other.
Copyright 2021 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

## Page 166

part 2 • Technology Infrastructure
144
are required to operate and maintain the servers. Thus, server virtualization 
provides three benefits: (1) lower capital costs for hardware, (2) savings in 
energy costs to operate and cool the data center, and (3) savings in software 
licenses and personnel costs.
PKO Bank Polski S.A. is the largest commercial bank in Poland providing 
service to over 9 million customers. The bank’s information systems must oper-
ate 24 × 7 with a goal of less than 1 hour of unscheduled downtime per year. 
Server virtualization is now a standard for critical applications at the bank and 
this strategy has reduced hardware related costs, cut unscheduled downtime 
for applications, and reduced the time spent on problem solving.40
Enterprise Operating Systems
Mainframe computers, often referred to as “Big Iron,” provide the computing 
and storage capacity required for massive data-processing environments, and 
they provide systems that can support many users while delivering high per-
formance and excellent system availability, strong security, and scalability. A 
wide range of application software has been developed to run in the mainframe 
environment, making it possible to purchase software to address almost any 
business problem. Examples of mainframe OSs include z/OS from IBM, HP-UX 
from Hewlett-Packard, and Linux. The z/OS is IBM’s first 64-bit enterprise OS 
and is capable of handling very heavy workloads, including serving thousands 
of concurrent users and running an organization’s critical applications. (The z 
stands for zero downtime.)
Embedded Operating Systems
An embedded system is a computer system that is implanted in and dedicated 
to the control of another device often within a larger mechanical or electrical 
system. An embedded system is designed with one purpose in mind while a 
general-purpose computer can be used for many tasks. Embedded systems 
control many devices in common use today, including video game consoles, 
ATM machines, TV cable boxes, digital watches, digital cameras, MP3 players, 
calculators, microwave ovens, washing machines, and traffic lights. The typical 
car contains many embedded systems, including those that control antilock 
brakes, air bag deployment, fuel injection, active suspension devices, transmis-
sion control, and cruise control.
embedded system:  A computer 
system (including some sort of 
processor) that is implanted in and 
dedicated to the control of another 
device.
Figure 4.9
Server virtualization
Virtualization is an approach to 
improving hardware utilization by 
logically dividing the resources of 
a single physical server to create 
multiple logical servers called virtual 
machines. 
Virtual
Machine #1
App #1
Guest
Operating
System
Guest
Operating
System
Guest
Operating
System
Guest
Operating
System
App #2
Hypervisor
Host system operating system
Host system hardware
App #3
App #4
Virtual
Machine #2
Virtual
Machine #3
Virtual
Machine #4
Copyright 2021 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

## Page 167

Chapter 4 • Hardware and Software
145
The U.S. power grid is extremely complex consisting of over 200,000 miles 
of transmission lines managed by some 500 companies. The grid is designed 
so that peak energy demand in one area of the country can be met by using 
electricity generated elsewhere. Embedded computers are used to monitor 
energy generation, transmission, distribution, and usage, thus enabling intel-
ligent real-time decisions regarding its operation to be made. See Figure 4.10. 
Alarmingly, as Ted Koppel points out in his book Lights Out, a well-designed 
cyberattack on the power grid could cripple our power grid affecting tens of 
millions of people.
Figure 4.10
Electrical grid near urban 
area
U.S. Power grid relies on embed-
ded systems to help control and 
manage its operation.
An embedded operating system is designed to run in computers with a 
limited amount of memory and it must be highly reliable. As a result, it may not 
perform many of the functions that nonembedded computer operating systems 
provide, just those functions that are required by the specialized application 
it runs. Furthermore, unlike other operating systems, an embedded operating 
system does not load and execute multiple applications. An embedded operat-
ing system is only able to run a single application. Some of the more popular 
OSs for embedded systems include Google Android Things, the Windows IoT 
family of Microsoft embedded operating systems, many variations of embedded 
Linux, Lynx Software’s LynxOS, Blackberry’s QNX used to build autonomous 
cars, and Wind River’s VxWorks.
Swiss-based Liebherr collaborated with Microsoft to create the SmartDe-
viceBox to provide interesting new capabilities to their refrigerators. Based 
on the Windows 10 IoT Core operating system, the SmartDeviceBox is about 
twice the size of a large USB drive and plugs directly into a port on most of 
the brand’s newest refrigerators. With it you can view the status of your refrig-
erator online and make changes to its settings from any location. If a problem 
occurs with your refrigerator (e.g., the temperature varies outside the desired 
setting), you are notified by means of an alarm message sent to your smart-
phone or tablet. The Media Intelligence Assistant voice module enables you to 
verbally add additional groceries to your shopping list which you can access 
via a mobile app while you are in the supermarket.41
The Wii gaming console uses an embedded operating system based on the 
Linux kernel. Linux is a popular choice for embedded systems because it is free 
and highly configurable. It has been used in many embedded systems, including 
e-book readers, ATMs, smartphones, networking devices, and media players.
Utility Programs
Utility programs perform a variety of tasks typically related to system mainte-
nance or problem correction. For example, there are utility programs designed 
to merge and sort sets of data, keep track of computer jobs being run, compress 
data files before they are stored or transmitted over a network (thus saving 
space and time), and perform other important tasks.
utility programs:  A program 
that helps to perform maintenance 
or correct problems with a computer 
system.
urbans/Shutterstock.com
Copyright 2021 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

## Page 168

part 2 • Technology Infrastructure
146
Just as your car engine runs best if it has regular maintenance, computers 
also need regular maintenance to ensure optimal performance. Over time, your 
computer’s performance can start to diminish as system errors occur, files clut-
ter your hard drive, and security vulnerabilities materialize. Sysinternals Suite 
is a collection of Windows utilities that can be downloaded for free from the 
Microsoft TechNet Web site. These utilities can be used to boost the perfor-
mance of a slow PC, repair errors in the registry and on a hard drive, remove 
unnecessary files, improve system security and privacy, and optimize sluggish 
system processes.
Although many PC utility programs come installed on computers, you can 
also purchase utility programs separately. There are hardware utilities that can 
be used to check the status of all parts of the PC, including hard disks, memory, 
modems, speakers, and printers. Disk utilities check the hard disk’s boot sector, 
file allocation tables, and directories and analyze them to ensure that the hard 
disk is not damaged. Antivirus and antimalware utilities can be used to con-
stantly monitor and protect a computer. If a virus or other malware is found, it 
can often be removed. File-compression utilities can reduce the amount of disk 
space required to store a file or reduce the time it takes to transfer a file over the 
Internet. Both Windows and Mac operating systems let you compress or decom-
press files and folders. A broad range of network- and systems-management 
utility software is available to monitor hardware and network performance and 
trigger an alert when a server is crashing or a network problem occurs. IBM’s 
Tivoli Netcool Network Management, Hewlett-Packard’s Automated Network 
Management Suite, and Paessler’s PRTG Network Monitor can be used to solve 
computer network problems and help save money (see Figure 4.11).
Figure 4.11
PRTG network monitor
Prtg network monitor and other 
network utility software can help 
you to keep track of network com-
ponents, traffic flows, and network 
performance.
Source: Paessler AG
Managing the vast array of operating systems for smartphones and mobile 
devices has been difficult for many companies. Many organizations unwisely 
allow employees to connect to corporate databases using smartphones and 
mobile devices with little or no guidance. Utility programs called mobile device 
Copyright 2021 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

## Page 169

Chapter 4 • Hardware and Software
147
management (MDM) software can help a company manage security, enforce 
corporate strategies, and control downloads and content streaming from cor-
porate databases into smartphones and mobile devices. They can even be used 
to wipe a device of all apps and data if it is lost or stolen. Brookdale Senior 
Living is a major owner and operator of senior living communities, operating 
over 1,100 senior living communities and retirement communities in the United 
States. The organization employs MDM software to enable the clinical staff to 
safely access and update medical records from remote sites and ensure that 
sensitive patient data is always secure.42
Middleware
Middleware is software that provides messaging services that allow different 
applications to communicate and exchange data. Middleware is software that lies 
between an operating system and the applications running on it. For example, it 
can be used to transfer a request for information from a corporate customer on 
the company Web site to a traditional database on a mainframe computer and 
to return the results of that information request to the customer on the Internet.
The use of middleware to connect disparate systems has evolved into an 
approach for developing software and systems called SOA. Service-oriented 
architecture (SOA) is a software design approach based on the use of discrete 
pieces of software (modules) to provide specific functions (such as displaying a 
customer’s bill statement) as services to other applications. Each module is built 
in such a way that ensures that the service it provides can exchange informa-
tion with any other service without human interaction and without the need to 
make changes to the underlying program itself. In this manner, multiple mod-
ules can be combined to provide the complete functionality of a large, complex 
software application. Systems developed with SOA are highly flexible, as they 
allow for the addition of new modules that provide new services required to 
meet the needs of the business as they evolve and change over time.
Many organizations have taken the SOA approach to the extreme and built 
complex applications using a series of smaller specialized applications called 
microservices. Each microservice performs a single well-defined function. 
Microservices communicate to one another using agreed upon interfaces called 
application programming interfaces (API). This enables many microservices 
to be linked together in Lego fashion to create a large, complex, multifunctional 
application. A major advantage of the SOA approach is that a microservice 
built for one application may be reused in another application to perform the 
same function. Reapplication of proven microservices greatly reduces software 
development time and improves software quality.
Expedia, Inc., the U.S. travel company, employs a software development 
strategy based on microservices. Its Checkout online payment function that 
supports billions of dollars in transactions and has a huge number of features 
has been subdivided into a series of much smaller and more logical-like sets 
of microservices. The benefit of smaller, segmented applications is that Expe-
dia can update these microservices quicker or quickly add new microservices 
providing new services. Currently Expedia follows a weekly deployment cycle 
but will eventually shorten this to daily software releases allowing developers 
to try out new ideas and add new features quickly.43
Embedded System for Smart Oven
 Technology Agility
You are designing an app and a state-of-the-art “smart” oven that can be controlled 
remotely via smartphone. The app allows the user to select cooking time, tempera-
ture, start, stop, set time of day, and cancel. The oven has a display to show the 
middleware:  Software that allows 
various systems to communicate and 
exchange data.
service-oriented architecture 
(soa):  A software design approach 
based on the use of discrete pieces 
of software (modules) to provide 
specific functions as services to other 
applications.
application programming 
interfaces (api):  A set of 
programming instructions and 
standards that enable one 
microservice to access and use the 
services of another microservice.
Critical 
Thinking 
Exercise
Copyright 2021 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

## Page 170

part 2 • Technology Infrastructure
148
cooking time left, temperature, and time of day. In addition, the oven has a heating 
element for cooking the food, a door sensor to sense when the door is open, and a 
weight sensor to detect if there is an item in the oven. A beeper sounds when the 
cooking time is expired. It is possible to cook at item for a period of time at one 
temperature, stop, and then reset the temperature and cook for a while at another 
temperature. Cooking is only permitted when the door is closed and when there 
is something in the oven. Cooking can be interrupted at any time by opening the 
oven door or entering the stop command to the app. Cooking is terminated when 
the timer elapses. When the door is open a lamp inside the oven is switched on; 
when the door is closed the lamp is off.
Review Questions
1.	 What operating systems could be employed in the smartphone?
2.	 What operating systems could be employed in the embedded system to control 
the oven? Must this be a real-time operating system? Why or why not?
Critical Thinking Questions
1.	 What safety features should be designed into the software? Should these fea-
tures be programmed into the smartphone app or the software that operates 
the stove or both?
2.	 What are some creative additional features that might be designed into the 
oven?
	 Application Software
The primary function of application software is to apply the power of a com-
puter system to enable people, workgroups, and entire enterprises to solve 
problems and perform specific tasks. Millions of software applications have 
been created to perform a variety of functions on a wide range of operating 
systems and device types. The following are some of the dozens of categories 
of applications:
Business
Genealogy
Personal information manager
Communications
Language
Photography
Computer-aided design
Legal
Public safety
Desktop publishing
Library
Science
Educational
Medical
Simulation
Entertainment
Multimedia
Video
Gaming
Music
Video games
In almost any category of software, you will find many options from which 
to choose. For example, Microsoft Internet Explorer and Edge, Mozilla Firefox, 
Google Chrome, Apple Safari, and Opera are all popular Web browsers that 
enable users to surf the Web. The availability of many software options enables 
users to select the software that best meets the needs of the individual, work-
group, or enterprise. For example, the Procter & Gamble Company, a large, 
multi-national organization, chose the SAP Enterprise Resource Planning soft-
ware with its vast array of options, features, and functionality to meet its com-
plex global accounting needs. However, a small neighborhood bakery might 
decide that Intuit’s QuickBooks, an accounting software package designed for 
small businesses, meets its simple accounting needs.
Copyright 2021 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

## Page 171

Chapter 4 • Hardware and Software
149
Overview of Application Software
Proprietary software and off-the-shelf software are two important types of 
application software. The relative advantages and disadvantages of proprietary 
software and off-the-shelf software are summarized in Table 4.8. The primary 
advantages of proprietary software are that you are directly involved in the 
development of the software and so are more likely to get the features that 
are needed. You also have control over the changes made to the software to 
meet evolving needs. The disadvantages of proprietary software are that it can 
take a significant amount of time and resources to develop, in-house system 
development staff may be hard-pressed to provide the required level of ongo-
ing support and maintenance, and there is significant risk the project may 
exceed budget and schedule. The advantages of off-the-shelf software are the 
initial cost is likely less, the users can evaluate the features of the software to 
ensure that it meets their needs, and the software is likely to be of high quality. 
The disadvantages of off-the-shelf software are it may come with features not 
needed, it may lack important features necessitating expensive customization, 
and the software may not match current work processes and data standards.
Proprietary Software
Off-the-Shelf Software
Advantages
Disadvantages
Advantages
Disadvantages
You can get exactly what 
you need in terms of fea-
tures, reports, and so on.
It can take a long time 
and a significant amount 
of resources to develop 
required features.
The initial cost is lower 
because the software firm 
can spread the develop-
ment costs across many 
customers.
An organization might 
have to pay for features 
that it does not require 
and never uses.
Being involved in the 
development offers more 
control over the results.
In-house system develop-
ment staff may be hard-
pressed to provide the 
required level of ongoing 
support and maintenance 
because of pressure to 
move on to other new 
projects.
The software is likely to 
meet the basic business 
needs. Users have the 
opportunity to more fully 
analyze existing features 
and the performance 
of the package before 
purchasing.
The software might lack 
important features, thus 
requiring future modifica-
tion or customization. This 
can be very expensive, and 
because users will eventu-
ally be required to adopt 
future releases of the soft-
ware, the customization 
work might need to be 
repeated.
You can more easily mod-
ify the software and add 
features. This can help you 
to counteract an initiative 
by competitors or to meet 
new supplier or customer 
demands.
The features and perfor-
mance of software that has 
yet to be developed pres-
ents more potential risk.
The package is likely to 
be of high quality because 
many customer firms have 
tested the software and 
helped identify its bugs.
The software might not 
match current work pro-
cesses and data standards.
Ta bl e 4.8  Comparison of proprietary and off-the-shelf software
Proprietary software is one-of-a-kind software designed for a specific 
application and for an individual company, organization, or person that uses 
it. Proprietary software can give a company a competitive advantage by pro-
viding services or solving problems in a unique manner—better than methods 
used by a competitor. For example, Amazon’s proprietary e-commerce software 
employs its patented 1-Click checkout process that enables customers to com-
plete a purchase with a single click using payment credentials and shipping 
information previously stored with Amazon. This eliminates the tedious and 
proprietary software:  One-of-a-
kind software designed for a specific 
application and for an individual 
company, organization, or person that 
uses it.
Copyright 2021 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

## Page 172

part 2 • Technology Infrastructure
150
error prone step of manually entering payment card and shipping address 
information. 1-Click also enables Amazon Echo owners to complete a purchase 
with a single voice command. Other companies that wish to employ the 1-Click 
checkout process must pay a license fee to Amazon, thus the software has cre-
ated a competitive advantage. It is estimated that Amazon’s exclusive hold on 
this process has earned it billions in licensing fees.44
Off-the-shelf software is produced by software vendors to address needs 
that are common across businesses, organizations, or individuals. Literally 
thousands of small, medium, and large companies around the world employ 
off-the-shelf software from German software manufacturer SAP to support 
their routine business processes, maintain records about those processes, and 
provide extensive reporting and data analysis capabilities.
Software as a Service (SaaS)
Software as a service (SaaS) is a software distribution model under which a 
third-party provider hosts applications and makes them available to subscrib-
ers over the Internet as shown in Figure 4.12. In most cases, subscribers pay a 
monthly service charge or a per-use fee. Many business activities are supported 
by SaaS. SaaS providers include Oracle, SAP, NetSuite, Salesforce, Google, and 
many others. There are several advantages associated with the SaaS model, as 
follows:
• SaaS applications are available from any computer or any device—­
anytime, anywhere. Users simply logon to the SaaS vendor’s Web site  
and enter a logon and password to access the software and their data.
• Since the SaaS provider manages all upgrades and new releases, there 
are no software patches for customers to download or install. This frees 
up time for members of the IS organization and ensures users always 
have access to the latest most up-to-date version of the software.
• The cost associated with upgrades and new releases are lower than the 
traditional software licensing model that usually forces the user to buy 
an upgrade package and install it.
• The SaaS provider manages service levels and availability, so there’s 
no need for subscribers to add hardware, software, or communications 
capacity as the number of users increases.
off-the-shelf software:  Software 
produced by software vendors to 
address needs that are common 
across businesses, organizations, or 
individuals.
software as a service 
(saas):  A software distribution 
model under which a third-party 
provider hosts applications and makes 
them available to subscribers over the 
Internet.
Figure 4.12
Software as a service
SaaS Provider
Mobiles
Mobiles
PCs
PCs
Copyright 2021 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

## Page 173

Chapter 4 • Hardware and Software
151
Google’s Chromebook line of personal computers employ the SaaS model. 
Built by Samsung and Acer, Chromebooks include only an Internet browser—
with all software applications accessed through an Internet connection. Rather 
than installing, storing, and running software on the Chromebook, users access 
software that is stored on and delivered from a Web server. Typically, the data 
generated by the software is also stored on the Web server.
Personal Application Software
Hundreds of thousands of personal software applications are available to meet 
the needs of individuals at school, home, and work—with new applications 
released daily. New computer software under development, along with existing 
GPS technology, for example, will enable people to see 3D views of where they 
are, along with directions and 3D maps to where they would like to go. The 
features of some popular types of personal application software are summa-
rized in Table 4.9. In addition to these general-purpose programs, thousands 
of other personal computer applications perform specialized tasks that help 
users prepare their taxes, get in shape, lose weight, get medical advice, write 
wills and other legal documents, repair their computers, fix their cars, write 
music, and edit pictures and videos. This type of software, often called user 
software or personal productivity software, includes the general-purpose tools 
and programs that support individual needs.
Type of Software
Use
Example
Word processing
Create, edit, and print text documents
Apache OpenOffice Writer Apple Pages 
Corel Write Google Docs Microsoft Word 
WordPerfect
Spreadsheet
Perform statistical, financial, logical, data-
base, graphics, and date and time calcula-
tions using a wide range of built-in functions
Apache OpenOffice Calc Apple Numbers 
Google Sheets IBM Lotus 1-2-3 Microsoft 
Excel
Database
Store, manipulate, and retrieve data
Apache OpenOffice Base Microsoft Access 
IBM Lotus Approach
Graphics
Develop graphs, illustrations, drawings, and 
presentations
Adobe FreeHand Adobe Illustrator Apache 
OpenOffice Impress Microsoft PowerPoint
Personal information 
management
Helps people, groups, and organizations 
store useful information, such as a list of 
tasks to complete or a set of names and 
addresses
Google Calendar Microsoft Calendar Micro-
soft Outlook One Note
Project management
Plan, schedule, allocate, and control people 
and resources (money, time, and technology) 
needed to complete a project according to 
schedule
Microsoft Project Scitor Project Scheduler
Financial 
management
Track income and expenses and create 
reports to create and monitor budgets (some 
programs also have investment portfolio 
management features)
GnuCash Intuit Mint Intuit Quicken Money-
dance You Need a Budget (YNAB)
Desktop publishing 
(DTP)
Use with personal computers and high-­
resolution printers to create high-quality 
printed output, including text and graphics; 
various styles of pages can be laid out; art 
and text files from other programs can also 
be integrated into published pages
Adobe InDesign Apple Pages Corel Ventura 
Publisher Microsoft Publisher QuarkXpress
Table 4.9  Examples of personal application software
Copyright 2021 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

## Page 174

part 2 • Technology Infrastructure
152
Software Suites and Integrated Software Packages
A software suite is a collection of programs packaged together and sold in a 
bundle. A software suite might include a word processor, a spreadsheet pro-
gram, a database management system, a graphics program, communications and 
note-taking tools, and organizers. Some suites support the development of Web 
pages. Some offer a speech-recognition feature—so that applications in the suite 
can accept voice commands and record dictation. Software suites offer many 
advantages. The software programs within a suite have been designed to work 
similarly—after you learn the basics for one application, the other applications 
are easy to learn and use. Buying software in a bundled suite is cost effective; 
the programs usually sell for a fraction of what they would cost individually.
Table 4.10 lists the most popular general-purpose software suites for per-
sonal computer users. Most of these software suites include a spreadsheet 
program, a word processor, a database program, and graphics presentation 
software. All can exchange documents, data, and diagrams. In other words, 
you can create a spreadsheet and then cut and paste that spreadsheet into a 
document created using the word-processing application.
software suite:  A collection of 
programs packaged together and sold 
in a bundle.
Personal  
Productivity 
Function
Microsoft 
Office
Corel  
WordPerfect 
Office
Apache 
OpenOffice
Apple iWork
G Suite  
(Google Apps)
Word processing
Word
WordPerfect
Writer
Pages
Docs
Spreadsheet
Excel
Quattro Pro
Calc
Numbers
Sheets
Presentation graphics
PowerPoint
Presentations
Impress and 
Draw
Keynote
Slides
Database
Access
Paradox
Base
N/A
N/A
Table 4.10  Major components of leading software suites
Microsoft, Apple, and Google also offer Web-based productivity software 
suites that do not require the installation of any software on your device 
except a Web browser. Figure 4.13 depicts the Microsoft Office 365 Software 
as a Service. These Software as a Service cloud-based applications cost on the 
order of $10 per user per month depending on the features and the amount of 
cloud-based storage requested.
Whirlpool is a leading manufacturer and marketer of major home appli-
ances with 68,000 employees and 66 manufacturing and technology research 
centers around the world. A key challenge it faces is the need to innovate faster. 
Its CIO believes that Google Apps helps to connect its employees to think, 
share ideas, and move faster to bring products to the marketplace. This enables 
Whirlpool to unleash the talent in the company without a lot of IT support.45
Other Personal Application Software
In addition to the software already discussed, many other interesting and pow-
erful application software tools are available for personal and business use, 
as follows:
• CreditKarma Tax, TaxAct, Tax Slayer, and TurboTax are popular 
tax-preparation programs that each year saves millions of people many 
hours and even dollars in preparing their taxes.
• With just a quick online search, you can find software for creating Web 
sites, composing music, and editing photos and videos. MuseScore, for 
example, enables you to create, play back, and print sheet music.
Copyright 2021 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

## Page 175

Chapter 4 • Hardware and Software
153
• Many people use educational and reference software and software for 
entertainment, games, and leisure activities. Game-playing software is 
popular and can be very profitable for companies that develop games 
and various game accessories, including virtual avatars such as colorful 
animals, fish, and people.
• Some organizations have launched programs designed to promote phys-
ical activity by incorporating the use of active video games (e.g., Wii 
Boxing and Dance Dance Revolution) into broader physical education 
programs. Retirement communities also use video games to keep seniors 
physically active.
• Engineers, architects, and designers often use computer-assisted design 
(CAD) software to design and develop buildings, electrical systems, 
plumbing systems, and more. Autosketch, CorelCAD, and AutoCad are 
examples of CAD software.
• Other programs perform a wide array of statistical tests. Colleges and 
universities offer many courses in statistics that use this type of applica-
tion software. Two popular statistical analytics applications in the social 
sciences are SPSS and SAS.
Software companies are even developing mobile apps that are changing 
the whole dating scene. For example, SceneTap, an application for iPhones and 
Android devices, can determine the number of people at participating bars, 
pubs, or similar establishments and the ratio of males to females. The applica-
tion uses video cameras and facial-recognition software to identify males and 
females. SocialCamera, an application for Android phones, allows people to 
take a picture of someone and then search their Facebook friends for a match. 
However, many people consider facial-recognition software a potential invasion 
to privacy.
Mobile Application Software
The number of applications (apps) for smartphones and other mobile devices 
has exploded in recent years. Besides the proprietary apps that come with 
these devices, hundreds of thousands of mobile apps have been developed 
by third parties. As of April 2018, Apple’s App Store had over 2.1 million apps 
Figure 4.13
Office 365 software as a 
service
Microsoft office 365 is a web-based 
application suite that offers basic 
software suite features over the 
internet using cloud computing.
Microsoft screenshot used with permission from Microsoft Corporation
Copyright 2021 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

## Page 176

part 2 • Technology Infrastructure
154
available for iOS device users. Android users could choose from over 2.8 mil-
lion mobile apps on Google’s Play Store. The Windows store had 700,000 apps, 
and Amazon had 400,000 apps available.46
Table 4.11 lists a few mobile application categories. Many apps are free, 
whereas others range in price from 99 cents to hundreds of dollars.
Category
Description
Books and reference
Access e-books, subscribe to journals, or look up information on the Merriam-Webster or 
Wikipedia Web sites
Business and finance
Track expenses, trade stocks, and access corporate information systems
Entertainment
Access all forms of entertainment, including movies, television programs, music videos, and 
information about local night life
Games
Play a variety of games, from 2D games such as Pacman and Tetris to 3D games such as 
Need for Speed, Call of Duty, and Minecraft
Health and fitness
Track workout and fitness progress, calculate calories, and even monitor your speed and 
progress from your wirelessly connected Nike shoes
Lifestyle
Find good restaurants, make a dinner reservation, select wine for a meal, and more
Music
Find, listen to, and create music
News and weather
Access major news and weather providers, including Reuters, AP, the New York Times, and 
the Weather Channel
Photography
Organize, edit, view, and share photos taken on your phone’s camera
Productivity and utilities
Create grocery lists, practice PowerPoint presentations, work on spreadsheets, synchronize 
with PC files, and more
Social networking
Connect with others via major social networks, including Facebook, Twitter, and Instagram
Sports
Keep up with your favorite team or track your own golf scores
Travel and navigation
Use the GPS in your smartphone to get turn-by-turn directions, find interesting places to 
visit, access travel itineraries, and more
Table 4.11  Categories of mobile applications
Workgroup Application Software
Workgroup application software is designed to support teamwork, whether 
team members are in the same location or dispersed around the world. Exam-
ples of workgroup software include group-scheduling software, electronic mail, 
instant messaging, project management, and other software that enables people 
to share ideas. IBM Notes and Domino are examples of workgroup software 
from IBM. (Notes runs on the end user’s computing device, while Domino 
runs on a server and supports the end user). Web-based software is ideal for 
group use. Because documents are stored on an Internet server, anyone with 
an Internet connection can access them easily.
Personal application software can extend into the workgroup applica-
tion arena. For example, Apple, Google, and Microsoft all provide workgroup 
options of its online applications, which allow users to share documents, 
spreadsheets, presentations, calendars, and notes with other specified users 
or anyone on the Web. This sharing makes it convenient for several people 
to contribute to a document without concern for software compatibility or 
storage.
workgroup application 
software:  Software designed to 
support teamwork, whether team 
members are in the same location or 
dispersed around the world.
Copyright 2021 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

## Page 177

Chapter 4 • Hardware and Software
155
Enterprise Application Software
An enterprise application is software used to meet organization-wide busi-
ness needs and typically shares data with other enterprise applications used 
within the organization. Enterprise applications support processes in logis-
tics, manufacturing, human resources, marketing and sales, order processing, 
accounting, inventory control, customer relationship management, and other 
essential business functions. These processes require cross-functional col-
laboration with employees from multiple organizational units, and even peo-
ple outside the organization such as customers, suppliers, and government 
agencies. Enterprise applications are required to comply with an organiza-
tion’s security guidelines and may also be required to comply with standards 
defined by government agencies or industry groups to which the organiza-
tion belongs. For example, all organizations that store, process, and transmit 
cardholder data strive to meet the Payment Card Industry Data Standard 
which provides a framework of specifications, tools, measurements, and sup-
port resources to help organizations ensure the safe handling of cardholder 
information.
The total cost, ease of installation, level of training and support required, 
and the ability to integrate the software with other enterprise applications are 
the major considerations of organizations when selecting enterprise software. 
The ability to run enterprise applications on smartphones and other mobile 
devices is becoming a priority for many organizations.
Enterprise software also helps managers and workers stay connected. At one 
time, managers and workers relied on email to stay in touch with each other, but 
business collaboration and enterprise social networking tools—such as Asana, 
blueKiwi, Yammer, and Jive—are replacing traditional email and text messaging.
But how are all these systems actually developed and built? The answer is 
through the use of programming languages, some of which are discussed in 
the next section.
Programming Languages
Both system and application software are written in coding schemes called 
programming languages that provide instructions to the computer system so 
that it can perform a processing activity. Information systems professionals 
work with different programming languages, which are sets of keywords, 
commands, symbols, and rules for constructing statements that people can use 
to communicate instructions to a computer. Programming involves translating 
what a user wants to accomplish into a code that the computer can understand 
and execute. Program code is the set of instructions that signal the CPU to 
perform circuit-switching operations. In the simplest coding schemes, a line 
of code typically contains a single instruction such as, “Retrieve the data in 
memory address X.” The instruction is then decoded during the instruction 
phase of the machine cycle.
Like writing a report or a paper in English, writing a computer program 
in a programming language requires the programmer to follow a set of rules. 
Each programming language uses symbols, keywords, and commands that 
have special meanings and usage. Each language also has its own set of 
rules, called the syntax of the language. The language syntax dictates how 
the symbols, keywords, and commands should be combined into statements 
capable of conveying meaningful instructions to the CPU. Rules such as 
“statements must terminate with a semicolon,” and “variable names must 
begin with a letter,” are examples of a language’s syntax. A variable is a 
quantity that can take on different values. Program variable names such as 
SALES, PAYRATE, and TOTAL follow the sample rule shown above because 
they start with a letter, whereas variables such as %INTEREST, $TOTAL, and 
#POUNDS do not.
enterprise application:  Software 
used to meet organization-wide 
business needs and typically shares 
data with other enterprise applications 
used within the organization.
programming languages:  Sets 
of keywords, commands, symbols, 
and rules for constructing statements 
by which humans can communicate 
instructions to a computer.
Copyright 2021 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

## Page 178

part 2 • Technology Infrastructure
156
With higher-level programming languages, each statement in the language 
translates into several instructions in machine language. A special software 
program called a compiler translates the programmer’s source code into the 
machine-language instructions, which consist of binary digits. A compiler cre-
ates a two-stage process for program execution. First, the compiler translates 
the program into a machine language; second, the CPU executes that program. 
Another programming approach is to use an interpreter, which is a language 
translator that carries out the operations called for by the source code. An 
interpreter does not produce a complete machine-language program. After the 
statement executes, the machine-language statement is discarded, the process 
continues for the next statement, and so on.
Most software today is created using an integrated development environ-
ment. An integrated development environment (IDE) combines all the tools 
required for software engineering into one package. For example, the popular 
IDE Microsoft Visual Studio includes an editor that supports several visual 
programming interfaces and languages (visual programming uses a graphical 
or “visual” interface combined with text-based commands), a compiler and 
an interpreter, programming automation tools, a debugger (a tool for finding 
errors in the code), and other tools that provide convenience to the developer. 
Software developers for Google’s Android smartphone platform use the Java 
programming language along with the Android Studio with built-in Android 
Developer Tools to streamline their Android app development. This is an exam-
ple of a software development kit (SDK), which is a set of tools that enable the 
creation of software for a particular platform. They can also use special code 
libraries provided by Google for Android functionality, and they test out their 
applications in an Android Emulator.47
IDEs and SDKs have made software development easier than ever. Many 
novice coders, including some who might have never considered developing 
software, are publishing applications for popular platforms such as Facebook 
and the iPhone.
Table 4.12 lists some of the most commonly used programming languages 
and identifies how they are used.
compiler:  A special software 
