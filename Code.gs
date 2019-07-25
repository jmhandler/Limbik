function onEdit() 
{
   var ss = SpreadsheetApp.getActiveSpreadsheet();
   var sheet = ss.getActiveSheet();
   var sheetName = sheet.getName();
   var cell = sheet.getActiveCell();
   
   if (sheetName == "Patients" && cell.getValue() == true && !sheet.getRange("C4").isBlank())
   {   
       var docSheet = ss.getSheetByName("Doctors");
       var queueNum = sheet.getRange("B4").getValue();
       var totalQueued = docSheet.getRange("A5").getValue();
       var row = totalQueued + 7;
       var qNumRange = "A" + row; 
       cell.setValue(false);
       if (totalQueued == 99)
       {
           ss.toast("ERROR: too many on the queue");
       }
       else 
       {
         docSheet.getRange(qNumRange).setValue(queueNum);
         docSheet.getRange("A5").setValue(totalQueued + 1);
         if (queueNum == 99)
         {
             sheet.getRange("B4").setValue(1);
         }
         else
         {
             sheet.getRange("B4").setValue(queueNum + 1);
         }
       
         cutPaste(4, row, "Patients", "Doctors", "C", "D", "B", "C");
       
         var today = new Date();
         var time = today.getHours() + ":" + today.getMinutes() + ":" + today.getSeconds();
         var timeRange = "D" + row; 
         docSheet.getRange(timeRange).setValue(time);
       }
       
       
   
   }
   if (sheetName == "Doctors" && sheet.getRange("I3").getValue() == true)
   {
       var today = new Date();
       var time = today.getHours() + ":" + today.getMinutes() + ":" + today.getSeconds();

       if (sheet.getRange("A5").getValue() > 0)
       {
           sheet.getRange("A5").setValue(sheet.getRange("A5").getValue() - 1);
       }
       if (!sheet.getRange("A3").isBlank())
       {
           var dbSheet = ss.getSheetByName("DB");
           var dbIndex = dbSheet.getRange("A2").getValue() + 2;
           dbSheet.getRange("A2").setValue(dbSheet.getRange("A2").getValue() + 1);
           cutPaste(3, dbIndex, "Doctors", "DB", "A", "D", "B", "E");
           var checkinTimeRange = "D" + dbIndex; 
           var startTimeRange = "E" + dbIndex; 
           var endTimeRange = "F" + dbIndex; 
           dbSheet.getRange(endTimeRange).setValue(time);
          
           var cost = costCalc(dbSheet.getRange(checkinTimeRange).getValue(), dbSheet.getRange(startTimeRange).getValue(), dbSheet.getRange(endTimeRange).getValue());
           var costRange = "G" + dbIndex;
           dbSheet.getRange(costRange).setValue(cost);
       }
       
       sheet.getRange("I3").setValue(false);
       cutPaste(7, 3, "Doctors", "Doctors", "B", "D", "A", "C");
       sheet.getRange("D3").setValue(time);
       sheet.deleteRow(7);

   }

  
}

function costCalc(checkin, start, end)
{
    var checkin_to_start = (start - checkin);
    var start_to_end = (end - start);
    var cost;            

    if (start_to_end < 900000)
    {
        cost = 30;
    }
    else if (start_to_end > 2700000)
    {
        cost = 60;
    }
    else
    {
        cost = 45;
    }
    
    if (checkin_to_start > 1800000)
    {
        cost = cost * 0.8;
    }
    
    return cost;
}

//Range1/Range2 in form --> "A7:F7"
function rowToRange(row, col1, col2)
{
    var range = col1 + row + ":" + col2 + row;
    return range;
}
// col is a letter, not number
function cutPaste(row1, row2, sheet1, sheet2, colA1, colA2, colB1, colB2) 
{
     var range1 = rowToRange(row1, colA1, colA2);
     var range2 = rowToRange(row2, colB1, colB2);
     
     var ss = SpreadsheetApp.getActiveSpreadsheet();
     var sheetStart = ss.getSheetByName(sheet1);
     var sheetEnd = ss.getSheetByName(sheet2);
     
     var copyRange = sheetStart.getRange(range1);
     var pasteRange = sheetEnd.getRange(range2);
     
     pasteRange.setValues(copyRange.getValues());
     copyRange.clear();
}
