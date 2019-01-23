#include <iostream>
#include <fstream>
#include <string>


using namespace std;

#define maxStudent 80
#define maxSubject 80

class scoresGroup {
	friend class studentGroup;

public:
	scoresGroup() {};

private:
	int std_id;
	int ary_scores[maxStudent];
};

class rankGroup {
	friend class studentGroup;

public:
	rankGroup() { 
		fill_n(ary_rank, maxStudent, 1); 
	};
private:
	int ary_rank[maxStudent];
	
	int count = 0;
};

class studentGroup {

public:
	
	int inputStd(void);
	void sort_out_Std(void);
	

private:
	scoresGroup scArray[maxStudent];
	rankGroup rkArray[maxStudent];


	int std_num, sub_num, sort_num;

	int top_array[30];
	int top_num=0;
	int pair_count = 0;
	int pair_array[200][2];
	
};

int studentGroup::inputStd()
{
	int j,i=0;

	ifstream inFile("scores.inp");

	if (inFile.fail())
	{
		return 0;
		
	}

	inFile >> std_num >> sub_num >> sort_num;
	

	while (i<std_num)
	{
		inFile >> scArray[i].std_id;
		
		for (j = 0; j < sub_num; j++)
			inFile >> scArray[i].ary_scores[j];
		i++;
		
	}

	inFile.close();

	return 0;
	
}

void studentGroup::sort_out_Std()
{
	int i, j, k;
	int s = 0;
	ofstream rOut("scores.out");

	rOut << std_num << endl;
	while (s < sub_num)
	{
		for (i = 0; i < std_num; i++)
			for (j = 0; j < std_num; j++)
				if (scArray[i].ary_scores[s] < scArray[j].ary_scores[s])
					rkArray[i].ary_rank[s]++;
		s++;
	}

	for (i = 1; i <= std_num; i++)
	{
		for (j = 0; j < std_num; j++)
		{

			if (rkArray[j].ary_rank[sort_num - 1] == i)
			{
				rOut << scArray[j].std_id;
				for (k = 0; k < sub_num; k++)
					rOut << " "<< rkArray[j].ary_rank[k];

			}
		}
		rOut << endl;
	}
	
	if (sub_num >= 3 && std_num >= 3)
	{
		
		for (i = 0; i < std_num; i++)
		{
			for (j = 0; j < sub_num; j++)
			{
				if (rkArray[i].ary_rank[j] == 1 || rkArray[i].ary_rank[j] == 2 || rkArray[i].ary_rank[j] == 3)
					rkArray[i].count++;
				
			}
		}
		
		for (i = 0; i < std_num; i++)
		{
		
			if (rkArray[i].count > 3)
				top_array[top_num++] = i;
		}
		int temp;

		for (i = 0; i < top_num; i++)
		{
			for (j = i+1; j < top_num; j++)
			{
				if (scArray[top_array[i]].std_id > scArray[top_array[j]].std_id)
				{
					temp = top_array[i];
					top_array[i] = top_array[j];
					top_array[j] = temp;
				}

			}
		}
		rOut << top_num << endl;
		for (i = 0; i < top_num; i++)
		{
			rOut << scArray[top_array[i]].std_id;
			for (j = 0; j < sub_num; j++)
			{
				rOut << " "<< rkArray[top_array[i]].ary_rank[j];
			}
			rOut << endl;
		}


	}
	else
		rOut << "0"<< endl;

	int t;
	int sub;
	int sub_code=0;
	if (sub_num >= 2 && std_num >= 12)
	{
		while (sub_code < sub_num) {

			for (i = 0; i < std_num; i++)
			{
				for (j = i+1; j < std_num; j++)
				{
					sub = rkArray[i].ary_rank[sub_code] - rkArray[j].ary_rank[sub_code];
					if (sub > 2 || sub < -2)
					{
						
						for (k = sub_code + 1; k < sub_num; k++)
						{
							sub = rkArray[i].ary_rank[sub_code] - rkArray[j].ary_rank[sub_code];
							if (sub > 10 || sub < -10)
							{
								
								if (pair_count == 0)
								{
									pair_array[pair_count][0] = i;
									pair_array[pair_count][1] = j;
									pair_count++;
								}

								else 
								{
									for (t = 0; (t < pair_count) && (((pair_array[t][0] == i) && (pair_array[t][1] == j)) != 1); t++)
									{

										if (t == pair_count - 1)
										{
											pair_array[pair_count][0] = i;
											pair_array[pair_count][1] = j;
											pair_count++;
										}

									}
								}
							}

						}
						

					}

				}
			}
			sub_code++;
		}
		rOut << pair_count << endl;
	}
	else
		rOut << "0" << endl;
	rOut.close();
}
	
int main()
{

	studentGroup stdG;
	stdG.inputStd();
	stdG.sort_out_Std();
	

	

	return 0;
}