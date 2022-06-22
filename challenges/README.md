# Project files

I present two projects:
- `project00`: individual challenges (from 01 to 07), each with its own `main()` function, `defs.h` and `Makefile` files (you may build individual challenges, e.g., `make challenge06`), and `markov.c` with the implementations.
- `project01`: a full project (with a single `main()` function), with lots of 'services', such as:

```
void echo_help() {
   printf("This is the Markov chain solver [last update: 23/03/2022].\n");
   printf("To run DTMC: markov <FILE> <OP>\n");
   printf(" where <OP> is one out of these options:\n");
   printf("   0 Solve DTMC - Power Matrix\n");
   printf("   1 Solve DTMC - Vector-Matrix Multiplication\n");
   printf("   2 Simulate DTMC (pass <SAMPLES> parameter!)\n");
   printf("   3 Convert CTMC to Embedded DTMC\n");
   printf("   4 Simulate CTMC (pass <TIME> parameter!)\n");
}
```
