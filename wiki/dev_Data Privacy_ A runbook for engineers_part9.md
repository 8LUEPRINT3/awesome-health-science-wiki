---
title: Data Privacy_ A runbook for engineers - Part 9
source: Data Privacy_ A runbook for engineers.md
category: development
---

## Page 766

out of malevolence or incompetence or something in
between, insiders and their ability to process data could
cause privacy harm. Therefore, preparing for that risk is
critical. Table 11.12 presents a framework for evolving your
insider threat offering.
Table 11.12 Incident response management maturity evolution

## Page 767

 
        
Foundational
 
      
 
        
Mature
 
      
 
        
Advanced
 
      
 
        
System owners must 
complete incident 
response training and 
detailed assessments 
when they get access 
to a system and data 
store; there is limited 
clarity on training 
refreshes.
 
      
 
        
System owners are 
required to 
participate in 
incident response 
training and 
assessments every 
six months. The 
training and the 
assessments have 
owners who 
continually update 
them.
 
      
 
        
System owners are 
required to 
participate in 
incident response 
training and testing 
quarterly.
 
 
        
Privacy and security 
engineers help 
improve the incident 
response runbook 
based on lessons 
learned from high-
visibility and high-
impact incidents; 
training and targeted 
testing emerge from 
these insights as 
well.
 
      
 
        
 
        
 
        

## Page 768

The security and 
privacy engineers 
create bespoke 
response runbooks 
that speak to 
different services 
with the goal of 
creating a more 
universal process.
 
      
The security and 
privacy engineers 
create response 
runbooks that 
become more 
comprehensive and 
representative 
because of half-yearly 
reviews.
 
 
        
A response workflow 
automatically sends 
an alert to service 
owners and impacted 
parties with 
information and 
timelines that are 
driven by severity and 
blast radius.
 
      
The security and 
privacy engineers 
create response 
runbooks that 
become more 
comprehensive and 
representative 
because of quarterly 
reviews.
 
 
        
There are capabilities 
to disable the system 
partly or entirely in 
the event of an 
incident of a certain 
impact level or 
magnitude.
 
 
        
Engineers and 
program managers 
have access to a 
dashboard with 
updated incident 
status; there are 
templates for 
communicating 
mission-critical 
details to executives, 
regulators, and 
customers.

## Page 769

 
      
 
        
Incident prioritization 
is driven by the 
“squeaky wheel” 
approach.
 
      
 
        
Incident prioritization 
is based on IP 
address, time of day, 
or day of the week, 
business vertical that 
is impacted, 
compliance 
obligations, 
enterprise customer 
expectations, etc.
 
      
 
        
In the event of 
incidents above a 
specific prioritization 
level, the responses 
follow a defined 
checklist, including 
alerting 
administrators and 
applying stringent 
security controls.
 
      
Now that we have built an understanding of organizational
and infrastructural maturity for privacy engineering, we will
explore the skill set required in your team.
11.2 The privacy engineering domain and
skills
I have aimed this book at companies that run fast, operate
lean, and where engineers and other technical leaders often
have to multitask. Such companies don’t always have the
luxury and resources to hire privacy engineering specialists.
Even so, companies often grow enough in revenue and
scrutiny to make such hires possible and necessary. It may

## Page 770

also be that existing personnel need to absorb the work and
develop the skills to build privacy tooling.
In this section, I will provide a synopsis of the sorts of skills
that make up the privacy engineering domain. Some of
these skills can be found in one person, while others require
a level of domain specialization. The degree to which you
will require and be able to afford to hire individuals with
these skills will depend upon several factors about your
business:
Scale
Geographic reach
Regulatory scrutiny
Engineering depth
Regardless of how you staff your privacy engineering
function, it will help to have an understanding of these
skills. Cybersecurity, data protection, and privacy
engineering are novel enough that there is still plenty of
incorrect information around domain expertise. I’d rather
companies with finite resources make more informed
staffing decisions. With that background, let’s do a quick
runthrough of privacy-related skills.
PRIVACY SOFTWARE ENGINEERS
Privacy software engineers are engineers who may not have
privacy domain expertise—for example, cryptography,
anonymization, etc.—but who build privacy-preserving
tooling. Their tools could detect data using crawlers that

## Page 771

deploy regular expressions, enforce access control using
behavioral analytics, delete data while maintaining service
continuity, etc. These engineers understand data, system
architecture, data warehousing, and query efficiency. They
contribute to the attainment of privacy goals and can build
privacy skills gradually. This book is primarily aimed at
existing internal engineers with this skill set who can go on
and become your privacy engineers.
COMPLIANCE SPECIALISTS
It is helpful to understand the difference between privacy
engineering and compliance. Compliance is the act of
ensuring documented due diligence—showing that you
followed known rules. Compliance is reactive in that it is
aimed at satisfying rules borne of previous failures.
Compliance specialists are often not engineers, but experts
at mapping rules to engineering outcomes, performing gap
analysis, and helping drive prioritization for the gaps
creating most risk. Just as an actuarial analyst could
provide insurance rates based on risk, compliance
specialists can recommend the next course of action based
on a company’s need to meet a specific standard.
PRIVACY ANALYSTS
Chapter 6 and its focus on privacy reviews was aimed at
privacy analysts. These privacy experts should look at your
products and features (or preferably, the designs for these
features at an early stage), ask questions, identify risks,
and help you redesign in a privacy-safe fashion before you

