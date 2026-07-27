---
title: Data Privacy_ A runbook for engineers - Part 5
source: Data Privacy_ A runbook for engineers.md
category: development
---

The entities you share data with may not be as
transparent and honest as you are.
Whoever you share data with could have more
sophisticated abilities than you do to process that
data.
It often takes a while to understand the full
implications of data sharing, so in this case, no
news is not necessarily good news.
Remember these lessons before you dismiss the risk
inherent to data sharing.
5.6.2 Sharing data and weaknesses
As if we have not already seen enough attack vectors for
data sharing, there is ransomware. Ransomware is malicious
software that spreads quickly across computer networks and
encrypts them, holding sensitive documents hostage until
victims decide to pay the hackers.12
Ransomware has a significant impact:
In 2019, ransomware hit 103 federal, state, and
municipal agencies, 759 healthcare providers, and
86 schools and universities.13
Four US cities were hit with ransomware in
December alone.

## Page 380

After seeing Atlanta spend $2.6 million to restore
its systems rather than pay the $52,000 ransom,
many officials have decided that it’s cheaper to
pay the hackers.14
A ransomware attack cost the city of Baltimore
$18 million.
These attacks have only increased in frequency as attackers
realize how weak cyber defense capabilities are and how
much sensitive data companies and governments hold.
The key lesson here is that when you share data with
someone, you are also sharing their security and privacy
weaknesses. And when those weaknesses are exploited, you
will share in the consequences.
Summary
In modern companies, data sharing is a key engine
of growth, engagement, personalization, and just
about every aspect of innovation.
Companies share data with third parties for
endeavors ranging from compliance to advertising
to data quality.
There are several techniques available for sharing
data with privacy controls.
Some of these techniques are inherent to standard
data security requirements, in that they manage
access to data as it leaves your organizational
perimeter.

## Page 381

