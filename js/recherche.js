function validateForm() {
    //Récupérer les valeurs des champs
    let realisateur = document.getElementById("realisateur").value;
    let duree = document.getElementById("duree").value;

    //Définir les expressions régulières
    let realisateurRegex = /^[a-zA-Z]/;
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
        realisateurError.innerHTML = "Le réalisateur doit contenir uniquement des lettres";
    }

    if (isDureeValid || duree === "") {
        dureeError.innerHTML = "";
    } else {
        dureeError.innerHTML = "La duree doit être en minutes et uniquement composé de chiffres";
    }

    if (isRealisateurValid || realisateur === "" && isDureeValid || duree === "") {
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
findFic();
function printMovies(){


}