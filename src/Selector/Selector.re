type d = {m: int, n: int};

[@react.component]
let make = () => {
  let (dims, setDims) = React.useState(() => {m: 2, n: 2});

    <div>
        <div id="Selector">
            <div>
            <label>"m : "->React.string</label>
            <input type_="button" onClick={_event => setDims(dims => {...dims, m: dims.m - 1})} value="-"/>
            <label>dims.n->string_of_int->React.string</label>
            <input type_="button" onClick={_event => setDims(dims => {...dims, m: dims.m + 1})} value="+"/>
            </div>
            <div>
            <label>"n : "->React.string</label>
            <input type_="button" onClick={_event => setDims(dims => {...dims, n: dims.n - 1})} value="-"/>
            <label>dims.n->string_of_int->React.string</label>
            <input type_="button" onClick={_event => setDims(dims => {...dims, n: dims.n + 1})} value="+"/>
            </div>
        </div>
        <AllMazes m={dims.m} n={dims.n} />
    </div>

};