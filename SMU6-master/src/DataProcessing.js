var departmentIndex = -1;
var locationIndex = -1;
var jobTitleIndex = -1;

var extraInforIndex = 8;
//return the array index of extra information
function extraInfor() {
  return extraInforIndex;
}

//return buliding name in an array
function getBuildingName() {
  var dataSheet = SpreadsheetApp.openById(spreadsheetId).getSheetByName(
    'BuildingStaffNumber'
  );
  var range = 'A3:B';
  var buildingName = [];
  var values = dataSheet.getRange(range).getValues();

  for (var i = 0; i < values.length; i++) {
    buildingName.push(values[i][0]);
  }

  buildingName = buildingName.filter(function (e) {
    return e;
  });
  buildingName.pop();
  Logger.log(buildingName);
  return buildingName;
}

//return the number of staff in each buliding
function getBuildingStaffNumber() {
  var dataSheet = SpreadsheetApp.openById(spreadsheetId).getSheetByName(
    'BuildingStaffNumber'
  );
  var buildingStaffNumber = [];
  var range = 'A3:C';
  var values = dataSheet.getRange(range).getValues();

  for (var i = 0; i < values.length; i++) {
    if (values[i][1] != '' && values[i][1] != null)
      buildingStaffNumber.push(values[i][1].toFixed(0));
  }
  buildingStaffNumber.pop();
  Logger.log(buildingStaffNumber);
  return buildingStaffNumber;
}

//return the number of teams/divisions in each building
function getBuildingDepartmentNumber() {
  var dataSheet = SpreadsheetApp.openById(spreadsheetId).getSheetByName(
    'BuildingStaffNumber'
  );
  var buildingDepartmentsNumber = [];
  var range = 'A3:C';
  var values = dataSheet.getRange(range).getValues();

  for (var i = 0; i < values.length; i++) {
    if (values[i][2] != '' && values[i][2] != null)
      buildingDepartmentsNumber.push(values[i][2].toFixed(0));
  }
  buildingDepartmentsNumber.pop();
  Logger.log(buildingDepartmentsNumber);
  return buildingDepartmentsNumber;
}

// return the team name in each building
function getBuildingDepartmentName() {
  var dataSheet = SpreadsheetApp.openById(spreadsheetId).getSheetByName(
    'BuildingDepartmentName'
  );
  var range = 'A4:B';
  var values = dataSheet.getRange(range).getValues();
  var buildingDepartmentName = new Array(3);

  for (var i = 0; i < buildingDepartmentName.length; i++) {
    buildingDepartmentName[i] = new Array(10);
  }

  for (var i = 0; i < values.length; i++) {
    if (values[i][0] == 'Building 1' && values[i][1] != null)
      buildingDepartmentName[0][i] = values[i][1];
    if (values[i][0] == 'Building 2' && values[i][1] != null)
      buildingDepartmentName[1][i] = values[i][1];
    if (values[i][0] == 'Building 3' && values[i][1] != null)
      buildingDepartmentName[2][i] = values[i][1];
  }

  for (var i = 0; i < buildingDepartmentName.length; i++) {
    buildingDepartmentName[i] = buildingDepartmentName[i].filter(function (e) {
      return e;
    });
  }

  Logger.log(buildingDepartmentName);
  return buildingDepartmentName;
}

// female & male ratio in each building
function getBuildingGenderRatio() {
  var dataSheet = SpreadsheetApp.openById(spreadsheetId).getSheetByName(
    'BuildingGender'
  );
  var buildingName = getBuildingName();
  var range = 'A4:E';
  var values = dataSheet.getRange(range).getValues();
  var MaleRatio = new Array(buildingName.length);

  for (var i = 0; i < buildingName.length; i++) {
    MaleRatio[i] = new Array(buildingName.length);
  }

  for (var i = 0; i < buildingName.length; i++) {
    MaleRatio[i][0] = buildingName[i];
    MaleRatio[i][1] = 'Male';
    MaleRatio[i][2] = (values[i][3] / values[i][4]).toFixed(3);
    MaleRatio[i][3] = 'Female';
    MaleRatio[i][4] = (values[i][2] / values[i][4]).toFixed(3);
    MaleRatio[i] = MaleRatio[i].filter(function (e) {
      return e;
    });
  }

  Logger.log(MaleRatio);
  return MaleRatio;
}

// return the staff name & employed time in each building
function getBuildingStaffEmployed() {
  var dataSheet = SpreadsheetApp.openById(spreadsheetId).getSheetByName(
    'BuildingNameEmployed'
  );
  var range = 'A4:C';
  var values = dataSheet.getRange(range).getValues();
  var buildingName = getBuildingName();
  let buildingStaffName = new Array();

  for (let i = 0; i < buildingName.length; i++) {
    buildingStaffName[i] = new Array();
    for (let j = 0; j < 136; j++) {
      buildingStaffName[i][j] = new Array(2);
    }
  }

  for (var j = 0; j < 136; j++) {
    if (values[j][0] == buildingName[0]) {
      buildingStaffName[0][j][0] = values[j][1];
      buildingStaffName[0][j][1] = values[j][2];
    }
    if (values[j][0] == buildingName[1]) {
      buildingStaffName[1][j][0] = values[j][1];
      buildingStaffName[1][j][1] = values[j][2];
    }
    if (values[j][0] == buildingName[2]) {
      buildingStaffName[2][j][0] = values[j][1];
      buildingStaffName[2][j][1] = values[j][2];
    }
  }

  buildingStaffName = removeEmpty(buildingStaffName);
  Logger.log(buildingStaffName);

  return buildingStaffName;
}

