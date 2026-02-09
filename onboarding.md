# For New Developers

## Install Git

### Windows
[Download v2.53.0](https://github.com/git-for-windows/git/releases/download/v2.53.0.windows.1/Git-2.53.0-64-bit.exe)

Important options to pick

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

### Mac
```
brew install git
```
### Debian/Ubuntu
```
apt install git
```

## Initial Config
All the folloing commands are in bash, (or git bash on Windows)
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
If this contains any file with extension `.pub`, you already have keys ➔ skip to [Saving keys to Github](#saving-keys-to-github).

#### Make new Keys
```
ssh-keygen -t ed25519 -C "your_email@example.com"
```
If you enter a passphrase, and prefer to not enter it for every push, refer to [this reference](https://docs.github.com/en/authentication/connecting-to-github-with-ssh/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent) for using the ssh-agent to store your credentials during a session.

#### Saving keys to Github
Register the content of ~/.ssh/<some-file>.pub [here](https://github.com/settings/ssh/new)

Test that your keys work by cloning, creating and pushing a new branch.

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