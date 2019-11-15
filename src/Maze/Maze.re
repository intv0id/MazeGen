open Utils;
open CanvasDrawing;

type d = {
  m: int,
  n: int,
};

[@react.component]
let make = (~m, ~n, ~configuration) => {
  let conf_string = configuration->string_of_bool_list;

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
      "Maze_" ++ configuration->string_of_bool_list,
      Array.of_list(configuration),
    )
    |> ignore;
    None;
  });
  <div>
    <canvas id={"Maze_" ++ conf_string} className="MazeCanvas" style=swh />
  </div>;
};