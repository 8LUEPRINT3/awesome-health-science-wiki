---
title: Data Privacy_ A runbook for engineers - Part 7
source: Data Privacy_ A runbook for engineers.md
category: development
---

language remains the same as before, although
there is a nuance whereby the consent you surface
may depend on the territory or language in the
user’s account settings or the user’s device
settings. You can make these choices depending
on business factors and regulations.
We can now look at the response object for the API to get
the disclosure copy.
struct LocaleCopy { 
  
 1: optional UUID localeCopyUuid, 
 2: optional UUID disclosureVersionUuid, 
 3: optional string territoryId, 
 4: optional string copy, 
 5: optional string richText, 
 6: optional DateTime createdAt, 
 7: optional map<string, string> richTextMappingV2, 
 8: optional list<DocumentDetails> documents 
  
}

## Page 604

This response object for the disclosure retrieval API is fairly
unremarkable, but it will still be helpful to look at an
example. The request body could look like this:
{ 
  "getLocaleCopyRequest": { 
    "disclosureVersionUuid": "2b2b33a7-1426-4a88-acc5-8bbebf50f265", 
    "territoryId": "24", 
    "language": "en" 
  } 
}
The corresponding response could look like the following:
{ 
  "ok": true, 
  "head": { 
    "$rpc$-service": "consents-staging" 
  }, 
  "body": { 
    "localeCopyUuid": "18873e56-a28c-4a79-87e7-1d0b55c42212", 
    "disclosureVersionUuid": "2b2b33a7-1426-4a88-acc5-8bbebf50f265", 
    "territoryId": "24", 
    "copy": null, 
    "richText": "This is the privacy policy.", 
    "createdAt": "2019-09-12 20:51:44.706 +0000 UTC", 
 "richTextMappingV2": { 
      "BODY": "This is the privacy policy.", 
    }, 
    "documents": null 
  }, 
  "headers": { 
    "as": "thrift" 
  } 
}
As you can see, in keeping with the response object, we
allow for separate fields for the copy and a rich text version,
but these are implementation nuances. The key takeaway is
the mapping between disclosureVersionUuid, which was

## Page 605

in part of the request, and localeCopyUuid, which is in the
response. Mapping these correctly in the data model is
critical, which is why we looked at the data models before
looking at the code.
This may seem trivial in the context of this book, but I have
seen real-life situations where incorrect or poorly scaled
mappings led to content decrees simply because a user was
provided with the wrong disclosure. If you fail to provide the
user with the disclosure that applies to them, any consent
you procure could be invalid as well.
This is an example of small decisions made during a
company’s early growth stages ending up having deleterious
effects on their compliance posture. Having to resurface a
new disclosure to re-acquire consent poses the risk that the
user may not consent the second time around, which would
lead to business risk. It is therefore critical to get these
mappings right early, and to ensure alignment between
these groups:
The attorneys who draft these disclosures
The privacy engineers who implement your
consent management platform
The engineering and product teams that use the
consent logic
So far, we have covered the endpoints for checking the
consent status for a user for a specific disclosure and for
retrieving the disclosure. We will now look at the endpoint
for updating the user’s consent status.

## Page 606

9.4.3 API to update the consent status for a disclosure
Now we’ll look at the code to update the user’s consent
status when a fresh or updated disclosure is presented to
the user. Here is the API code:
UserConsent updateCompliance( 
  
   1: UpdateComplianceRequest userConsentRequest 
   ) throws ( 
   1: ValidationError validationError, 
   2: InternalServerError internalServerError 
   3: NotFoundError notFoundError 
 )
As with previous APIs, we allow for errors.
Next, let’s look at the request object for the API.
struct UpdateComplianceRequest { 
  
 1: optional UUID userUuid,                // Requiredness enforced by  
 ➥ service 
 2: optional UUID disclosureVersionUuid,   // Either localeCopyUuid or  
 ➥ disclosureVersionUuid is required 
 3: optional string territoryId,           // Required unless the  
 ➥ disclosureVersion territoryGranularity is GLOBAL 
 4: optional string deviceId,              // Requiredness enforced by  
 ➥ service 
 5: optional i32 compliance,               // Requiredness enforced by  
 ➥ service 
 6: optional UUID localeCopyUuid,          // Either localeCopyUuid or  
 ➥ disclosureVersionUuid is required 
 7: optional string language,              // Requiredness enforced by  
 ➥ service, IETF language code, defaults to "en" 
 8. optional string ipAddress 
}

## Page 607

As with previous code examples, the fields validate specific
design requirements:
userUuid is required. We wish to update the
consent status for a specific user, so the primary
key is a non-negotiable prerequisite.
disclosureVersionUuid or localeCopyUuid is
required, since we need to record the acceptance
for a specific one-to-one mapping. A specific user’s
consent maps to a specific disclosure.
territoryId is required, since the disclosure
version or the locale copy maps to a specific
location, which we derive from the territoryId.
deviceId is critical, since we may need to
maintain an audit trail indicating on which device
the user consented. Companies often need to
maintain consent on a per-device basis or maintain
a record of which device the user consented from.
compliance is the binary value of the consent for
the user (1 for when the user accepts, and 0 for
when consent is declined).
The corresponding response object to update the consent
could look like the following:
struct UserConsent { 
/* Below we call out the fields that correspond to the user consent. Every  
➥ consent will have the following fields for an update to occur*/ 
 1: optional UUID userUuid, 
 2: optional string deviceId, 
 3: optional string ipAddress, 
 4: optional DateTime timestamp, 
 5: optional string language,          // IETF language code 

## Page 608

 6: optional string territoryId, 
 7: optional UUID disclosureUuid, 
 8: optional UUID localeCopyUuid, 
}
By way of explaining the response object, let’s look at an
example of a specific request and the corresponding
response body:
{ 
  "userConsentRequest": { 
    "userUuid": "UserUUID", 
    "disclosureVersionUuid": "", 
    "territoryId": "1", 
    "deviceId": null, 
    "compliance": 0, 
    "ipAddress": "203.0.113.1", 
    "localeCopyUuid": "LocaleUUID", 
    "language": "en" 
  } 
}
The preceding request, which indicates that consent was not
granted, would produce a response that looks like the
following:
{ 
  "ok": true, 
  "head": { 
    "$rpc$-service": "consents" 
  }, 
  "body": { 
    "userUuid": "UserUUID", 
    "deviceId": "", 
    "compliance": 0, 
    "ipAddress": "203.0.113.1", 
    "timestamp": "2021-04-22 03:21:43.218029116 +0000 UTC", 
    "language": "en", 
    "territoryId": null, 
    "disclosureUuid": "DisclosureUUID", 
    "localeCopyUuid": "LocaleUUID" 
  }, 

## Page 609

  "headers": { 
    "as": "thrift" 
  } 
}
So far, you have seen how to process disclosures and
consents on a one-off basis, but given the scale of modern
businesses, it may make sense to process several at the
same time. The next subsection will explore how.
9.4.4 API to process multiple disclosures
In a real-life scenario, engineers must allow for the fact that
they will need to retrieve multiple disclosures at once, rather
than retrieving them one by one. They will need to verify or
update multiple consent acceptances at once as well. This is
where the need to get privacy right has to be balanced
against the customer user interface design and business
considerations.
If you make the customer accept four consents, one after
the other, it not only makes for substandard design, but the
customer may get weary, step away from the workflow, and
not complete the purchase, for example. In this case, you
will have achieved complete privacy at the expense of
business success.
Therefore, we will now look at a way to get the consent
status for multiple disclosures in one go. That way, in the
example we just discussed, you could only surface the
disclosures that require acceptance.
The API call for this capability could be as follows:

## Page 610

GetComplianceAndCopyForFeaturesResponse getComplianceAndCopyForFeatures ( 
  
   1: GetComplianceAndCopyForFeaturesRequest 
getComplianceAndCopyForFeaturesRequest 
  
 ) throws ( 
   1: ValidationError validationError 
   2: InternalServerError internalServerError 
   3: NotFoundError notFoundError 
  
 )
In the following request object, you will notice the one-to-
many mapping for the user to the disclosures. This call is
like multiple getCompliance calls from section 9.4.1:
struct GetComplianceAndCopyForFeaturesRequest { 
  
 1: optional UUID userUuid,                
 2: optional list<UUID> featureUuids,       
 3: optional string territoryId,            
 4: optional string language,              
 5: optional string deviceId, 
 6: optional map<UUID, UserConsent> userConsentsToSync,  
 7: optional string ipAddress 
}
As with the previous calls, we check for location, language,
and device IDs. However, in keeping with our intent to
secure compliance status for multiple disclosures, we map
the UUID to the UserConsent object.
The corresponding response object is as follows:
struct GetComplianceAndCopyForFeaturesResponse { 
  
 1: optional map<UUID, UserConsent> userConsents  // most recent 
userConsent  
 ➥ for requested features, keyed by featureUUID 
 2: optional map<UUID, LocaleCopy> localeCopies  // localeCopy for any  

## Page 611

 ➥ requested features WITHOUT UserConsent recorded 
  
}
In order to understand what the practical functionality would
look like, let’s look at an example. In the following call, we
are checking for acceptance for a user with UUID UserUUID
for feature IDs covered by d6063933-161d-4134-abce-
ff786db70193 and 13eaf184-b855-4a8d-8b84-
7ded597f62a9. This approach allows us to check for user
acceptance for multiple disclosures that correspond to
multiple features.
{ 
  "getComplianceAndCopyForFeaturesRequest": { 
    "userUuid": "UserUUID", 
    "featureUuids": [ 
      "d6063933-161d-4134-abce-ff786db70193", 
      "13eaf184-b855-4a8d-8b84-7ded597f62a9" 
    ], 
    "territoryId": "1", 
    "language": "en", 
    "deviceId": null, 
    "userConsentsToSync": { 
      "13eaf184-b855-4a8d-8b84-7ded597f62a9": { 
        "userUuid": "UserUUID", 
        "deviceId": "hailstorm", 
        "ipAddress": "203.0.113.1", 
        "language": "en", 
        "territoryId": null, 
        "disclosureUuid": "DisclosureUUID", 
        "localeCopyUuid": "LocaleUUID" 
      } 
    } 
  } 
}
In our use case, a response to the preceding call could be as
follows:

## Page 612

{ 
  "ok": true, 
  "head": { 
    "$rpc$-service": "consents" 
  }, 
  "body": { 
    "userConsents": { 
      "13eaf184-b855-4a8d-8b84-7ded597f62a9": { 
        "userUuid": "UserUUID", 
        "deviceId": "hailstorm", 
        "compliance": 1, 
        "ipAddress": "203.0.113.1", 
        "language": "en", 
        "territoryId": null, 
        "disclosureUuid": "DisclosureUUID", 
        "localeCopyUuid": "LocaleUUID" 
      } 
    }, 
    "localeCopies": { 
      "d6063933-161d-4134-abce-ff786db70193": { 
        "localeCopyUuid": "769b6726-dcf8-41a1-a268-8b48f81cac89", 
        "disclosureVersionUuid": "331b724f-a72d-4d47-9490-e034e6e3c442", 
        "territoryId": "1", 
        "copy": null, 
        "richText": "test", 
        "createdAt": "2018-12-27 00:30:15.78 +0000 UTC", 
        "richTextMapping": { 
          "BODY": "This is the first disclosure" 
        }, 
        "documents": null 
      }, 
      "13eaf184-b855-4a8d-8b84-7ded597f62a9": { 
        "localeCopyUuid": "a878d99a-d817-43f1-9800-2879c652f1c4", 
        "disclosureVersionUuid": "c0e80149-d3e2-440c-8cc3-ed401061122b", 
        "territoryId": "1", 
        "copy": null, 
        "richText": "testing one two three", 
        "createdAt": "2018-12-26 23:48:13.383 +0000 UTC", 
        "richTextMapping": { 
          "BODY": "This is the second disclosure" 
        }, 
        "documents": null 
      } 
    }, 
      }, 
  "headers": { 
    "as": "thrift" 

## Page 613

  } 
}
In the preceding response snippet, a few points stand out:
Our check for disclosure acceptance for features
represented by feature IDs d6063933-161d-4134-
abce-ff786db70193 and 13eaf184-b855-4a8d-
8b84-7ded597f62a9 yielded an acceptance for
just one, "13eaf184-b855-4a8d-8b84-
7ded597f62a9" as represented by the compliance
value of 1. Since the other feature ID did not have
an accepted disclosure, we had no values
returned.
Regardless of the disclosure acceptance, we are
able to obtain the disclosures that correspond to
the feature IDs we supplied.
This provides privacy engineers and business stakeholders
with clear choices on how to proceed with data collection
and usage based on consent statuses that correspond to
multiple disclosures. They could make decisions on how to
surface disclosures that had not been accepted yet and
possibly make any changes accordingly. This is important,
since you can imagine thousands (or even more) calls to the
consents service, and even more calls to retrieve updated
disclosures.
All of these decisions build on the data model and the Thrift
code we have discussed in this chapter. It is therefore critical
to have an appropriate data model as a starting point to

