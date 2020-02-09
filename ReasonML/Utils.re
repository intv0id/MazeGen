type direction =
  | Vertical
  | Horizontal;

let digit_of_bool = a => a ? "1" : "0";

let string_of_bool_list = {
  let rec string_of_bool_list_tail = (acc, bl) => {
    switch (bl) {
    | [a, ...b] => string_of_bool_list_tail(acc ++ digit_of_bool(a), b)
    | [] => acc
    };
  };
  string_of_bool_list_tail("");
};