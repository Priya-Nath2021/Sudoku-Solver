#include <iostream>
using namespace std;
/********************FUNCTION DECLARATION************************/
void enterAPuzzle(int grid[][9]);
bool search(int grid[][9]);
int getFreecell(int grid[][9], int freeCellList[][2]);
void printGrid(int grid[][9]);
bool isValid(int i, int j, int grid[][9]);
bool isValid(int grid[][9]);
void introduction();
/**************************************************************/

/************************INTRODUCTION**************************/
void introduction()
{
  cout<<"\t\t\t\t\t\t\t  SUDOKU SOLVER   \t\t\t\t\t\t\t"<<endl;
  cout<<"\t\t\t\t\t\t  NAME   : PRIYA NATH  \t\t\t\t\t\t\t"<<endl;
  cout<<"\t\t\t\t\t\t  BRANCH : IT  \t\t\t\t\t\t\t"<<endl;
  cout<<"\t\t\t\t\t   UNIV. ROLL NO.: 2015537   \t\t\t\t\t\t\t"<<endl;
}
/*************************************************************/

/**********************MAIN FUNCTION**************************/
int main() {
  introduction();
  int grid[9][9];
  enterAPuzzle(grid);

  if (!isValid(grid))
    cout << "Invalid input" << endl;
  else if (search(grid)) {
    cout << "The solution is found:" << endl;
    printGrid(grid);
  } else
    cout << "No solution" << endl;

  return 0;
}
/*******************************************************/

/************FUNCTION TO ENTER A SUDOKU PUZZLE**********/
void enterAPuzzle(int grid[][9]) 
{

  cout << "Enter a Sudoku puzzle:" << endl;
  for (int i = 0; i < 9; i++)
    for (int j = 0; j < 9; j++)
      cin >> grid[i][j];
}
/******************************************************/

/***********FUNCTION TO CHECK NUMBER OF FREE CELLS AVAILABLE****/
int getFreeCell(int grid[][9], int freeCellList[][2]) {
  
  int numberOfFreeCells = 0;

  for (int i = 0; i < 9; i++)
    for (int j = 0; j < 9; j++)
      if (grid[i][j] == 0) {
        freeCellList[numberOfFreeCells][0] = i;
        freeCellList[numberOfFreeCells][1] = j;
        numberOfFreeCells++;
      }

  return numberOfFreeCells;
}
/*************************************************************/

/*****************FUNCTION TO PRINT THE GRID********************/
void printGrid(int grid[][9]) {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++)
      cout << grid[i][j] << " ";
    cout << endl;
  }
}
/*************************************************************/

/***************FUNCTION TO SEARCH A SOLUTION****************/
bool search(int grid[][9]) {
  int k = 0;          
  bool found = false; 

  int freeCellList[81][2];
  int numberOfFreeCells = getFreeCell(grid, freeCellList);

  while (!found) 
  {
    int i = freeCellList[k][0];
    int j = freeCellList[k][1];
    if (grid[i][j] == 0)
      grid[i][j] = 1; // Start with 1

    if (isValid(i, j, grid)) 
    {
      if (k + 1 == numberOfFreeCells) 
      { 
        found = true;                   
      } 
      else 
      {                          
        k++;
      }
    } 
    else if (grid[i][j] < 9) 
    {
      grid[i][j] = grid[i][j] + 1; 
    } 
    else 
    {                       
      while (grid[i][j] == 9) {
        grid[i][j] = 0; 
        if (k == 0) {
          return false; 
        }
        k--; 
        i = freeCellList[k][0];
        j = freeCellList[k][1];
      }

      grid[i][j] = grid[i][j] + 1; 
    }
  }

  return true; 
}
/********************************************************************/


/********FUNCTION TO CHECK WHETHER THE grid[i][j] IS VALID**********/
bool isValid(int i, int j, int grid[][9]) {
  
  for (int column = 0; column < 9; column++)
    if (column != j && grid[i][column] == grid[i][j])
      return false;

  
  for (int row = 0; row < 9; row++)
    if (row != i && grid[row][j] == grid[i][j])
      return false;

  
  for (int row = (i / 3) * 3; row < (i / 3) * 3 + 3; row++)
    for (int col = (j / 3) * 3; col < (j / 3) * 3 + 3; col++)
      if (row != i && col != j && grid[row][col] == grid[i][j])
        return false;

  return true; 
}
/*********************************************************************/

bool isValid(int grid[][9]) 
{
  // Check for duplicate numbers
  for (int i = 0; i < 9; i++)
    for (int j = 0; j < 9; j++)
      if (grid[i][j] != 0)
        if (!isValid(i, j, grid))
          return false;

  
  for (int i = 0; i < 9; i++)
    for (int j = 0; j < 9; j++)
      if ((grid[i][j] < 0) || (grid[i][j] > 9))
        return false;

  return true; 
}

