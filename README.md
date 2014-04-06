tasks
=====

BOI 2014 task descriptions, translations, test data and solutions.

To start:

    # Select where you want to store the files:
    cd ~/Documents/boi

    # Clone repository:
    git clone https://github.com/boi-2014/tasks.git

To make changes:

    # Sync your repository to head:
    git pull

    # Change something:
    cd tasks
    vim day1/task/task.tex

    # Review and stage your changes:
    git status
    git diff
    git add day1/task/task.{tex,pdf}

    # Commit and push:
    git commit -m "Updated limits of task Foo."
    git push
