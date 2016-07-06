/*!
 * @author : Varun Vijaykumar <varun.vijaykumar@s2014.tu-chemnitz.de>
 * @file   : timeline.h
 * @date   : 15 June 2016
 * @brief  : Timeline Scheduling (Using the Maximum Flow approach <FORD FULKERSON>
 */

#ifndef timeline_h
#define timeline_h

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define DEBUG_ENABLED /*! < For controlling Debug switches .. comment out on Release build*/

/*!
 * @brief Structure to describe the task details received.
 */
typedef struct _task_details {
    int ID;           /*!< Identity of the Task */
    int periodicity;  /*!< Periodicity of the Task */
    int exec_time;    /*!< Execution Time of the Task */
    int deadline;     /*!< Deadline of the Task */
} task_details;

/*!
 * @brief Structure to describe the timeline Scheduling Analysis Output.
 */
typedef struct _cyclic_schedule {
    int ID;                /*!< Identity of the Task */
    int exec_time;         /*!< Execution Time of the Task */
    int periodicity;       /*!< Periodicity of the Task */
} cyclic_schedule;

typedef struct _schedulerReport {
    int jobNumber;       /*!< Job number of the particular task */
    task_details job;    /*!< Job details */
    int scheduledFrame; /*!< Task scheduled in the frame */
} schedulerReport;

int m_frameSize;    /*!< Minor Cycle for Scheduling */
int m_hyperPeriod;  /*!< Major Cycle for Scheduling */
int m_NumOftasks;   /*!< Number of tasks passed for scheduling */
int m_totalNumOfJobs; /*!< Number of jobs scheduled */

schedulerReport *schedule; /*!< Schedule generated job wise for Timeline scheduling */

/*!
 * @brief Time line Scheduling (Cyclic Scheduling)
 * @details Function to initiate the Timeline Scheduling
 *          the task sets passed and print out the results
 *          obtained.
 * @param taskDetails Taskset(s) received from the user.
 * @param major Major Cycle Value.
 * @param minor Minor Cycle Value.
 * @return Success of timeline Scheduling
 */
int timelineScheduling(task_details *taskDetails);

/*!
 * @brief Calculate the Minor cycles (Frame Size)
 * @details Function to calculate the minor cycle
 * @param taskDetails Taskset(s) received from the user.
 * @return Schedulability of Tasks
 */
void calculateMinorCycle(task_details *taskDetails);

/*!
 * @brief Calculate the Minor cycles (Frame Size)
 * @details Function to calculate the minor cycl
 * @param taskDetails Task set(s) received from the user.
 * @return Major Cycle calculated.
 */
int calculateMajorCycle(task_details *taskDetails);

/*!
 * @brief Calculate the processor utilisation of the current processor
 * @details Function to calculate the minor cycle
 * @param[in] taskDetails Task set(s) received from the user.
 * @return Major Cycle calculated.
 */
float calculateProcessorUtilisation(task_details *taskDetails);

/*!
 * @brief To process the scheduling by Maximum flow algorithm
 * @details Function will take the task details supplied and create a schedule.
 * @param taskDetails Task set(s) received from the user.
 * @return success or failure in creating a schedule
 */
int timelineScheduler(task_details *taskdetails, int frameSize);

/*!
 * @brief Calculate the GCD of two decimals
 * @details Function to calculate the GCD
 * @param First number for GCD calculation
 * @param Secomd number for GCD calculation
 * @return Calculated Greatest common Decimal
 */
int gcd (int x , int y);

#endif /* timeline_h */
