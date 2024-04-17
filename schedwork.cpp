#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool makeSchedule(
  size_t n_row, 
  size_t d_col, 
  const AvailabilityMatrix& avail, const size_t maxShifts, 
  DailySchedule& sched,
  map<Worker_T, int>& freqCounter
  );

// Add your implementation of schedule() and other helper functions here

// n - number of days to be worked
// k - all possible workers
// d - amount of workers needed per day
// m - maximum shifts workers can do 

bool schedule(
    const AvailabilityMatrix& avail, // n x k availability matrix
    const size_t dailyNeed, // d - amount of workers needed per day
    const size_t maxShifts, // m - maximum shifts worker can do
    DailySchedule& sched // n x d schedule that needs to be made
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    
    // Add your code below
    if (maxShifts == 0) {
      return false;
    } else if (dailyNeed == 0) {
      return true;
    }

    size_t n_days = avail.size();

    for (size_t i = 0; i < n_days; i++) {
      vector<Worker_T> day_sched(dailyNeed, INVALID_ID);
      sched.push_back(day_sched);
    }

    map<Worker_T, int> freqCounter; 
    
    return makeSchedule(0, 0, avail, maxShifts, sched, freqCounter);
}

bool makeSchedule(
  size_t n_row, 
  size_t d_col, 
  const AvailabilityMatrix& avail, const size_t maxShifts, 
  DailySchedule& sched,
  map<Worker_T, int>& freqCounter
  ) {
    
    // base condition
    if (n_row == avail.size()) {
      return true;
    }

    if (d_col == sched[0].size()) {
      return makeSchedule(n_row + 1, 0, avail, maxShifts, sched, freqCounter);
    }

    // recursive logic/condition
    for (int work_id = 0; work_id < avail[n_row].size(); work_id++) { // iterating through k workers
      // check if worker is available and hasn't worked more than maximum shifts
      if (avail[n_row][work_id] && freqCounter[work_id] < maxShifts) {
        sched[n_row][d_col] = work_id;
        freqCounter[work_id]++;

        // recursive call 
        if (makeSchedule(n_row, d_col + 1, avail, maxShifts, sched, freqCounter)) {
          return true;
        }

        // backtracking logic
        sched[n_row][d_col] = INVALID_ID;
        freqCounter[work_id]--;
      }
    }

    return false;
}
