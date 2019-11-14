open Verifier;

let rec combinations_tail = (prefix, f, k, m) =>
  switch (k, m) {
  | (a, b) when a < 0 || b < 0 => failwith("k or m negative")
  | (a, b) when a > b => failwith("k > m")
  | (0, 0) => f(Array.of_list(prefix)) ? [prefix] : []
  | (0, b) => combinations_tail([false, ...prefix], f, 0, b - 1)
  | (a, b) when a == b =>
    combinations_tail([true, ...prefix], f, a - 1, b - 1)
  | (a, b) =>
    combinations_tail([true, ...prefix], f, a - 1, b - 1)
    @ combinations_tail([false, ...prefix], f, a, b - 1)
  };

let combinations = combinations_tail([]);

let generate_tail = (m, n) =>
  combinations(
    sanity_check(m, n),
    (m - 1) * (n - 1),
    m * (n - 1) + n * (m - 1),
  );