## Page 614

prevent inconsistent capturing of consent status and audit
failures, or worse, creating an impression that consent was
disingenuously secured. Many a troubling headline has been
born out of bad backend management of consent
architectures with hard-to-undo architectural decisions.
Now that you’ve seen how to use the capabilities around the
disclosures and acceptance status, we can look at how you
would connect to (or onboard) this consent service.
9.4.5 API to register with the consents service
In this section, I will use the term onboarding to refer to a
microservice or some other capability to utilizing our
consents service. We will define the parameters that a
service would need to support so as to use our consents
capability.
The goal behind building a service is to allow multiple teams
at a company to use this service. For example, if you run an
online retail company, you would want the iOS, Android, and
web teams to use the same service. We will look at how you
could shape the code to allow other services to onboard the
consents service. The request code is as follows:
struct OnboardingRequest { 
  
    1: optional list<string> territoryIDs,          
    2: optional TerritoryGranularity territoryGranularity,      
    3: optional string owningTeam,                  
    4: optional string featureName,              
    5: optional string businessPurposeName, 
    6: optional bool mandatoryFeatureUpdate, 
    7: optional bool isPerDevice, 

## Page 615

     
}
In the preceding code snippet, a service owner would need
to specify the applicability of the disclosure while registering
their service with our consents service. They would need to
address the following considerations for the disclosures for
which they need to use the consents service:
The territories or locations where the disclosure
will apply
Any information on location granularity—states,
countries, regions, etc.
IDs for the team and features that will map to the
disclosure
The business purpose for the disclosure
Whether the disclosure will be mandated each time
the corresponding feature is updated
Whether the disclosure is mandated on a per-
device basis
You can implement this onboarding/registration capability as
you like, but this provides a template that you can adapt.
We have defined several core capabilities for a consents
service. In the next subsection we will look at some
foundational definitions to complete the service.
9.4.6 Useful definitions for the consents service

## Page 616

A significant chunk of the code you have seen thus far
assumes certain accepted definitions. For example, you saw
that a value of 1 meant that the user had provided consent
for a specific disclosure. In this section, I will provide a
template for some of these definitions.
The following code snippet creates a definition for the sorts
of actions the user might undertake when they are given the
chance to offer their consent to a disclosure:
enum UserConsentStatus  
{ 
  ACCEPTED = 1 
  DEFERRED  = 2 
  INVALIDATED = 3 
  DECLINED = 0 
}
This code is fairly self-explanatory. It allocates intuitive
values for consent acceptance and other actions the user
may take.
We also referenced territory granularity for the locale that a
disclosure is tied to. The following code provides a sample
template for how you could define granularity.
enum TerritoryGranularity { 
  
 CITY = 1001, 
 STATE = 1002, 
 COUNTRY = 1003, 
 GLOBAL = 1004, 
}
Besides defining those foundational values, it is vital that
you throw meaningful errors in the event that the data in

## Page 617

the call is not valid, or if there is a server-side error or a
problem locating the data for the consent status or
disclosures. The three snippets that follow should offer some
ideas to build upon.
/** Validation Error, thrown when there's an issue with provided data*/ 
  
exception ValidationError { 
 1: required string code, 
 2: required string message 
} 
  
/** Internal Server Error -- thrown when unexpected errors occur during  
➥ handler execution */ 
exception InternalServerError { 
 1: required string code, 
 2: required string message 
} 
  
/** Not Found Error -- thrown when entity is not found in the data store */ 
exception NotFoundError { 
 1: required string code, 
 2: required string message 
}
While these represent a fairly strong list of errors and
definitions for a CMP, the next section will help privacy-
forward businesses plan for other scenarios as well.
Throughout this book, I have aimed to build automation for
privacy into the design as early as possible, so this will help
smaller and growing companies to be as thorough as
possible.
9.5 Other useful capabilities in a CMP

## Page 618

This section will identify features you can embed into your
CMP to make sure there is no conscious asymmetry between
the data you collect and the consent you possess. While the
capabilities I will list here do not fall neatly into the frontend
or backend buckets, they could still be useful to implement.
For starters, almost every website uses third parties such as
pixels or social media platforms, but in many regions, until
the user has consented, you cannot load those scripts. You
will want your CMP to automatically block and unblock third-
party scripts to ensure unsanctioned third parties don’t
collect user data without consent.
Several countries have visitor consent laws, but each
country has its own nuances about what constitutes consent.
In order to automatically display and enforce the correct
consent requirement based on the geolocation of each
website visitor, you will want clear guidelines on how to
decipher user location. You could use the information in a
user’s account settings, but that may not account for
unregistered users who still use your website or app. In that
case, you may wish to lean on the user’s IP address, but
that may affect users connecting via a VPN. Regardless of
how you decipher a user’s location, having clear standards
could help ensure your consent is valid.
Fast-growing companies often find themselves surprised
when some part of their online infrastructure that’s
unaccounted for by their CMP nonetheless collects user data.
This is especially challenging when the data is collected by a
page that isn’t searchable. You will want your CMP to be

## Page 619

continually aware of hidden pages and keep you in the loop
about what is loaded where on your site.
Given that small and even some larger companies do not
always have cross-platform visibility, it will help if your CMP
is equipped with A/B testing and reporting tools to track,
manage, and optimize consumer consent.
Additionally, a CMP can be priceless if it enumerates all
triggered cookies, trackers, and technologies by capturing all
content executed via pixels, cookies, JavaScript, and API
calls, and if it utilizes scenario emulation that mirrors user
interactions (privacy preferences, login).
One of the lines of pushback that privacy engineers will get,
especially in businesses that run lean and where privacy
knowledge is not high, is that consent tooling will slow down
the customer flow. Having to check those boxes will annoy
customers and lead to missed conversion and cart
abandonment issues. While it will help to educate those
stakeholders on the cost of not getting consent,
implementing a business-friendly consent solution will help.
To that end, integrating identity solutions for a frictionless
user experience across devices, and tracking user consent
across the desktop and mobile web is helpful. This will avoid
creating unnecessary speed bumps in the user’s navigation
path. Continually checking on the user’s consent status and
having a consent graph akin to the well-known identity
graph will balance privacy and business imperatives. Finally,
mapping your internal ID to proprietary or partner IDs could
help ensure that privacy preferences can easily be recorded
and shared as needed with partners.

## Page 620

Another area of consent management is third-party vendors.
Business growth often requires, and leads to, vendor
relationships. However, as Facebook found out during the
Cambridge Analytica affair, data-sharing with third parties
can be fraught with risk as far as consent is concerned.
Therefore, you will want your CMP to flag privacy
vulnerabilities that can lead to data leakage, non-
compliance, and reputational risk, and to provide actionable
insights to ensure compliance. You will want to consider the
following specific capabilities:
A page-scanning feature to monitor pages and add
vendors to your list automatically
Creating a comprehensive view of unauthorized
vendors processing personal data—not just via
cookies, but also via local storage and
fingerprinting
Detecting vendors creating fraudulent consent
strings and sharing them with the ecosystem
Another useful capability in a CMP can be assigning roles and
responsibilities for users who access a CMP. The
configuration of the CMP impacts who can edit disclosures,
map disclosures to locations, update versions, etc.
Therefore, it is important to control who can edit, push, or
check internal configurations within the administrative
interface. Teams ranging from legal or marketing to IT need
different levels of permissions.
A lot of these capabilities are not top of mind for customers
who think a CMP is nothing more than a tiny check box on

## Page 621

the login screen, so this section bears serious consideration
for companies that are fast growing and that use data to fuel
that growth.
So far we have looked at the capabilities and automation
that drive the CMP. However, a lot of small businesses, and
even some large established companies, struggle to build a
practical workflow that integrates a CMS into their products.
This is often because engineers and attorneys operate in
different siloes and lack shared context. It helps to have a
practical example of the consent logic workflow.
9.6 Integrating consent management into
product workflow
You have so far seen how consent management logic can be
built to manage disclosures, consent collection, and status
retrieval. In this section we will look at how a functional CMP
can be used in a practical product workflow.
I want you to walk away with a specific use case so that you
understand how the data model we reviewed earlier and the
code snippets we looked at correspond to a realistic
workflow. Privacy is not an abstract altruistic capability;
when implemented correctly, it can play a critical role in
enabling the business. This example will show you how the
relationships between different entities and the capabilities
of a CMP support a specific business need. Having an eye on
the business need will help you craft a solution that drives

## Page 622

business adoption, which in turn will lead to protecting the
data privacy of the end user.
In this example, we will assume that our company is to host
an online event. We will also assume that in order to collect
data from the attendees of the events, we will need their
consent. In the previous code examples, consents and
disclosures were mapped to locations; similarly in this
example, disclosures are mapped to specific events. The
attorneys or planners in charge of the event would need to
create the disclosures.
For this system, we will have two key microservices: the
first, named NET, will govern the creation of events; the
second, named NULL, will govern the creation of disclosures
and record the user’s consent for that disclosure.
To facilitate these capabilities, we will have three APIs:
The first API will enable NET to send to NULL the
parameters germane to the event and retrieve
from NULL the relevant disclosure(s).
The second API will periodically enable NET to send
to NULL the RSVPs for the events (the list of
attendees) and their corresponding disclosures
with consent status.
The third API will periodically enable NULL to send
updated PDFs for disclosures to cloud storage and
send corresponding URLs to NET with a mapping to
the events affected by those disclosure updates.

## Page 623

In summary, the first two APIs will enable NET to tell NULL
about the events and either
Retrieve disclosures that require acceptance
or
Send accepted disclosures
The third API will allow NULL to keep disclosures ready so
that when someone uses NET to create an event, they can
create an event much faster.
Let’s look briefly at each of the steps (I am taking for
granted the step where attorneys create disclosures; this
workflow starts with the event creation):
1. The creator of the event logs into NET to create
the event. They will need to possess some baseline
details about the event, including
Event name
Location
Start and end times
2. The creator uses NET to create the event. We’ll
assume the event is not marked as complete until
there is a corresponding disclosure. Events without
disclosures are marked as “not complete.”

## Page 624

3. When the creator saves the event in NET, the
backend logic recognizes the event as one with
possible attendees and seeks out a disclosure that
those attendees can consent to.
In order to get these disclosures, NET sends to NULL
the same parameters that the creator provided
(event name, location, and start/end times).
Any default values that NET creates, like event ID,
are also passed to NULL so that NULL can map a
location-specific version of a disclosure to that
event.
NET may also supply NULL additional context on
whether it needs a standard off-the-shelf disclosure
or a customized one.

## Page 625

4. Before supplying a disclosure to NET, the NULL
system will proceed with a workflow for standard
or custom disclosures.
In the case of a standard disclosure, NULL fills the
event details in an event-specific version of the
disclosure and sends it to storage—an S3 location in
this case. This generates a URL for the disclosure
and marks the event as complete.
If a standard disclosure does not exist for a specific
location, for example, or there is some other system
error, the NULL service can send the legal or tech
team an email.
If the event requires a custom disclosure (one that
would need to be created by an attorney for this
event), NULL proceeds to save the event but not
mark it complete. NULL also generates an email to
the legal team asking them to supply a custom
disclosure.
5. The system used by the company’s lawyers to
create disclosures now has a shell disclosure with
details about the event filled in. Once the lawyers
fill in their details, the custom disclosure can be
deemed completed.

## Page 626

6. Upon completion of the custom disclosure, the
content management system (CMS) maintained by
the legal team would need to notify NULL that an
event-specific custom disclosure now exists. (Most
companies I have worked for provide legal teams
with some sort of CMS, but you may need to
implement additional capabilities to enable the
CMS to work with APIs as defined in this example.)
7. NULL transfers the newly generated custom
disclosure to storage (again, an S3 location in our
example) so as to generate a URL for the waiver.
This is critical, since every disclosure—be it
standard or custom—could apply to more than one
event, so having a URL enables you to link it to
relevant events.
8. There is a call from NULL to send the URL of the
newly created disclosure to NET, with information
about the event the disclosure was created for.
This enables NET to retrieve an event that is
marked “not complete” for want of a disclosure.
9. The NULL service sends a notification to the
creator of the event that the relevant disclosures
have now been created and associated with their
event. In a real-life scenario, this call may also be
made by the NET service. Either way, the creator
of the event needs to be notified that they can
now proceed forward.

## Page 627

10. Having been notified of the disclosure completion,
the event owner publishes the event. In real
terms, this means that attendees can start
registering for the event and accept the
disclosures.
11. When an attendee clicks on the link to view the
disclosure, the mapping logic (of the kind we
viewed in the code examples earlier in this
chapter) kicks in, and a call is made by NET to the
storage layer to retrieve the disclosure.
12. The NET service registers the acceptance of the
attendee for a disclosure and stores it in a table
(using logic similar to what you saw earlier).
13. To maintain an auditable record of disclosure
acceptances, the NET service may want to send
batch updates to the NULL service so that there is
a running list of who has accepted what
disclosures. This ongoing inventory will allow
companies to demonstrate that they have a way of
verifying compliance.
14. This optional step allows attorneys to make edits
to disclosures via their CMS, and to notify the
NULL service that disclosures it tracks have been
updated. The mapping between disclosures and
locations, for example, is critical in executing these
calls. This use case shows how the data model and
code examples build a logical progression and are
an irreplaceable part of a CMP that will need to
accommodate several possibly concurrent
permutations and combinations.