//return department name in an array
function getDepartmentName() {
  var dataSheet = SpreadsheetApp.openById(spreadsheetId).getSheetByName(
    'DepartmentGender'
  );
  var range = 'A3:B';
  var values = dataSheet.getRange(range).getValues();
  var departmentName = [];

  for (var i = 0; i < values.length; i++) {
    departmentName.push(values[i][0]);
  }

  departmentName = departmentName.filter(function (e) {
    return e;
  });
  departmentName.pop();
  Logger.log(departmentName);
  return departmentName;
}

// return the number of staff in each department
function getDepartmentStaffNumber() {
  var dataSheet = SpreadsheetApp.openById(spreadsheetId).getSheetByName(
    'DepartmentGender'
  );
  var departmentName = getDepartmentName();
  var range = 'A4:E';
  var values = dataSheet.getRange(range).getValues();
  var departmentStaffNumber = [];

  for (var i = 0; i < departmentName.length; i++) {
    departmentStaffNumber.push(values[i][4].toFixed(0));
  }
  Logger.log(departmentStaffNumber);
  return departmentStaffNumber;
}

// return the gender ratio in each department
function getDepartmentGenderRatio() {
  var dataSheet = SpreadsheetApp.openById(spreadsheetId).getSheetByName(
    'DepartmentGender'
  );
  var departmentName = getDepartmentName();
  var range = 'A4:E';
  var values = dataSheet.getRange(range).getValues();
  var departmentGenderRatio = new Array(departmentName.length);
  for (var i = 0; i < departmentName.length; i++) {
    departmentGenderRatio[i] = new Array(departmentName.length);
  }

  for (var i = 0; i < departmentName.length; i++) {
    departmentGenderRatio[i][0] = departmentName[i];
    departmentGenderRatio[i][1] = 'Male';
    departmentGenderRatio[i][2] = (values[i][3] / values[i][4]).toFixed(3);
    departmentGenderRatio[i][3] = 'Female';
    departmentGenderRatio[i][4] = (values[i][2] / values[i][4]).toFixed(3);
    departmentGenderRatio[i] = departmentGenderRatio[i].filter(function (e) {
      return e;
    });
  }

  Logger.log(departmentGenderRatio);
  return departmentGenderRatio;
}

// return staff name & employed time in each department
function getDepartmentStaffNameEmployed() {
  var dataSheet = SpreadsheetApp.openById(spreadsheetId).getSheetByName(
    'DepartmentStaffNameEmployed'
  );
  var range = 'A4:C';
  var values = dataSheet.getRange(range).getValues();
  var departmentName = getDepartmentName();

  //myArr: departmentStaffNameEmployed
  var myArr = new Array();
  for (let i = 0; i < 10; i++) {
    myArr[i] = new Array();
    for (let j = 0; j < 150; j++) {
      myArr[i][j] = new Array(2);
    }
  }

  for (var j = 0; j < 150; j++) {
    if (values[j][0] == departmentName[0]) {
      myArr[0][j][0] = values[j][1];
      myArr[0][j][1] = values[j][2];
    }
    if (values[j][0] == departmentName[1]) {
      myArr[1][j][0] = values[j][1];
      myArr[1][j][1] = values[j][2];
    }
    if (values[j][0] == departmentName[2]) {
      myArr[2][j][0] = values[j][1];
      myArr[2][j][1] = values[j][2];
    }
    if (values[j][0] == departmentName[3]) {
      myArr[3][j][0] = values[j][1];
      myArr[3][j][1] = values[j][2];
    }
    if (values[j][0] == departmentName[4]) {
      myArr[4][j][0] = values[j][1];
      myArr[4][j][1] = values[j][2];
    }
    if (values[j][0] == departmentName[5]) {
      myArr[5][j][0] = values[j][1];
      myArr[5][j][1] = values[j][2];
    }
    if (values[j][0] == departmentName[6]) {
      myArr[6][j][0] = values[j][1];
      myArr[6][j][1] = values[j][2];
    }
    if (values[j][0] == departmentName[7]) {
      myArr[7][j][0] = values[j][1];
      myArr[7][j][1] = values[j][2];
    }
    if (values[j][0] == departmentName[8]) {
      myArr[8][j][0] = values[j][1];
      myArr[8][j][1] = values[j][2];
    }
    if (values[j][0] == departmentName[9]) {
      myArr[9][j][0] = values[j][1];
      myArr[9][j][1] = values[j][2];
    }
  }
  myArr = removeEmpty(myArr);
  Logger.log(myArr);
  return myArr;
}

