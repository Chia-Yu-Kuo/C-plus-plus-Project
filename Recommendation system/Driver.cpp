#include <vector>
#include <set>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <iomanip>
#include <string.h>
#include <sstream>

#include "Strategy.h"

using namespace std;
const int K = 10;

bool ReadFile(const string inputName, vector<vector<double>> &Table)
{
    Table.clear();

    ifstream inputFile;
    inputFile.open(inputName.c_str());
    if (!inputFile.is_open())
    {
        cerr << inputName << "not open" << endl;
        return false;
    }

    string line1, line2;
    int userNum, itemNum;

    inputFile >> userNum;
    inputFile >> itemNum;

    vector<double> V(itemNum, -1);
    vector<vector<double>> T(userNum, V);
    Table = T;
    int userIdx = 0;

    getline(inputFile, line1);
    while (getline(inputFile, line1) && getline(inputFile, line2))
    {

        istringstream in1(line1);
        istringstream in2(line2);

        int item;
        double rating;

        while (in1 >> item && in2 >> rating)
        {

            Table[userIdx][item] = rating;
        }
        userIdx++;
    }

    inputFile.close();

    return true;
}

bool Recommend_Check(vector<vector<int>> ans, const int K)
{
    bool err = 0;

    set<int> check;
    for (int i = 0; i < (int)ans.size(); i++)
    {
        if ((int)ans[i].size() == K)
        {
            check.clear();
            for (int j = 0; j < (int)ans[i].size(); j++)
            {
                check.insert(ans[i][j]);
            }
            if (ans[i].size() != check.size())
            {
                err = 1;
                cerr << "Duplicate Recommended items" << endl;
            }
        }
        else
        {
            err = 1;
            cerr << "Num of recommended items < " << K << endl;
        }
        if (err == 1)
        {
            break;
        }
    }
    return err;
}

double Score(vector<vector<int>> RecomdList, vector<vector<double>> Table)
{
    int count_users = (int)Table.size();
    int count_items = (int)Table[0].size();
    int count_recommendedItems = (int)RecomdList[0].size();

    vector<int> vec_tp(count_users, 0);
    vector<int> vec_countAnswer(count_users, 0);

    for (int i = 0; i < count_users; i++)
    {
        for (int j = 0; j < count_recommendedItems; j++)
        {
            if (Table[i][RecomdList[i][j]] != (-1))
            {
                vec_tp[i] = vec_tp[i] + 1;
            }
        }
        for (int j = 0; j < count_items; j++)
        {
            if (Table[i][j] != (-1))
            {
                vec_countAnswer[i] = vec_countAnswer[i] + 1;
            }
        }
    }

    vector<double> vec_precision(count_users, 0);
    vector<double> vec_recall(count_users, 0);

    for (int i = 0; i < count_users; i++)
    {
        if (count_recommendedItems != 0)
        {
            vec_precision[i] = (double)vec_tp[i] / (double)count_recommendedItems;
        }
        if (vec_countAnswer[i] != 0)
        {
            vec_recall[i] = (double)vec_tp[i] / (double)vec_countAnswer[i];
        }
    }

    vector<double> vec_dcg(count_users, 0);
    vector<double> vec_idcg(count_users, 0);
    vector<double> vec_ndcg(count_users, 0);
    vector<double> vec_weight(count_recommendedItems, 0);
    for (int i = 0; i < count_recommendedItems; i++)
    {
        vec_weight[i] = log2(i + 2);
    }
    vector<vector<double>> vec2d_rel(count_users, vector<double>(count_recommendedItems, 0));
    for (int i = 0; i < count_users; i++)
    {
        for (int j = 0; j < count_recommendedItems; j++)
        {
            if (Table[i][RecomdList[i][j]] != (-1))
            {
                vec2d_rel[i][j] = Table[i][RecomdList[i][j]];
            }
            vec_dcg[i] = vec_dcg[i] + vec2d_rel[i][j] / vec_weight[j];
        }
    }
    for (int i = 0; i < count_users; i++)
    {
        for (int j = 0; j < count_recommendedItems; j++)
        {
            sort(vec2d_rel[i].begin(), vec2d_rel[i].end(), greater<double>());
            vec_idcg[i] = vec_idcg[i] + vec2d_rel[i][j] / vec_weight[j];
        }
        if (vec_idcg[i] != 0)
        {
            vec_ndcg[i] = vec_dcg[i] / vec_idcg[i];
        }
    }

    double ndcg = 0;
    for (auto e : vec_ndcg)
        ndcg += e;
    ndcg /= vec_ndcg.size();

    double precision = 0;
    for (auto e : vec_precision)
        precision += e;
    precision /= vec_precision.size();

    double recall = 0;
    for (auto e : vec_recall)
        recall += e;
    recall /= vec_recall.size();

    double score = recall * 0.6 + ndcg * 0.3 + precision * 0.1;

    cout << "recall=" << setprecision(64) << fixed << recall << endl;
    cout << "nDCG=" << setprecision(64) << fixed << ndcg << endl;
    cout << "precision=" << setprecision(64) << fixed << precision << endl;
    cout << "normalizedScore =" << setprecision(64) << fixed << score << endl;
    return (score);
}

int main(int argc, const char *argv[])
{

    srand((unsigned int)time(NULL));

    vector<vector<int>> RecomdList;
    vector<vector<double>> Table;

    //Read Training Data
    string inputName = "";
    inputName += "Train.txt";
    if (!ReadFile(inputName, Table))
    {
        exit(EXIT_FAILURE);
    }

    vector<int> V(K, 0);
    vector<vector<int>> TV(Table.size(), V);
    RecomdList = TV;
    //Main Algorithm
    Algorithm(Table, RecomdList, K, (int)Table.size(), (int)Table[0].size());

    //Read Testing Data
    inputName = "";
    inputName += "Test.txt";
    if (!ReadFile(inputName, Table))
    {
        exit(EXIT_FAILURE);
    }

    //Validation Check
    if (Recommend_Check(RecomdList, K))
        cout << "Illegal List" << endl;
    else
        cout << "Legal List" << endl;


    //Compute Score

    Score(RecomdList, Table);
    system("pause");
    return 0;
}
