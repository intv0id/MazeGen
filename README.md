# ReasonReact Maze Generator

A few years ago, I had a [maths challenge](https://tfjm.org) for which a question of a given problem was to find all maze conformations such that:
* The maze is maze of m*n square cells.
* The cells can be separated by walls.
* The maze is surrounded by a wall.
* The maze is strictly connex (i.e. each couple of cells can be linked using a path that doesn't cross any wall)
* If we add a single wall, the maze is not connex anymore.

It can be shown that for a m*n cells conformation to be a maze, 

* there are (n-1)m +(m-1)n wall slots ;
* the number of walls has to be (n-1)(m-1) ;

Thus to find a maze we have to find all such conformations that respect the connex constraint.

The approach we use is the following one :

1. we generate ...
2. we filter ...

## Install

```sh
npm install --global bs-platform@6.2.1
```

## Build

```sh
npm install
bsb -make-world -clean-world
```

## Run

```sh
npm run server
# in a new tab
npm start
```

Open a new web page to `http://localhost:8000/`.


## Bundle for Production

```sh
npm install webpack webpack-cli
./node_modules/.bin/webpack
open indexProduction.html
```
