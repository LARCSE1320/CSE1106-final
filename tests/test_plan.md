# Testing plan
## Test 1:
  Have all temps within normal range
  Test Passed
  ### Temp: 68 Status: Normal LED: Off
  ### Temp: 70 Status: Normal LED: Off
  ### Temp: 76 Status: Normal LED: Off
## Test 2:
  Have 2 temps outside of normal range
  Test Passed
  ### Temp: 68 Status: Normal LED: Off
  ### Temp: 10 Status: Warning LED: Blinking
  ### Temp: 100 Status: Warning LED: Blinking
## Test 3:
  Change the temp range via the global variables and rerun tests 1 and 2 again with the new edited range (69 - 75).
  Tests Passed
  ## Test 1 retake:
  ### Temp: 68 Status: Normal LED: Off
  ### Temp: 70 Status: Normal LED: Off
  ### Temp: 75 Status: Normal LED: Off
  ## Test 2 retake:
  ### Temp: 11 Status: Warning LED: Blinking
  ### Temp: 70 Status: Normal LED: Off
  ### Temp: 200 Status: Warning LED: Blinking
