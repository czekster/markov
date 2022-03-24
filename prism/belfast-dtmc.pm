dtmc

const int N=3; // N - number of states

const int sRainy=0;
const int sCloudy=1;
const int sSunny=2;

module Module1	
	n : [0..N] init sRainy; // total states, initial state sRainy
	// transitions
	[] (n=sRainy)  -> 0.80 : (n'=sRainy)  + 0.15 : (n'=sCloudy) + 0.05 : (n'=sSunny);
	[] (n=sCloudy) -> 0.20 : (n'=sCloudy) + 0.70 : (n'=sRainy)  + 0.10 : (n'=sSunny);
	[] (n=sSunny)  -> 0.20 : (n'=sSunny)  + 0.50 : (n'=sRainy)  + 0.30 : (n'=sCloudy);
endmodule