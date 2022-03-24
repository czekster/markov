clear;

% MATLAB DTMC solver
% Author: Ricardo M. Czekster
% Date: 18/03/2022 

SIZE=3;

% Model
Q = [-109.3154, 100, 0, 0, 0, 9.1854, 0, 0, 0.13, 0, 0;
200, -205.13, 5, 0, 0, 0, 0, 0, 0, 0, 0.13;
0, 0.0004, -135.0004, 8, 0, 0, 127, 0, 0, 0, 0;
0, 0, 41.58, -58.58, 17, 0, 0, 0, 0, 0, 0;
0, 0, 0, 1.69, -3.04, 1.35, 0, 0, 0, 0, 0;
87, 0, 0, 0, 0.18, -87.18, 0, 0, 0, 0, 0;
0, 0, 14, 0, 0, 0, -17.5, 3.5, 0, 0, 0;
0, 0, 0, 0, 0, 0, 4.2336, -104.4436, 100, 0.21, 0;
100, 0, 0, 0, 0, 0, 0, 419.58, -519.58, 0, 0;
0, 0, 0, 0, 0, 0, 0, 2.77, 0, -10.57, 7.8;
0, 0.013, 0, 0, 0, 0, 0, 0, 0, 30.24, -30.253];

% ultimo elemento da coluna recebe zero (este elemento nao eh perdido pois a diagonal contem a diferenca)
for i=1:SIZE
  Q(i,SIZE) = 1;
end

% b eh uma matriz de uma coluna com a ultima posicao igual a 1 (esta coluna nao pode ser zerada)
b = [0; 0; 0; 0; 0; 0; 0; 0; 0; 0; 1];

% QT guarda a transposta da matriz Q
QT = Q';

% solucao linear do sistema de equacoes (resulta no vetor P)
P = QT \ b;

% multiplica o indice encontrado por 100 para determinar a probabilidade de permanencia do estado
%P = P*100;

%mostra o conteudo do vetor de probabilidades P
P

