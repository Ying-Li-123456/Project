// (de)select all buttons
$(document).ready(function(){
    function allFadingoOut() {
        $("div.publications h3").fadeOut(); 
        $("div.publications div").fadeOut(); 
        for (let index = 0; index < counter[1].length; index++) {
            counter[1][index] = 0;
        }
    }

    function fadingIn(someone) {
        if(someone.is(":checked")){
            return false;
        }else{
            someone.prop("checked", true);
            return true;
        }
    }

    $("button#deselect-year-all").click(function() {
        $('input[name="select_year"]').prop("checked" , false);
        allFadingoOut();
    });
        
    $("button#select-year-all").click(function() {
        $('input[name="select_year"]').filter(function () {
            return fadingIn($(this));
        }).change();
    });

    $("button#deselect-type-all").click(function() {       
        $('input[name="select_type"]').prop("checked" , false);
        allFadingoOut();
    });

    $("button#select-type-all").click(function() {
        $('input[name="select_type"]').filter(function () {
            return fadingIn($(this));
        }).change();
    });

    $("button#deselect-conference-all").click(function() {
        $('input[name="select_conference"]').filter(function () {
            if($(this).is(":checked")){
                $(this).prop("checked", false);
                return true;
            }else{
                return false;
            }
        }).change();
    });
    $("button#select-conference-all").click(function() {
        $('input[name="select_conference"]').filter(function () {
            if($(this).is(":checked")){
                return false;
            }else{
                $(this).prop("checked", true);
                return true;
            }
        }).change();
    });

    $("button#deselect-researcher-all").click(function() {
        $('input[name="select_researcher"]').prop("checked" , false);
        allFadingoOut();
    }); 

    $("button#select-researcher-all").click(function() {
        $('input[name="select_researcher"]').filter(function () {
            return fadingIn($(this));
        }).change();
    });

});

// jquery 内容添加分类类型
$(function() {
    $(".books").each(function(index, ele) {
        // $(this).prepend("<img src={{ url_for( 'static', filename='images/1.png' ) }} width='12' height='12' alt='books'/>");
        $(this).prepend("<img src='../../static/images/1.png' width='12' height='12' alt='books'/>");
    })
    $(".conf").each(function(index, ele) {
        $(this).prepend("<img src='../../static/images/2.png' width='12' height='12' alt='conferences'/>");
    })
    $(".journals").each(function(index, ele) {
        $(this).prepend("<img src='../../static/images/3.png' width='12' height='12' alt='journals'/>");
    })
    $(".phd").each(function(index, ele) {
        $(this).prepend("<img src='../../static/images/4.png' width='12' height='12' alt='phd thesis'/>");
    })
    $(".series").each(function(index, ele) {
        $(this).prepend("<img src='../../static/images/5.png' width='12' height='12' alt='series'/>");
    })
    $(".reference").each(function(index, ele) {
        $(this).prepend("<img src='../../static/images/6.png' width='12' height='12' alt='reference'/>");
    })
});

// initialise the counter
var counter = new Array();
counter[0] = new Array();
counter[1] = new Array();
counter[2] = new Array();
$(function(){
    $("h1.info_head").each(function () {
        counter[0].push(this.id);
        counter[1].push(this.innerText);
        counter[2].push(this.innerText);
    });
    $("div.content ul li#year").children().last().text(function(i,origText){
        return origText.slice(0,-2);});
    $("div.content ul li#conference").children().last().text(function(i,origText){
        return origText.slice(0,-2);});
    $("div.content ul li#researcher").children().last().text(function(i,origText){
        return origText.slice(0,-2);});
});

