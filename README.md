# CWRU Robotics Code Sandbox
This is a repository that hosts code for the various CWRU Robotics Club Projects.
### How to contribute
Step 1: Install git  
  - Windows: Go to https://git-scm.com/downloads
  - Linux (debian based, aka ubuntu): Run *sudo apt-get install git*
  - Linux (Fedora things): Run *sudo yum install git*
  - Mac: Run *git* in the XCode command terminal

Step 2: Configuring git
  - Run the command *git config --global user.name "John Doe"* where John Doe is your name
  - Run the command *git config --global user.email example@case.edu* where example@case.edu is the email you use for github

Step 3: Set up the repository
  - Create a folder somewhere that will be the home to all this code
  - Inside that folder open up a command terminal (windows users this is not powershell this is bash, run git bash from the start menu)
  - Make sure the folder is empy and run the command *git init*
  - Run the command *git remote add origin https://github.com/cwruRobotics/sandbox.git*
  - Run the command *git pull origin master*
  - You should now see many files in that folder, this is now your working directory

Step 4: Committing your changes
  - Go up to the top directory in the workspace (where you did git init)
  - Run the command *git pull origin master*.  This pulls the code from github in case any changes were made.  If any changes were made to the files you have changed and they conflict with the changes you made, a manual merge is needed
  - Run the command *git status*.  If you have made any changes they will show up as red.  You can use the *git add filepath* to add the files manually or add them all with *git add -A*
  - Once the files are added run *git status* again to make sure all the files you wanted were added.  The added files will show up as green
  - Once all is in order, run *git commit -m "message detailing the commit here"* and write a little message saying what code you changed
  - Finally, run *git push origin master* to push your code to github

Note, it is generally not good to push to the master branch of a repository but since this repo is small and unorganized it should be fine.

### Questions?
Step 1:
  - Google it

Step 2:
  - Ask a computer science friend

Step 3:
  - Email Marc
