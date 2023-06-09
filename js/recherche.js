function research(){
    let authorName=document.getElementById("realisateur");
    let dureeMovie=document.getElementById("duree");
    if(authorName.length!==0){
        writeFile('research','readFileByName');
    }
    if(dureeMovie.length!==0){
        writeFile('formRequest','readFileByName');
    }
    if(authorName.length===0 && dureeMovie.length===0){
        writeFile('coucou','fonction qui affiche les films');
    }
}
// fonction qui permet d'écrire dans un fichier
function writeFile(id_form,func) {

    var element = document.createElement('a');

    let text1 = document.getElementById(id_form);
    let count = text1.elements.length;
    let textToSave = func;
    for(let i = 0;i<count-1;i++){
        textToSave += ";" + text1[i].value;
    }

    element.setAttribute('href', 'data:text/plain;charset=utf-8,' + encodeURIComponent(textToSave));
    element.setAttribute('download', 'request.txt');

    element.style.display = 'none';
    document.body.appendChild(element);
    element.click();
    document.body.removeChild(element);

    text1.submit();
}
function validateForm() {
    //Récupérer les valeurs des champs
    let realisateur = document.getElementById("realisateur").value;
    let duree = document.getElementById("duree").value;

    //Définir les expressions régulières
    let realisateurRegex = /^[a-zA-Z \-]+$/;
    let dureeRegex =/^[0-9]+$/;

    //Tester les valeurs des champs avec les expressions régulières
    let isRealisateurValid = realisateurRegex.test(realisateur);
    let isDureeValid = dureeRegex.test(duree);
    //console.log(isRealisateurValid, isDureeValid, isMessageValid);
    //console.log(realisateur, duree, message);

    //Récupérer les éléments d'erreur
    let submitBtn = document.getElementById("submitBtn");
    let realisateurError = document.getElementById("realisateurError");
    let dureeError = document.getElementById("dureeError");


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

    if ((isRealisateurValid|| realisateur === "") && (isDureeValid|| duree === "")) {
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

//fonction qui affiche les films dans un tableau
function printMovies(){
    // Lecture des films à partir d'une source externe en utilisant la fonction readFile()
    let movies = readFile();
    
    // Division des données des films en un tableau en utilisant le saut de ligne comme séparateur
    let moviesArray = movies.split("\n");
    
    // Récupération de la référence à l'élément de tableau HTML avec l'ID "moviesTable"
    let table = document.getElementById("moviesTable");
    
    // Parcours de chaque film dans le tableau moviesArray
    for(let i = 0; i < moviesArray.length; i++){
        // Séparation des données du film en utilisant le point-virgule comme séparateur
        let movie = moviesArray[i].split(";");
        
        // Insertion d'une nouvelle ligne dans le tableau HTML
        let row = table.insertRow(i+1);
        
        // Insertion de deux cellules dans la nouvelle ligne pour afficher les données du film
        let cell1 = row.insertCell(0);
        let cell2 = row.insertCell(1);
        
        // Remplissage des cellules avec les données du film
        cell1.innerHTML = movie[0];
        cell2.innerHTML = movie[1];
    }
}
