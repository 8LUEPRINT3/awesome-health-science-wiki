---
title: Data Privacy_ A runbook for engineers - Part 3
source: Data Privacy_ A runbook for engineers.md
category: development
---

industry—what I like to call the “our competitors do it
already” argument.
The engineering team may propose a solution that looks like
table 3.4, where fields that could uniquely identify an
individual—their names and emails—are obfuscated using a
technique called hashing. It may be worth pointing out that
while emails do uniquely identify the specific person who
created the account, names are not unique. But if you have
a name like mine (Nishant Bhajaria), it is possible that very
few, if any, individuals have the same name. That said, in
the interest of avoiding records that would uniquely identify
a specific user, the engineering team could obfuscate both
the names and the email addresses.
Table 3.4 Backend database for Directions app

## Page 217

 
        
Name
 
      
 
        
Email
 
      
 
        
Starting 
address(Lat/Lo
n)
 
      
 
        
Ending 
address(Lat/Lo
n)
 
      
 
        
(hashed)
 
      
 
        
(hashed)
 
      
 
        
3 decimals
 
      
 
        
3 decimals
 
      
 
        
(hashed)
 
      
 
        
(hashed)
 
      
 
        
3 decimals
 
      
 
        
3 decimals
 
      
 
        
(hashed)
 
      
 
        
(hashed)
 
      
 
        
3 decimals
 
      
 
        
3 decimals
 
      
 
        
(hashed)
 
      
 
        
(hashed)
 
      
 
        
3 decimals
 
      
 
        
3 decimals
 
      
 
        
(hashed)
 
        
(hashed)
 
        
3 decimals
 
        
3 decimals

## Page 218

 
      
 
      
 
      
 
      
 
        
(hashed)
 
      
 
        
(hashed)
 
      
 
        
3 decimals
 
      
 
        
3 decimals
 
      
In order to make the location less precise, the engineering
team could reduce the number of decimal points in the GPS
addresses retained for analysis. The limited precision could
mean that the starting and ending addresses describe a
much larger geographic area. That makes it less likely that a
given address would uniquely identify a specific home or
office location.
The collective changes could mean that the data, as a whole,
is now less sensitive, and that the database records as listed
in table 3.4 are Confidential rather than Restricted.
This does leave open a question: what if there are use cases
that need precise addresses and identities? For example,
The safety team may need access to granular
location and contact information data in the event
that a customer complains they got into an
accident due to bad directions.
You may wish to launch premium versions of your
app where a user’s entire ride history is available
to them for a small fee.

## Page 219

In this situation, you could retain both versions of the data,
albeit with qualifications:
Table 3.3 would be available to a small set of
engineers with access controls, so that they would
have to request access with a business
justification, and their access dates would be
logged.
Table 3.4 would have less stringent requirements
and be more open in terms of access and retention
periods.
NOTE The preceding example casts engineers as less conservative on privacy, but
in a truly bottom-up startup culture, engineers may take on a “conscience of the
customer” activist role for privacy, while attorneys may be content with a
“compliance first” approach. A solid data governance strategy will provide you
flexibility to allow for the human dimension that is inherent in something as
contextual and personal as privacy.
Step 1 represents the ideation phase, where you collect data
from varying perspectives. However, in a real-world
scenario, you will need to formalize a data classification
scheme somewhat rapidly, since engineers and data
scientists will depend on it to make decisions. Accordingly, I
have customized steps 2 and 3, which follow, to allow for a
scenario where you need an operative data classification
system even as you work to evolve it with new information
and use cases coming in.
3.5.2 Formalizing and refactoring your data
classification

## Page 220

In step 2, I would produce an initial classification system
based on the regulation-focused input from legal and real-
word guidance from other stakeholders.
This is where engineers and aspiring engineers need to
empower their privacy leadership to ensure that there is a
conscious decision around how different risk levels are
created and how different data components are mapped to
those risk levels. This is the phase where many companies
end up with either a half-baked data classification scheme
that covers only the most urgent use cases, or several
different versions of data classification that are bespoke to
teams, geographies, etc.
While either of these may be great in the short term, fast-
moving companies may find that the “urgent replaces the
important” phenomenon takes over, in which case the
company settles on a half-baked classification with a
commitment to finalize it, but never gets around to it. At the
same time, multiple engineering and data science teams end
up making possibly irreversible decisions, thereby
entrenching this data classification.
To avoid this, as a privacy leader, I work with my
engineering and legal counterparts to create a biannual
cadence for data classification, whereby we release our
classification, V1 for example, as an official artifact while
opening up a copy of the same document in draft format to
collect comments. This is, in effect, the third step.
In step 3, the goals are to

## Page 221

Identify stakeholders who may not have weighed
in during steps 1 and 2, thereby making sure the
process is truly inclusive and representative of the
disparate work and product silos.
Ensure that any new use cases that come up with
business growth and other changes are assimilated
on an ongoing basis into a data classification that
is a truly living and breathing document, much like
the company’s products and technology stack
itself.
The third step is critical, since you will uncover areas where
key stakeholders may disagree on how privacy-critical a
particular data element is.
Let’s assume your company owns a platform where app
developers can build video games. You may come across a
use case where the engineering team wants to join internal
IDs with external data about the customer to track which
customers bought products by clicking on ads displayed in
the game.
You may find that the engineering team believes that such
an ID is not privacy-sensitive, since it is internal to the
company and will not identify a customer externally. The
legal team may disagree, since it may be possible to join
this ID to information that will personally identify a
customer, like an email address. The legal team may also
contend that such data could create re-identification risks,
especially in cases where customers request a copy of their
data.

## Page 222

3.5.3 The data classification process: A Microsoft
template
The three-step process I’ve just described represents the
most effective and iterative incarnation of data classification
that I have deployed at companies of various sizes. However,
it is only fair that I present you with alternatives, especially
from stakeholders I deem credible.
Microsoft has identified a model that I have found useful to
replicate in organizations that are large and sprawled out, as
well as in companies that are smaller and where specialized
roles around privacy may not exist.
In their white paper “Data classification for cloud
readiness,”14 Microsoft introduced a Plan, Do, Check, Act
model (see figure 3.6):
1. Plan—Identify a key individual from a central
privacy team whose role would include identifying
data systems, data collection points, the systems
through which data flows (for example, Kafka
Pipelines), the systems where data is stored
(unstructured databases like Cassandra, structured
databases like MySQL), various teams that use the
data, etc. This person will create a profile of the
data that helps the company operate by working
with the cross-functional stakeholders that I listed
before.

## Page 223

2. Do—After data classification policies are agreed
upon, this individual will own the deployment of
data classification, which could include governance
documents, system controls, etc.
3. Check—Merely classifying the data is not
sufficient; you’d want to make sure that the
privacy controls in your company as well as the
products the controls apply to reflect the data
classification. This is critical, since the purpose of
data classification is to ensure that the data is
treated in a meaningfully different fashion,
especially from a privacy standpoint.
4. Act—Data classification is not a “once and done”
effort. Companies grow and shrink, laws evolve
continually, privacy activists and media ask
questions, and engineering and product teams
become creative in their data collection strategies.
As such, the privacy team will constantly need to
classify and reclassify data and adapt access
control techniques accordingly.
Figure 3.6 explains the iterative nature of data classification,
which is reflective of how the process will typically play out.

## Page 224

Figure 3.6 A model for data classification15
It is now time for us to walk through an example of the data
classification process in detail.
3.6 Data classification: An example
Let’s look at a scenario reminiscent of what a real company
may face in terms of its data. It is vital to remember that
there may not be a single right answer to how data is
classified—there may be differences in opinion between
different teams and, as mentioned before, as the company

## Page 225

iterates through this process, data elements may later be
classified differently than they were before.
In this example, your company is part of a hospital where
patients get treatment and are prescribed medicines. Your
company also runs an online pharmacy and provides
customers the ability to browse, compare, and buy
medicines and then ship them to a specific address.
Customers can access these prescriptions via an app or the
website. In order to conduct business, the company needs,
as you can imagine, data from customers, such as the types
of data described in table 3.5.
Table 3.5 Different categories of data

## Page 226

 
        
Type of data
 
      
 
        
Examples
 
      
 
        
Identity data
 
      
 
        
Name, email, address, gender, Social Security number, 
tax ID, passport number, driver’s license number, income, 
marital status, occupation
 
      
 
        
Sensitive data
 
      
 
        
Medical history, prescription refill information, health 
care coverage information, preexisting conditions, etc.
 
      
 
        
Payment data
 
      
 
        
Credit card number (with or without expiration date), 
bank account and routing numbers, third-party payment 
service information (e.g., Venmo, PayPal)
 
      
 
        
Demographic 
data
 
      
 
        
Race, ethnicity, religion, sexual orientation/identity, 
political opinions or trade union membership
 
      

## Page 227

 
        