## Page 772

make irreversible technical decisions. For example, rather
than making a copy of data and encrypting it for limited
access, a privacy analyst could help drive access from a
centralized source. This would allow for consistency, reduce
duplication, and cut down on the work involved to manage
encryption keys and access logs. These experts don’t just
look at technical artifacts on their own, but at how human
ingenuity or malfeasance could lead to unpredictable
outcomes. They are privacy engineers by trade.
PRIVACY PRODUCT MANAGERS
Privacy product managers have two key responsibilities.
First, they design and finalize requirements for privacy-
specific products, like deletion, data extraction, etc. These
designs are used by privacy software engineers to then
build the products, which are then used by the rest of the
company. This way, you don’t end up with bespoke privacy
tooling on a team-by-team basis in the company. Second,
these product managers should also build privacy features
that are user facing, like consent capture tools, privacy
settings, dashboards, etc.
Privacy product managers should also try to build privacy
features into the company’s core products that aim to drive
engagement and revenue. In so doing, they would be
consultants to other product managers whose remit focuses
on building features that drive engagement and revenue.
That way, the company’s privacy maturity is not dependent
solely on the adoption of central privacy tools.

## Page 773

DATA ANALYSTS
Data analysts have a deep background in mathematics and
data querying. They can help provide data-driven guidance;
quantifying re-identification risk and k-anonymity, which
you saw in chapter 5, are examples. Well-resourced
companies can hire mathematicians and then SQL analysts
to provide support. More nimble companies hire
mathematicians and then teach them how to query
databases; this approach scales better, since it helps ensure
that an understanding of the data as well as the ability to
retrieve it will reside in the same individual.
PRIVACY INFRASTRUCTURE SPECIALISTS
All the tooling we have discussed in this book needs to
account for scale and the segmentation and distribution of
the tech stack. Implementing deletion at scale requires
knowledge about data warehousing, caches, availability
zones, and adjusting all these for business continuity.
Allowing for scale will require that privacy infrastructure
specialists focus on validation and verification at scale as
well. In my opinion, this role can repurpose existing
systems architects and does not require privacy domain
knowledge, although such expertise can help build
credibility with stakeholders ranging from privacy attorneys
to the rest of the engineers who may have zero privacy
expertise. Given the reality of cloud-based computing and
trans-national data transfers, this role is critical for growth
companies.

## Page 774

PRIVACY UX DESIGNERS
Privacy UX designers act as user advocates, so they will
need at least some formal privacy expertise. Their remit
ranges from
Writing copy for public-facing privacy tools that
needs to account for regulatory needs yet must be
clear enough for the layperson to understand
Deploying quantitative and qualitative methods to
understand how users (internal and external)
could react with privacy products
Advising privacy product managers on why
adoption of privacy products may differ from
expectations based on observed user behavior
patterns
For companies that operate with diverse populations or deal
with very personal data, this skill is vital.
PRIVACY ARCHITECTS
When I am not leading global privacy teams at major
companies, this is the domain I occupy at companies.
Privacy architects have aggregated and accumulated
expertise in privacy regulation, public policy, software
development, and system architecture. Their role is to drive
internal alignment around privacy and security standards.
They need to thread the needle between writing policy that
is aspirational and capturing the status quo on data
handling at a company. The former requires privacy and

## Page 775

regulatory expertise, and the latter needs engineering and
architectural chops. This role requires the ability to manage
relationships, build bridges, and create privacy champions
out of skeptical executives. Among other things, this book
aspires to help companies create homegrown privacy
architects.
Finally, let’s take a look at the larger regulatory climate that
privacy operates in.
11.3 Privacy and the regulatory climate
I have long believed that regulation is downstream from
popular sentiment. It is no accident that laws like the GDPR,
CCPA, and others have arrived just as resentment toward
the tech sector has grown. Simultaneously, it is no accident
that institutional distrust of governments and businesses
has led to populist movements worldwide.
What does this have to do with engineers, whose aspiration
in life is to build products and solve problems? Engineers
have had to live downstream from decision makers for far
too long. In the days of waterfall development, they lived
downstream from product management and sales and were
often glorified order-takers. Today, in a more agile and
bottom-up phase, they find themselves downstream from
privacy regulation, which re-examines decisions that were
made under an environment that was vastly different.

## Page 776