## Page 628

15. Upon being notified of an update to a disclosure,
NULL publishes the disclosure update to the
storage layer, generating a new version number
and a new URL, if applicable.
As this use case shows, it is critical that a CMP must aspire
for consistency (data schemas and code should stay in
harmony) while also working seamlessly with other services
(like the event service), platforms (like the CMS, where the
legal team physically stores the disclosures), and a
persistence layer (the S3 database).
It is important for privacy engineers to understand this,
since many of them become privacy advocates rather than
problem solvers and build solutions that are incompatible
with existing technical infrastructure as well as business
goals. When that happens, you end up with solutions that
solve immediate problems (such as getting a new disclosure
written and uploaded to launch a critical product) without
providing auditable capability (ensuring the consent was
recorded for automated retrieval).
Summary
Consent collection and maintenance are critical for
businesses to meet compliance requirements as
well as to meet user trust and transparency
requirements.

## Page 629

In addition to governments, industry players are
also using consent as a key metric for privacy
rights.
Consent management platforms are key to
securing informed and granular consent and
maintaining it in an auditable format.
CMPs can have several key capabilities that enable
businesses besides meeting the privacy use case.
Privacy engineers building CMPs need to focus on
how these platforms will play with the existing
tech stack and infrastructure.
1 “What are the GDPR consent requirements?” Complete guide to GDPR compliance, GDPR,
https://gdpr.eu/gdpr-consent-requirements/.
2 “What are the GDPR Fines?” Complete guide to GDPR compliance, GDPR,
https://gdpr.eu/fines/.
3 “General Data Protection Regulation (GDPR),” Complete guide to GDPR compliance, GDPR,
http://mng.bz/oaVD.
4 “User Privacy and Data Use,” Apple App Store, http://mng.bz/nYxd.
5 Nick Statt, “Apple’s next iOS 14 beta will begin forcing developers to ask for permission to
track you,” The Verge, January 28, 2021, http://mng.bz/voOa.
6 “User Privacy and Data Use,” Apple App Store.
7 Estelle Laziuk, “iOS 14.5 Opt-in Rate - Daily Updates Since Launch,” Flurry, May 25, 2021,
http://mng.bz/4jvQ; Corinne Reichert, “App tracking has only 5% opt-in rate since iOS 14.5
update, analyst says,” CNET, May 10, 2021, http://mng.bz/g4YG.
8 Rachel Kraus, “After Update, Only 4 Percent Of iOS Users In U.S. Let Apps Track Them,”
Mashable, May 10, 2021, http://mng.bz/XWAE.
9 Joanna Kamińska and Karolina Matuszewska, “Comparison of 9 leading consent
management platforms,” Piwik, November 20, 2020, https://piwik.pro/blog/consent-
management-platforms-comparison/.
10 Tag Inspector, Lucas Long, “Marketing Tags and Pixels – What They Are and How They
Work,” Tag Inspector, May 24, 2016, http://mng.bz/y42e.

## Page 630

inside back cover

## Page 631

Comparison of privacy done wrong (above) and privacy done right
(below). When privacy is done wrong, data flows into a company and is
not dealt with until it has already proliferated throughout the company
via sharing and copying. Privacy tools may not scale well for such a
volume of data, and privacy violations become much more likely. When
privacy is done right, data flows into a company and is immediately
tagged and cataloged. Data becomes much more manageable, privacy

## Page 632

measures work effectively, and privacy violation is much less likely to
occur.

## Page 633

10 Closing security vulnerabilities
This chapter covers
Privacy risks hidden within security risks
How testing and development efficiencies can increase risk
Building an enterprise risk model to identify, track, and address
privacy risks
How major privacy and security risks are cumulative and
impactful in ways that are hard to predict and plan for
Using authorization to reduce risk
Privacy risks hidden in authorization implementations
Privacy controls are complicated for many companies to
implement—particularly those with limited budgets or that
are small or medium sized. Such organizations often face a
critical question: “Where do we get started when it comes to
building privacy into our technical infrastructure?” While
prioritization questions are perennial, the much harder
question to answer is what to do first.
In my experience, companies just starting out in the privacy
space may find it daunting to start making their data
privacy-safe. Practices like data minimization and data
governance require significant changes that, in many cases,
will affect all levels of the company. Data minimization, for
example, requires engineers to collect less data.
Implementing it at scale will require changes in culture,

## Page 634

processes, and automation that may take time to scale,
even as other vulnerabilities (around permissions
management, affecting data you already have, for example)
may remain unaddressed. Data governance may prove to be
even more complicated for companies, since it requires
understanding what is being collected, for what purpose, and
by whom, and then implementing tools to enforce data
privacy.
Companies may wish to consider an approach where they
start not with an approach that doesn’t focus on the data
itself; a more forward-looking approach would entail
protecting data privacy by safeguarding the infrastructure
and reducing the attack surface. This would mean that the
containers holding the data are more secure, thereby
making the data itself more secure and setting the stage for
the more granular privacy engineering approaches you have
seen so far in this book.
Purely from a risk management perspective, it is critical for
companies to secure their infrastructure, since any
deficiencies in infrastructure open the company to not just
external risk but internal risk as well. Applying security
tooling to address privacy risks offers a definitive starting
point, identifies key vulnerabilities, and helps create a
knowledge base around data lineage as well as the
organizational muscle necessary for data-driven
prioritization. For many engineers and technical leaders, this
work alone is both challenging and rewarding.
This chapter will offer insights into key considerations
around their infrastructure and how users interact with it.

## Page 635

The following are areas to focus on when engineers consider
how effectively they can protect their data and systems:
Attack surface reduction
Perimeter protection
Multi-factor authentication
Mobile security
Account takeover situations
Weak password management
Email compromise via malware and phishing
The preceding list represents a checklist for privacy
engineers in that it mixes weaknesses and actions to prevent
those weaknesses. It represents a starting point checklist for
engineers as they seek to harden their defenses against
attacks. These points would need to be mapped to services
and endpoints before they are open for use by external
customers.
Addressing these makes sense for all kinds of businesses,
since that will help protect the company from losing not just
customer data but also intellectual property and other
business secrets. This chapter, in that way, will help you
make progress on technical privacy by improving your
security. That is a win both for your business and its
customers.
In this chapter, I will walk you through real-life scenarios
that demonstrate these vulnerabilities, how they were
exploited, their attendant privacy impacts, and how
companies can address them.

## Page 636

Note that this chapter will not cover every possible privacy
security risk. My goal is to help you build an instinct so that
you can use the guidelines and skills presented here as a
stepping stone rather than a capstone.
Given that businesses with low margins and fast-moving
releases are always stretched thin, they often have to
prioritize where to start. I have found that reducing the
attack surface is a win-win because expenditures on incident
response and data protection could decrease, and the entire
exercise tends to help the company become more mature in
its overall data management. The first section of this chapter
will explore this area in detail.
However, companies will still need to exchange data and
context between their online capabilities and customers. This
is where the risk of fraudsters and attackers pretending to
be customers poses privacy risks. As such, the second
section of this chapter will look at a more comprehensive
access management regime by way of a deep dive into the
famous breach at Target Corporation. I will show you how to
account for such vulnerabilities in you own designs.
The third section of this chapter will focus on common
access management risk-remediation strategies, since you
will need to evolve your security stacks as attackers become
more sophisticated.
10.1 Protecting privacy by reducing the
attack surface

## Page 637

One of the reasons why data privacy suffers is the profligate
spread of data in a company’s systems. This is why I am
advocating a comprehensive approach to reducing your
company’s attack surface.
In this section, we will first look at a traditional baseline
approach for reducing a company’s attack surface for
security and privacy. We will then look at reducing the attack
surface by examining the connections between data,
infrastructure, and product development. Finally, we will
build an enterprise risk model that will help you plan for
innovation and growth while concurrently managing security
and privacy risks.
First, let’s look at how fast-moving companies can get
started with attack surface management.
10.1.1 Managing the attack surface
Engineers who write customer-facing or customer-impacting
tools need to account for attack vectors. Before you even
begin to take a privacy-centric view of your security
infrastructure, you will want to account for things like
Vulnerable web components that are not fixed by
appropriate software patches.
Expired certificates and unused ports.
Unsecured APIs that have access to customer or
business data.

## Page 638

Servers or networks that an attacker can flood
with traffic in an attempt to disrupt and overwhelm
a service and render it inoperable.
Malware and phishing attempts that are targeted
for maximal impact.
Ransomware attempts that involve locking down
your network and hijacking it.
Lack of content filtering, due to which employees
may visit unsecured websites, which in turn may
lead to data loss.
Lack of web server hardening, which is critical,
since these servers often sit at the edge of the
network. They could present an entry point for
hackers, but proper hardening will ensure that you
change default configurations and disable certain
services.
Your attack surfaces are all the places where your
organization is vulnerable to cyberthreats and attacks.
Attack surfaces are not discrete and disconnected gaps that
you can remedy. Given how quickly engineers build features,
it is imperative that you look at your engineering practices,
testing needs, infrastructure relationships, and
organizational dependencies as an attack universe.
TIP The typical company focuses on detection and remediation. A forward-looking
security and privacy approach instead optimizes for prevention and, therefore,
minimizes the need for remediation and its costs.
This is important for engineers and program managers to
understand, since the attack surface in modern companies

## Page 639

expands from the inside out. While the points in the
preceding list are outside-in, the unaccounted for risks
emerge from siloed teams making disconnected decisions
that end up expanding macro risks. Such decisions create
services and processes that impact the data platform and
infrastructure. Looking at this holistically is critical to
understanding what “reducing the attack surface” means.
To make this point clear, let’s look at a specific example. In
the next subsection, we will look at how well-intentioned
engineering created a privacy risk, and how a good
engineering instinct—more robust integration testing—
inadvertently expanded the company’s attack surface.
10.1.2 How testing can cause security and privacy
risks
Companies that create customer-facing products and
services need to test them extensively throughout the
design, development, and deployment process. The goal
behind this testing is to ensure that functionality is in line
with the design. This process is complex because such
products are composed of several smaller microservices; for
example, a retail shopping app could have separate services
like user experience, recommendations, payments, billing,
shipping, and fraud detection. All of these capabilities
require individualized or unit testing as well as integration
testing. That way, engineers can ensure that the individual
capabilities work as expected, and the aggregated product
works as expected as well.

## Page 640

Given that different teams work at different cadences and
often with varying tech stacks, it is common in many small
companies to use real customer data for testing. In some
cases, companies copy production data to a separate test
server that is used for such testing. Such practices are
understandable, since it saves engineering time, subjects
the code to a more rigorous test process, and reduces costs.
The following benefits flow from such testing:
You can debug a problem that has only appeared
in production.
You can test the corresponding fix before applying
it in production.
You can allow people (such as customer support)
to train on IT systems without the risk of
impacting the live system.
You can allow access to the data for easy end-to-
end testing.
USING PRODUCTION DATA IN TEST
I once consulted for a company that followed a similar
process for testing. The engineers in that company copied
production data to test servers on a weekly basis. This
process, called the “weekly refresh of Cassandra clusters,”
was handled by a tool that handled backup, token
management, maintenance, and refreshes. All the Cassandra
clusters in the production server were backed up by this
process, which involved daily full snapshots and incremental
data being copied to S3.

## Page 641

Another tool, using configuration settings, determined which
test clusters needed to be refreshed with a copy of the
production data, and a Jenkins job kicked off the refresh.
The weekly refresh involved the copying of data files from
S3 in production to the local instance in the corresponding
test servers. The business goal was to enable any and all
engineering teams access to production data without the
access constraints enforced in production.
Once the refresh was complete on all the nodes, the fast
property specifying the cluster name for an app was
switched to the new cluster that had been refreshed so that
the app teams could start using the new refreshed cluster.
Figure 10.1 illustrates the workflow for the weekly refresh.
The “CID” in the figure stands for “customer identifier,” but it
is really a placeholder for any internal identifier that
identifies a customer or user.
Given that this book is not about testing, I will pass over the
deep technical details in figure 10.1, but it does help to show
why using production data in the test server was critical for
this company.
The company moved a significant number of its
production accounts to the test server and then
had a tool named TestTool identify accounts that
could be used for testing. That way, the company
could customize, on a weekly basis, which
production accounts were to be used for testing.

## Page 642

In steps 2–5, TestTool played the role of
intermediary between the accounts and the
services that needed those accounts.
At the top right, you can see that since multiple
services probably used the same accounts in the
test servers, the data kept changing. This meant
that TestTool had to repeatedly fetch accounts to
find the right ones. This caused a lot of swirl, and
avoiding that in the production server was key,
since that server was used by paying customers.

## Page 643