Transaction 
history
 
      
 
        
Services requested, services provided, date and time of 
service, amount charged and currency
 
      
 
        
Authentication 
and 
authorization 
data
 
      
 
        
Email (for authentication and login purposes, and to 
confirm order status), phone (for possible two-factor 
authentication, status updates, etc.), IP and device info 
(to check for fraud and other analysis)
 
      
Let’s see what step 1 in the data classification process I
described might look like for this business (the Plan phase,
as described by Microsoft).
If you look at this purely from a legal and risk-based lens,
you could make an argument for the lockdown model. For a
specific customer, you would retain data for a specific order
Only for as long as that order was in progress, and
Only teams in charge of orders could access that
data.
Once a customer receives their medicines and the refund
period expires, the data would be deleted. In this context, all
or most of these fields would be labeled, such that it reflects
their privacy sensitivity.

## Page 228

In contrast, your marketing team may want to conduct
analysis on purchases:
What are the buying patterns based on
demographics and location?
What products are purchased regularly versus
seasonally?
How does use of the app versus the website
correspond to purchases?
How can we identify patterns of shoppers based on
various income levels?
How can we look at this data individually and in
aggregate so as to provide better customer service
and plan for inventory?
These insights, and others like them, will help drive future
investments. And in order for these insights to be
meaningful, you would need data from a lot of users over a
protracted period of time.
As you can imagine, there is some tension between a very
privacy-focused approach where you want limited retention
and access, and a business-focused approach that requires
higher levels of access and retention.
This is where the cross-functional and iterative approach to
data classification can create a win-win situation:
You could create an operational database with
limited retention and access, where data is stored
for individual users.

## Page 229

You could then create an analysis database with
longer retention periods and relaxed access, but
with data aggregated for a large number of users.
As most seasoned leaders would agree, you should never
need to look at a specific user’s shopping habits in order to
make strategic business investments. Besides being creepy
from a privacy standpoint, you will likely end up with bad
business decisions. By splitting the data and aggregating it,
you can keep individualized data separate from aggregated
data and use it appropriately. Good business and good
privacy go hand in hand. Keep this in mind the next time
someone tells you that privacy is a blocker.
So what does data classification look like in this brave new
world?
Under Restricted, you could list individualized data that could
specifically identify a user:
Name
Birthdate
Address
Email
Phone
IP and device info
Payment information
In my experience, payment data is always rated at the
highest level of sensitivity. The preceding data would be

## Page 230

retained in the operational database for short periods of time
with tightly controlled and audited access.
For the analytics database, you could aggregate purchases
along the following lines:
Birth years
ZIP codes or GPS coordinates
Phone area codes
Device types
Purchase date ranges
That way, you could perform the sort of analysis we
described earlier without tying any of these purchases back
to a specific user. You could store this data for longer periods
of time and allow access to a range of stakeholders, from
business teams in charge of inventory to security teams
protecting the company from fraud. This is how a data
classification process evolves to balance privacy needs and
business goals.
At this point, you can use either the process I described to
iterate on the data classification, based on new use cases, or
follow the Microsoft process. In reality, step 2 as I described
it combines the Do and Check steps in the Microsoft model,
but I highly recommend tailoring a process that works for
your team.
In either case, you will need to achieve two concurrent
goals:

## Page 231

Collect feedback on the most current version of
your data classification with the goal of working
toward the next iteration.
Create enforceable and auditable controls to
support the practical implementation of the data
classification guidelines.
Some of the enforceable controls would be as follows:
Encryption at rest (to be confirmed by an
encryption expert)
Encryption in transit (to be confirmed by an
encryption expert)
Limited and business-approved access by your
own and third-party employees
Compliance with user retention and deletion policy
Continual iteration on the individual data classifications and
these controls will form the bulk of the work once an initial
version is finalized. Note that the four controls in the
preceding list are meant to be a starting point. I strongly
encourage executives to look at the controls I have describe
in this chapter and others more broadly as you develop your
overall data governance.
Summary

## Page 232

Data classification is a critical part of your overall
data governance strategy; this is the process that
helps you identify what you have and how it
changes your overall privacy risk for your business
and your customers.
Data classification will help you build a solid data
protection strategy to protect your business, scale
your resources, and maintain user trust.
As you classify data and revisit your classifications,
you can more intelligently deploy tools and policies
to handle various use cases without creating
unnecessary bureaucracy and process.
The complexity of privacy laws can be managed by
a sound data classification process and the
learnings that emerge from it.
Data classification is a strategic investment in
building a truly company-wide, cross-functional
process to help drive privacy, since several teams
will need to contribute to the end result.
Ultimately, every company will need to create and
customize its own data classification process.
1 Nishant Bhajaria, “Why isn’t the tech boom helping the economy?” LinkedIn, May 5, 2015,
http://mng.bz/v4j1.
2 Adam Hartung, “Three Smart Lessons From Facebook’s Purchase Of WhatsApp” Forbes,
February 24, 2014, http://mng.bz/4K0D.
3 “WhatsApp’s 55 Employees Are Rich. So Now What?” NBC News, February 20, 2014,
http://mng.bz/QqAR.
4 Sam Gustin, “Inside Yahoo!’s Tumblr Deal: Here's Who Hit the Billion Dollar Jackpot” Time,
May 21, 2013, http://mng.bz/voNm.
5 “Data classification for cloud readiness,” Microsoft, http://mng.bz/Xrv1.
6 “Data Types: Structured vs. Unstructured Data,” Enterprise Big Data Framework, January 9,
2019, http://mng.bz/yJlo.

## Page 233

7 Bernard Marr, “What Is Unstructured Data And Why Is It So Important To Businesses? An
Easy Explanation For Anyone,” Forbes, October 16, 2019, http://mng.bz/MvND.
8 Mary Shacklett, “Unstructured data: A cheat sheet,” TechRepublic, July 14,
http://mng.bz/aZW9.
9 “Capability Maturity Model (CMM),” TechTarget,
https://searchsoftwarequality.techtarget.com/definition/ Capability-Maturity-Model.
10 John Walsh, “Distinguishing Authn and Authz,” DZone, April 4, 2018, http://mng.bz/g1Z8.
11 Ellen Zhang, “What is Role-Based Access Control (RBAC)? Examples, Benefits, and More,”
DataInsider, December 1, 2020, http://mng.bz/5Z97.
12 PII definition, NIST, https://csrc.nist.gov/glossary/term/PII.
13 Gennie Gebhart, Bennett Cyphers, and Kurt Opsahl, “What We Mean When We Say ‘Data
Portability’,” EFF, September 13, 2018, http://mng.bz/6mWR.
14 Microsoft, “Data classification for cloud readiness,” http://mng.bz/o8XD.
15 Microsoft, “Data classification for cloud readiness.”

## Page 234

4 Data inventory
This chapter covers
What a data inventory is
Creating tags and a baseline for a data inventory
The technical architecture for the data inventory process
Understanding your data better for a more accurate inventory
Starting and adjusting the depth of the data inventory process
Assessing the effectiveness of your data inventory outcomes
In the last chapter, we dove deep into data classification. We
saw how the classification exercise helps build cross-
functional context on privacy risk, how it changes based on
data usage and context, and how it helps you tailor data
protection methodologies. The process and outcomes equip
engineering leaders and their lieutenants to make informed
decisions around what data to collect and how to protect it.
However, the data classification process is just half of a
larger data governance exercise. In order to right-size and
scale your privacy and security tools, you need the right
tooling to ensure that your data systems reflect your data
classification. This chapter will help you accomplish just that
by completing your data inventory. This is more important
than most leaders realize.
When companies had tightly controlled top-down cultures,
data collection operated in a need-based and awareness-

## Page 235

centric paradigm. Engineers knew what they could collect, so
the privacy and security controls were baked in by way of
preemption. In a decentralized and democratized setup, data
collection is ad hoc, automated, and voluminous. The
preponderance of universal identifiers, mobile devices, and
internet connectivity means that it is very difficult to control
data intake. Having your data—in databases, data stores,
and warehouses—reflect the data classification means that
anyone seeking to access and process it will have a good
sense of the privacy risk attached to that data. Building this
automation into your data and your systems will ensure that
you can proactively detect privacy risk even at scale. This is
what a data inventory does. Based on my experience, it is
unlikely that any manual process will enable you to sift
through petabytes of data and identify the risk levels without
either high error rates or significant delays in data flows to
downstream users. Additionally, just as finding books in a
library or emails in an inbox is that much easier when you
have a label (some sort of index) attached to them, it is
easier to locate data in your systems if the data has tags.
This is critical, since you may need to locate data quickly
and accurately when the need arises to delete it or to
surface it to a customer by way of a Data Subject Access
Request (DSAR). Those privacy requirements will be much
harder to fulfill without a data inventory.
And that is why, once your data classification is complete,
you will need the other half of the data governance offering
—the data inventory.

## Page 236