This book is aimed at solving a part of that problem; it will
help engineers deploy a “build in” model for privacy rather
than a “bolt on” model. The former embeds privacy into the
design, process, and architecture of the company. The
latter, by contrast, tries to close gaps as they emerge, with
containment as its ceiling. However, engineers need to form
alliances outside the company with industry influencers,
privacy commentators, media, and others so as to make
sure that privacy regulations are meaningful.
In my opinion, privacy regulations have three key
objectives:
Hold bad actors accountable when they misuse
data.
Provide customers and users with meaningful
protections.
Create quantifiable expectations that companies
can meet.
To that end, I want to provide two examples of the macro-
political picture to help you understand why the engineer’s
already difficult job regarding privacy is about to get harder.
In 2006, then Chair of the Senate Commerce Committee,
Senator Ted Stevens, was expressing his thoughts on Net
Neutrality. In part of his speech, he said the following:
There’s one company now that you can sign up [with] and get a movie
delivered to your house. Daily. By delivery service [...] This service is now
going to go through the Internet. And what you do now is go to a place and
order your movie, and guess what? You can order 10 of them delivered to you
and the delivery charge is free, right?

## Page 777

10 movies streaming across that Internet. And what happens to your own
personal Internet? Just the other day an Internet was sent by my staff at
10:00 in the morning on Friday—I got it yesterday. Why? Because it got
tangled up with all these things going on the Internet commercially.
And here we have this one situation where enormous entities want to use the
Internet for their purpose to save money for doing what they’re doing now.
They use FedEx, they use deliver services, they use the mail. They deliver in
other ways, but they want to deliver vast amounts of information over the
Internet.
And again, the Internet is not something that you just dump something on,
it’s not a big truck. It’s a series of tubes. And if you don’t understand, those
tubes can be filled, and if they’re filled, when you put your message in, it gets
in line it’s going to be delayed by anyone that puts into that tube enormous
amounts of material.1
Sen. Stevens was, in all likelihood, discussing the upcoming
business model for Netflix. The senator’s remarks have
been widely mocked on the internet for years due to the
errors they contain. For example,
He uses the words “email” and “internet”
interchangeably.
There was no evidence to suggest that video
streaming led to delayed email in this specific
case.
That said, a report from Canadian networking equipment
company Sandvine found that more than a third of all North
American internet was generated by Netflix alone during
peak hours.2 Even though the senator’s statement and the
Sandvine findings were almost a decade apart, there have
been other examples that suggest that even as the tech

## Page 778

industry is impacting the world at levels not seen before,
the sophistication and understanding of political leaders
with regulatory power has not made much progress.
This poses a critical problem for engineers and the tech
industry. Regulations are being pushed by advocates,
including many in government, whose strong point of view
about online commerce is unaccompanied by an equal
immersion in the technical details. Engineers are always
expected to write code, deliver products, and not violate
such complicated laws; the lack of connection between the
regulatory apparatus in government and the productivity
apparatus in industry hurts the very customers the laws are
intended to protect.
At this point, you might wonder if things have changed in
the 15 years since the Stevens speech. In early 2018, as
the U.S. Senate held hearings on the Cambridge Analytica
episode, Facebook CEO Mark Zuckerberg had an exchange
with then Senator Orrin Hatch. Sen. Hatch asked
Zuckerberg if Facebook was still committed to offering its
service for free. The transcript of that exchange is as
follows:
ZUCKERBERG: Senator, yes. There will always be a version of Facebook that
is free. It is our mission to try to help connect everyone around the world and
to bring the world closer together.
In order to do that, we believe that we need to offer a service that everyone
can afford, and we’re committed to doing that.
HATCH: Well, if so, how do you sustain a business model in which users don’t
pay for your service?

## Page 779

ZUCKERBERG: Senator, we run ads.
HATCH: I see. That’s great.3
The fact that one of the most experienced sitting senators
did not do his homework on Facebook’s business model
prior to a televised hearing was disconcerting. The video of
this exchange has prompted mockery among many
engineers around politicians’ lack of technical knowledge.4
Many engineers in online forums use this video as an
example of their superiority over those who are far less tech
savvy.
My reaction is the exact opposite. If someone with more
power than you knows less than you about a critical
domain, that problem is yours to fix. Engineers can no
longer assume that functional fidelity, engagement, and
adoption are the sole metrics for success. To the extent that
data is the fuel of the information superhighway, regulators
will control the speed limits and enforce detours. The lack of
technical sophistication of these regulators could lead to
unhelpful laws that stifle innovation, hurt competition, and
fail to protect consumers.
I cannot sign off without another recollection, one from my
own memory. I was once at a four-person panel that
featured two cybersecurity industry experts (me and
another person) and two individuals who advised
governments on privacy law. The exchange was mostly off
the record, but during a portion of the event open to the
public, the following exchange ensued:

## Page 780

GOVERNMENT EXPERT: We need more privacy laws because the tech
industry is out of control.
BHAJARIA: Well, we have two laws already on the books with wide
applicability and open to emulation. Would it not be better to study their
effectiveness and use them as a baseline? That way we know the laws are
producing intended protections for users.
GOVERNMENT EXPERT: There are not very many good actors in industry to
partner with, and besides, why not have 50 privacy laws in 50 states? The
cream rises to the top, and we will have a superset of protections that way.
The exchange returns to me every time I argue for privacy
budgets and projects to be prioritized. The lack of technical
sophistication among privacy regulators in government is
matched only by their desire to regulate companies that
monetize user data.
This book will help engineers and companies front-load
privacy engineering into their businesses. This is critical,
since emerging and growing companies have two choices.
They could continue business as usual and surrender their
future to someone who will gradually regulate them into the
ground. Unlike the big tech giants, newer companies lack
endurance to deal with punitive laws.
They could, however, make a second choice. This book lays
out the engineering tools companies can build for privacy,
but it is just as critical that engineers engage more widely
to educate and influence. The future of data protection will
depend on the healthy tension as well as collaboration
between innovation and regulation. Both need to inform

