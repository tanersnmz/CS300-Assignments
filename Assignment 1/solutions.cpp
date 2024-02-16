/*******************************************************************************************************************
Purpose: Basically, the main idea of this program is to generate random mazes and solve them by using stacks.

Author: Taner Giray Sonmez

Date: 25/03/2022

Any known bugs: No known bugs
******************************************************************************************************************/




#include <iostream>
#include <vector>
#include <string>
#include "randgen.h"
#include "Stack.h"
#include "Stack.cpp"
#include <fstream>


using namespace std;

//For generating random integers while constructing the maze.
RandGen random;

/**************************************************************************************************
This struct keeps the coordinates of the cell, the walls around it, and whether the cell is visited.
***************************************************************************************************/
struct cell{
    int x;
    int y;
    bool cellVisited;
    bool upWall;
    bool downWall;
    bool rightWall;
    bool leftWall;
    
    cell(int xCordinate, int yCordinate, bool visited, bool uWall, bool dWall, bool rWall, bool lWall):
        x(xCordinate),y(yCordinate),cellVisited(visited),upWall(uWall),downWall(dWall),rightWall(rWall),leftWall(lWall)
    {}
};



/**************************************************************************************
While generating the maze, this function decides which directions we can move to, 
if we can move in any direction, it returns true, otherwise, it returns false.
**************************************************************************************/
bool visitable(const cell & currentCell, int direction, int rowNum, int colNum, const vector<vector<cell>> & maze){
    bool visit = false;

	//Checking whether we can move to the right.
    if (direction==1 && currentCell.y != colNum-1 && maze[currentCell.x][currentCell.y+1].cellVisited==0 ) { 
        visit = true;     
    }

	//Checking whether we can move to the up.
    else if (direction==2 && currentCell.x != 0 && maze[currentCell.x-1][currentCell.y].cellVisited==0){ 
        visit = true;    
    }

	//Checking whether we can move to the left.
    else if (direction ==3 && currentCell.y != 0 && maze[currentCell.x][currentCell.y-1].cellVisited==0){ 
        visit = true;     
    }

	//Checking whether we can move to the down.
    else if (direction==4 && currentCell.x != rowNum-1 && maze[currentCell.x+1][currentCell.y].cellVisited==0){ 
        visit = true;    
    } 

    return visit;   
}