4.1 Data inventory: What it is and why you
need it
The process of adding tags derived from your data
classification to your data systems is the data inventory
process. As you build your data inventory, you are indexing
the contents of your data stores and making individual
components expeditiously searchable. Creating a data
inventory is like building the backend of a search engine for
your data, much like a team of smart engineers built the
backend of tools like Google.
This explanation offers an intuitive explanation of a data
inventory, but it is key that technical leaders understand the
risk mitigation and business enablement that a data
inventory makes possible.
In the lead-up to the GDPR, the International Association of
Privacy Professionals (IAPP) provided an enumerated plan so
companies could get a head start on compliance.1 This was
to be a checklist so that companies would know where to
start and what structures and processes to create as they
prepared for a post-GDPR world, one where privacy was to
become front and center like never before. This list remains
fairly applicable, even as its individual components have
become more complex to implement and there are more
variations based on a company’s use of data.
I have listed the plan here with my insights added:

## Page 237

1. “Conduct data inventory and mapping.” This
assumes that the starting point of a sound data
protection program is the ability to classify,
catalog, and discover data, such that the privacy
risk is comprehensible at the time of data
collection and access. This book provides a deep
dive into data governance based on this time-
tested guidance from industry experts.
2. “Establish a lawful basis for data processing and
cross-border transfers.” This is something your
legal team should advise on, but how you can
process data and where you can transfer it to may
take on additional complexities when it comes to
geographic boundaries. Making that assessment
requires exactly the sort of insight and
discoverability that data classification and data
inventory make possible.
3. “Build and maintain a data governance system,
including establishing leadership (where
appropriate, a data protection officer, setting forth
policies and training personnel).” This helps ensure
that rather than allocating privacy responsibilities
to engineering teams, it is preferred that privacy
leadership be separate. This independence will
allow for better tracking and accountability.

## Page 238

4. “Perform data protection impact assessments,
along with data protection by design and by
default.” This typically refers to the privacy risk
assessments and privacy reviews that your teams
conduct on products and features. We will be
looking at privacy risk assessments in chapter 6.
5. “Prepare and implement data retention and record
keeping policies and systems” so that you can be
transparent about what you collect and retain.
These obligations could form a part of your audits,
for which prudent bookkeeping is a prerequisite.
Otherwise, your audit processes could become
cumbersome and expensive.
6. “Configure systems and put in place processes to
accommodate data subjects’ rights, including
access, rectification, erasure, portability, objection
to automated processing and revocation of
consent.” As mentioned before, data subjects’
rights (DSAR) are a key commitment for many
companies thanks to laws like the GDPR and the
CCPA. Having a data inventory is key to meeting
these commitments at scale and with accuracy.

## Page 239

7. “Prepare for security breach response and
notification.” You will want your legal team and/or
outside counsel to weigh in, but several
jurisdictions in the United States and elsewhere
have breach notification laws. These laws create
expectations that companies that suffer from a
data breach need to notify the impacted entities
with specific pieces of information and within
specific timeframes.
8. “Have a sound vendor management protocol.” This
step is critical, since vendors that may get access
to your systems and your data could make
decisions with privacy implications. Assessing both
the ability of your vendors to follow your data
protection guidelines and their past record is
critical. As you saw previously, companies may
claim that data privacy issues occurred at third
parties, but your stakeholders in the privacy
community may hold you responsible nonetheless.
9. “Establish systems and channels for
communicating with your data protection
authority.” It is possible that you will need to
provide regulatory authorities with granular details
around data, your decisions about handling it, and
time-stamped records. A data inventory will enable
and accelerate this disclosure process, and that
could help build a strong trust relationship as well.
To engineering leaders who seek comfort from the fact that
the only companies in the news for privacy breaches are the
big tech giants, I have this to say: These high-visibility

## Page 240

companies faced a moment of truth after rapid growth; at
least they had the money to build privacy teams and retain
lawyers to represent them in court. What if regulators or
activist citizens come after a startup pre-IPO, and VCs fail to
even get a basic return on their investments?
Additionally, the smaller your size and the more limited your
resources, the harder it will be to adapt to a sudden
regulatory change—I know of several small companies that
found their roadmaps severely impacted. If you think privacy
is expensive, the opportunity cost of not having privacy
controls will almost certainly be higher. As a somewhat
imperfect analogue, consider this: Bill Gates recently said
that the antitrust investigation around Microsoft in the late
1990s affected the company’s ability to effectively
comprehend the threat posed by Google’s SaaS model and
Apple’s mobile computing model, resulting in a lost decade
for Microsoft. Why would you knowingly subject your
company to such uncertainty, especially when doing the
right thing with privacy will help your business build trust
with your customers and help growth?
The data inventory process is a key part of your data
protection program. Having established what a data
inventory is and the reasons that it is key, we will now look
at the foundational building blocks of a data inventory. The
next section will look at data inventory tags.
NOTE A data inventory is the act of making sure that your classification of data
based on privacy risk is reflected in the physical data stored in your systems and
data stores.

## Page 241

4.2 Machine-readable tags
Tagging or labeling is something we all do routinely in our
lives to help locate important materials like our tax returns
or medical records. However, this concept and process is key
when it comes to data governance. In this section, we’ll
discuss in detail what data inventory tags are, and we’ll look
at a specific example of their use.
4.2.1 What are data inventory tags?
A data inventory is the process of applying your data
classification onto your physical data stores. As you have
already seen, the classification process is fairly cross-
functional, and it forces teams to come up with labels that
describe the nature of the data and the privacy risk attached
to it. However, additional steps are required to ensure that
your data inventory is functional and serves its purpose—you
need to index the data, making it searchable and easier to
protect.
The first step in this process—one that many companies
tend to overlook, to their eventual detriment—is to come up
with tags or labels. These tags are the machine-readable
incarnation of the data classification. This may well be the
first time a company has common definitions relating to the
data previously collected by several teams across the
company. The task of finalizing these tags can often be
confusing, as teams may have gotten used to their own
naming conventions.

## Page 242

To simplify this process, I’ll provide some criteria for useable
data tags that will help your data inventory process and
outcomes:
These data tags should be easily consumable by
enforcement points like data loss prevention
gateways or information rights management for
actionable intelligence.
The tags should be compatible with and support
external regulatory requirements (e.g., GDPR,
CCPA). There will often be occasions when you
need to apply controls germane to specific
legislation, so tagging your data appropriately will
be helpful. (As an analogue, in Gmail you can tag
a specific email with the labels “family vacation
December 2019” and “Mom.” In this case, a search
for either term will surface that email.)
Tags should be applicable to all data in these
states: data at rest, data in transit, and data in
use. When it comes to data, you will need to
protect it regardless of its state, so the tags that
enable you to locate it should yield similar
outcomes regardless of whether the data is being
transported between data centers or lives in a data
warehouse.

## Page 243

Tag definitions should be canonical, unambiguous,
and machine-readable. They can be used either
individually (such as for individual database
columns or API parameters) or as a group,
represented as comma-separated values where
applicable (such as for an entire dataset or API).
This list is not exhaustive, but it should offer you a great
place to start. It is vital that your team take seriously the
exercise to come up with tag names. The process of applying
these tags, as you will soon find out, can be extremely
expensive. This is one area where weeks of planning will
save you months and years of retagging or months and
years of applying incorrect privacy protections.
4.2.2 Data inventory tags: A specific example
Now that you have a conceptual understanding of data
inventory tags, looking at specific patterns and examples will
help you form your own tagging strategy. This exercise will
provide an educational view of the granularity and variety of
data, as well as insight into why the tagging exercise is
mission critical.
Since the data inventory extends the existing data
classification, we will focus on a specific level of privacy
sensitivity. Table 4.1 shows how you can create different
kinds of tags for your most sensitive data (which I am calling
level 1 data).
First, the format for a specific tag would be along the
following lines:

## Page 244

(business|personal):[a-z]+(-[a-z]+)* 
This regular expression provides a template for what the end
result is allowed to be. This format achieves two goals:
It provides a clearly identifiable signal to
distinguish between business and user data; the
former may have lower privacy risk but high
security or IP risk, while the latter may have a
high privacy risk in that it probably belongs to your
customers.
It includes a descriptive name that will identify, for
consumers of that data, what is contained in the
record.
Note that table 4.1 also contains the retention period and
how the data is to be handled after the retention period
expires. This is critical for engineers to absorb.
Table 4.1 Data inventory tag template (level 1 data)

## Page 245

 
        
Level
 
      
 
        
Busin
ess/
perso
nal
 
      
 
        
Descripti
on
 
      
 
        
Maximu
m 
retentio
n period
 
      
 
        
Preservation 
requirement
 
      
 
        
Tag value
 
 
        
(business|pers
onal):[a-z]+(-[a-
z]+)*
 
 
        
Alternate value 
(e.g., GCP label)
 
 
        
(business|pers
onal)_[a-z]+(-[a-
z]+)*
 
      
 
        
Le
ve
l 1
 
      
 
        
Bu
si
ne
ss
 
      
 
        
Board 
meetin
gs
 
      
 
        
N/A
 
      
 
        
N/A
 
      
 
        
business:board
-material
 
 
        