## Page 781

rather than cancel each other. This will be the subject of my
future endeavors and authorship.
For now, I want to close with a word of advice. I hope the
engineers and other technologists who are this book’s
primary audience will use this book aggressively as a
starting point. Use it as a framework to build out privacy
technology into products, tools, and processes. You have a
baseline now available that you can customize for your
technical implementations.
I also want to reach out to company executives who are
often disconnected from the details and often surprised by
suboptimal privacy outcomes. While you may not
understand every detail, this book is aimed at conveying
the risk and scope related to privacy, but also the
efficiencies and benefits as well. This book is aimed at
helping you, as a leader and decision maker, to prioritize
and drive maturity within your businesses.
Finally, members of the media and regulatory apparatus
have focused on privacy with increasing intensity in recent
times. This book should help you understand the
complexities and interdependencies when it comes to
privacy engineering. The media often act as thermometers,
in that their coverage provides a sense of how well or poorly
things are going. Regulators then act like thermostats in
that they turn up or down the heat, depending on customer
impact and sentiment. Things often move quickly amid the
flurry of news without appropriate context, and this book is
aimed at healing that. Technical journalists, lawmakers, and

## Page 782

regulators should also benefit from this book and be
enabled to fulfill your roles more prudently.
Whatever your background and the angle with which you
have approached this book, thank you for coming on this
journey with me. It is my hope that we will see a future in
which privacy is increasingly built (engineered!) into all that
we do, to the benefit of users and in turn the businesses
who prove to have their users’ interests in mind. Good luck!
Summary
Companies need to gradually and continuously
mature their privacy engineering systems and
tools.
Given the wide scope of privacy, there are several
dimensions and choices for companies to track
program maturity.
Companies also need to understand the diversity
of privacy engineering skills, all of which come
with varying levels of criticality.
The disconnect and knowledge imbalance between
the tech industry and the regulatory authorities is
the next risk/challenge for government and
industry to solve.
1 Evan Dashevsky, “A Remembrance and Defense of Ted Stevens’ ‘Series of Tubes’,” PC
Magazine, June 5, 2014, http://mng.bz/BxDg.
2 Stephanie Mlot, “Netflix Dominates Web Traffic as Cord Cutters Gobble Data,” PC
Magazine, May 14, 2014, http://mng.bz/doPX.

## Page 783

3 “Transcript of Mark Zuckerberg’s Senate hearing,” The Washington Post, April 10, 2018,
http://mng.bz/raBZ.
4 “Senator Asks How Facebook Remains Free, Mark Zuckerberg Smirks: ‘We Run Ads’,”
YouTube, http://mng.bz/VlqO.

## Page 784

index
A
access
closing access-control gaps 316–320
control as privacy tool 137–138
identity and access management 330–331
management 78–82
examples 79–82
options 78–79
perimeter access 295–316
authorization best practices 305–313
continuous monitoring of accounts and credentials 313–314
MongoDB security weaknesses 302–305
remote work and privacy risk 314–316
Target breach 295–302
real-time 196–197
relationship between precision and 143–146
accounts
continuous monitoring of 313–314
data, account-level 205–210
registering services and data fields for deletion 207–209
scheduling data deletion 209–210
deletion 202–204
overview 202–203
scaling 203–205
accuracy 185, 207
Act, in Plan, Do, Check, Act model 89
advertising
online 128–132
privacy in 132–133
API
checking consent status 264–266
processing multiple disclosures 271–274
registering with consents service 274–275

## Page 785

retrieving disclosures 266–268
updating consent status for disclosure 268–270
API gateway 196
API type 208
archival data 142
archival data storage
data storage growing from collection to 199–200
overview 197–198
asset management 326–327
attack surface 284–295
enterprise risk model for security and privacy 289–295
automated detection for attack surface management 289–290
defense in depth 293
security risk management implementation 290–292
service segmentation 292–293
supportability 294–295
managing 284–285
testing causing security and privacy risks 285–289
flexible testing with expanded attack surface 287–288
potential mitigations explored and abandoned 288
takeaway for engineers and technologists 288–289
using production data in test 286–287
audit trail 229
authorization 80, 305
enforcing separation of authorization policy from code 306–307
making secure, service-based, and easy to integrate 307–309
verifying strength of data links and validating authenticity of identity 309–313
automation 205–210
registering services and data fields for deletion 207–209
scheduling data deletion 209–210
availability 207
B
baseline, data inventory 102–103
BigID 28–30
building program
overview 58

## Page 786