Figure 10.1 The weekly refresh workflow
This process, while technically efficient, caused privacy and
security problems.
I was brought in when the company failed an audit primarily
because the auditors faulted them for loose access control.

## Page 644

The company was surprised at the finding, since they had
never considered the privacy and security risks.
FLEXIBLE TESTING BUT WITH AN EXPANDED ATTACK
SURFACE
Retaining personally identifiable customer data in more than
one location is analogous to creating photocopies of your
Social Security card and scattering them throughout your
apartment, thereby increasing the probability of
unauthorized discovery. Minimizing the number of copies of
this data reduces the attack surface.
Retaining sensitive data in a test server could potentially
make it harder to meet deletion requirements, since, for
example, data could be copied to other locations from a test
server. These other locations may not be known or
accessible to automated processes that enforce other privacy
controls, like anonymization.
Encrypting just the personal data in the test copy was
explored as a solution but abandoned. In evaluating the
encryption option, it turned out that different services were
using their own subsets of fields that they’d need to decrypt
in order to run their tests. This would require significant key-
management infrastructure and logic to map tests, data, and
keys. The cost for this setup was deemed too high, so the
company explored an option where they’d continue the
weekly refresh with more modest privacy protections.

## Page 645

POTENTIAL MITIGATIONS EXPLORED AND
ABANDONED
The company attempted to encrypt just the sensitive fields,
like email address, IP address, etc., in the test server.
However, the infrastructure team that maintained the test
server got many requests from engineers wanting those
fields decrypted. The infrastructure team, already stretched
thin, dropped this plan as well.
There was another attempt to scramble and obfuscate
sensitive data from the production servers before a copy was
transferred to the test server. This plan ran into trouble as
well.
The weekly refresh was initiated on Thursday and
culminated on Sunday so as to make the data available on
Monday for testing. There was no easy way to modify the
data files directly. The only way to modify or alter the data
was to rewrite the mutations for the entire dataset, which
would slow down the refresh and affect test schedules.
Modifying terabytes of data in Cassandra generally would
take weeks and not suit the weekly refresh schedules. In a
choice between security and productivity, the latter once
again won out.
As a result, the company ended up with real production data
in a test server that was accessed by prototype apps; these
apps had even more access than the release-ready versions
of those apps did in the production server. Additionally, the
test apps had other vulnerabilities endemic to fast-moving

## Page 646

companies: reused or weak credentials, credentials in the
code itself, verbose logging that may include sensitive data,
limited security testing, and reduced alerting.
As new engineers joined the company, there was limited
training and documentation on the differences between the
test and production accounts, even as the use of production
data in the test server increased. The testing server
remained unprotected while the sensitive data gushing into
it rose, and the attendant privacy risks increased.
This practice persisted even as the engineers using it found
it suboptimal. For example, engineers who used the test
server often had to run multiple queries before they found
data that met their needs. This means they often wasted
company resources and exposed and logged sensitive data
that proved useless.
As you saw in figure 10.1, the data in the test server was
constantly changing even as it was being used. This occurred
because multiple teams were concurrently using the single
copy of production data that sat in the test server. This led
to failed tests and repeat attempts.
TAKEAWAY FOR ENGINEERS AND TECHNOLOGISTS
The lesson for engineers and technical program managers is
simple: your company is almost certainly accumulating
security risks because of habit and inertia. These risks will
one day result in privacy harms, and when that occurs, you
will be left with a paper trail of half-measures and the

## Page 647

realization that enough people were aware of these risks and
yet did not address them.
Your company may not have the exact same issues as the
ones caused by this weekly refresh, but it may have others
that are similar. Even as I helped this specific company
migrate away from the weekly refresh, I helped them build a
more strategic risk-reduction model.
In the next subsection, we will look at such an approach to
strengthening security and improving privacy without
alienating engineering stakeholders.
10.1.3 An enterprise risk model for security and
privacy
Given the dissemination of data across companies,
depending on perimeter security and detection capabilities
alone is inadequate. Industry consensus is increasingly
adopting a zero-trust model that focuses on always verifying
the identity of users, devices, and applications within the
network while upholding the principle of least privilege.
Wide-open access to production data is one of the ways
attackers can move laterally and breach a company’s
network and data.
The process of mapping user identities to access privileges is
complex. An assessment of this requirement often covers all
layers of a company’s platform, including administration
tools, hosts, containers, data stores, and even APIs.

## Page 648

Given that, I recommend that companies build a two-
pronged strategy that starts with automated detection and
closes with an evolving risk management matrix. We will
first look at the automated detection approach.
AUTOMATED DETECTION FOR ATTACK SURFACE
MANAGEMENT
In the weekly refresh example, you saw examples of
security risk embedded into processes and infrastructure.
The only way to stay ahead of these risks is the
“thermometer and thermostat” approach—measure the
status quo, much like a thermometer tells you the
temperature, and then take action to alter the status quo,
like a thermostat does by helping heat or cool the room. In
the data protection analog, you’d want to build automation
that detects these risks and proactively mitigates them.
Smaller companies may not have privacy specialists or
engineers on their payroll, especially during early growth
stages. But they may have invested in IT, application
security (AppSec), or security operations (SecOps)
specialists. These companies can leverage those specialists
to fix security issues and in turn address privacy gaps.
Technical program managers could, for example, work with
AppSec and SecOps to build a number of mechanisms to find
code repositories that may be storing sensitive materials,
such as credentials or private keys. These mechanisms
would then feed a workflow that allows program managers
to engage the repository owners and both remediate the

## Page 649

issue and educate engineers on secure and supported
methods for handling secret data. For companies using
enterprise cloud services, these mechanisms could be
further automated to detect and respond to
misconfigurations and anomalous access of cloud storage
resources.
Rather than creating multiple locations for sensitive data
that, as you have already seen, create inefficiencies and
risks, the company could take a different approach.
Engineers could build a service for a number of security
functions, including the secure storage of secrets, keys, and
data. This service could be used to store not just privacy-
related data but also business IP, and access would be
restricted and audited. This approach would help win
business support and funding, since it would be seen as a
business enabler rather than a privacy imposition.
One of the reasons the aforementioned company persisted
with the weekly refresh was credential management. They
could not generate custom credentials for production access
and felt like that necessitated data duplication with freer
access. I helped drive a program that implemented an AWS
capability called IAM roles for EC2 to access AWS resources
from their EC2 instances. This service provides dynamic and
ephemeral credentials that avoid many of the security issues
associated with static and long-lived credentials. That way,
the company was able to grant production access for many
tests using credentials that were mapped to use cases and
timelines.

## Page 650

As you also saw in the weekly refresh use case, the
accumulation of risks was gradual, so it is likely that no one
person internally could quantify the likelihood and impact of
these risks. While we will shortly build a framework for such
risk management, engineers and technical leaders at all
types of companies may want to keep themselves honest
with outside perspectives.
Your AppSec and IT teams should initiate a Bug Bounty
program, which would allow external security researchers to
responsibly disclose security vulnerabilities in your systems
and receive appropriate compensation. Your internal
technical leaders would need to work with these researchers
to ensure any Bug Bounty reports involving access to
personal data are handled appropriately and legally.
These ideas are by no means exhaustive, but they do point
to several solutions that will stop the decentralized
accumulation of risk by way of unaddressed bad habits. Left
unchanged, those risks and habits will create technical debt
that, while invisible on the company’s balance sheet, will
demand repayment. This is why the company will need a
strategic approach to security, and an examination of such a
strategy is up next.
SECURITY RISK MANAGEMENT IMPLEMENTATION
After addressing the most gaping security issues connected
to the weekly refresh, I worked with the aforementioned
company to build out their security and privacy apparatus.
Before addressing data privacy, I helped them migrate to a

## Page 651

more principled and intentional cloud and security
infrastructure to scale their service.
The first step was to map services and applications that used
data to the AWS accounts that housed the data. When I
arrived, the company had dozens of separate AWS accounts
to run its services and business. This growth and
architecture began organically and was influenced by timing,
resource constraints, compliance drivers, and varying
business needs. As a result, their architecture was largely
devoid of organizing principles, creating operational
variances that made it impossible to operate efficiently and
effectively.
For example, two distinct services with no shared objectives
—payments and user interface personalization—used the
same accounts and therefore the same test data. This made
it impossible to provide security tailored to the specific
service or to meaningfully customize the data itself for
testing. The purpose of my initiative was to bring the
company’s AWS infrastructure in line with best practices for
security. In order to achieve this goal, we sought account
separation so that there was a tighter mapping between the
storage account and service.
This is where the concept of service residency (which
account a given application should be hosted in) is critical.
The configuration of the account has implications on the
robustness of the service itself.
If or when your company attempts to design such an
architecture, you will notice that decisions about service

## Page 652

residency are rarely completely deterministic. That said, I
recommend using the following principles when determining
the destination account for a given service or resource:
Business purpose—What is the business purpose of
the system or resource? This question will help you
conduct a sort of service affinity by asking several
follow-ups:
Is it part of the core service?
Is it part of a critical ancillary capability like payment
processing, or other support applications like
security monitoring, platform infrastructure, or big
data processing?
Is it part of internally oriented services for internal
employees like IT systems or expense management?
You will want to consider the business purpose to
be a primary mechanism for determining service
residency.
Service and risk affinity—Related to business
purpose is the idea of service and risk affinity.
Systems with the same business purpose (such as
studio support) are likely to have dependencies on
each other and have similar risk profiles and user
populations. This affinity helps determine service
residency.

## Page 653

Compliance requirements—Is the service within
the scope of regulatory compliance such as
Payment Card Industry Data Security Standard
(PCI) or the Sarbanes Oxley Act of 2002 (SOX)?
Regulatory-sensitive systems may have restricted
access requirements that are more easily
facilitated by a separate and more isolated account
environment.
Ownership—Each account will be owned by a
single team, even if the account is multi-tenant
and the data and applications come from multiple
owners. This team is responsible for defining the
organizing principles of the applications and
systems within their account. As such, the team
that owns the account must agree that the service
or data should be collocated in their account.
Absence of general purpose buckets—Companies
should move away from broad general purpose
buckets and instead create buckets for applications
and individual teams where appropriate. This will
identify bucket and data ownership for teams that
utilize S3.
So far, you have seen automation to detect homegrown
vulnerabilities and account consolidation as security
improvements. Now we will look at implementing parallel
tracks to improve security across the board so as to accrue
privacy benefits rather than technical debt and risk. For each
track, we will enumerate

## Page 654

Principle—The business and security impact of the
specific track
What and why—The business justification, so as to
define the scope and business case
Suboptimal starting point
Potential vulnerabilities
Desired (end) state
Capabilities
I recommend three tracks that engineers and technical
leaders can optimize: service segmentation, defense in
depth, and supportability. We’ll look at each of those in turn.
SERVICE SEGMENTATION
The implementation details of service segmentation are as
follows:
Principle—Limit blast radius and enforce “least
privilege” access model.
What—The goal is to limit the impact of critical
events, such as security incidents (such as a data
breach) or capacity limits (such as API throttling or
resource exhaustion). Every service will only be
able to access the information and resources that
are necessary for its legitimate purpose.
Why—This track will limit the number of avenues
that an attacker might have to compromise critical
systems or data and therefore reduce the impact
of compromise.

## Page 655

Suboptimal starting point—Because of chaotic
growth, there is often no particular rationale with
respect to the resources grouped within an
account. Critical services are mixed in with non-
critical services across various domains and with
varying levels of security and access requirements
(for example, core infrastructure services,
OpenConnect control plane, and dashboards may
be co-located). Services often have access to
unneeded and unrelated resources, services, and
data, and application owners are able to add
access to arbitrary system resources. All virtual
private clouds (VPCs) in the network could be
peered with all other VPCs, enabling network
connectivity and reachability between any system
within the environment and any other system.
Potential vulnerabilities—Because of these gaps,
attackers have more straightforward access to
valuable services and data given the broad access
provided to most systems, and any security issue
can rapidly spread beyond the initial compromise
vector. For an attacker, getting an initial point of
compromise is not as important as you may
initially think, given that many companies have
many entry points that will provide access to
valuable data.

## Page 656

Desired (end) state—The company should strive
for a more purposeful account structure, into
which applications are deployed based on affinity,
ownership, and similar access requirements and
configurations. Services should be able to access
only the information and resources that are
required for their purpose. Using automation and
data analysis, the IT leads should strike a balance
between delegating administration to improve
operational efficiency while maintaining oversight
over the infrastructure for security.
Capabilities—The IT team should leverage separate
accounts to help define boundaries and provide
strong and natural blast-radius isolation. Ensure all
services implement appropriate authentication and
authorization protocols.
DEFENSE IN DEPTH
The utilization of data in modern services grows as more use
cases emerge. This inevitably leads to more touchpoints and
vulnerabilities. Therefore, building a defense mechanism that
allows for granular risk assessment and remediation is
critical.
Principle—Have several layers of security.
What—The company should implement multiple
levels of security controls, placed throughout the
stack.

## Page 657