or

## Page 246

 
 
        
business_boar
d-material
 
      
 
        
Le
ve
l 1
 
      
 
        
Bu
si
ne
ss
 
      
 
        
Non-
public 
financi
al data
 
      
 
        
N/A
 
      
 
        
N/A
 
      
 
        
business:non-
public-
financial
 
 
        
or
 
 
        
business_non-
public-
financial
 
      
 
        
Le
ve
l 1
 
      
 
        
Bu
si
ne
ss
 
      
 
        
Securi
ty 
busine
ss 
data
 
      
 
        
N/A
 
      
 
        
N/A
 
      
 
        
business:secur
ity
 
      

## Page 247

 
        
Le
ve
l 1
 
      
 
        
Pe
rs
on
al
 
      
 
        
Locati
on 
data
 
      
 
        
7 
years
 
      
 
        
Delete (non-
registered 
users);
 
 
        
retain until 
retention 
period expires 
(registered 
users)
 
      
 
        
personal:level
1-location
 
      
 
        
Le
ve
l 1
 
      
 
        
Pe
rs
on
al
 
      
 
        
Govern
ment 
identif
iers
 
      
 
        
Life of 
applic
ation 
(LOA)
 
      
 
        
Delete (for 
non-registered 
users);
 
 
        
7 years 
(registered 
users)
 
      
 
        
personal:gover
nment-id
 
      
 
        
Le
ve
l 1
 
        
Pe
rs
 
        
Level 
1 
demog
 
        
LOA
 
      
 
        
Delete
 
      
 
        
personal:level
1-demographic

## Page 248

 
      
on
al
 
      
raphic
data
 
      
 
      
 
        
Le
ve
l 1
 
      
 
        
Pe
rs
on
al
 
      
 
        
Biome
tric
 
      
 
        
LOA
 
      
 
        
Delete
 
      
 
        
personal:biom
etric
 
      
If you decide to categorize data at the tail end of the data
pipeline, the volume of data makes it difficult to identify and
classify, let alone automate policy enforcement, such as
automated retention and deletion policies. Tailoring these
policies in line with privacy risk at the categorization stage
and then applying tags to the data at the point of ingestion
will help scale privacy engineering for your organization.
Let’s assume, for example, that you have decided that a
data field has a lower privacy risk than was previously
thought. All you’d need to do is change the tag affixed to it,
and the corresponding policy would then apply.
Now that you understand how tags are created in line with
the regular expression format, we can examine how these
tags are mapped to data that you need to store and protect.
Let’s look at different tags for a business that owns several
restaurants and wants to build its data inventory.

## Page 249

Since your business owns restaurants, there would be a
significant number of employees who work as cooks,
delivery persons, and other staff. It is also likely that you’d
support a vast number of different ways whereby people
could prove their identity. Some of them might have a
driver’s license, while others may opt for a state ID.
Your use cases may involve
Updating the database with employment
verification records of new employees and
supporting all forms of ID
Searching for employees based on a specific ID
criteria, such as all employees who are on a two-
day probation after their first day, since they have
not provided a government ID yet
In table 4.2, the tag format (business|personal):[a-z]+
(-[a-z]+)*) allows you to provide a binary value
(True/False). With this value you can discern which
employees have provided a valid government ID (John Smith
and Jane Doe) and which ones have not (Abe Linc). After the
first three days of employment, you could run a query that
searches for employees with “False” in their tags, and
identify the employees who have yet to furnish an ID. This
assumes that “government-id” is set to be a Boolean;
alternatively, you could configure its value to be a number
that would either match the pattern of a government ID
(driver’s license, passport, etc.) or be a sequence of zeros to
indicate that a valid ID has not been provided.

## Page 250

The key takeaway here is that even if your data isn’t in a
structured data format, you can still use tagging to make the
data searchable and identifiable.
Table 4.2 Basic data inventory tags with binary values

## Page 251

 
        
Tier
 
      
 
        
Busi
ness
/user
 
      
 
        
Description
 
      
 
        
Tag value
 
 
        
(business|personal):[a-z]+
(-[a-z]+)*
 
 
        
Alternate value (e.g., GCP 
label)
 
 
        
(business|personal)_[a-z]+
(-[a-z]+)*
 
      
 
        
Tag example
 
      
 
        
Le
ve
l 1
 
      
 
        
Us
er
 
      
 
        
Govt 
identifiers
 
      
 
        
personal:government-id
 
      
 
        
John 
Smith:True
 
      
 
        
 
        
 
        
 
        
personal:government-id
 
        

## Page 252

Le
ve
l 1
 
      
Us
er
 
      
Govt 
identifiers
 
      
 
      
Jane 
Doe:True
 
      
 
        
Le
ve
l 1
 
      
 
        
Us
er
 
      
 
        
Govt 
identifiers
 
      
 
        
personal:government-id
 
      
 
        
Abe 
Linc:False
 
      
Now let’s assume you want to identify employees who are on
a work permit, and you therefore need to submit their
passports to prove their eligibility to work in the United
States. Table 4.3 shows how a data inventory can help. The
second (personal :government-id-passport) and third
(personal:government-id-driverlicense) rows have tag
formats to allow for different kinds of IDs. Instead of a
binary value of the kind in table 4.2, you can use regular
expressions to map the value of the tag. That way, the tags
will tell you whether a user has supplied a driver’s license or
a passport.
Table 4.3 Data inventory tags

## Page 253

 
        
Tier
 
      
 
        
Busi
ness
/user
 
      
 
        
Description
 
      
 
        
Tag value
 
 
        
(business|user):[a-z]+(-[a-
z]+):L|F
 
 
        
Alternate value (e.g., GCP 
label)
 
 
        
(business|user)_[a-z]+(-[a-
z]+):L/F
 
      
 
        
Tag example
 
      
 
        
Le
ve
l 1
 
      
 
        
Us
er
 
      
 
        
Govt 
identifiers
 
      
 
        
personal:government-id-
passport
 
      
 
        
Jerry 
Seinfeld:^
d{10}
 
      
 
        
 
        
 
        
 
        
 
        

## Page 254

Le
ve
l 1
 
      
Us
er
 
      
Govt 
identifiers
 
      
personal:government-id-
driverlicense
 
      
Jerry 
Maguire:^
d{9}
 
      
 
        
Le
ve
l 1
 
      
 
        
Us
er
 
      
 
        
Govt 
identifiers
 
      
 
        
personal:government-id-
passport
 
      
 
        
Jerry 
Tom:^d{10}
 
      
In table 4.3, the first and third users will match a request to
identify employees with valid passports (on the assumption
that passports have 10 numbers), while Jerry Maguire will
match a user who still needs to supply a passport (since he
has provided just a driver’s license, which has 9 numbers).
In this way, you can use a data inventory to
Come up with tags that make your data searchable
and map the data to privacy sensitivity
Extend the tags to meet diverse business use
cases
The preceding example is a simplified exercise. Data
inventory and real-world scenarios will get more complex
and more diverse. The key takeaway is that you are far
better off being able to search for, process, and delete data
using the preceding inventory rather than searching for
sensitive data in JSON blobs or other data formats. In that

## Page 255

scenario, you may miss sensitive data or end up spending
significant resources in the discovery process.
A data inventory ties in your privacy-centric understanding
of your data (your data classification) to the data itself. This
means that if you were to transfer your data from an on-
premises environment to the cloud, or from MongoDB to
Cassandra, you’d ensure that the data carried with it the
identities and risk values you have attached to it. This will
significantly help manage the privacy risk in a very
decentralized and bottom- up data-driven company.
Now that you have the tags ready to apply to the data, we
can create a baseline (a starting point) for your data
inventory before using automation.
4.3 Creating a baseline
For any organization, getting a handle on its data will require
a mix of human effort and automation. You will see in the
next section how the process of applying the tags involves a
combination of both, partly because of the volume of the
data and partly because of its complexity.
Before you do that, however, you need a process for
discovering your data. This is critical since, as you will see
shortly, most companies start the data inventory process
after a significant amount of data has already been
collected. While this initial discovery represents an often
unforeseen significant upfront expense, it also allows
companies to build a baseline of their existing data.

## Page 256

What we are looking at is some initial legwork to collect
information that is readily available but scattered across
different teams or that is in the minds of engineers without
being documented. This information is euphemistically
referred to as “tribal knowledge,” and turning tribal
knowledge into communal understanding is what we mean
by creating a baseline.
To create a baseline for a data inventory, engineers, data
scientists, and others can come up with models and
estimations of what data they have collected and where it
lives. While these initial results may turn out to be
incomplete or incorrect or both, this process can be useful in
capturing known use cases and building machine learning
(ML) models for additional discovery.
I recommend doing this pre-inventory by inspecting your
data storage from two dimensions:
Data inventory by storage systems
Data inventory by data owner
In preparing your teams to inventory their data by storage
system, you will want to hand them a template that helps
them record what they find in their first manual inventory of
the systems they can account for. For each storage system
(e.g., Hive, Vertica, Kafka, SQL database, S3 buckets, etc.),
data should be inventoried using the following attributes:
Total size (storage volume)
Structured/unstructured data by %

