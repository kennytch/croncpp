#include <iostream>
#include <chrono>
#include <vector>
#include <string>

#include "croncpp.h"

template <typename Time = std::chrono::microseconds,
   typename Clock = std::chrono::high_resolution_clock>
   struct perf_timer
{
   template <typename F, typename... Args>
   static Time duration(F&& f, Args... args)
   {
      auto start = Clock::now();

      std::invoke(std::forward<F>(f), std::forward<Args>(args)...);

      auto end = Clock::now();

      return std::chrono::duration_cast<Time>(end - start);
   }
};

void test_cron(std::vector<std::string> const & expressions)
{
   for (auto const & e : expressions)
   {
      try
      {
         auto cron = cron::make_cron(e);
      }
      catch (cron::bad_cronexpr const & ex)
      {
         std::cerr << ex.what() << std::endl;
      }
      catch (std::exception const & ex)
      {
         std::cerr << "UNEXPECTED: " << ex.what() << std::endl;
      }
   }
}

int main()
{
   std::vector<std::string> expressions =
   {
      "* * * * * *",
      "*/5 * * * * *", "0,5,10,15,20,25,30,35,40,45,50,55 * * * * *",
      "1/6 * * * * *", "1,7,13,19,25,31,37,43,49,55 * * * * *",
      "0/30 * * * * *", "0,30 * * * * *",
      "0-5 * * * * *", "0,1,2,3,4,5 * * * * *",
      "55/1 * * * * *", "55,56,57,58,59 * * * * *",
      "57,59 * * * * *", "57/2 * * * * *",
      "1,3,5 * * * * *", "1-6/2 * * * * *",
      "0,5,10,15 * * * * *", "0-15/5 * * * * *",
      "* */5 * * * *", "* 0,5,10,15,20,25,30,35,40,45,50,55 * * * *",
      "* 1/6 * * * *", "* 1,7,13,19,25,31,37,43,49,55 * * * *",
      "* 0/30 * * * *", "* 0,30 * * * *",
      "* 0-5 * * * *", "* 0,1,2,3,4,5 * * * *",
      "* 55/1 * * * *", "* 55,56,57,58,59 * * * *",
      "* 57,59 * * * *", "* 57/2 * * * *",
      "* 1,3,5 * * * *", "* 1-6/2 * * * *",
      "* 0,5,10,15 * * * *", "* 0-15/5 * * * *",
      "* * */5 * * *", "* * 0,5,10,15,20 * * *",
      "* * 1/6 * * *", "* * 1,7,13,19 * * *",
      "* * 0/12 * * *", "* * 0,12 * * *",
      "* * 0-5 * * *", "* * 0,1,2,3,4,5 * * *",
      "* * 15/1 * * *", "* * 15,16,17,18,19,20,21,22,23 * * *",
      "* * 17,19,21,23 * * *", "* * 17/2 * * *",
      "* * 1,3,5 * * *", "* * 1-6/2 * * *",
      "* * 0,5,10,15 * * *", "* * 0-15/5 * * *",
      "* * * 1-31 * *", "* * * 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31 * *",
      "* * * 1/5 * *", "* * * 1,6,11,16,21,26,31 * *",
      "* * * 1,11,21,31 * *", "* * * 1-31/10 * *",
      "* * * */5 * *", "* * * 1,6,11,16,21,26,31 * *",
      "* * * * 1,6,11 *", "* * * * 1/5 *",
      "* * * * 1-12 *", "* * * * 1,2,3,4,5,6,7,8,9,10,11,12 *",
      "* * * * 1-12/3 *", "* * * * 1,4,7,10 *",
      "* * * * */2 *", "* * * * 1,3,5,7,9,11 *",
      "* * * * 2/2 *", "* * * * 2,4,6,8,10,12 *",
      "* * * * 1 *", "* * * * JAN *",
      "* * * * 2 *", "* * * * FEB *",
      "* * * * 3 *", "* * * * mar *",
      "* * * * 4 *", "* * * * apr *",
      "* * * * 5 *", "* * * * may *",
      "* * * * 6 *", "* * * * Jun *",
      "* * * * 7 *", "* * * * Jul *",
      "* * * * 8 *", "* * * * auG *",
      "* * * * 9 *", "* * * * sEp *",
      "* * * * 10 *", "* * * * oCT *",
      "* * * * 11 *", "* * * * nOV *",
      "* * * * 12 *", "* * * * DEC *",
      "* * * * 1,FEB *", "* * * * JAN,2 *",
      "* * * * 1,6,11 *", "* * * * NOV,JUN,jan *",
      "* * * * 1,6,11 *", "* * * * jan,jun,nov *",
      "* * * * 1,6,11 *", "* * * * jun,jan,nov *",
      "* * * * JAN,FEB,MAR,APR,MAY,JUN,JUL,AUG,SEP,OCT,NOV,DEC *", "* * * * 1,2,3,4,5,6,7,8,9,10,11,12 *",
      "* * * * JUL,AUG,SEP,OCT,NOV,DEC,JAN,FEB,MAR,APR,MAY,JUN *", "* * * * 1,2,3,4,5,6,7,8,9,10,11,12 *",
      "* * * * * 0-6", "* * * * * 0,1,2,3,4,5,6",
      "* * * * * 0-6/2", "* * * * * 0,2,4,6",
      "* * * * * 0-6/3", "* * * * * 0,3,6",
      "* * * * * */3", "* * * * * 0,3,6",
      "* * * * * 1/3", "* * * * * 1,4",
      "* * * * * 0", "* * * * * SUN",
      "* * * * * 1", "* * * * * MON",
      "* * * * * 2", "* * * * * TUE",
      "* * * * * 3", "* * * * * WED",
      "* * * * * 4", "* * * * * THU",
      "* * * * * 5", "* * * * * FRI",
      "* * * * * 6", "* * * * * SAT",
      "* * * * * 0-6", "* * * * * SUN,MON,TUE,WED,THU,FRI,SAT",
      "* * * * * 0-6/2", "* * * * * SUN,TUE,THU,SAT",
      "* * * * * 0-6/3", "* * * * * SUN,WED,SAT",
      "* * * * * */3", "* * * * * SUN,WED,SAT",
      "* * * * * 1/3", "* * * * * MON,THU", 
   };

   auto t = perf_timer<>::duration(test_cron, expressions);

   auto micro = std::chrono::duration<double, std::micro>(t).count();

   std::cout << "Total time: " << micro << " microsec\n";
   std::cout << "Average time: " << (micro/expressions.size()) << micro << " microsec\n";
}