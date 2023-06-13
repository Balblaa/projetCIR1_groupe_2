function research(event){
    event.preventDefault();
    //on récupère les éléments du formulaire
    let authorName=document.getElementById("realisateur").value;
    let dureeMovie=document.getElementById("duree").value;
    let nameMovie=document.getElementById("titre").value;
    let categorieMovie=document.getElementById("genre").value;
    //si quelque chose est rempli dans le formulaire
    if(authorName.length!==0){
        //on exécute la fonction de recherche avec le paramètre entrée.
        writeFile('research','searchByAuthor');
        printMovies();
    }
    if(dureeMovie.length!==0){
        writeFile('research','searchByTime');
        printMovies();
    }
    if(nameMovie.length!==0){
        writeFile('research','searchByTitle');
        printMovies();
    }
    if(categorieMovie.length!==0){
        writeFile('research','searchByType');
        printMovies();
    }
    if(authorName.length===0 && dureeMovie.length===0 && nameMovie.length===0 && categorieMovie.length===0 ){
        printMovies();
    }
}
// fonction qui permet d'écrire dans un fichier
function writeFile(id_form,func) {
    var element = document.createElement('a');

    let text1 = document.getElementById(id_form);
    let count = text1.elements.length;
    let textToSave = func;
    console.log(text1);
    for(let i = 0;i<count-2;i++){
        textToSave += ";" + text1[i].value;
    }

    element.setAttribute('href', 'data:text/plain;charset=utf-8,' + encodeURIComponent(textToSave));
    element.setAttribute('download', 'request.txt');

    element.style.display = 'none';
    document.body.appendChild(element);
    element.click();
    document.body.removeChild(element);

  //  text1.submit();
}

function validateForm() {
    //Récupérer les valeurs des champs
    let realisateur = document.getElementById("realisateur").value;
    let duree = document.getElementById("duree").value;
    let film = document.getElementById("titre").value;
    let categorie = document.getElementById("genre").value;

    //Définir les expressions régulières
    let realisateurRegex = /^[a-zA-Z \-\']+$/;
    let dureeRegex =/^[0-9]+$/;
    let filmRegex = /^[a-zA-Z \-\']+$/;
    let categorieRegex = /^[a-zA-Z \-\']+$/;

    //Tester les valeurs des champs avec les expressions régulières
    let isRealisateurValid = realisateurRegex.test(realisateur);
    let isDureeValid = dureeRegex.test(duree);
    let isFilmValid = filmRegex.test(film);
    let isCategorieValid = categorieRegex.test(categorie);
    //console.log(isRealisateurValid, isDureeValid, isMessageValid);
    //console.log(realisateur, duree, message);

    //Récupérer les éléments d'erreur
    let submitBtn = document.getElementById("submitBtn");
    let realisateurError = document.getElementById("realisateurError");
    let dureeError = document.getElementById("dureeError");
    let filmError = document.getElementById("titreError");
    let categorieError = document.getElementById("genreError");


    //Afficher les messages d'erreur 
    if (isRealisateurValid || realisateur === "") {
        realisateurError.innerHTML = "";
    } else {
        realisateurError.innerHTML = "Le réalisateur doit contenir uniquement des lettres et pas d'accents";
    }

    if (isDureeValid || duree === "") {
        dureeError.innerHTML = "";
    } else {
        dureeError.innerHTML = "La duree doit être en minutes et uniquement composé de chiffres";
    }
    if (isFilmValid || film === "") {
        filmError.innerHTML = "";
    } else {
        filmError.innerHTML = "Le film doit contenir uniquement des lettres et pas d'accents";
    }
    if (isCategorieValid || categorie === "") {
        categorieError.innerHTML = "";
    } else {
        categorieError.innerHTML = "Le genre doit contenir uniquement des lettres et pas d'accents";
    }

    if ((isRealisateurValid|| realisateur === "") && (isDureeValid|| duree === "") && (isFilmValid|| film === "") && (isCategorieValid|| categorie === "")) {
        submitBtn.disabled = false;
        submitBtn.classList.remove("btn-notvalid");
    } else {
        submitBtn.disabled = true;
        //Edit css for the button to be gray
        submitBtn.classList.add("btn-notvalid");
    }
}

// appeler la fonction validateForm à chaque fois qu'un champ est modifié
document.getElementById("realisateur").addEventListener("input", validateForm);
document.getElementById("duree").addEventListener("input", validateForm);
document.getElementById("titre").addEventListener("input", validateForm);
document.getElementById("genre").addEventListener("input", validateForm);

//Appeler la fonction validateForm au chargement de la page
validateForm();

// fonction qui permet de lire un fichier
function readFileByName(fileName){

    let xhr = new XMLHttpRequest();
    do {
        xhr.open("GET", fileName, false);
        xhr.send(null);

    }while(xhr.status === 404);

    // assumes status 200
    return xhr.responseText;
}

function readFile(){
    readFileByName("ready.txt");
    return readFileByName("results.txt");
}

//fonction pour insérer une nouvelle place pour une catégorie film
function insertCell(row, cellNumber, text){
    let cell = row.insertCell(cellNumber);
    cell.innerHTML = text;
}

//fonction pour insérer une nouvelle place pour un film
function insertRow(table, rowNumber){
    let row = table.insertRow(rowNumber);
    return row;
}

//fonction qui affiche les films dans un tableau
function printMovies(){
    // Lecture des films à partir d'une source externe en utilisant la fonction readFile()
    let movies = readFile();
    // Division des données des films en un tableau en utilisant le saut de ligne comme séparateur
    let moviesArray = movies.split("\n");
    //ajout d'un compteur
    let compteur = document.getElementById("compteur");
    let count = 0;
    // Récupération de la référence à l'élément de tableau HTML avec l'ID "moviesTable"
    let table = document.getElementById("moviesTable");
    // Parcours de chaque film dans le tableau moviesArray
    for(let i = 0; i < moviesArray.length - 1; i++){
        // Séparation des données du film en utilisant le point-virgule comme séparateur
        let movie = moviesArray[i].split(";");

        // Insertion d'une nouvelle ligne dans le tableau HTML
        let row = table.insertRow(i+1);
        
        // Insertion de deux cellules dans la nouvelle ligne pour afficher les données du film
        let cell1 = row.insertCell(0);
        let cell2 = row.insertCell(1);
        let cell3 = row.insertCell(2);
        let cell4 = row.insertCell(3);
        
        // Remplissage des cellules avec les données du film
        cell1.innerHTML = movie[0];
        cell2.innerHTML = movie[1];
        cell3.innerHTML = movie[2];
        cell4.innerHTML = movie[3];
        count++;    
    }
    //effacer le contenu du fichier results.txt et ready.txt
    writeFile("deleteFilmotheque", "results.txt");
    writeFile("deleteFilmotheque", "ready.txt");
    compteur.innerHTML = "Il y a " + count + " films affichés";

    return moviesArray;
}

function deleteFiles(){
    writeFile("delete", "stopprocess");
    return readFileByName("ready.txt");
}

function insererFilm(){
    let realisateur = document.getElementById("realisateur").value;
    let duree = document.getElementById("duree").value;
    let film = document.getElementById("titre").value;
    let categorie = document.getElementById("genre").value;
    let filmString = realisateur + ";" + duree + ";" + film + ";" + categorie + "\n";
    writeFile('filmString', "ready.txt");
    return filmString;
}