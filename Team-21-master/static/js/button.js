function folder() {
    if($("a#folder").html() == "[Fold]")
    {
        
        fold();
        $("a#folder").html("[Expand]");
    } else{
        expend();
        $("a#folder").html("[Fold]")
    }   
}

function fold() {
    $("label#Sixth").nextAll("label").fadeOut();
}

function expend() {
    $("label#Sixth").nextAll("label").fadeIn();
}
