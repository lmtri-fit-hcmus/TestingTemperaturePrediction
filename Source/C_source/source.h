#ifndef __SOURCE_H__
#define __SOURCE_H__
#include"Date.h"
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<math.h>
#include<map>
using namespace std;

const double alpha = 0.05;  //Muc y nghia 0.1 
//Duong dan toi file phan phoi student
const string S_DISTRIBUTE_FILEPATH = "Data/StudentDistribution.csv";
//Duong dan toi file dataset
const string DATASET_FILEPATH = "Data/TAVG_Dataset.csv";

vector<pair<Date,double>> ReadCsv(string file_path);    //Doc tap tin csv de lay ra ngay thang
pair<double, double> CountSAndAVG(vector<pair<Date, double>> listDate,int beginYear, int endYear, int &count); //Tinh nhiet do trung binh tu nam beginYear toi năm endYear
map<int,double> LoadStudentDistribution(string file_path);  //Ham load vao bang phan phoi student
void Test(double u1, double s1, int n1, double u2, double s2, int n2, map<int, double> StudentDistribution);  // Ham kiem dinh cac gia thuyet
void Solve();  //Ham xu ly tong quat
#endif





