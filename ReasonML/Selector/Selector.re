type d = {
  m: int,
  n: int,
};

[@react.component]
let make = () => {
  let (dims, setDims) = React.useState(() => {m: 2, n: 2});

  let styleButtons =
    ReactDOMRe.Style.make(~width="40%", ~display="inline-block", ());
  let styleClicableButtons =
    ReactDOMRe.Style.make(~padding="20px", ~margin="20px", ~fontSize="1.5em", ~fontStyle="Bold", ());
  let styleForm =
    ReactDOMRe.Style.make(~textAlign="center", ~padding="50px", ());

  <div>
    <div id="Selector" style=styleForm>
      <div style=styleButtons>
        <label> "m : "->React.string </label>
        <button
          onClick={_event => setDims(dims => {...dims, m: dims.m - 1})}
          style=styleClicableButtons>
          "-"->React.string
        </button>
        <label> {dims.m->string_of_int->React.string} </label>
        <button
          onClick={_event => setDims(dims => {...dims, m: dims.m + 1})}
          style=styleClicableButtons>
          "+"->React.string
        </button>
      </div>
      <div style=styleButtons>
        <label> "n : "->React.string </label>
        <button
          onClick={_event => setDims(dims => {...dims, n: dims.n - 1})}
          style=styleClicableButtons>
          "-"->React.string
        </button>
        <label> {dims.n->string_of_int->React.string} </label>
        <button
          onClick={_event => setDims(dims => {...dims, n: dims.n + 1})}
          style=styleClicableButtons>
          "+"->React.string
        </button>
      </div>
    </div>
    <AllMazes m={dims.m} n={dims.n} />
  </div>;
};