## Page 257

Data classification tier (if your storage unit has
data with multiple classifications, you should apply
the highest risk tier)
Whether or not the unit contains personal data
It is not sufficient to inventory your data by storage system,
however. Storage systems are often owned by multiple
stakeholders. You may also find that some storage systems
are not owned by anyone, but multiple engineers use them
to store data.
To get an accurate view of your systems, you will want to
inventory your data by data owner as well. That way,
orphaned data stores will find owners, and you can drive
some accountability for privacy.
The attribute checklist for this second step would be similar
to the first, and could look like this:
Total size (storage volume)
Unit count (# of services, users, accounts, or
datasets)
Structured vs. unstructured
Data classification tier (if your storage unit has
data with multiple classifications, you should apply
the highest risk tier)
Whether or not the unit contains personal data
Once these initial baselines are complete, you will have a
sense of which business unit owns what percentage of
privacy-sensitive data, and what systems the data lives in.

## Page 258

This mapping is critical, and I have, on occasion, discovered
data and systems that went undetected by automation;
sometimes one reclusive engineer knows of an S3 bucket
containing a table that maps home addresses to food
deliveries.
Now that you have the tags ready to apply to the data, as
well as an initial manual inventory, it’s time to look at the
technical and backend infrastructure required to execute the
data inventory process.
4.4 The technical architecture
Many business leaders enjoy using phrases like “It costs
money to make money.” This typically refers to marketing,
research, and other investments that are necessary for
business growth. New products in new markets, for
example, often require more expense in early stages before
the product leads to revenue and profits.
There is a similar challenge with regard to data inventories.
The business value add for a data inventory is that it
attaches critical information to data, highlighting the privacy
risk, and it also indexes the data for easy discoverability.
The engineering challenge in a data inventory involves a
one-time expense in discovering the data so that you can
index it and tag it; in other words, you have to first discover
the data so as to make it discoverable. Note that this
assumes you have a backlog of data already collected before
the data inventory. In subsequent chapters, we will look at

## Page 259

how you can time the data inventory process so as to
minimize this backlog.
For the remainder of this chapter, we will be focusing on
data discovery and ML-driven data categorization as key
components for your data inventory. There is a clear
implication in these terms that conventional tools are
insufficient to discover such data.
4.4.1 Structured and unstructured data
I have had many business leaders ask me questions like,
“Database A did not take long to process, so why is database
B taking much longer, even though it has less data?” This is
where the inherent difference between structured and
unstructured data is key.
According to G2.com, a peer-to-peer review site,
Structured data is most often categorized as quantitative data, [and it is
typically] data that fits neatly within fixed fields and columns in relational
databases and spreadsheets. Structured data is highly organized and easily
understood by machine language. Those working within relational databases
can input, search, and manipulate structured data relatively quickly... This is
the most attractive feature of structured data.2
In figure 4.1, you can get a clearer sense of how structured
data is created and how its components relate to each other.
It shows a database that has tables for users (or more
specifically, customers), the orders made by each customer,
the composition of each order, and descriptions of the
products themselves.

## Page 260

Figure 4.1 Structured data
With figure 4.1 in mind, let’s construct a database that will
allow us to track orders for a retail business:

## Page 261

1. We will create a User table of users/customers.
In order to send the merchandise to and possibly market
to a customer, we will need to create a table that stores
information about each user, like their name and contact
information. Two things bear mentioning:
Each user’s row contains personally identifiable
information, like their address, email, etc.
Each row also contains a unique ID that can be used
to associate a user’s data in one table with other
data about the user in a different table.
2. We will create an Order table that contains orders
placed by a user.
Since one user can place many orders, this table could
have several entries for each user. Note that instead of
using the user’s name or email to link this table back to
the main User table, we use the ID for two reasons:
This reduces the duplication of sensitive data in the
computer systems for the company.
The ID can be numeric, and that could make
matching easier for queries that are run for
troubleshooting and analysis.
Note that each order also has an OrderID, and that will
help us further develop our database for the contents of
the order.

## Page 262

3. We will create a LineItem table that contains
details about the orders, so that we know what
products are contained in an order.
Just as each order has an ID, the products contained in
the order also have an ID. In our LineItem table, we
have a many-to-one relationship between products and
orders, since each order could have zero or more
products. The presence of a ProductID enables us to
relate the LineItem table to a different table that
contains details about the products.
4. We will create a Product table that contains details
about the products themselves.
This table links back to the LineItem table using the
ProductID and contains details about the products
themselves.
From the top down in figure 4.1, you can see that UserID 1
refers to the customer Alice, who had two OrderIDs of 1234
and 5678. Next, Alice had two ProductIDs of 765 and 987.
Finally, we can see that Alice purchased two packages of
potatoes and one package of dried spaghetti.
This data is organized very neatly and logically, but in
modern systems the data does not often flow in with clear
field and column delineations and logical correlations. In
order to more accurately analyze your business
performance, you need to account for data that does not
follow the structured format. That brings us to unstructured
data.

## Page 263

Unstructured data is often qualitative and cannot be
processed or analyzed using conventional tools. The data
management company NetApp identifies several examples:3
Rich media—Media and entertainment data,
surveillance data, geospatial data, audio, etc.
Document collections—Invoices, records, emails,
and productivity applications
Internet of Things (IoT)—Sensor data, ticker data
Application logs—Machine learning, artificial
intelligence
These examples come under the umbrella of unstructured
data because different service owners may define and store
them differently. The interoperability between different apps
and services means that a consistent key/value schema may
not be possible.
The NetApp article points out that companies routinely
collect and process large volumes of such data. This is
unsurprising, given the proliferation of devices, internet
connectivity, services, and identities that are available to
engineers and customers alike. This means that the data
itself could vary significantly across its various components,
and inferences or changes to the data could lead to growth
in its size. This data then proliferates across the tech stack,
making it challenging in terms of size when it comes to
privacy protections.
The difference between structured and unstructured data is
instructive in terms of the value proposition for the

## Page 264

company. The rigid schemas for structured data make
discoverability easier but inhibit possible experimentation.
The diversity of datasets within unstructured data creates
new insights, but the volume makes maintainability and
privacy harder. The value of the data is hard to quantify, and
so is developing a tighter correlation between privacy risk
and volume.
That said, given the autonomy that modern engineering
teams possess, they opt to collect unstructured data not in
response to a need, but in anticipation of needs down the
line.
In subsequent portions of this chapter, you will note that
expeditious discovery of this data for inventory purposes and
methodical assessment of the privacy risk is key.
4.4.2 Data inventory architectural capabilities
It is now time to look at the technical implementation of
data inventories. You need a data inventory architecture that
can perform the following activities:
1. Crawl various known data stores.
2. Discover other datasets (especially unstructured
data).
3. Make those datasets and corresponding metadata
available for tagging.
4. Provide extensibility to add new metadata.
5. Support the categorization of personal data
(privacy use case).

## Page 265

In this list, the first three steps refer to data discovery and
tagging. That core capability is at the heart of a data
inventory. It is vital that your infrastructure be able to
discover data spread out across your storage systems.
As I’ve mentioned, a significant chunk of data we collect
tends to be unstructured. A chunk of data may enter your
systems as JSON blobs, for example, so you will need tools
like crawlers to crawl various data stores and discover
datasets, and then apply the tags to the data at the right
level of granularity. These data crawlers will use tools like
regular expressions and data lineage to search for data and
make it available for tagging. As you will see later, these
tools will become richer as you discover more data, and, in
that sense, a data inventory is a process that yields
outcomes and improves based on those outcomes.
The fourth step in the preceding list, where your
infrastructure allows engineers to enter additional metadata,
is also important. Engineering leaders and the engineers
they manage may ask, “Why invest in so much
infrastructure only to include a manual process where
engineers enter critical inventory information?” The reality is
that, as you just learned, a data inventory is an evolutionary
process that improves as you penetrate more systems and
build relationships between different data. Until you reach
data inventory maturity, a topic we will touch on shortly, it is
vital that your process be as comprehensive as possible. You
cannot rely on your engineers to inventory all your data, but
you should allow them the option of entering the appropriate
information via an API or some sort of UI. I have had the

## Page 266

