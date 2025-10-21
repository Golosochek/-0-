#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <random>
#include <algorithm>
#include <cmath>
#include <functional>

// Подключаем windows.h после всех остальных заголовков и отключаем макросы min/max
#define NOMINMAX
#include <windows.h>

class PGMImage {
private:
    std::vector<std::vector<int>> pixels;
    int width, height;
    int maxVal;
    std::string magicNumber;

public:
    PGMImage() : width(0), height(0), maxVal(255) {}
    
    bool load(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Cannot open file: " << filename << std::endl;
            return false;
        }
        
        file >> magicNumber;
        if (magicNumber != "P2" && magicNumber != "P5") {
            std::cerr << "Unsupported PGM format: " << magicNumber << std::endl;
            return false;
        }
        
        file >> width >> height >> maxVal;
        pixels.resize(height, std::vector<int>(width));
        
        if (magicNumber == "P2") {
            for (int i = 0; i < height; ++i) {
                for (int j = 0; j < width; ++j) {
                    file >> pixels[i][j];
                }
            }
        } else {
            file.get();
            for (int i = 0; i < height; ++i) {
                for (int j = 0; j < width; ++j) {
                    unsigned char pixel;
                    file.read(reinterpret_cast<char*>(&pixel), 1);
                    pixels[i][j] = static_cast<int>(pixel);
                }
            }
        }
        
        file.close();
        return true;
    }
    
    bool save(const std::string& filename, bool binary = false) {
        std::ofstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Cannot create file: " << filename << std::endl;
            return false;
        }
        
        if (binary) {
            file << "P5\n";
        } else {
            file << "P2\n";
        }
        
        file << width << " " << height << "\n" << maxVal << "\n";
        
        if (binary) {
            for (int i = 0; i < height; ++i) {
                for (int j = 0; j < width; ++j) {
                    unsigned char pixel = static_cast<unsigned char>(
                        (std::min)((std::max)(pixels[i][j], 0), 255));
                    file.write(reinterpret_cast<char*>(&pixel), 1);
                }
            }
        } else {
            for (int i = 0; i < height; ++i) {
                for (int j = 0; j < width; ++j) {
                    file << pixels[i][j] << " ";
                }
                file << "\n";
            }
        }
        
        file.close();
        return true;
    }
    
    void addSaltPepperNoise(double noiseLevel) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.0, 1.0);
        
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (dis(gen) < noiseLevel) {
                    pixels[i][j] = (dis(gen) < 0.5) ? 0 : maxVal;
                }
            }
        }
    }
    
    void addGaussianNoise(double sigma) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<> dis(0.0, sigma);
        
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                int newVal = pixels[i][j] + static_cast<int>(dis(gen));
                pixels[i][j] = (std::min)((std::max)(newVal, 0), maxVal);
            }
        }
    }
    
    void applyMedianFilter(int kernelSize = 3) {
        std::vector<std::vector<int>> result = pixels;
        int offset = kernelSize / 2;
        
        for (int i = offset; i < height - offset; ++i) {
            for (int j = offset; j < width - offset; ++j) {
                std::vector<int> window;
                for (int ki = -offset; ki <= offset; ++ki) {
                    for (int kj = -offset; kj <= offset; ++kj) {
                        window.push_back(pixels[i + ki][j + kj]);
                    }
                }
                std::sort(window.begin(), window.end());
                result[i][j] = window[window.size() / 2];
            }
        }
        pixels = result;
    }
    
    void applyMeanFilter(int kernelSize = 3) {
        std::vector<std::vector<int>> result = pixels;
        int offset = kernelSize / 2;
        
        for (int i = offset; i < height - offset; ++i) {
            for (int j = offset; j < width - offset; ++j) {
                int sum = 0;
                for (int ki = -offset; ki <= offset; ++ki) {
                    for (int kj = -offset; kj <= offset; ++kj) {
                        sum += pixels[i + ki][j + kj];
                    }
                }
                result[i][j] = sum / (kernelSize * kernelSize);
            }
        }
        pixels = result;
    }
    
    void applyGaussianFilter(int kernelSize = 3, double sigma = 1.0) {
        std::vector<std::vector<int>> result = pixels;
        int offset = kernelSize / 2;
        
        std::vector<std::vector<double>> kernel(kernelSize, std::vector<double>(kernelSize));
        double sum = 0.0;
        
        for (int i = -offset; i <= offset; ++i) {
            for (int j = -offset; j <= offset; ++j) {
                double value = exp(-(i*i + j*j) / (2 * sigma * sigma));
                kernel[i + offset][j + offset] = value;
                sum += value;
            }
        }
        
        for (int i = 0; i < kernelSize; ++i) {
            for (int j = 0; j < kernelSize; ++j) {
                kernel[i][j] /= sum;
            }
        }
        
        for (int i = offset; i < height - offset; ++i) {
            for (int j = offset; j < width - offset; ++j) {
                double filtered = 0.0;
                for (int ki = -offset; ki <= offset; ++ki) {
                    for (int kj = -offset; kj <= offset; ++kj) {
                        filtered += pixels[i + ki][j + kj] * kernel[ki + offset][kj + offset];
                    }
                }
                result[i][j] = static_cast<int>(filtered);
            }
        }
        pixels = result;
    }
    
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    
    int getPixel(int x, int y) const { 
        if (y >= 0 && y < height && x >= 0 && x < width) {
            return pixels[y][x]; 
        }
        return 0;
    }
    
    void setPixel(int x, int y, int value) { 
        if (y >= 0 && y < height && x >= 0 && x < width) {
            pixels[y][x] = (std::min)((std::max)(value, 0), maxVal); 
        }
    }
};

