#include <iostream>
#include <fstream>
#include <vector>
#include "score.h"
#include <string>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;
int
main(int argc, char*argv[])
//Open a file to read and create a file to write.
{
	if (argc !=3)
{
	cerr<<"Wrong command line arguments";
	return 1;
}
	
	ifstream in_str(argv[1]);
	if (!in_str.good()) 
{
    cerr << "Can't open "<< argv[1] << " to read.\n";
	exit(1);
}
	char* filename=argv[2];

	ofstream out_str(filename);
	if (!out_str)
{
	cerr<<"Could not open "<< filename<<" to write\n";
}
    //Create a vector of type 'Score', so that we can stroe the data, and use the functions defined.
	vector<Score> player_score;
	Score one_player;
    
	//Read from file and store the data onto 'player_score'.
	while (one_player.read(in_str))
{
	player_score.push_back(one_player);
}
	//Sort the vector 'player_score'. less_name is well defined so that the sorting funtion will
	//allocate the order in 'player_score" according to the grade.
	sort(player_score.begin(), player_score.end(), less_names);
	
	//Our out function will automatically output the table required;
	out_score(out_str, player_score);



//*******************for the statistic part××××××××××××××××××××××××××××××××××××××××××××
	//We actually leave the value of 'grade_' empty, now define them.
	player_score=calculate_grade(player_score);
	sort(player_score.begin(), player_score.end(), more_grade);

//=====================================================================================
	//This sector will give some basic information about the vector<Score> player_score.
	//Like size, max name length. So out result automatically changes.
	int size=player_score.size();
	vector<int> a;
	for (int i=0; i<size; ++i)
	a.push_back(player_score[i].first_name().size()+player_score[i].last_name().size()); 
	vector<string> names;
	for (int i=0; i<size; ++i)
{
	string tran=player_score[i].first_name()+' ';
	tran=tran+player_score[i].last_name();
	names.push_back(tran);
}
	int max_length=0;
	for (int i=0; i<size; ++i)
{
	if (max_length<a[i])
    max_length=a[i];
}
//=====================================================================================
	
	//Output the statistic result. First is the final score after a game: called 'grade_' in my work.
	cout<<'\n';
	out_str<<'\n';
	for (int i=0; i<size; ++i)
	{cout<<setw(max_length+3)<<left<<names[i]<<setw(3)<<right<<player_score[i].get_grade()<<'\n';
	out_str<<setw(max_length+3)<<left<<names[i]<<setw(3)<<right<<player_score[i].get_grade()<<'\n';}
	cout<<'\n';
	out_str<<'\n';




	//Calculate the standard deviation and re-sort vector<Score> player_score.
	player_score=calculate_standard_deviation(player_score);
	sort(player_score.begin(), player_score.end(), less_standard_deviation);



//=====================================================================================
	//Like before...This sector will give some basic information about the vector<Score> player_score.
	//Like size, max name length. So out result automatically changes.
	size=player_score.size();
	a.clear();
	for (int i=0; i<size; ++i)
	a.push_back(player_score[i].first_name().size()+player_score[i].last_name().size()); 
	names.clear();
	for (int i=0; i<size; ++i)
{
	string tran=player_score[i].first_name()+' ';
	tran=tran+player_score[i].last_name();
	names.push_back(tran);
}
	max_length=0;
	for (int i=0; i<size; ++i)
{
	if (max_length<a[i])
    max_length=a[i];
}
//=====================================================================================

//Output the my own statistic part. That is sort the players by standard deviation. From big to small.	
for (int i=0; i<size; ++i)
	{cout<<setw(max_length+3)<<left<<names[i]<<setprecision(3)<<right<<player_score[i].get_standard_deviation()<<'\n';
out_str<<setw(max_length+3)<<left<<names[i]<<setprecision(3)<<right<<player_score[i].get_standard_deviation()<<'\n';}
return 0;
}