privacy-first culture 58–60
businesses
CMP, importantance of 252–253
data and growth strategy 45–46
data inventory gaining insights about 121–122
needing data sharing 126–133
online advertising 128–132
privacy in advertising 132–133
Taxicab companies 127–128
privacy process unlocking opportunities 18–20
C
CalECPA (California Electronic Communications Privacy Act) 223
Cambridge Analytica 156–157
Capability Maturity Model (CMM) 75
capacity 207
CCPA (California Consumer Privacy Act) 24, 218
Check, in Plan, Do, Check, Act model 89
closing access-control gaps 316–320
cloud-based data protection 333
cluster analysis 28
CMM (Capability Maturity Model) 75
CMP (consent management platform) 281
capabilities in 276–277
consent code 263–276
API to check consent status 264–266
API to process multiple disclosures 271–274
API to register with consents service 274–275
API to retrieve disclosures 266–268
API to update consent status for disclosure 268–270
definitions for consents service 275–276
data schema model for 256–263
database schemas 257–263
entity relationships 256–257
importantance of 248–253
businesses and 252–253
privacy-related regulation 249–251

## Page 787

tech industry changes 251–252
integrating into product workflow 278–281
overview 253–255
Collibra 30–31
combine/harvester module 229
compliance mapping 29, 261
compliance requirements 291
compliance specialists 340
consent code, CMP 263–276
API to check consent status 264–266
API to process multiple disclosures 271–274
API to register with consents service 274–275
API to retrieve disclosures 266–268
API to update consent status for disclosure 268–270
definitions for consents service 275–276
consultation, DPIA 168
contact tracing 189–191
COVID 23–24
credentials 313–314
cross-functional stakeholders 85–87
cryptographic function, two-way 151
CSPRNG (cryptographically secure pseudorandom number generator) 149
cuboids 230–232
culture, privacy-first 58–60
customers
data classification and 64–65
Target breach 295–302
compromising third-party vendor 297–298
exploiting web application vulnerability 298
gaining and maintaining access to customer data 299
propagating access to customer data 299–300
recon to detect network vulnerabilities 297
searching for customer data 298–299
sending stolen data outside company's network 300–302
stealing customer personal data and credit card data 300
cyclical process 24–26

## Page 788

D
dashboards
building 226–227
internal-facing screens 236–244
data
business growth strategy and 45–46
describing in DPIA 167–168
flow of into and within company 7–9
governance
necessity of data classification 66–67
unstructured data and 74–75
machine learning (ML) and 185–186
systems and policy enforcement 41
data analysts 341
data anonymization
mapping universal IDs to internal IDs 146–148
relationship between precision and access 143–146
relationship between precision and retention 142–143
data classification 7–93
access management 78–82
examples 79–82
options 78–79
customer context and 64–65
example of 90–92
necessity of 65–78
aligning priorities 67–73
data governance 66–67
industry benchmarking 73
organizational maturity 75–78
unstructured data and governance 74–75
privacy laws 82–84
data classification as abstraction of 82–83
resolving tension between interpretations of 83–84
process of 84–90
formalizing and refactoring 87–88
Microsoft template 88–90
working with cross-functional stakeholders 85–87

## Page 789

data collection
modern data collection architecture 194–200
archival data storage 197–198
data storage growing from collection to archival 199–200
data storage locations 198–199
distributed architecture and microservices 195–196
real-time data storage and access 196–197
data deletion 7, 120–215
account deletion 202–204
overview 202–203
scaling 203–205
account-level data 205–210
registering services and data fields for deletion 207–209
scheduling data deletion 209–210
data collection architecture 201–202
modern data collection architecture 194–200
archival data storage 197–198
data storage growing from collection to archival 199–200
data storage locations 198–199
distributed architecture and microservices 195–196
real-time data storage and access 196–197
ownership of 213–215
reasons for 193–194
sensitive data deletion 210–213
data inventory 7–124
creating baseline 102–103
defined 95–97
machine-readable tags 97–101
defined 97–98
example of 98–101
metadata 111–114
definition process 111–112
discovery process 113–114
stages of maturity 117–122
level 1 117–119
level 2 119
level 3 120–122

## Page 790

starting process of 114–117
difficulty, reasons for 114–115
early stages 115–117
successful process of 122–124
objective success metrics 122
subjective success metrics 123–124
technical architecture 111
architectural capabilities 106–108
structured and unstructured data 103–106
workflow 108–111
data lakes 197
data pipeline 229
data protection 37
data protection authorities (DPAs) 17
data schema model, CMP 256–263
database schemas 257 &#8211; 263
Disclosure Version table 259–260
Feature table 258–259
Locale Copy table 262
Locale Territory table 262–263
User Consent table 260–262
entity relationships 256–257
data sharing 158
companies needing, reasons for 126–133
online advertising 128–132
privacy in advertising 132–133
Taxicab companies 127–128
measuring privacy impact 151–156
k-anonymity 152
k-anonymity with imprecise data 152–153
k-anonymity with industry best practice 154–155
k-anonymity with precise data 153–154
l-diversity 155–156
obfuscation techniques for privacy-safe data sharing 140–148
data anonymization 142–148
US national security 140–141
privacy harms 156–158

## Page 791