Why—The intent is to provide redundancy in the
event that a security control fails or a vulnerability
is exploited.
Suboptimal starting point—Overly permissive
security groups provide network access to
services, with few services performing application-
level authentication or additional restrictions.
Broad peering relationships assume correct and
complete functioning of other controls (such as
security groups and host firewalls) to restrict
network traffic. Some (not all) sensitive data is
encrypted at rest and in transit.
Potential vulnerabilities—Since smaller companies
do not have a dedicated security or privacy
function, one control tends to protect many
different services and data stores. As a result,
many controls are single points of failure and are
overly broad (such as security groups).
Compromising systems and data is easier, as fewer
controls need to be subverted. Consequently, a
data breach or AWS account compromise becomes
that much more impactful.

## Page 658

Desired (end) state—Implement multiple levels of
security controls throughout the stack. For
example, have multiple ways to protect against
attacks on data in transit or attacks on endpoints
or instances. Higher-level controls (such as TLS,
service authentication, and authorization) would
be broadly deployed to supplement lower-level
controls (such as security groups). As a next layer,
pervasive auditing and monitoring controls will
facilitate faster and more comprehensive detection
of issues early in the attack lifecycle.
Capabilities—There will need to be several
developer-focused capabilities at play. First,
provide developers with tools and context to make
timely decisions for their apps and to manage their
security group ecosystem. Implement mutual TLS
across the ecosystem to ensure secure
communication between services. Implement
robust and comprehensive monitoring of AWS
activity across the environment.
SUPPORTABILITY
This area refers to an apparatus for across-the-board system
visibility, ownership identity, and relationship management.
That way, privacy and security experts can preempt attacks
and mitigate impact.
Principle—Visibility, ownership, and dependency
management.

## Page 659

What—Infrastructure teams should know what is
present in the environment and how it operates.
Data flows and dependencies should be
understood and cataloged, as well as aligned with
accepted availability and security patterns. Any
special cases or exceptions should be known and
documented.
Why—This visibility reduces operational complexity
and supports availability, continuity, and disaster
recovery activities. This also helps with improved
detection to support security and privacy needs.
Suboptimal starting point—As with previous tracks,
companies build services in a rush, start data
collection to meet innovation needs, and then
generate accounts to manage access. As a result,
without central oversight, dependency
management becomes hard to manage. There is
often no authoritative ownership of accounts or of
the services, resources, and data within them, and
there is limited network and service-to-service
visibility. This culminates in circular dependencies
or dependencies that are not understood (and that
therefore cannot be planned for).

## Page 660

Potential vulnerabilities—This situation is akin to
trying to reconstruct a building after an
earthquake without images or blueprints. Outages
and issues (security and other types) take longer
to resolve than they should. Privacy regulations
may be unmet because of the lack of data
governance and maps. Data governance, discussed
elsewhere in this book, will be hampered by this.
Desired (end) state—As the company evolves its
data protection stance, all dependencies and data
flows need to be understood and aligned with
accepted availability and security patterns. This
could mean you need to include AWS
dependencies, third-party dependencies, native
service dependencies, cross-regional
dependencies, cross-account dependencies, etc.

## Page 661

Capabilities—Engineers and technical program
managers will need to identify (and require)
owners for all resources in the infrastructure and
ensure that discovery of ownership-related
metadata is simple and easy to integrate into
solutions and tools. Second, I recommend that
companies classify all resources on a number of
dimensions, including business purpose, service
and risk affinity, and compliance requirements.
This classification helps to ensure that engineers
dedicated to data protection are able to segment
resources, improve their ability to appropriately
secure sensitive data or resources critical to core
services, and support availability, continuity, and
disaster recovery activities. Third, it would be
helpful to analyze dependencies within and across
accounts (and regions). This insight will help
accelerate the process of migrating accounts, and
your system architects can take it into account
when making decisions around service residency.
Based on all of this legwork, the company will need to define
an intentional and deterministic account segmentation
strategy and persist with it over time.
In this section, we have looked at reducing and managing
the attack surface. Previously we have looked at reducing
the company’s data footprint by deleting and reducing data
risk via anonymization. However, the fact remains that you
will have data that, if it’s accessed and processed
unscrupulously, could lead to privacy harm. It therefore

## Page 662

behooves companies to invest in access control at the
perimeter level. The next section will dive deep into this
concept with practical examples.
10.2 Protecting privacy by managing
perimeter access
Reducing the attack surface area is critical, as you saw in
the last section, since it helps scale data protection.
Reducing the attack surface is like not keeping stacks of
cash in your house and so reducing your loss in the event of
a burglary. However, that does not rule out the need for a
strong front door and security system that will prevent an
intruder from getting in. For small and medium-sized
companies, it is critical to have automated and scalable
criteria set up to moderate access to their data and
infrastructure.
It is often hard to create a framework for such access
management, so I will offer one here: Companies must
create contextual access policies that assess risk factors,
such as device, network, location, IP address, and other
contexts at multiple steps of the authentication process.
Each time an access request is mapped to a policy, the
company can assess the risk level for that access request.
The next step is to pair the risk levels with appropriate
access decisions, such as allowing or denying access or
prompting for multifactor authentication (MFA).

## Page 663

To explain why such an investment is necessary, we will walk
through an example where data security vulnerabilities
caused business, security, and privacy risk. This example will
serve as a guide for what not to do. After that, we will look
at how to do things right.
10.2.1 The Target breach
In December 2013, Target released a statement confirming a
breach, saying that 40 million credit and debit card accounts
may have been impacted between Nov. 27 and Dec. 15,
2013.1 The type of data stolen—also known as data track—
allows crooks to create counterfeit cards by encoding the
information onto any card with a magnetic stripe. If the
thieves were also able to intercept PIN data for debit
transactions, they would theoretically be able to reproduce
the stolen debit cards and use them to withdraw cash from
ATMs.2 There cannot be a bigger example of a security
breach that led to a privacy violation.
This story exploded in the cybersecurity and privacy circles
when blogger Brian Krebs reported that hackers broke into
the retailer’s network using login credentials stolen from a
heating, ventilation, and air conditioning company that did
work for Target at a number of locations.3 Since its initial
disclosure, Target has made an argument that many others
in its position have made before and since. The company’s
leadership sent two messages: their data-protection and
threat-defense programs were reliable and solid, and the
breach occurred because the attack was unprecedented and
therefore not easily preventable.

## Page 664

Subsequent analysis painted a different picture. One of the
counterpoints came from Jody Brazil, founder and CTO at
security vendor FireMon. Brazil suggested that there was
nothing especially sophisticated about the breach. This was
an issue where Target paid a price for a lack of segmentation
of its network, leading to an “all or nothing” approach.
Giving Fazio access to do their job meant Target had given
them a lot more access than was required, such as to
Target’s payment systems. This painstaking work of system
segmentation allows for more targeted access and more
focused protection. Too many companies fail to act on this
until it is too late.4
For engineering and technical specialists at companies that
handle large volumes of sensitive customer data, it may be
hard to understand the underlying security vulnerabilities
that caused this breach. This is especially the case since the
amount of commentary and analysis on security and privacy
has exploded, but readers are often more confused about
the facts and necessary next steps at the end of the
discussion than before.
Therefore, we will look at the workflow of the Target breach
so that you can account for these vulnerabilities as you set
up your own IT security.5 Figure 10.2 shows how the Target
breach was incremental, methodical, and, in the end,
consequential.

## Page 665

Figure 10.2 The sequence of the Target breach
As you can see in figure 10.2, the attackers were purposeful
in their research and penetration of Target’s systems,
compromising applications within the systems and then
stealing the data by first accessing it and then expanding
their privileges. While the subsections that follow will offer
more detail, the key point for engineers at smaller and fast-
moving companies to understand is that ignoring or
underestimating minor risks can prove to be fatal. As we
dive into the details, you will see that the tale of Target was
one of missed opportunities and catastrophic outcomes.
RECON TO DETECT NETWORK VULNERABILITIES

## Page 666

As you have seen elsewhere in the book, data about you
that is available elsewhere can lead to security and privacy
vulnerabilities. The same is true for network infrastructure.
In the Target breach case, research suggests that attackers
may have gleaned information about Target’s infrastructure
in preparation for the breach. For example, according to
researcher Teri Radichel, there was a detailed case study on
Microsoft’s website that described how Target used key
Microsoft capabilities: virtualization software and centralized
name resolution. The Microsoft documentation also
described how Target used the Microsoft System Center
Configuration Manager to deploy security patches and
system updates. Microsoft’s case study also described
Target’s technical infrastructure, and the description of the
point of sale system may have been of significant value to
the attackers.6
Thus, even before interacting with the Target infrastructure,
the hackers had a blueprint of the attack surface. Engineers
configuring your company’s network access may wish to
account for such freely available information.
As is often the case with modern distributed systems with
different owners, it was not too difficult to unearth links
between Target’s infrastructure and its vendors. Krebs
pointed out that Target’s Supplier Portal was freely available
on the web. The portal was aimed at educating new and
existing vendors and partners on how to exchange
information and conduct transactions with Target. That
portal also contained a page that listed HVAC and
refrigeration companies.7

## Page 667

The lesson here is that engineers who care about privacy
and security must look at their vendors as a potential risk
vector as well.
COMPROMISING THE THIRD-PARTY VENDOR
The attackers started with stealing the credentials of Target’s
HVAC vendor, Fazio Mechanical Services. According to
KrebsonSecurity, which first broke the story of the breach,
the attackers infected Fazio with general-purpose malware
known as Citadel through an email phishing campaign.8
With Citadel in place, the attackers waited until the malware
offered Fazio Mechanical’s login credentials.9 The attackers
then used the stolen credentials to gain access to Target-
hosted web services dedicated to vendors.
Companies with limited budgets or ones that lack targeted
expertise are often tempted to use third-party vendors for
specialized tasks, and that thinking may have proved to be
fatal in this case. Many such vendors themselves operate
lean and hence take a dim view of security investments,
doing the bare minimum in order to cut costs.
Fazio’s leaders said the company did not perform remote
monitoring or control of heating, cooling, or refrigeration
systems for Target. In their telling, Fazio’s data connection
with Target was exclusively for electronic billing, contract
submission, and project management.
The attackers now had access to an internal web application
hosted on Target’s internal network, but the application did

## Page 668

not allow for arbitrary command execution, a necessity to
compromise the machine.10 Because of such design
decisions, it is often assumed that access to a single
application limits the privacy and security exposure. Target
found out otherwise. The lesson for engineers and program
managers is to vet third-party vendors that have access to
your network.
EXPLOITING A WEB APPLICATION VULNERABILITY
Small-time and limited-purpose vendors often offer
capabilities to upload documents. Either because of cost or
gullibility, the vendors assume that this upload capability will
only be used for documents and not malicious files. As such,
no security checks are performed to ensure that executable
files are not uploaded by outside bad actors.
The attackers used this gap to upload a PHP file, of the kind
that is used for running scripts within web applications. The
malicious script was probably a “web shell,” a web-based
backdoor that allowed the attackers to upload files and
execute arbitrary operating system commands. The
attackers made the file look like a popular PHP component to
make it resemble a legitimate file and hide it in plain sight.
At this point, the attackers were inside the gates and had
the ability to run scripts. However, what they still needed
was the location of the customer data. There is a security
and privacy lesson here for companies: what you permit into
your ecosystem can determine what ends up leaving your

## Page 669

infrastructure. Continuous monitoring of new entrants and
their capabilities is critical.
SEARCHING FOR CUSTOMER DATA
It is at this stage that the security vulnerability became a
privacy impact. The attackers, having penetrated the
network periphery, needed to learn where the customer data
was located before their intrusion was detected.
According to Thor Olavsrud, writing for CIO Online, the key
vector the attackers homed in on was Target’s Active
Directory. The directory served as a data repository for
users, members, and services. Using the standard LDAP
protocol, the attackers were able to query Active Directory,
and they may not have needed to know which service did
what or served whom. It was quite possible that they
searched for services matching the value “MSSQLSvc,” and
the names of the services helped identify the ones they
wished to exploit, like the ones handling billing. Having
obtained the names and deciphered the functions of the
target services, a simple querying of the DNS server was all
it probably took to get their IP addresses.
11
This is where behavioral analytics can help: if someone were
trying to access your services for legitimate purposes, they
should not need to retrieve all services. Having security
monitoring helps protect privacy as well; engineers need to
invest in algorithms that detect fraudulent and anomalous
behavior when outsiders and insiders try to access sensitive
data.

## Page 670

GAINING AND MAINTAINING ACCESS TO CUSTOMER
DATA
Having identified the location of sensitive data, the attackers
used a technique called Pass-the-Hash (PtH) to gain access
to a hash token that would allow them to impersonate the
Active Directory administrator. With PtH, a bad actor doesn’t
need to decrypt the hash to obtain a plain text password.
PtH attacks exploit the authentication protocol, as the
password hash remains static for every session until the
password is rotated (until the administrator changes the
password). Attackers commonly obtain hashes by scraping a
system’s active memory and other techniques.12
Fraudulently obtaining administrator access is ineffective if
the administrator changes their password. Anticipating that
possibility, the attackers used their stolen privileges to
create a new account and add it to the Domain Admins
group. This gave the newly created account the privileges
the attackers required while eliminating the possibility that
someone else would change the password.13
The lesson for engineers is clear: there needs to be more
layered and continuous access control and authentication for
anyone seeking a way into your network. Adding more
friction to the intake process is worth it, given the risks to
customer privacy should a bad actor find their way in and
identify where your crown jewels are located.
PROPAGATING ACCESS TO CUSTOMER DATA

