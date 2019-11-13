'use strict';

var $$Array = require("bs-platform/lib/js/array.js");
var React = require("react");
var Caml_splice_call = require("bs-platform/lib/js/caml_splice_call.js");
var Maze$ReasonReactExamples = require("../Maze/Maze.bs.js");
var Generator$ReasonReactExamples = require("../Generator/Generator.bs.js");

function AllMazes(Props) {
  var m = Props.m;
  var n = Props.n;
  var maze_configurations = Generator$ReasonReactExamples.generate_tail(m, n);
  var conf_elements = $$Array.map((function (a) {
          return React.createElement(Maze$ReasonReactExamples.make, {
                      m: m,
                      n: n,
                      configuration: a
                    });
        }), $$Array.of_list(maze_configurations));
  return React.createElement("div", undefined, Caml_splice_call.spliceApply(React.createElement, [
                  React.Fragment,
                  undefined,
                  conf_elements
                ]));
}

var make = AllMazes;

exports.make = make;
/* react Not a pure module */