Facebook and Cambridge Analytica 156–157
sharing data and weaknesses 158
safely sharing 134–139
protecting data at rest 137–139
protecting data in motion 135–136
tracking President Trump 134–135
sharing internal IDs with third parties 148–151
minimal session 149
recovering pseudonymized values 150–151
session spanning datasets 150
single session per dataset 149–150
technical privacy review 184
Data Subject Access Requests see DSARs (Data Subject Access Requests) in ch01,
in ch02, in ch04, in ch09
data warehouses 197
DataGrail 30–31
DELETE endpoint 208
deletion and retention policy 194
demand-side platform (DSP) 128
Dennedy, Michelle Finneran 66
detection 336–338
insider threat 337–338
threat intelligence 336–337
disclosure 256–257
Disclosure Version table 259–260
disclosure_uuid 260
disclosure_version_uuid 259
disclosures
processing multiple 271–274
retrieving 266–268
updating consent status for 268–270
distributed services
automation and scaling for 205–210
microservices 195–196
registering services and data fields for deletion 207–209
scheduling data deletion 209–210
Do, in Plan, Do, Check, Act model 89

## Page 792

downloading personal data 120
DPAs (data protection authorities) 17
DPIA (data protection impact assessment) 165–170
conduct risk assessment 169
consultation 168
describing data processing 167–168
describing relationship with user 168
identifying need for 166–167
identifying risk mitigation measures 169–170
DSAR batch request module 229
DSAR template module 228
DSARs (Data Subject Access Requests) 29, 37, 95, 120–244, 248
data structures 228–236
components 228–230
cuboids 230–232
data sources for templates 234–236
templates 232–234
internal-facing screens and dashboards 236–244
request fulfillment process 221–224
rights given to users 220–221
setting up 224–227
building status dashboard 226–227
steps in creating 224–226
DSP (demand-side platform) 128
E
early-stage efficiency 11–13
Edge API 196
encryption 138–139
engagement apps 187–189
engineers 32–34
enterprise risk model 289–295
automated detection for attack surface management 289–290
defense in depth 293
security risk management implementation 290–292
service segmentation 292–293
supportability 294–295

## Page 793

entity relationship paradigm 256
Equifax 47–48
equity 185
ERDs (engineering requirement documents) 178–184
ETL (extract, transform, load) 41, 202
EU (European Commission)
Facebook 2014 policy changes 17–18
fine for WhatsApp data misrepresentations 15–16
European General Data Protection Regulation (GDPR) 24, 51, 218, 249
exporting user data 244
F
Facebook 17–18, 156–157
Feature table 258–259
feature_name 259
featureUuid field 267
fines, privacy 9–11
formalizing data classification 87–88
G
Gamesbuster case study 11–13
GDPR (European General Data Protection Regulation) 24, 51, 218, 249
GET_TEST_USER endpoint 208
getCompliance calls 271
governance 327–328
H
Hern, Alex 31
holds, legal 199
horizontal access control 317
I
IAB (Interactive Advertising Bureau) 254
IAM (Identity and Access Management) 59, 304
IAPP (International Association of Privacy Professionals) 95, 166
identification 326–329
asset management 326–327
governance 327–328

## Page 794

risk management 328–329
identity and access management 330–331
identity graph 132
IDOR (insecure direct object reference) 316–320
overview 316–319
testing and mitigation 319–320
incident response management 339
industry benchmarking 73
Informatica 30–31
infrastructure-based data protection 334–336
innovation process example 41–45
insider threat 337–338
Interactive Advertising Bureau (IAB) 254
internal IDs 146–151
minimal session 149
recovering pseudonymized values 150–151
mapping table 151
two-way cryptographic function 151
session spanning datasets 150
single session per dataset 149–150
internal-facing screens 236–244
International Association of Privacy Professionals (IAPP) 95, 166
investigations, privacy 13–18
EU fine for WhatsApp data misrepresentations 15–16
Facebook 2014 policy changes 17–18
privacy process unlocking business opportunities 18–20
WhatsApp fine from Italian antitrust regulator 16
IP address 186
IS_DELETED endpoint 209
ISMS (Information Security Management System) 19
ISO 9001 standard 75
Italian antitrust regulator 16
J
JSON blobs 12
judicial investigations 38
K

## Page 795

k-anonymity 152, 341
with imprecise data 152–153
with industry best practice 154–155
with precise data 153–154
key insight 15, 17
KMS (key management systems) 40
KPIs (key performance indicators) 117
KRIs (Key Risk Indicators) 336
L
l-diversity 155–156
LabCorp and Quest Diagnostics 50–51
latency 185, 207
legal privacy reviews
process of 170–172
technical privacy review vs. 174–176
levels of data inventory maturity 117–122
list default DSAR templates 229
Locale Copy table 262
Locale Territory table 262–263
locations, data storage 198–199
lockdown model 78
M
machine-learning (ML) models 27, 102, 185–186
machine-readable tags 97–101
defined 97–98
example of 98–101
mapping IDs 146–148
mapping table 151
masks 189–191
maturity model for privacy engineering 324–339
cloud-based data protection 333
detection 336–338
insider threat 337–338
threat intelligence 336–337
identification 326–329
asset management 326–327

## Page 796

