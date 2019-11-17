open Verifier;

exception EndOfCombinations;

type combinationsChunk =
  | LastChunk(list(list(bool)))
  | Chunk(list(list(bool)));

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

let reset_suffix = {
  let rec reset_suffix_tail = (prefix, k, m) =>
    switch (k, m) {
    | (_, 0) => prefix
    | (a, b) when b > a => reset_suffix_tail([false, ...prefix], k, m - 1)
    | _ => reset_suffix_tail([true, ...prefix], k - 1, m - 1)
    };
  reset_suffix_tail([]);
};

let incr = (k, m) => {
  let rec incr_tail = (acc, k_, m_, combination) => {
    switch (k, m) {
    | (0, m_) when m_ > 0 => raise(EndOfCombinations)
    | _ =>
      switch (combination) {
      | [false, true, ...c] =>
        reset_prefix(k - k_, m - m_) @ [true, false, ...c]
      | [false, ...b] => incr_tail([true, ...acc], k_, m_ - 1, b)
      | [true, ...b] => incr_tail([true, ...acc], k_ - 1, m_ - 1, b)
      | _ => raise(EndOfCombinations)
      }
    };
  };
  incr_tail([], k, m);
};

let generate_nb_combinations =
    (m_dim, n_dim, nb, ~start_combination as sc=?, ()) => {
  let (k, m) = (
    (m_dim - 1) * (n_dim - 1),
    m_dim * (n_dim - 1) + n_dim * (m_dim - 1),
  );
  let incr_conf = incr(k, m);
  let check = sanity_check(m_dim, n_dim);
  let rec generate_next_combinations_tail = (acc, nb_, ~comb_start=?, ()) =>
    switch (nb_) {
    | 0 => Chunk(acc)
    | _ =>
      try (
        {
          let new_comb =
            switch (comb_start) {
            | None => reset_prefix(k, m)
            | Some(a) => incr_conf(a)
            };
          check(new_comb->Array.of_list)
            ? generate_next_combinations_tail(
                [new_comb, ...acc],
                nb_ - 1,
                ~comb_start=new_comb,
                (),
              )
            : generate_next_combinations_tail(
                acc,
                nb_,
                ~comb_start=new_comb,
                (),
              );
        }
      ) {
      | EndOfCombinations => LastChunk(acc)
      }
    };

  generate_next_combinations_tail([], nb, ~comb_start=?sc, ());
};