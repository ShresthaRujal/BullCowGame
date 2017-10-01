#include <iostream>
#include <string>
#include"FBullCowGame.h"

using int32 = int32;
using FText = std::string;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
void PrintGameSummary();
bool AskToPlayAgain();
FText Guess = "";
FBullCowGame BCGame;

int main() {
	bool wantToPlay = false;
	do {
		PrintIntro();
		PlayGame();
		wantToPlay=AskToPlayAgain();
	} while (wantToPlay);
	return 0;
}

void PlayGame(){
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	//lopo for the number of turns asking for guesses
	//TODO change from FOR to WHILE loop once we are validation tries
	while(!BCGame.IsGameWon()&& BCGame.GetCurrentTry()<=MaxTries){
		Guess=GetValidGuess();
		
		//submit valid guess to the game, and receive counts
		BullCowCount BullCowCount=BCGame.SubmitValidGuess(Guess);
		
		std::cout << "Bulls=" << BullCowCount.Bulls;
		std::cout << "Cows=" << BullCowCount.Cows<<std::endl;
	}
	//TODO summarise game
	PrintGameSummary();
}

void PrintIntro() {
	//game intro.
	
	std::cout << "Welcome to Bulls and Cows.\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of? \n\n";
}

//loop continually until the user gives a valid guess
FText GetValidGuess() {
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		//get input from player.
		int32 MycurrentTry = BCGame.GetCurrentTry();
		std::cout << "TRY " << MycurrentTry << ".";
		std::cout << "Enter your Guess: ";
		std::getline(std::cin, Guess);
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << "letter word.\n \n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter lowercase character only!\n \n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Your Word is not an isogram!\n \n";
			break;
		default:
			//assuming its valid guess
			break;
		}
		std::cout<<std::endl;
	} while (Status!=EGuessStatus::OK);
	return Guess;
}

void PrintGameSummary() {
	if (BCGame.IsGameWon())
	{
		std::cout << "Well Done -- You won! \n";
	}
	else {
		std::cout << "Better luck next time! \n";
	}
}

bool AskToPlayAgain() {
	std::cout << "Do you want to play again with the same hidden word (y/n)? \n";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y'|| Response[0] == 'Y');
}