/*!
 * @author : Varun Vijaykumar <varun.vijaykumar@s2014.tu-chemnitz.de>
 * @file   : timeline.c
 * @date   : 15 June 2016
 * @brief  : Timeline Scheduling (Using the Maximum Flow approach <FORD FULKERSON>
 */

#include "timeline.h"

int gcd (int x , int y)
{
    return (y == 0) ? x : gcd (y , x % y );
}

int timelineScheduler(task_details *taskdetails, int frameSize)
{
    schedulerReport pScheduledTasks[300];
    int numOfScheduledJobs = 0;

    int numberOfJobsPerTask[m_NumOftasks];

    // calculate number of jobs for each task
    for (int i = 0; i < m_NumOftasks; i++)
    {
        numberOfJobsPerTask[i] = m_hyperPeriod / taskdetails[i].periodicity;
    }

    // calculate the number of Frames in the hyperperiod
    int pFramesPerHyperPeriod = m_hyperPeriod / frameSize;
    
    // each task
    int remainingFrameTime[pFramesPerHyperPeriod];
    
    // set the whole array with framesize
    for (int frame = 0 ; frame < pFramesPerHyperPeriod; frame++)
    {
        remainingFrameTime[frame] = frameSize;
    }
    
    for (int task = 0 ; task < m_NumOftasks ; task++)
    {
        // each job per task
        for (int job = 0 ; job < numberOfJobsPerTask[task] ; job++)
        {
            // calculate the job Release Time
            int jobReleaseTime = job * taskdetails[task].periodicity;
            int remainingJob = taskdetails[task].exec_time;

            for (int frame = 0 ; frame < pFramesPerHyperPeriod ; frame++)
            {
                int currentFrameStart = frame * frameSize; //start

                if ((jobReleaseTime <= currentFrameStart) && (remainingFrameTime[frame] != 0 ))
                {
                    if (taskdetails[task].exec_time > remainingFrameTime[frame])
                    {
                        pScheduledTasks[numOfScheduledJobs].jobNumber = job;
                        pScheduledTasks[numOfScheduledJobs].scheduledFrame = frame;
                        pScheduledTasks[numOfScheduledJobs].job.exec_time = remainingFrameTime[frame];
                        pScheduledTasks[numOfScheduledJobs].job.periodicity = taskdetails[task].periodicity;
                        pScheduledTasks[numOfScheduledJobs].job.deadline = taskdetails[task].deadline;
                        pScheduledTasks[numOfScheduledJobs].job.ID = taskdetails[task].ID;
                        remainingJob = remainingJob - remainingFrameTime[frame];
                        remainingFrameTime[frame] = 0;
                        
                        if (remainingJob == 0) // whole job taken care of
                        {
                           printf("Job scheduled for task %d job %d \n",task,job);
                           numOfScheduledJobs++;
                           break;
                        }
                    }
                    else
                    {
                        pScheduledTasks[numOfScheduledJobs].jobNumber = job;
                        pScheduledTasks[numOfScheduledJobs].scheduledFrame = frame;
                        pScheduledTasks[numOfScheduledJobs].job.exec_time = taskdetails[task].exec_time;
                        pScheduledTasks[numOfScheduledJobs].job.periodicity = taskdetails[task].periodicity;
                        pScheduledTasks[numOfScheduledJobs].job.deadline = taskdetails[task].deadline;
                        pScheduledTasks[numOfScheduledJobs].job.ID = taskdetails[task].ID;
                        remainingJob = 0;
                        numOfScheduledJobs++;
                        
                        // update the frame remaining time
                        remainingFrameTime[frame] = remainingFrameTime[frame] - taskdetails[task].exec_time;
                        break;
                    }
                }
            }
        }
    }
    
    // run Ford fulkerson from here
    // first find the total execution time
    int totalexectime = 0;
    for (int tsk = 0 ; tsk < m_NumOftasks ; tsk ++ )
    {
        totalexectime = totalexectime + (numberOfJobsPerTask[tsk] * taskdetails[tsk].exec_time);
    }

    int timeUsedInframes = 0;
    for (int i = 0 ; i < pFramesPerHyperPeriod ; i++ )
    {
        timeUsedInframes = timeUsedInframes + (frameSize - remainingFrameTime[i]);
    }

    if (timeUsedInframes >= totalexectime)
    {
        // ford fulkerson passed
        m_totalNumOfJobs = numOfScheduledJobs;
        schedule = pScheduledTasks;
    }
    return 0;
}

