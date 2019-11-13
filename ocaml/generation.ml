type ordinals = Left | Right | Up | Down;; 

let concat x y = x::y ;;

let rec map f l = match l with
    | [] -> []
    | a::b -> f(a)::(map f b)
;;

let rec filter f l = match l with
    | [] -> []
    | a::b -> if f a then a::filter f b else filter f b
;;

let rec combinations k m = match k, m with
    | k, m when k < 0 || m < 0 -> failwith "ki or mi negative"
    | k, m when k > m -> failwith "k > m"
    | 0, 0 -> [[]]
    | 0, m -> map (concat false) (combinations 0 (m-1))
    | k, m when k = m -> map (concat true) (combinations (k-1) (m-1))
    | k, m -> map (concat true) (combinations (k-1) (m-1)) @ map (concat false) (combinations k (m-1))
;;

let rec passage configuration m n x y ord = match ord, x, y with
    | Left, 0, _                    -> false
    | Up, _, 0                      -> false
    | Right, a, _ when a = (m-1)    -> false
    | Down, _, b when b = (n-1)     -> false

    | Right, _, _   -> passage configuration m n (x+1) y Left
    | Down, _, _    -> passage configuration m n x (y+1) Up

    | Left, _, _    -> configuration.(y*(m-2) + x)
    | Up, _, _      -> configuration.((m-2) * (n-2) + x*(n-2) + y)
;;

let sanity_check m n configuration = 
    let maze = Array.make_matrix m n false
    in
    let counter = ref 0
    in
    let rec search x y = if maze.(x).(y) = false then 
        (
            maze.(x).(y) <- true;
            counter.contents <- counter.contents + 1 ;
            if passage configuration m n x y Left   then search (x-1) y ;
            if passage configuration m n x y Right  then search (x+1) y ;
            if passage configuration m n x y Up     then search x (y-1) ;
            if passage configuration m n x y Down   then search x (y+1) ;
        )
    in
    search 0 0;
    counter.contents = m*n
;;

let generate m n = 
    let c = combinations ((m-1) * (n-1)) (m*(n-1)+n*(m-1))
    in
    let c_array = map Array.of_list c
    in 
    filter (sanity_check m n) c_array
;;


generate 2 3 ;;







