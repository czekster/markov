# Book: "Markov Chains for programmers"
This book was published by me, Ricardo M. Czekster, in April/2022. I hope you enjoy it reading as much as I've enjoyed working on it.

You will find here supporting materials for the book I have written about Markov Chains (MC), which you may also download here.

## Challenges
I proposed a number of challenges throughout the book. The code for all solutions are available for download here.

One remark: to avoid repeated functions I created a folder called `project00` that has a `Makefile` and all the challenges (you may want to check the file `markov.c` to access auxiliary functions). In this project, each challenge has a `main()` function, so they work independently.

The `project01` folder contains a full project with one `main()` function and several built-in command-line options. Consult "Challenge 07" for more information about this project.

## Models
The following models are available (they were named **S**N where N is the number of states):

- S2-lighting-ctmc.txt
- S2-lighting-dtmc.txt
- S2-pushkin-dtmc.txt
- S3-land-of-oz-dtmc.txt
- S3-weather-belfast-dtmc.txt
- S4-generic-ctmc.txt
- S4-lilypad-ctmc.txt
- S4-maze-model-dtmc.txt
- S5-ehrenfest-dtmc.txt
- S6-birth-and-death-ctmc.txt
- S9-maze-model-dtmc.txt

You may try to run the challenges code for these models (beware that the type should match, either CTMC or DTMC).

## Numerical methods and tools
I have explored Power Matrix, Vector-Matrix Multiplication, some MATLAB&reg; scripting, _forward_ simulation, and some MS-Excel spreadsheets.

## Author
Ricardo M. Czekster
rczekster at gmail
