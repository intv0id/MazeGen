open Iterator;
open Utils;

[@react.component]
let make = (~m, ~n) => {
  let conf_elements =
    List.map(
      a => <Maze m n configuration=a key={a->string_of_bool_list} />,
      generate(m, n),
    );
  <div style={ReactDOMRe.Style.make(~textAlign="center", ())}>
    {conf_elements->Array.of_list->React.array}
  </div>;
};