/*************************************************************************************
This function generates the maze, writes it into the desired text file, and returns it.
**************************************************************************************/
vector<vector<cell>>  MazeGenarator(int rowNumber, int colNumber, int numberOfTheMaze){
	Stack<cell> mazeStack;
    int sizeRowNumber=rowNumber;
    int sizeColNumber=colNumber;
    vector<vector<cell>> maze(rowNumber, vector<cell>(colNumber, cell(0,0,0,1,1,1,1)));
    for (int k=0; k<rowNumber; k++) {
        for (int j=0; j<colNumber; j++) {        
            maze[k][j].x=k;
            maze[k][j].y=j;
        }
    }    
    mazeStack.push(maze[0][0]);
    maze[0][0].cellVisited=true;
    int cellVisitedCounter=0;
    while (cellVisitedCounter < sizeColNumber*sizeRowNumber-1) {
        cell currentCell = mazeStack.top();      
        vector<int> visitableDirections;
        for (int i=1; i<=4; i++) {
            if (visitable(currentCell,i , sizeRowNumber, sizeColNumber, maze)) visitableDirections.push_back(i);
        }       
        if (visitableDirections.size()==0) {
            mazeStack.pop();           
        }
        else{
            int randomIdx =random.RandInt(0,visitableDirections.size()-1);
            unsigned int direction = visitableDirections[randomIdx];

			// If we are moving to the right, it breaks necessary walls and marks the cell as visited.
            if (direction==1) { 
                maze[currentCell.x][currentCell.y].cellVisited=1;
                maze[currentCell.x][currentCell.y].rightWall=0;            
                maze[currentCell.x][currentCell.y+1].leftWall=0;
                maze[currentCell.x][currentCell.y+1].cellVisited=1;                
                mazeStack.push(maze[currentCell.x][currentCell.y+1]);
            }

			//If we are moving to the up, it breaks necessary walls and marks the cell as visited.
            else if (direction==2){ 
                maze[currentCell.x][currentCell.y].cellVisited=1;
                maze[currentCell.x][currentCell.y].upWall=0;          
                maze[currentCell.x-1][currentCell.y].downWall=0;
                maze[currentCell.x-1][currentCell.y].cellVisited=1; 
                mazeStack.push( maze[currentCell.x-1][currentCell.y]);
            }

			//If we are moving to the left, it breaks necessary walls and marks the cell as visited.
            else if (direction==3){ 
                maze[currentCell.x][currentCell.y].cellVisited=1;
                maze[currentCell.x][currentCell.y].leftWall=0;                                
                maze[currentCell.x][currentCell.y-1].rightWall=0;
                maze[currentCell.x][currentCell.y-1].cellVisited=1;               
                mazeStack.push( maze[currentCell.x][currentCell.y-1]);
            }

			//If we are moving to the down, it breaks necessary walls and marks the cell as visited.
            else if (direction==4){ 
                maze[currentCell.x][currentCell.y].cellVisited=1;
                maze[currentCell.x][currentCell.y].downWall=0;  
                maze[currentCell.x+1][currentCell.y].upWall=0;
                maze[currentCell.x+1][currentCell.y].cellVisited=1;
                mazeStack.push(maze[currentCell.x+1][currentCell.y]);
            }
            cellVisitedCounter++;
        }        
    }

	//Bellow part for writing the maze into a file.
    ofstream output;
    string filename="maze_"+ to_string(numberOfTheMaze)+  ".txt";
    output.open(filename.c_str());  
    output << sizeRowNumber << " "<< sizeColNumber <<endl;
    for (int k=0; k<sizeRowNumber; k++) {
        for (int j=0; j<sizeColNumber; j++) {
            output<< "x="<< maze[k][j].y <<" y=" <<  maze[k][j].x <<  " l="<<maze[k][j].leftWall<< " r="<< maze[k][j].rightWall << " u=" << maze[k][j].downWall << " d=" << maze[k][j].upWall << endl; 
        }
    }
    output.close();  

    return maze;
}

/*****************************************************************************
While solving the maze, this function decides which directions we can move to, 
if we can move in any direction, it returns true, otherwise, it returns false.
*******************************************************************************/
bool visitablePath(const cell & currentCell, int direction, int rowNum, int colNum, const vector<vector<cell>> & maze){
    bool visit = false;

	//Checking whether we can move to the right.
    if (direction==1 && currentCell.y != colNum-1 && maze[currentCell.x][currentCell.y+1].leftWall==0 && maze[currentCell.x][currentCell.y].rightWall ==0 && maze[currentCell.x][currentCell.y+1].cellVisited==0 ) { 
        visit = true;     
    }

	//Checking whether we can move to the up.
    else if (direction==2 && currentCell.x != 0 && maze[currentCell.x-1][currentCell.y].downWall==0 && maze[currentCell.x][currentCell.y].upWall==0 && maze[currentCell.x-1][currentCell.y].cellVisited==0)  { 
        visit = true;      
    }

	//Checking whether we can move to the left.
    else if (direction ==3 && currentCell.y != 0 && maze[currentCell.x][currentCell.y-1].rightWall==0 && maze[currentCell.x][currentCell.y].leftWall==0 && maze[currentCell.x][currentCell.y-1].cellVisited==0){ 
        visit = true;      
    }

    //Checking whether we can move to the down.
    else if (direction==4 && currentCell.x != rowNum-1 && maze[currentCell.x+1][currentCell.y].upWall==0 && maze[currentCell.x][currentCell.y].downWall==0 && maze[currentCell.x+1][currentCell.y].cellVisited==0){ 
        visit = true;     
    }

    return visit;   
}





