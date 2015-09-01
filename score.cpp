#include <iostream>
#include <vector>
#include "score.h"
#include <string>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <cmath>
using namespace std;


void Score::set_grade(int n)//Set the grade_ which means the final score after a game.
{
 grade_= n;
}

void Score::set_standard_deviation(float n)//Set the standard_deviation.
{
 standard_deviation_=n;
}

bool Score::read(istream& in_str)//Read from a file and store the data onto player_score.
{
	if (!(in_str>>first_name_>> last_name_))
	{
		return false;
	}

	player_score_.clear();
	int score;
	unsigned int i;
/*Since strikes and spares may happen, the number of scores for each player may vary. 
If no strike or spare, there will give 20 scores. A perfect game will give only 12 scores.
So for consistency, we will set all game consist 21 score. In order to realize that, we have
to input twice if a 10 appears at a even position( when j=0, 2, 4...). And if some one
does not have the chance to play the bonus games, we set them as -1. And our function will 
recognize these certain patterns like: two 10, first one at even positin, second at odd, or the score is -1.etc, 
and output the exactly right format*/
	{for (i=0; i<18 && (in_str>>score); ++i)
		if (score==10 && i%2==0)//A strike happens.
		{player_score_.push_back(score);
	     player_score_.push_back(score);++i;}
		else
			player_score_.push_back(score);}
	int score1, score2,score3;//Set last 3 scores aside.
	in_str>>score1;
	in_str>>score2;
	player_score_.push_back(score1);
	player_score_.push_back(score2);

	//A player plays spare at 10th frame, so do not qulify the second bonus frame.Set to -1;
	if (score1!=10&&score1+score2!=10)
	{score3=-1; player_score_.push_back(score3);}
	else
	{in_str>>score3; player_score_.push_back(score3);}
	return true;
}

