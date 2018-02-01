#include "tournament.h"
#include "stdafx.h"

tournament::tournament()
{
    m_tournamentRound = 0;
    m_computerScore = 0;
    m_humanScore = 0;
    round = new game();
}

tournament::tournament(std::string a_savedGame)
{    
    // File successfully loaded and is valid.
    if(loadSavedFile(a_savedGame))
    {   
        round = new game(m_humanColorFromFile, m_computerColorFromFile, m_nextPlayerFromFile, m_boardSizeFromFile, *m_boardTableFromFile);
    }
    else
    {
        std::cout << "File is invalid. Exiting game now." << std::endl;
        exit(1);
    }
}

tournament::~tournament()
{
    std::cout << "Thanks for playing. Exiting game." << std::endl;
    delete round;
}

// Checks to see if the filename provided is a valid/compliant save file.
// After check, then loads the contents of the file.
bool tournament::loadSavedFile(std::string a_savedGame)
{
    std::ifstream inFile;
    std::string buff;
    std::vector<std::string> fileContents;

    inFile.open(a_savedGame);
    if (!inFile)
    {   
        std::cout << "Could not open file.. Terminating Kono." << std::endl;
        return false;
    }

    // Read entire file line by line and parse line using istringstream.
    while(!inFile.eof())
    {
        getline(inFile, buff);
        std::istringstream line(buff);
        while(line)
        {
            buff.clear();
            line >> buff;
            if(buff!="")
            {    
                fileContents.push_back(buff);
            }
        }
    }

    // ADD TRY CATCH BLOCK HERE

    // Get round #
    m_tournamentRound = stoi(fileContents[1]);

    // Get computer score.
    m_computerScore = stoi(fileContents[4]);

    // Get computer color.
    if(fileContents[6] == "Black")
    {
        m_computerColorFromFile = 'B';
    }
    else if(fileContents[6] == "White")
    {
        m_computerColorFromFile = 'W';
    }
    
    // Get Human score.
    m_humanScore = stoi(fileContents[9]);

    // Get Human color.
    if(fileContents[11] == "Black")
    {
        m_humanColorFromFile = 'B';
    }
    else if(fileContents[11] == "White")
    {
        m_humanColorFromFile = 'W';
    }

    // Get Board state.
    std::vector<std::string>::iterator first = find(fileContents.begin(),fileContents.end(),"Board:")+1;
    std::vector<std::string>::iterator last = find(fileContents.begin(),fileContents.end(),"Next");
    
    m_boardSizeFromFile = std::sqrt(std::distance(first,last));

    std::vector <char> rows (m_boardSizeFromFile,'+');
    m_boardTableFromFile = new std::vector < std::vector<char> > (m_boardSizeFromFile,rows);

    int startIndex = std::distance(fileContents.begin(),first);

    for(int i = 0; i < m_boardSizeFromFile; i++)
    {
        for(int j = 0; j < m_boardSizeFromFile; j++)
        {
            (*m_boardTableFromFile)[i][j] = fileContents[startIndex].c_str()[0];
            startIndex++;
        }
    }
        
    // Get next player.
    if(fileContents[40] == "Human")
    {
        m_nextPlayerFromFile = 'h';
    }
    else if(fileContents[40] == "Computer")
    {
        m_nextPlayerFromFile = 'c';
    }

    return true;
}

void tournament::showMenu() const
{
    round -> showMenu();
}

void tournament::saveGame(std::string a_fileName) const
{
    std::ofstream outFile(a_fileName,std::ofstream::out);

    outFile << "Round: " << m_tournamentRound << "\n";
    outFile << "Computer:\n";
    outFile << "Score: " << round -> getComputerScore() << "\n";
    outFile << "Color: " << round -> getComputerColor() << "\n";
    outFile << "Human:\n";
    outFile << "Score: " << round -> getHumanScore() << "\n";
    outFile << "Color: " << round -> getHumanColor() << "\n";
    outFile << "Board:\n";

    unsigned short boardSize = round -> getBoardSize();
    std::vector< std::vector <char> > boardTable = round ->getBoardState();
    
    for( int row = 0; row < boardSize; row++ )
    {
        for( int col = 0; col < boardSize; col++ )
        {
            if(boardTable[row][col] == '+')
                outFile << "O  ";
            else
                outFile << boardTable[row][col] << "  ";
        }

        outFile <<"\n";
    }
    
    outFile << "Next Player: " << round -> getNextPlayer();

    outFile.close();
};

void tournament::playGame() const
{
    round -> playRound();
};

void tournament::helpGame() const
{
    round -> getHelp();
};

bool tournament::continueGame()
{
    std::string choice = "";
    while(choice != "Yes" || choice != "No")
    {
        std::cout << "Do you want to play another round? (Yes/No)";
        std::cin >> choice;

        if(choice == "Yes")
            return true;

        else if(choice == "No")
            return false;
  
        else
            continue;
    }    
};

void tournament::getWinner() const
{
    std::cout << "Human Score: " << m_humanScore << std::endl;
    std::cout << "Computer Score: " << m_computerScore << std::endl;
    if(m_humanScore == m_computerScore)
    {
        std::cout << "There is no clear winner. It is a draw." << std::endl;
    }
    else if(m_humanScore > m_computerScore)
    {
        std::cout << "Human is the winner!" << std::endl;
    }
    else
    {
        std::cout << "Computer is the winner!" << std::endl;
    }
};

void tournament::calculateScores()
{
    
}