## Page 671

At this point, the attackers needed to bypass firewalls and
other network-based security solutions that limited direct
access to their targets, and then run remote processes on
various machines in the chain toward their targets.
The attackers used their credentials in conjunction with the
Microsoft PSExec utility (a telnet-replacement for executing
processes on other systems) and the Windows internal
Remote Desktop (RDP) client. Both tools use Active
Directory to authenticate and authorize the user, which
means Active Directory is aware of this activity if anyone is
looking for it.
Once the attackers had access to the targeted systems, they
used the Microsoft Orchestrator management solution to
gain persistent access, which allowed them to remotely
execute arbitrary code on the compromised servers.14
At the risk of being repetitive: this additional vulnerability
shows yet again how critical it is to ensure your monitoring
capabilities are continuous and cover third parties, especially
given Fazio’s limited view of their data protection obligations.
As stated before, Fazio’s leaders said the company did not
perform remote monitoring or control of heating, cooling, or
refrigeration systems for Target. In their telling, Fazio’s data
connection with Target was exclusively for electronic billing,
contract submission, and project management.
STEALING CUSTOMER PERSONAL DATA AND CREDIT
CARD DATA

## Page 672

Section 3.2 of the PCI-DSS standard states: “Do not store
sensitive authentication data after authorization (even if
encrypted). If sensitive authentication data is received,
render all data unrecoverable upon completion of the
authorization process.”15 Since Target was PCI-compliant at
the time of the breach, the databases did not store any
credit-card-specific data. So while the attackers had
managed to access the PII of 70 million Target customers, it
did not have access to their credit cards.
However, as discussed in the “Searching for Customer Data”
and “Gaining and Maintaining Access to Customer Data”
sections previously, the attackers had obtained access to
Target’s point-of-sale machines. They also had the ability to
execute programs remotely on these machines. They used
these combined capabilities to install malware that they then
used to scan the memory of infected machines and save any
credit cards found to a local file.
The lesson for engineers here is that smaller security
vulnerabilities that are not top of mind often accumulate to
pose serious privacy threats, and they can lead to the
exfiltration of sensitive customer data.
Researcher Tal Be’ery, whose work I have cited throughout
this discussion, states that “The initial penetration point is
not the story, because eventually you have to assume you’re
going to get breached.... You cannot assume otherwise. You
have to be prepared and have an incident response plan for
what to do when you are breached. The real problem arises
when malware is able to enable an attacker to penetrate
deeper into the network.”16

## Page 673

SENDING THE STOLEN DATA OUTSIDE THE COMPANY’S
NETWORK
Once the malware obtained the credit card data, it created a
remote fileshare on an FTP-enabled machine using a
Windows command and the Domain Admin credentials. It
would periodically copy its local file to the remote share.
These activities would have been authorized against Activity
Directory, making it aware of the activity. Had there been
any monitoring of data leaving the company, all previous
mistakes notwithstanding, the company and its partners
may have been able to prevent the loss of this data.
Thor Olavsrud, whose analysis this section has cited
(published by CIO and later by CSO), provides several
hands-on techniques for engineers wishing to protect their
company’s privacy and security. I have drawn from and
added to these techniques, but you may also wish to look up
Olavsrud’s original article.17
Create a more robust access controls regime. This
is where privacy and security engineers need to
work with data scientists by categorizing data
access requests. You will need to define “normal”
and “expected” access requests and block the ones
that deviate from that norm.
Given the rapidity with which access can result in
exfiltration, multifactor authentication (MFA) is a
critical “friction point” for managing leaks of user
authentication data.

## Page 674

Just as you would want to first categorize and then
inventory, you will want access to networks to be
tiered as well. That way, how someone connects to
your services and data stores determines the fine-
grained access they have. Free-for-all access to
data is unwise, and broad access to networks can
similarly be problematic. Researcher Teri Radichel
states that limited administrative privileges may
have prevented inserting software to get into the
deployment process used to infect the POS
systems with malware.18 This is a cultural shift
more than an engineering challenge; one that may
need to walk back engineers’ sense of entitlement
to ubiquitous and perpetual access to sensitive
data.
Given the prevalence of shadow IT and distributed
service ownership, you will want to assess whether
new users and their privileges are in line with
demonstrable needs. You will also want to check
for irregular activities performed by user accounts
with the ability to grant other users access. This is
especially important in companies without top-
down command-and-control shops where rigid
adherence to policy drives the addition of user
privileges. This may add initial latency, but you will
avoid a “power user” situation, where a rogue
account with strong access extricates data without
any guardrails.

## Page 675

Since attackers often come sniffing for low-
hanging fruit (small security vulnerabilities) before
attacking sensitive data, you need to monitor any
queries that seem optimized to gather intelligence.
If you see a user making such requests to services
or for data, that could be an indication that
something suboptimal is afoot.
For servers that are dedicated to specific services
or users or that hold sensitive data, you will want
to maintain an explicit list of users who are
permitted access. The default access response
should be “no” unless the user seeking access
belongs to that list.
Anti-malware solutions can be effective if the
attacker is using homegrown tools, but most
sophisticated attackers tend to use off-the-shelf
enterprise tools to fool anti-malware solutions. You
will want to diversify accordingly.
Active Directory can serve as both the gateway as
well as the vehicle for outside attacks, so your
automated controls will need to track its use for
the life of any attack.
Besides the preceding tips, experts that I speak to
recommend enforcing MFA on everything that is internet-
facing (VPN, email, chat programs, etc.). Given distributed
SaaS and data storage, the infrastructure perimeter has
become more porous, and network access has become more
global, so continuous MFA is important and will help reduce
the chances of account compromise.

## Page 676

TIP The old approach that optimized for perimeter-based access control is
insufficient, given the spread of data and infrastructure and the ability of attackers
to hijack systems to gain additional access once they penetrate the perimeter.
Access management, therefore, needs to be continuous and intelligent.
Additional hands-on best practices from researcher Teri
Radichel include maintenance, monitoring, and analysis of
audit logs.19 These logs could help you watch for anomalies
like malformed packets and packets with unexpected sizes or
data. While voluminous, these logs could flag the egress of
large amounts of data. These logs could also record
unexpected traffic to and from critical systems. An example
of an anomaly would be a payments system shedding data
outside of its normal cycle. These anomalies are often signs
that someone unwelcome is committing unwanted acts upon
sensitive data.
Radichel also suggests that companies “profile accounts for
normal activity and usage periods to spot anomalies.”
Account privileges should be limited to need to know. The
company’s IT and security engineers must “segregate
account access across network tiers. Disable and delete
unneeded accounts.”20 The Target and Colonial Pipeline
issues both highlight the risks of broad access as well as
those of unmaintained dormant accounts. This is another
cultural change moment, where companies need to optimize
for the quality of their user engagement rather than just the
quantity.
When it comes to vendor portals, Teri Radichel recommends
“Penetration Tests and Red Team Exercises: Since this
system is on the perimeter at the first layer of defense....”21

## Page 677

Just as preventing entry to bad actors is critical, it is equally
critical that you ensure that data stored in specific locations
does not leave the network perimeter. As such, URL filtering
for egress capabilities may help limit outbound access.
Target’s response to the breach included the implementation
of many of these ideas.22
The vendor vulnerabilities we have seen thus far are
important, but they’re hardly exclusive to low-tech single-
purpose vendors. The next subsection will show why.
10.2.2 MongoDB security weaknesses
MongoDB was a popular choice for developers during the
transition to cloud-based servers, such as those hosted by
Amazon AWS. I had to become conversant overnight in
MongoDB during my time at Nike, when I led the identity
management team. That age represented significant
adoption of the MongoDB technology.
MongoDB is particularly useful in storing unstructured data;
its document data model stores all related data together
within a single document, making it much more flexible than
the rigid structure of the relational database model.23
However, MongoDB has been subjected to more high-profile
attacks than any other database platform.
Early releases of MongoDB allowed the installation of a
database server with no authentication mechanism enabled.
In simple terms, the default MongoDB installation was
insecure. This meant that anybody who had access to the
database port would be able to connect to the database with

## Page 678

unlimited authority. It is possible that the central purpose of
MongoDB—low-latency access of massive volumes of data—
caused this vulnerability. However, given the proliferation of
sensitive data across companies, this is not purely a security
risk but a major privacy risk, and one that is inside the
perimeter, not one that emanates from a vendor.
The period from 2014 through 2017 was significant because
during this time there was an expansion of both the online
identity space and the amount of unstructured data that
companies were accessing. Databases like Cassandra and
MongoDB were beneficiaries of this change. They were also
targets of attacks, with MongoDB databases being routinely
attacked and with some attacks succeeding in exfiltrating
data. In 2017 there were several ransomware attacks
targeted at MongoDB cloud databases. Given the nature of
ransomware attacks, the data was not recovered in many of
these instances.24
As data protection laws ramped up and breaches became
common, MongoDB made changes.25
MongoDB 3.6 (2017) closed external access by
default, resulting in low discoverability by potential
attackers. This did not fix every vulnerability, but it
did reduce the likelihood that default installations
were attacked.
MongoDB 3.6 also introduced IP allowlisting, which
meant that access was not automatically granted
and the default behavior was to deny access
outside of approved IP addresses.

## Page 679

In version 4.0, the Atlas cloud server’s addition of
LDAP authentication support meant that there was
a higher bar to initial entry. On the storage side,
the disk storage was encrypted with the customer
in control of the keys. This helped reduce the
likelihood that loss of storage was tantamount to
loss of data. Version 4.2 built on the encryption
progress by way of client-side encryption as well
as field-level encryption. All these changes, put
together, made it difficult to execute an attack and
exfiltrate data.
MongoDB 4.4 added x509 authentication and
integration with the AWS Identity and Access
Management (IAM) system, thereby juxtaposing
encryption with AWS’s access-control regime.
In spite of these improvements, as of July 24, 2020,
thousands of MongoDB databases were destroyed by the
Meow attack.
After seeing how consistently database breaches were
occurring, researchers planted honeypots to find out how
these attacks happen, where the threats are coming from,
and how quickly thay take place. A honeypot is “a computer
or computer system intended to mimic likely targets of
cyberattacks.”26 The researchers set up a number of
unsecured MongoDB honeypots across the web, each filled
with fake data. They monitored network traffic for malicious
activity; if password hashes were exfiltrated and seen
crossing the wire, that was an indication that a database was
breached.27

## Page 680

The research showed continuous attacks on MongoDB online
databases. The attacks seemed automatically configured
toward newly online databases, and were high volume so as
to exploit vulnerabilities. In one sample, unsecured
databases were compromised in less than 24 hours on
average.28
During the research, at least one of the honeypots was
successfully attacked and held to ransom within a minute of
being online. In a modus operandi that seems all too familiar
now, the attacker erased the database and left a ransom
note, asking for a Bitcoin payment in exchange for the data.
Note that in such situations there is no guarantee that the
attacker still has the data or is willing to return it after
money changes hands.
The researchers set up other honeypots, and in that
research, an exposed Mongo database was breached within
13 hours of internet connectivity. One breach, which the
researchers believe to be the fastest recorded, was carried
out nine minutes after the database setup was complete.29
Researcher Chris Wallis states that responding to such
attacks before nine minutes may be hard, and this is
especially true for smaller companies. Wallis points out that
there are two challenges that companies face: first,
detecting an unsecured database and assessing the risk
level; and second, troubleshooting the issue and closing the
security gap. Completing both these tasks in 13 hours is
hard enough, Wallis says, making nine minutes a much
bigger challenge.30

## Page 681

As security expert Guy Harrison states, “MongoDB’s own
Atlas database as a service platform is fully secured and
immune from such attacks. Only systems configured
manually on cloud-based virtual machines will exhibit these
vulnerabilities.”31 In that sense, only those systems that
were configured manually on cloud-based virtual machines
exhibit these vulnerabilities. So all a business has to do is
use MongoDB Atlas to achieve a high level of cloud database
security.
Herein lies the risk for small businesses with limited
budgets. They may not have the funds to procure the top-of-
line Atlas database, and their manual configurations may
rely on MongoDB defaults, thereby inheriting privacy and
security vulnerabilities. It is also possible that most
unsecured MongoDB databases are development or test
instances using obsolete versions of MongoDB code.
However, as you have seen, test and development instances
can contain production data with limited access and audit
controls. Such instances, and accounts to access them, are
often not retired by small businesses. Therefore, while this
issue is not endemic to MongoDB, the progression of default
settings and lax security practices could create a data
exfiltration possibility and therefore a privacy risk.
The lessons for small and medium-sized companies and the
engineering community are clear: enterprises running
MongoDB should review their installations to ascertain they
are secure and not exposed to the internet.
The examples we have looked at so far have offered
defensive hands-on techniques for engineers to protect their