int timelineScheduling(task_details *taskdetails)
{
    // No Valid schedule created ? Stop printing this
    if (schedule == NULL)
        return -1;
    
    
    int printSuccess = 0;
    int pNumberOfFrames = m_hyperPeriod / m_frameSize;
    int numberOfJobsPerTask[m_NumOftasks];
    int totalJobs = 0;

    // calculate number of jobs for each task
    for (int i = 0; i < m_NumOftasks; i++)
    {
        numberOfJobsPerTask[i] = m_hyperPeriod / taskdetails[i].periodicity;
        totalJobs = totalJobs + numberOfJobsPerTask[1];
    }
    
    
    // Since we want to go frame wise
    if (m_totalNumOfJobs != 0)
        printf("frames:%d %d\n",pNumberOfFrames,m_frameSize);
    
    // we need task wise
    
    for (int task = 0 ; task < m_NumOftasks ; task++)
    {
        for (int job = 0 ; job < m_totalNumOfJobs ; job++)
        {
            if (schedule[job].job.ID == (task+1))
            {
                printf("%d:%d %d %d\n",schedule[job].job.ID, (schedule[job].jobNumber+1),(schedule[job].scheduledFrame+1),schedule[job].job.exec_time);
                printSuccess++;
            }
        }
    }
    
    
    if (printSuccess == 0 || m_totalNumOfJobs == 0)
    {
        return -1;
    }
    //printf("\n");
    return 0;
}

void calculateMinorCycle(task_details *taskDetails)
{
    int multiples[100];
    int multipleCount = 0;
    int frameSizeValue = 0, prevFrameSize = 0;
    
    for (int i = 2 ; i < m_hyperPeriod ; i++)
    {
        if ((m_hyperPeriod % i) == 0)
        {
            multiples[multipleCount] = i;
            multipleCount++;
        }
    }
    
    for (int j = 0 ; j < multipleCount ; j++)
    {
        int passed = 0;
        prevFrameSize = frameSizeValue;
        for (int i = 0 ; i < m_NumOftasks; i++ )
        {
            if (2 * multiples[j] - gcd(multiples[j],taskDetails[i].periodicity) <= taskDetails[i].deadline)
            {
                passed++;
            }
        }

        if ((passed == m_NumOftasks) && (multiples[j] > prevFrameSize))
        {
            if (timelineScheduler(taskDetails,multiples[j]) == 0 )
            {
                
                m_frameSize = multiples[j];
                break;
            }
            frameSizeValue = multiples[j];
        }
    }
}

float calculateProcessorUtilisation(task_details *taskDetails)
{
    float pUtilisation = 0.0;
    for (int i = 0 ; i < m_NumOftasks ; i++ )
    {
        pUtilisation = pUtilisation + ((float)taskDetails[i].exec_time/ (float)taskDetails[i].periodicity);
    }
    return pUtilisation;
}

int calculateMajorCycle(task_details *taskDetails)
{
    int lcm = 1;
    for (int j = 0 ; j < m_NumOftasks ; j++)
    {
        lcm = lcm * taskDetails[j].periodicity / gcd(lcm,taskDetails[j].periodicity);
    }
    return lcm;
}

/*!
 * \brief Main function.
 * \details Function to read all the task sets supplied by the user,
 *          initiate the Time Demand analysis.
 * \param[in] argc Number of arguments passed to the binary.
 * \param[in] argv[] array of strings arguments passed to binary.
 */
int main(int argc, const char *argv[])
{
  if (argc == 1)
  {
    printf("Please enter the correct set of data ! \n ");
    return -1;
  }

  int numOfArgs = argc - 1;

  // Each will have 4 -- (<ID>␣<period>␣<executiontime>␣<deadline>)
  m_NumOftasks = numOfArgs / 4;

  task_details initialTaskDetails[m_NumOftasks];

  int parser = 1;

  for (int i = 0; i < m_NumOftasks; i++)
  {
    initialTaskDetails[i].ID = atoi(argv[parser++]);
    initialTaskDetails[i].periodicity = atoi(argv[parser++]);
    initialTaskDetails[i].exec_time = atoi(argv[parser++]);
    initialTaskDetails[i].deadline = atoi(argv[parser++]);
  }

  // Before starting the whole process, we need to confirm to the utilisation of task sets
  float utilisation = calculateProcessorUtilisation(initialTaskDetails);
  if (utilisation > 1.0)
  {
      printf("No schedule possible\n");
  }

  m_hyperPeriod = calculateMajorCycle(initialTaskDetails);
  calculateMinorCycle(initialTaskDetails);

#ifdef DEBUG_ENABLED
  printf("\n .....................................\n");
  printf("Stats for current Task set: \n ");
  printf("CPU utilisation: %f \n",utilisation);
  printf("Hyperperiod: %d \n ",m_hyperPeriod);
  printf("Frame Size : %d \n",m_frameSize);
  printf(".....................................\n");
#endif

  if (timelineScheduling(initialTaskDetails) == -1)
  {
      printf("No schedule possible\n");
  }
  
  return 0;
}
