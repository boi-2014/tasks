Test data
=========

Please create a subdirectory for each task using task code name (for example,
"portals"). Use the following convention for test files:

    task.0-01.in
    task.0-01.sol
    task.0-02.in
    task.0-02.sol
    task.1-01.in
    task.1-01.sol
    task.1-02.in
    task.1-02.sol
    task.2-01.in
    task.2-01.sol
    ...

The first number in "1-01" is the number of subtask, and the second number is the
number for the test within subtask. Use subtask 0 for example tests that are
provided in the task statement.

Also, add a text file that briefly describes the scoring and purpose of each
subtask and test. For example:


    Example tests:

        task.0-01.in
        task.0-01.sol
        task.0-02.in
        task.0-02.sol

    Subtask 1: 20 points. N <= 100, and no two lines cross each other.

        task.1-01.in  - all lines are horizontal.
        task.1-01.sol
        task.1-02.in  - all lines are vertical.
        task.1-02.sol
        ...
