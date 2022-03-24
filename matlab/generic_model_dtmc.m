clear;

% MATLAB CTMC solver
% Author: Ricardo M. Czekster
% Date: 21/03/2022 

%original model
R = [-10, 1, 5, 4;
2, -2, 0, 0;
0, 9, -11, 2;
7, 0, 1, -8];

% for CTMC, pi = pi * P, i.e., P * pi = pi:
% pi1 pi2 pi3 pi4 * -10  1  5  4  = 0 0 0 0
%                     2 -2  0  0
%                     0  9 -11 2
%                     7  0  1 -8

% -10pi1 + 2pi2 + 7pi4 = 0
% pi1 - 2pi2 + 9pi3 = 0
% 5pi1 - 11pi3 + pi4 = 0
% 4pi1 + 2pi3 - 8pi4 = 0
% pi1 + pi2 + pi3 + pi4 = 1

% Model
Q = [-10, 2, 0, 7;
1, -2, 9, 0;
5, 0, -11, 1;
4, 0, 2, -8;
1, 1, 1, 1];

% auxiliary vector with one position set as 1
b = [0; 0; 0; 0; 1];

pi = linsolve(Q,b);

% show result
pi