class ImageComparator {
public:
    static double calculateMSE(const PGMImage& img1, const PGMImage& img2) {
        if (img1.getWidth() != img2.getWidth() || img1.getHeight() != img2.getHeight()) {
            return -1.0;
        }
        
        double mse = 0.0;
        int width = img1.getWidth();
        int height = img1.getHeight();
        
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                int diff = img1.getPixel(x, y) - img2.getPixel(x, y);
                mse += diff * diff;
            }
        }
        
        return mse / (width * height);
    }
    
    static double calculatePSNR(const PGMImage& img1, const PGMImage& img2) {
        double mse = calculateMSE(img1, img2);
        if (mse <= 0.0 || std::isnan(mse) || std::isinf(mse)) return 0.0;
        double psnr = 10.0 * log10(255.0 * 255.0 / mse);
        return (std::isnan(psnr) || std::isinf(psnr)) ? 0.0 : psnr;
    }
    
    static double calculateSSIM(const PGMImage& img1, const PGMImage& img2) {
        if (img1.getWidth() != img2.getWidth() || img1.getHeight() != img2.getHeight()) {
            return -1.0;
        }
        
        int width = img1.getWidth();
        int height = img1.getHeight();
        
        double mean1 = 0.0, mean2 = 0.0;
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                mean1 += img1.getPixel(x, y);
                mean2 += img2.getPixel(x, y);
            }
        }
        mean1 /= (width * height);
        mean2 /= (width * height);
        
        // Если изображения идентичные, возвращаем 1.0
        if (mean1 == mean2 && mean1 == 0) {
            return 1.0;
        }
        
        double var1 = 0.0, var2 = 0.0, covar = 0.0;
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                double diff1 = img1.getPixel(x, y) - mean1;
                double diff2 = img2.getPixel(x, y) - mean2;
                var1 += diff1 * diff1;
                var2 += diff2 * diff2;
                covar += diff1 * diff2;
            }
        }
        var1 /= (width * height - 1);
        var2 /= (width * height - 1);
        covar /= (width * height - 1);
        
        const double C1 = 6.5025, C2 = 58.5225;
        
        double numerator = (2 * mean1 * mean2 + C1) * (2 * covar + C2);
        double denominator = (mean1 * mean1 + mean2 * mean2 + C1) * (var1 + var2 + C2);
        
        if (denominator == 0.0) {
            return 1.0; // Если знаменатель 0, изображения идентичны
        }
        
        double ssim = numerator / denominator;
        return (std::isnan(ssim) || std::isinf(ssim)) ? 1.0 : ssim;
    }
    
    // Функция для безопасного вывода чисел (заменяет NaN на 0)
    static double safeValue(double value) {
        if (std::isnan(value) || std::isinf(value)) {
            return 0.0;
        }
        return value;
    }
};

// Функция для создания директории
bool createDirectory(const std::string& path) {
    DWORD fileAttributes = GetFileAttributesA(path.c_str());
    if (fileAttributes == INVALID_FILE_ATTRIBUTES) {
        // Директория не существует, создаем
        return CreateDirectoryA(path.c_str(), NULL) != 0;
    } else if (fileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
        // Директория уже существует
        return true;
    } else {
        // Путь существует, но это не директория
        return false;
    }
}

