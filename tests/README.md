# Tests

Run everything from the repository root:

```bash
make -C tests
```

This builds `project00` and `project01` with `-Wall -Werror`, then runs:

- **`unit_tests.c`**: checks individual functions of `project01`: validation (row sums, absorbing states), `fix_ctmc`, `discover_lambda`, the uniformised DTMC (`I + Q/lambda`), `Q' = Q + lambda*I`, Power and VMM on the Belfast model, float drift under repeated squaring, the exponential generator, and the CTMC race (`P(j wins) = q_ij/|q_ii|`).
- **`model_tests.sh`**: runs the `markov` binary and the challenges on every model in `../models`, comparing results against the exact steady states in `expected.txt`. Periodic chains must report non-convergence, and invalid matrices must be rejected.

Simulations are random, so their tolerances are 1–2%.

## Run the tests before every commit

Once per clone:

```bash
git config core.hooksPath .githooks
```

From then on, `git commit` runs the tests and aborts if any fail. In an emergency, `git commit --no-verify` skips them.

GitHub Actions (`.github/workflows/tests.yml`) runs the same tests on every push and pull request.
