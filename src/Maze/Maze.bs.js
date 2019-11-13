'use strict';

var React = require("react");
var Caml_array = require("bs-platform/lib/js/caml_array.js");
var Caml_int32 = require("bs-platform/lib/js/caml_int32.js");

function digit_of_bool(a) {
  if (a) {
    return "1";
  } else {
    return "0";
  }
}

function string_of_bool_list(param) {
  var _acc = "";
  var _bl = param;
  while(true) {
    var bl = _bl;
    var acc = _acc;
    if (bl) {
      _bl = bl[1];
      _acc = acc + (
        bl[0] ? "1" : "0"
      );
      continue ;
    } else {
      return acc;
    }
  };
}

function Maze(Props) {
  var m = Props.m;
  var n = Props.n;
  var configuration = Props.configuration;
  var conf_string = string_of_bool_list(configuration);
  return React.createElement("div", undefined, "Maze" + (String(m) + ("x" + (String(n) + (": " + conf_string)))), React.createElement("br", undefined), React.createElement("canvas", {
                  className: "MazeCanvas",
                  id: "Maze_" + conf_string,
                  height: "100",
                  width: "200"
                }));
}

function draw(m, n, id, configuration) {
  var myCanvas = document.getElementById(id);
  var ctx = myCanvas.getContext("2d");
  var mf = m;
  var nf = n;
  var wall_length_h = (100.0 - (mf + 1) * 1.0) / mf;
  var wall_length_v = (100.0 - (nf + 1) * 1.0) / nf;
  var draw_wall = function (x, y, dir) {
    var xf = x;
    var yf = y;
    var xmin = xf * wall_length_h + (xf + 1) * 1.0;
    var ymin = yf * wall_length_v + (yf + 1) * 1.0;
    var xmax = xmin + wall_length_h;
    var ymax = ymin + wall_length_v;
    if (dir) {
      ctx.fillRect(xmin, ymin, xmax, ymin);
      return /* () */0;
    } else {
      ctx.fillRect(xmin, ymin, xmin, ymax);
      return /* () */0;
    }
  };
  for(var idx = 0 ,idx_finish = configuration.length - 1 | 0; idx <= idx_finish; ++idx){
    if (Caml_array.caml_array_get(configuration, idx)) {
      var match;
      if (idx < Caml_int32.imul(m - 2 | 0, n - 2 | 0)) {
        match = /* tuple */[
          /* Vertical */0,
          Caml_int32.mod_(idx, m - 2 | 0),
          Caml_int32.div(idx, m - 2 | 0)
        ];
      } else {
        var idx_h = idx - Caml_int32.imul(m - 2 | 0, n - 2 | 0) | 0;
        match = /* tuple */[
          /* Horizontal */1,
          Caml_int32.div(idx_h, n - 2 | 0),
          Caml_int32.mod_(idx, n - 2 | 0)
        ];
      }
      draw_wall(match[1], match[2], match[0]);
    }
    
  }
  return /* () */0;
}

var make = Maze;

exports.digit_of_bool = digit_of_bool;
exports.string_of_bool_list = string_of_bool_list;
exports.make = make;
exports.draw = draw;
/* react Not a pure module */
