---
marp: true
theme: default
class: invert
paginate: true
---
<style>
section {
    font-size: 24px;
}
.foot {
    position: absolute;
    bottom: 40px;
    font-size: 16px;
    color: #999;
}
img[alt~="top-right"] {
    position: absolute;
    top: 120px;
    right: 60px;
}
.done {
    text-decoration: line-through;
    color: #689;
}
</style>


# Embedded Devops on Day One
First steps to a building firmware The Easier Way™

<div class="foot">
Slides accessible: github.com/mthielvoldt/embedded-day-one/blob/main/roadmap.md<br>
Before we start, please write your github username on the whiteboard
</div>

---

## Who's Presenting
### [Mike Thielvoldt](https://www.linkedin.com/in/mike-thielvoldt/) ![top-right w:150](https://mgtfirmware.com/logo6-256.png)

- 15 Years at startups with headcounts from [1 - 250+]
- Industries: [green tech](https://www.gradientcomfort.com/), [energy](https://lunarenergy.com), [powersport](), [special effects](https://livesparkfire.com), [Burning Man shit](https://www.lepidodgera.com/)
- Started as a Mechanical Engineer
- Led firmware efforts with up to 6-ish contributors
- Currently a freelance firmware engineer: [MGT Firmware](https://mgtfirmware.com)

**Translation ➔** I have tech-debt battle scars, but fully accept that startups need to be lean and fast.

---

## Roadmap
![top-right w:350](images/roadmap-image.drawio.png)
1. Measure up the project
1. Make hard choices
1. Close the loop with CI
1. Get it building for everyone
1. Hook up unit tests
1. Automate on-hardware test
1. Release it into the wild

---

## Glossary
**CI**: Continuous Integration: A development process involving frequent contributions to a code repository, which trigger tests in the cloud to reveal issues early

**EE**: Electrical engineer(ing)

**FW**: Firmware

**MCU**: Microcontroller

**Onboarding**: Facilitating new team members in becoming effective contributors

**QA**: Quality Assurance.  A team that tests software, and may also write it

**PR**: Pull Request.  A process where a branch is tested and reviewed before it gets merged

**Refactor**: Code changes that improve maintainability, but don't add features

**Regression**: A release breaks something that wasn’t broken before

**Release**: A formal distribution of a specific, tested version of firmware to users

---

## Glossary git-specific

**Branch**: A pointer to a commit that's considered to be the tip of a line of development, which automatically moves to stay on the tip

**Clone**: A command to create a local copy of a remote repository

**Commit**: A snapshot of the repository at a point in time, which also references its parent commit(s)

**Diff**: The set of differences between two commits

**Git**: A version-control program that developers use to manage code changes, which runs locally

**`main`**: A conventional name for the most thoroughly-validated branch

**Merge**: Re-playing the changes from one branch into another. Commonly from topic ➔ `main`

**Push**: Sending local commits to a remote (most often central) repository

**Repository**: A directory containing project files and metadata git uses to track those files

---

## 1. Measure up the Project
### How big/complex?
<table>
    <tr>
        <td>Many MCU’s?</td>
        <td>code re-use, integration tests with HW in the loop</td>
    </tr>
    <tr>
        <td>How many coders?</td>
        <td>version-control process, CI performance, onboarding</td>
    </tr>
    <tr>
        <td>How many customers?</td>
        <td>Release process, binary distribution, test infrastructure</td>
    </tr>
    <tr>
        <td>How long will this take?</td>
        <td>Conveniences become important</td>
    </tr>
</table>


### Team culture and proficiencies?
<table>
    <tr>
        <td>Level of trust in colleagues?</td>
        <td>How police-like to configure CI</td>
    </tr>
    <tr>
        <td>Experience working in big teams?</td>
        <td>Version control guidance, code style enforcement</td>
    </tr>
    <tr>
        <td>Seniority/skill level?</td>
        <td>A-la-carte (configurable) tools vs batteries-included</td>
    </tr>
</table>

---

## 1. What We're Going For

<table>
    <tr>
        <th>Metric</th>
        <th>The Easier Way™</th>
        <th>The Hard Way</th>
    </tr>
    <tr>
        <td><h4>Onboarding</h4></td>
        <td>New engineers confidently make first PRs</td>
        <td>New engineers delay/avoid making PRs</td>
    </tr>
    <tr>
        <td><h4>Tests</h4></td>
        <td>
            <ul>
                <li>Demos are fairly low-stress</li>
                <li>Regressions are rare</li>
                <li>Engineers are confident changing things</li>
                <li>Tests are friends, not food</li>
            </ul>
        </td>
        <td>
            <ul>
                <li>Demos are high-stress</li>
                <li>Regressions are commonplace</li>
                <li>Engineers avoid touching code that “already works”</li>
                <li>Tests are a hassle: grumbles + sighs</li>
            </ul>
        </td>
    </tr>
    <tr>
        <td><h4>Release</h4></td>
        <td>Other teams (EEs) are comfortable self-serving new FW versions</td>
        <td>FW team members frequently asked “where to get firmware”</td>
    </tr>
</table>

---

## 2. Choices: Flavor of version control (scm)
### Options
- Mnual name-mangling 
- Google docs
- Git (or mercurial)
- Svn (and other live-connection version control)
### Driving Forces
- As of tonight, this is a group project
- Code: is unforgiving of errors
- We want ability to step through history and see diff
- Learning is tolerable: it's what we're here for
### Decision ⇨ *Git (in the terminal)*

---

## 2. Choices: Where to put `origin`?
### Options (among many)
- Github:  *huge community, simple automation*
- Gitlab:  *self-hosting friendly, powerful CI/CD*
- Self-hosted:  *for regulatory compliance*
### Driving Forces
- Making a popular choice can make onboarding faster
- We want them-hosted CI runners to save us effort
- Mike happens to know github actions best
### Decision ⇨ *Github*

---

## 2. Choices: How should we use Git?
### Options
- Anarchy
  - Everyone pushes to `main`, or does their own thing
- [Trunk-based](https://www.atlassian.com/continuous-delivery/continuous-integration/trunk-based-development)
  - Work happens in ephemeral topic branches with only one long-lived branch: `main`
- [Gitflow](https://www.atlassian.com/git/tutorials/comparing-workflows/gitflow-workflow)
  - Ephemeral topic branches, and 3 or more long-running branches: `main`, `develop`, `release`, [ `hotfix`… ]
  - New code flows (eventually) from topic > `develop` > `release` > `main` with progressively more time-consuming tests or reviews at each step

---

## 2. Choices: How should we use Git? \[continued\]
Aside: Trunk-based with ineffective tests is hell for QA teams

![](images/git-workflows-2.png)

---

## 2. Choices: How should we use Git? \[continued\]

### Driving Forces
- We don't have a separate QA team (yet)
- We’d prefer to not have any time-consuming manual tests ➔ so let's not build them a shelter
- Having only one long-running branch `main` avoids merge-hell

### Decision ⇨ *Trunk-based flow*

---

## 2. Choices: When do we test?
### Options
1. We test things when we think we should (ad-hoc)
2. We use PRs as a vehicle for driving tests before affecting `main`
3. Tests auto-run once new commits hit `main`
4. Tests run on every push to every branch
5. In the cloud, all the time ➔ symbolic execution / continuous verification
### Driving Forces
- Humans *will* forget, especially if modules get too inter-connected
- It takes much longer to find a bug that was written long ago
- We can't hole-up and study modern testing paradigms for 6 months
- A slow test will be avoided or eaten
### Decision ⇨ *1 (as needed) + 2 (PR) + 3 (main)*

---

## 2. Choices: What tests should we build now?
### Options
1. Unit tests that run on host
2. Code builds for a target CPU
3. Tests on emulated hardware or circuit simulation
4. Hardware-in-the-loop (HIL) tests
### Driving Forces
- If hardware isn't available, 4 isn't doable
- If hardware designs aren't stable, 3 and 4 are perishable efforts/maintenance items
- If our HW isn't internet-connected, we either add a gateway, or do this outside CI
- Simulation takes up-front effort; you need evidence it represents reality
### Decision ⇨ *Start with 1 + 2.  Make 4 a reach-goal*

---

## 2. Choices: How should customers access new FW versions?
### Options
1. Ask the friendly FW engineer to slack you a binary
3. Set up workstation to build source code, pick the branch with the coolest name
2. Buy "*the good shit*" off the black market the EE team set up
4. Download it from Github releases

### Driving Forces
- Non-release binaries that escape our laptops = pointeless bug hunts
- We need to make this process easy for others if we want it to be used
- We want a quick release process so we can be responsive to other teams' needs
### Decision ⇨ *Set up github releases*

---

## 2. Choices: What OS are we developing on?
### Options
1. Force everyone to use the same OS
2. Use docker containers
3. Support native development on multiple OS's

### Driving Forces
- This group has strong preferences/opinions
- Docker doesn't do USB*, effort to learn, not compatible with everything, extra layer

### Decision ⇨ *Mac + Win + Ubuntu, no Docker (challenge mode enabled)*

---

## 2. Choices summarized
<style scoped>
  h2 {
    position: relative;
    top: -30px;
    margin-bottom: -30px;
  }
  p {
    font-size: 22px;
  }
  .icon {
    position: absolute;
    top: 40px;
    right: 70px;
    font-size: 2.5em;
  }
  table {
    height: 100%;
    width: 100%;
    font-size: 13px;
}
</style>

From here on, we'll move down this table using our PR Process.

<div class="icon">🚀</div>

<table>
    <tr>
        <th>Step</th>
        <th>Deliverable</th>
        <th>Acceptance Criteria</th>
        <th>Your Action Items</th>
    </tr>
    <tr class="">
        <td>1</td>
        <td>Using Git</td>
        <td>
            <ul>
                <li class="done">Onboarding doc covers git</li>
                <li>Works for full team</li>
            </ul>
        </td>
        <td rowspan="3">
            <ul>
                <li>Sign in to <a href="https://github.com">Github</a></li>
                <li>Put your Github username on whiteboard (or give to Melinda)</li>
                <li>Accept the project invite (in your email)</li>
            </ul>
            At the bottom of <a href="https://github.com/mthielvoldt/embedded-day-one"><code>github.com/mthielvoldt/embedded-day-one</code></a>
            <ul>
                <li>Follow "Manual Software Installs" steps</li>
                <li>Follow "Initial Config" steps</li>
            </ul>
        </td>
    </tr>
    <tr class="">
        <td>2</td>
        <td>Using Github</td>
        <td>
            <ul>
                <li class="done">Docs cover getting access</li>
                <li>Everyone can push a branch</li>
            </ul>
        </td>
    </tr>
    <tr class="">
        <td>3</td>
        <td>Trunk-based flow</td>
        <td>
            <ul>
                <li class="done">Docs cover PR process</li>
                <li>Everyone has a look</li>
            </ul>
        </td>
    </tr>
    <tr class="">
        <td>4</td>
        <td>Tests run locally, on PR, and <code>main</code></td>
        <td>
            <ul>
                <li><code>run-tests</code> runs locally for everyone</li>
                <li>We see check-marks on main and PRs</li>
            </ul>
        </td>
        <td>
            <ul>
                <li>Look at PR <a href="https://github.com/mthielvoldt/embedded-day-one/pull/1">#1</a></li>
                <li>Switch to that branch locally <code>git switch step-4-local-scripts</code></li>
                <li>Refer to <code>.github/workflows/test.yml</code> to run tests on your platform
            </ul>
        </td>
    </tr>
    <tr class="">
        <td>5</td>
        <td>Build checks for target MCU</td>
        <td>
            <ul>
                <li><code>bootstrap</code> installs cross-compiler</li>
                <li><code>generate</code> script builds the project locally</li>
                <li><code>generate</code> builds in CI</li>
            </ul>
        </td>
        <td>
            <ul>
                <li>Look at PR <a href="https://github.com/mthielvoldt/embedded-day-one/pull/3">#3</a> then <a href="https://github.com/mthielvoldt/embedded-day-one/pull/2">#2</a>, following along locally with <code>git switch ...</code></li>
                <li>Refer to <code>.github/workflows/test.yml</code> to bootstrap and build code
            </ul>
        </td>
    </tr>
    <tr class="">
        <td>6</td>
        <td>Unit Tests</td>
        <td>
            <ul>
                <li><code>bootstrap</code> installs unit test prerequisites</li>
                <li><code>run-tests</code> compiles and tests one .c file</li>
            </ul>
        </td>
        <td>
            <ul>
                <li>Look at PR <a href="https://github.com/mthielvoldt/embedded-day-one/pull/4">#4</a></li>
                <li>Run the unit tests.  Maybe try writing one!</li>
            </ul>
        </td>
    </tr>
    <tr class="">
        <td>7</td>
        <td>On-hardware automated test</td>
        <td>
            <ul>
                <li>Code that enables comms to/from MCU</li>
                <li>A scripted test that checks for echo</li>
            </ul>
        </td>
        <td>
            <ul>
                <li>Look at PR <a href="https://github.com/mthielvoldt/embedded-day-one/pull/5">#5</a></li>
                <li>Plug into PCB and use <code>hw-test</code> to test on-hardware</li>
            </ul>
        </td>
    </tr>
    <tr class="">
        <td>8</td>
        <td>Github releases</td>
        <td>
            <ul>
                <li>Make a release that exports build artifacts</li>
                <li>Add flashing instructions</li>
            </ul>
        </td>
        <td>
            <ul>
                <li>Dogfood installing a released binary</li>
            </ul>
        </td>
    </tr>
</table>
