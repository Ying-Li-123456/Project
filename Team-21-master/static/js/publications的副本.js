function checkForYear(aP, gotSth) {
    var classes = $(aP).prop("class").trim().split(/\s/);
    if($("div#check-type-content input[value="+classes[2]+"]").is(":checked")){
        if(classes.length==3 || $("div#check-conference-content input[value="+classes[3]+"]").is(":checked")){
            if($("div#check-researcher-content input[value="+classes[0]+"]").is(":checked")){
                gotSth = true;
                return true;
            }else { return false;}
        } else {return false;}
    } else {return false;}   
}

function checkForType(aP, gotSth) {
    var classes = $(aP).prop("class").trim().split(/\s/);
    if($("div#check-year-content input[value="+classes[1]+"]").is(":checked")){
        if(classes.length==3 || $("div#check-conference -content input[value="+classes[3]+"]").is(":checked")){
            if($("div#check-researcher-content input[value="+classes[0]+"]").is(":checked")){
                gotSth = true;
                return true;
            }else { return false;}
        } else {return false;}
    } else {return false;}
}

function checkForConf(aP, gotSth) {
    var classes = $(aP).prop("class").trim().split(/\s/);
    if($("div#check-year-content input[value="+classes[1]+"]").is(":checked")){
        if($("div#check-type-content input[value="+classes[2]+"]").is(":checked")){
            if($("div#check-researcher-content input[value="+classes[0]+"]").is(":checked")){
                gotSth = true;
                return true;
            }else { return false;}
        } else {return false;}
    } else {return false;}
}

function checkForRese(aP, gotSth) {
    var classes = $(aP).prop("class").trim().split(/\s/);
    if($("div#check-year-content input[value="+classes[1]+"]").is(":checked")){
        if($("div#check-type-content input[value="+classes[2]+"]").is(":checked")){
            if($(classes.length==3 || "div#check-conference-content input[value="+classes[3]+"]").is(":checked")){
                gotSth = true;
                return true;
            }else { return false;}
        } else {return false;}
    } else {return false;}
}

$(function () {

    $("input").change(function(){
        console.log("Got in");
        var gotSth = false; //flag
        if($(this).is(":checked")){
            if(this.name == "select_year"){
                $("p."+this.value).filter(function(){return checkForYear(this, gotSth);}).fadeIn();
                
            } else if (this.name == "select_type"){                
                $("p."+this.value).filter(function(){return checkForType(this, gotSth);}).fadeIn();
               
            } else if (this.name == "select_conference"){                    
                $("p."+this.value).filter(function(){return checkForConf(this, gotSth);}).fadeIn();
             
            } else if (this.name == "select_researcher"){
                $("p."+this.value).filter(function(){return checkForRese(this, gotSth);}).fadeIn();
             
            } else { 
                console.log(this.name);
                console.log("an error on input detected.");
            }

        } 
        else {
            $('p.' + this.value).fadeOut();
        }
    });

        // if (!gotSth) {
        //     // function showTips(tips, height, sizeWidth, time) {
        //         var windowWidth = document.documentElement.clientWidth;
        //         var tipsDiv = '<div class="tipsClass">No changes have been made, please check options you have unchecked.</div>';
            
        //         $('body').append(tipsDiv);
        //         $('div.tipsClass').css({
        //             'top': '200px',
        //             'right': 450+ 'px',
        //             'position': 'absolute',
        //             'padding': '3px 5px',
        //             'background': '#8FBC8F',
        //             'font-size': 12 + 'px',
        //             'margin': '0 auto',
        //             'text-align': 'center',
        //             'width': '20 px',
        //             'color': '#fff',
        //             'opacity': '0.8'
        //         }).show();
        //         setTimeout(function () { $('div.tipsClass').fadeOut(); }, (3 * 1000));
        // }
    // });

//     // year change
//     $("input[name='select_year']").change(
//         function() {
//             // console.log(this.value, $(this).attr("checked"));
//             if ($(this).is(":checked")) {
//                 // console.log('div.' + this.value);
//                 $('p.' + this.value).fadeIn();
//                 // delete the animation 
//                 // $("html,body").animate({
//                 //     scrollTop: $('div.' + this.value).offset().top
//                 // }, 100);
//             } else {
//                 $('p.' + this.value).fadeOut();
//                 // console.log('div.' + this.value);
//             }
//         }
//     );
//     // type change via js
//     $("input[name='select_type']").change(function() {
//         if ($(this).is(":checked")) {
//             // console.log('div.' + this.value);
//             $('p.' + this.value).fadeIn();
//         } else {
//             $('p.' + this.value).fadeOut();
//             // console.log('div.' + this.value);
//         }
//     });
//     $("input[name='select_conference']").change(function() {
//         if ($(this).is(":checked")) {
//             // console.log('div.' + this.value);
//             $('p.' + this.value).fadeIn();
//         } else {
//             $('p.' + this.value).fadeOut();
//             // console.log('div.' + this.value);
//         }
//     });
//     $("input[name='select_researcher']").change(function() {
//         if ($(this).is(":checked")) {
//             // console.log('div.' + this.value);
//             $('p.' + this.value).fadeIn();
//         } else {
//             $('p.' + this.value).fadeOut();
//             // console.log('div.' + this.value);
//         }
//     });

    $("#deselect-year-all").click(function() {
        $(":input[name='select_year']").each(function() {
            // $(this).attr("checked", false);
            $(this).trigger("change");
        })
    });

    $("#deselect-type-all").click(function() {
        $(":input[name='select_type']").each(function() {
            // $(this).attr("checked", false);
            $(this).trigger("change");
        })
    });
    $("#deselect-conference-all").click(function() {
        $(":input[name='select_conference']").each(function() {
            // $(this).attr("checked", false);
            $(this).trigger("change");
        })
    });
    $("#deselect-researcher-all").click(function() {
        $(":input[name='select_researcher']").each(function() {
            // $(this).attr("checked", false);
            $(this).trigger("change");
        })
    });
        
});

// jquery 内容添加分类类型
$(function() {
    $(".books").each(function(index, ele) {
        $(this).prepend("<img src='images/1.png' width='12' height='12' alt='books'/>");
    })
    $(".conf").each(function(index, ele) {
        $(this).prepend("<img src='images/2.png' width='12' height='12' alt='conferences'/>");
    })
    $(".journals").each(function(index, ele) {
        $(this).prepend("<img src='images/3.png' width='12' height='12' alt='journals'/>");
    })
    $(".phd").each(function(index, ele) {
        $(this).prepend("<img src='images/4.png' width='12' height='12' alt='phd thesis'/>");
    })
    $(".series").each(function(index, ele) {
        $(this).prepend("<img src='images/5.png' width='12' height='12' alt='series'/>");
    })
});