// delete the empty array elements
function removeEmpty(array) {
  var front = [];
  var back = [];

  for (var i = 0; i < array.length; i++) {
    for (var j = 0; j < array[i].length; j++) {
      if (array[i][j][0] != null) {
        front[i] = j;
        break;
      }
    }
  }

  for (var i = 0; i < array.length; i++) {
    array[i].splice(0, front[i]);
  }

  for (var i = 0; i < array.length; i++) {
    for (var j = array[i].length - 1; j >= 0; j--) {
      if (array[i][j][0] != null) {
        back[i] = j;
        break;
      }
    }
  }

  for (var i = 0; i < array.length; i++) {
    array[i].splice(back[i] + 1, array[i].length - back[i]);
  }
  return array;
}

//For demo use
function getFirstRowData() {
  // Read all the cells on the first row
  var range = 'A1:Z1';
  //get access to the first spread sheet
  var spreadSheet = SpreadsheetApp.openById(spreadsheetId).getSheets()[0];
  var values = spreadSheet.getRange(range).getValues();
  for (var i = values[0].length - 1; i >= 0; i--) {
    if (values[0][i] == '') values[0].pop();
    else if (values[0][i] == 'Department') departmentIndex = i;
    else if (values[0][i] == 'Office Location') locationIndex = i;
    else if (values[0][i] == 'Job Title') jobTitleIndex = i;
  }
  Logger.log(values);
  return values;
}

function departmentData() {
  getFirstRowData();
  //return specific column data--department data
  var workSheet = SpreadsheetApp.openById(spreadsheetId).getSheets()[0];
  var sheetData = washData(workSheet.getRange('A2:Z').getValues());
  var departmentData = [];
  for (var i = 0; i < sheetData.length; i++) {
    for (var j = 0; j < sheetData[i].length; j++) {
      if (j == departmentIndex && sheetData[i][j] != '')
        departmentData.push(sheetData[i][j]);
    }
  }

  //Added by Eric: Filter out the duplicate ones
  departmentData = departmentData.filter((val, index, self) => {
    return self.indexOf(val) === index;
  });

  return departmentData;
}

function locationData() {
  getFirstRowData();
  //return specific column data--office location data
  var workSheet = SpreadsheetApp.openById(spreadsheetId).getSheets()[0];
  var sheetData = washData(workSheet.getRange('A2:Z').getValues());
  var locationData = [];
  for (var i = 0; i < sheetData.length; i++) {
    for (var j = 0; j < sheetData[i].length; j++) {
      if (j == locationIndex && sheetData[i][j] != '')
        locationData.push(sheetData[i][j]);
    }
  }

  //Added by Eric: Filter out the duplicate ones
  locationData = locationData.filter((val, index, self) => {
    return self.indexOf(val) === index;
  });

  return locationData;
}

//Added by Eric: Find the unique job titles for searching
function jobTitleData() {
  getFirstRowData();
  //return specific column data--office location data
  var workSheet = SpreadsheetApp.openById(spreadsheetId).getSheets()[0];
  var sheetData = washData(workSheet.getRange('A2:Z').getValues());
  var jobTitleData = [];
  for (var i = 0; i < sheetData.length; i++) {
    for (var j = 0; j < sheetData[i].length; j++) {
      if (j == jobTitleIndex && sheetData[i][j] != '')
        jobTitleData.push(sheetData[i][j]);
    }
  }

  jobTitleData = jobTitleData.filter((val, index, self) => {
    return self.indexOf(val) === index;
  });

  return jobTitleData;
}

// clean the data following the request of the google api Creaded by Jin;
function washData(rawData) {
  var data = [];
  // shorten the data if necessary information is empty.
  for (var i = 0; i < rawData.length; i++) {
    var isEmpty = false;
    for (var j = 0; j < rawData[i].length; j++) {
      // if leading elements is null, the information is illeagle.
      if (j < 3 && rawData[i][j] == '') {
        // if Department is empty, it should be as same as the above one
        if (j == 0) rawData[i][j] = rawData[i - 1][j];
        else {
          isEmpty = true;
          break;
        }
      }
      //if the data is time;
      if (rawData[i][j] instanceof Date)
        rawData[i][j] = rawData[i][j].toString();
      //if the data is number
      if (Number.isInteger(rawData[i][j]))
        rawData[i][j] = rawData[i][j].toString();
      // other elements are optional
    }
    if (isEmpty) continue;
    else data.push(rawData[i]);
  }
  return data;
}

//reading the required data for chart
//Modified by Jin
function chartsData() {
  //get access to the spread sheet.
  var spreadSheet = SpreadsheetApp.openById(spreadsheetId).getSheets();
  //get the first worksheet. Would be Sheet1 in this demo.
  var workSheet = spreadSheet[0];
  var rawData = workSheet.getDataRange().getValues();
  var data = washData(rawData);
  Logger.log(data);
  return data;
}