// Функция для получения списка файлов в директории
std::vector<std::string> getFilesInDirectory(const std::string& directory) {
    std::vector<std::string> files;
    std::string searchPath = directory + "\\*.pgm";
    
    WIN32_FIND_DATAA findFileData;
    HANDLE hFind = FindFirstFileA(searchPath.c_str(), &findFileData);
    
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                files.push_back(directory + "\\" + std::string(findFileData.cFileName));
            }
        } while (FindNextFileA(hFind, &findFileData) != 0);
        FindClose(hFind);
    }
    return files;
}

void processAllImages(const std::string& inputDir, const std::string& outputDir) {
    std::ofstream csvFile(outputDir + "\\results.csv");
    csvFile << "Image,NoiseType,FilterType,MSE,PSNR,SSIM\n";
    
    using FilterFunction = std::function<void(PGMImage&)>;
    std::vector<std::pair<std::string, FilterFunction>> filters = {
        {"Median3", [](PGMImage& img) { img.applyMedianFilter(3); }},
        {"Median5", [](PGMImage& img) { img.applyMedianFilter(5); }},
        {"Mean3", [](PGMImage& img) { img.applyMeanFilter(3); }},
        {"Mean5", [](PGMImage& img) { img.applyMeanFilter(5); }},
        {"Gaussian3", [](PGMImage& img) { img.applyGaussianFilter(3, 1.0); }},
        {"Gaussian5", [](PGMImage& img) { img.applyGaussianFilter(5, 1.5); }}
    };
    
    std::vector<std::string> imageFiles = getFilesInDirectory(inputDir);
    
    if (imageFiles.empty()) {
        std::cout << "No PGM files found in directory: " << inputDir << std::endl;
        return;
    }
    
    for (const auto& filepath : imageFiles) {
        size_t lastSlash = filepath.find_last_of("\\/");
        std::string filenameWithExt = (lastSlash == std::string::npos) ? filepath : filepath.substr(lastSlash + 1);
        std::string filename = filenameWithExt.substr(0, filenameWithExt.length() - 4);
        
        std::cout << "Processing: " << filename << std::endl;
        
        PGMImage original;
        if (!original.load(filepath)) {
            std::cout << "Failed to load: " << filepath << std::endl;
            continue;
        }
        
        std::vector<std::pair<std::string, double>> noiseTypes = {
            {"SaltPepper_0.05", 0.05},
            {"SaltPepper_0.1", 0.1},
            {"Gaussian_10", 10.0},
            {"Gaussian_20", 20.0}
        };
        
        for (const auto& noise : noiseTypes) {
            PGMImage noisy = original;
            
            if (noise.first.find("SaltPepper") != std::string::npos) {
                noisy.addSaltPepperNoise(noise.second);
            } else {
                noisy.addGaussianNoise(noise.second);
            }
            
            noisy.save(outputDir + "\\" + filename + "_" + noise.first + ".pgm");
            
            for (const auto& filter : filters) {
                PGMImage filtered = noisy;
                filter.second(filtered);
                
                std::string outputFilename = outputDir + "\\" + filename + "_" + 
                                           noise.first + "_" + filter.first + ".pgm";
                filtered.save(outputFilename);
                
                double mse = ImageComparator::calculateMSE(original, filtered);
                double psnr = ImageComparator::calculatePSNR(original, filtered);
                double ssim = ImageComparator::calculateSSIM(original, filtered);
                
                // Используем безопасные значения (заменяем NaN на 0)
                double safe_mse = ImageComparator::safeValue(mse);
                double safe_psnr = ImageComparator::safeValue(psnr);
                double safe_ssim = ImageComparator::safeValue(ssim);
                
                csvFile << filename << "," << noise.first << "," << filter.first << ","
                       << safe_mse << "," << safe_psnr << "," << safe_ssim << "\n";
                
                std::cout << "  " << noise.first << " + " << filter.first 
                          << " - MSE: " << safe_mse << ", PSNR: " << safe_psnr 
                          << ", SSIM: " << safe_ssim << std::endl;
            }
        }
    }
    
    csvFile.close();
}

int main() {
    std::string inputDir = "images";
    std::string outputDir = "output";
    
    if (!createDirectory(inputDir)) {
        std::cout << "Warning: Could not create input directory" << std::endl;
    }
    if (!createDirectory(outputDir)) {
        std::cout << "Warning: Could not create output directory" << std::endl;
    }
    
    std::cout << "Image Denoising Program" << std::endl;
    std::cout << "Place your PGM images in the 'images' folder" << std::endl;
    std::cout << "Results will be saved in the 'output' folder" << std::endl;
    
    processAllImages(inputDir, outputDir);
    
    std::cout << "Processing complete! Check 'output/results.csv' for detailed results." << std::endl;
    
    return 0;
}