#ifndef __score_h_
#define __score_h_


#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Score{

public:
	//Accessors
	const string& first_name() const {return first_name_;}
	const string& last_name() const {return last_name_;}
	const int get_score(int j) const {return player_score_[j];}
	const float get_standard_deviation() const {return standard_deviation_;}
	//"Grade" means the final score the player will get after one game.
	const int get_grade()const {return grade_;}
	
	//Modifiers
	void set_grade(int n);
	void set_standard_deviation(float n);
	//Allow you to read from a txt file and set values.
	bool read(istream& in_str);
	
	
	
private: //Representation
	string first_name_;
	string last_name_;
	vector<int> player_score_;
	float standard_deviation_;
	int grade_;
};

//Given a vector of the class type 'Score', this function calculates the standard deviation or grade
//and return a new vector with the standard_deviation_ or grade being set.
vector<Score> calculate_grade(vector<Score> player_score);
vector<Score> calculate_standard_deviation(vector<Score> player_score);

//For sorting purpose.
bool less_names(const Score& player1, const Score& player2);
bool less_standard_deviation(const Score& player1, const Score& player2);
bool more_grade(const Score& player1, const Score& player2);

//Given a vector of the class type 'Score', this function returns the ASCII art table.
void out_score(ostream& out_str, vector<Score> player_score);
#endif
