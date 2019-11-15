open Verifier;

exception EndOfCombinations;

let reset_prefix = {
  let rec reset_prefix_tail = (prefix, k, m) =>
    switch (k, m) {
    | (_, 0) => prefix
    | (a, _) when a > 0 =>
      reset_prefix_tail([true, ...prefix], k - 1, m - 1)
    | _ => reset_prefix_tail([false, ...prefix], 0, m - 1)
    };
  reset_prefix_tail([]);
};

let rec incr = (k, m, combination) => {
  switch (k, m) {
  | (0, m_) when m_ > 0 => raise(EndOfCombinations)
  | _ =>
    switch (combination) {
    | [false, true, ..._] => [true, false, ...reset_prefix(k - 1, m - 2)]
    | [false, ...b] => [false, ...incr(k, m - 1, b)]
    | [true, ...b] => [true, ...incr(k - 1, m - 1, b)]
    | _ => raise(EndOfCombinations)
    }
  };
};

let generate_n_combinations = (k, m, n, ~start_combination as sc=?, ()) => {
  let incr_conf = incr(k, m);
  let check = sanity_check(k, m);
  let rec generate_n_combinations_tail = (acc, comb_start, n) =>
    try (
      switch (n) {
      | 0 => acc
      | _ =>
        check(comb_start->Array.of_list)
          ? generate_n_combinations_tail(
              [comb_start, ...acc],
              incr_conf(comb_start),
              n - 1,
            )
          : generate_n_combinations_tail(acc, incr_conf(comb_start), n - 1)
      }
    ) {
    | EndOfCombinations => acc
    };
  let cs =
    switch (sc) {
    | None => reset_prefix(k, m)
    | Some(a) => a
    };
  generate_n_combinations_tail([], cs, n);
};

let generate = (m_dim, n_dim) => {
  let (k, m) = (
    (m_dim - 1) * (n_dim - 1),
    m_dim * (n_dim - 1) + n_dim * (m_dim - 1),
  );
  let incr_conf = incr(k, m);
  let check = _ => true;
  let rec generate_next_combinations_tail = (acc, comb_start) =>
    try (
      check(comb_start->Array.of_list)
        ? generate_next_combinations_tail(
            [comb_start, ...acc],
            incr_conf(comb_start),
          )
        : generate_next_combinations_tail(acc, incr_conf(comb_start))
    ) {
    | EndOfCombinations =>
      check(comb_start->Array.of_list) ? [comb_start, ...acc] : acc
    };
  generate_next_combinations_tail([], reset_prefix(k, m));
};