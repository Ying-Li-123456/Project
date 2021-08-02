//Object with items of page:loadingFunction
Route = {};
Route.path = function (page, loadingFunction) {
  Route[page] = loadingFunction;
};

function doGet(e) {
  //Creating pages
  Route.path('chart', loadChart);
  Route.path('report', loadReport);
  Route.path('search', loadSearch);
  Route.path('manual', loadManual);
  Route.path('manualSearch', loadManualSearch);
  Route.path('manualReport', loadManualReport);
  Route.path('manualChart', loadManualChart);

  //Url parameter v differentiate different pages
  if (Route[e.parameter.v]) {
    return Route[e.parameter.v]();
  } else {
    //If parameter is not found/valid, load chart

    //eric's original function
    return loadChart();
  }
}

//Added by Eric:
//!!!!!!!!--->this function is needed to modify when deployed to a different company<---!!!!!!!!!
function getUrlRoot() {
  return url_root;
  /*
  var url_root = ScriptApp.getService().getUrl();
  var re = /(.*script.google.com)(\/macros\/s\/.*)/;
  url_root = url_root.replace(re, '$1/a/student.adelaide.edu.au$2');
  return url_root;
  */
}

function include(filename) {
  return HtmlService.createHtmlOutputFromFile(filename).getContent();
}

/**************************************************************************
I checked it on google, it said that the HtmlService.createTemplateFromFile made the page be ran on server side, and can not be execute again once the page loaded. But the interface is designed for interacting with the user, it should be available for running on client side
*************************************************************************/
function render(page, argsObj) {
  var tmp = HtmlService.createTemplateFromFile(page);
  // If the args parameter is set
  if (argsObj) {
    var keys = Object.keys(argsObj);
    keys.forEach((key) => {
      tmp[key] = argsObj[key];
    });
  }
  return tmp.evaluate();
}

/***************function for generating chart****************/
function loadOrgChart() {
  return HtmlService.createTemplateFromFile('chart').evaluate();
}

// organization chart loading goes here..

function loadChart() {
  var url_root = getUrlRoot();
  return render('chart', { url: url_root });
}

// report generation loading goes here.

function loadReport() {
  var url_root = getUrlRoot();
  var department_list = departmentData();
  var location_list = locationData();
  return render('report', {
    url: url_root,
    department_checkbox: department_list,
    location_checkbox: location_list,
  });
}
function loadSearch() {
  var url_root = getUrlRoot();
  var department_list = departmentData();
  var location_list = locationData();
  var job_title_list = jobTitleData();
  return render('search', {
    url: url_root,
    department_list: department_list,
    location_list: location_list,
    job_title_list: job_title_list,
  });
}

function loadManual(){
  var url_root = getUrlRoot();
  return render("manualSetup", { url: url_root });
}

function loadManualSearch(){
  var url_root = getUrlRoot();
  return render("manualSearch", { url: url_root });
}

function loadManualReport(){
  var url_root = getUrlRoot();
  return render("manualReport", { url: url_root });
}

function loadManualChart(){
  var url_root = getUrlRoot();
  return render("manualChart", { url: url_root });
}

// for exporting report into google doc named "meptek_smu_report"
function exportAsPDF(htmlText) {
  var htmlText = `<h1>Maptek Staff Management Utility Report</h1>` + htmlText;
  htmlText = htmlText.replace('<h4>Report Content</h4>', '');

  htmlText = htmlText.replace(/<h5>/g, '<h2>');
  htmlText = htmlText.replace(/<\/h5>/g, '</h2>');
  htmlText = htmlText.replace(/<h6>/g, '<h3>');
  htmlText = htmlText.replace(/<\/h6>/g, '</h3>');
  htmlText = htmlText.replace(/<div class="row">/g, '');
  htmlText = htmlText.replace(/<div class="col-md-4">/g, '');
  htmlText = htmlText.replace(/<\/div>/g, '');
  htmlText = htmlText.replace(/<p id="writing_report">/g, '');
  
  var blob = HtmlService.createHtmlOutput(htmlText).getBlob();
  Drive.Files.insert({title: "maptek_smu_report", mimeType: MimeType.GOOGLE_DOCS}, blob);
}
