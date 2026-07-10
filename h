[1mdiff --git a/data/government-services.json b/data/government-services.json[m
[1mindex 9e59681..8f1b879 100644[m
[1m--- a/data/government-services.json[m
[1m+++ b/data/government-services.json[m
[36m@@ -122,6 +122,69 @@[m
       }[m
     ][m
   },[m
[32m+[m[32m  {[m
[32m+[m[32m    "id": "census-bureau-differential-privacy-ban",[m
[32m+[m[32m    "title": "Commerce Department ban on Census Bureau statistical-noise privacy protections",[m
[32m+[m[32m    "institution": "U.S. Census Bureau and Bureau of Economic Analysis (Department of Commerce)",[m
[32m+[m[32m    "domain": "data_collection_halted",[m
[32m+[m[32m    "status": "Ongoing (order in effect as of June 2026; could be revoked by a future administration before the 2030 census)",[m
[32m+[m[32m    "date_of_action": "2026-06 (order issued; effects unfolding through 2030 census preparation)",[m
[32m+[m[32m    "what_changed": "The Commerce Department, which oversees the Census Bureau, issued an order banning 'noise infusion' - one of the bureau's core techniques for anonymizing survey and administrative-record data before public release, mandated by federal law (13 U.S.C. §8) to protect respondents' confidentiality. Noise infusion has been used for decades, and more recently through a differential-privacy system built under former chief scientist John Abowd, to make it mathematically much harder to re-identify individuals in small-area statistics. The order leaves the Census Bureau and the Bureau of Economic Analysis only one remaining privacy option: 'coarsening' data (releasing broader, less-detailed categories) or not publishing some statistics at all. Data experts warn this could make data for many rural counties and small communities unpublishable, and that 2030 census redistricting data preparation - already underway - will need to be redesigned from scratch. The order followed, and is intertwined with, a separate 2025 lawsuit by America First Legal (co-founded by White House deputy chief of staff Stephen Miller) challenging the bureau's differential-privacy system, and came after a broader thinning of the bureau's statistical expertise amid Trump administration workforce cuts. It was issued with no public technical rationale, no advance opportunity for outside statisticians to review or comment, and no response from Commerce to a reporter's request for specific examples of the harm it claims to be fixing.",[m
[32m+[m[32m    "primary_proponent": {[m
[32m+[m[32m      "name": "Howard Lutnick",[m
[32m+[m[32m      "role": "U.S. Secretary of Commerce, whose department issued the order and oversees the Census Bureau and BEA",[m
[32m+[m[32m      "note": "Commerce, under Lutnick, published the order banning noise infusion; Commerce spokesperson Kristen Eichamer defended it publicly as necessary to 'maintain public confidence' in the data, while declining to provide examples of noise infusion having undermined data integrity when asked directly by NPR."[m
[32m+[m[32m    },[m
[32m+[m[32m    "estimated_impact": {[m
[32m+[m[32m      "summary": "Removing the bureau's primary legally-mandated privacy technique, with no substitute of comparable quality, is expected to shrink or eliminate published statistics for small counties, rural areas, and minority communities, and to force a redesign of 2030 census redistricting-data preparation already underway.",[m
[32m+[m[32m      "figures": [[m
[32m+[m[32m        {[m
[32m+[m[32m          "metric": "Federal statistical agencies directly affected",[m
[32m+[m[32m          "value": "2 (Census Bureau and Bureau of Economic Analysis)",[m
[32m+[m[32m          "source": "Commerce Department order, June 2026, reported by NPR"[m
[32m+[m[32m        },[m
[32m+[m[32m        {[m
[32m+[m[32m          "metric": "Remaining privacy-protection option after the ban",[m
[32m+[m[32m          "value": "1 ('coarsening' - broader, less detailed data categories - or non-publication)",[m
[32m+[m[32m          "source": "NPR interview with former Census Bureau chief scientist John Abowd, June 2026"[m
[32m+[m[32m        },[m
[32m+[m[32m        {[m
[32m+[m[32m          "metric": "Prior legal challenge timeline",[m
[32m+[m[32m          "value": "America First Legal's suit against the bureau's differential-privacy system was refiled after a 3-judge panel ruled an earlier version untimely",[m
[32m+[m[32m          "source": "CourtListener docket, University of South Florida College Republicans v. Lutnick, cited by NPR"[m
[32m+[m[32m        }[m
[32m+[m[32m      ],[m
[32m+[m[32m      "caveat": "Commerce's stated rationale is that 'indiscriminate use of noise infusion...ultimately undermined confidence in the department's products and cast doubt on their integrity,' and that coarsening better 'upholds our duty to safeguard the privacy of those who provide information' - i.e., the administration frames this as a pro-privacy, pro-integrity move, not a cut. Independent data-user advocates (Beth Jarosz, Association of Public Data Users; John Abowd, former Census chief scientist) and an anonymous current bureau employee dispute this, calling the change 'cataclysmic' for data production and noting it removed the normal scientific/public review process. Long-running controversy over the differential-privacy system predates this administration - Alabama Republican officials sued to block it in 2021 - so this is a continuation of a genuine, multi-year methodological dispute, not a one-sided fabrication."[m
[32m+[m[32m    },[m
[32m+[m[32m    "confidence_note": "High confidence on the existence, timing, and content of the order and the range of expert reaction, based on NPR's direct interviews with the Commerce Department spokesperson, a former Census Bureau chief scientist, and outside data-user advocates, corroborated by a September 2025 Commerce Inspector General audit and a CBPP policy report documenting broader statistical-agency budget and staffing pressure. The ultimate real-world impact on specific datasets is still unfolding and not yet independently audited.",[m
[32m+[m[32m    "last_verified": "2026-07-09",[m
[32m+[m[32m    "sources": [[m
[32m+[m[32m      {[m
[32m+[m[32m        "name": "NPR - 'A Trump push to cut statistical noise could mean less data from the Census Bureau'",[m
[32m+[m[32m        "url": "https://www.npr.org/2026/06/12/nx-s1-5855734/census-bureau-data-differential-privacy"[m
[32m+[m[32m      },[m
[32m+[m[32m      {[m
[32m+[m[32m        "name": "NPR - 'Disappearing data at the Census Bureau raises concerns'",[m
[32m+[m[32m        "url": "https://www.npr.org/2025/02/12/nx-s1-5289329/us-census-bureau-survey-data"[m
[32m+[m[32m      },[m
[32m+[m[32m      {[m
[32m+[m[32m        "name": "Center on Budget and Policy Priorities - 'Federal Data Are Disappearing as Statistical Agencies Face Budget Cuts and Political Pressure'",[m
[32m+[m[32m        "url": "https://www.cbpp.org/research/poverty-and-inequality/federal-data-are-disappearing-as-statistical-agencies-face-budget"[m
[32m+[m[32m      },[m
[32m+[m[32m      {[m
[32m+[m[32m        "name": "U.S. Department of Commerce OIG - 'Audit of the Census Bureau's Progress in Meeting Workforce Hiring Goals for the 2026 Census Test'",[m
[32m+[m[32m        "url": "https://www.oig.doc.gov/wp-content/OIGPublications/OIG-25-030-A_FinalReport-SECURED.pdf"[m
[32m+[m[32m      },[m
[32m+[m[32m      {[m
[32m+[m[32m        "name": "Commerce Department disclosure avoidance order",[m
[32m+[m[32m        "url": "https://www.commerce.gov/opog/disclosure-avoidance-statistical-products"[m
[32m+[m[32m      },[m
[32m+[m[32m      {[m
[32m+[m[32m        "name": "CourtListener - University of South Florida College Republicans v. Lutnick docket",[m
[32m+[m[32m        "url": "https://www.courtlistener.com/docket/71353803/university-of-south-florida-college-republicans-v-lutnick/"[m
[32m+[m[32m      }[m
[32m+[m[32m    ][m
[32m+[m[32m  },[m
   {[m
     "id": "cfpb-dismantlement-trump2",[m
     "title": "CFPB Ordered to Stop All Work, Nearly Defunded — Federal Judge Called It 'Hanging by a Thread'",[m
[36m@@ -686,6 +749,90 @@[m
       }[m
     ][m
   },[m
[32m+[m[32m  {[m
[32m+[m[32m    "id": "fda-cber-vaccine-leadership-turmoil",[m
[32m+[m[32m    "title": "FDA vaccine/biologics division leadership purge and COVID vaccine access restriction",[m
[32m+[m[32m    "institution": "FDA — Center for Biologics Evaluation and Research (CBER)",[m
[32m+[m[32m    "domain": "staff_office_cuts",[m
[32m+[m[32m    "status": "Ongoing (acting leadership in place; permanent successor search underway as of May 2026)",[m
[32m+[m[32m    "date_of_action": "March 2025 - April 2026",[m
[32m+[m[32m    "what_changed": "CBER, the FDA division that regulates vaccines, gene therapies, and blood products, went through six different directors across it and its sister division (CDER) since January 2025. Longtime CBER director Peter Marks resigned in March 2025 amid reported disagreements with HHS Secretary Robert F. Kennedy Jr. over vaccine policy. Vinay Prasad was installed as CBER director in May 2025. In July 2025 Prasad was forced out after backlash over his handling of Sarepta Therapeutics' Duchenne muscular dystrophy gene therapy, then reinstated roughly two weeks later after Commissioner Marty Makary intervened. Upon returning, Prasad fired the official in charge of vaccine safety/surveillance and took direct control of that function himself, and went on to push out at least seven other agency leaders during his second tenure. In May 2025, Makary and Prasad co-authored a New England Journal of Medicine framework limiting FDA approval of updated COVID-19 vaccines to adults 65+ and people with qualifying risk factors, reversing the prior policy of a universal annual-vaccine recommendation for everyone 6 months and older; manufacturers must now run new randomized trials to get approval for healthy people outside that group. Prasad also repeatedly overruled career staff on individual drug and vaccine decisions (initially refusing to review Moderna's mRNA flu vaccine, reversed only after White House pressure; rejecting or discouraging gene-therapy applications from uniQure, Ultragenyx, Capricor, and Replimune). Prasad departed CBER for a second and final time on April 30, 2026; deputy director Katherine Szarama was elevated to acting director.",[m
[32m+[m[32m    "primary_proponent": {[m
[32m+[m[32m      "name": "Vinay Prasad",[m
[32m+[m[32m      "role": "Director, FDA Center for Biologics Evaluation and Research (May-July 2025, Aug 2025-Apr 2026); also served as FDA Chief Scientific and Medical Officer",[m
[32m+[m[32m      "note": "Co-authored the NEJM framework restricting COVID vaccine approval to high-risk groups; fired the FDA's vaccine-safety-and-surveillance lead and took over that role himself; personally signed the initial refusal-to-review letter for Moderna's flu vaccine; pushed out at least seven other CBER leaders during his second tenure, according to agency officials cited by STAT."[m
[32m+[m[32m    },[m
[32m+[m[32m    "estimated_impact": {[m
[32m+[m[32m      "summary": "Constant leadership churn destabilized the FDA division responsible for vaccine and gene-therapy approvals, while a policy rewrite removed the default annual-vaccine recommendation for the majority of the U.S. population under 65, shifting them to a prescription/out-of-pocket access model.",[m
[32m+[m[32m      "figures": [[m
[32m+[m[32m        {[m
[32m+[m[32m          "metric": "Combined CBER + CDER director turnover since Jan. 2025",[m
[32m+[m[32m          "value": "6 different (acting or permanent) directors",[m
[32m+[m[32m          "source": "Regulatory consultant Jeff Grossman via BioSpace, July 2026"[m
[32m+[m[32m        },[m
[32m+[m[32m        {[m
[32m+[m[32m          "metric": "Americans still eligible for a default COVID-19 vaccine recommendation under the new risk-based framework",[m
[32m+[m[32m          "value": "100-200 million (out of ~340 million total population), per FDA's own estimate",[m
[32m+[m[32m          "source": "FDA/NEJM framework, cited by Axios, PBS NewsHour, and The Conversation, May-Sept 2025"[m
[32m+[m[32m        },[m
[32m+[m[32m        {[m
[32m+[m[32m          "metric": "Rare-disease/gene-therapy drug applications denied or discouraged in the prior year due to data disputes",[m
[32m+[m[32m          "value": "At least 8",[m
[32m+[m[32m          "source": "RTW Investments analysis, cited by CNBC, March 2026"[m
[32m+[m[32m        },[m
[32m+[m[32m        {[m
[32m+[m[32m          "metric": "CBER leaders pushed out during Prasad's second tenure (Aug. 2025-Mar. 2026)",[m
[32m+[m[32m          "value": "At least 7",[m
[32m+[m[32m          "source": "FDA officials speaking to STAT News, October 2025-March 2026"[m
[32m+[m[32m        }[m
[32m+[m[32m      ],[m
[32m+[m[32m      "caveat": "FDA leadership frames these as deliberate, evidence-based reforms rather than harmful disruption: Commissioner Makary credited Prasad with four 'long-lasting' reforms (a 2-to-1 pivotal-trial requirement, national priority review vouchers, the risk-stratified vaccine framework, and a new 'plausible mechanism' pathway for ultra-rare diseases), and said CBER hit a record number of approvals in December 2025. FDA officials also point to comparable age/risk-based vaccine policies in Canada, Denmark, and Australia as precedent. On the other side, 12 former FDA commissioners warned the new vaccine evidence bar could make it commercially unworkable for manufacturers to develop new vaccines, more than 75 medical organizations criticized the policy shift, and multiple biotech companies said the agency reversed prior agreements on trial design after their programs were already underway. A November 2025 internal Prasad memo claiming COVID vaccines caused at least 10 pediatric deaths was reported by the Washington Post but no supporting case data was released, leaving that specific claim unverified and contested."[m
[32m+[m[32m    },[m
[32m+[m[32m    "confidence_note": "High confidence on the leadership-turnover and policy-change facts themselves, which are corroborated across many independent outlets (STAT, BioSpace, CNBC, Axios, PBS, Fierce Biotech, BioPharma Dive, PharmExec) and FDA's/Makary's own public statements. No formal GAO or Inspector General report on this specific matter has been identified yet; impact figures (drug denial count, population access figures) come from industry analysis (RTW Investments) and the FDA's own framework rather than an independent audit.",[m
[32m+[m[32m    "last_verified": "2026-07-09",[m
[32m+[m[32m    "sources": [[m
[32m+[m[32m      {[m
[32m+[m[32m        "name": "STAT News - 'FDA's Vinay Prasad, controversial CBER chief, to depart'",[m
[32m+[m[32m        "url": "https://www.statnews.com/2026/03/06/fda-vinay-prasad-controversial-cber-director-leaving/"[m
[32m+[m[32m      },[m
[32m+[m[32m      {[m
[32m+[m[32m        "name": "CNBC - 'FDA vaccine head will step down in April after string of controversial decisions'",[m
[32m+[m[32m        "url": "https://www.cnbc.com/2026/03/06/fda-vaccine-head-prasad-step-down.html"[m
[32m+[m[32m      },[m
[32m+[m[32m      {[m
[32m+[m[32m        "name": "BioSpace - 'Despite chaos and churn, FDA decisions hold mostly steady in H1 2026'",[m
[32m+[m[32m        "url": "https://www.biospace.com/fda/despite-chaos-and-churn-fda-decisions-hold-mostly-steady-in-h1-2026"[m
[32m+[m[32m      },[m
[32m+[m[32m      {[m
[32m+[m[32m        "name": "Fierce Biotech - 'CBER Director Vinay Prasad to depart FDA'",[m
[32m+[m[32m        "url": "https://www.fiercebiotech.com/biotech/fdas-vinay-prasad-depart-agency-end-april"[m
[32m+[m[32m      },[m
[32m+[m[32m      {[m
[32m+[m[32m        "name": "BioPharma Dive - 'Vinay Prasad, controversial FDA leader, to again depart agency'",[m
[32m+[m[32m        "url": "https://www.biopharmadive.com/news/vinay-prasad-fda-depart-cber-vaccines-makary/814121/"[m
[32m+[m[32m      },[m
[32m+[m[32m      {[m
[32m+[m[32m        "name": "PharmExec - 'Vinay Prasad Out at CBER for Second Time in Under a Year'",[m
[32m+[m[32m        "url": "https://www.pharmexec.com/view/vinay-prasad-out-cber-second-time-under-year"[m
[32m+[m[32m      },[m
[32m+[m[32m      {[m
[32m+[m[32m        "name": "Axios - 'New COVID booster rules could limit shots for people under 65'",[m
[32m+[m[32m        "url": "https://www.axios.com/2025/05/20/fda-limits-covid-boosters"[m
[32m+[m[32m      },[m
[32m+[m[32m      {[m
[32m+[m[32m        "name": "PBS NewsHour - 'Who is eligible for a COVID shot? What to know about the latest U.S. changes'",[m
[32m+[m[32m        "url": "https://www.pbs.org/newshour/health/who-is-eligible-for-a-covid-shot-what-to-know-about-the-fdas-latest-changes"[m
[32m+[m[32m      },[m
[32m+[m[32m      {[m
[32m+[m[32m        "name": "PBS NewsHour / AP - 'FDA approves updated COVID-19 shots with some restrictions for kids and adults'",[m
[32m+[m[32m        "url": "https://www.pbs.org/newshour/health/fda-approves-updated-covid-19-shots-with-some-restrictions-for-kids-and-adults"[m
[32m+[m[32m      },[m
[32m+[m[32m      {[m
[32m+[m[32m        "name": "yourNEWS - 'FDA Vaccine Chief Vinay Prasad Departs Again, Deputy Elevated to Lead Biologics Center'",[m
[32m+[m[32m        "url": "https://yournews.com/2026/05/04/6885169/fda-vaccine-chief-vinay-prasad-departs-again-deputy-elevated-to/"[m
[32m+[m[32m      }[m
[32m+[m[32m    ][m
[32m+[m[32m  },[m
   {[m
     "id": "fema-capacity-collapse-texas-floods-trump2",[m
     "title": "FEMA Capacity Collapse — Staff Exodus and Spending Bottleneck Delayed Texas Flood Response",[m
[36m@@ -1241,6 +1388,79 @@[m
       }[m
     ][m
   },[m
[32m+[m[32m  {[m
[32m+[m[32m    "id": "nist-workforce-standards-cuts",[m
[32m+[m[32m    "title": "NIST workforce reduction and standards/research budget cuts",[m
[32m+[m[32m    "institution": "National Institute of Standards and Technology (Department of Commerce)",[m
[32m+[m[32m    "domain": "staff_office_cuts",[m
[32m+[m[32m    "status": "Ongoing (staff reductions already executed; a further Reduction-in-Force and reorganization plan pending as of early 2026; FY2026 budget still being negotiated in Congress)",[m
[32m+[m[32m    "date_of_action": "2025-02 to 2026-01 (workforce cuts); FY2026 budget proposal released June 2025",[m
[32m+[m[32m    "what_changed": "NIST, the 125-year-old nonregulatory agency that sets the country's measurement, cybersecurity, and technology standards (including the widely used Cybersecurity Framework, the AI Risk Management Framework, and post-quantum encryption standards), lost more than 700 positions between the start of the Trump administration and January 2026 through resignations, retirements, and voluntary deferments, including roughly 500 recent hires who were let go early in 2025 while still in probationary status. A lab responsible for testing and validating the federal government's encryption implementations lost 89 staff. The administration's FY2026 budget request proposed cutting NIST's $1.2 billion budget by $325 million, eliminating the Hollings Manufacturing Extension Partnership Program entirely (97 positions, $175 million, serving small and mid-size manufacturers in all 50 states and Puerto Rico) and cutting $125 million and 556 positions from NIST's core Scientific and Technical Research and Services program, citing cybersecurity/privacy, health and biological measurements, and physical-infrastructure research as target areas. House appropriators later rejected the steepest of these cuts and restored funding above the administration's request, but the agency has already absorbed the workforce losses and, as of early 2026, is still awaiting a formal Reduction-in-Force and reorganization plan.",[m
[32m+[m[32m    "primary_proponent": {[m
[32m+[m[32m      "name": "Howard Lutnick",[m
[32m+[m[32m      "role": "U.S. Secretary of Commerce, whose department oversees NIST and sought roughly a 20% department-wide staff cut without using formal layoffs",[m
[32m+[m[32m      "note": "A bipartisan congressional letter to Lutnick in April 2025 (from the Maryland and Colorado delegations, home to major NIST facilities) demanded details on the reduction-in-force plan, citing the department's own reported goal of cutting 20% of Commerce staff without formal layoffs and warning of 'irreparable' damage to NIST's ability to recruit and retain scientific talent."[m
[32m+[m[32m    },[m
[32m+[m[32m    "estimated_impact": {[m
[32m+[m[32m      "summary": "A sustained loss of specialized technical staff and a proposed further budget cut have weakened NIST's capacity in encryption/post-quantum cryptography, AI safety standards, and manufacturing extension services relied on by industry and other federal agencies.",[m
[32m+[m[32m      "figures": [[m
[32m+[m[32m        {[m
[32m+[m[32m          "metric": "Total NIST positions lost since Jan. 2025",[m
[32m+[m[32m          "value": "700+",[m
[32m+[m[32m          "source": "Kevin Stine, NIST Director of the Information Technology Laboratory, at an Information Security and Privacy Advisory Board meeting, reported by CyberScoop, Jan. 2026"[m
[32m+[m[32m        },[m
[32m+[m[32m        {[m
[32m+[m[32m          "metric": "Staff lost at the lab testing/validating federal encryption",[m
[32m+[m[32m          "value": "89",[m
[32m+[m[32m          "source": "CyberScoop, January 2026"[m
[32m+[m[32m        },[m
[32m+[m[32m        {[m
[32m+[m[32m          "metric": "Probationary employees targeted in initial Feb. 2025 cuts",[m
[32m+[m[32m          "value": "~500",[m
[32m+[m[32m          "source": "Axios/Bloomberg reporting, cited by WIRED, February 2025"[m
[32m+[m[32m        },[m
[32m+[m[32m        {[m
[32m+[m[32m          "metric": "FY2026 administration proposed cut to NIST discretionary budget",[m
[32m+[m[32m          "value": "$325 million (from $1.2 billion)",[m
[32m+[m[32m          "source": "NIST FY2026 Congressional Budget Submission, Dept. of Commerce, June 2025"[m
[32m+[m[32m        },[m
[32m+[m[32m        {[m
[32m+[m[32m          "metric": "Positions and funding proposed for elimination in the Hollings Manufacturing Extension Partnership",[m
[32m+[m[32m          "value": "97 positions / $175 million",[m
[32m+[m[32m          "source": "NIST FY2026 Congressional Budget Submission"[m
[32m+[m[32m        }[m
[32m+[m[32m      ],[m
[32m+[m[32m      "caveat": "The administration frames the cuts as fiscal discipline and a redirection away from programs it considers outside NIST's core mission - the FY2026 budget documents specifically criticize environmental-sustainability research grants as advancing 'a radical climate agenda,' and argue MEP has outgrown its original rationale after 37 years. House appropriators, controlled by the same party as the administration, disagreed on the scale of cuts and restored $980 million to NIST's Scientific and Technical Research and Services program (a $237 million increase over the administration's request) and full funding for MEP, suggesting the final outcome remains contested within Congress rather than settled. Congressional critics (the Maryland/Colorado delegation letter) warn of a 'brain drain' effect and cite estimates that federal MEP dollars generate nine times their value in economic output, though that multiplier figure originates from program advocates rather than an independent audit."[m
[32m+[m[32m    },[m
[32m+[m[32m    "confidence_note": "High confidence on the staffing-loss figures, which come from NIST's own director speaking on the record at a public advisory board meeting, and on the budget figures, which come directly from NIST's FY2026 Congressional Budget Submission. Moderate confidence on downstream real-world impact (e.g., effects on the AI Risk Management Framework or post-quantum cryptography rollout), which is based on expert commentary rather than a formal audit.",[m
[32m+[m[32m    "last_verified": "2026-07-09",[m
[32m+[m[32m    "sources": [[m
[32m+[m[32m      {[m
[32m+[m[32m        "name": "CyberScoop - 'NIST officials detail impact of staff cuts on encryption and other priorities'",[m
[32m+[m[32m        "url": "https://cyberscoop.com/encryption-nist-officials-detail-staff-cuts-impact/"[m
[32m+[m[32m      },[m
[32m+[m[32m      {[m
[32m+[m[32m        "name": "Cybersecurity Dive - 'NIST loses key cyber experts in standards and research'",[m
[32m+[m[32m        "url": "https://www.cybersecuritydive.com/news/nist-cyber-retirements-quantum-ai-research-standards/747270/"[m
[32m+[m[32m      },[m
[32m+[m[32m      {[m
[32m+[m[32m        "name": "Federal News Network - 'House appropriators reject NIST funding cuts'",[m
[32m+[m[32m        "url": "https://federalnewsnetwork.com/congress/2025/07/nist-to-get-funding-boost-under-house-bill/"[m
[32m+[m[32m      },[m
[32m+[m[32m      {[m
[32m+[m[32m        "name": "NIST-NTIS FY2026 Congressional Budget Submission, Dept. of Commerce",[m
[32m+[m[32m        "url": "https://www.commerce.gov/sites/default/files/2025-06/NIST-NTIS-FY2026-Congressional-Budget-Submission.pdf"[m
[32m+[m[32m      },[m
[32m+[m[32m      {[m
[32m+[m[32m        "name": "WIRED, via Rep. Jake Auchincloss office - 'The National Institute of Standards and Technology Braces for Mass Firings'",[m
[32m+[m[32m        "url": "https://auchincloss.house.gov/media/in-the-news/the-national-institute-of-standards-and-technology-braces-for-mass-firings"[m
[32m+[m[32m      },[m
[32m+[m[32m      {[m
[32m+[m[32m        "name": "Congressional letter to Secretary Lutnick re: NIST probationary and RIF plans",[m
[32m+[m[32m        "url": "https://mcclaindelaney.house.gov/sites/evo-subsites/mcclaindelaney.house.gov/files/evo-media-document/amd-letter-to-sec-lutnik-re-nist-probationary-and-rif-plans-v.f.pdf"[m
[32m+[m[32m      }[m
[32m+[m[32m    ][m
[32m+[m[32m  },[m
   {[m
     "id": "nsf-grant-terminations-peer-review-trump2",[m
     "title": "DOGE Terminated 1,752 NSF Research Grants Using a Senator's Keyword List, Then NSF Formally Weakened Its Own Peer Review Standards",[m
[36m@@ -1383,6 +1603,82 @@[m
       }[m
     ][m
   },[m
[32m+[m[32m  {[m
[32m+[m[32m    "id": "smithsonian-content-review",[m
[32m+[m[32m    "title": "White House-directed content review and exhibit alterations at the Smithsonian",[m
[32m+[m[32m    "institution": "Smithsonian Institution (Washington, DC museums, via White House Domestic Policy Council/OMB)",[m
[32m+[m[32m    "domain": "research_suppression",[m
[32m+[m[32m    "status": "Ongoing (review targeting first-phase museums largely complete; White House published findings report July 2026; second-phase museums and further 'content corrections' still pending)",[m
[32m+[m[32m    "date_of_action": "2025-03-27 (executive order) through 2026-07 (findings report)",[m
[32m+[m[32m    "what_changed": "President Trump's March 27, 2025 executive order 'Restoring Truth and Sanity to American History' directed Vice President JD Vance, who sits on the Smithsonian's Board of Regents, to work to 'remove improper ideology' from Smithsonian museums, and instructed OMB and the Vice President to condition future appropriations on exhibits not 'degrading shared American values' or 'dividing Americans based on race.' In August 2025, White House aide Lindsey Halligan, Domestic Policy Council Director Vince Haley, and OMB Director Russell Vought sent a letter to Smithsonian Secretary Lonnie Bunch launching a formal review of eight flagship DC museums (including the National Museum of American History, the National Museum of African American History and Culture, and the National Portrait Gallery), demanding exhibition texts, future exhibition plans, internal curatorial guidelines, staff manuals, and organizational charts, with a 120-day deadline for museums to begin 'content corrections' replacing 'divisive or ideologically driven language.' The National Museum of American History removed references to Trump's two first-term impeachments from a display in July 2025 as part of an internal content review the Smithsonian undertook under White House pressure; the references were restored about a week later after public criticism. The Smithsonian's Office of Diversity was closed. National Portrait Gallery director Kim Sajet resigned in mid-2025 after Trump publicly said he was firing her, calling her 'a highly partisan person, and a strong supporter of DEI' (the Smithsonian said only Secretary Bunch could make that personnel decision). Artist Amy Sherald canceled a planned exhibition of her work at the National Portrait Gallery in late July 2025 following a dispute over a painting depicting a transgender Statue-of-Liberty figure. In July 2026, the White House Domestic Policy Council published a report titled 'Saving America's Story' accusing the National Museum of American History of 'extreme political activism' and faulting it for not having created a dedicated exhibit on the Founding Fathers, the Declaration of Independence, or the Revolutionary War even in the 250th-anniversary year.",[m
[32m+[m[32m    "primary_proponent": {[m
[32m+[m[32m      "name": "Lindsey Halligan",[m
[32m+[m[32m      "role": "Special Assistant to the President and Senior Associate Staff Secretary, White House",[m
[32m+[m[32m      "note": "Co-signed and helped lead the August 2025 letter to Secretary Bunch launching the formal Smithsonian museum review, and, per legal analysis, has 'sought to influence the Smithsonian's decisions, including by instigating a curatorial review of the museum,' despite being a non-Senate-confirmed executive branch appointee with no formal authority over the historically independent institution."[m
[32m+[m[32m    },[m
[32m+[m[32m    "estimated_impact": {[m
[32m+[m[32m      "summary": "A White House-directed content review, backed by the implicit threat of withholding congressionally appropriated funds, has already produced at least one exhibit alteration, contributed to the departure of two museum leaders, and led to the cancellation of at least one planned exhibition, at an institution that hosted nearly 17 million visitors in the prior year.",[m
[32m+[m[32m      "figures": [[m
[32m+[m[32m        {[m
[32m+[m[32m          "metric": "Smithsonian museums in the first phase of the White House content review",[m
[32m+[m[32m          "value": "8, including the National Museum of American History, NMAAHC, National Air and Space Museum, and National Portrait Gallery",[m
[32m+[m[32m          "source": "CNN and CBS News, August 2025, citing the White House review letter"[m
[32m+[m[32m        },[m
[32m+[m[32m        {[m
[32m+[m[32m          "metric": "Annual Smithsonian visitors (scale of institution affected)",[m
[32m+[m[32m          "value": "~17 million (prior year)",[m
[32m+[m[32m          "source": "Smithsonian Institution figures cited by CNN, August 2025"[m
[32m+[m[32m        },[m
[32m+[m[32m        {[m
[32m+[m[32m          "metric": "Review timeline imposed on museums",[m
[32m+[m[32m          "value": "30/75/120-day compliance deadlines for submitting materials and beginning 'content corrections'",[m
[32m+[m[32m          "source": "White House review letter, reported by NPR, August 2025"[m
[32m+[m[32m        },[m
[32m+[m[32m        {[m
[32m+[m[32m          "metric": "Senior leadership departures tied to the review/pressure campaign",[m
[32m+[m[32m          "value": "2 (National Portrait Gallery director Kim Sajet; NMAAHC director)",[m
[32m+[m[32m          "source": "CBS News and Yale Law Journal analysis, 2025-2026"[m
[32m+[m[32m        }[m
[32m+[m[32m      ],[m
[32m+[m[32m      "caveat": "The White House frames this as restoring historical accuracy and 'American exceptionalism' rather than suppressing content, and its July 2026 report argues specific exhibits (e.g., 'The Shape of Power,' framing on 'White culture' at NMAAHC) promote an ideological rather than factual narrative. The Smithsonian has consistently maintained its independence, stating its content is grounded in 'scholarly excellence, rigorous research, and the accurate, factual presentation of history,' has said it was not directed by the administration to remove the impeachment references (calling that specific placard 'temporary' and not meeting museum standards on its own), and Secretary Bunch has publicly reaffirmed the institution's independence from political influence in a September 2025 letter to staff. The Smithsonian's unique legal status as a congressionally chartered 'trust instrumentality' - not a standard executive-branch agency - is itself a live, unresolved legal question about whether the White House has authority to compel these changes at all."[m
[32m+[m[32m    },[m
[32m+[m[32m    "confidence_note": "High confidence on the executive order, the review letter, and the individual episodes (impeachment placard, Sajet resignation, Sherald cancellation), which are corroborated across NPR, CNN, CBS, ABC News, and a Yale Law Journal legal analysis. The characterization of specific exhibit content and the White House's July 2026 findings report reflect the administration's own framing and are presented here as such, not verified as fact.",[m
[32m+[m[32m    "last_verified": "2026-07-09",[m
[32m+[m[32m    "sources": [[m
[32m+[m[32m      {[m
[32m+[m[32m        "name": "White House - Executive Order 'Restoring Truth and Sanity to American History'",[m
[32m+[m[32m        "url": "https://www.whitehouse.gov/presidential-actions/2025/03/restoring-truth-and-sanity-to-american-history/"[m
[32m+[m[32m      },[m
[32m+[m[32m      {[m
[32m+[m[32m        "name": "NPR - 'Trump administration calls for comprehensive internal review of Smithsonian'",[m
[32m+[m[32m        "url": "https://www.npr.org/2025/08/12/nx-s1-5500550/smithsonian-trump-review"[m
[32m+[m[32m      },[m
[32m+[m[32m      {[m
[32m+[m[32m        "name": "CNN - 'White House orders review of Smithsonian exhibits to ensure alignment with Trump directives'",[m
[32m+[m[32m        "url": "https://www.cnn.com/2025/08/12/politics/smithsonian-exhibits-white-house-review"[m
[32m+[m[32m      },[m
[32m+[m[32m      {[m
[32m+[m[32m        "name": "CBS News - 'White House launching review of Smithsonian museums to ensure alignment with Trump's plans'",[m
[32m+[m[32m        "url": "https://www.cbsnews.com/news/white-house-review-smithsonian-museums-trump/"[m
[32m+[m[32m      },[m
[32m+[m[32m      {[m
[32m+[m[32m        "name": "ABC News - 'In scathing report, White House accuses Smithsonian of presenting a radical view of American history'",[m
[32m+[m[32m        "url": "https://abcnews.com/Politics/scathing-report-white-house-accuses-smithsonian-presenting-radical/story?id=134515705"[m
[32m+[m[32m      },[m
[32m+[m[32m      {[m
[32m+[m[32m        "name": "The Spokesman-Review (via Washington Post) - 'White House report accuses Smithsonian museum of extreme political activism'",[m
[32m+[m[32m        "url": "https://www.spokesman.com/stories/2026/jul/06/white-house-report-accuses-smithsonian-museum-of-e/"[m
[32m+[m[32m      },[m
[32m+[m[32m      {[m
[32m+[m[32m        "name": "Yale Law Journal - 'Fight at the Museum: Executive Overreach and the Future of the Smithsonian Institution'",[m
[32m+[m[32m        "url": "https://yalelawjournal.org/collections/fight-at-the-museum-executive-overreach-and-the-future-of-the-smithsonian-institution0"[m
[32m+[m[32m      },[m
[32m+[m[32m      {[m
[32m+[m[32m        "name": "EveryLibrary - statement on White House overreach into the Smithsonian Institution",[m
[32m+[m[32m        "url": "https://www.everylibrary.org/smithsonian"[m
[32m+[m[32m      }[m
[32m+[m[32m    ][m
[32m+[m[32m  },[m
   {[m
     "id": "snap-shutdown-funding-freeze-trump2",[m
     "title": "SNAP Benefits Withheld During 2025 Government Shutdown",[m
