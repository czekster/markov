# Book: "Markov Chains for programmers"
This book was published by Self Publishers Worldwide (another publication by the _lazy panda_ collection), Ricardo M. Czekster, in April/2022. I hope you enjoy it reading as much as I've enjoyed crafting paragraphs and coding it.

You will find here supporting materials for the book I have written about Markov Chains (MC), which you may also [download here](MC-for-programmers2022.pdf).

## License
The book is under Creative Commons (CC BY 4.0) and the code is under GPLv3.

Feel free to use it and attribute the original source.

## Folders
The structure of the repository is as follows:

- `challenges`: proposed challenges throughout the book;
- `matlab`: MATLAB&reg; scripts for some solutions; 
- `models`: a list of DTMC and CTMC models (in the format that we explored in the book, with code);
- `prism`:  [PRISM](https://www.prismmodelchecker.org/) models (in CTMC and DTMC);

## Challenges
I proposed a number of challenges throughout the book. The code for all solutions are available for download here.

One remark: to avoid repeated functions I created a folder called `project00` that has a `Makefile` and all the challenges (you may want to check the file `markov.c` to access auxiliary functions). In this project, each challenge has a `main()` function, so they work independently.

The `project01` folder contains a full project with one `main()` function and several built-in command-line options. Consult "Challenge 07" for more information about this project.

[Click here for more information about individual challenges](challenges.md)


## Models
The following models are available (they were named **S**N where N is the number of states):

- `S2-lighting-ctmc.txt`: The Lighting model, using rates;
- `S2-lighting-dtmc.txt`: The Lighting model, using probabilities;
- `S2-pushkin-dtmc.txt`: The pushkin model developed by A. A. Markov (according to Snell's book);
- `S3-land-of-oz-dtmc.txt`: The land of oz model;
- `S3-weather-belfast-dtmc.txt`: The Belfast weather model (by Stewart);
- `S4-generic-ctmc.txt`: The Generic model;
- `S4-lilypad-ctmc.txt`: The Lily Pad model (frog in the pond);
- `S4-maze-model-dtmc.txt`: The Mouse Maze model;
- `S5-ehrenfest-dtmc.txt`: The Ehrenfest model
- `S6-birth-and-death-ctmc.txt`: A six state Birth and Death model;
- `S9-maze-model-dtmc.txt`: A larger Mouse Maze model, with 9 states;

You may try to run the challenges code for these models (beware that the type should match, either CTMC or DTMC).

## Numerical methods and tools
I have explored Power Matrix, Vector-Matrix Multiplication, [PRISM](https://www.prismmodelchecker.org/) models, some MATLAB&reg; scripting, _forward_ simulation, and some MS-Excel spreadsheets.

## Author
Ricardo M. Czekster
rczekster at gmail
