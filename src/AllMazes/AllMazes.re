open Generator;

[@react.component]
let make = (~m, ~n) => {
  let conf_elements = List.map(
    a => <Maze m=m n=n configuration=a />, 
    generate_tail(m, n));
  <div style={ReactDOMRe.Style.make(~textAlign="center", ())}>
    conf_elements->Array.of_list->React.array
  </div>;
};