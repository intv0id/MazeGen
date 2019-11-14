open Utils

type context;
type canvas;

[@bs.val] external document: Js.t({..}) = "document";
[@bs.send] external getContext: (canvas, string) => context = "getContext";
[@bs.send]

external fillRect: (context, float, float, float, float) => unit = "fillRect";

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