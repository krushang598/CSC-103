#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
  int dice1, dice2, dice3, score_p = 0, score_c = 0, total_p, total_c, round_no = 1, difference = 0, inc = 0;
  string input = "";
  
  srand(static_cast<unsigned int>(time(0)));

  //while loop to keep the game running unless one reaches to 150 
  while ( score_p < 150 && score_c < 150 )
  {
    //player's turn
    //rolling dice (randomly)
    roll: dice1 = 1 + rand() % 6;
          dice2 = 1 + rand() % 6;
          dice3 = 1 + rand() % 6;
    cout << "Rolled " << dice1 << ", " << dice2 << ", " << dice3 << endl ;
        
    //check for one's if any
    if ( dice1 == 1 && dice2 == 1 && dice3 == 1 )
    {
      score_p = 0 ;
      cout << "Three ones, lose all holdings, and lose turn." << endl << endl ;
    }
    else if ( dice1 == 1 && dice2 == 1 || dice2 == 1 && dice3 == 1 || dice3 == 1 && dice1 == 1 )
    {
      score_p = score_p / 2 ;
      cout << "Two ones, lose half of holdings, and lose turn" << endl << endl ;
    }
    else if ( dice1 == 1 || dice2 == 1 || dice3 == 1 )
    {
      cout << "Single one, lose turn" << endl << endl ;
    }
    
    else
    {
      total_p = dice1 + dice2 + dice3 ;
      cout << "sum = " << total_p << endl ;
        
      //check the user input if valid
      print_cond: cout << "Bank ( y / n ) ? " ;
      getline (cin,input) ;
        
      //loop for player's banking system
      if ( input == "y" || input == "n" )
      {
        if ( input == "y" )
        {
          score_p = score_p + total_p ;
        }
        else
        {
          goto roll;
        }
        }
      else
      {
        goto print_cond;
      }
    }
      
    //computer's turn
    cout << "Computer's turn" << endl ;
      
    roll_comp: dice1 = 1 + rand() % 6;
               dice2 = 1 + rand() % 6;
               dice3 = 1 + rand() % 6;
    cout << "Rolled " << dice1 << ", " << dice2 << ", " << dice3 << endl ;
        
    //check for one's for computer
    if ( dice1 == 1 && dice2 == 1 && dice3 == 1 )
    {
      score_c = 0 ;
      cout << "Three ones, lose all holdings, and lose turn." << endl;
    }
    else if ( dice1 == 1 && dice2 == 1 || dice2 == 1 && dice3 == 1 || dice3 == 1 && dice1 == 1 )
    {
      score_c = score_c / 2 ;
      cout << "Two ones, lose half of holdings, and lose turn" << endl ;
    }
    else if ( dice1 == 1 || dice2 == 1 || dice3 == 1 )
    {
      cout << "Single one, lose turn" << endl ;
    }
    else
    {
      total_c = dice1 + dice2 + dice3 ;
      cout << "sum = " << total_c;
      difference = score_p - score_c - total_c ;
      
      if ( difference > 10 )
      {
        inc = ( difference / 10 );
        inc = ( inc < 3 ) ? inc : 3 ;
        if ( total_c > 11 + inc )
        {
          score_c = score_c + total_c ;
          cout << " bank " << endl;
        }
        else
        {
          cout << " no bank " << endl ;
          goto roll_comp;
        }
      }
      else
      {
        if ( score_c + total_c > score_p )
        {
          score_c = score_c + total_c ;
          cout << " bank " << endl;
        }
        else
        {
          cout << " no bank " << endl; 
          goto roll_comp;
        }
      }
    }
    cout << "After round " << round_no++ << " human has " << score_p << " and computer has " << score_c << endl << endl ;
  }
  //check who wins
  if ( score_c == score_p )
  {
    cout << "Tie";
  }
  else if ( score_c > score_p && score_c >= 150 )
  {
    cout << "Computer won";
  }
  else
  {
    cout << "Human won";
  }
}
