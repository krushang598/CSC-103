#include <iostream>
#include <chrono>
#include <string>
#include <cctype>

using namespace std;

/*
This function generates the random string
*/
std::string generate(const int length)
{
  int number;
  char temp;
  string rand_str;
  
  srand(time(0));
 
  /*
  Random String is generated here after the loop
  */
  for ( int i = 0; i < length; i++ )
  {
    number = rand() % 5;
    if ( number == 4 )
    {
      number = rand() % 2;
      if ( number == 0 )
      {
        rand_str.push_back('*');
      } 
      else 
      { 
        rand_str.push_back('0');
      }
    }
    else
    {
      number = rand() % 2;
      if ( number == 0 )
      {
        number = (rand() % 26) + 65 ;
        temp = number;
        rand_str.push_back(temp);
      }
      else 
      { 
        number = (rand() % 26) + 97 ;
        temp = number;
        rand_str.push_back(temp);
      }
    }
  }
  return rand_str;
}

//function to calculate the offset
int offset_calc(const string generated, const string userInput)
{
  int penalty = 0;
  for ( int i=0 ; i<5 ; i++ )
  {
    if ( generated[i] == '*' && (isalnum(userInput[i]) == 0) )
    {
      penalty += 0;
    }
    else if( generated[i] == '0' && (isdigit(userInput[i])) != 0 )
    {
      penalty += 0;
    }
    else
    {
      penalty += abs( int(generated[i]) - int(userInput[i]) );
    }
  }
  return penalty;
}

//main function
int main()
{
  string rand_str,human_str;
  int player_points = 2000, offset = 0, difference = 0;
  bool loop_end = false;

  //while loop to keep it running
  while(!loop_end)
  {
    rand_str = generate(5);
    cout << "Your current points " << player_points << ", just type -> ";
    for( int i=0 ; i<5 ; i++ )
    {
      if( rand_str[i] == '0')
      {
        cout << "[0-9]";
      }
      else if ( rand_str[i] == '*' )
      {
        cout << "[!-%]";
      }
      else
      {
        cout << rand_str[i];
      }
    }
    cout << ": ";
    //start time after printing
    auto t_start = std::chrono::high_resolution_clock::now();

    getline(cin,human_str);
    //end time after user presses enter
    auto t_end = std::chrono::high_resolution_clock::now();

    int elapsedTimeMs = std::chrono::duration<double, std::milli>(t_end-t_start).count();

    //checking offset value
    offset = offset_calc( rand_str, human_str );

    if( elapsedTimeMs <= 10000 && offset == 0 )
    {
      player_points += 500;
      cout << elapsedTimeMs << " milliseconds, you made it within the interval of 10000..." << endl;
    }
    else if ( elapsedTimeMs <= 10000 && offset != 0 )
    {
      player_points = player_points - offset;
      cout << elapsedTimeMs << " milliseconds, you made it within the interval of 10000..." << endl << "String offset is " << offset <<" , your total penalty is " << offset << "..." << endl;
    }
    else if ( elapsedTimeMs > 10000 && offset == 0 )
    {
      difference = elapsedTimeMs - 10000;
      player_points = player_points - difference;
      cout << elapsedTimeMs << " milliseconds, you *failed* it within the interval of 10000..." << endl;
    }
    else
    {
      difference = elapsedTimeMs - 10000;
      player_points = player_points - (2*offset) - difference;
      cout << elapsedTimeMs << " milliseconds, you *failed* it within the interval of 10000..." << endl << "String offset is " << offset <<" , your total penalty is " << (2*offset) + difference << "..." << endl;
    }
    
    //reseting the variables
    rand_str = "";
    human_str = "";
    difference = 0;
    
    //exit loop if points >= 5000 or <= 0
    if( player_points >= 5000 || player_points <= 0 )
    {
      loop_end = true;
      cout << "Bye...";
    }
  }
}
