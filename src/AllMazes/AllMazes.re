open Generator

[@react.component]
let make = (~m, ~n) => {
  let maze_configurations = generate_tail(m, n);
  let conf_elements = Array.map(
    a => <Maze m=m n=n configuration=a />, 
    Array.of_list(maze_configurations)
    );
  <div>{ReactDOMRe.createElement(ReasonReact.fragment, conf_elements)}</div>;
};