governance 327–328
risk management 328–329
infrastructure-based data protection 334–336
protection 329–336
identity and access management 330–331
vulnerability management 331–332
remediation 338–339
software development security and privacy 332–333
maturity, data inventory stages of 117–122
level 1 117–119
level 2 119
level 3 120–122
data deletion 120–121
downloading personal data and DSARs 120
gaining insights about business 121–122
MDM (mobile device management) 335
mental model, privacy 20–22
messaging apps 187–189
metadata 111–114
definition process 111–112
discovery process 113–114
MFA (multifactor authentication) 137, 295, 301, 314
microservices 195–196
Microsoft template 88–90
ML (machine-learning) models 27, 102, 185–186
mobile device management (MDM) 335
modern data collection architecture 194–200
archival data storage 197–198
data storage growing from collection to archival 199–200
data storage locations 198–199
distributed architecture and microservices 195–196
real-time data storage and access 196–197
MongoDB security weaknesses 302–305
mop_id, mop_token_id payment object 211
mop_token_id token 211
motion, data in 135–136
multifactor authentication (MFA) 137, 295, 301, 314

## Page 797

N
naturalization 53–54
O
obfuscation techniques for privacy-safe data sharing 140–148
data anonymization
mapping universal IDs to internal IDs 146–148
relationship between precision and access 143–146
relationship between precision and retention relationship between precision and
retention 142–143
US national security 140–141
objective success metrics 122
objects, IDOR 316
OneTrust 28–30
online advertising 128–132
operational data 142
OPM (Office of Personnel Management) breach 48–50
organizational maturity 75–78
ownership, data deletion 213–215
P
Pass-the-Hash (PtH) technique 299
perimeter access 295–316
authorization best practices 305–313
enforcing separation of authorization policy from code 306–307
secure, service-based, and easy to integrate 307–309
verifying strength of data links and validating authenticity of identity 309–313
continuous monitoring of accounts and credentials 313–314
MongoDB security weaknesses 302–305
remote work and privacy risk 314–316
Target breach 295–302
compromising third-party vendor 297–298
exploiting web application vulnerability 298
gaining and maintaining access to customer data 299
propagating access to customer data 299–300
recon to detect network vulnerabilities 297
searching for customer data 298–299
sending stolen data outside company's network 300–302

## Page 798

stealing customer personal data and credit card data 300
personal data
defining 82
downloading 120
PIA (privacy impact assessment) 164–165
PII (Personally Identifiable Information) 82, 164
Plan, Do, Check, Act model 88
platform solutions 28–30
point solutions 30–31
policy enforcement 41
pre-aggregation 186
precision
relationship between access and 143–146
relationship between retention and 142–143
prioritization 67–73
data protection 67–70
data segmentation 70–71
privacy 9–60
building program
overview 58
privacy-first culture 58–60
data
business growth strategy and 45–46
systems and policy enforcement 41
data sharing
harms of 156–158
measuring impact of 151–156
defined 4–7
difficulties with 36–37
early-stage efficiency 11–13
expectations for privacy engineers 37–39
fines 9–11
innovation process example 41–45
investigations 13–18
laws 82–84
data classification as abstraction of 82–83
resolving tension between interpretations of 83–84

## Page 799

machine learning and 186
mental model 20–22
regulations 51–53
CMP, importantance of 249–251
impacting product and their users 51–52
preparing for changing privacy law 53
user and 53–55
naturalization 53–54
privacy concerns 54–55
violations, examples of 46–51
Equifax 47–48
LabCorp and Quest Diagnostics 50–51
Office of Personnel Management (OPM) breach 48–50
privacy analysts 340–341
privacy architects 342
privacy by design 176
Privacy Engineer’s Manifesto, The (Dennedy) 6, 66
privacy engineering 34, 346
at macro level, affecting business 22–26
regulations and cyclical process 24–26
safety and COVID 23–24
data flows into and within company 7–9
domain and skills 339–342
compliance specialists 340
data analysts 341
privacy analysts 340–341
privacy architects 342
privacy infrastructure specialists 341
privacy product managers 341
privacy software engineers 340
privacy UX designers 341–342
engineers 32–34, 37–39
maturity model for 324–339
cloud-based data protection 333
detection 336–338
identification 326–329
infrastructure-based data protection 334–336

## Page 800

protection 329–336
remediation 338–339
software development security and privacy 332–333
privacy and regulatory climate 342–346
tooling 26–32
privacy engineers 32–34, 37–39
privacy harm 4
privacy infrastructure specialists 341
privacy product managers 341
privacy reviews 191
data protection impact assessment (DPIA) 165–170
conduct risk assessment 169
consultation 168
describing data processing 167–168
describing relationship with user 168
identifying need for 166–167
identifying risk mitigation measures 169–170
legal privacy review 170–172
privacy impact assessment (PIA) 164–165
technical privacy review 172–176
integrating into innovation pipeline 177–184
legal privacy reviews vs. 174–176
samples of 187–191
scaling process 184–186
timing and scope 172–173
privacy software engineers 340
privacy UX designers 341–342
Privicera 30–31
PRNG (pseudorandom number generator) 149
products, regulations impacting 51–52
protection
data at rest 137–139
access control as privacy tool 137–138
encryption as privacy tool 138–139
data in motion 135–136
maturity model for privacy engineering 329–336
identity and access management 330–331

