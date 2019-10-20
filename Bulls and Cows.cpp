#include <iostream>
#include <ctime>
#include <vector>
#include <math.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main()
{
  
  //variables declaration and initialization
  vector<int> user_no(1);
  vector<int> random_no(1);
  int number = 0, i, j, temp, rem, power, bulls = 0, cows = 0, counter = 0, minutes = 0, seconds = 0;
  bool check = true;
  srand(time(0));
 
  // code for genearating a random number without repetition
  for ( j = 1 ; j < 5 ; j++ )
  {
    random: temp = rand() % 10;
    for ( i = 1 ; i < 5 ; i++ )
    {
      if ( temp == random_no[i])
      {
        goto random;
      }
      else
      {
        number = temp;
      }
    }
    random_no.push_back(temp);
  }

  //start time calculations
  const std::time_t start = std::time(nullptr) ;
  const std::tm start_time = *std::localtime( std::addressof(start) );
  
  do
  {
    //user input 
    cout << "Enter a 4 digit number(unique digits):";
    cin >> temp;
    counter++;
    
    //seperating digits from user data
    for ( i = 3 ; i >=0  ; i-- )
    {
      power = pow (10 , i);
      rem = temp / power;
      temp = temp % power;
      user_no.push_back(rem);
    }

    //checking for bulls and cows
    for ( i = 1 ; i < 5 ; i++ )
    {
      
      //check for bull
      if ( user_no[i] == random_no[i] )
      {
        bulls++;
      }
      else
      {
        //check for cow
        for ( j = 1 ; j < 5 ; j++ )
        {
          if ( user_no[i] == random_no[j])
          {
            cows++;
          }
        }
      }
    }

    //print number of bulls and cows
    cout << "bulls = " << bulls << " and cows = " << cows << endl;
    
    //exit loop if 4 bulls
    if ( bulls == 4 )
    {
      check = false;
    }
    
    //reseting values
    bulls = 0;
    cows = 0;
    user_no.clear();
    user_no.push_back(0);
  } while (check);
  
  //end time calculation
  const std::time_t end = std::time(nullptr) ;
  const std::tm end_time = *std::localtime( std::addressof(end) );
  
  //time conversion
  minutes = (end_time.tm_min - start_time.tm_min) * 60;
  seconds = (end_time.tm_sec - start_time.tm_sec) + minutes;
  minutes = seconds / 60;
  seconds = seconds % 60;
  
  //print result
  cout << "You guessed it in " << counter << " tries,  taking " << minutes << " minutes and " << seconds << " seconds";

}