// jQuary function, filters
$(function () {
    $("div.checkbox_content input").change(function(){
        console.log("Got in");
        var gotSth = false; //flag
        if($(this).is(":checked")){
            if(this.name == "select_year"){
                $("div."+this.value).filter(function(){
                    if (checkForYear(this)){
                        increment(this);
                        gotSth = true;
                        return true;
                    }
                    else {return false;}
                }).fadeIn();
                
            } else if (this.name == "select_type"){   
                $("div."+this.value).filter(function(){
                    if (checkForType(this)){
                        increment(this);
                        gotSth = true;
                        return true;
                    }
                    else {return false;}
                }).fadeIn();
               
            } else if (this.name == "select_conference"){      
                $("div."+this.value).filter(function(){
                    if (checkForConf(this)){
                        increment(this);
                        gotSth = true;
                        return true;
                    }
                    else {return false;}
                }).fadeIn();

             
            } else if (this.name == "select_researcher"){
                $("div."+this.value).filter(function(){
                    if (checkForRese(this)){
                        var classes = $(this).prop("class").trim().split(/\s/);
                        if (checkName(classes)!=1) {
                            return false;
                        }
                        increment(this);
                        gotSth = true;
                        return true;
                    }
                    else {return false;}
                }).fadeIn();
             
            } else { 
                console.log(this.name);
                console.log("an error on input detected.");
            }

        } 
        else {
            if(this.name == "select_year"){
                $("div."+this.value).filter(function(){
                    if (checkForYear(this)){
                        reduction(this);
                        gotSth = true;
                        return true;
                    }
                    else {return false;}
                }).fadeOut();
                
            } else if (this.name == "select_type"){
                $("div."+this.value).filter(function(){
                    if (checkForType(this)){
                        reduction(this);
                        gotSth = true;
                        return true;
                    }
                    else {return false;}
                }).fadeOut();
               
            } else if (this.name == "select_conference"){
                $("div."+this.value).filter(function(){
                    if (checkForConf(this)){
                        reduction(this);
                        gotSth = true;
                        return true;
                    }
                    else {return false;}
                }).fadeOut();
             
            } else if (this.name == "select_researcher"){
                $("div."+this.value).filter(function(){
                    if (checkForRese(this)){
                        var classes = $(this).prop("class").trim().split(/\s/);
                        if (checkName(classes)!=0) {
                            return false;
                        }
                        reduction(this);
                        gotSth = true;
                        return true;
                    }
                    else {return false;}
                }).fadeOut();
             
            } else { 
                console.log(this.name);
                console.log("an error on input detected.");
            }
        }

        $("div.publications h3").each(function(){
            if (counter[1][counter[0].lastIndexOf($(this).prop("id"))]==0)
                $(this).fadeOut();
            else
                $(this).fadeIn();
        });

        if(!gotSth){
            $('<div>').appendTo('body').addClass('alert alert-info').html('No Changes have been made due to the checked options.').show().delay(1500).fadeOut();
        }
    });

    // assist functions
    // check every other fields
    function checkForYear(aP) {
        var classes = $(aP).prop("class").trim().split(/\s/);
        if($("div#check-type-content input[value="+classes[1]+"]").is(":checked")){
            if(classes[2] == "None" || $("div#check-conference-content input[value="+classes[2]+"]").is(":checked")){
                if(checkName(classes)){
                    return true;
                }else { return false;}
            } else {return false;}
        } else {return false;}   
    }

    function checkForType(aP) {
        var classes = $(aP).prop("class").trim().split(/\s/);
        if($("div#check-year-content input[value="+classes[0]+"]").is(":checked")){
            if(classes[2] == "None" || $("div#check-conference-content input[value="+classes[2]+"]").is(":checked")){
                if(checkName(classes)){
                    return true;
                }else { return false;}
            } else {return false;}
        } else {return false;}
    }

    function checkForConf(aP) {
        var classes = $(aP).prop("class").trim().split(/\s/);
        if($("div#check-year-content input[value="+classes[0]+"]").is(":checked")){
            if($("div#check-type-content input[value="+classes[1]+"]").is(":checked")){
                if(checkName(classes)){
                    return true;
                }else { return false;}
            } else {return false;}
        } else {return false;}
    }

    function checkForRese(aP) {
        var classes = $(aP).prop("class").trim().split(/\s/);
        if($("div#check-year-content input[value="+classes[0]+"]").is(":checked")){
            if($("div#check-type-content input[value="+classes[1]+"]").is(":checked")){
                if(classes[2] == "None" ||  $("div#check-conference-content input[value="+classes[2]+"]").is(":checked")){
                    return true;
                }else { return false;}
            } else {return false;}
        } else {return false;}
    }

    function checkName(classes) {

        var checked = 0;
        for (let index = 3; index < classes.length; index++) {
            const aName = classes[index];
            if($("div#check-researcher-content input[value="+aName+"]").is(":checked")){++checked;}
        }
        return checked;
    }

    function increment(aP){
        if ($("div.publications").prop("id") == "year" )
        {
            if(counter[1][counter[0].lastIndexOf($(aP).prop("class").trim().split(/\s/)[0])] != counter[2][counter[0].lastIndexOf($(aP).prop("class").trim().split(/\s/)[0])])
                ++counter[1][counter[0].lastIndexOf($(aP).prop("class").trim().split(/\s/)[0])];
        }       
        else
        {
            if(counter[1][counter[0].lastIndexOf($(aP).prop("class").trim().split(/\s/)[1])] != counter[2][counter[0].lastIndexOf($(aP).prop("class").trim().split(/\s/)[1])])
            ++counter[1][counter[0].lastIndexOf($(aP).prop("class").trim().split(/\s/)[1])];
        }
            
    }

    function reduction(aP){
        if ($("div.publications").prop("id") == "year")
            --counter[1][counter[0].lastIndexOf($(aP).prop("class").trim().split(/\s/)[0])];
            
        else
            --counter[1][counter[0].lastIndexOf($(aP).prop("class").trim().split(/\s/)[1])];     
    }
});