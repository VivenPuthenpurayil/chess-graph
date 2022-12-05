#include "utils.h"

int SplitString(const std::string & str1, char sep, std::vector<std::string> &fields) {
    std::string str = str1;
    std::string::size_type pos;
    while((pos=str.find(sep)) != std::string::npos) {
        fields.push_back(str.substr(0,pos));
        str.erase(0,pos+1);  
    }
    fields.push_back(str);
    return fields.size();
}

float LinearRegression(const std::vector<float> & x, const std::vector<float> & y) {

    if (x.size() <= 1 || x.size() != y.size())
    {
        return 0;
    }

    int N = x.size();

    float sumX = 0;
    float sumXX = 0;
    float sumY = 0;
    float sumXY = 0;

    float meanY = sumY / N;

    float c0 = 0;
    float c1 = 0;

    for (size_t i = 0; i < (size_t) N; i++) {
        sumX += x[i];
        sumXX += x[i] * x[i];
        sumY += y[i];
        sumXY += x[i] * y[i];
    }

    // Calculate c1
    c1 = (N * sumXY - sumX * sumY) / (N * sumXX - sumX * sumX);

    // Calculate c0
    c0 = (sumY * sumXX - sumX * sumXY) / (N * sumXX - sumX * sumX);

    // Predict = c0 + c1 * value
    // Calculate R2
    float r = 0;
    float m = 0;
    for (size_t i = 0; i < (size_t) N; i++) {
        // Residuals
        r += std::pow((y[i] - (c0 + c1 * x[i])), 2);
        // Mean
        m += std::pow((y[i] - meanY), 2);
    }

    return 1 - r/m;
        

}