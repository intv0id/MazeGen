  type ordinals =
    | Left
    | Right
    | Up
    | Down;

  let rec combinations_tail = (f, k, m, prefix) =>
    switch (k, m) {
    | (a, b) when a < 0 || b < 0 => failwith("ki or mi negative")
    | (a, b) when a > b => failwith("k > m")
    | (0, 0) =>
      if (f(Array.of_list(prefix))) {
        [prefix];
      } else {
        [];
      }
    | (0, b) => combinations_tail(f, 0, b - 1, [false, ...prefix])
    | (a, b) when a == b =>
      combinations_tail(f, a - 1, b - 1, [true, ...prefix])
    | (a, b) =>
      combinations_tail(f, a - 1, b - 1, [true, ...prefix])
      @ combinations_tail(f, a, b - 1, [false, ...prefix])
    };

  let rec passage = (configuration, m, n, x, y, ord) =>
    switch (ord, x, y) {
    | (Left, 0, _) => false
    | (Up, _, 0) => false
    | (Right, a, _) when a == m - 1 => false
    | (Down, _, b) when b == n - 1 => false

    | (Right, _, _) => passage(configuration, m, n, x + 1, y, Left)
    | (Down, _, _) => passage(configuration, m, n, x, y + 1, Up)

    | (Left, _, _) => configuration[y * (m - 2) + x]
    | (Up, _, _) => configuration[(m - 2) * (n - 2) + x * (n - 2) + y]
    };

  let sanity_check = (m, n, configuration) => {
    let maze = Array.make_matrix(m, n, false);

    let counter = ref(0);

    let rec search = (x, y) =>
      if (maze[x][y] == false) {
        maze[x][y] = true;
        counter.contents = counter.contents + 1;
        if (passage(configuration, m, n, x, y, Left)) {
          search(x - 1, y);
        };
        if (passage(configuration, m, n, x, y, Right)) {
          search(x + 1, y);
        };
        if (passage(configuration, m, n, x, y, Up)) {
          search(x, y - 1);
        };
        if (passage(configuration, m, n, x, y, Down)) {
          search(x, y + 1);
        };
      };

    search(0, 0);
    counter.contents == m * n;
  };

  let generate_tail = (m, n) =>
    combinations_tail(
      sanity_check(m, n),
      (m - 1) * (n - 1),
      m * (n - 1) + n * (m - 1),
      [],
    );