pleasant surprise, as I led data inventory programs into a
stage of maturity, of engineers and data scientists
volunteering to enter this information for data they had
collected and knew about but that our scripts and tools had
failed to detect.
You can then make a judgment call on whether to check
their work using your tools or to divert your automation to
other data stores.
Finally, as noted in the fifth step, your infrastructure should
enable the categorization of personal data. This is where,
having discovered your data, you will want to apply the tags.
As I will explain shortly, this process requires infrastructure,
automation, human judgment, and artificial intelligence.
The infrastructure for all this work will cost money, and the
results will take some time to materialize. With tight
budgets, many engineering leaders may wonder if the
expense is worth it. As a privacy expert, as someone who
sets a high bar on protecting user trust, and as someone
who has had to work with regulators, I believe the data
inventory is a bargain, considering the fines and reputational
harm that privacy issues can cause.
Even so, it makes sense to look at the preceding list more
holistically. Specifically, the first four steps are required by
data science teams anyway, for improving data discovery
and quality. Teams that guide business investment decisions
need high-quality data that is correctly labeled. They
typically avail themselves of such data in an aggregated
form from the data warehouse. Having this data labeled and

## Page 267

collated, with non-essential data deleted, will improve their
analysis results and reduce the time it takes to run data
retrieval queries.
Similarly, any time you discover too late in the process that
you have retained data you shouldn’t have, you have
created work for teams like the data platform and
warehousing teams. I once worked for a company where we
unknowingly collected IP addresses from our users without
their consent. The data made it to our warehouses in JSON
blobs and was not discovered at the time of ingestion and
initial storage. In order to delete this data, we had to take
our databases offline, restate our tables (in essence,
deleting them and rewriting them with less information), and
re-run all our queries to derive analysis data. The entire data
analyst team had to sit on their hands for three days while
all available hardware was thrown at the problem to clean up
the backend data. Besides the cost of deleting the IP
address, we bore the opportunity cost of not being able to
conduct data analysis for three days and losing out on
legitimate data we could have collected.
I recommend that companies not make the privacy team the
face of the data inventory. The data inventory is a business
requirement, not a privacy requirement. In fact, the privacy,
data platform, and data science teams should be able to split
the costs, pool their abilities, and produce a better data
inventory.
4.4.3 Data inventory workflow

## Page 268

Figure 4.2 outlines the flow of data and layout of systems for
the data inventory infrastructure. It shows how the
classification of data is followed by the creation of tags and
their application to ingested data. Understanding this is
critical for creating the tooling necessary to execute a data
inventory.
Figure 4.2 The data inventory flow diagram
Figure 4.2 zooms out a bit further on the data inventory
workflow. I have labeled the boxes with numbers for easy
reference, but please note that these actions are not always
sequential. You will need to configure them to suit your
needs.
The data inventory service (DIS, shown in box 6 in the
diagram) is where the data inventory happens. This box

## Page 269

represents the fifth step in the previous subsection, where
you add tags to the data in line with your data classification.
Let’s walk through this process in a bit more detail.
The data classification process is represented by box 1 in
figure 4.2. This is where your cross-functional teams classify
data based on regulations, usage, etc., with the intention of
ending up with tags for your data. In a real-life scenario, this
process will iterate and resurface repeatedly rather than be
represented by just one box, but this diagram aims to
simplify the process. Box 2 represents the creation of the
machine-readable tags that you saw examples of earlier.
The data coming into your system is represented by box 3 at
the bottom left. This diagram assumes you have one main
API that makes all this data ingestion possible, though your
infrastructure is almost certainly more complex.
The DIS can obtain all the data and related metadata via
crawlers, event listeners, and other devices. All of this
tooling is represented by box 4 in the middle section. I will
explain this tooling more, shortly.
The data flow in figure 4.2 is logical in that it visualizes the
steps ranging from the collaborative and manual (classifying
data, planning the tags) to the automated (discovering data,
affixing tags). However, there are some nuances to the
process that call for further examination.
Figure 4.3 dives deeper and provides a technical view of the
data flow ranging from discovery and ingestion to the

## Page 270

classification, tagging, and additional processing tailored to
the privacy risks represented by the tags. In order to
perform a data inventory scalably and against the most
comprehensive data set, it makes sense to consolidate as
much of your data as possible before starting the tagging
process.
Figure 4.3 The data inventory system; consolidate your data before the
tagging process.
Figure 4.3 shows how you can consolidate your data and
metadata in one location (step 1 in the figure). You can do
that using crawlers, event listeners, etc. These tools will use
regular expressions and ML-based techniques to step

## Page 271

through your data stores, sample specific databases, and
look at the data lineage to infer the presence and risk of
data. For example, in order to search for columns or rows
with Social Security numbers, your crawlers could look for
any piece of data that matches ^\d{3}-\d{2}-\d{4}$,
whereby you will look for a pattern that has three numbers,
followed by a hyphen, two numbers, another hyphen, and
then four more numbers.
These tools will get more comprehensive and accurate with
successive iterations of your data inventory process. You
may also want to provide a UI portal for engineers to
manually enter their data schemas, as we have already
discussed.
The middle column of this diagram (step 2) highlights that
Engineers and data scientists who know their data
can manually categorize the data.
This manual classification can be used to train ML-
based models that will apply data classification
tags to your data.
This combination of manual and ML-based data inventory will
help reduce your dependence on manual classification
On the far-right of the figure (step 3) is the step of finalizing
your data tagging after manual and ML-driven classification.
The diagram shows DIS as a multidimensional system in
how it instruments the data inventory process. DIS is both a
service and a database. As a service, it feeds the data to be
classified to the manual and ML-based classifiers. The

## Page 272

classifiers are both human experts and ML-tools that infer
what the data is and then assign a privacy classification and
tag to that data. As a database, DIS provides information to
classifiers such as column name, column type, manual
personal data categorization, etc. The classifiers use this
information to infer the personal data category type
automatically. Manual classification is similarly enabled by
this incarnation of DIS. In this way, DIS combines the data
and the business logic to enable the actual tagging of this
data. All the tagged data is then stored in a separate and
temporary database.
Note that DIS also plays the role of a pure database on the
far right. At this stage, it stores the data that has been
tagged and processed through a “decider” process to make
sure that the initial tagging was completed correctly. This
decider could involve tooling to sample data, or it could
allow for human verification to provide a sanity check. This
is the judgment call I referenced earlier to ensure that you
are not being overly conservative or cavalier in your tagging
process.
Once all of this is complete, you can apply policies to protect
your data. Remember, this is where you can
programmatically apply policies like authentication,
authorization, etc.
Now your data is ready to use, with appropriate protection
embedded into the data. You may have heard industry
buzzwords like “privacy by design.” We have taken things a
step further here with “privacy by data.”

## Page 273

Since embedding appropriate controls into the data is critical
for privacy, let’s dive deeper into building a better
understanding of the data.
4.5 Understanding the data
Key to successfully creating a data inventory is being able to
recognize the data and infer what is contained in specific
records. In order to get to this stage, you need to discover
and assess all the metadata attached to the data.
4.5.1 The metadata definition process
You’ll need a way to capture as much metadata as possible,
so that data is classified correctly, and you’ll need consistent
metadata definitions across all your sources. Figure 4.4
shows the comprehensive nature of metadata collection that
you will need. DIS needs to span not only datasets but all
data entities. This means that merely locating data is not
sufficient; you need to understand what service made that
data available, where it was last located, and maybe even
what the source of original ingestion was. All of this
information, simplistically speaking, constitutes the
metadata.

## Page 274

Figure 4.4 The metadata discovery system
The DIS needs to capture metadata about online, offline,
and real-time datasets and other data artifacts such as ML
features, business metrics, and dashboards. It must also
collect information from services, such as data lineage and
other infrastructure components.
Collecting this metadata reflects a singular priority: for
years, companies have built infrastructure to harvest and
consume data; the data inventory requires investing in
handling this data based on what that data is and its
attendant risk.

## Page 275

Because the DIS needs to understand the data it collects
from many sources, you first need to establish a metadata
definition, specifying what the metadata tells you about the
data itself. Establishing such a definition will help distinguish
your desired data from similar data found in different
sources. If you lack a metadata definition, this may result in
ambiguity within the information you are processing. For
example, you will want metadata to distinguish between a
valid credit card that needs to be protected and an expired
gift card that poses less risk and may therefore need a lot
less privacy protection.
The absence of a metadata definition may also lead to
unstructured data being detected (and classified) incorrectly,
since the definitions will vary across different searches. For
example, credit card numbers and gift cards will ideally
contain metadata that will help engineers differentiate
between the two. It stands to reason that credit cards with a
high limit would require more privacy protections than gift
cards, whose value is presumably lower. Figure 4.5
illustrates how you can handle this problem. I recommend
that you use a taxonomy-like structure with entity and value
types to define the metadata. In figure 4.5, the MySQL and
RelationalDB tables are defined as entity types with
properties that define what they mean. Just as a human
being has properties like height and weight, MySQL has
properties like Name and Structure.

## Page 276

