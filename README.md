# Embedded Day One
A workshop covering concerns that come up the day you start an embedded software repo.

This workshop begins with going through `roadmap.md` and continues by reviewing, in order, PRs #1, #3, #2, #4.


## Manual Software Installs
These baseline tools are required to access the code and run `bootstrap`, which does the rest of the setup.

### Visual Studio Code
Our suggested editor for all platforms: [VS Code](https://code.visualstudio.com/download) \
To view `roadmap.md` as slides, install VSCode extension: `marp-team.marp-vscode`

### Windows

#### Git
[Download git v2.53.0](https://github.com/git-for-windows/git/releases/download/v2.53.0.windows.1/Git-2.53.0-64-bit.exe)
 then install, selecting the following important options:

<table>
    <tr>
        <th>Install step</th>
        <th>Option we use</th>
    </tr>
    <tr>
        <td>Choosing the default editor</td>
        <td>vscode/notepad (unless you know Vim)</td>
    </tr>
    <tr>
        <td>Configuring the line ending conversions</td>
        <td>Checkout Windows-style, commit Unix-style</td>
    </tr>
    <tr>
        <td>Choose the default behavior of `git pull`</td>
        <td>Only ever fast-forward</td>
    </tr>
</table>

#### MSYS2
Our team focuses on unix-style scripts to keep effort reasonable.  For this strategy to work on Windows, we use MSYS2. Follow the **Installation** instructions at https://www.msys2.org

### Mac
```
brew install git
```
### Debian/Ubuntu
```
apt install git
```

## Initial Config
All the folloing commands are in bash, (or git bash on Windows).

### name and email for commits
To get "credit" for your work on github, your email should match the one you used to create your account in github.
```
git config --global user.email "your_email@example.com"
git config --global user.name "<Your Name>"
```
### SSH keys
To make writing (push) to this repo easy, we can set up SSH keys. 
#### Check for existing keys
```
ls ~/.ssh
```
If this contains any file named `id_ed25519.pub` or `id_rsa.pub`, you already have keys ➔ skip to [Saving keys to Github](#saving-keys-to-github).

#### Make new Keys
```
ssh-keygen -t ed25519 -C "your_email@example.com"
```
If you enter a passphrase, and prefer to not enter it for every push, refer to [this reference](https://docs.github.com/en/authentication/connecting-to-github-with-ssh/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent) for using the ssh-agent to store your credentials during a session.

#### Saving keys to Github
1. Use cat to print the content of your **public** key.
    ```
    cat ~/.ssh/id_ed25519.pub
    ```
1. Copy-paste the printed line into the "key" field [here](https://github.com/settings/ssh/new)
1. Enter a "Title" that indicates which computer's key this is.
1. Leave "Key type" as "Authentication key".

### Testing Git
Test you have read/write access by cloning and pushing a new branch.
```
cd ~/your/choice
git clone git@github.com:mthielvoldt/embedded-day-one.git
cd embedded-day-one
git switch -c <your-branch-name>
git push -u origin <your-branch-name>
```

## Pull Request Process
Here's our standard workflow.  It's meant to be reasonably light but keep us out of trouble.
1. Decide what your next effort aims to do.
1. start with the latest in `main`
    ```sh
    git switch main
    git pull
    ```
1. Create a branch
    ```sh
    git switch --create=example-branch-name
    git push -u origin HEAD
    ```
1. Do work, adding commits...
    ```sh
    git commit -a -m "short description of what this commit changes"
    git commit -a -m "another short description" 
    git push
    ```
1. When you get to a point that you want CI to start testing, create a PR.  If you just pushed new commits recently, github will suggest you open a PR. [Check it out](https://github.com/mthielvoldt/embedded-day-one/)
1. If your work isn't yet ready for review, **mark it as a draft** PR.  CI checks still run, so you can use draft PRs to get tests passing.
1. When your work is ready for review (tests passing), rebase your branch on `main` and re-run tests.
1. If the previous step succeeds, request a review from someone(s) specific.
1. Work with your reviewer.  Don't take requests for changes personally, it probably comes from a place of caring.
1. When approved, do a Rebase and Merge.

## Hardware
We're using a RP2040-Zero 
https://www.amazon.com/dp/B0DXL12W59

## Links
[Getting Started with Pico](https://pip-assets.raspberrypi.com/categories/610-raspberry-pi-pico/documents/RP-008276-DS-1-getting-started-with-pico.pdf?disposition=inline)

[RP2040 Datasheet](https://pip-assets.raspberrypi.com/categories/814-rp2040/documents/RP-008371-DS-1-rp2040-datasheet.pdf)
