open Iterator;
open Utils;

type lastCombination =
  | LastOne
  | Running(option(list(bool)));

type mazesList = {
  mazes: list(React.element),
  configurations: list(list(bool)),
  last: lastCombination,
};

let chunk_size = 10;

let default_state = {mazes: [], configurations: [], last: Running(None)};

[@react.component]
let make = (~m, ~n) => {
  let (configurations, setConfigurations) =
    React.useState(() => default_state);

  let appendNextMazesChunk = _configurations => {
    switch (_configurations.last) {
    | LastOne => _configurations
    | Running(oldState) =>
      let nextChunk =
        generate_nb_combinations(
          m,
          n,
          chunk_size,
          ~start_combination=?oldState,
          (),
        );
      let (nextConfigurations, newState) =
        switch (nextChunk) {
        | Chunk([a, ...b]) => ([a, ...b], Running(Some(a)))
        | LastChunk(a) => (a, LastOne)
        | Chunk([]) =>
          failwith("This case should not happen : Chunk is empty")
        };
      let reactObjects =
        List.map(
          a => <Maze m n configuration=a key={a->string_of_bool_list} />,
          nextConfigurations,
        );
      {
        mazes: _configurations.mazes @ reactObjects,
        configurations: _configurations.configurations @ nextConfigurations,
        last: newState,
      };
    };
  };

  React.useEffect2(
    () => {
      setConfigurations(_ => appendNextMazesChunk(default_state));
      None;
    },
    (m, n),
  );

  <div style={ReactDOMRe.Style.make(~textAlign="center", ())}>
    {configurations.mazes->Array.of_list->React.array}
    <button
      type_="button"
      style={ReactDOMRe.Style.make(~margin="30px", ~padding="10px", ())}
      onClick={_event =>
        setConfigurations(oldConf => appendNextMazesChunk(oldConf))
      }>
      "Load more"->React.string
    </button>
  </div>;
};