Figure 4.5 Metadata definition and registration
The MySQL table is defined as a relational database, and its
ID is a UUID value by design. Every record in the MySQL
database will have a unique ID, since the definition of the
UUID guarantees as much.
Part of what DIS helps accomplish, besides discovering data,
is correlating the metadata definition to the data. This way,
we are able to standardize metadata across the board, from
online schemas or offline Hive dataset schemas, from
services or storage- level components. Once you have an
understanding of how your datasets—which you have
already classified conceptually—relate to each other, you can
use tooling to inform the tagging outcome.
4.5.2 The metadata discovery process

## Page 277

Given the vast spread of data in your systems, you will need
a mix of tools for data discovery. Figure 4.6 shows how you
can use some of the tools we have already discussed to
discover and collate your data and attendant metadata.
Figure 4.6 How a data inventory system can obtain data using the Pull
and Push models
I recommend you use both the Pull and Push models to
collect metadata from various metadata sources.
On the Pull model side, you have

## Page 278

Crawlers that periodically collect information from
metadata sources. Crawlers are very effective for
collecting certain metadata types where the
collection process needs to be throttled on the
client side to avoid overloading target systems.
Event-based listeners for near real-time metadata
collection, to capture time-sensitive information
such as data quality or metadata versioning. This
way you can notify data users in a timely manner.
On the Push model side, things should be a bit more
straightforward:
You can use existing developer APIs and other
tools engineers use to exchange data for discovery
purposes.
You can also use crowdsourcing to obtain humanly
curated information, such as descriptions. This
may sound basic, but you might be surprised by
what you can get from engineers who have tucked
away data on the premise that they might need it
later.
It is reasonable to conclude that the Push model will lead to
an inventory not just of the data but also of the pipes and
vehicles that move it from system to system. In that way,
the data inventory will help you build a better understanding
of how data flows through your system in a way that very
few engineers, if any, possess in modern businesses.

## Page 279

Now that you understand the logical and technical
implementation of a data inventory, it is time to place this
important activity in the ever-growing list of business
priorities. The next section offers guidance on when to start
your data inventory process.
4.6 When should you start the data
inventory process?
Imagine asking someone for feedback on your cooking, only
to be told something like, “It needs a little less salt.” Some
decisions are impossible to undo, and that is especially the
case with data. This question—when is the right time to start
a data inventory—goes to the heart of the second question,
about why a data inventory is difficult; appreciating the first
of those two questions tends to inform the response to the
second.
4.6.1 Why is the data inventory process so hard?
Besides the technical details we have already seen, it is
important to understand why the data inventory process is
so complex to execute.
First, both as a business challenge and in the race for
resources, privacy lags behind growth. In most companies,
privacy/security specialists are never early hires. If
engineers and data scientists are elephants in a circus,
privacy and security specialists have the thankless task of
trailing them with shovels. But more seriously, I have usually

## Page 280

been hired at major companies after the company was hit by
a fine or a consent decree, a lot of data had been collected,
bad habits were formed, and there was a lot of catching up
to do. At the same time, unless a company grows revenue
and users, it cannot afford privacy specialists. Growth
finances privacy, and privacy specialists need to remember
that the business is not the enemy.
Second, as we have already seen, modern companies
optimize for growth and build decentralized teams that chart
their courses independently. Privacy, on the other hand,
needs a centralized focus. Someone in France who uses the
English version of your online service should get the same
privacy protection as someone in France who uses the
French version. This is challenging to enforce when various
teams operate in their silos and make decisions around
mapping artifacts to services in an inconsistent fashion. To
that end, if any of your teams cause privacy issues, your
company as a whole suffers, rather than just your payment
team or billing team. You will need a sophisticated privacy
program, since privacy not only lags behind growth but also
requires a mindset different from the one that enabled you
to grow.
Finally, there is procrastination. Too many companies wait
until there is a major privacy incident or regulatory action
before they start with privacy programs. By that time, data
and risk have accumulated, and a fix needs to be put in
place before the risk becomes financial and consequential.
Engineers have gotten used to the “we have always done it
this way” principle. In these cases, even mature and

## Page 281

prestigious companies resemble data addicts. They feel a
compulsion to keep going, to repeat the pattern again and
again, because carrying on feels easier than stopping;
stopping would mean a brutal audit of harm already done,
money squandered, and trust destroyed. This moment of
reckoning can be painful, but like getting a root canal, it’s
not one that can be postponed for long. Continuing this
practice in the face of such risk would be doubling down on
the sunk cost fallacy.
Given the costs of delaying the data inventory process too
much, let’s take a look at how you can place this critical step
into your data lifecycle.
4.6.2 Data inventory: Sooner is better than later
A peer of mine from my Netflix days (where I started the
privacy engineering program) had a pithy saying: “When it
comes to protecting data, the best time to start is
yesterday; the second best time is today.”
To conceptualize an early stage data inventory process, think
of data coming into your company as a funnel (figure 4.7).
Once data enters your system, users will copy it, infer other
data from it, and so on. As that data moves deeper into your
system from left to right, it grows in size, just like the an
inverse funnel. More than a few senior leaders may be too
far removed from the front lines to appreciate this dynamic.

## Page 282

Figure 4.7 Data inventory through the lens of a data funnel; as data
flows through the company’s systems, it grows in size due to copies,
inferences, joins, etc.
As engineers and data scientists have collected more data,
cloud computing has made it easier to acquire more storage,
compared to the early days when IT had to physically
acquire more hardware. In much the same way, any time
there is available storage bandwidth and computing power,
creative engineers and data scientists will leverage them to
conduct experiments with data that was previously not
processed. The system is designed for growth: growth in
data collection and growth in the infrastructural capabilities
to process it. A colleague from my time at Google called this
the paradox of “high availability, low visibility.” This is how
the funnel grows from left to right.

## Page 283

Recently published research by Gartner (“Guidance for
Addressing Risks with Unstructured Data”) explains how our
IT infrastructure has become denser and more
interconnected. This has had downstream implications on
data. As companies grow and engineers become more
empowered to manage their own services, the power of
central IT teams to manage data and services tends to
shrink. Individual engineers can provision services to
automate their existing capabilities, optimize antiquated
capabilities, evangelize new services to drive adoption, etc.
This state of affairs means that creating a standard for data
management becomes difficult. To make matters more
complicated, sharing the data generated by these services
with third parties complicates the task of maintaining a data
catalog.
Bottom-up innovation offers teams across the company a lot
of freedom, but freedom is not free. There is a cost-benefit
balance to consider. The key goal of an in-house IT
organization is to streamline the software and hardware
procurement process. That discipline has the added benefit
of helping the company manage data governance. However,
as businesses have become more decentralized, the ability
of IT to enforce this discipline has diminished.
There is no doubt that all the non-IT services help provide
better experiences to customers and employees alike. After
all, someone is paying for these enterprise accounts. These
services could also help generate vast amounts of data to
help drive marketing and product development. But they
also make any kind of data management hard. That, in turn,

## Page 284

makes risk measurement and data protection difficult.
Creating a technical infrastructure that finds the right
balance between these two systems is a challenge for all
engineering leaders, but the data inventory process cannot
be put off, given the risks inherent in the data.
To stick with the funnel analogy, the right time to inventory
your data is as early in the funnel as possible. You want your
data inventory to be as far left in figure 4.7 as possible. This
will help you apply the optimum data protection techniques
before engineers start using the data.
Engineering leaders often find it hard to make decisions
about the timing for the data inventory when they face
pushback from stakeholders across the business. Even as it
makes sense to front-load the process, as described in figure
4.7, this requires additional expense (since most companies
do not have the capability to tag the data at the ingestion
point), and it may even slow the flow of data to downstream
services, at least for some time.
A data inventory gets more and more accurate once
engineers examine categorized data by sampling it for
accuracy. The goal here is to build models that can be used
to tag data at scale using automation. Until the data
inventory process builds in enough models around data
types and metadata, the inventory process may increase the
time before your microservices can run low-latency queries
like before.
In order to help drive that evolution and progress, figure 4.8
helps to explain how initiating data inventory early could

## Page 285

demonstrably help manage and mitigate business risk. As
you can see, unless you have inventoried your data, it is
impossible to apply any meaningful controls to it. The
message this diagram sends is that the moment you collect
data (in the far left panel), you’d ideally want to start the
data inventory (the second panel from the left) so that you
can finalize the logic around what data gets what protection
via security and privacy controls (the third panel from the
left). Once the privacy protections are tied to the data itself,
you can move to data usage, external sharing, and eventual
deletion, all of which are represented by subsequent panels.
Figure 4.8 The earlier you inventory the data, the more you help
reduce risk.
The arrow that hovers over the rightmost three panels in
figure 4.8 covers the parts that we are most familiar with:
engineers running queries against data; modifying it; joining
it; sharing it with vendors with tracking pixels, APIs, or file
transfers; and finally deleting it. It is vital that you apply
data governance, which includes classification and physical

## Page 286

