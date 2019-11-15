type ordinals =
  | Left
  | Right
  | Up
  | Down;

let rec passage = (configuration, m, n, x, y, ord) => {
  let check_pass = passage(configuration, m, n);
  switch (ord, x, y) {
  | (Left, 0, _) => false
  | (Up, _, 0) => false
  | (Right, a, _) when a == m - 1 => false
  | (Down, _, b) when b == n - 1 => false

  | (Left, _, _) => check_pass(x - 1, y, Right)
  | (Up, _, _) => check_pass(x, y - 1, Down)

  | (Right, _, _) => !configuration[y * (m - 1) + x]
  | (Down, _, _) => !configuration[n * (m - 1) + (y * m + x)]
  };
};

let sanity_check = (m, n, configuration) => {
  let maze = Array.make_matrix(m, n, false);
  let check_pass = passage(configuration, m, n);
  Js.log(configuration);

  let rec search = (x, y) =>
    if (maze[x][y] == false) {
      maze[x][y] = true;

      let l = check_pass(x, y, Left) ? search(x - 1, y) : 0;
      let r = check_pass(x, y, Right) ? search(x + 1, y) : 0;
      let u = check_pass(x, y, Up) ? search(x, y - 1) : 0;
      let d = check_pass(x, y, Down) ? search(x, y + 1) : 0;

      1 + l + r + u + d;
    } else {
      0;
    };

  search(0, 0) == m * n;
};