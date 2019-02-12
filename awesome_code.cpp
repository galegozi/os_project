#include <iostream>
#include <queue>
using namespace std;
struct Resource
{
  int size;
  string type;
};
class Process
{
public:
  queue<Resource> r;
  int ftime = 0;
};
bool operator<(const Process& a, const Process& b)
{
  return a.ftime > b.ftime;
}
int main()
{
  priority_queue<Process> p;
  string s;
  cin >> s;
  int ncores;
  cin >> ncores;
  cin >> s;
  while(s == "NEW")
  {
    Process proc_temp;
    cin >> proc_temp.ftime;
    while(cin >> s && s != "NEW")
    {
      Resource r_temp;
      r_temp.type = s;
      cin >> r_temp.size;
      proc_temp.r.push(r_temp);
    }
    p.push(proc_temp);
  }
  //input complete.
  priority_queue<int> ready_queue;
  int ssd_ftime = 0;
  int input_ftime = 0;
  int global_time = p.top().ftime;
  while(!p.empty())
  {
    Process top = p.top();
    p.pop();
    if(!top.r.empty())
    {
      Resource rec = top.r.front();
      top.r.pop();
      if(rec.type == "CORE")
      {
        if(ready_queue.size() < ncores)
        {
          ready_queue.push(global_time + rec.size);
          top.ftime = global_time + rec.size;
          if(p.empty()) global_time = top.ftime;
        }
        else
        {
          int rqueue_top = ready_queue.top();
          ready_queue.pop();
          rqueue_top = max(rqueue_top + rec.size, global_time + rec.size);
          top.ftime = rqueue_top;
          ready_queue.push(rqueue_top);
          if(p.empty()) global_time = top.ftime;
        }
      }
      else if(rec.type == "INPUT")
      {
        input_ftime = max(input_ftime + rec.size, global_time + rec.size);
        top.ftime = input_ftime;
        if(p.empty()) global_time = top.ftime;
      }
      else if(rec.type == "SSD")
      {
        ssd_ftime = max(ssd_ftime + rec.size, global_time + rec.size);
        top.ftime = ssd_ftime;
        if(p.empty()) global_time = top.ftime;
      }
      else
      {
        cerr << "YOUR INPUT IS INVALID!" << '\n';
        exit(1);
      }
      p.push(top);
      global_time = p.top().ftime;
    }
    else
    {
      cout << "A PROCESS FINISHED AT TIME " << global_time << "!" << endl;
    }
  }
}
