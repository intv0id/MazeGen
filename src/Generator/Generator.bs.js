'use strict';

var $$Array = require("bs-platform/lib/js/array.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Caml_array = require("bs-platform/lib/js/caml_array.js");
var Caml_int32 = require("bs-platform/lib/js/caml_int32.js");
var Pervasives = require("bs-platform/lib/js/pervasives.js");

function combinations_tail(f, _k, _m, _prefix) {
  while(true) {
    var prefix = _prefix;
    var m = _m;
    var k = _k;
    if (k < 0 || m < 0) {
      return Pervasives.failwith("ki or mi negative");
    } else if (k > m) {
      return Pervasives.failwith("k > m");
    } else if (k !== 0) {
      if (k === m) {
        _prefix = /* :: */[
          true,
          prefix
        ];
        _m = m - 1 | 0;
        _k = k - 1 | 0;
        continue ;
      } else {
        return Pervasives.$at(combinations_tail(f, k - 1 | 0, m - 1 | 0, /* :: */[
                        true,
                        prefix
                      ]), combinations_tail(f, k, m - 1 | 0, /* :: */[
                        false,
                        prefix
                      ]));
      }
    } else if (m !== 0) {
      _prefix = /* :: */[
        false,
        prefix
      ];
      _m = m - 1 | 0;
      _k = 0;
      continue ;
    } else if (Curry._1(f, $$Array.of_list(prefix))) {
      return /* :: */[
              prefix,
              /* [] */0
            ];
    } else {
      return /* [] */0;
    }
  };
}

function passage(configuration, m, n, _x, _y, _ord) {
  while(true) {
    var ord = _ord;
    var y = _y;
    var x = _x;
    switch (ord) {
      case /* Left */0 :
          if (x !== 0) {
            return Caml_array.caml_array_get(configuration, Caml_int32.imul(y, m - 2 | 0) + x | 0);
          } else {
            return false;
          }
      case /* Right */1 :
          if (x === (m - 1 | 0)) {
            return false;
          } else {
            _ord = /* Left */0;
            _x = x + 1 | 0;
            continue ;
          }
      case /* Up */2 :
          if (y !== 0) {
            return Caml_array.caml_array_get(configuration, (Caml_int32.imul(m - 2 | 0, n - 2 | 0) + Caml_int32.imul(x, n - 2 | 0) | 0) + y | 0);
          } else {
            return false;
          }
      case /* Down */3 :
          if (y === (n - 1 | 0)) {
            return false;
          } else {
            _ord = /* Up */2;
            _y = y + 1 | 0;
            continue ;
          }
      
    }
  };
}

function sanity_check(m, n, configuration) {
  var maze = $$Array.make_matrix(m, n, false);
  var counter = /* record */[/* contents */0];
  var search = function (x, _y) {
    while(true) {
      var y = _y;
      if (Caml_array.caml_array_get(Caml_array.caml_array_get(maze, x), y) === false) {
        Caml_array.caml_array_set(Caml_array.caml_array_get(maze, x), y, true);
        counter[/* contents */0] = counter[/* contents */0] + 1 | 0;
        if (passage(configuration, m, n, x, y, /* Left */0)) {
          search(x - 1 | 0, y);
        }
        if (passage(configuration, m, n, x, y, /* Right */1)) {
          search(x + 1 | 0, y);
        }
        if (passage(configuration, m, n, x, y, /* Up */2)) {
          search(x, y - 1 | 0);
        }
        if (passage(configuration, m, n, x, y, /* Down */3)) {
          _y = y + 1 | 0;
          continue ;
        } else {
          return 0;
        }
      } else {
        return 0;
      }
    };
  };
  search(0, 0);
  return counter[/* contents */0] === Caml_int32.imul(m, n);
}

function generate_tail(m, n) {
  return combinations_tail((function (param) {
                return sanity_check(m, n, param);
              }), Caml_int32.imul(m - 1 | 0, n - 1 | 0), Caml_int32.imul(m, n - 1 | 0) + Caml_int32.imul(n, m - 1 | 0) | 0, /* [] */0);
}

exports.combinations_tail = combinations_tail;
exports.passage = passage;
exports.sanity_check = sanity_check;
exports.generate_tail = generate_tail;
/* No side effect */
