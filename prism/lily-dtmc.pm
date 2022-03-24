// Lily Pad model (frog in the pond) - DTMC

dtmc

const int N=4; // N - number of states

const int sA=0;
const int sB=1;
const int sC=2;
const int sD=3;

module Module1	
	n : [0..N] init sA; // total states, initial state sA
	// transitions
	[] (n=sA) -> 0.10 : (n'=sA) + 0.55 : (n'=sB) + 0.30 : (n'=sC) + 0.05 : (n'=sD);
	[] (n=sB) -> 0.45 : (n'=sA) + 0.00 : (n'=sB) + 0.45 : (n'=sC) + 0.10 : (n'=sD);
	[] (n=sC) -> 0.40 : (n'=sA) + 0.10 : (n'=sB) + 0.35 : (n'=sC) + 0.15 : (n'=sD);
	[] (n=sD) -> 0.25 : (n'=sA) + 0.35 : (n'=sB) + 0.10 : (n'=sC) + 0.30 : (n'=sD);
endmodule