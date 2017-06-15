#include "imports.h"
#include "EntropyCounter.h"
int EntropyCounter::countIntersect(char* filename, int blockSize) 
{

}
int EntropyCounter::count(char* filename, int blockSize) {
    FILE *inputfile;
    fopen_s(&inputfile, filename, "rb");
    if (!inputfile)return 1;
    fseek(inputfile, 0, SEEK_END);
    int size = ftell(inputfile);
    fseek(inputfile, 0, SEEK_SET);
    double pi = 0;
    double P = 0;
    if (blockSize == 8) {
        long long* x = new long long[size];
        fread(x, sizeof(long long), size / blockSize, inputfile);
        std::map<long long, int> mapX;
        for (int i = 0; i < size; i += blockSize)
        {
            if (mapX.find(x[i]) == mapX.end()) mapX.insert(std::pair<long long, int>(x[i], 1));
            else
                mapX.at(x[i])++;
        }
        for (auto it = mapX.begin(); it != mapX.end(); ++it)
        {
            pi = 1.0*it->second / size * blockSize;
            P -= log(pi) / log(blockSize*8.0)*pi;
        }
        std::cout << "Block=" << blockSize << "byte: " << P << "\n";
    }
    else
        if (blockSize == 4) {
            int* x = new int[size];
            fread(x, sizeof(int), size / blockSize, inputfile);
            std::map<int, int> mapX;
            for (int i = 0; i < size; i += blockSize)
            {
                if (mapX.find(x[i]) == mapX.end()) mapX.insert(std::pair<int, int>(x[i], 1));
                else
                    mapX.at(x[i])++;
            }
            for (auto it = mapX.begin(); it != mapX.end(); ++it)
            {
                pi = 1.0*it->second / size * blockSize;
                P -= log(pi) / log(blockSize*8.0)*pi;
            }
            std::cout << "Block=" << blockSize << "byte: " << P << "\n";
        }
        else
            if (blockSize == 2) {
                char* y = new char[size];
                fseek(inputfile, 0, SEEK_SET);
                fread(y, sizeof(char), size, inputfile);
                std::map<char, int> mapY;
                for (int i = 0; i < size; i += blockSize)
                {
                    if (mapY.find(y[i]) == mapY.end()) mapY.insert(std::pair<char, int>(y[i], 1));
                    else
                        mapY.at(y[i])++;
                }
                for (auto it = mapY.begin(); it != mapY.end(); ++it)
                {
                    pi = 1.0*it->second / size * blockSize;
                    P -= log(pi) / log(blockSize*8.0)*pi;
                }
                std::cout << "Block=" << blockSize << "byte: " << P << "\n";
            }
            else
                if (blockSize == 1) {
                    unsigned char* z = new unsigned char[size];
                    fseek(inputfile, 0, SEEK_SET);
                    fread(z, sizeof(unsigned char), size / blockSize, inputfile);
                    std::map<unsigned char, int> mapZ;
                    for (int i = 0; i < size; i++)
                    {
                        if (mapZ.find(z[i]) == mapZ.end()) mapZ.insert(std::pair<unsigned char, int>(z[i], 1));
                        else
                            mapZ.at(z[i])++;
                    }
                    for (auto it = mapZ.begin(); it != mapZ.end(); ++it)
                    {
                        pi = 1.0*it->second / size*blockSize;
                        P -= log(pi) / log(blockSize*8.0)*pi;
                    }
                    std::cout << "Block=" << blockSize << "byte: " << P << "\n";
                };

    return 0;
}


//                    for (int i = 0; i <= size / blockSize; i++)std::cout << (int)z[i] << ' ';