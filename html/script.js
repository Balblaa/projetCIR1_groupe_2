function research(){
    let authorName=document.getElementById("realisateur");
    let dureeMovie=document.getElementById("duree");
    if(authorName.length!==0){
        writeFile('formrequest','dinero');
    }
    if(dureeMovie.length!==0){
        writeFile('formRequest','dinero');
    }
}
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

   // text1.submit();
}