Other techniques entail obfuscating data and
processing it in ways to contain the privacy harm.
There are also industry-acclaimed techniques (k-
anonymity, l -diversity, etc.) available to measure
the impact of your privacy techniques so as to
assess whether you can safely share data.
Data sharing is one of the most irreversible
decisions a company can make, with discernible
impacts upon the users whose data it is, so
companies should share data very carefully.
The techniques in this chapter are part of a larger
data governance effort, and are successors to the
previous efforts involving data classification and
data inventory.
1 Bennett Cyphers and Gennie Gebhart, “Behind the One-Way Mirror: A Deep Dive Into the
Technology of Corporate Surveillance,” part 3, Electronic Frontier Foundation, December 2,
2019, www.eff.org/wp/behind-the-one-way-mirror#Part3.
2 Cyphers and Gennie Gebhart, “Behind the One-Way Mirror.” The diagram is under Creative
Commons License (https://creativecommons.org/licenses/by/3.0/).
3 Cyphers and Gennie Gebhart, “Behind the One-Way Mirror.” The diagram is under Creative
Commons License (https://creativecommons.org/licenses/by/3.0/).
4 Cyphers and Gennie Gebhart, “Behind the One-Way Mirror.” The diagram is under Creative
Commons License (https://creativecommons.org/licenses/by/3.0/).
5 Stuart A. Thompson and Charlie Warzel, “How to Track President Trump,” The New York
Times, December 20, 2019, http://mng.bz/2joa.
6 Stuart A. Thompson and Charlie Warzel, “Twelve Million Phones, One Dataset, Zero Privacy,”
The New York Times, December 19, 2019, http://mng.bz/1j6q.
7 Joe Lindsey, “Strava’s Heatmap Is Giving Away the Locations of US Military Bases,”
Bicycling, January 29, 2018, http://mng.bz/PWmR.
8 Global Heatmap, Strava, https://labs.strava.com/heatmap/.
9 Latanya Sweeney, “k-anonymity: A model for protecting privacy” (May 2002),
http://mng.bz/J1mZ.
10 “K-Anonymity,” www.cs.cmu.edu/~jblocki/Slides/K-Anonymity.pdf.
11 Kevin Granville, “Facebook and Cambridge Analytica: What You Need to Know as Fallout
Widens,” The New York Times, March 19, 2018, http://mng.bz/q21x.

## Page 382

12 Alfred Ng, “Ransomware froze more cities in 2019. Next year is a toss-up,” CNET,
December 5, 2019, http://mng.bz/7WYQ.
13 Dan Patterson, “Four U.S. cities attacked by ransomware this month,” CBS News,
December 17, 2019, http://mng.bz/mxE8.
14 Ng, “Ransomware froze more cities in 2019.”

## Page 383

Part 3. Building tools and processes
This part will help engineers build point solutions using the
data governance capabilities discussed earlier. Privacy
engineering is aimed at delivering critical verifiable
capabilities to customers of a platform. Many of these
capabilities are technical incarnations of expectations put in
place by regulations. This part will offer hands-on skills to
help engineers meet these expectations.
Chapter 6 will help engineers set up a technical privacy
review process to embed privacy as a technical feature for
the company’s products and services.
Chapter 7 will walk through a detailed architecture for data
deletion, thereby providing a service-based framework for
data erasure. It covers data deletion ranging from account
data to streaming event data. 
Chapter 8 will help readers design a data export capability
so as to meet high-visibility “Data Subject Access Requests”
or “DSARs.”
Chapter 9 offers a sample design for a Consent
Management Platform (CMP) so that businesses can meet
this new requirement that is being enforced by regulators
and corporations.
  

## Page 384

6 The technical privacy review
This chapter covers
What is meant by “privacy reviews”
How companies can split privacy reviews between legal and
technical teams
How technical privacy reviews can be integrated into a company’s
workstream
How the technical privacy review can become more automated
and efficient
Examples of both kinds of reviews (by lawyers and by engineers)
In earlier chapters of this book, you have seen how the
modern development process empowers engineers to build
products without the constraints of process. Adding to this
innovative spirit is the flow of data and the inherent
possibilities and risks. Add in impatient business leaders,
complicated regulators, and a skeptical customer base, and
you have a realistic possibility of products shipping with
privacy issues.
The privacy review process is aimed at ensuring that privacy
risks are addressed before a company releases products or
features. Since the engineers who build the products do not
always appreciate or have the time to understand the
privacy implications of their work, it is vital that there be a

## Page 385

process to ensure scrutiny of these products through a
privacy lens.
Creating a privacy review process is a continuation of the
work we have discussed so far, whereby a company has to
manage how it classifies data, catalogs the data, protects it
using access controls, and processes and shares it over the
course of conducting business. While all the data-centric
privacy controls are critical, ensuring that there is a specific
stage in the development of products where these privacy
controls can be validated and applied is critical. Just as we
know that eating healthy and exercising is critical but often
wait for an annual physical checkup to apply those lessons,
the privacy review process is critical.
This chapter dives deep into this critical step and will provide
tips on how technical leaders with limited resources can
provide this service to their engineers.
Broadly speaking, this chapter is split into five logical parts:
In part 1, you will learn what privacy reviews
mean in the traditional sense. It helps to have this
background even for smaller process-lite
businesses, given regulatory scrutiny and
customer expectations.
In part 2, we will operationalize legal privacy
reviews for two different kinds of development
environments.

## Page 386

In part 3, the reader will learn how to make the
case for a technical privacy review to protect the
customer and the company.
In part 4, the reader will learn how to integrate the
technical review more logistically, by way of
automation.
In part 5, scale and efficiency will be the focus so
as to enable widespread adoption of the technical
privacy review
In part 6, we will look at hands-on examples to
help train our readers in realistic technical privacy
reviews.
Let’s start with the fundamentals: what do we mean by
“privacy reviews”?
6.1 What are privacy reviews?
Before diving deep into the kinds of privacy reviews and how
to create a program to administer them, it would be helpful
to understand what we mean by “privacy reviews.” Modern
interactive products and features are conceived by product
managers, designers, and data scientists; they are built by
software developers and architects; they scale based on
work done by data platform teams and database operatives
who manage data centers and cloud storage systems; and
they are deployed by yet another team of specialists. As you
can probably infer, the innovation process is owned end-to-
end by individuals and teams that specialize in specific
domain areas. In this modern, highly regulated, and risk-

## Page 387

sensitive space, it is imperative that the work of vetting
these products for privacy concerns be owned by privacy
specialists as well.
Since there is no canonical definition of a privacy review,
we’ll define one for this book. A privacy review is the process
by which privacy specialists assess a tech product (or
feature) to ensure adherence to industry standards and
customer expectations.
There are two basic steps in a complete privacy review
process, and they are not always completed in any specific
order.
First, the privacy legal team in the company, which is often
just one attorney with multiple other responsibilities, needs
to critique the products. This review will focus on laws like
the GDPR, CCPA, Brazil’s LGPD, etc., and help ensure that
the products are in compliance with the requirements of
applicable laws.
Second, privacy engineers, who in smaller companies often
have other responsibilities such as security and IT, have to
complete a more in-depth review that focuses on various
aspects of data handling. This privacy review is tricky, since
unlike attorneys, the privacy engineers cannot point to
specific laws that may be violated. And since the technical
review often occurs after the lawyers have given their go
ahead, privacy engineers often have limited leverage and
are accused of slowing down the product rollout, making
process the enemy of progress, and other heresies.

## Page 388

This chapter will explain how smaller and agile companies
that lack the budget and staff of companies like Google and
Apple can craft a privacy review process. These companies
will need to lean on automation to help their innovative
engineers through the privacy review process. This chapter
will also provide several examples of products and features
that can be put through the privacy review process. No book
can teach companies how to come up with a foolproof
privacy review, since innovation often moves faster than the
guardrails; what this chapter will provide is a framework for
a process and several examples to help you build a privacy
muscle so you can prevent and spot privacy issues. This will
help reduce the risk of privacy harms, and over time it will
make the entire company better custodians of customer
data.
DEFINITION A privacy review is the process where privacy specialists assess a
tech product (or feature) to ensure adherence to industry standards and customer
expectations.
Before diving into the process and examples, it is key to
establish some concepts. This book looks at the privacy
review process holistically and covers both the legal and
technical privacy reviews. To that end, we will first look at
legal privacy reviews—the portion of the review process
undertaken by the company’s legal team or outside counsel.
These reviews fall into two specific categories: the privacy
impact assessment (PIA) and the data protection impact
assessment (DPIA). The following subsections will explain
them both in detail as well as how they fit into a company’s
overall privacy review process.

## Page 389

6.1.1 The privacy impact assessment (PIA)
For most companies, the only privacy reviews they conduct
are the ones completed by the legal team. These are often
attorneys with a background in privacy and security, but
more often these are attorneys who have other
responsibilities like litigation, employment laws, etc. As
such, the scope and depth of such a review, called a privacy
impact assessment (PIA), can be somewhat limited. Still, it
is critical to come up with a definition of and criteria for a
privacy impact assessment.
The PIA can be thought of as a decision tool for identifying
and mitigating privacy risks along the following lines1:
What Personally Identifiable Information (PII) a
company and its employees may be collecting from
customers and other users
Why the data is being collected, with clearly
identified and enumerated use cases
The collection, usage, sharing, security, and
storage of this data
A PIA should accomplish three goals:
1. Ensure alignment of design and functional aspects
of the product or feature with the company’s
regulatory and compliance obligations.
2. Determine the possibility and impact of any
privacy risks and the impact of those risks on the
users or customers.

## Page 390

3. Evaluate protections and alternative processes to
mitigate potential privacy risks and especially help
ensure that privacy protections tied to specific
geographies are applied. Quantify remediations
and changes to the product design and
requirements to minimize the likelihood and
impact of privacy harms, and view these changes
through the lens of countries, regions, etc.
It also helps to establish clear criteria for PIAs. For example,
a company should conduct a PIA when it is
Developing or obtaining any new technologies or
systems that handle or collect PII. This distinction
is critical, since companies often acquire and
merge new tools due to mergers and acquisitions.
Creating a new program, system, technology, or
information database that may have privacy
implications.
Updating a system that results in new privacy
risks. These updates could include building APIs or
data crawlers that enhance data collection or
loosening administrative controls that then result
in more engineers having access to sensitive data.
Software systems are rarely static and constantly
change in how they process the user’s data, so the
PIA may need to be a continual process rather
than a “once and done” affair.

## Page 391

Issuing new or updated rules that entail the
collection of PII. Governments and regulatory
authorities often write and interpret new rules on
data and privacy implications. The legal team will
need to provide guidance to engineering teams
accordingly.
The PIA is just one part of a company’s process to check for
privacy controls. Whether the PIA is conducted by in-house
legal teams or outside counsel, companies need program or
project managers to follow up on the remediation issues.
This requires the ability to absorb a lot of the context around
the initial gap and recommended remedy, privacy expertise
to understand the options, and credibility to negotiate
prioritization with the engineering teams. In many
companies, there is simply not enough investment to fund
this resource, so PIA teams often depend on an “honor
system” when it comes to having engineering teams fix any
privacy issues. That is why, later in the chapter, we will
identify ways to embed technical privacy review checks,
conducted by specialists outside legal, into the engineering
workflow.
6.1.2 The data protection impact assessment (DPIA)
For many companies, the PIA may be sufficient, but for
others a more elaborate process, the data protection impact
assessment (DPIA), may be required.
According to the Information Commissioner’s Office (ICO) in
the United Kingdom, “A DPIA is a process designed to help

## Page 392

you systematically analyse, identify and minimise the data
protection risks of a project or plan. It is a key part of your
accountability obligations under the GDPR, and when done
properly helps you assess and demonstrate how you comply
with all of your data protection obligations.”2 Under the
GDPR, failure to carry out a DPIA when required may leave
you open to enforcement action, including a fine of up to
€10 million, or 2% of global annual turnover if higher.
Companies often relegate a DPIA to helping create legal
compliance for a specific product. However, if DPIAs are
conducted more strategically and their findings are used to
improve the planning and design of the next set of tech
products, it can help create organizational maturity. As the
ICO points out, this maturity can help the organization as a
whole adhere to a more global standard and avoid bespoke
fixes.
There are four main questions that organizations should
answer in the execution of a DPIA3:
1. How is the personal data being processed and for
what purpose? Rather than answering with a
simple high-level statement, the company should
track what is collected, how the use of that data
produces specific outcomes, how those outcomes
map to the purposes initially identified, etc.

## Page 393

2. Why were specific pieces of data collected? Could
the company have obtained the same benefits and
insights through a different set of data, or fewer
data sets? The goal is to make the case that data
collection was fit for purpose rather than collecting
voluminous data without a directly identified
purpose.
3. What are the specific impacts on the user by way
of rights, freedoms, vulnerabilities, and safety?
This will force the company to look at the data
from the perspective of the user rather than
looking at the user through the lens of the data.
4. How will the company protect its users from
privacy harms? The company will need to find a
way to make the data accessible and usable but in
a way that the privacy harms do not manifest. It is
ideal to have defined controls, operational details,
metric-driven descriptions of how these controls
will address privacy harms, etc.
These four elements will help you focus on the type of data
you are collecting and processing, the risks associated with
data processing, and the likelihood of occurrence and their
impact. A DPIA can help you determine the worst-case
scenarios and prepare for or mitigate them.
NOTE A DPIA is a risk assessment required by the GDPR depending on the nature,
scope, context, and purpose of data processing, and especially for high risk
activities and new technologies where the impact is unknown. It may only be
required for activities that will target EU residents. You should seek advice from
counsel on the applicability of the DPIA for your business.

## Page 394

The International Association of Privacy Professionals (IAPP)
has provided a step-by-step DPIA process that can help
small businesses conduct a DPIA in an expedited fashion.
These steps are listed in figure 6.1. Let’s look at each of
these steps in turn.
Figure 6.1 The data protection impact assessment process
IDENTIFY THE NEED FOR A DPIA
Based on guidance from the EU authorities, “The GDPR does
not require a DPIA to be carried out for every processing
operation which may result in risks for the rights and
freedoms of natural persons. The carrying out of a DPIA is

## Page 395

only mandatory where processing is ‘likely to result in a high
risk to the rights and freedoms of natural persons’ (Article
35(1), illustrated by Article 35(3) and complemented by
Article 35(4)). It is particularly relevant when a new data
processing technology is being introduced.”4
Per the IAPP template, this is the time to “Explain broadly
what the project aims to achieve and what type of
processing it involves. You may find it helpful to refer or link
to other documents, such as a project proposal. Summarise
why you identified the need for a DPIA.”
It is here that the privacy review process needs to be seen
as part of a continuum, with a common understanding of
data via the classification and inventory process and a
common understanding of workflows. At this stage, a
company has two choices:
Have the engineers building the new technology
explain what the project seeks to achieve.
Have all-purpose technical leaders (or privacy
engineers) shape the explanation at the design
stage. This would be in an engineering
requirements document (ERD) that would be co-
authored by the engineers building the product
and technical privacy specialists.
I advocate the latter approach, as you will see shortly. Either
way, it is critical that there is a written understanding of the
project, since, as previously discussed, teams that are
focused on their remit often lack the big picture
understanding necessary for a DPIA applicability evaluation.

## Page 396

DESCRIBE THE DATA PROCESSING
As described in the previous subsection, the engineers
building the product should lay out specifics around the data
processing inherent to the change by answering the
following questions:
Nature of data processing
How will you collect, use, store, and delete data?
What is the source of the data? Will you be sharing
data with anyone? You might find it useful to refer to
a flow diagram or another way of describing data
flows.
What types of processing identified as likely high risk
are involved? This is where lessons from chapter 5
are very useful.
Scope of data processing
What is the nature of the data, and does it include
special category or criminal offense data?
How much data will you be collecting and using?
How often will you be collecting the data?
How long will you keep it?
How many individuals are affected?
What geographical area does it cover?
Having a list of these questions is critical since, in my
experience, it is often only when the privacy team asks
questions that engineers and product managers assess the
downstream impact of data collection. Often the data
collection is conducted with a view to feature development
and use engagement. The job of the privacy specialists is to

## Page 397

create use cases and scenarios whereby the privacy
implications are well understood.
DESCRIBE THE RELATIONSHIP WITH THE USER
Having understood the overall scope of the work and the
flow or processing of the data, it is critical that the DPIA dive
into the impact upon the user. As we have discussed before,
privacy is highly contextual, so understanding each
technology change and data flow in relation to the user is
important.
Some questions to help assess this, as recommended by the
IAPP, are as follows:
What is the nature of your relationship with the
individuals? This relationship could include
customers, non-registered users, etc.
How much control will they have?
Would they expect you to use their data in this
way?
Do they include children or other vulnerable
groups?
Are there prior concerns over this type of
processing or security flaws? Given the constant
swirl around privacy concerns, it is helpful to draw
parallels because they could help advise on
mitigation efforts.

## Page 398

Is it novel in any way? In other words, is this
different from an existing expectation the user
would have?
What is the current state of technology in this
area?
Are there any current issues of public concern that
you should factor in? There may be implications
around fairness, for example, which is a topic of
discussion at the present time.
Are you signed up to any approved code of
conduct or certification scheme?
What do you want to achieve? It is helpful to
itemize and quantify these outcomes, since
engineers often have an approach loosely summed
up as “let’s collect data and we will find a use for it
later.”
What is the intended effect on individuals? What
are the benefits of the processing for you, and
more broadly?
CONSULTATION
In this step, the engineers building the product and the
privacy specialists will need to list specific steps they will
take to manage the privacy risks. The following points
should be addressed at this stage:

## Page 399

Describe when and how you will seek individuals’
views, or justify why it’s not appropriate to do so.
In other words, the innovators will need to explain
how they have notified users impacted by the
technology change. We will cover aspects of this in
chapter 9.
Who else do you need to involve within your
organization? Do you plan to consult information
security experts, or any other experts? This is a
critical step, since many privacy harms can be
mitigated using access control tools that security
teams may already be using, such as multifactor
authentication.
Describe compliance and proportionality measures;
in particular,
What is your lawful basis for processing?
Does the processing actually achieve your purpose?
Is there another way to achieve the same outcome?
How will you prevent function creep?
How will you ensure data quality and data
minimization? What information will you give
individuals?
How do you safeguard any international transfers?
CONDUCT THE RISK ASSESSMENT
If you follow the data governance steps I have laid out so
far, the risk assessment process should be relatively
straightforward, since it is based on an understanding of the
data in the abstract and the privacy risk posed by the

## Page 400

specific change. The IAPP provides a handy template that I
have modified in table 6.1.5
Table 6.1 Privacy risk assessment format

## Page 401

 
        
Describe the 
privacy risk and 
impact on users
 
      
 
        
Likelihood
 
      
 
        
Severity
 
      
 
        
Quantified risk 
on a scale of 1–
100
 
      
 
        
  
 
      
 
        
  
 
      
 
        
  
 
      
 
        
  
 
      
 
        
  
 
      
 
        
  
 
      
 
        
  
 
      
 
        
  
 
      
 
        
  
 
      
 
        
  
 
      
 
        
  
 
      
 
        
  
 
      
 
        
  
 
      
 
        
  
 
      
 
        
  
 
      
 
        
  
 
      
The list of risks will provide the privacy team and engineers
a clear-eyed, ranked, and quantified view of the privacy

## Page 402

impacts of the innovation being proposed, thereby
presenting clear choices on fixes and next steps.
IDENTIFY RISK MITIGATION MEASURES
Having enumerated the risks, you now need a similar
template for the measures you’ll take to manage the risks
and remediate them. Table 6.2 provides such a template,
courtesy the IAPP.
Table 6.2 Privacy risk management format

## Page 403

 
        
Risk
 
      
 
        
Mitigat
ion 
option
s
 
      
 
        
Risk status 
post-mitigation
 
      
 
        
Residual risk
 
      
 
        
Outcome
 
      
 
        
  
 
      
 
        
  
 
      
 
        
Eliminated/red
uced/unchang
ed
 
      
 
        
Low/medium/
high
 
      
 
        
Change 
approved or 
declined
 
      
 
        
  
 
      
 
        
  
 
      
 
        
  
 
      
 
        
  
 
      
 
        
  
 
      
 
        
  
 
      
 
        
  
 
      
 
        
  
 
      
 
        
  
 
      
 
        
  
 
      
 
        
  
 
      
 
        
  
 
      
 
        
  
 
      
 
        
  
 
      
 
        
  
 
      

## Page 404

The last two steps, of conducting the risk assessment and
identifying mitigation steps, are often deemed onerous by
companies, especially since they are often the last step
before going live. Engineers and product managers often
believe that a consultation is enough, and they can be overly
optimistic about being able to manage privacy harms. This
dynamic makes these last two steps seem like a blocker,
even though they are critical from a privacy and trust
perspective. However, an existing data governance program
can help accelerate them. Additionally, audits and other
compliance activities will require such documentation, so it is
helpful to build these processes and habits at least for high-
risk projects. Finally, in the event that there is a breach or
some other privacy incident, and questions like “why did we
not see this coming?” come up, having risk assessment and
risk management documentation can help accelerate the
work of the incident response teams and post mortem.

## Page 405

Figure 6.2 The legal privacy review in the traditional software
development process
6.2 Implementing the legal privacy review
process
Let’s now look at the privacy reviews conducted by the legal
team. Figure 6.2 shows a traditional development process
followed at many companies. Note that both figures 6.2 and
6.3 are oversimplified and may not cover all use cases.

## Page 406

In figure 6.2, you can observe how the needs of the
customer feed into the company’s core mission; the mission,
in turn, helps define the quarterly goals. The goals enable
product managers and business leaders to define the
requirements and specs for the products, which in turn, the
engineering teams build. The products, once built, go
through testing and reviews and are then released.
Given the relatively smaller size of legal teams as compared
to engineering teams, the legal reviews (including the PIA
and the DPIA) can occur after all the development and
testing is complete. That way, the legal team does not end
up reviewing products that may end up changing anyway.
The process, as the figure illustrates, is fairly linear and
predictable. The tight alignment between the customer, the
company’s strategic goals, and the engineering development
could make the privacy reviews easier to manage and scale.
Teams may be able to use some of the same processes and
alignment to track the privacy reviews that they use for
software testing, release management, and the like. The
upshot is that the legal privacy reviews occur at the end of
the development process.
However, with the onslaught of the agile and scrum
revolution, the development process has become more
susceptible and amenable to disruption. Figure 6.3 shows
what a modern innovative development shop might look like.

## Page 407

Figure 6.3 The legal privacy review in the modern agile software
development process
Figure 6.3 shows how there may be several products being
developed that follow the traditional development process.
This does not change the legal privacy review process, since
the attorneys may still wish to conduct their privacy risk
assessments after product development is complete but
before it ships. However, the collective volume of these
products may overwhelm the review and testing resources.
Additionally, modern companies have adopted a startup
mentality whereby developers are empowered to push their

## Page 408

ideas and iterate in byte-sized increments. These may be
ideas that deviate from, and over time help expand, the
company’s customer imprint and core mission. As you can
see in the diagram, several ideas could eventually become
products without adhering to the company’s core mission in
the traditional top-down way. When such features and
products make it to the review stage, some of the
assumptions that otherwise help accelerate testing and
reviews may fall apart.
This poses several problems with the legal privacy review
process:
There are high volumes of proposals, and not all of
them of consistent quality.
There is a lack of context for attorneys, since not
every product adheres to a top-down process.
You would be right to assume that there could be tension
between quality and throughput in such a scenario, when it
comes to privacy reviews.
As a company hits its stride in growth and user engagement,
engineers building products and privacy reviewers alike may
find that operationalizing the privacy review process at the
end of the development cycle does not scale, either from a
quality or a quantity standpoint. The volume of work means
that it is vital to innovate the privacy review process. The
next section will provide a business case for a technical
privacy review as part of the development process rather
than just depending on the legal review.

## Page 409

6.3 Making the case for a technical
privacy review
Since privacy and its attendant compliance requirements are
still fairly new, too many corporate leaders feel like the legal
review alone is fairly sufficient. This section will help you
make the case as to why the legal reviews are necessary but
insufficient and why technical privacy reviews are critical to
protect your company and customers.
6.3.1 Timing and scope
A key reason why privacy reviews orchestrated by the legal
team are insufficient to protect your customers is the timing
of when such reviews occur in the product development
lifecycle. You saw in the previous section that legal privacy
reviews occur at the end of the development process. This
makes for two theoretical efficiencies:
Engineering designs and specifications undergo
changes, and attorneys often prefer to assess the
finished product for privacy risks. This is seen as a
more prudent expenditure of resources, rather
than assessing in-flight products that may then
undergo revisions that render previously dispensed
advice redundant.

## Page 410

Attorneys can look at several finished products at
once and make judgments based on previous
experience and current context (customers
impacted, type of data, location where the product
will be released, etc.) regarding which products
they can review, while the others do not get
reviewed. This methodology allows the company’s
attorneys to make sure that the most critical and
sensitive products go through legal scrutiny, and
possibly are blocked before they go out the door. It
also means that some products will not get
reviewed, given bandwidth constraints. This
approach has a significant disadvantage: attorneys
may make decisions on what to review without
understanding all the technical details, since they
were not part of the incremental development that
occurred. It is often impossible to make a
judgment about the privacy risk without knowing
the context of how the product evolved.
The legal privacy review is inhibited not because attorneys
or legal teams do not care about privacy. The timing of such
reviews is governed by the ratio of engineers to attorneys,
whereby there is a culling of what makes the cut for a
review and when. The process is therefore not adequate,
given the complexity of modern engineering and the
ramifications of data-driven innovation.
Besides the timing of the review, there is also the matter of
how the scope of the legal privacy review is somewhat
circumscribed. Figure 6.4 shows how the legal PIA or DPIA is

## Page 411

a subset of the overall work required when it comes to
privacy reviews.
Figure 6.4 Legal privacy reviews and their limitations
In figure 6.4, the large circle shows the full scope of privacy
issues that the review process should address, ranging from
legal reviews to complex technical issues that must be
addressed before products can ship. The second circle shows
the number of privacy reviews a legal team may be able to
undertake, based on their staff. The third, and smallest,
circle shows the amount of technical depth the attorneys are
able to bring to the projects they do review.

## Page 412

The questions cross-functional leaders need to ask are as
follows:
What if a high-risk feature doesn’t get reviewed on
account of bandwidth or technical depth?
If an attorney were to find an issue with a feature
at the eleventh hour, the only choices would be to
block the release or ship it with the risks intact.
Why not intercept the feature earlier in the
pipeline and imbue privacy at that stage?
6.3.2 What the technical review covers that the legal
review does not
As already stated, the recommended privacy process for
today’s companies requires a technical assessment as well.
Whereas legal privacy reviews focus on regulatory
compliance, technical privacy reviews focus on technical
implementation details, data flows, and other aspects of how
the tech products are built and designed. The goal for these
reviews is to assess the downstream impact upon the user,
look for potential harms, and put in place remediations.
Therefore, the legal privacy review—the PIA or the DPIA—is
a useful resource from a due diligence standpoint, but to
secure customer trust and provide technical coverage for
privacy risk, it is vital that privacy engineers who have a
technical background are part of the product process before
development work begins.

## Page 413

Figure 6.5 explains at a high level the difference between
privacy reviews when conducted by attorneys via the PIA or
the DPIA process and the technical privacy reviews
conducted by privacy engineers.
Figure 6.5 Legal privacy reviews versus technical privacy reviews
The difference between the two reviews lies in the
framework and depth. The legal team will use regulatory
frameworks to ensure compliance. For example, during their
review, the legal team may ask questions like these:
Is the data to be collected to be used only for a
specified purpose?
Will the data collected be used for anything other
than the specified purpose?
The goal behind these questions is to ensure that there is an
unbroken link between the expectations of laws like GDPR,

## Page 414

the privacy disclosures of the company, and the designs and
specifications being put forward by the engineers. However,
there is no way for the legal team to look under the hood
and validate that some rogue engineer is not making
multiple copies of the data, one of which is queried by a
different team and another of which is available via an API to
a third party that has not been vetted for privacy practices.
Often, engineers neglect to mention these details in
documentation that they put together in a rush for the legal
review, and just as often they forget to put in place controls
to check for privacy violations after the product ships.
Therefore, the privacy reviews conducted by the legal team
are a necessary but insufficient resource for building privacy
by design into your engineering and innovation processes.
The technical privacy reviews help address this gap. In the
technical privacy programs I have shaped, the technical
privacy specialists collaborate with engineers and product
managers at the whiteboard phase—when the product or
feature is being designed. The privacy specialists make sure
that every blueprint, product specification, and engineering
design accounts for privacy protections. So, for example, the
technical privacy review may prompt questions such as
these:

## Page 415

What data is being collected?
How much of the data is structured versus
unstructured (JSON blobs, XML, etc.)?
Where are you detecting it? At the edge layer? In in-
memory databases like REDIS? In low-latency
databases like Cassandra? Or at the tail end of the
pipeline in the data warehouse?
What does access control look like for each of
these databases?
Are you using encryption? If so, is it point-to-point
encryption? Or is it encryption at rest, while the data
transport occurs in the clear with the data being
unencrypted?
What does the key management system look like?
Are we using keys such that ML algorithms and fraud
analysis algorithms can access the data but others
cannot?
Is there multifactor authentication? If so, are we
using tools like Okta, OneLogin, or Ping? Or is there
a homegrown solution?
What does auditing for access to this data look
like?
Are the audit logs written in real time or via batch
processes? This can be critical in timely
determination of inappropriate access and blocking
insider risk and third-party risk?
Are the audit logs tamper-proof?
What does the retention period for these audit logs
look like? How is it consistently enforced?

## Page 416

The technical privacy review will look at the product design
and specs in much more detail and elicit information that
engineers often forget to specify in the documentation. This
in-depth review is the connecting tissue between the legal
compliance imperative, the customer trust imperative, and
the engineering implementation.
A colleague of mine, who is an attorney, recently remarked
that attorneys can offer “privacy by defense,” while privacy
engineers can offer “privacy by design.” Attorneys can
defend against discernible and visible privacy harms, while
engineers can build privacy controls into the design. The
upshot is that we need both kinds of reviews to protect both
the company and the users.
NOTE The legal privacy review offers privacy by defense while the technical privacy
review offers privacy by design. Both are irreplaceable parts of preventing privacy
harms and mitigating privacy issues in products and features.
Figure 6.6 provides a condensed representation of the
differences between the legal privacy review and the
technical privacy review. As you can see, a given
engineering product can get varying levels of scrutiny in the
privacy review process depending on who is conducting the
review.

## Page 417

Figure 6.6 Legal privacy reviews versus technical privacy reviews
As figure 6.6 makes clear, you could have the same
engineering product get varying levels of scrutiny in the
privacy review process depending on who is conducting the
review.
HOW TECHNICAL PRIVACY REVIEWS HELP The Technical Privacy Review is
the connecting tissue between the legal compliance imperative, the customer trust
imperative and the engineering implementation.
So far, we have examined the privacy review process
conducted by the legal team by way of the PIA, we’ve looked
at the DPIA, and we have touched on the technical privacy
review.
Next we will look at how technical leaders can incorporate a
more technical privacy review in the process and front-load
it so as to ease the load on the legal privacy review and
scale the overall process better.

## Page 418

6.4 Integrating technical privacy reviews
into the innovation pipeline
Understanding how technical privacy reviews help fill the
gaps left by the legal privacy review is helpful, but technical
leaders need to understand how to fit such reviews into the
workflow as well.
6.4.1 Where does the technical privacy review belong?
To help ensure that you can identify and remedy privacy
gaps, the technical privacy specialists will enter the picture
in two places:
At the early stage, while the product is being
imagined and designed. Here they will identify
areas of possible privacy risk and embed technical
controls like the ones we have looked at
(classification, inventory, encryption, obfuscation,
etc.) into the design and product features.
Alongside the PIA and the DPIA, where they can
ensure that the aforementioned privacy controls
were successfully implemented as well as assist
the lawyers in the legal privacy process.
In this fashion, the technical privacy review will help provide
technical depth and scale to the overall privacy review
process.

## Page 419

Figure 6.7 shows how technical privacy reviews can be
added to the traditional development process. Technical
privacy specialists can iterate on the product spec with
engineers and ensure that privacy controls are embedded
into the design before engineering and testing can begin.
They can then partner with the attorneys for the legal
privacy review prior to product release.
Figure 6.7 Technical privacy reviews in a traditional engineering flow
Figure 6.8 shows similar efficiencies available by
incorporating the technical privacy review in the more agile
development process.

## Page 420

Figure 6.8 How technical privacy reviews could fit into an agile
development process
As you can imagine, ensuring that multiple concurrent agile
efforts are integrated with technical privacy controls at the
design stage will help accelerate the subsequent verification
prior to release and significantly accelerate the legal privacy
review as well.
Now that you have a clear idea how a technical privacy
review fits into the overall development process, we can now
focus on the mechanics of how to incorporate products into

## Page 421

such a review such that you can address privacy risks
without creating unnecessary process burdens.
6.4.2 How to implement a technical privacy intake?
Engineers will need clear guidelines on how to integrate their
work into the technical privacy review process. Given the
heightened visibility around privacy, companies need to
establish objective criteria to drive the level of scrutiny
applied on individual requirements documents, often called
engineering requirement documents (ERDs). Figure 6.9
shows what such a form could look like.

## Page 422

Figure 6.9 Sample technical privacy review questionnaire
As you can see in figure 6.9, a lot of information is
requested in this questionnaire. This enables the privacy
team to rank the privacy risk for a specific ERD based on
variables like these:
Business function

## Page 423

Data collected, stored, and shared based on risk
tiers
Any vendors that may be in the picture
Whether machine learning will be applied
Regions where data will be collected or stored
Let’s look at a few of these points in more detail to see how
the privacy review process is part of an overall data
governance strategy.
First, asking engineers to enumerate the data they intend to
collect and use forces them to understand their own data
flows and APIs, and it will help avoid the kinds of surprises
that often elude legal reviewers. The effectiveness of this
step depends on whether the company has correctly
classified and catalogued its data, as we have discussed. At
the backend, the entries from the engineers can be used to
adjudicate the level of privacy review required.
Similarly, if the data being collected is to be used for
machine-learning modeling and analysis, it is possible that
the data will need to be retained for an extended period of
time.
Finally, if the data is being collected from privacy-conscious
regions like Western Europe, that may increase the privacy
risk and require a more detailed technical review as well.
Once the engineers enter their values and click the Create
button on the form, the outcome might look something like
figure 6.10.

## Page 424

Figure 6.10 Technical privacy review questionnaire sample outcomes
Figure 6.10 shows two examples of how an engineer could
fill out the sample questionnaire. In the first example, a
large amount of sensitive data is collected and at the
individual user level, with the potential of being used for
machine learning. Accordingly, the corresponding JIRA ticket
shows a high level of sensitivity.
I have configured my processes to allocate a privacy
engineer to co-author the ERD with the engineer so that
there is some privacy oversight in the entire design from the
start. This is critical, since once data enters the system, you
need to classify, catalog, and protect it, and that gets
expensive. The technical privacy review is aimed at reducing
this expense by limiting the collection of data to legitimate

## Page 425

needs. This helps both from a compliance standpoint and a
user trust standpoint.
This process can also be configured to create a privacy
section in the ERD that the engineers and privacy reviewers
can update on an ongoing basis, as risks are discovered and
mitigated. Figure 6.11 shows how the technical privacy
review process could work at the backend.

## Page 426


## Page 427

Figure 6.11 Technical privacy review backend workflow
The first question about data usage, “Do you collect, use,
update, share personal data?” could trigger a privacy review,
and the additional details could be used to populate the ERD
privacy section. It stands to reason that answering “yes”
would trigger a technical privacy review, so I often advise
engineers to use synthetic data or fake data to conduct tasks
that do not require product customer data. That way, they
can still perform several activities without the added risk of
collecting, accessing, sharing, and storing customer data.
This discipline will help reduce overall privacy risk—after all,
it is hard to misuse data you don’t collect. It will also help
reduce security risk—if there is a breach, it is hard to end up
losing data you don’t have. It will also help reduce costs in
storing data and reduce the strain placed on your system by
calls to delete this data.
The way you word the questions that drive the technical
privacy review can help send subtle signals and offer soft
training to your engineers. This is another opportunity to
embed privacy by design in your company.
The second set of questions in figure 6.11, in the Triage and
JIRA Creation section, will help determine the level of
technical privacy review that the product or feature will
undergo. In figure 6.10, you saw how individualized data led
to a much deeper review than the aggregated data. The
responses to questions in this section will help privacy
engineers determine the level of privacy review required.
Much like the first question, there is a subtle nudge to
engineers here as well. Engineers can avoid using sensitive

## Page 428

data or reduce the storage and sharing, and consequently
reduce the intensity of the technical privacy review.
The third section of figure 6.11 shows the requirements
document with the data entered in steps 1 and 2. This
section captures the areas of the product that need to be
scrutinized by the technical privacy team. Collecting the
privacy findings in the requirements document serves
several purposes:
Engineers and privacy specialists can easily
reference the document and debate the validity of
any privacy concerns and proposed remediations
from the same set of facts.
Having a constantly updated privacy section helps
avoid a disconnect whereby product features are
neatly maintained while the privacy fixes are
tacked on at the end. This section sends a
message that privacy is on par with the remaining
product features.
When the legal team takes up the project for their
PIA and DPIA, they can use this section and the
context the privacy specialists have acquired as
background. This greatly expedites the PIA/DPIA
process and improves the relationship between
privacy legal and engineering as well.
Based on my experience, I have two key insights to offer for
the technical leaders at small companies who will champion
privacy reviews. Readers may disagree or seek to improvise,
but I wanted to offer them for consideration:

## Page 429

It is critical that engineers not be pre-educated on
how their input maps to the privacy review
process. If engineers were to become aware that
answering “No” to the data collection question
could help them bypass the technical privacy
review, you may run the risk of engineers trying to
game the system so as to expedite their review.
It is equally important that the ERDs have a
privacy section, as shown in figure 6.11. This will
help ensure that the privacy impact of the ERD will
be catalogued and managed on an ongoing basis
rather than as an afterthought right before
release. This will help avoid two problems that
impede the legal PIA process. It will help
accumulate all the privacy findings from the
beginning, rather than creating chaos at the end
and having privacy become a “blocker.” Second, if
there is a section dedicated to privacy in the ERD,
it makes the engineers think of privacy as a
feature rather than an add-on.
Let’s now look at the end to end process for an ERD
technical privacy review and see how the work can be
tracked in a scalable fashion. Figure 6.12 shows the process.

## Page 430

Figure 6.12 Technical privacy review process workflow
The process in figure 6.12 shows the essential steps:
Creation of the ticket
Initial reviewer questions
Question-answer loop
Reviewer outcomes with suggested privacy
controls
This process is especially critical, because in a real
workplace and in small companies, multiple engineers may
iterate on the product coding, and multiple privacy reviewers
could cycle through as well. Having this contextual continuity
is critical so that your technical privacy review will produce
consistent outcomes regardless of ownership. This provides

## Page 431

a process that is easy to follow, is scalable, and will embed
technical privacy reviews into the design of your products.
You have so far seen how to integrate the technical privacy
review into your business. The fact remains, however, that
small companies could find this burdensome and expensive.
Engineers may try to work around this new expectation, and
that may lead to privacy harms. It is therefore critical to find
efficiencies when possible, and the next section will offer
some ideas.
6.5 Scaling the technical privacy review
process
Even with all the ingenious data governance in place, there
may still be more ERDs than there are technical privacy
reviewers. As such, it behooves cross-functional leaders to
provide automated recommendations as much as possible
for behaviors that are repeated across multiple ERDs.
This section will provide tips for automating
recommendations based on information provided by the
engineers.
6.5.1 Data sharing
If the author of the design and specification states that they
will be sharing customer data with third parties, providing a
handy checklist can help them avoid problems and make

## Page 432

sure that any irreversible movement of data can be done
correctly from the start.
The following example data-sharing checklist is purely for
instructional purposes. It would need to be customized,
based on context and use case.
Use an approved tool for data sharing.
API/Box is the most preferred way of sharing.
You should not use Google Drive/Sheets/Docs for
sharing unless it is approved on a case-by-case
basis.
If you must share data with S3 (e.g., regulator
requires it), then perform client-side encryption and
limit retention periods.
You should never use email to share PII, like a Social
Security number.
For Box:
The file should not be publicly accessible. It should
be password protected.
Retention is set to one week, unless client-side
encryption is supplied.
You should use an employer enterprise account to
share files, and not your personal Box account.
For API:
Secure tokens are used for authorization.
Built-in authentication and authorization using oAuth
2.0.
Rate limiting and timeout need to be configured.

## Page 433

For SFTP:
Encrypt personal data using CMS (RFC 6032) with
the recipient’s public encryption key. The receiving
party may generate an RSA 2048 bit public/ private
key pair and share it with Uber using a X509
Certificate.
Private keys should be securely created and
managed. Align with our crypto standard to create
the keys. Keys must be rotated every three months.
6.5.2 Machine-learning models
As companies increasingly rely on efficiency and automation,
they often create programs to perform tasks otherwise
completed by human beings. Machine learning (ML) is an
increasingly popular solution in automating tasks that
previously required manual input by a human user. ML
usually requires large quantities of data in order to develop
properly trained models, so here I will briefly explore the
implications of ML for privacy.
MACHINE LEARNING AND DATA
As an example of ML usage, governments may use ML to
process appeals for traffic citations. If someone gets a traffic
ticket (or a fine) for going over the speed limit, it is
reasonable in many cases that they would appeal the fine by
demonstrating past good behavior and promising better
behavior in the future. Let’s assume that a major metropolis
were to implement such a system. The key ingredients of
such a system would include the following:

## Page 434

Accuracy—The data must be correct, in terms of
the past records for the person appealing, the
speed details, etc.
Latency—The response must be quick, since the
person appealing may call or email repeatedly if
they don’t get a response.
Equity—If two people have the same chance of
repeating (or not repeating) the offense, the
outcome for their appeals must be the same.
This system would need to work at scale and produce results
for vast amounts of data—remember, this is a big city with
possibly thousands of appeals every day. In that context,
data that the city collects would be used as a foundation for
assessing the validity of future appeals.
Existing citations and appeals could be grouped into
categories like the following:
Folks who were 5 mph over the speed limit and
repeated their offense
Folks who were 10 mph over the speed limit and
repeated their offense
Folks who were 15 mph over the speed limit and
repeated their offense
For any new driver who gets a citation, the system would
match their appeal against one of the preceding categories.
Then, within each category, the process of looking for the
closest match would continue, based on other variables (for
example, based on age, part of the city where the citation

## Page 435

was issued, etc.). Upon finding the closest match, the
system would check how that match fared upon appeal. And
based on that outcome, the system would determine the
likelihood of a future violation for the current appellant.
The system would then either
Keep the existing fine
Reduce the fine
Waive the fine
This is a very simple example and I expect real appeals
systems work differently, but any system where subjective
and contextual human decision-making is replaced by
automation will require a significant amount of data. Given
the potency of personal data (in this case, driver’s license
number, car plates, location, etc.) privacy controls would
need to be in place to protect the user’s data privacy.
MACHINE LEARNING, DATA, AND PRIVACY
In order to collect data for ML in a privacy-centric
framework, it is critical that the data be obfuscated so as to
avoid identifying or profiling individual users. The following
checklist provides some useful guidelines:
Remove attributes—Any attribute that is not
needed for the purpose should not be collected,
read, or shared. For example, if date of birth is not
needed for your service, do not collect or copy it.

## Page 436

Granularity—Any attribute that is not needed at a
granular level must be aggregated. For location
data:
IP address—Zero out the last octet of IP addresses
wherever possible. An IP address may have been
collected from the vehicle’s security system.
GPS lat/long—If possible, use a cell ID or landmark
instead. If precise location is needed, minimize the
decimals used (max 3 decimals). If 2 decimals or
fewer are used, the GPS may not be associated with
a precise location (thereby reducing the GPS data’s
privacy sensitivity). Three decimals gives about 100
meter accuracy compared to 5 decimals, which gives
1 meter accuracy. The less accuracy, the better.
Timestamp—Aggregate to 24 hours; if that’s not
possible, aggregate to 1 hour; if that’s not possible
(the worst case) aggregate to 15 minutes.
Pre-aggregation—Pre-aggregate data, and use a
cohort size of 18, or at least 11–20 when
aggregating trips to reduce the risk of re-
identification. This means there are at least 11–20
individual trips that are indistinguishable from one
another based on the combination of datetime and
location.
Volume—Use less data where possible. For
example, if you can train your modeling data (for
machine learning, for example) with 50,000
records, do not collect a million.
In order for these checklists to be useful, it may help to
write bots or other programs that inject this content into the

## Page 437

ERD JIRA tickets so that the engineers can check against
them and then submit the ERD for privacy review. This will
help create a consistent process and save time for the
engineers and technical privacy reviewers alike.
Additionally, providing engineers with this information
without them having to hunt for it in large databases will
create a more agile training approach for privacy. For small
companies that do not have training budgets and operate on
lean margins, such economies are critical and over time will
help build privacy not just into the design of the products,
but into the company culture as well.
6.6 Sample technical privacy reviews
Having put in place a process to scale the technical privacy
review process, it is now time to learn by example. This
section will feature several use cases of real-world software
development tools that can be improved for privacy risks by
the review process. Given that this chapter touches on both
the legal PIA and DPIA process as well as the more in-depth
technical privacy review, we will first look at a privacy review
through a purely legal lens and see what sorts of issues a
PIA may uncover.
6.6.1 Messaging apps and engagement apps: Do they
connect?
Let’s imagine that your company is in the business of
building applications that allow users to communicate and

## Page 438

engage with each other. As your company grows,
1. It builds a messaging platform that lets users build
profile pages for themselves or their businesses.
2. The platform then expands to let these users
create groups and communities to engage with
like-minded individuals. The engagement platform
is geared toward users with high-speed internet
and a culture where information-sharing is
encouraged.
3. The company then acquires another smaller
company that lets users send each other messages
in an SMS-like fashion, except these are sent over
the internet. The messaging app is geared towards
locations and countries with possibly limited
internet connections, and takes low bandwidth to
operate.
NOTE This example contains analysis based on my understanding of regulations,
but it should not be construed as legal advice. The analysis here is for instructional
purposes only.
The goal of the business is to have users on the engagement
app eventually also use the messaging app, thereby
competing with SMS and other methods of communication.
Correspondingly, having onboarded users to the messaging
app in other locations, the business aimed to gently nudge
those users to its more engagement-driven app as well. The
cumulative body of users would drive more data collection
that could be used for analysis to help build other products
and monetization.

## Page 439

As the company builds out its authentication protocols, the
team building the identity database produces an ERD that
makes a representation that it’s technologies would not
match accounts opened on the engagement platform with
accounts opened on the messaging platform unless the
users had provided explicit consent.
Upon the completion of the ERD, the identity team decided
to complete the DPIA process. During this review, the
privacy legal team found that the identity team was using
phone numbers to validate the accounts for both the
engagement platform and the messaging platform. Phone
numbers can serve as a useful tool for multifactor
authentication and thereby prevent attacks like fraudulent
account creation or account takeover attempts. Collecting
phone numbers as a precondition to letting users create
these accounts is a valid security use case. However, the
DPIA revealed that there was no restriction on linking the
phone numbers in the databases for both these programs.
Figure 6.13 Identity databases from engagement and messaging apps

## Page 440

As you can see in figure 6.13, there is overlap in the users
who use the engagement app and the identity app. This is
not a problem—in fact, it is a sign of success that the
company has the same user using two distinct products. This
presents several benefits:
This affords the company customization
opportunities by repurposing data collected from
one app to personalize the user experience in the
other.
A specific user could connect with the same set of
friends on both apps and decide which ones they
wish to engage with in more detail and which ones
they wish to just message once in a while.
If the user gets locked out of one app, the
company could use the other app to unlock them
using the common identity. In figure 6.13, it
stands to reason that 232-333-9092 could help
unlock the same user for both apps.
The preceding benefits, ranging from user convenience to
security, depend on the apps sharing data and user
identities. Based on my experience, most companies may
believe that they will keep user identities disconnected in
two separate databases, as in figure 6.13. However, as the
business grows, the opportunity to grow user engagement,
sloppiness, or bad ethics result in creating “joins” or
“connections” between the two databases. And once the two
databases are joined, it is impossible to disconnect them,
since a lot of downstream processes become acclimated to
having the vast amount of data at their disposal. Often the

## Page 441

join is done using automated scripts and APIs that are
written to extract special insights from the data.
Given the vast amount of merger and acquisition activity
occurring these days, and the vast amounts of data flowing
between countries, EU antitrust regulators believe that
consumer data use rights and promises are important in
analyzing mergers and enforcing competition law.
Inadequate transparency around data could affect a
company’s prospects adversely. It is vital that engineers
understand that a simple query that runs in mere seconds
could have far-reaching implications, depending on how the
outcomes line up with user expectations.
Given that background, the DPIA findings came back as
follows:
The company needed to update its guidance to
enumerate the use cases where the data present
in the identity database for one app could connect
with the identity in another database.
The company must have a clear workflow to
explain whether the messaging app users
consented to their accounts being combined with
their engagement accounts.
The DPIA process builds on the fact that the company has a
data governance program with an understanding of what
data lives in which database, the impact on user
identifiability, and how that information needs to be
furnished to users.

## Page 442

This example again brings home the point that privacy
reviews, whether they are technical or legal in nature, need
to be part of a systematic privacy program so as to protect
both the business and its users. Here we saw a possible
tension between privacy and security, where account linking
could protect users but also hurt their privacy. In the next
example, we will examine a similar tension between safety
and privacy.
6.6.2 Masks and contact tracing
In this example, we will imagine a more contemporaneous
situation whereby a care home for the elderly allows family
members to visit only if they wear masks. Given the limited
human contact possible, there are cameras and sensors
outside the facility that will take a photograph of visitors.
Upon detecting a mask, the visitor is allowed to enter. If no
mask is detected, then the visitor is not allowed to enter.
Given the devastation caused by COVID-19, it is not hard to
imagine care homes, schools, companies, and other entities
using tools like these for public health and safety. However,
at the backend, the information collected as part of this
process needs to be handled with care. For example,
Where will the photographs be stored?
For how long will the photographs be stored?
Who will have access to them?
Will the software glean other data about the user?
For example, will the company also store the
timestamp of when the user visited the facility?

## Page 443

What protections and controls exist to make sure
the photo is only used to verify that the user is
wearing a mask and not for other purposes?
As you may imagine, the problem space in this example is
very new, and it is highly unlikely that there are prescriptive
laws to guide a privacy review. Such an initiative needs a
detailed technical privacy review to assess and then manage
the privacy risk.
The technical privacy review could recommend changes such
as the following:
Any images are to be stored in operational
databases like Cassandra for prompt verification
and not in a data warehouse like Hive, where data
is typically retained for a long period of time.
Once an image is used to ascertain the presence
or absence of a mask, the image should be deleted
before any other algorithms can infer details like
facial features that could then be used to identify
the user. Remember, the goal here is not to
identify the user or build a profile, but just to
verify that they are wearing a mask. Part of the
technical privacy review is to advocate for a user’s
privacy protection in a way that laws and
regulations never can.

## Page 444

If the images need to be transferred to cloud
storage for analysis, the technical privacy review
may insist on encryption, since it is possible that
the image could be intercepted in transit, which
could in turn hurt user privacy. This may have the
effect of slowing down verification a bit, but having
this negotiated ahead of time could help make
decisions along the lines of image size. This will
help balance privacy with image quality, thereby
helping achieve both goals. This is the sort of
check a compliance-centric DPIA can almost never
conduct, and that is why a technical privacy review
is critical.
The technical privacy review could suggest a
feature whereby a user could submit their photo
before arriving, and once they receive validation
that their mask is correct, they would then get a
code that they could provide to secure entry. This
would expedite their reunion with family and allow
for health safety and privacy as well. Figure 6.14
shows what that UI could look like.

## Page 445

Figure 6.14 Mask verification software
This is yet another example of how the technical privacy
review process can make for a better user experience,
provide enhanced privacy protections, and avoid a situation
where highly personal biometric data is collected or misused
erroneously, leading to privacy harms and fines. It is almost
impossible to make major design changes and
implementation modifications at a late stage, once
implementation is in full swing, and the deleterious impact
on public confidence is irreversible if photos end up being
leaked.

## Page 446

Having a culture of privacy governance enables cross-
functional leaders to set initiatives like these into the larger
business and societal context. That way, a business can
balance physical safety on the one hand with privacy on the
other.
Summary
Modern companies innovate rapidly and are
powered by data collection.
As part of their overall data governance and trust
offering, companies need to evaluate products not
just from a regulatory perspective but also through
a technical privacy lens.
There are clear differences between traditional
privacy impact assessments (PIAs) conducted by
lawyers, and the more technical reviews conducted
by privacy engineers.
The PIA and DPIA reviews focus on regulatory
compliance and map product and system level
decisions to laws. The technical depth of such
reviews is fairly limited, and these reviews occur
toward the end of the development life cycle.
The technical privacy review can start early in the
process and shape the product design and
technical architecture, thereby ensuring that
privacy controls are baked into the product at the
feature and data levels.

## Page 447

There are ways to integrate and automate the
technical privacy review process that will help build
an overall culture of privacy, make the business
more efficient, and build trust with users.
1. “Privacy Impact Assessments,” Homeland Security, 26 November, 2020,
http://mng.bz/8l7D.
2. “What is a DPIA,” ICO, http://mng.bz/jyoe.
3. Focal Point Insights, “Understanding the Differences between PIAs and the GDPR’s DPIAs,”
Focal Point, January 17, 2019, http://mng.bz/doNw.
4. The working party on the protection of individuals with regard to the processing of personal
data, “Guidelines on Data Protection Impact Assessment (DPIA) and determining whether
processing is ‘likely to result in a high risk’ for the purposes of Regulation 2016/679,” EU,
October 4, 2017, http://mng.bz/9K7r.
5. “Sample DPIA template,” ICO, http://mng.bz/Nxdd.

## Page 448

7 Data deletion
This chapter covers
What is meant when we refer to data deletion
Why companies need to delete data
How modern data collection works
Deleting account-level data
Deleting warehouse data and sensitive data
How to structure data ownership
We have, so far, looked at privacy as a holistic business
differentiator as well as a risk mitigator, involving processes
such as classifying data, building an inventory, sharing data
securely, and conducting technical privacy reviews. Another
key concept in data privacy is data deletion; this is critical,
since most security and privacy risks emanate from data
misuse, leakage, and exfiltration. Chapter 5 provided some
useful techniques for obfuscating data so as to mitigate
privacy harms if the data is mishandled. However, in some
cases, it may be more practical to delete the data altogether,
since the best way to prevent data misuse is to not have the
data at all.
This chapter will walk you through a system architecture for
deleting data in a highly distributed environment. You will
need to adapt what we discuss here to your systems, since
all companies vary in their architecture and data, but this

## Page 449

chapter will provide you with hands-on skills to start this
complex but necessary initiative. You will learn how to
approach operational and archival data from a privacy
perspective.
First though, let’s define data deletion. For the purposes of
this book, deleting data means physically or logically
destroying identifiable user data so that it cannot be
recovered or anonymizing data so that it can not reasonably
be re-identified by anyone, either at your company or
anywhere else, even if it is publicly disclosed.
The act of deletion covers systems ranging from real-time
databases to databases that hold archival data to backup
systems where the company stores data. It is critical that
the engineering coverage of data deletion—in terms of what
data is deleted, how it is changed, and what systems are
impacted—map to any representations (public
commitments) the company makes on data deletion and
retention.
NOTE There are many other legal definitions and interpretations of deletion, but
since this is not a legal book, I will focus on the end result of deletion as defined
here.
Having defined what it means to delete data, let’s move on
to why a company would want to, and indeed must, go
through the process of data deletion.
7.1 Why must a company delete data?

## Page 450

Companies need to delete data so that they can comply with
regulatory requirements, like the ones spelled out in the
GDPR and CCPA.
In Article 17, the GDPR outlines the specific circumstances
under which the right to be forgotten applies.1 An individual
has the right to have their personal data erased if
The personal data is no longer necessary for the
purpose an organization originally collected or
processed it.
An organization is relying on an individual’s
consent as the lawful basis for processing the data
and that individual withdraws their consent.
An organization is relying on legitimate interests
as its justification for processing an individual’s
data, the individual objects to this processing, and
there is no overriding legitimate interest for the
organization to continue with the processing.
An organization is processing personal data for
direct marketing purposes, and the individual
objects to this processing.
An organization processed an individual’s personal
data unlawfully.
An organization must erase personal data in order
to comply with a legal ruling or obligation.
An organization has processed a child’s personal
data to offer their information society services.2

## Page 451

The preceding list is not intended to be interpreted by
engineers, but I’ve included it so that engineers have some
context when they seek guidance from privacy legal on
specifics regarding deletion.
For any company, the legal team typically maintains a
deletion and retention policy that outlines how employees
must implement data protection, retention, retrieval, and
deletion/dissociation methods to comply with existing and
anticipated regulations. The policy exists so that the
company adheres to known regulatory guidelines and
complies with the deletion rights outlined in the company’s
own public-facing privacy policy. This is critical, since
companies often state in their privacy policy how they will
delete customer data once that data is no longer needed.
However, deleting data just because that requirement is part
of a law tends to be a myopic approach. Smart technical
leaders will use privacy regulation as the floor to build on
rather than a ceiling to cap their tooling for privacy. Beyond
the mandatory deletion activities, companies will want to
give users control of their private data. Companies should
only hold private data so long as it serves a business
purpose, and an approach to user privacy that focuses on
data minimization can ultimately be a competitive
differentiator.
Additionally, as companies seek efficiencies in data storage
and improvements in data quality, it is critical that they
identify, automate, and scale data deletion processes and
tools. This chapter will dip into the deletion best practices
that I have learned over the last decade—these range from

## Page 452

how companies collect data to how they build deletion logic
and tooling.
TIP Don’t come up with a deletion strategy just to meet the bar on regulation and
compliance. Deletion offers the opportunity for additional privacy controls, like data
minimization by eliminating spare or redundant copies of data. Deletion is an
example of how you can use the possibility of privacy risk to help broader data
discipline.
However, before we can take such a strategic view, you’ll
need to understand how modern distributed systems work.
At the end of the day, engineers who build and use these
architectures will make decisions that will influence deletion
strategies. It behooves leaders to build these hands-on skills
so they can make intelligent decisions around data collection
and deletion, even if the leaders do not themselves own the
data collection infrastructure or the deletion capabilities.
7.2 What does a modern data collection
architecture look like?
Implementing a deletion process for a modern business is at
once easy and difficult. Data deletion is easy because
deletion is not a new concept. Getting rid of data is
something that companies do all the time. However, locating
that data, understanding how and why data ends up in
different storage locations across the company, deciding how
to prioritize the deletion based on the privacy risk of the
data, and such other details can be extremely difficult for
cross-functional technical leaders, since that information is

## Page 453

not typically documented and not usually understood by a
single person at a company.
Further, even as technical leaders try to locate a target data
set for deletion, more data is being collected, which in turn
makes deletion even harder, since the resources required to
delete the data become that much harder to implement.
Deletion is the quintessential example of a moving target,
whereby how you delete, what you delete, and from where
you delete change constantly.
This section, therefore, will look at modern technical data-
collection architectures. This will enable you to work with
engineers, data scientists, and architects to build a deletion
strategy. These hands-on skills may not match up precisely
with your company’s architecture or processes, but this
discussion should provide enough context for you to apply
them to most situations.
First, we’ll discuss how modern distributed architectures
collect and process data using services, especially
microservices.
7.2.1 Distributed architecture and microservices: How
companies collect data
Every company will have its unique architecture and data
storage capabilities, but most modern companies follow a
microservices-powered architecture. To understand how a
company is to implement deletion, it is critical to understand
how modern data ingestion and storage works.

## Page 454

As you can see in figure 7.1, most companies build their
capabilities not as a single chunk of code but as a
combination of different services. On the far left of the figure
is a load balancer (ELB) that decides how to handle incoming
requests. These requests will include customers trying to use
a company’s website, its app, etc. All those requests come in
real time, sometimes in the millions, and the load balancer
has to line them up and map them to servers that can meet
the needs of the customers.
Figure 7.1 A modern microservices infrastructure
In this simplified use case, the load balancer transfers the
requests to the main API—also often known as the Edge API
or the API gateway—which then decides how to handle the
request based on the nature and urgency of the request.

## Page 455

Typically, behind the Edge API are a series of other smaller
services, called microservices, that handle the customer
requests. For example, if a customer connects to a retail
app, then behind the Edge API layer of the retail app will be
microservices that conduct the activities like the following:
Create a customer’s account
Verify the customer’s identity (login and
authentication)
Show the customer the products available for
purchase
Display the customer’s shopping history
As the customer performs additional activities, microservices
like these collect and, in turn, generate additional data, and
that data ends up in several data stores across the
company’s storage ecosystem.
As you build a deletion strategy and architecture, you will
want to focus on all the services spread out across your
system and perform a lineage analysis of these services and
their owners.
Let’s now look at how companies store and access real-time
data for customer operations.
7.2.2 How real-time data is stored and accessed
A customer’s account data (such as their login credentials,
their most recent activities, their current transactions, etc.)
end up on low-latency and high-availability databases like

## Page 456

Cassandra. This approach renders such data accessible
rapidly, should the need arise to serve the customer. The
data stored in such databases is unstructured, a concept we
discussed in detail in earlier chapters.
Let’s consider how data can be stored in Cassandra.
Cassandra data is stored in multiple nodes (storage
locations). This helps create redundancy, in that if one node
or storage location fails, the customer making the request
(to search for products or make payments, etc.) can still get
assistance.
The upside behind this approach is that if an engineer were
to build a new capability that requires customer data (such
as recommending new products to a customer based on the
last few products they purchased), that capability can access
the data from multiple possible storage locations. This is an
important point, since it is possible that the new capability
may need a dedicated data source because it needs a
constant data refresh. Such a capability might saturate
existing capacity, so redundancy can help prevent such
failures. Additionally, even if a specific node were to fail or
get corrupted, the new capability could still access the
customer data.
Just as understanding the storage and collection of real-time
data is critical, so is understanding the storage of
aggregated data at the data warehouse level, where
engineers working on machine learning and data science
operate. These engineers use the warehouse to derive
insights that could help guide future business decisions. This
is why data tends to be archived for a protracted period in

## Page 457

these data warehouses, and that is where privacy risks often
hide. The next subsection will look at such storage.
7.2.3 Archival data storage
Companies often need to analyze the data they collect so
that they can unlock deeper insights about the business.
This data is often collected in databases that could either be
data warehouses or data lakes, as illustrated in figure 7.2.
Figure 7.2 Data warehouses and data lakes
As figure 7.2 shows, data warehouses and data lakes are a
rich store of data that can provide the company’s data
analysts and data scientists with the historical aggregated
data needed to drive business decisions. Data lakes and data
warehouses are both widely used for storing data, but they
are not interchangeable terms.3 A data lake is a vast pool of

## Page 458

raw data, the purpose of which is not yet defined. A data
warehouse, on the other hand, is a repository for structured,
filtered data that has already been processed for a specific
purpose.
The two types of data storage are often confused, but they
are much more different than they are alike. In fact, the
only real similarity between them is their high-level purpose
of storing data. The distinction is important, because they
serve different purposes and require different sets of eyes to
be properly optimized. While a data lake may work well for
one company, a data warehouse may be a better fit for
another.
For the purposes of this book, the distinction between a data
warehouse and a data lake is not as critical as the idea that
these are both repositories where data collected by
microservices is aggregated from real-time systems like
Cassandra and MongoDB. These archival stores—be they
warehouses or lakes—consolidate and centralize data that is
collected upstream. They are a meeting point of various
tributaries of data.
This is important from a privacy standpoint, because even if
data stored in these archives is aggregated and anonymized,
the combined data from several distinct sources could pose a
re-identification risk. For example, aggregated shopping data
from one database and specific refund transactions from
another could end up identifying specific customers, and that
data could then be used to perform analysis.

## Page 459

7.2.4 Other data storage locations
We have so far touched on real-time data access and
archival data storage. These represent the bookends of the
data collection process, the former being important for
operational systems that support customers and the latter
for analytics, research, and future insights.
We’ll now consider other data storage that can serve specific
needs germane to either accelerating the fulfillment of data
requests or creating extra copies of data just in case a
server goes down. This is a common use case; companies
create caching layers that usually retain data for a short
amount of time but that sometimes can persist information.
Here you have the same tension between operational
efficiency and privacy that we have seen before. But before
we look at these tensions, Figure 7.3 shows how caching
works at a basic level. The user may think they are
connecting to the main server and the backend database
with all their data, but the reality is more complex. The main
server itself has several copies to allow for scaling, in an
attempt to meet traffic expectations.

## Page 460

Figure 7.3 Caching and the spread of data
In figure 7.3, the user may think that they are connecting to
the main server and the backend database with all their
data, but the reality is more complex. The main server itself
has several copies so as to allow for scaling in an attempt to
meet traffic expectations. That is why you see the servers
pointing to multiple databases.
Additionally, as figure 7.3 shows, before using the database
to fulfill user requests, the infrastructure will use the caching
capabilities that are maintained with backup data stores.
The details involved in caching are beyond the scope of this
book. However, at a high level, when a user request causes
a call to a database, the service first checks in the cache,
and if the information is available in the cache, the service
uses the cached values, even if they are outdated. This

## Page 461

reduces the burden on the database and allows it to be used
for more urgent use cases. This replication of data can lead
to a more functional system in a modern infrastructure.
This is where the privacy vs. efficiency tension comes to the
fore. The need for continuous availability and low latency is
a key driver behind caching, and as I previously stated,
replication of data opens up the risk of inappropriate access,
leakage, exfiltration, and other privacy harms. Just as
organizational efficiency leads to caching, the duplication
that caching results in also leads to additional privacy risks.
In this case, since caches constantly get accessed and
refreshed, data is often harder to detect and its privacy risks
harder to manage. Engineers may exchange data messages
using chat channels, email, etc., and may even retain data in
their laptops and other systems. Just as caching represents
one kind of data persistence, such ad hoc storage represents
the other end of the data flow. These and other potential
data locations may need to be scrubbed in order to avoid
privacy harms.
7.2.5 How data storage grows from collection to
archival
The replication of data that you saw in the previous
subsections poses a problem for privacy. We have discussed
before the privacy governance challenge of dealing with the
tension between reducing your company’s data footprint to
avoid privacy harms, while also making data available for
business uses:

## Page 462

Operations—Allowing customers, engineers, etc.,
to locate data on demand quickly.
Analysis—Allowing data scientists and analysts to
use the data to better understand the overall
strategic direction of the business and help advise
on next steps.
Holds—Enabling the legal team, tax team, audit
team, or law enforcement team to retrieve this
data in case of litigation or other compliance
activities.
In many companies, data is copied to different databases for
these purposes, since each use case has varying retention
and access-control requirements. This spread of data is
often unregulated and unaudited, and that makes deletion
very difficult.

## Page 463

Figure 7.4 How the data footprint grows
Figure 7.4, which you first saw in chapter 4, illustrates how
data grows once it enters the company. This is one of many
reasons why I recommend that technical leaders classify,
catalog, and inventory data toward the left end of the
funnel. This will enable them to delete data faster when it is
no longer needed. This is critical because companies may
have to delete data either when the retention period for
specific kinds of data expires or when a customer/user
requests that their data be deleted.
NOTE In order for a company to be able to delete data meaningfully, accurately, and
scalably, it is vital that the company classifies and inventories data early in the
pipeline. Deletion is not a standalone activity but part of an overall data governance
strategy.
Regardless of whether or not a company has classified and
inventoried its data, most companies need to answer these

## Page 464

questions:
How will you delete user account data—data about
customers such as registration and other
operations?
How will you delete warehouse data? This could
include removing personal data from raw Kafka
tables in Hive after a user requests an account
deletion.
How will you delete data that is extremely
sensitive, like credit card data, that needs to be
very accessible for the right teams (for example,
the payments team) but needs to be deleted
immediately when the time comes for deletion?
Subsequent sections of this chapter will explore these
questions and suggest an architectural design you can use to
implement a deletion system for a modern data-driven
business.
7.3 How the data collection architecture
works
We’ve looked at how data flows from the collection frontend
to backend warehouses. Figure 7.5 shows a simplified
picture of a typical microservice, represented by the box on
the left. This service accepts user requests and writes user
data to and reads it from some kind of data store,
represented by the cylinder in the middle. This could be one

## Page 465

of many supported data stores, such as MySQL or
Cassandra. After data is written to this data store, it is
ingested into the data warehouse, where it could be used for
business analytics or machine learning. There’s a lot of
complexity within the data warehouse itself, but those
details are beyond the scope of this book.
Figure 7.5 The data flow from microservices to database to data
warehouse
The microservice in figure 7.5 would receive data to perform
a specific function; for example, it might collect IP address
data from someone who signs up with your company in
order to ensure that they are a legitimate user and not a bot
or attacker. Upon verifying their authenticity (or determining
that they are a threat), the service could store their data to
a Cassandra database containing information about

## Page 466

legitimate users or to a different database that stores
information about fraudulent users. Future login attempts by
this user will prompt this microservice to call both
databases. Depending upon which database returns a
match, the user is either allowed to proceed or not.
Aggregated analysis of thousands or millions of such users
would need to be conducted so that the business could
meaningfully analyze usage and fraud patterns. To do that, a
significant portion of the data will need to be transferred
from the databases to a data warehouse.
This is an accurate but incomplete narrative. Technical and
senior leaders need to understand the scale of the data that
flows into their warehouse, so that they can harbor realistic
expectations and make appropriate investments in data
deletion infra-structure. Figure 7.6 paints a richer picture of
this scale. In a realistic scenario, data flows from multiple
data sources, is then transformed by extract, transform, load
(ETL) processes, and is then funneled into the data
warehouse. As companies buy other companies, ink deals
with vendors, and empower engineers to create more data
sources (microservices, APIs, etc.), the data flow to the
warehouse will only increase.

## Page 467

Figure 7.6 The data flow into the warehouse for modern businesses
In subsequent sections, when we discuss data deletion, we
will be looking at deleting user data on request or upon the
expiration of a specific time period from the middle cylinder
in figure 7.5 (the database) and then from the warehouse at
the far right in figure 7.5.
Deletion is at once very intuitive and yet very difficult to
execute, so in this chapter we will design systems that
collect and process data and use those systems to build a
deletion architecture. That will enable technical leaders to
execute deletion with a system as a reference and a privacy
lens rather than understanding deletion purely from a
conceptual standpoint.

## Page 468

7.4 Deleting account-level data: A starting
point
When a fast-moving company has to create its first-ever
deletion process, it can be difficult to come up with a list of
areas to focus on. This section will help you build a basic
process and then help drive automation efficiencies.
7.4.1 Account deletion: Building the tooling and
process
In modern businesses, a common vector for account deletion
tends to be a customer calling (or emailing or using social
media) and requesting that their account be deleted.
Many companies struggle to implement a basic process for
customer account deletion. A common early-stage deletion
process, whereby you seek to delete data as early as
possible once its use is complete, could follow these steps:
1. Upon receiving a deletion request, the customer’s
user record is tagged (marked with a flag),
indicating that the record for this specific customer
is to be deleted. You could come up with a
machine-readable tag like “to_be_deleted”.
2. The customer’s credit balances (refunds) are
changed to zero.
3. The customer’s mobile number is marked as
available for use by new customers.

## Page 469

4. The customer’s profile pictures and other biometric
artifacts are deleted from S3.
5. The customer is “deleted.” This could include a list
of actions such as the following:
a. The customer’s primary Personally Identifiable
Information (name, mobile number, etc.) is
overwritten with bogus or empty values.
b. All “notes” are deleted. This is critical, since notes
made by engineers and customer support
specialists could contain personal data. I have
seen many instances where engineers have
entered information that identifies customers in
comments and then forgotten to delete them.
Many privacy incidents are the outcome of such
carelessness rather than willful malevolence.
c. All third-party identities (Facebook, Google+, etc.)
and corresponding identity graphs are deleted, as
is the data connected to the cookies for those
identities. This is critical, since many privacy
harms occur because of incomplete deletions
where identity data is subsequently connected to
activity data. Ensuring identity deletion is vital to
avoid any surprises.
d. All alternate emails (if any) are deleted.
e. All behavioral and inferred data is deleted.
f. All data tags are deleted. These tags could indicate
the type of data or any details that provide context
regarding the data.
6. All payment profiles are deleted. We will cover an
example of payment data deletion in section 7.6.

## Page 470

7. The user is unsubscribed from any email lists so as
to avoid any outreach to a user who has asked for
their data to be deleted.
7.4.2 Scaling account deletion
Based on my experience, deletion often tends to scale poorly
in companies because of the varying user data profiles and
data types. Here are some examples:
The process in the preceding section may not
apply to all types of users and customers. For
example, customers who have different profiles for
subsidiaries could have a different deletion path.
This could happen if a company provides banking
services as well as retirement planning services,
and both require customers to create separate
profiles. That in turn could lead to complexity in
building out the requisite deletion tooling.
Derived and downstream data stores that replicate
customer information will need to receive deletion
notifications as well, so that any data they have
stored about the customers is deleted.
Append-only data stores like Kafka, and data
stores that consume from Kafka (Elasticsearch, for
example) may retain personal data in records that
were emitted before the customer’s profile was
deleted. This could require the creation of more
bespoke deletion processes.

## Page 471

Deletion may not permitted in the following cases:
The user’s account is exempted from the deletion
process by someone with the right privileges.
The customer has been banned, in which case the
company may end up needing to retain customer
data even after the customer requests deletion.
The customer has an outstanding credit balance in
the event of services not rendered after payment
was received (for example, cancelling a service after
an upcoming month was prepaid for).
The customer has an outstanding credit (refund).
The customer has an outstanding debit balance.
Quite a bit of this information often lives in databases that
are append-only, which is to say that the database is
“immutable.” This means the database keeps the entire
history of all completed transactions. This is useful for log
data, and it is recommended for Kappa architectures.
The Kappa software architecture is used for processing
streaming data. The main idea is that it can perform both
real-time and batch processing, especially for analytics, with
a single tech stack. It is based on a streaming architecture
in which an incoming series of data is first stored in a
messaging engine, like Apache Kafka. From there, a stream-
processing engine will read the data and transform it into an
analyzable format, and then store it in an analytics database
for end users to query. This type of architecture has become
widespread. In particular, HDFS, the bedrock of Hadoop, was
designed in this fashion.

## Page 472

There may also be legal requirements to consider when
designing this deletion infrastructure:
You will need the ability to reach out to all tools
and systems to delete records that are linked to
internal identifiers like GUIDs. This is harder than
you might think; it may be easier to correlate data
between databases based on identifiers that are
universal in nature, like Social Security numbers,
whereas internal teams may have a variety of
identifiers that may allow them to retain the data
for longer. This process may allow for bespoke
data storage for engineering teams, but it may
make the data harder to eventually delete.
Your infrastructure will need to block deletion
requests for tables containing data that law
enforcement might need. This would require some
sort of tag to ensure that any attempt to delete
such tables spares the tables subject to legal
holds. This is an example of how data inventory
can help policy enforcement.
Teams will need to invest in verification methods to
ensure the data is deleted but that also raise flags
when it doesn’t work.
A few points of clarification are in order so architects
understand the roles and responsibilities on how this
deletion system would work.
Let’s assume we want to delete some data for Jack. To do
this, a central deletion service will issue a request to the

## Page 473

microservice that collects user data; the message will ask
the microservice to delete Jack’s data. That way, the central
service can track deletion, but the task of deletion is handled
by individual services. These individual services know best,
or should know best, what they need to collect and for how
long, and this approach will also avoid creating a central
point of failure when deletion is executed by one central
service.
This approach maintains the ownership model where
individual services are responsible for their own data. I
recommend this model because it can seamlessly inject
deletion into your workflow, and it can create accountability
as well.
The microservice ownership model offers yet another
advantage. The deletion requests can be ingested
automatically into the data warehouse such that the
ingestion platform can overwrite the original records. There
will almost certainly be some nuance to this, depending on
which data store your company may be using, but generally
speaking, when the central deletion service issues a deletion
request, the resulting data deletions should propagate all the
way to the data warehouse.
7.5 Deleting account-level data:
Automation and scaling for
distributed services

## Page 474

In this section we will create a high-level system design for
the central deletion service, which we’ll name “Destroyer.”
You can repurpose this design for your individual use cases if
you choose.
In the most basic sense, Destroyer should support deleting
personal or private data from a company’s primary data
stores upon customer request. This is accomplished through
services that manage private data and their response to
deletion calls. These deletion calls will be made from a
scheduling service that will be part of Destroyer.
We will look at the scheduling service architecture shortly
but before the deletion of user account data can be
scheduled, there needs to be a check to ensure that there is
no legal hold on the data. Destroyer should check for legal
holds before initiating a delete of any customer data. This
should be done using a Pull model: Destroyer should query a
legal hold database (or service) to check for holds on the
data targeted for deletion.
There are different ways a company could implement such a
legal hold authority.

## Page 475

A company could build its own separate legal hold
authority service that would abstract information
about customers that the company has collected.
This abstraction could be in the form of a service
(user interface, plus database) much like tax
preparation software. Just as you get the data and
guidance best suited to you from a government
tax database without knowing all the underlying
tax laws, the legal hold authority service could
automatically return data that can be deleted
without being subject to a legal hold.
Alternatively, Destroyer (or the microservices that
will actually delete the data) must be able to
directly communicate with a legal hold database.
This database would queue data fields whose legal
hold has expired and therefore ensure timely
deletion.
If an active hold is discovered during a deletion attempt, the
deletion could be rescheduled, either by setting a specific
postponement for the field you are attempting delete, or by
using a default postponement period of 30 days.
Regardless of how this service is implemented, the basic
underlying design remains the same. This service would
need a unified source of legal hold information. For input
such as an email address or a customer’s internal ID, this
service could expose an API that would answer questions
such as these:

## Page 476

Is an employee, contractor, or customer with the
given email or UUID on litigation hold?
What is the list of employees or contractors or
customers on litigation hold?
What is the retention policy associated with an
employee or contractor or customer?
Every service that requires legal hold information would
need to query directly from a legal hold database, which
would normally be a service used by the legal team. This
may turn out to be inefficient, since you want to avoid a
situation where engineers and attorneys are competing for
data from the same database. As a result, I strongly
recommend building a legal hold authority service, which
would serve as an abstraction layer on top of your legal hold
database (which the legal team would maintain) and provide
a RESTful HTTP interface. This will keep engineers and
attorneys from competing for data from the same database.
Since deletion could be a key compliance metric, the legal
hold service must account for some enforceable attributes
and service level agreements (SLAs). The SLAs can either
apply to all APIs, a specific API, or a category of APIs. You
could measure the following metrics:

## Page 477

Accuracy—What is the maximum permissible error
rate for false positives and false negatives? This
would include user records returned (so that they
can be deleted) even if subject to legal hold, or
records not returned even when legal holds are a
non-factor. To be clear, user data should be
returned for deletion only if there is no legal hold.
Capacity—What is the minimum required
throughput (requests/second)?
Latency—What is the median response time, and
what is the 99th percentile response time?
Availability—What is the guaranteed uptime?
Please add justification if it’s less than 99.999%.
Once you validate that the data you wish to delete is not
subject to a legal hold, you will need a mechanism to
schedule the deletion.
7.5.1 Registering services and data fields for deletion
In order to manage deletion requests, service owners that
manage private data should have to register those services
and the private data fields they handle with the Destroyer
deletion service. Destroyer would be in charge of initiating
the deletion of those fields when a scheduled delete request
is executed.
As I have mentioned previously, data collection occurs in a
decentralized fashion among many teams that build tools
and capabilities for customers. That is why the step of
registering these services with the central Destroyer service

## Page 478

is critical. If this step is not completed, you could have some
services where data deletion occurs and others where it does
not. Take it from me, you do not want to have to deal with a
situation where you promised that data was deleted only to
then find out that some fields were missed.
NOTE In this design, we are optimizing for data deletion at the field level, which
means we could deploy the service to delete data for customers on a field-by-field
basis, and delete some accounts only partially if needed. For example, let’s assume
you run a retail website and wish to delete names and addresses of customers on
transactions that are more than a year old, but you wish to retain their purchase
history for subsequent analysis. You could use Destroyer to complete such a
deletion.
When a service that collects user data and will subsequently
need to delete it is registered with Destroyer, that service
needs to help set the context for the future deletion to occur.
The service will need to provide for each field a list of
attributes that describe the field, its owner, and the relevant
details for the API to be used when initiating a delete. The
registration details could look like the following:

## Page 479

Field type—The type of the private data field to be
deleted, denoted by F, selected from a predefined
list of types, which would determine which data
retention policy applies to F. For instance,
FIRSTNAME. This indicates the type of field that
would need to be deleted and which retention
policy would apply to this field. You could maintain
a list of types, of which one would map to this
field. For example, the types could include
“firstname”, “email”, “location”, etc. Supplying the
field and type could also determine the type of
deletion applied to the field itself.
Description—Some text describing what data from
the field is being deleted, for example, “First name
deletion from MySQL.“
Service name—The service that “owns” F (that is,
the service that contains the data field F ),
selected from a list of available services. The
owners of this service would need to be notified in
case of issues such as a deletion error or a test
failure.
API type—The type of the API that will be provided
to and called by Destroyer for deletion.
Deletion and testing API templates—I will provide
below the details on the deletion APIs and
attendant endpoints. They will assume the
existence of a unique identifier to locate the user
to be deleted.

## Page 480

There are three endpoints that could be provided, either via
an HTTP or Thrift API. All endpoints could use the following
parameters in any of their template URLs or headers:
{user_id}—This is the internal identifier of the
user to be deleted.
{field_type}—We will match this field at runtime
to the registered field type selected for deletion,
such as “firstname”. This approach would be useful
if you wanted to utilize the same endpoint to
delete multiple fields for the same UUID.
{requestor_uuid}—This will match at runtime to
the ID of the service that is making the deletion
request.
Given that deletion is a mostly irreversible action, validating
and matching the fields and services is important.
These are three recommended endpoints:
DELETE—This is the main endpoint to support
deletion of a field for a particular ID.
This field must allow passing of the three parameters
we just looked at.
The deletion implementation can range from
complete erasure to replacing the target fields with
synthetic data to anonymization. This should be
finalized by the team that maintains the Destroyer
service and the engineers wishing to use Destroyer
to delete data.

## Page 481

GET_TEST_USER—This endpoint would return a
user_id to be used for testing, so that you can
test the delete endpoint
This user_id must be a valid user, with enough data
to adequately test the first part of the deletion flow
that provides an account for deletion.
Upon calling to this endpoint, services should
attempt to configure a user account that will
“refresh” or “undelete” its data fields. The account
would be seen as not-deleted, and the endpoint
would therefore return its user_id on every call.
That way, you can access a fresh record for deletion
as part of this test.
The alternative would be to generate a fresh test
user on every call and return its user_id. Either
way, the goal is to obtain a non-deleted user that
could be deleted.
IS_DELETED—This endpoint would ascertain
whether data has been deleted for the given
user_id. This endpoint would help test the second
part of the deletion flow that executes the deletion
process.
This endpoint should return whether the user is
deemed as deleted, according to the deletion logic
specified in the deletion policy.
The rest of the implementation details should be trivial for
engineers, but this design offers a reliable foundation to
build on.

## Page 482

A key part of deletion is creating a queue that ensures that
accounts are deleted in an orderly fashion. To do so, you
need a service or capability that orchestrates deletion among
the thousands of microservices, engineers, and data stores
that live at a company. The next section will offer some tips.
7.5.2 Scheduling data deletion
We can now look at high-level designs for the scheduler in
our deletion service. The scheduler will serve as the backend
for incoming delete requests and as the executor of
scheduled deletes.
The scheduler will also be the engineering source of truth for
your data retention and deletion policy, which is to say that
the deletions that the scheduler orchestrates will need to line
up with the retention periods in your policies (the
assumption being that you may need to reference multiple
retention policies to identify the one that is applicable). The
policy would consist of two period definitions: the retention
period for the data after a deletion request is submitted, and
the extended retention period to apply if an active legal hold
exists on the account, after which deletion could be
reattempted. From an implementation standpoint, the
receipt of a deletion request is tantamount to the expiration
of the retention period for that customer’s data. The logic
flow would be similar if the retention period expires without
any request from the user.
The process you follow in designing the deletion scheduling
logic could resemble the following:

## Page 483

1. Check for legal hold—You would need to query the
legal hold authority for any holds on the given
user_id. If a legal hold exists, you’d need to
pause deletion and reschedule the delete according
to the legal hold policy and retry at a later time.
2. Validate that the user remains deletable—Once the
legal hold expires, if there was one, you would
need to verify that the state of the user’s account
has not changed between the scheduling and
execution of deletion. For example, the user who
requested that their account be deleted may have
renewed their subscription, in which case it is not
clear that the deletion request is operative.
3. Initiate delete—This step would execute the
deletion (by erasing the data, obfuscating it, etc.).
Scheduling a deletion for a user account or checking the
status of a deletion request would need to be managed
centrally, so as to maintain an inventory of successful and
unsuccessful deletions. This way, if the legal team needs to
verify deletions across multiple services, they could just
check one central source rather than chase individual service
owners.
This section has provided an architecture for a deletion
system for account data in operational databases. Next we’ll
look at how a company can delete highly sensitive data, like
financial information, that is typically stored in a very secure
database.

## Page 484

7.6 Sensitive data deletion
Every company will have its own unique payments system,
and that will bring unique deletion challenges. For the
purposes of this discussion, we will assume that our system
has a database that stores customer data (called
PaymentsDB, where Destroyer would operate) that contains
some of the data required to charge the customer. We also
have a second database (SecureDB) that contains payment-
specific data that is protected using security tools to prevent
exfiltration and misuse.
Let’s also assume the following concepts, where “mop” is
short for “method of payment.”
mop_token_id—This is a tokenized version of a
16-digit credit card stored in PaymentsDB and
SecureDB, with the latter being the source of
truth. Basically, this is a randomly generated ID
assigned to a real credit card value. Tokenization,
when applied to data security, is the process of
substituting a sensitive data element with a non-
sensitive equivalent, referred to as a token, that
has no extrinsic or exploitable meaning or value.
The token is a reference that maps back to the
sensitive data through a tokenization system.

## Page 485

mop_id—This ID can be owned by a payments
engineering team. Every time a customer updates
or enters a credit card number (even if it is the
same as the previous credit card), payments
creates a new mop_id (using a sequence
generator, not sequential but distributed).
The Payments system typically uses an app, which we’ll call
COP (Cloud Online Pay) in this example, in order to handle
customer credit card numbers in conjunction with SecureDB
and the PaymentsDB.
The COP app receives a request from another
microservice to add a payment. When the request
comes in, COP sends the payment info to
SecureDB and gets a token (mop_token_id) from
SecureDB, which COP stores in the PaymentsDB
(cass_seg_pay). The Payments Cassandra
database stores the following information:
The payment object (mop_id, mop_token_id, first
name, last name, ZIP code) and status
(primary/inactive/deactivated).
Transaction (activity) log with a time-to-live (TTL) of
10 months.
The mapping between mop_id and mop_token_id.
The first of two upcoming examples in this section
describes this in more detail.
This token (mop_token_id) is stored in
PaymentsDB regardless of whether the payment
goes through or not.

## Page 486

In SecureDB, we store the following:
The mapping between the token and the encrypted
payment (possible schema: token, hashed payment
ID, encrypted payment ID). That way, we supply
both the hashed and encrypted version of the
payment info. This is how SecureDB returns the
token for a payment.
If a previously submitted credit card is reused, the
app attempts to find the hashed and encrypted entry
and return an existing token, but you may end up
with a new token.
In the event of a soft delete, a longer retention
period of 3 years could be set in SecureDB for
mop_token_id and hashed payment when the API
for the database that maintains the subscriber
records informs the Payments service that the
account has been cancelled for 10 months. The
assumption at work here is that the account has to
be cancelled for a specific period—10 months in this
case—before formal deletion is initiated. This allows
the cancelled customer to possibly return and
resume their usage with their original data.
Figure 7.7 shows how a system like this would process
deletions. Here are some salient points:

## Page 487

The system is designed to delete customer
payment data in batches, and that is true in many
real-life situations as well, since companies are
rarely able to delete data immediately. This is why
companies routinely state that their systems may
take a while to reflect a deletion request, and 401k
account changes take more than one pay cycle.
Payments systems check whether there has been
recent activity on the account, in which case
payments deletion can be halted.
Deletion occurs in phases, whereby account data is
delinked from payments data, after which
Destroyer would delete account data, and then
payments data would be deleted as well.

## Page 488


## Page 489

Figure 7.7 Payments data deletion, where “mop” is “method of
payment”
A typical credit card wipe process could work as follows:
1. An upstream microservice calls Payments to the
initiate wipe.
2. Payments goes into PaymentsDB and obfuscates
all personal data by replacing their values with
“PII_WIPE”.
3. When the expiration date passes, at which point
the customer data must be deleted, the Payments
system undergoes what is called a “PII WIPE”. This
leads to the deletion of:
Activity logs that have credit card related
information.
In the table that contains the link between mop_id
and mop_token_id, the token is replaced with
“PII_WIPE”. As a consequence, payments cannot
request the credit card from SecureDB and the
customer cannot be billed.
4. When the Payments microservice sends a
“PII_WIPE” request to SecureDB, the latter
removes the encrypted credit card but retains the
one-way hash of the card and its mapping to the
mop_token_id, and it sets the TTL to three years
for the token.

## Page 490

5. For a soft delete, the encrypted credit card is
deleted in SecureDB, but the credit card hash and
token are retained for a TTL of three years,
besides being tagged as soft deleted. This will
preclude the credit card from being used for
payments.
6. For a hard delete, the deletion process removes
mop_token_id as well. This is what happens when
a customer requests full deletion of their credit
card.
In the event that you wish to deal with multiple customers
using the same credit card, and you have to delete the card
for one customer, the payments team can do what is called
unlinking. This will accommodate a situation where
customers C1 and C2 (or potentially others) share the same
credit card. The PaymentsDB would look like figure 7.8.
Figure 7.8 Shared credit cards
Also, the database contains a row that lists all the customers
that a mop_token_id links to. For example,
[(mop_token_id), (C1, C2)]. With mop_token_id being
mapped to both C1 and C2 shows that both customers are
using the same payment instrument.
If C1 calls to have their credit card deleted, the
aforementioned row will let the payments system know that

## Page 491

the credit card is shared. The Payments system then does
the following:
Sets the mop_id to “PII_WIPE”.
Unlinks the C1 box in figure 7.8 from the
mop_token_id box.
The C2 box in figure 7.8 continues to be linked to
the mop_token_id box.
In the [(mop_token_id), (C1, C2)] example,
the entry changes to [(mop_ token_id), ( C2)].
Now let’s look at data deletion holistically in terms of
ownership and maintenance, so that the process can
function smoothly as the company grows.
7.7 Who should own data deletion?
As you have probably figured out by now, data deletion can
be very complex and time-consuming. As a result,
companies often struggle to identify clear owners for the
deletion logic and infrastructure.
In my experience, having a central privacy team owning the
Destroyer service while having individual teams own the
deletion APIs is the most scalable and efficient way to delete
customer data.
Deleting warehouse data gets more complicated. It is vital
that this work be someone’s distinct responsibility, because
otherwise you run the risk of non-compliance and also of
