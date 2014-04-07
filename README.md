BOI'2014 tasks
==============

Getting Started
---------------

Here are quick steps to get you started. In this example, we assume
that we will keep files under ~/Documents, please change that to
your prefered location.

Start by cloning the repository:

    cd ~/Documents
    git clone https://github.com/boi-2014/tasks.git

Now whenever you need to change something, follow this cycle:

    # Sync your repository to head.
    git pull

    # Change something.
    vim ~/Documents/tasks/day1/foo/en/foo.tex

    # Review and stage your changes.
    git status
    git diff
    git add day1/task/task.{tex,pdf}

    # Commit and push.
    git commit -m "Updated limits for task Foo."
    git push

If you need an introduction to git, visit http://try.github.io/.

Configuring LaTeX
-----------------

The LaTeX class files are stored in "latex" subdirectory,
and figures are stored in subdirectory "figures".
In order to compile task statements, you will need to tell
LaTeX about these directories.
One way to achieve that is to add symlinks in standard LaTeX searched directories:

    mkdir -p ~/Library/texmf/tex/
    ln -s ~/Documents/tasks/latex ~/Library/texmf/tex/boi2014-latex
    ln -s ~/Documents/tasks/figures ~/Library/texmf/tex/boi2014-figures

Or if you use Linux:

    ln -s ~/Documents/tasks/latex /usr/local/share/texmf/boi2014-latex
    ln -s ~/Documents/tasks/figures /usr/local/share/texmf/boi2014-figures
    
Alternatively you can set TEXINPUTS enviroment variable, or use settings
of your prefered GUI editor.

Translating Task Descriptions
-----------------------------

First translate the LaTeX class file for your language, which contains common
strings used as section headers. Any additional packages required to support
your language should also be added to this file.

Then make a copy of task you want to translate (be sure to respect the naming
convention), set your language specific class file as documentclass and
translate the text of the task description.
