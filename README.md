Developer Challenge
===================
We require a small application that:
 - Can take in a CSV formatted file
 - Transpose the contents
 - Save the result
 - Uses no external libraries to perform the transposition
    - Using external libraries to open/close files or anything not related to the transposion is acceptable

Example
-------
```
    122,   139,   156
    138,   155,   172     becomes     122,   138,   154,   170,   186,   202
    154,   171,   188    -------->    139,   155,   171,   187,   203,   219
    170,   187,   204                 156,   172,   188,   204,   220,    11
    186,   203,   220
    202,   219,    11
```

Development
-----------
 - You are provided this minimal repository, `interview-challenge`, please perform your work on branch `<candidate_name>`
 - Sample data to be found at `interview-challenge/_sample_data`
 - Once complete please email back this repository to your interviewers

Scope
-----
Please do not work on this problem for longer than 45 minutes.

This is *not* a closed-book assessment.

Don’t worry if you cannot complete the challenge in the allotted time

Extra thoughs
-------------
How could you provide this same solution using Python via Flask, Django or equivalent framework?

How the solution could be expanded given further time with respect to: testing, interfaces (www/api), deployment and maintenance?

Program Function
-----------
void transpose_csv(const char *path, const char *outfile)

**arg:
const char* path = file path to input.csv file
const char* outfile = file path to output.csv (can be changed to whatever) file

Return: void

Usage
-----------
run gcc transpose_csv.c -o transpose_csv && ./transpose_csv