inventory, before your data enters this realm. This is where
either your data will have built-in privacy controls, or it will
not. The only way to be on the right side of that divide is
having governance in place.
The use cases for data will keep increasing as innovation in
the space grows; having your data classified, tagged, and
protected in line with your privacy risk and trust metrics is
critical. This is especially important, since data usage is
irreversible; you cannot un-share data with a third party, so
you will want to prioritize your data inventory so that you
can make informed decisions around the use of your data.
4.7 A data inventory is not a binary
process
Engineering leaders and their technical deputies will want to
know how they can calibrate their data inventory in stages of
maturity. It’s not possible to inventory all or even significant
chunks of data in one go, nor does all data need to be
inventoried at the same time. To that end, I will present
three stages of data inventory maturity. Besides allowing
your teams to improve the reach and accuracy of your
inventory process, this gradual maturing will allow your
inventory process to evolve in line with specific business
goals.
4.7.1 Data inventory level 1

## Page 287

Level 1 is the most basic level, where the data classification
tags are applied at the database/bucket level. The results
and key performance indicators (KPIs) of a level 1 data
inventory are defined in table 4.4, but you will want to make
changes as necessary for your business.
Table 4.4 Data inventory level 1

## Page 288

 
        
Data source
 
      
 
        
Results to be produced
 
      
 
        
KPI for measuring 
progress
 
      
 
        
Databases 
(structured 
data) in 
data 
centers
 
      
 
        
 
          
1. Total data volume (TB/PB) for 
each database instance
 
 
          
2. Data classification category tags 
for each database instance (i.e., 
what tags are represented in this 
specific database instance?)
 
 
          
 
        
 
          
1. % of total 
production data 
volume in 
production data 
centers that has 
undergone a level 
1 inventory
 
 
          
2. % of production 
database 
instances in 
production data 
centers that have 
undergone a level 
1 inventory
 
        
 
      

## Page 289

3.  
            Data tier composition for 
production data in production data 
centers: 
 
            
 
              
% of total production data 
volume containing the most 
sensitive data
 
 
              
% of total production minus 
sensitive data
 
 
              
% of total production data 
volume containing public 
data
 
            
 
          
 
        
 
      
 
        
Public 
cloud 
storage 
 
        
 
          
 
        
 
          

## Page 290

buckets 
(unstructur
ed data; 
currently 
AWS/GCP)
 
      
1. Total data volume (TB/PB) for 
each bucket
 
 
          
2. Data classification category tags 
for each bucket (i.e., what tags are 
represented in this specific 
bucket?)
 
 
          
1. % of total 
production data 
volume in 
production public 
clouds that have 
completed a level 
1 inventory
 
 
          
2. % of buckets in 
production public 
clouds that have 
completed a level 
1 inventory
 
        
 
      

## Page 291

3.  
            Data tier composition in 
production public clouds: 
 
            
 
              
% of total production data 
volume containing the most 
sensitive data
 
 
              
% of total production minus 
sensitive data
 
 
              
% of total production data 
volume containing public 
data
 
            
 
          
 
        
 
      
As table 4.4 shows, a level 1 data inventory operates at the
level of the storage container (the database or the bucket)
and gives you a sense of the kind of data contained (by way
of the tags present in the data) and the composition of the

## Page 292

data itself (by way of the breakdown of the tiers of sensitive
data).
As an engineering leader, you can get interesting insights
from even this high level of data inventory:
Buckets and databases that contain high volumes
of data, but where only a small percentage of it is
sensitive, could be split into two different
databases or buckets with only the system
containing sensitive data being subject to strict
access controls.
If a high percentage of a database instance has
undergone the inventory process, but the portion
yet to be inventoried contains a disproportionate
share of unstructured data, the risk assessment
could change. This could help you delay decisions
around data sharing until fuller levels of inventory
are achieved.
To address these concerns, and as your organization grows
and privacy scrutiny increases, you may want even deeper
insights. This is where the level 2 data inventory becomes
critical.
4.7.2 Data inventory level 2
At level 2, tagging is much more fine-grained—either at the
column level for structured data (such as a Hive database)
or at the object level for unstructured data (such as AWS
S3). The outcome of a level 2 inventory is that all columns in

## Page 293

structured data stores and all objects in unstructured data
stores are tagged. The results and KPIs for a level 2 data
inventory are defined in table 4.5.
Table 4.5 Data inventory level 2

## Page 294

 
        
Data source
 
      
 
        
Results to be produced
 
      
 
        
KPI for measuring 
progress
 
      
 
        
Databases 
(structured 
data) in 
data 
centers
 
      
 
        
 
          
1. Total data volume (TB/PB) for 
each database instance
 
 
          
2. Data classification category tags 
for data columns in each column
 
 
          
 
        
 
          
1. % of total 
production data 
volume in 
production 
database 
instances that 
have completed a 
level 2 inventory
 
 
          
2. % of production 
columns and 
objects that have 
completed a level 
2 inventory
 
        
 
      

## Page 295

3.  
            Data tier composition for 
production data in primary 
production data centers: 
 
            
 
              
% of total production data 
volume containing the most 
sensitive data
 
 
              
% of total production minus 
sensitive data
 
 
              
% of total production data 
volume containing public 
data
 
            
 
          
 
        
 
      
 
        
Public 
cloud 
storage 
 
        
 
          
 
        
 
          

## Page 296

buckets 
(unstructur
ed data; 
currently 
AWS/GCP)
 
      
1. Total data volume (TB/PB) for 
each bucket
 
 
          
2. Data classification category tags 
for every data object (e.g., file) in 
each bucket
 
 
          
3.  
            Data tier composition in 
production public clouds: 
 
            
 
              
% of total production data 
volume containing the most 
sensitive data
 
 
              
% of total production minus 
sensitive data
 
 
              
% of total production data 
volume containing public 
data
 
            
 
          
1. % of total 
production data 
volume in 
production public 
clouds that have 
completed a level 
2 inventory
 
 
          
2. % of buckets in 
production public 
clouds that have 
completed a level 
2 inventory
 
        
 
      

## Page 297

 
        
 
      
As table 4.5 shows, a level 2 data inventory picks up from
where the level 1 inventory left off and examines the spread,
presence, and privacy-sensitivity of data one level deeper
than database instances (by way of columns) and cloud
buckets (by way of objects). This will help answer some of
the previously raised questions around structured and
unstructured data as well.
So far, we have examined data inventories from the
perspective of discovering data and protecting it. However, if
you want easy and expeditious retrieval of data based on
privacy risk, you may want to go even one level deeper by
indexing the data. This is where a level 3 data inventory
becomes critical.
4.7.3 Data inventory level 3
The outcome of a level 3 data inventory is that, given some
identifiers (UUID, name, phone, email, etc.) of a user, the
underlying system should return pointers or references to all
rows in each structured data store or objects in each
unstructured data store that contain the user’s data.
The results and KPIs of a level 3 data inventory are very
similar to what you saw in tables 4.4 and 4.5, with the

## Page 298

addition of an indexed database being the outcome rather
than just tagged data.
This additional step will be time consuming, so you will want
to understand the business forcing functions to help
prioritize the inventory. In my mind, the following use cases
would justify this expense:
Supporting features like downloading personal
data and DSARs
Supporting features like data deletion
Gaining insights about the business
Let’s look at those each in turn.
SUPPORTING FEATURES LIKE DOWNLOADING
PERSONAL DATA AND DSARS
Many data privacy use cases rely on access to account data
on an individual basis, but most storage systems are not
constructed to support such discovery at scale. A level 3
data inventory allows you to support these use cases without
an infrastructure overhaul whereby entire databases would
have to be re-created. This is particularly relevant as new
privacy laws are coming online, which will almost certainly
lead to an increase in the number and scope of user data
requests. We will be looking at DSARs in more detail in
subsequent chapters.
SUPPORTING FEATURES LIKE DATA DELETION

## Page 299

User account deletion relies on access to account data on an
individual basis. Most systems are not constructed to
support that at scale.
Currently, in order to delete data, many companies have a
search mechanism such as a simple row-level Hive search
that locates all records that match a user’s UUID. For all
those rows, data could then be obfuscated and rewritten in
Hive tables.
This is a very limited search:
It searches for records based only on UUID and
ignores the fact that other transactions for the
same user may not contain a UUID.
It searches in specific Hive tables.
It may be very slow.
We could use a level 3 search capability to aid the search by
suggesting the table/row locations containing a vast range of
data points present in database systems several layers deep.
A deletion system backed by a level 3 inventory would also
greatly improve your ability to audit the completeness and
correctness of deletions.
Furthermore, as figure 4.9 shows, even when the number of
breaches goes down, it is possible for bad actors to exfiltrate
more and more data. With data inventory insights, you can
aim your finite deletion tools toward the most privacy-
sensitive data and the locations that contain it. This may
help reduce the likelihood of your sensitive data being

## Page 300

affected by a breach, and it may help reduce the impact of
such a breach were one to occur.
Figure 4.9 Annual number of data breaches and exposed records in
the U.S. from 2005 to H1 20204
Most engineering leaders will understand that starting the
inventory process early can prevent the buildup of data and
