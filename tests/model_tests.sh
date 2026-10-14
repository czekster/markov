#!/usr/bin/env bash
# End-to-end tests: run the project01 'markov' binary and the project00 challenges
# on the models in ../models and compare against tests/expected.txt.
set -u
cd "$(dirname "$0")"
ROOT=..
BIN=$ROOT/challenges/project01/markov
P00=$ROOT/challenges/project00
MODELS=$ROOT/models
fail=0; pass=0

ok()  { pass=$((pass+1)); }
bad() { fail=$((fail+1)); echo "  FAIL $*"; }

# compare "i=value" lines (last n of them) with expected vector, max abs error <= tol
compare() {   # $1=output $2=tol $3...=expected
   local out=$1 tol=$2; shift 2
   local n=$#
   echo "$out" | grep -E '^[0-9]+=' | tail -n "$n" | cut -d= -f2 |
      awk -v tol="$tol" -v ev="$*" 'BEGIN{split(ev,e," ")}
         {d=$1-e[NR]; if (d<0) d=-d; if (d>m) m=d; if ($1!=$1+0) m=1e9}
         END{if (NR!='"$n"' || m>tol) {printf "maxerr=%g rows=%d", m, NR; exit 1}}'
}

# ---- expected steady states
while read -r model op tol rest; do
   [[ -z "$model" || "$model" == \#* ]] && continue
   case $op in
      1) out=$("$BIN" "$MODELS/$model" 1) ;;
      2) out=$(echo 500000 | "$BIN" "$MODELS/$model" 2) ;;
      4) lam=$("$P00/challenge06" "$MODELS/$model" | sed -n 's/^lambda=//p')
         t=$(awk -v l="$lam" 'BEGIN{t=2e6/l; if (t>499999) t=499999; printf "%d", t}')
         out=$(echo "$t" | "$BIN" "$MODELS/$model" 4) ;;
   esac
   if msg=$(compare "$out" "$tol" $rest); then ok; else bad "$model OP=$op $msg"; fi
done < expected.txt

# ---- periodic chains must warn instead of claiming convergence
for model in S9-maze-model-dtmc.txt S4-maze-model-dtmc.txt S5-ehrenfest-dtmc.txt; do
   for op in 0 1; do
      if "$BIN" "$MODELS/$model" $op | grep -q "no convergence"; then ok; else bad "$model OP=$op: expected non-convergence warning"; fi
   done
done

# ---- power method agrees with VMM on an aperiodic chain
out=$("$BIN" "$MODELS/S3-weather-belfast-dtmc.txt" 0 | tail -1 | tr ' ' '\n' | grep . | awk '{print NR-1"="$1}')
if msg=$(compare "$out" 1e-4 0.762500 0.168750 0.068750); then ok; else bad "Belfast OP=0 $msg"; fi

# ---- uniformised DTMC (OP=3) of the Generic model
out=$("$BIN" "$MODELS/S4-generic-ctmc.txt" 3 | grep -A4 "(uniformised) DTMC" | tail -4 | tr '\n' ' ')
exp="0.090909 0.090909 0.454545 0.363636 0.181818 0.818182 0.000000 0.000000 0.000000 0.818182 0.000000 0.181818 0.636364 0.000000 0.090909 0.272727"
if [[ "$(echo $out)" == "$exp" ]]; then ok; else bad "Generic OP=3 got: $out"; fi

# ---- every DTMC model validates; bad matrices are rejected
for f in "$MODELS"/*dtmc.txt; do
   if "$P00/challenge04" "$f" 1 | grep -q "well-formed"; then ok; else bad "$(basename "$f") should validate"; fi
done
tmp=$(mktemp -d)
printf "0.5 0.4 0\n0.2 0.8 0\n0.3 0.3 0.4\n" > "$tmp/sum.txt"
printf "0.5 0.5 0\n0 1 0\n0.3 0.3 0.4\n"    > "$tmp/abs.txt"
printf "0 1 0\n0 0 0\n2 0 0\n"             > "$tmp/cabs.txt"
"$P00/challenge04" "$tmp/sum.txt" 1 | grep -q "does NOT sum" && ok || bad "row-sum error not detected"
"$P00/challenge04" "$tmp/abs.txt" 1 | grep -q "absorbing state (state=1)" && ok || bad "DTMC absorbing state not detected"
"$P00/challenge06" "$tmp/cabs.txt"  | grep -q "absorbing state (state=1)" && ok || bad "CTMC absorbing state not detected"
rm -rf "$tmp"

# ---- challenge06 lambda and the remaining challenges run
[[ "$("$P00/challenge06" "$MODELS/S4-generic-ctmc.txt" | sed -n 's/^lambda=//p')" == "11.000000" ]] && ok || bad "challenge06 lambda != 11"
"$P00/challenge01" 20 >/dev/null && ok || bad "challenge01 exited with error"
"$P00/challenge02" 20 5 >/dev/null && ok || bad "challenge02 exited with error"
"$P00/challenge03" | grep -q "well-formed" && ok || bad "challenge03"
"$P00/challenge05" "$MODELS/S3-weather-belfast-dtmc.txt" 1000 >/dev/null && ok || bad "challenge05 exited with error"
"$P00/challenge07" "$MODELS/S4-lilypad-ctmc.txt" 100 >/dev/null && ok || bad "challenge07 exited with error"

echo "model tests: $((pass+fail)) checks, $fail failed"
[[ $fail -eq 0 ]]
