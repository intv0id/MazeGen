open Generator

[@react.component]
let make = (~m, ~n) => {
  let maze_configurations = generate_tail(m, n);
  let conf_elements = Array.map(
    a =>  ReasonReact.element(Maze.make(m, n, a)), 
    Array.of_list(maze_configurations)
    );
  <div style={ReactDOMRe.Style.make(~textAlign="center", ())}>{ReactDOMRe.createElement(ReasonReact.fragment, conf_elements)}</div>;
};
