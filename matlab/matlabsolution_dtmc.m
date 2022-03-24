clear;

% MATLAB DTMC solver
% Author: Ricardo M. Czekster
% Date: 18/03/2022 

%original model
P = [0.8, 0.15, 0.05;
0.7, 0.2, 0.1;
0.5, 0.3, 0.2];

% for DTMC, pi = pi * P, i.e., P * pi = pi:
% 0.80 0.15 0.05     pi1     pi1
% 0.70 0.20 0.10  *  pi2  =  pi2
% 0.50 0.30 0.20     pi3     pi3

% becomes
% 0.80pi1 + 0.70pi2 + 0.50pi3 = pi1
% 0.15pi1 + 0.20pi2 + 0.30pi3 = pi2
% 0.05pi1 + 0.10pi2 + 0.20pi3 = pi3

% so, the model becomes:
% -0.20pi1 + 0.70pi2 + 0.50pi3 = 0
%  0.15pi1 - 0.80pi2 + 0.30pi3 = 0
%  0.05pi1 + 0.10pi2 - 0.80pi3 = 0

% subjected to pi1 + pi2 + pi3 = 1;

% Yielding:
% -0.20pi1 + 0.70pi2 + 0.50pi3 = 0
%  0.15pi1 - 0.80pi2 + 0.30pi3 = 0
%  0.05pi1 + 0.10pi2 - 0.80pi3 = 0
%  1.00pi1 + 1.00pi2 + 1.00pi3 = 1

% Model
M = [-0.2, 0.7, 0.5;
0.15, -0.8, 0.3;
0.05, 0.1, -0.8;
1, 1, 1];

% auxiliary vector with one position set as 1
b = [0; 0; 0; 1];

pi = linsolve(M,b);

% show result
pi