## Page 682

infrastructure. The next subsection will provide some
proactive best practices in authorization management.
10.2.3 Authorization best practices
Many companies set up their authorization design during
their early growth stage. Mistakes from that growth phase
tend to haunt companies at a time not of their choosing. In
this subsection, I will provide some best practices that will
serve as a checklist for such companies as they evolve their
authorization posture.
The real challenge companies face is that of fine-grained
authorization. Authentication has been discussed for long
enough that it has standards based on OAuth 2, SAML, and
OpenID Connect. By contrast, there is no analog for
authorization in terms of how it may be consistently
implemented across different services. As a result, each
service owner is free to customize permissions, privileges,
and roles. This results in a bespoke access-control regime
rather than a fine-grained authorization architecture that can
be mapped to risk and usage.32
According to security researcher Omri Gazitt, your approach
to authorization needs to adhere to certain best practices.33
We will consider some of these practices in detail in the
following subsections.
ENFORCING SEPARATION OF AUTHORIZATION POLICY
FROM CODE

## Page 683

Engineers may be tempted to decentralize authorization
policy and customize it for their service just as they do other
features, but this will pose problems as the service usage
and threats grow. For example,34
Even if individual services have bespoke
authorization policies, there may be a time when
you need to harmonize those policies across all
services. Making those changes on a per-service
level will get more expensive.
Given the rapid turnover in engineering and
security teams, it is often hard to understand why
authorization policies were set a certain way for a
specific service.
As companies grow because of mergers, they may
inherit services written in different languages. This
makes onerous not just the task of modifying the
authorization policy, but also potentially the rest of
the service as well.
Based on insights from Omri Gazitt, here are some
recommended best practices for delineating between policy
and code:35

## Page 684

There is a risk in joining applications and the
authorization policy, since it could breed
confirmation bias. You will be better off
implementing authorization policies using
languages or tools that are separate from the
service they govern. This could help address the
issue where engineers have an incorrect risk-
assessment of their services and tightly couple the
functionality of the service to the authorization
threshold to access the service.
Even as you separate the authorization policy from
the application itself, it is appropriate for the
application owner to have easy access to the
policy. You will want to apply the same rigor when
it comes to versioning and quality control. Since
the code and authorization logic are to remain
decoupled, you should map the policy version to
the code version for automated implementation
and auditing.
You may often need to change the authorization
policy without impacting application capabilities. In
this case, you will want to be able to make these
changes seamlessly. Otherwise, your policy could
be outdated, and that could lead to compliance or
other issues. Planning for this at an early stage
may help you respond to changes in laws,
enterprise customer needs, and security patches.
Additionally, I strongly recommend that, as a transition to
this separation mode, you create a first principle whereby in
cases where services have varying authorization policies,

## Page 685

you ensure that the strictest policy applies to all the
services. That way, as new services come online with more
advanced authorization policies, those policies would then
apply to the older services as well. This will help ensure
enforcement of policies at the account level rather than the
app level. This will also help you avoid a situation where an
ingenious engineer deploys a service without an
authorization policy.
If Target had these protections, they might have been able
to patch their vulnerabilities at scale. Many breaches and
privacy violations come down to insufficient enforcement of
authorization policies because services make their own
policies, and that makes scaling any fixes next to impossible.
MAKING AUTHORIZATION SECURE, SERVICE-BASED,
AND EASY TO INTEGRATE
Security and IT engineers and program managers at small
businesses must approach authorization with two
assumptions. Most engineers, if given the right tooling and
context, will do the right thing for privacy and security. The
same engineers, often because time is short and instructions
are confusing, may end up making sloppy mistakes.
To show how this could play out, let’s look at how bugs in
John Deere’s code base created a vulnerability. Engineers
often think of bugs in code as being distinct from how their
data can be protected. In this case, the bugs served as an
open door to the data of customers who owned John Deere
equipment and vehicles.36

## Page 686

The vulnerabilities, if exploited, would have exposed
personal data about John Deere’s customers, including their
physical address. According to the researcher, “on newer
farm equipment he was able to see the vehicle or equipment
owner’s name, their physical address, the equipment’s
unique ID, and its Vehicle Identification Number or VIN, the
identifying code for a specific car.”37
The researcher said that “the first vulnerability allowed
anyone to list all usernames on the John Deere Web Portal.”
This would be the equivalent of visiting a retail website and
being able to see the usernames of all the shoppers. If this
vulnerability were to go undetected, an attacker could easily
find out how many users had subscribed to the online portal.
This could be prevented if the website or the mobile app
were able to detect such requests. However, this is where
the second vulnerability was to become even more critical.
A remote unauthenticated attacker, which is to say someone
who was not even signed in, could simply remove the cookie
from the original request, so that each successive request
would seem like a new one. The attacker could make the
same request multiple times. Besides the weak
authentication protocol, the absence of a rate limit would
allow the attack to persist unabated. This limitless ability to
find usernames, coupled with being able to obtain personal
data on newer equipment, represented a strong attack
vector.
These gaps could be used by attackers to dox all John
Deere’s owners. According to the researcher, this
vulnerability was accessible via the John Deere Operations

## Page 687

Center Mobile app for Android and iOS and the
corresponding web version.
An attacker could obtain the requisite API cookie by just
signing up for the app without having purchased John Deere
equipment. They could then “expose any vehicle or
equipment owner’s name, physical address, equipment GUID
(permanent equipment ID) and the status of whether the
Terminal is remotely accessible via the RDA protocol via the
Vehicle Identification Number (VIN) API,” according to the
vulnerability report.
Cases like this one could be addressed by several techniques
recommended by researcher Omri Gazitt:38

## Page 688

Make policies secure by default—The danger in
using authentication tokens for policy decisions is
that the token may be outdated, or someone else
may be accessing the account. This is why your
policy needs to be conservative in that the default
policy outcome will be to disallow access, followed
by a real-time assessment of the credentials, the
account, and the privileges to which access is
being sought. This is akin to deeming users as
having opted-out of data collection by default and
respecting their privacy by having them
proactively opt in.
Lest you think this is a theoretical exercise, recently the
Venmo account of President Joe Biden was revealed. It
took researchers at Buzzfeed less than 10 minutes to
find it once they started looking. Not only were they able
to find the President’s account, but also a network of his
private social connections. The lesson here for app
developers is that engagement and privacy can be
inversely related if the app is not built carefully. The
features that drive engagement—the ability to pay
connections easily and invite friends to subscribe in
exchange for incentives—create a graph that makes data
leaks more impactful. In the case of President Biden,
this could have been a national security issue. For
regular everyday users, this represented a major privacy
concern because there was no way to predict how they
might be impacted by this gap. “Customers always have
the ability to make their transactions private and
determine their own privacy settings in the app” said

## Page 689

Venmo in response.39 This led to a demand by privacy
influencers to make transactions and friends private by
default. So “privacy by default” is an idea whose time
has come.
Delivering authorization as a service, rather than a
library—Delivering a developer solution as a library
instead of a service is an idea that works in theory,
not in practical adoption. Instead, if you deliver a
developer service, it may help provide a central
point of control and handle the work necessary to
scale the solution. Gazitt identifies this as a critical
reason why developers trust services like Stripe for
payments or Auth0 for authentication.

## Page 690

Make authorization services easy to integrate—In
many (if not most) cases, authorization services
will need to adapt to the services that drive
engagement and make the business money. Your
company’s CEO can extol their commitment to
security and privacy ad nauseum, but integrating
an authorization tool is akin to cleaning up after a
party where everyone imbibed and celebrated
without restraint.
As such, Gazitt recommends, you will want to build an
authorization service that integrates with your existing
identity and directory providers and offers a variety of
hosting models. It would need to have bindings and
samples for every language and framework, so service
owners can get it integrated in minutes.
Your authorization system must be flexible and
extensible. It should ideally integrate with standard
authentication systems so that the “AuthN to AuthZ”
transition is seamless. This implementation would
require that the authorization system accepts identity
information in a cryptographic token such as a
JavaScript Web Token (JWT). Authorization systems are
required to provide broad coverage ranging from
platform identity providers like Google and Azure to
federated identity providers like Okta to enterprise
directories like Active Directory.
In order to be comprehensive, the system should align
various kinds of identities, such as universal identifiers
like a Google ID, federated identities like Okta, and

## Page 691

enterprise identities like LDAP. That way, you can
maintain all the overlapping identities that map to a
single user. This will ensure that your authorization
policies provide the same outcome regardless of what
identity is used.
Additionally, the authorization policies must be available
quickly for any application-identity combination. If the
policy discovery and enforcement takes too long, there is
a danger that a less-than-ideal default setting gets used.
Measuring and testing for this is key.
Finally, Gazitt points out that this system must support
“REST and gRPC APIs for authorization, SDKs and
language bindings for popular languages and
frameworks, [and] simple conventions for organizing and
authoring policies for resources that are accessed using
standard architectural patterns (e.g., REST, GraphQL).”40
This is more important than many privacy newcomers
may realize: rapid integration will help you build models
that track user behavior, fraud attempts, and anomalies.
Therefore, ease of integration is critical in driving
developer adoption and consequently in minimizing
privacy risk. It will help make your business safer,
smarter, and cheaper.
VERIFYING THE STRENGTH OF DATA LINKS AND
VALIDATING AUTHENTICITY OF IDENTITY

## Page 692

You have so far seen how we can better protect the
perimeter, layer protections inside the perimeter, and make
those protections more applicable for adoption. But how do
we make those protections more effective so that we
achieve our main goal—protecting the customer’s data and
privacy?
Identity expert Robert McKay points out the risks in the
confined verification processes companies follow.41 This is
especially true for fast-moving companies that are desperate
for customer engagement. Companies often verify user
identities by validating information that in theory only the
real user would know, like your pet’s name or your mother’s
maiden name. Traditionally, identity verification is a linear
process where the person trying to authenticate provides
verifiable artifacts as proof. Depending on a company’s
workflow and risk appetite, the number of artifacts
requested could be high or low. The most intuitive example
is when we provide a Social Security number (SSN) or tax ID
number (TIN) to avail of financial services. There are many
avenues to verify that the SSN is linked to the person
providing it. The user may further need to provide a utility
bill as proof of residence.
However, those approaches have limitations as bad actors
become sophisticated. McKay says that “rather than
performing authentication through a series of data point
verifications, they should instead examine the linkages
between all the identity markers holistically over time.”42 The
reason behind the need for a new approach is that the

## Page 693

sequential pieces of data that drive the verification process
are becoming more easily obtainable by bad actors.
McKay describes an attack known as the man-in-the-middle
attack. While it’s possible to mitigate if mutual TLS is
correctly applied, this attack could be highly impactful given
the potency of phishing attempts, the insufficient application
of MFA, and the profligate presence of credentials in the dark
web. Figure 10.3 below shows how such an attack works
conceptually.
Figure 10.3 A man-in-the-middle attack
This attack is executed as follows:
1. The attacker sets up two parallel conversations
between a business and its customer.
2. The business believes it is connecting with the
customer, and the customer thinks they are talking
to the business. In reality, it is the attacker
interacting with both parties.

## Page 694

3. The attacker might initiate the scheme by
requesting the issuance of a one-time passcode via
a session on the business’s website. This has
become easier because people’s email addresses
tend to be more freely available online, and other
credentials are available due to other breaches on
the dark web.
4. In parallel, posing as the business, the attacker
calls the unwitting customer and, using social
engineering, convinces the individual to read off
the one-time passcode sent by the business.
5. The attacker then uses this information to log in to
the customer’s account and perform unauthorized
transactions.
6. Since the attacker was able to provide all
requested data to pass each point in the
verification process, access is granted.
Such attackers can also create fake identities using a
combination of genuine data that belongs to a customer and
fake data that may plausibly belong to that customer.
To get a sense of human engineering that drives
impersonation attacks, consider this: if you or I find that our
Social Security number is being used by someone else, it is
likely that we’d immediately take action. This is why some
attackers may use personal data belonging to children, the
elderly, and folks who are homeless. A stable or even
average credit history coupled with simple identity checks
(using information freely available on the internet) may
satisfy the verification threshold for many institutions.43

## Page 695

This occurs partly because of the number of transactions and
volume of data at play, and the dynamics where
engagement and low latency are the coin of the realm. This
state of affairs is suboptimal across the board—both for the
person whose identity is misused and the institution that
gets defrauded. An incident where security and privacy
harms occur almost always has more than one victim.
Even more dynamic techniques like location verification have
limitations, McKay correctly points out. Companies have
smartly incorporated the use of location data to verify
identity. One example is a bank adding extra layers of
verification if you happen to use their app from a brand new
location. In such cases, the application may send a one-time
code to a verified email or phone number. However, this
approach has loopholes ripe for abuse by wannabe
attackers. An attacker could be physically close to the
address of the customer so as to come up with a GPS
location that is close enough to fool the verification process.
This is where privacy protections are often in conflict. I have
stated elsewhere in the book that companies could abridge
the number of decimals in GPS coordinates they store for
location data. Doing so protects data privacy by making
users hard to identify in a cohort; on the flipside, the limited
precision of such data hurts the preciseness of the location
and leaves an open door for attackers.
Given these risks, what are engineers and technical program
managers to do when verifying user identity? McKay
recommends that they adopt a holistic view of identity
across online, offline, and device-based data and behaviors

