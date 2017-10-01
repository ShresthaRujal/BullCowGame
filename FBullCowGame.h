#pragma once
#include <string>

using int32 = int;
using FString = std::string;

struct BullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};
enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

enum class EGameStatus
{
	Win,
	Lose
};

class FBullCowGame {
private:
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
public:
	FBullCowGame();
	void Reset();//TODO make a more rich return value.
	int32 GetMaxTries() const;
	int32 TotalWrongs() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	BullCowCount SubmitValidGuess(FString);

	EGuessStatus CheckGuessValidity(FString) const;

};
