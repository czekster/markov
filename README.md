# Book: "Markov Chains for programmers"
[<img align="right" src="cover-imgs/cover-thumb.png">](MC-for-programmers2022.pdf)
This book was published by Self Publishers Worldwide (another publication by the _lazy panda_ collection), and authored by Ricardo M. Czekster.

The first edition was made public in April/2022. 

"Markov Chains for programmers" is devoted to programmers at any level wanting to understand more about the underpinnings of Markov Chains (MC) and basic solution methods.

You will find here supporting materials for the book such as **C programming code** and solutions, MATLAB scripts, PRISM models (CTMC/DTMC) for the examples provided in the book, which you may also [download here](MC-for-programmers2022.pdf).

This book is a companion to this [paper about Performance Evaluation](https://www.researchgate.net/publication/337623607_Introduction_to_Performance_Evaluation_of_Systems), published as a pre-print in [ResearchGate](https://www.researchgate.net/profile/Ricardo-Czekster).

## License
The book is under Creative Commons (CC BY 4.0) and the code is under GPLv3.

Feel free to use it and attribute the original source.

DOI link: [http://dx.doi.org/10.6084/m9.figshare.19714384.v2](http://dx.doi.org/10.6084/m9.figshare.19714384.v2)

## Folders
The structure of the repository is as follows:

- `challenges`: proposed challenges throughout the book;
- `matlab`: MATLAB&reg; scripts for some solutions; 
- `models`: a list of DTMC and CTMC models (in the format that we explored in the book, with code);
- `prism`:  [PRISM](https://www.prismmodelchecker.org/) models (in CTMC and DTMC);
- `spreadsheets`: MS-Excel spreadsheets reproducing the experiments (CTMC/DTMC solution, simulation);

## Challenges
The book proposes a number of _challenges_ throughout its chapters. The code for all solutions is available for download in this repository.

One remark: to avoid repetitions in the code, there is a folder called `project00` that has a `Makefile` and all the challenges (you may want to check the file `markov.c` to access auxiliary functions). In this project, each challenge has a `main()` function, so they work independently.

The `project01` folder contains a full project with one `main()` function and several built-in command-line options. Consult "Challenge 07" for more information about this project.

Please, let me know if you find something odd or something that needs changing. Thank you in advance.

[Click here for more information about individual challenges](challenges.md)


## Models
The book offers many models for evaluating your projects in a textual matrix format (.txt), prism (.sm or .pm), and MATLAB (.m).

### CTMC/DTMC models to run internally
The following models are available (they were named **S**N where N is the number of states):

- `models/S2-lighting-ctmc.txt`: The Lighting model, using rates;
- `models/S2-lighting-dtmc.txt`: The Lighting model, using probabilities;
- `models/S2-pushkin-dtmc.txt`: The pushkin model developed by A. A. Markov (according to Grinstead and Snell's book _Introduction to Probability_);
- `models/S3-land-of-oz-dtmc.txt`: The land of oz model;
- `models/S3-weather-belfast-dtmc.txt`: The Belfast weather model (by Stewart);
- `models/S4-aging-rejuvenation-ctmc`: Software aging and rejuvenation model, CTMC;
- `models/S4-aging-rejuvenation-dtmc`: Same (aging & rej), DTMC version;
- `models/S4-generic-ctmc.txt`: The Generic model;
- `models/S4-lilypad-ctmc.txt`: The Lily Pad model (frog in the pond);
- `models/S4-maze-model-dtmc.txt`: The Mouse Maze model;
- `models/S5-ehrenfest-dtmc.txt`: [The Ehrenfest model](https://en.wikipedia.org/wiki/Ehrenfest_model);
- `models/S6-birth-and-death-ctmc.txt`: A six state Birth and Death model;
- `models/S9-maze-model-dtmc.txt`: A larger Mouse Maze model, with 9 states;
- `models/S26-shakespeare-ctmc.txt`: A brief analysis of one of Shakespeare's Sonnets with MC;

### PRISM models
- `prism/belfast-dtmc.pm` for the Belfast weather model;
- `prism/generic-ctmc.sm` for the Generic model;
- `prism/lily-ctmc.sm` and `lily.dtmc.pm` for the Lily pad model;
- `prism/aging.sm` and accompanying `prism/aging.props` model and property file, respectively;

### MATLAB models
- `matlab/generic_model_dtmc.m`;
- `matlab/matlabsolution_dtmc.m`;

## Challenges
You may try to run the challenges code for these models (beware that the type should match, either CTMC or DTMC).
[Click here for more information on models](models.md)

## Numerical methods, models and tools
The methods, models and tools explored in the book are Power Matrix, Vector-Matrix Multiplication, [PRISM](https://www.prismmodelchecker.org/) models, some MATLAB&reg; scripting, _forward_ simulation, and some MS-Excel spreadsheets (with basic models).

## How to cite the work
I thank you for your attribution, and for recognising the work.
To cite the book, please follow this suggestion:
- Czekster, Ricardo M. **"Markov Chains for programmers"**, Available at: https://czekster.github.io/markov/. DOI: http://dx.doi.org/10.6084/m9.figshare.19714384.v2, April, 2022.

## Author
<img align="right" width="200" src="images/rmc.png">
Ricardo M. Czekster
rczekster at gmail

Ricardo is an active researcher in dependability and cyber-security.
Please, check out his virtual presence on the following platforms:
- [ORCID](https://orcid.org/0000-0002-6636-4398)
- [ResearchGate](https://www.researchgate.net/profile/Ricardo-Czekster)
- [DBLP](https://dblp.uni-trier.de/pers/hd/c/Czekster:Ricardo_M=)
- [Google Scholar profile](https://scholar.google.com.br/citations?user=M4SZcHsAAAAJ)
- [LinkedIn](https://www.linkedin.com/in/ricardoczekster/)
- [Publons](https://publons.com/researcher/1440444/ricardo-m-czekster/)
- [GitHub](https://github.com/czekster/)
