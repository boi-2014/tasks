Test data
=========

Please create a subdirectory for each task using task code name (for example,
"portals"). Use the following convention for test files:

    task.01p-1.in
    task.01p-1.sol
    task.02-1.in
    task.02-1.sol
    task.03-2.in
    task.03-2.sol
    task.04-12.in
    task.04-12.sol
    ...

The first number in "04-12" is the unique number of the test, and the second number is the
set of subtasks the test is in. Append letter `p` (public) to the test number for example tests 
that are provided in the task statement.

Also, add a text file that briefly describes the scoring and purpose of each
subtask and test. For example:


    Subtask 1: 20 points. N <= 100, and no two lines cross each other.

        task.01p-1.in  - example test 1.
        task.01p-1.sol
        task.02-1.in  - all lines are horizontal.
        task.02-1.sol
        task.03-1.in  - all lines are vertical.
        task.03-1.sol
        ...

If you use a program to generate tests, please upload it and make sure to add a
comment explaining the usage.
