type direction =
  | Vertical
  | Horizontal;
type context;
type canvas;

type d = {
  m: int,
  n: int,
};

[@bs.val] external document: Js.t({..}) = "document";
[@bs.send] external getContext: (canvas, string) => context = "getContext";
[@bs.send]
external fillRect: (context, float, float, float, float) => unit = "fillRect";

let digit_of_bool = a => a ? "1" : "0";

let string_of_bool_list = {
  let rec string_of_bool_list_tail = (acc, bl) => {
    switch (bl) {
    | [a, ...b] => string_of_bool_list_tail(acc ++ digit_of_bool(a), b)
    | [] => acc
    };
  };
  string_of_bool_list_tail("");
};

let draw = (m, n, id, configuration) => {
  let myCanvas = document##getElementById(id);
  let ctx = getContext(myCanvas, "2d");

  let mf = float_of_int(m);
  let nf = float_of_int(n);

  let w: float = myCanvas##width;
  let h: float = myCanvas##height;

  let wall_thickness = 0.05 *. max(w /. mf, h /. nf);
  let wall_length_h = (w -. (mf +. 1.) *. wall_thickness) /. mf;
  let wall_length_v = (h -. (nf +. 1.) *. wall_thickness) /. nf;

  let draw_wall = (x, y, dir) => {
    let (xf, yf) = (float_of_int(x), float_of_int(y));
    let xmin = xf *. wall_length_h +. (xf +. 1.) *. wall_thickness;
    let ymin = yf *. wall_length_v +. (yf +. 1.) *. wall_thickness;

    switch (dir) {
    | Horizontal =>
      fillRect(
        ctx,
        xmin,
        ymin -. wall_thickness,
        wall_length_h,
        wall_thickness,
      )
    | Vertical =>
      fillRect(
        ctx,
        xmin -. wall_thickness,
        ymin,
        wall_thickness,
        wall_length_v,
      )
    };
  };

  for (idx in 0 to Array.length(configuration) - 1) {
    if (configuration[idx]) {
      let (dir, x, y) =
        switch (idx) {
        | i when i < (m - 1) * n => (
            Vertical,
            1 + idx / (m - 1),
            idx mod (m - 1),
          )
        | _ =>
          let idx_h = idx - (m - 1) * n;
          (Horizontal, idx_h / (n - 1), 1 + idx_h mod (n - 1));
        };
      draw_wall(x, y, dir);
    };
  };
};

[@react.component]
let make = (~m, ~n, ~configuration) => {
  let (dims, setDims) = React.useState(() => {m: 2, n: 2});
  let (conf, setConf) = React.useState(() => configuration);
  let conf_string = conf->string_of_bool_list;

  let style =
    ReactDOMRe.Style.make(~borderWidth="3px", ~borderStyle="solid", ());
  let sw = ReactDOMRe.Style.unsafeAddProp(style, "width", "550px");
  let swh =
    ReactDOMRe.Style.unsafeAddProp(
      sw,
      "height",
      string_of_int(550 * n / m) ++ "px",
    );

  React.useEffect0(() => {
    draw(
      m,
      n,
      "Maze_" ++ conf->string_of_bool_list,
      Array.of_list(configuration),
    )
    |> ignore;
    None;
  });
  <div>
    {React.string(
       "Maze"
       ++ string_of_int(m)
       ++ "x"
       ++ string_of_int(n)
       ++ ": "
       ++ conf_string,
     )}
    <br />
    <canvas id={"Maze_" ++ conf_string} className="MazeCanvas" style=swh />
  </div>;
};