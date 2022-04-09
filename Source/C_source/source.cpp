#include "source.h"

//Đọc file csv là file dataset, trả về danh sách các tháng-năm và nhiệt độ 
//tương ứng của tháng đó
vector<pair<Date, double>> ReadCsv(string file_path)
{
    vector<pair<Date, double>> listData;
    string filePath(file_path);
    ifstream input(filePath);
    if (!input)
        cout << "Error: Can't load dataset";

    string line = "";
    while (getline(input, line, ','))
    {
        Date date(line);
        getline(input, line, '\n');
        double temperate = stof(line);
        pair<Date, double> tempOfMonth(date, temperate);
        listData.push_back(tempOfMonth);
    }
    return listData;
}
//Hàm tính nhiệt độ trung bình từ năm beginYear đến năm
//endYear, biến count để tính số tháng (góp phần là số lượng phần tử không gian mẫu)
pair<double, double> CountSAndAVG(vector<pair<Date, double>> listDate,int beginYear, int endYear, int &count)
{
    // Tinh trung binh nhiet do tu nam 1938-1978
    count = 0;
    double sum = 0;
    for (auto i : listDate)
    {
        if(i.first.getYear() < beginYear)
            continue;
        else if (i.first.getYear() < endYear)
        {
            sum += i.second;    
            count++;
        }
        else
            break;
    }
    double AVG = sum / count;
    sum = 0;
    for (auto i : listDate)
    {
        if(i.first.getYear() < beginYear)
            continue;
        else if (i.first.getYear() < endYear)
        {
            sum += (i.second - AVG) * (i.second - AVG);
        }
        else
            break;
    }
    double S = sqrt(sum / (count - 1));
    return pair<double, double>(AVG, S);
}

//Tải lên bảng tra phân phối student với alpha = 0.05
map<int, double> LoadStudentDistribution(string file_path)
{
    map<int, double> StudentDistribution;
    string filePath(file_path);
    ifstream input(filePath);
    if (!input)
        cout << "Khong the load file ";
    string line = "";
    getline(input, line, '\n');
    while (getline(input, line, ','))
    {
        int a = stoi(line);
        getline(input, line, '\n');
        double t = stof(line);
        StudentDistribution.insert(pair<int, double>(a, t));
    }
    return StudentDistribution;
}

// Kiểm định giả thuyết
void Test(double u1, double s1, int n1, double u2, double s2, int n2, map<int, double> StudentDistribution)
{
    // H0: u1<=u2 voi u1 la nhieu do trung binh tu 1978-2018, u2 la nhiet do trung binh tu 1938-1978
    // H1: u1 > u2
    // Buoc 1: Tinh thong ke kiem dinh
    double t0 = (u1 - u2) / (sqrt(s1 * s1 / n1 + s2 * s2 / n2));
    // Buoc 2: Tim v
    double tmp1 = s1 * s1 / n1, tmp2 = s2 * s2 / n2;
    int v = (tmp1 + tmp2) * (tmp1 + tmp2) / (tmp1 * tmp1 / (n1 - 1) + tmp2 * tmp2 / (n2 - 1));
    // Buoc 3: Tim khong ke kiem dinh bang cach tra bang phan phoi student
    double GTQDKD;
    if(StudentDistribution.find(v) == StudentDistribution.end())
        GTQDKD = StudentDistribution[0];
    else{
        GTQDKD = StudentDistribution[StudentDistribution.find(v)->second];
    }
    // Buoc 4: Ket luan
    if(t0>GTQDKD)
        cout << "Nhiet do trung binh tu nam 1978 den 2018 lon hon nhiet do trung binh tu nam 1938 den 1978(Bac bo H0)";
    else
        cout << "Nhiet do trung binh tu nam 1978 den 2018 nho hon hon nhiet do trung binh tu nam 1938 den 1978(Khong bac bo H0)";
}

// Hàm tiền xử lý để kiểm định (Hàm tổng quát)
void Solve()
{
    vector<pair<Date, double>> listDate = ReadCsv(DATASET_FILEPATH);    //Tải dataset lên
    double u1,u2,s1,s2;
    int n1,n2;
    pair<double,double> element1 = CountSAndAVG(listDate,1978,2022,n1); //Tính u1 là nhiệt độ tb 1978-2018 và s1
    pair<double,double> element2 = CountSAndAVG(listDate,1938,1978,n2); //Tính u2 là nhiệt độ tb 1938-1978 và s2
    u1 = element1.first;
    s1 = element1.second;
    u2 = element2.first;
    s2 = element2.second;
    map<int,double> StudentDistribution = LoadStudentDistribution(S_DISTRIBUTE_FILEPATH); // Tải bảng tra phân phối student
    Test(u1,s1,n1,u2,s2,n2,StudentDistribution);    // Kiểm định
}