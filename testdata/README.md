Test data
=========

Please create a subdirectory for each task using task code name (for example,
"portals"). Use the following convention for test files:

    task.1-01p.in
    task.1-01p.sol
    task.1-02.in
    task.1-02.sol
    task.2-01.in
    task.2-01.sol
    ...

The first number in "1-01" is the number of subtask, and the second number is the
number for the test within subtask. Append letter `p` (public) for example tests 
that are provided in the task statement.

Also, add a text file that briefly describes the scoring and purpose of each
subtask and test. For example:


    Subtask 1: 20 points. N <= 100, and no two lines cross each other.

        task.1-01p.in  - example test 1.
        task.1-01p.sol
        task.1-02.in  - all lines are horizontal.
        task.1-02.sol
        task.1-03.in  - all lines are vertical.
        task.1-03.sol
        ...

If you use a program to generate tests, please upload it and make sure to add a
comment explaining the usage.
