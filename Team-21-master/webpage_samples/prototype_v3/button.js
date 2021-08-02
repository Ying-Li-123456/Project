var checkYears = document.querySelector('#check-years-content').querySelectorAll('input'),
    btnYears = document.querySelector('#deselect-year-all'),
    checkType = document.querySelector('#check-type-content').querySelectorAll('input'),
    btnType = document.querySelector('#deselect-type-all');
checkConference = document.querySelector('#check-conference-content').querySelectorAll('input'),
    btnConference = document.querySelector('#deselect-conference-all');
checkResearcher = document.querySelector('#check-researcher-content').querySelectorAll('input'),
    btnResearcher = document.querySelector('#deselect-researcher-all');

btnYears.addEventListener('click', function() {
    if (btnYears.innerHTML == 'deselect all') {
        for (var i = 0; i < checkYears.length; i++) {
            checkYears[i].checked = false;
        }
        btnYears.innerHTML = 'select all';
    } else {
        for (var i = 0; i < checkYears.length; i++) {
            checkYears[i].checked = true;
        }
        btnYears.innerHTML = 'deselect all';
    }
})

btnType.addEventListener('click', function() {
    if (btnType.innerHTML == 'deselect all') {
        for (var i = 0; i < checkType.length; i++) {
            checkType[i].checked = false;
        }
        btnType.innerHTML = 'select all';
        // flag2 = 1;
    } else {
        for (var i = 0; i < checkType.length; i++) {
            checkType[i].checked = true;
        }
        btnType.innerHTML = 'deselect all';
        // flag2 = 0;
    }
})

btnConference.addEventListener('click', function() {
    if (btnConference.innerHTML == 'deselect all') {
        for (var i = 0; i < checkConference.length; i++) {
            checkConference[i].checked = false;
        }
        btnConference.innerHTML = 'select all';
    } else {
        for (var i = 0; i < checkConference.length; i++) {
            checkConference[i].checked = true;
        }
        btnConference.innerHTML = 'deselect all';
    }
})

btnResearcher.addEventListener('click', function() {
    if (btnResearcher.innerHTML == 'deselect all') {
        for (var i = 0; i < checkResearcher.length; i++) {
            checkResearcher[i].checked = false;
        }
        btnResearcher.innerHTML = 'select all';
    } else {
        for (var i = 0; i < checkResearcher.length; i++) {
            checkResearcher[i].checked = true;
        }
        btnResearcher.innerHTML = 'deselect all';
    }
})