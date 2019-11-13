type state = {
  m: int,
  n: int,
};

type action =
  | DecrM
  | IncrM
  | DecrN
  | IncrN;

let component = ReasonReact.reducerComponent("Selector");

let make = () => {
  ...component,

  initialState: () => {m: 2, n: 2},

  reducer: (action, state) =>
    switch (action) {
    | IncrM => ReasonReact.Update({...state, m: state.m + 1 })
    | IncrN => ReasonReact.Update({...state, n: state.n + 1 })
    | DecrM => ReasonReact.Update({...state, m: max(state.m - 1, 2) })
    | DecrN => ReasonReact.Update({...state, n: max(state.n - 1, 2) })
    },

  render: self => {
    <div>
    <div id="Selector">
        <div>
        <label>{React.string("m : ")}</label>
        <input type_="button" onClick={_event => self.send(DecrM)} value="-"/>
        <label>{React.string(string_of_int(self.state.m))}</label>
        <input type_="button" onClick={_event => self.send(IncrM)} value="+"/>
        </div>
        <div>
        <label>{React.string("n : ")}</label>
        <input type_="button" onClick={_event => self.send(DecrN)} value="-"/>
        <label>{React.string(string_of_int(self.state.n))}</label>
        <input type_="button" onClick={_event => self.send(IncrN)} value="+"/>
        </div>
    </div>
    <AllMazes m={self.state.m} n={self.state.n} />
    </div>
  },
};