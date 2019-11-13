type direction = Vertical | Horizontal;
type context;
type canvas;

[@bs.val] external document: Js.t({..}) = "document";
[@bs.send] external getContext : (canvas, string) => context = "getContext";
[@bs.send] external fillRect : (context, float, float, float, float) => unit = "fillRect";

let digit_of_bool(a) = switch a {
  | true => "1"
  | false => "0"
};

let string_of_bool_list = {
  let rec string_of_bool_list_tail = (acc, bl) => {
    switch (bl) {
    | [a, ...b] => string_of_bool_list_tail(acc ++ digit_of_bool(a), b)
    | [] => acc
    };
  };
  string_of_bool_list_tail("")
};

[@react.component]
let make = (~m, ~n, ~configuration) => {
  let conf_string = string_of_bool_list(configuration);
  <div> 
    {React.string("Maze" ++ string_of_int(m) ++ "x" ++ string_of_int(n) ++ ": " ++ conf_string)} 
    <br/> 
    <canvas id={"Maze_" ++ conf_string} className="MazeCanvas" width="200" height="100"></canvas>
  </div>;
};

let draw = (m, n, id, configuration) => {
  
  let myCanvas: canvas = document##getElementById(id);
  let ctx = getContext(myCanvas, "2d");

  let mf = float_of_int(m);
  let nf = float_of_int(n);

  let wall_thickness = 1.0;
  let wall_length_h = (100.0 -. (mf +. 1.) *. wall_thickness) /. mf;
  let wall_length_v = (100.0 -. (nf +. 1.) *. wall_thickness) /. nf;

  let draw_wall = (x, y, dir) => {
    let (xf, yf) = (float_of_int(x), float_of_int(y))
    let xmin = xf *. wall_length_h +. (xf +. 1.) *. wall_thickness;
    let ymin = yf *. wall_length_v +. (yf +. 1.) *. wall_thickness;
    let xmax = xmin +. wall_length_h;
    let ymax = ymin +. wall_length_v;

    switch (dir) {
      | Horizontal  => fillRect(ctx, xmin, ymin, xmax, ymin)
      | Vertical    => fillRect(ctx, xmin, ymin, xmin, ymax)
    };
  }

  for(idx in 0 to Array.length(configuration)-1) {
    if (configuration[idx]) {
      let (dir, x, y) = switch (idx) {
        | a when a < (m-2) * (n-2) => (Vertical, idx mod (m-2), idx / (m-2))
        | _ => {
          let idx_h = idx - (m-2) * (n-2); 
          (Horizontal, idx_h/(n-2), idx mod (n-2))
          }
      };
      draw_wall(x, y, dir);
    }    
  };
  
};
