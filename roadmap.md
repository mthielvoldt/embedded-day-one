# Embedded Devops on Day One
First Steps to a High-Quality Project and the Easy Way

## Who's Presenting
### Mike Thielvoldt
- 15 Years at startups with headcounts from [1 - 250+].
- Industries: Green tech, Energy, Powersport, Special Effects, Art.
- I started my career as a Mechanical Engineer.
- I have led team firmware efforts with up to 7-ish contributors.
- Currently an independent firmware consultant.

#### Translation --> I have many tech-debt battle scars, but fully accept that startups need to be lean and fast.

## Roadmap
1. Measure up the project
1. Make some hard choices
1. Start with a tiny closed loop
1. Put a little business logic in the loop
1. Put your target toolchain in the loop
1. Put your hardware in the loop (the hard part)
1. Share it out

## Glossary
**CI**: Continuous Integration: Coders frequently contribute changes to a central repository, which triggers builds tests in the cloud to reveal issues early.\
**MCU**: Microcontroller.\
**EE**: Electrical engineer(ing).\
**Release**: A formal distribution of a specific, tested version of firmware to users.\
**Regression**: A release breaks something that wasn’t broken before.\
**Onboarding**: Enabling a new team member to become an effective contributor. \

## Measure up the Project
- How big/complex?
    - Many MCU’s? -> code re-use, integration + end-to-end tests with HW in loop.
    - How many coders? -> version-control process, CI performance, onboarding
    - How many customers? -> Release process, binary distribution, test infra.
    - How long will this take? -> Conveniences become important
- Team culture and proficiencies?
    - Level of trust in colleagues? -> How police-like should CI be?
    - Experience working in big teams? -> Version control guidance, code style enforcement?
    - Seniority/skill level? -> A-la-carte (configurable) tools vs batteries-included. 

## What We're Going For

<table>
    <tr>
        <th>Metric</th>
        <th>Probably Good Enough</th>
        <th>Needs Improvement</th>
    </tr>
    <tr>
        <td><h4>Onboarding</h4></td>
        <td>New engineers push early and write tests</td>
        <td>New engineers hesitate to push and share</td>
    </tr>
    <tr>
        <td><h4>Release</h4></td>
        <td>EEs are comfortable self-serving new FW versions.</td>
        <td>FW team members frequently asked “where to get firmware”</td>
    </tr>
    <tr>
        <td><h4>Tests</h4></td>
        <td>
            - Demos are fairly low-stress.<br>
            - Regressions are rare.<br>
            - Refactors appear in most PRs
        </td>
        <td>
            - Demos are sweat-inducing.<br>
            - Regressions commonplace<br>
            - Engineers avoid refactoring code that “already works”
        </td>
    </tr>
</table>

## Choices: Flavor of version control (scm)
### Options
- No version control, manual name-mangling 
- Google docs
- Git
### Forces
- As of tonight, this is a group project.
- We're writing code: it's text based and correctness matters.
- We want ability to step through history and see diff.
- Learning is tolerable: it's what we're here for.
### Decision ⇨ *Git (CLI for power-use)*


## Choices: Where to put `origin`?
### Options (among many)
- Github  *huge community, simple automation*
- Gitlab  *self-hosting friendly, powerful CI/CD*
- Self-hosted  *for regulatory compliance*
### Forces
- Some of us may have already had an account = convenient.
- We want them-hosted CI runners, and simple pipelines for now.
- Mike happens to know github actions best.
### Decision ⇨ *Github*