## Page 696

over time. Such a process entails the following near-real-
time assessments:
Do not treat data points individually but correlate
them to each other and derive a single view of the
user’s identity. This way, you have a greater
chance of detecting an attack, since the attacker
now has to meet a higher verification threshold.
The validity of identity depends upon the
connection between individual data points. You will
need to look at each grouping of data points, their
age, how frequently they connect to one another,
etc. Examining the strength of these various
permutations could help you detect attacks faster
when those attacks use either legitimate data
points or a combination of real and fake data.
You could look at risk as not being attached merely
to the attacker but also to the device they use. You
could consider the recent usage of the mobile
device as well as whether SIM swapping or
spoofing have occurred. This individualized
assessment of the device is the next logical step
after assessing data points individually and
collectively.

## Page 697

Assign a risk factor to the person’s identity and
device collectively before moving forward with the
interaction. This step is about answering the
following question: Is this action appropriate from
this user using this device? This could help address
the attacks directed at low-tech users like the
elderly who do not frequently use their online
accounts and are the targets of attackers.
In the preceding four points, we start with an aggregated set
of data points, move on to groupings of individual data
points, followed by focusing on the device itself, and finally
considering a combination of the individual’s data points and
the device’s. In the progression of these ideas, you have risk
values affixed to each of these steps. You can now allow or
disallow access depending on your benchmarks and risk
appetite.
Building this intelligence over time is critical for companies,
since they have to balance the business need for rapidity,
the engineering need for simplicity, and concerns around
fairness and bias as well. The preceding criteria will enable
engineers to make risk-driven deterministic decisions around
letting users validate their accounts.
The company’s algorithms can then make decisions, with
close calls possibly escalated for human decision-making. A
continuous audit trail will allow engineers to revisit past
decisions, change the preceding criteria, and also adjust risk
value calculations.

## Page 698

So protecting privacy for your customers goes beyond
protecting data you have about your customers. You need to
think about processing that data en route to verify customer
identity as well.
Of course, the other key tension here is the need to often
collect data for security purposes (fraud detection, DDOS
prevention) and the privacy risk if the company were to
suffer a breach. It is imperative that engineers, especially
those who focus on security and privacy, emphasize the
need to collect only what is needed and retain it only for as
long as it is needed.
TIP It is imperative that data collection geared toward security adhere to data
minimization (collect only what is needed) and retention only for as long as needed.
Given the propensity and potency of modern breaches, companies need to avoid
turning a security initiative into a privacy problem.
In the next section, you will see how gaps in your
authorization logic can allow users more access than they
are supposed to have. The privacy risks in such a situation
are obvious.
10.2.4 Why continuous monitoring of accounts and
credentials is important
There are those who believe that engineers have gotten
wiser about the need for data protection, given the time that
has passed since the Target breach and the fact that the
stakes are now much higher. Their optimism seems
unwarranted in the face of recent evidence.

## Page 699

In early 2021, one of the nation’s largest pipelines, which
carries refined gasoline and jet fuel from Texas up the East
Coast to New York, was forced to shut down after being hit
by ransomware. This was the latest example of how
vulnerable America’s energy infrastructure could be to
cyberattacks. The operator of the system, Colonial Pipeline,
said that it had shut down its 5,500 miles of pipeline, which
it said carried 45 percent of the East Coast’s fuel supplies, in
an effort to contain the breach.44
You would think that a breach of this scale would emanate
from a compromise of equal magnitude. This would
especially be the case given the carnage that ensued: there
was a shortage of fuel and long lines across the East Coast.
However, this hack, at its core, was the outcome of a single
compromised password, according to a cybersecurity expert.
According to a Bloomberg report,45 hackers were able to
access the Colonial Pipeline networks because of a
vulnerability that should not have existed, given the lessons
that should have been learned from breaches at Target and
Equifax. The hackers used a virtual private network (VPN)
account that was set up to allow employees to remotely
access the company’s computer network. The part that
should be especially concerning is that the account was
dormant but had still retained its access to the network of
the company.
We have seen a few times over the course of this book that
the combination of data points can significantly magnify
vulnerabilities. In this case, the aforementioned account
coupled with the discovery of the account’s password inside

## Page 700

a batch of leaked passwords on the dark web was all it took.
It is impossible to know for certain how that credential
ended up on the dark web. Charles Carmakal, a security
expert interviewed in the Bloomberg article, surmised that
an employee of Colonial Pipelines could have used another
account with the same credentials, which then got hacked.
The number of identities and their mappings to privileges is
hard to update and protect, and one failure is sufficient for
attackers to swoop in.
Additionally, the VPN account did not use multifactor
authentication (MFA). In hindsight, an account that allowed
for remote access and had not been authenticated for a
while should have been a prime candidate for multifactor
authentication. The absence of this hurdle reduced any
friction from the attackers’ path. An investigation into
possible phishing attempts directed at the employee whose
account it was came up empty.
This means that the breach could have been the outcome of
A VPN account that may have been lying dormant
for a while
Lack of monitoring for account dormancy and
password reuse
Credential reuse, whereby someone used the same
password elsewhere on the internet that they used
for the VPN
Lack of MFA, due to which the failure of the basic
authentication layer led to a security failure

## Page 701

This exact set of events could occur in a hospital, grocery
chain, clothing store, fitness enterprise, gaming company,
etc. The privacy implications there would be staggering.
Therefore, it is vital that engineers follow best practices like
the following:
Enforce MFA as a best practice, especially each
time someone needs additional access or data. If
you are not certain how much access control to
apply, you could reply on behavioral analytics and
anomaly detection. With all that said, being
conservative and escalating the scrutiny is the
safer bet before granting additional and more
powerful privileges.
Disable accounts that are no longer in use and
change passwords for those accounts. That way,
even if an employee is naive enough to reuse the
same credentials elsewhere and that other account
is compromised, that failure does not become a
gateway into the business.
Search code repositories for plain text secrets
(passwords, identities, etc.), which all too often
lead to sensitive data that should be protected.
Keep an eye on credential leaks on the dark web.
This is critical, since your adversaries will search
email, intranet sites, etc., for credentials.
Of course, this list is not exhaustive, but it gives you a sense
of how, even as the attention on security and privacy has
risen, business preparation has not. At a minimum, the

## Page 702

contents of this chapter should serve as a starting point for
sensible access control.
10.2.5 Remote work and privacy risk
As I write this, there is a raucous debate occurring in
corporate America. Employees who have been working from
home for almost a year and a half have gotten accustomed
to the flexibility and the lack of commute. Companies are
confronting the possibility of rising attrition in the event that
their return-to-work arrangements are deemed to be not
responsive to this changed environment. What challenges
might this pose to infrastructure security and, consequently,
to privacy?
The possible risk presented by weak data protection became
real on January 15, 2021. The target was a water treatment
plant that served the Bay Area. Not only did a bad actor get
in unauthorized, they tried to poison the water, directly
connecting the vulnerability to public health in a direct way.
The mode of entry was an open door: the username and
password of a former employee’s account for a software
program that enabled remote access. As we have seen
before in this chapter, the combination of easy access and
privileges can be consequential. Sure enough, the hacker
tried to delete water treatment programs upon logging in.46
This incident is an example of how cyberattacks are now
being aimed at water infrastructure. Just a few weeks after
the Bay Area attack, there was a similar one in Oldsmar,
Florida. The second attack was similar to the first one in that

## Page 703

the access path involved a TeamViewer account. The
attacker used their privileges to raise the levels of lye in the
drinking water to poisonous levels. Detection came not via
controls or automated monitoring but via an alert employee
noticing that the computer’s mouse was moving on its own.
Fortunately, that employee was able to undo the hacker’s
changes.
47
The NBC news report about the Bay Area incident points out,
correctly, that the decentralized nature of the water supply
inoculates it from centralized outages. Just as elections are
localized, so are most water supplies. This inhibits an
attacker from exploiting a central point of failure.
And that blessing is also a problem. The lack of a central
managed authority in our infrastructure also aligns with a
lack of central cybersecurity and privacy law.
“‘It’s really difficult to apply some kind of uniform cyber
hygiene assessment, given the disparate size and capacity
and technical capacity of all the water utilities,’ said Mike
Keegan, an analyst at the National Rural Water Association,
a trade group for the sector.”48
The electric grid in the United States mostly consists of for-
profit corporations, which could be more tightly regulated.
On the other hand, most of the drinking water facilities in
the United States are nonprofits. Their cybersecurity muscle
depends on how large their customer base is, which in turn
determines the funding available for cybersecurity. When
local governments cut funding, it is likely that the
cybersecurity functions suffer, leading to upgrades being

## Page 704

delayed and staffing levels being slashed. This has echoes of
the HVAC vendor whose vulnerabilities formed a key
breadcrumb in the Target breach almost a decade ago.
The NBC News report cites a specific anecdote that I find
especially troubling.
Small rural water facilities tend to be reluctant to share their vulnerabilities,
said Daryn Martin, a technical assistant at the Kansas Rural Water
Association, a trade organization for about 800 Kansas water treatment
facilities, including Post Rock.
“Generally, they’re not reporting to the federal government. There’s some
distrust, you know, in small-town, Midwest USA,” he said....
“Remote access makes it so you don’t have to man a facility 24 hours a day,”
he said. “We have a lot of remote water districts that cover hundreds of miles.
To pay a guy to drive 30 miles to turn a pump on and then he might have to
turn it off in 3 hours when the tank gets full? He can do all that remotely. That
saves money.”
49
Replace intergovernmental distrust with organizational
disconnect, and you have the makings of a major business
with data about healthcare, travel, and finances being
susceptible to cyberwarfare and privacy harm.
While remote work and service segmentation are here to
stay, the implications on data protection keep getting more
serious. Just as a bad actor can sabotage a water supply by
altering programs and data, the damage they could do to
personal data is unimaginable and unquantifiable. There is a
reason ransomware and cybersecurity are thought of as a
key component of national security.

## Page 705

Russian and Chinese spies have sneaked into numerous
federal government networks, sometimes going for months
undetected. Criminals have hacked into every industry and
extorted companies at will, including those that occupy
important parts of U.S. supply chains.
While there is no guaranteed fail-safe plan, companies and
organizations can take steps to contain the risk, as you will
now see.
10.3 Protecting privacy by closing access-
control gaps
No discussion of access control can be complete without
discussing insecure direct object references (IDORs). IDORs
are a type of access control vulnerability that arises when an
application uses user-supplied input to access objects
directly.
Let’s first look at how an IDOR vulnerability works, and then
we can look at mitigation options.
10.3.1 How an IDOR vulnerability works
Before we look at IDORs and ways to test for and remedy
them, understanding the core concepts can be helpful:

## Page 706

In the case of IDOR, object refers to data and/or
functionality. For example, as an e-commerce
shopper, I have access to objects like my shopping
cart but not the backend inventory of the website
that sells the merchandise.
“Vertical access control aims to control the
restrictions to access functions according to the
user roles.”50 In our e-commerce example, while I
as a shopper can change the items in my cart,
modifying items in the backend inventory that are
available to all shoppers is only possible for the
admin.
“Horizontal access control aims to control the
restrictions to access resources by users who have
the same capability level.”51 For example, I should
be able to remove items from my shopping cart,
but not from the cart of another user who has a
different account.
Put simply, an IDOR “occurs when an attacker gains direct
access by using user-supplied input to an object that has no
authorization to access.”52 This occurs when either
authentication (the mechanism that allows user entry into
the system) is not sufficiently tethered to authorization (the
mechanism that allows user access to objects in the
system). In other words, in the context of an IDOR
weakness, my access as a user to objects is not tied to my
identity.
It is also possible that weaknesses in the authorization
implementation are weak enough that attackers can bypass

## Page 707

the authorization mechanism and access resources in the
system.
In most web applications, an object is represented with an
ID. For example, in an e-commerce app or website, my
identity and the product I buy will have IDs. And if these IDs
are easy enough to guess or can be accessed by an attacker
by bypassing access controls, you have the telltale signs of
an IDOR.
Let’s look at an example to understand how such an attack
can work and then we will look at mitigation strategies.
Figure 10.4 shows an object schema for an e-commerce
backend. As you can see, a users object has attributes like
an ID, name, and creation date. Similarly, the orders object
has attributes like ID, creation date, user ID, and product
ID. Both objects have as primary keys their own IDs, but
they point to other IDs as well. For example, an order maps
back to a specific user ID, since normally one order maps to
one buyer. However, one order could map to multiple
products, so it is possible that one order ID maps to several
