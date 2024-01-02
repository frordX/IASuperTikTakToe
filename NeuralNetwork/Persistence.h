#pragma once
#include <vector>
#include <fstream>
#include <filesystem>

class Persistence
{
    static std::string addPrefixPathToFileName(const std::string& filename, bool createDir = false)
    {
        std::string documentsPath;
        char* documentsEnv;
        _dupenv_s(&documentsEnv, nullptr, "USERPROFILE");
        documentsPath = std::filesystem::path(documentsEnv).string();
        free(documentsEnv);
        std::string subfolder = "NJNeuralNetworkPersistence";
        auto fullPath = (std::filesystem::path(documentsPath) / subfolder).string();
        // Create the subfolder if it doesn't exist
        if (!std::filesystem::exists(fullPath)) {
            std::filesystem::create_directory(fullPath);
        }
        return fullPath + "/data.bin";
    }
public:
    // Function to save the vector to a file
    static void saveVectorToFile(const std::vector<std::vector<std::vector<double>>>& data, const std::string& filename)
    {
        auto finalfilename = addPrefixPathToFileName(filename);

        std::ofstream file(finalfilename, std::ios::binary);
        if (!file.is_open()) {
            return;
        }

        for (const auto& innerVec1 : data) {
            for (const auto& innerVec2 : innerVec1) {
                file.write(reinterpret_cast<const char*>(innerVec2.data()), innerVec2.size() * sizeof(double));
            }
        }

        file.close();
    }


    // Function to retrieve the vector from a file
    static std::vector<std::vector<std::vector<double>>> retrieveVectorFromFile(const std::string& filename, size_t numRows, size_t numCols) {
        std::vector<std::vector<std::vector<double>>> result;
        auto fullPath = addPrefixPathToFileName(filename);

        std::ifstream file(fullPath, std::ios::binary);
        if (!file.is_open()) {
            return result;
        }

        std::vector<double> tempVector;
        size_t fileSize = std::filesystem::file_size(fullPath);
        size_t elementsToRead = fileSize / sizeof(double);

        tempVector.resize(elementsToRead);
        file.read(reinterpret_cast<char*>(tempVector.data()), fileSize);

        result = std::vector<std::vector<std::vector<double>>>(numCols, std::vector<std::vector<double>>(numRows, std::vector<double>(numRows)));

        for (size_t i = 0; i < numCols; ++i) {
            for (size_t j = 0; j < numRows; ++j) {
                for (size_t k = 0; k < numRows; ++k) {
                    result[i][j][k] = tempVector[i * numRows * numRows + j * numRows + k];
                }
            }
        }

        file.close();
        return result;
    }
};