## Choices: How should we use Git (workflow)?
### Options
- Everyone pushes to `main`, or does their own thing.
- [Trunk-based](https://www.atlassian.com/continuous-delivery/continuous-integration/trunk-based-development) Work happens in ephemeral topic branches with only one long-lived branch: `main`.
- [Gitflow](https://www.atlassian.com/git/tutorials/comparing-workflows/gitflow-workflow)
  - Ephemeral topic branches, and 3 or more long-running branches: `main`, `develop`, `release`, [ `hotfix`… ]
  - New code flows (eventually) from topic > `develop` > `release` > `main` with progressively more time-consuming tests or reviews at each step.
### Forces
- Our coders do their own QA ➡ This lets us keep things simple and focused. Below is the problem with Trunk-based for QA teams:

![](images/git-workflows-2.png)
- We’d prefer to not have time-consuming manual tests at all, rather than risk merge-hell to accommodate them.
### Decision ⇨ *Trunk-based flow*


## Choices: When do we do Quality Control?
### Options
1. We don't; that's QA's job.
2. We test things when we think we should (ad-hoc). 
3. Tests auto-run once new commits hit `main`.
4. We use PRs as a vehicle for driving tests before affecting `main`.
5. We have tests run on all branches every push.
6. The bots figure it out. 
### Forces
- We're the QA team; can't pass it off.
- We're not as good as robots as 
- We hate 
### Decision ⇨ *2 (as desired), 3 (PR), and 4 (main)*


## Choices: What test infra should we build now?
### Options
1. Unit tests that run on host.
2. Code builds for a target CPU.
3. Tests on emulated hardware or circuit simulation.
4. Hardware-in-the-loop (HIL) tests.
### Forces
- If hardware isn't available, 4 and 5 aren't doable
- If hardware designs aren't stable, 4 and 5 are perishable efforts/maintenance items.
- If our hardware isn't built to sit online, we either need gateway hardware, or to do this outside CI.
- Doing things in sim require skill to make them relevant, and don't guarantee confidence.
### Decision ⇨ *Start with 1, 2.  Make 4 a reach-goal*


## Choices: How should customers access new FW versions?
### Options
1. Ask a FW engineer (the friendly one).
2. Buy "the good shit" off the black market the EE team set up.
3. Download it from Github releases.
4. Set up a workstation to build it yourself, and build the coolest looking branch. (sell this on the black market)
### Forces
- The difficulty you create for others gets reflected back at you or your FW colleagues.
- Bugs will still happen.  If our release process is light-weight, we can respond quickly when our customers encounter them.  That'll build inter-team trust.
### Decision ⇨ *Set up github releases*

## A To-do list
From here on, we'll move down the table below, advancing by `git cherry-pick <next-commit>`.

<table>
    <tr>
        <th>Number</th>
        <th>Deliverable</th>
        <th>Acceptance Criteria</th>
    </tr>
    <tr>
        <td>1</td>
        <td>Using Git</td>
        <td>
            - Git onboarding doc.<br>
            - Works for full team.
        </td>
    </tr>
    <tr>
        <td>2</td>
        <td>Using Github</td>
        <td>
            - Docs cover getting access.<br>
            - Everyone can push a branch.
        </td>
    </tr>
    <tr>
        <td>3</td>
        <td>Trunk-based flow</td>
        <td>
            - Docs cover PR process.
        </td>
    </tr>
    <tr>
        <td>4</td>
        <td>Tests runnable as desired</td>
        <td>
            A <code>bootstrap</code> script installs software for tests.<br>
            A <code>run-tests</code> script works locally for everyone.
        </td>
    </tr>
    <tr>
        <td>5</td>
        <td>Tests run on PR and main</td>
        <td>We see check-marks on main and PRs</td>
    </tr>
    <tr>
        <td>6</td>
        <td>Unit Tests</td>
        <td>
            - <code>bootstrap</code> installs test prerequisites<br>
            - <code>run-tests</code> compiles and tests one .c file
        </td>
    </tr>
    <tr>
        <td>7</td>
        <td>CI build check</td>
        <td>
            - <code>bootstrap</code> Installs cross-compiler.<br>
            - <code>generate</code> script builds the project locally <br>
            - <code>generate</code> builds in CI.
        </td>
    </tr>
    <tr>
        <td>8</td>
        <td>On-hardware automated test</td>
        <td>
            - Code that enables comms to/from MCU.<br>
            - A scripted test that checks for echo.
        </td>
    </tr>
    <tr>
        <td>9</td>
        <td>Github releases</td>
        <td>
            - Make a release that exports build artifacts.<br>
            - Add flashing instructions.
        </td>
    </tr>
</table>