## Page 801

vulnerability management 331–332
prioritizing 67–70
pseudonymization
recovering pseudonymized values 150–151
mapping table 151
two-way cryptographic function 151
suggested techniques
minimal session 149
session spanning datasets 150
single session per dataset 149–150
PtH (Pass-the-Hash) technique 299
publisher, defined 128
R
RDP (Windows Remote Desktop) 299
real-time data storage and access 196–197
recovering pseudonymized values 150–151
mapping table 151
two-way cryptographic function 151
redundancy 196
refactoring data classification 87–88
registering for deletion 207–209
regulations 24–26, 51–53
climate of 342–346
CMP, importantance of 249–251
impacting product and their users 51–52
preparing for changing privacy law 53
remediation 338–339
remote work 314–316
rest, data at 137–139
access control as privacy tool 137–138
encryption as privacy tool 138–139
retention, relationship between precision and 142–143
right to know 37
risks
DPIA (data protection impact assessment)
conducting risk assessment 169

## Page 802

identifying risk mitigation measures 169–170
management 328–329
security vulnerabilities 321
closing access-control gaps 316–320
managing perimeter access 295–316
reducing attack surface 284–295
third-party privacy tools 31–32
S
safety
data sharing and 134–139
protecting data at rest 137–139
protecting data in motion 135–136
tracking President Trump 134–135
privacy and 23–24
SailPoint 30–31
scheduling data deletion 209–210
security vulnerabilities 321
closing access-control gaps 316–320
insecure direct object reference (IDOR) testing and mitigation 319–320
insecure direct object reference (IDOR) vulnerability 316–319
managing perimeter access 295–316
authorization best practices 305–313
continuous monitoring of accounts and credentials 313–314
MongoDB security weaknesses 302–305
remote work and privacy risk 314–316
Target breach 295–302
reducing attack surface 284–295
enterprise risk model for security and privacy 289–295
managing attack surface 284–285
testing causing security and privacy risks 285–289
segmentation
data 70–71
service 292–293
sensitive data deletion 210–213
service and risk affinity 291
service level agreements (SLAs) 206

## Page 803

service residency 291
sessions
minimal session 149
single session per dataset 149–150
spanning datasets 150
skills 339–342
compliance specialists 340
data analysts 341
privacy analysts 340–341
privacy architects 342
privacy infrastructure specialists 341
privacy product managers 341
privacy software engineers 340
privacy UX designers 341–342
SLAs (service level agreements) 206
software development security and privacy 332–333
SSPs (supply-side platforms) 128
stakeholders, cross-functional 85–87
subjective success metrics 123–124
T
Target breach 295–302
compromising third-party vendor 297–298
exploiting web application vulnerability 298
gaining and maintaining access to customer data 299
propagating access to customer data 299–300
recon to detect network vulnerabilities 297
searching for customer data 298–299
sending stolen data outside company's network 300–302
stealing customer personal data and credit card data 300
Taxicab companies 127–128
TCF (IAB Transparency and Consent Framework) 254
teach, train, and trust culture 58
tech industry 251–252
techlash 33, 64
technical architecture, data inventory 111
architectural capabilities 106–108

## Page 804

structured and unstructured data 103–106
workflow 108–111
technical privacy reviews 172–176
integrating into innovation pipeline 177–184
engineering requirement documents (ERDs) 178–184
fitting into workflow 177–178
legal privacy reviews vs. 174–176
samples of 187–191
masks and contact tracing 189–191
messaging apps and engagement apps 187–189
scaling process 184–186
data sharing 184
machine-learning (ML) models 185–186
timing and scope 172–173
templates, DSAR
data sources for 234–236
overview 232–234
testing 285–289
flexible testing with expanded attack surface 287–288
potential mitigations explored and abandoned 288
takeaway for engineers and technologists 288–289
using production data in test 286–287
third-party privacy tools 28–31
platform solutions 28–30
point solutions 30–31
risks in buying 31–32
threat intelligence 336–337
timing, technical privacy review 172–173
tooling 26–32
third-party privacy tools 28–31
platform solutions 28–30
point solutions 30–31
risks in buying 31–32
training model 78
Trump, Donald 134–135
trust model 78
trust-seeking culture 58

## Page 805

two-way cryptographic function 151
U
universal IDs 146–148
unlinking 213
unstructured data 74–75
US national security 140–141
User Consent table 260–262
UserConsent object 271
users 53–55
describing relationship with 168
DSARs rights for 220–221
exporting user data 244
naturalization 53–54
privacy concerns 54–55
regulations impacting 51–52
users object 317
V
vertical access control 317
violations of privacy 46–51
Equifax 47–48
LabCorp and Quest Diagnostics 50–51
Office of Personnel Management (OPM) breach 48–50
vulnerability management 331–332
W
WhatsApp
EU fine for data misrepresentations 15–16
fine from Italian antitrust regulator 16
workflow automation 30