/******************************************************************
This function solves the maze, writes it into the desired text file.
*******************************************************************/
void mazeSolver(vector<vector<cell>>  & maze,int startingX,int startingY,int endingX,int endingY,int sizeRowNumber, int sizeColNumber,int mazeId){
    Stack<cell> mazeSolverStack;
	mazeSolverStack.push(maze[startingX][startingY]);
    maze[startingX][startingY].cellVisited=1; 
    while (mazeSolverStack.top().x!= endingX || mazeSolverStack.top().y != endingY) {
        cell currentCell = mazeSolverStack.top();    
        vector<int> visitableDirections;
        for (int i=1; i<=4; i++) {
            if (visitablePath(currentCell,i , sizeRowNumber, sizeColNumber, maze)) visitableDirections.push_back(i);
        }
        if (visitableDirections.size()==0) {
            mazeSolverStack.pop();    
        }
        else{
            int randomIdx =random.RandInt(0,visitableDirections.size()-1);
            unsigned int direction = visitableDirections[randomIdx];

			// If we are moving to the right, it marks necessary cells as visited.
            if (direction==1) { 
                maze[currentCell.x][currentCell.y].cellVisited=1;              
                maze[currentCell.x][currentCell.y+1].cellVisited=1;
                mazeSolverStack.push(maze[currentCell.x][currentCell.y+1]);
            }

			// If we are moving to the up, it marks necessary cells as visited.
            else if (direction==2){ 
                maze[currentCell.x][currentCell.y].cellVisited=1;                
                maze[currentCell.x-1][currentCell.y].cellVisited=1;
                mazeSolverStack.push( maze[currentCell.x-1][currentCell.y]);
            }

			// If we are moving to the left, it marks necessary cells as visited.
            else if (direction==3){ 
                maze[currentCell.x][currentCell.y].cellVisited=1;               
                maze[currentCell.x][currentCell.y-1].cellVisited=1;
                mazeSolverStack.push( maze[currentCell.x][currentCell.y-1]);
            }

			// If we are moving to the down, it marks necessary cells as visited.
            else if (direction==4){ 
                maze[currentCell.x][currentCell.y].cellVisited=1;
                maze[currentCell.x+1][currentCell.y].cellVisited=1;
                mazeSolverStack.push(maze[currentCell.x+1][currentCell.y]);
            }     
        }
    }

	//I used another stack to print the solution of the maze in the desired format.
    Stack<cell> printerStack;
    while (!mazeSolverStack.isEmpty()) {
        cell coppyCell = mazeSolverStack.top();      
        printerStack.push(coppyCell);
        mazeSolverStack.pop();
    }	

	//Bellow part for solving the maze into a file.
	ofstream output;
	string fileName ="maze_"+ to_string(mazeId)+"_path_"+to_string(startingY)+"_"+to_string(startingX)+"_"+to_string(endingY)+"_"+to_string(endingX)+".txt";
	output.open(fileName.c_str());
    while (!printerStack.isEmpty()) {
        cell currentCell =printerStack.top();
        output<< currentCell.y <<" "<< currentCell.x <<endl;
        printerStack.pop();      
    }
	output.close();    
}



int main() {
       
    int numberOfMazes;
    int numberOfRows;
    int numberOfColumns;
    cout << "Enter the number of mazes: ";
    cin >> numberOfMazes;
    cout << "Enter the number of rows and columns (M and N): ";
    cin >> numberOfRows >> numberOfColumns;
    
	//It keeps all mazes generated.
	vector<vector<vector<cell>>> allMazes;

	for (int i = 1; i <= numberOfMazes; i++)
	{
		vector<vector<cell>> generatedMaze = MazeGenarator(numberOfRows, numberOfColumns,i);
		allMazes.push_back(generatedMaze);
	}



    
    cout << "All mazes are generated."<<endl;
    cout << endl;
    
    
    
    
	cout << "Enter a maze ID between 1 to "<< numberOfMazes << " inclusive to find a path: ";
    int mazeId;
    cin >> mazeId;
    int userStartX,userStartY,userEndX,userEndY;
    cout << "Enter x and y coordinates of the entry points (x,y) or (column,row): ";
    
    cin >> userStartX >> userStartY;
    cout << "Enter x and y coordinates of the exit points (x,y) or (column,row): ";
    cin >> userEndX >> userEndY;
    
	//Before solving the maze, marking cells as not visited.
    for (int k=0; k<numberOfRows; k++) {
        for (int j=0; j<numberOfColumns; j++) {
            allMazes[mazeId-1][k][j].cellVisited=0;
        
        }
    }
    
    
    mazeSolver(allMazes[mazeId-1], userStartY, userStartX, userEndY, userEndX, numberOfRows,numberOfColumns,mazeId); 

    return 0;
}
