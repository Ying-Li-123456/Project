$(function() {
    // search type
    // $(".search-by").click(function() {
    //     var data = $(this).attr("data");
    //     if (data == "year") {
    //         $("#check-years-content").show();
    //         $("#check-type-content").hide();
    //         $("#dropdownMenu1").text("By Year")
    //         $("input[name=select_year]").each(function() {
    //             this.checked = true;
    //             $('div.' + this.value).fadeIn();
    //             $('p.' + this.value).fadeIn();
    //         });
    //         $("input[name=select_type]").each(function() {
    //             this.checked = true;
    //         });
    //         $("#deselect-year-all").html("deselect all");
    //     } else {
    //         $("#check-type-content").show();
    //         $("#check-years-content").hide();
    //         $("#dropdownMenu1").text("By Type")
    //         $("input[name=select_year]").each(function() {
    //             this.checked = true;
    //             $('div.' + this.value).fadeIn();
    //             $('p.' + this.value).fadeIn();
    //         });
    //         $("input[name=select_type]").each(function() {
    //             this.checked = true;
    //         });
    //         $("#deselect-type-all").html("deselect all");
    //     }
    // });

    // year change
    $("input[name='select_year']").change(
        function() {
            // console.log(this.value, $(this).attr("checked"));
            if ($(this).is(":checked")) {
                // console.log('div.' + this.value);
                $('p.' + this.value).fadeIn();
                // delete the animation 
                // $("html,body").animate({
                //     scrollTop: $('div.' + this.value).offset().top
                // }, 100);
            } else {
                $('p.' + this.value).fadeOut();
                // console.log('div.' + this.value);
            }
        }
    );
    // type change via js
    $("input[name='select_type']").change(function() {
        if ($(this).is(":checked")) {
            // console.log('div.' + this.value);
            $('p.' + this.value).fadeIn();
        } else {
            $('p.' + this.value).fadeOut();
            // console.log('div.' + this.value);
        }
    });
    $("input[name='select_conference']").change(function() {
        if ($(this).is(":checked")) {
            // console.log('div.' + this.value);
            $('p.' + this.value).fadeIn();
        } else {
            $('p.' + this.value).fadeOut();
            // console.log('div.' + this.value);
        }
    });
    $("input[name='select_researcher']").change(function() {
        if ($(this).is(":checked")) {
            // console.log('div.' + this.value);
            $('p.' + this.value).fadeIn();
        } else {
            $('p.' + this.value).fadeOut();
            // console.log('div.' + this.value);
        }
    });

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
    $(".article").each(function(index, ele) {
        $(this).prepend("<img src='./images/1.png' width='12' height='12' />");
    })
    $(".book").each(function(index, ele) {
        $(this).prepend("<img src='./images/2.png' width='12' height='12' />");
    })
    $(".incollection").each(function(index, ele) {
        $(this).prepend("<img src='./images/3.png' width='12' height='12' />");
    })
    $(".proceedings").each(function(index, ele) {
        $(this).prepend("<img src='./images/4.png' width='12' height='12' />");
    })
    $(".inproceedings").each(function(index, ele) {
        $(this).prepend("<img src='./images/5.png' width='12' height='12' />");
    })
    $(".phdthesis").each(function(index, ele) {
        $(this).prepend("<img src='./images/6.png' width='12' height='12' />");
    })
});