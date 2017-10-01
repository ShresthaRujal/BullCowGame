#include "FBullCowGame.h"
#include <map>
#define TMap std::map

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) {
		return true;
	}
	TMap<char, bool> LetterSeen;
	for (auto Letter : Word) {
		Letter = tolower(Letter);
		if (LetterSeen[Letter])//if Letter in map
		{
			return false;//No isogram
		}
		else {
			LetterSeen[Letter] = true;
		}
		//loop through all the letters of the word
		//if the letter is in the map
		//we do not have a isogram
		//otherwise
		//add the letter to the map as seen
	}
	
	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for(auto Letter:Word)
	{
		if (!islower(Letter))
			return false;
	}
	return true;
}

FBullCowGame::FBullCowGame()
{
	Reset();
}

void FBullCowGame::Reset()
{
	constexpr int32 CurrentTry = 1;
	MyCurrentTry = CurrentTry;
	MyMaxTries = 5;
	const FString Hidden_Word = "planet";
	MyHiddenWord = Hidden_Word;
	bGameIsWon = false;
}

int32 FBullCowGame::GetMaxTries() const
{
	return MyMaxTries;
}

int32 FBullCowGame::TotalWrongs() const
{
	return 0;
}

int32 FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}

bool FBullCowGame::IsGameWon() const
{
	return bGameIsWon;
}

//receives a VALID guess, incriments turn, and returns count
BullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	BullCowCount BullCowCount;
	//loop through all lettes in the hidden word
	int32 HiddenWordLength = MyHiddenWord.length();
	for (int32 MHWChar = 0; MHWChar < HiddenWordLength; MHWChar++) {
		//compare letter agains guess
		for (int32 GChar = 0; GChar < HiddenWordLength; GChar++)
		{
			if (Guess[GChar]==MyHiddenWord[MHWChar])
			{
				if (MHWChar == GChar) {
					BullCowCount.Bulls++;
				}else
				{
					BullCowCount.Cows++;
				}
			}
		}
		if (BullCowCount.Bulls == HiddenWordLength) {
			bGameIsWon = true;
		}
		else {
			bGameIsWon = false;
		}
	}
		return BullCowCount;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) {//if the guess isn't an isogram,return an errror
		return EGuessStatus::Not_Isogram;
	}else if (!IsLowercase(Guess)){//if the guess isn't all lowercase,return error//if the guess isn't all lowercase,return error
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length()!=GetHiddenWordLength()) {//if the guess length is wrong,return error
		return EGuessStatus::Wrong_Length;
	}
	else {
		return EGuessStatus::OK;
	}
}