//For sorting purpose, compare players' last names and first names alphabetically and return true or false.
bool less_names(const Score& player1, const Score& player2)
{
	return player1.last_name()<player2.last_name() || 
		(player1.last_name()==player2.last_name() && player1.first_name()<player2.first_name() );
}
//For sorting purpose, compare players' grade_ and return true or false.
bool more_grade(const Score& player1, const Score& player2)
{
	return player1.get_grade()>player2.get_grade();
}
//For sorting purpose, compare players' standard deviation and return true or false.
bool less_standard_deviation(const Score& player1, const Score& player2)
{
	return player1.get_standard_deviation()< player2.get_standard_deviation();
}
//Output the frame.
void out_score(ostream& out_str, vector<Score> player_score)
{
	//Some basic information about the vector.
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
	
	//First dash line.
	string dash_line(67+max_length,'-');
	cout<<dash_line<<"\n";
	out_str<<dash_line<<"\n";

	vector<int> total_score;
	for (int i=0; i<size; i++)
	{
	total_score.clear();
    total_score.push_back(0);

	//The very left. Names in right position.
	cout<<"| "<<setw(max_length+2)<<left<<names[i]<<"|";
	out_str<<"| "<<setw(max_length+2)<<left<<names[i]<<"|";


	//This output part only handle all the cells except the last one.
	int n=0;
	for (int j=0; j<18; j=j+2)
	{
	n++;

	
	
	if (player_score[i].get_score(j)==10&&player_score[i].get_score(j+1)==10)//Recognize strike.Tiem step 2, j is always even.
		{cout<<"   "<<"X"<<" |";
		out_str<<"   "<<"X"<<" |";}
	else
	
	{
		if (player_score[i].get_score(j)==0)//Recognize 0 score.
			{cout<<" "<<"-"<<" ";
			out_str<<" "<<"-"<<" ";}
		else 
			{cout<<" "<<player_score[i].get_score(j)<<" ";
			out_str<<" "<<player_score[i].get_score(j)<<" ";}
	

		if (player_score[i].get_score(j+1)==0)
			{cout<<"-"<<" |";
			out_str<<"-"<<" |";}
		else if (player_score[i].get_score(j)+player_score[i].get_score(j+1)==10)//Recognize spare.
			{cout<<"/"<<" |";
			out_str<<"/"<<" |";}
		else
			{cout<<player_score[i].get_score(j+1)<<" |";
			out_str<<player_score[i].get_score(j+1)<<" |";}

	}
	
	//===================================================================================================
	//This part is used to calculate the total score after each frame.
	//stike. Add the following 2 games as bonus. Also test whether  the following game is a strike. If yes, use j+3 instead of j+2.
    //Because stike has the pattern of double 10. One 10 is not real just for convenience purpose.
	if (player_score[i].get_score(j)==10)
		{if (player_score[i].get_score(j+2)!=10) 
			total_score.push_back(total_score[j/2]+player_score[i].get_score(j)+player_score[i].get_score(j+2)+player_score[i].get_score(j+3));
		else if(player_score[i].get_score(j+2)==10 && j/2==8)
			total_score.push_back(total_score[j/2]+player_score[i].get_score(j)+player_score[i].get_score(j+2)+player_score[i].get_score(j+3));
		else total_score.push_back(total_score[j/2]+player_score[i].get_score(j)+player_score[i].get_score(j+2)+player_score[i].get_score(j+4));}
  
	else if (player_score[i].get_score(j)+player_score[i].get_score(j+1)==10)//Spare.Add the following one game.
			{total_score.push_back(total_score[j/2]+player_score[i].get_score(j)+player_score[i].get_score(j+1)+player_score[i].get_score(j+2));}
	
	else//Nothing good happen.
			{total_score.push_back(total_score[j/2]+player_score[i].get_score(j)+player_score[i].get_score(j+1));}
	}
	//Bonus frames.
	if (player_score[i].get_score(20)==-1)//Recognize the last game as not played. Should plus 1, since a -1 is there.
		total_score.push_back(total_score[9]+player_score[i].get_score(18)+player_score[i].get_score(19)+player_score[i].get_score(20)+1);
	else//Total score is just add the following 3 scores up without -1.
		total_score.push_back(total_score[9]+player_score[i].get_score(18)+player_score[i].get_score(19)+player_score[i].get_score(20));

    //====================================================================================================
	
	//This output part handles the last cell in every line since it is very complicating.
	if (player_score[i].get_score(18)==0)//10th get 0 for first throw.
	{
		{cout<<" "<<"-"<<" ";
		out_str<<" "<<"-"<<" ";}

		{if (player_score[i].get_score(19)==10)//spare although get 10 because first throw is 0.
			{cout<<"/ ";
			out_str<<"/ ";}
		else if (player_score[i].get_score(19)==0)
			{cout<<"- ";
			out_str<<"- ";}
		else
			{cout<<player_score[i].get_score(19)<<" ";out_str<<player_score[i].get_score(19)<<" ";}
		}

		{if (player_score[i].get_score(20)<0)//If one do not have the change to play the second bonus, leave it empty.
			{cout<<"  |"<<'\n';
			out_str<<"  |"<<'\n';}
		else if (player_score[i].get_score(20)==0)
			{cout<<"- |"<<'\n';
			out_str<<"- |"<<'\n';}
		else if (player_score[i].get_score(20)==10)
			{cout<<"X |"<<'\n';
			out_str<<"X |"<<'\n';}
		else{
			if ((player_score[i].get_score(19)+player_score[i].get_score(20))==10)//nomal spare.
				{cout<<"/ |"<<'\n';
				out_str<<"/ |"<<'\n';}
			else
				{cout<<player_score[i].get_score(20)<<" |"<<'\n';
				out_str<<player_score[i].get_score(20)<<" |"<<'\n';}}
		}
	
	}

	else if (player_score[i].get_score(18)==10)// strike, 2 bonus.
	{

		{cout<<" "<<"X"<<" ";
		out_str<<" "<<"X"<<" ";}
		{if (player_score[i].get_score(19)==10)
			{cout<<"X ";
			out_str<<"X ";}
		else if (player_score[i].get_score(19)==0)
			{cout<<"- ";
			out_str<<"- ";}
		else
			{cout<<player_score[i].get_score(19)<<" ";
			out_str<<player_score[i].get_score(19)<<" ";}}

		{if (player_score[i].get_score(20)<0)//used up 2 throws on one frame. the 21st will be empty.
			{cout<<"  |"<<'\n';
			out_str<<"  |"<<'\n';}

		else if (player_score[i].get_score(20)==0)
			{cout<<"- |"<<'\n';
			out_str<<"- |"<<'\n';}
		else if (player_score[i].get_score(20)==10)
			{cout<<"X |"<<'\n';
			out_str<<"X |"<<'\n';}
		else{
		if ((player_score[i].get_score(19)+player_score[i].get_score(20))==10)
			{cout<<"/ |"<<'\n';
			out_str<<"/ |"<<'\n';}
		else
			{cout<<player_score[i].get_score(20)<<" |"<<'\n';
			out_str<<player_score[i].get_score(20)<<" |"<<'\n';}}}
    }
	
    else
    {
		{cout<<" "<<player_score[i].get_score(18)<<" ";
		out_str<<" "<<player_score[i].get_score(18)<<" ";}
	
		{if ((player_score[i].get_score(18)+player_score[i].get_score(19))==10)
			{cout<<"/ ";
			out_str<<"/ ";}
		else if (player_score[i].get_score(19)==0)
			{cout<<"- ";
			out_str<<"- ";}
		else
			{cout<<player_score[i].get_score(19)<<" ";
			out_str<<player_score[i].get_score(19)<<" ";}}

		{if (player_score[i].get_score(20)==-1)
			{cout<<"  |"<<'\n';
			out_str<<"  |"<<'\n';}
		else if (player_score[i].get_score(20)==0)
			{cout<<"- |"<<'\n';
			out_str<<"- |"<<'\n';}
		else if (player_score[i].get_score(20)==10)
			{cout<<"X |"<<'\n';
			out_str<<"X |"<<'\n';}
		else
			{cout<<player_score[i].get_score(20)<<" |"<<'\n';
			out_str<<player_score[i].get_score(20)<<" |"<<'\n';}}
	}
	    //The second row of one player. First comes some blanks.
		string blanks(max_length+1,' ');
		{cout<<"| "<<blanks<<" |";
		out_str<<"| "<<blanks<<" |";}
		
		//The total scores after each frame.
		total_score.push_back(total_score[n]+player_score[i].get_score(18)+player_score[i].get_score(19));
		for (int m=1; m<10; ++m)
		{cout<<setw(4)<<right<<total_score[m]<<" |";
		out_str<<setw(4)<<right<<total_score[m]<<" |";}
		cout<<setw(6)<<right<<total_score[n+1]<<" |"<<'\n';
		out_str<<setw(6)<<right<<total_score[n+1]<<" |"<<'\n';
		cout<<dash_line<<"\n";
		out_str<<dash_line<<"\n";
	}
	}


	
	
	vector<Score> calculate_grade(vector<Score> player_score)
	//This function is used to set the value of grade_. We use some cold that 
	//we have used when calculating the total scores after each frame.
	{
	int size=player_score.size();//Some basic information about the vector.
	vector<int> total_score;
	
	for (int i=0; i<size; ++i)
	{
		total_score.clear();
	    total_score.push_back(0);
		for (int j=0; j<18; j=j+2)
	{
	//===================================================================================================
	//As before...This part is used to calculate the total score after each frame.
	if (player_score[i].get_score(j)==10)
	{if (player_score[i].get_score(j+2)!=10) 
	total_score.push_back(total_score[j/2]+player_score[i].get_score(j)+player_score[i].get_score(j+2)+player_score[i].get_score(j+3));
	else if(player_score[i].get_score(j+2)==10 && j/2==8)
    total_score.push_back(total_score[j/2]+player_score[i].get_score(j)+player_score[i].get_score(j+2)+player_score[i].get_score(j+3));
	else total_score.push_back(total_score[j/2]+player_score[i].get_score(j)+player_score[i].get_score(j+2)+player_score[i].get_score(j+4));}
  
	else if (player_score[i].get_score(j)+player_score[i].get_score(j+1)==10)
	{total_score.push_back(total_score[j/2]+player_score[i].get_score(j)+player_score[i].get_score(j+1)+player_score[i].get_score(j+2));}
	
	else
	{total_score.push_back(total_score[j/2]+player_score[i].get_score(j)+player_score[i].get_score(j+1));}
	}
	if (player_score[i].get_score(20)==-1)
	total_score.push_back(total_score[9]+player_score[i].get_score(18)+player_score[i].get_score(19)+player_score[i].get_score(20)+1);
	else
    total_score.push_back(total_score[9]+player_score[i].get_score(18)+player_score[i].get_score(19)+player_score[i].get_score(20));
	//Grade_ is the final one of total_score.
	player_score[i].set_grade(total_score[10]);
	}
    //====================================================================================================
	return player_score;//The return is a vector of class Score.
	}






	vector<Score> calculate_standard_deviation(vector<Score> player_score)
	{
	int size=player_score.size();//Basic information.
	vector<int> total_score;
	vector<float> sigma;
	
	for (int i=0; i<size; ++i)
	{
		total_score.clear();
	    total_score.push_back(0);
		for (int j=0; j<18; j=j+2)
	{
	//===================================================================================================
	//As before...This part is used to calculate the total score after each frame.
	if (player_score[i].get_score(j)==10)
	{if (player_score[i].get_score(j+2)!=10) 
	total_score.push_back(total_score[j/2]+player_score[i].get_score(j)+player_score[i].get_score(j+2)+player_score[i].get_score(j+3));
	else if(player_score[i].get_score(j+2)==10 && j/2==8)
    total_score.push_back(total_score[j/2]+player_score[i].get_score(j)+player_score[i].get_score(j+2)+player_score[i].get_score(j+3));
	else total_score.push_back(total_score[j/2]+player_score[i].get_score(j)+player_score[i].get_score(j+2)+player_score[i].get_score(j+4));}
  
	else if (player_score[i].get_score(j)+player_score[i].get_score(j+1)==10)
	{total_score.push_back(total_score[j/2]+player_score[i].get_score(j)+player_score[i].get_score(j+1)+player_score[i].get_score(j+2));}
	
	else
	{total_score.push_back(total_score[j/2]+player_score[i].get_score(j)+player_score[i].get_score(j+1));}
	}
	if (player_score[i].get_score(20)==-1)
	total_score.push_back(total_score[9]+player_score[i].get_score(18)+player_score[i].get_score(19)+player_score[i].get_score(20)+1);
	else
    total_score.push_back(total_score[9]+player_score[i].get_score(18)+player_score[i].get_score(19)+player_score[i].get_score(20));
	//====================================================================================================
	//Calculating the standard deviation.
	float avg=total_score[8]/8;
	//qv stands for Quadratic Variance.
	float qv=0;
	for (int l=1; l<9; ++l)
	qv=qv+(total_score[l]-total_score[l-1]-avg)*(total_score[l]-total_score[l-1]-avg);

	//Divided by 7 instead of 8, in order to have a no-bia estimation
	float sigma=sqrt(qv/(8-1));
	player_score[i].set_standard_deviation(sigma);
	}
    
	return player_score;//Return a vector of class Score.
	}
