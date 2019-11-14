var svgns = "http://www.w3.org/2000/svg";
function max(a, b) {
    if (a > b) { return a; }
    else { return b; }
}
function replaceAt(string, index, character) {
    return string.substr(0, index) + character + string.substr(index + character.length);
}
function Afficher(dimension_n, dimension_m, labyrinthe, id) {
    if (labyrinthe != null && labyrinthe.length == dimension_n * (dimension_m - 1) + dimension_m * (dimension_n - 1)) {
        if (id == 0) {
            var main = document.getElementById('main');
            main.parentNode.removeChild(main);
            var newmain = document.createElement('div');
            newmain.id = "main";
            document.getElementById('corps').appendChild(newmain);
        }

        var div = document.createElement('div');
        div.id = "box_" + id;
        div.setAttribute("class", "box");
        if (id != 0) {
            div.onclick = function () { Afficher(dimension_n, dimension_m, labyrinthe, 0) };
        }
        document.getElementById('main').appendChild(div);

        if (id == 0) {
            var title = document.createElement('h1');
            title.id = "title";
            title.innerHTML = "Labyrinthe " + dimension_n + "x" + dimension_m + "</br>";
            document.getElementById("box_" + id).appendChild(title);

            var text = document.createElement('p');
            text.id = "subtitle";
            text.innerHTML = labyrinthe;
            document.getElementById("box_" + id).appendChild(text);
        }

        var svg_container = document.createElementNS(svgns, 'svg');
        svg_container.setAttributeNS(null, 'id', 'svg_container_' + id);
        svg_container.setAttributeNS(null, 'width', dimension_n / max(dimension_m, dimension_n) * 100 + "%");
        svg_container.setAttributeNS(null, 'height', dimension_m / max(dimension_m, dimension_n) * 100 + "%");
        document.getElementById('box_' + id).appendChild(svg_container);

        var unite_case_n = 9 / 10 / dimension_n * 100;
        var unite_case_m = 9 / 10 / dimension_m * 100;
        var unite_mur_n = 1 / 10 / (dimension_n + 1) * 100;
        var unite_mur_m = 1 / 10 / (dimension_m + 1) * 100;

        for (x = 0; x < dimension_n; x++) {
            for (y = 0; y < dimension_m; y++) {
                var cell = document.createElementNS(svgns, 'rect');
                cell.setAttribute("class", "cellule");
                cell.setAttributeNS(null, 'x', x * unite_case_n + (x + 1) * unite_mur_n + "%");
                cell.setAttributeNS(null, 'y', y * unite_case_m + (y + 1) * unite_mur_m + "%");
                cell.setAttributeNS(null, 'height', unite_case_m + "%");
                cell.setAttributeNS(null, 'width', unite_case_n + "%");
                document.getElementById('svg_container_' + id).appendChild(cell);
            }
        }
        for (x = 0; x < dimension_n; x++) {
            var enceinte_haut = document.createElementNS(svgns, 'rect');
            enceinte_haut.setAttribute("class", "enceinte");
            enceinte_haut.setAttributeNS(null, 'x', x * unite_case_n + (x + 1) * unite_mur_n + "%");
            enceinte_haut.setAttributeNS(null, 'y', "0%");
            enceinte_haut.setAttributeNS(null, 'height', unite_mur_m + "%");
            enceinte_haut.setAttributeNS(null, 'width', unite_case_n + "%");
            document.getElementById('svg_container_' + id).appendChild(enceinte_haut);

            var enceinte_bas = document.createElementNS(svgns, 'rect');
            enceinte_bas.setAttribute("class", "enceinte");
            enceinte_bas.setAttributeNS(null, 'x', x * unite_case_n + (x + 1) * unite_mur_n + "%");
            enceinte_bas.setAttributeNS(null, 'y', 100 - unite_mur_m + "%");
            enceinte_bas.setAttributeNS(null, 'height', unite_mur_m + "%");
            enceinte_bas.setAttributeNS(null, 'width', unite_case_n + "%");
            document.getElementById('svg_container_' + id).appendChild(enceinte_bas);
        }
        for (y = 0; y < dimension_m; y++) {
            var enceinte_gauche = document.createElementNS(svgns, 'rect');
            enceinte_gauche.setAttribute("class", "enceinte");
            enceinte_gauche.setAttributeNS(null, 'x', "0%");
            enceinte_gauche.setAttributeNS(null, 'y', y * unite_case_m + (y + 1) * unite_mur_m + "%");
            enceinte_gauche.setAttributeNS(null, 'height', unite_case_m + "%");
            enceinte_gauche.setAttributeNS(null, 'width', unite_mur_n + "%");
            document.getElementById('svg_container_' + id).appendChild(enceinte_gauche);

            var enceinte_droite = document.createElementNS(svgns, 'rect');
            enceinte_droite.setAttribute("class", "enceinte");
            enceinte_droite.setAttributeNS(null, 'x', 100 - unite_mur_n + "%");
            enceinte_droite.setAttributeNS(null, 'y', y * unite_case_m + (y + 1) * unite_mur_m + "%");
            enceinte_droite.setAttributeNS(null, 'height', unite_case_m + "%");
            enceinte_droite.setAttributeNS(null, 'width', unite_mur_n + "%");
            document.getElementById('svg_container_' + id).appendChild(enceinte_droite);
        }
        for (x = 0; x < dimension_n + 1; x++) {
            for (y = 0; y < dimension_m + 1; y++) {
                var jonction = document.createElementNS(svgns, 'rect');
                if (x == 0 || y == 0 || x == dimension_n || y == dimension_m) {
                    jonction.setAttribute("class", "enceinte");
                }
                else {
                    jonction.setAttribute("class", "mur_plein");
                }
                jonction.setAttributeNS(null, 'x', x * unite_case_n + x * unite_mur_n + "%");
                jonction.setAttributeNS(null, 'y', y * unite_case_m + y * unite_mur_m + "%");
                jonction.setAttributeNS(null, 'height', unite_mur_m + "%");
                jonction.setAttributeNS(null, 'width', unite_mur_n + "%");
                document.getElementById('svg_container_' + id).appendChild(jonction);
            }
        }
        var index = 0;
        for (x = 0; x < dimension_n; x++) {
            for (y = 0; y < dimension_m; y++) {
                if (y < dimension_m - 1) {
                    var mur_horizontal = document.createElementNS(svgns, 'rect');
                    if (labyrinthe.charAt(index) == "0") {
                        mur_horizontal.setAttribute("class", "mur_vide");
                    }
                    else {
                        mur_horizontal.setAttribute("class", "mur_plein");
                    }
                    mur_horizontal.setAttributeNS(null, 'x', x * unite_case_n + (x + 1) * unite_mur_n + "%");
                    mur_horizontal.setAttributeNS(null, 'y', (y + 1) * unite_case_m + (y + 1) * unite_mur_m + "%");
                    mur_horizontal.setAttributeNS(null, 'height', unite_mur_m + "%");
                    mur_horizontal.setAttributeNS(null, 'width', unite_case_n + "%");
                    document.getElementById('svg_container_' + id).appendChild(mur_horizontal);
                    index++;
                }
                if (x < dimension_n - 1) {
                    var mur_vertical = document.createElementNS(svgns, 'rect');
                    if (labyrinthe.charAt(index) == "0") {
                        mur_vertical.setAttribute("class", "mur_vide");
                    }
                    else {
                        mur_vertical.setAttribute("class", "mur_plein");
                    }
                    mur_vertical.setAttributeNS(null, 'x', (x + 1) * unite_case_n + (x + 1) * unite_mur_n + "%");
                    mur_vertical.setAttributeNS(null, 'y', y * unite_case_m + (y + 1) * unite_mur_m + "%");
                    mur_vertical.setAttributeNS(null, 'height', unite_case_m + "%");
                    mur_vertical.setAttributeNS(null, 'width', unite_mur_n + "%");
                    document.getElementById('svg_container_' + id).appendChild(mur_vertical);
                    index++;
                }
            }
        }
    }
}
function init() {
    var abscisse = document.getElementById('input_n').value;
    var ordonnee = document.getElementById('input_m').value;
    if (parseInt(abscisse) > 1 && parseInt(ordonnee) > 1) {
        var main = document.getElementById('main');
        main.parentNode.removeChild(main);
        var newmain = document.createElement('div');
        newmain.id = "main";
        document.getElementById('corps').appendChild(newmain);
        rechercher(parseInt(abscisse), parseInt(ordonnee));
    }
}
function rechercher(n, m) {
    var GAUCHE = "0";
    var DROITE = "1";
    var HAUT = "2";
    var BAS = "3";
    var COMPTE = "4";
    var PASSAGE = "0";
    var MUR = "1";
    var ENCEINTE = "2";
    var NON = "0";
    var OUI = "1";

    var murs = (n - 1) * (m - 1);
    var murs_potentiels = n * (m - 1) + m * (n - 1);
    var nb_cases = n * m;

    var labyrinthe = "";
    var index = [];

    var compteur_connexes = 0;

    var indexconstruction = 0;
    //On initialise l'index :
    for (var x = 0; x < murs; x++) {
        index[x] = x;
    }

    for (var i = 0; index[0] <= murs_potentiels - murs; i++) {
        //ON CONSTRUIT
        //mise � z�ro du labyrinthe
        for (var x = 0; x < murs_potentiels; x++) {
            if (x == 0) {
                labyrinthe = PASSAGE + "";
            }
            else {
                labyrinthe = labyrinthe + PASSAGE + "";
            }
        }

        for (var ii = 0; ii < murs; ii++) {
            labyrinthe = replaceAt(labyrinthe, index[ii], MUR);
        }


        //On augmente l'index :

        index[murs - 1] += 1;

        //On fait la retenue
        for (var x = murs - 1; x >= 0; x--) {
            if (index[x] >= murs_potentiels - (murs - 1 - x)) {
                index[x - 1] += 1;
            }
        }

        //on enl�ve le surplus li� � la retenue
        for (var x = 1; x < murs; x++) {
            if (index[x] > murs_potentiels - (murs - x)) {
                index[x] = index[x - 1] + 1;
            }
        }

        //ON REND DESORMAIS INTELLIGIBLE

        indexconstruction = 0;
        var cases = new Array(x);
        for (var x = 0; x < n; x++) {
            cases[x] = new Array(y), 5
            for (var y = 0; y < m; y++) {
                cases[x][y] = new Array(5)
                //INITIALISATION DU TABLEAU
                cases[x][y][HAUT] = PASSAGE;
                cases[x][y][GAUCHE] = PASSAGE;
                cases[x][y][BAS] = PASSAGE;
                cases[x][y][DROITE] = PASSAGE;
                cases[x][y][COMPTE] = NON;
                //VERIFICATIONS (HAUT ET GAUCHE)
                if (y == 0) { cases[x][y][HAUT] = ENCEINTE; }
                else if (y > 0 && cases[x][y - 1][BAS] == MUR) { cases[x][y][HAUT] = MUR; } //on v�rifie le haut

                if (x == 0) { cases[x][y][GAUCHE] = ENCEINTE; }
                else if (x > 0 && cases[x - 1][y][DROITE] == MUR) { cases[x][y][GAUCHE] = MUR; }

                //EXPANSIONS (BAS ET DROITE)

                if (y == m - 1) { cases[x][y][BAS] = ENCEINTE; }
                else {
                    if (labyrinthe[indexconstruction] == MUR) {
                        cases[x][y][BAS] = MUR;
                    }
                    indexconstruction++;
                }


                if (x == n - 1) { cases[x][y][DROITE] = ENCEINTE; }
                else {
                    if (labyrinthe[indexconstruction] == MUR) {
                        cases[x][y][DROITE] = MUR;
                    }
                    indexconstruction++;
                }
            }
        }



        //ON ANALYSE DESORMAIS
        var cases_ok = 1;
        var compteur_boucle = 0;
        cases[0][0][COMPTE] = OUI;

        while (cases_ok < nb_cases && compteur_boucle < nb_cases) {
            for (var x = 0; x < n; x++) {
                for (var y = 0; y < m; y++) {
                    if (cases[x][y][COMPTE] == NON) {
                        if ((cases[x][y][HAUT] == PASSAGE && typeof cases[x][y - 1] != "undefined" && cases[x][y - 1][COMPTE] == OUI)
                            || (cases[x][y][BAS] == PASSAGE && typeof cases[x][y + 1] != "undefined" && cases[x][y + 1][COMPTE] == OUI)
                            || (cases[x][y][GAUCHE] == PASSAGE && typeof cases[x - 1] != "undefined" && cases[x - 1][y][COMPTE] == OUI)
                            || (cases[x][y][DROITE] == PASSAGE && typeof cases[x + 1] != "undefined" && cases[x + 1][y][COMPTE] == OUI)) {
                            cases[x][y][COMPTE] = OUI;
                            cases_ok++;
                        }
                    }
                }
            }
            compteur_boucle++;
        }


        if (cases_ok == nb_cases) {
            compteur_connexes++;
            Afficher(n, m, labyrinthe, compteur_connexes)
        }
    }
}
