/*Problem*/
/**
A student signed up for n workshops and wants to attend the maximum number of workshops where no two workshops
overlap. You must do the following:
Implement 2 structures:
  1.struct Workshop having the following members:
    -The workshop's start time.
    -The workshop's duration.
    -The workshop's end time.
  2.struct Available_Workshops having the following members:
    -An integer,  (the number of workshops the student signed up for).
    -An array of type Workshop array having size n.
Implement 2 functions:
  1.Available_Workshops* initialize (int start_time[], int duration[], int n)
  Creates an Available_Workshops object and initializes its elements using the elements in the start_time[] and
  duration[] parameters (both are of size n). Here, start_time[i] and duration[i] are the respective start time
  and duration for the ith workshop. This function must return a pointer to an Available_Workshops object.
  2.int CalculateMaxWorkshops(Available_Workshops* ptr)
  Returns the maximum number of workshops the student can attend—without overlap. The next workshop cannot be
  attended until the previous workshop ends.
  Note: An array of unknown size (n) should be declared as follows:
  DataType* arrayName = new DataType[n];
Input Format
  Input from stdin is handled by the locked code in the editor; you simply need to write your functions to meet
  the specifications of the problem statement above.
Constraints
  1<=N<=10^5
  0<=start_time_i<=10^3
  0<=duration_i<=10^3
Output Format
  Output to stdout is handled for you.
  Your initialize function must return a pointer to an Available_Workshops object.
  Your CalculateMaxWorkshops function must return maximum number of non-overlapping workshops the student can
  attend.
Sample Input
  6
  1 3 0 5 5 8
  1 1 6 2 4 1
Sample Output
  CalculateMaxWorkshops should return 4.
Explanation
  The first line denotes n, the number of workshops.
  The next line contains n space-separated integers where the ith integer is the ith workshop's start time.
  The next line contains n space-separated integers where the ith integer is the ith workshop's duration.
  The student can attend the workshops 0,1,3, and 5 without overlap, so CalculateMaxWorkshops returns 4 to main
  which then prints 4 to stdout).
**/

#include<bits/stdc++.h>

using namespace std;
struct Workshop
{
    int start;
    int duration;
    int end;
};

struct Available_Workshops
{
    int N;
    vector<Workshop> v;
    Available_Workshops(int &n)
    {
        v = vector<Workshop>(n);
        N = n;
    }
};

bool compare(Workshop &w1, Workshop &w2)
{
    return w1.end < w2.end;
}

Available_Workshops *initialize(int start_time[], int duration[], int n)
{
    Available_Workshops *AW = new Available_Workshops(n);

    for(int i=0;i<n;i++)
    {
        AW->v[i].start = start_time[i];
        AW->v[i].duration = duration[i];
        AW->v[i].end = start_time[i] + duration[i];
    }
    sort(AW->v.begin(),AW->v.end(),compare);

    return AW;
}

int CalculateMaxWorkshops(Available_Workshops* ptr)
{
    int end_time=0;
    int count=0;

    for(int i=0;i<ptr->N; i++)
        if(ptr->v[i].start >= end_time)
        {
            end_time = ptr->v[i].end;
            count += 1;
        }

    return count;
}
/*always select the next possible event that ends as early as
possible.*/

//Define the structs Workshops and Available_Workshops.
//Implement the functions initialize and CalculateMaxWorkshops
/*iteration 1: passes everything but times out on some
/*struct Workshop
{
    int startTime;
    int duration;
    int endTime;

    Workshop(){
        startTime = -1;
        endTime = -1;
        duration = -1;
    }
    Workshop(int s, int d) : startTime(s), duration(d)
    {
        endTime = startTime + duration;
    }
    void operator=(Workshop b)
    {
        this->duration = b.duration;
        this->endTime = b.endTime;
        this->startTime = b.startTime;
        return;
    }
};

struct Available_Workshops
{
    int n;
    Workshop* ws;//pointer for the top of the array
    //vector<Workshop> ws;
    Available_Workshops(int * s, int * d,int num)
    {
        n = num;
        ws = new Workshop[num];
        Workshop temp;
        for(int i = 0; i < num; i++)
        {
            Workshop temp(s[i],d[i]);
            ws[i] = temp;
        }
        return;
    }
    void sortByDuration()
    {
        bool swapped = false;
        Workshop temp;
        do{
            swapped = false;
            for(int i = 0; i < n-1; i++)
            {
                if(ws[i].duration > ws[i+1].duration )
                {
                    temp = ws[i];
                    ws[i] = ws[i+1];
                    ws[i+1] = temp;
                    swapped = true;
                }
            }
        }while(swapped);
    }
    void sortByStartTime()
    {
        bool swapped = false;
        Workshop temp;

        do{
            swapped = false;
            for(int i = 0; i < n-1; i++)
            {
                if(ws[i].startTime > ws[i+1].startTime )
                {
                    temp = ws[i];
                    ws[i] = ws[i+1];
                    ws[i+1] = temp;
                    swapped = true;
                }
            }
        }while(swapped);
    }
    void specialSort()
    {
        bool swapped = false;
        Workshop temp;
        do{
            swapped = false;
            for(int i = 0; i < n-1; i++)
            {
                if(ws[i].endTime - ws[i+1].endTime > 0 )
                {
                    temp = ws[i];
                    ws[i] = ws[i+1];
                    ws[i+1] = temp;
                    swapped = true;
                }
            }
        }while(swapped);
    }
};
Available_Workshops* initialize(int* s, int *d, int n)
{
    Available_Workshops aws(s,d,n);
    Available_Workshops* p = &aws;
    return p;
}

int CalculateMaxWorkshops(Available_Workshops* ptr) {
    ptr->specialSort();

    int end_time=0;
    int count=0;

    for(int i=0;i<ptr->n; i++)
        if(ptr->ws[i].startTime >= end_time)
        {
            end_time = ptr->ws[i].endTime;
            count += 1;
        }

    return count;
}*/

int main(int argc, char *argv[]) {
    int n; // number of workshops
    cin >> n;
    // create arrays of unknown size n
    int* start_time = new int[n];
    int* duration = new int[n];

    for(int i=0; i < n; i++){
        cin >> start_time[i];
    }
    for(int i = 0; i < n; i++){
        cin >> duration[i];
    }

    Available_Workshops * ptr;
    ptr = initialize(start_time,duration, n);
    cout << CalculateMaxWorkshops(ptr) << endl;
    return 0;
}
