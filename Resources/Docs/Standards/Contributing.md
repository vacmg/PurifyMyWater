# Contributing GuideLines

## Description

The objective of this document is to tell the coders / designers what to do in defferent moments. And try to give them a standard to follow for that ocassions.


## Before everything
### Coding
Code without the standard followed on [BARR-C:2018](https://barrgroup.com/sites/default/files/barr_c_coding_standard_2018.pdf) will not be added on the master branch.

---


### Designing
Designs without the standard followed on [DESIGN_STANDARD] will not be used by the coders.

---



## Coders
### Coders want to start working on an ISSUE
* Create a new branch from the ISSUE menu.
    * Assign to yourself that your are working on that ISSUE. 
    * Located on the right menu, development, "create new branch".
    * **LEAVE THE NAME OF THE BRANCH LIKE THAT**
### Coders complete a ISSUE
* if (You didn't create a pull request) 
    * Create a pull-request in github repository. 
* Close the ISSUE


---
### Coders encounter a problem
* IF (The problem is not solved in any other ISSUE)
    * Create an ISSUE in github repository with the label: BUG
### Coders fixed a problem
* Create a pull-request in github repository. Try to create a description on how you solved that problem, both in the pull-request / when you close the ISSUE.
* Close the ISSUE.


---
### Coders want to add a new feature (Not approved by design team) ID:1
* Create an ISSUE in github repository with the label: FEATURE CODER
    * Add where it has to be / description of the new feature.
### Coders finished a feature (Approved by design team)
* Create a pull-request in github repository. 
* Close the ISSUE.



## Designers
### Designers create a new ISSUE
* Designers follow the [DESIGN_STANDARD] standard to create the new ISSUES. 
    * New ISSUE will be created on the GitHub repository.

### Designers take a new feature from coders ID:1
* For approving It, design team will have a meeting about if the new features is enough usefull.
* IF (approved)
    * Designers follow the [DESIGN_STANDARD] standard to create the new ISSUES. 
    * New ISSUE will be created on the GitHub repository.
---


### Whenever an ISSUE is closed
* It doesn't matter form where it comes coding / designing whenever an ISSUE is closed the design tema will consider the next step on the project.
---


### Designers find a BUG on ISSUES which are being used
*  Close that ISSUE until the designers have a meeting and make a decission.
    *  Try to inform the one/s who is/are working on that ISSUE ASAP.
### Designers find a BUG on ISSUES which are not being used
*  Close that ISSUE until the designers have a meeting and make a decission.

### Designers fixed a BUG that have affected some of the ISSUES
*  Create new ISSUES / reopen with the fix the other ones.
    *  Try to inform the one/s who was/were on that ISSUE.


---
---
## Disclaimer
### What we mean with "aprroved by the design team":
* The design team creates the ISSUES of new features only, because they need to know what changes are made to create new ISSUES with a good logical perception. Coders can make new ISSUES that will be considered in the next design meeting but only ISSUES with the label: FEATURE DESIGN will be accepted to merge to main.

### ID
* We use ID for connecting coding and designing questions. 
    * ID:1 means there is one coding question associated with other one with the same id on designing questions.

