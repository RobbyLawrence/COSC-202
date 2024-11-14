/* Name: Robert Lawrence
 *
 * 
 *
 *
 * */
#include "pgm.hpp"
#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>

// method to read in a .pgm file
bool Pgm::Read(const std::string &file) {
    std::ifstream ifs(file);
    if (!ifs) {
        return false;  // Return false if file can't be opened
    }

    std::string dummy;
    size_t width, height, max_val;
    // collect values from file
    ifs >> dummy >> width >> height >> max_val;

    // Check if the file format is correct (P2) and max value is 255
    if (dummy != "P2" || max_val != 255) {
        return false;
    }
    // get the correct height
    Pixels.resize(height);
    // load Pixels
    for (size_t i = 0; i < height; ++i) {
        // get the correct width for each sub-vector
        Pixels[i].resize(width);
        for (size_t j = 0; j < width; ++j) {
            ifs >> Pixels[i][j];
            // Ensure each pixel value is within the valid range
            if (Pixels[i][j] > 255) {
                return false;
            }
        }
    }

    return true;
}

bool Pgm::Write(const std::string &file) const {
    // check if there's data to write
    if (Pixels.empty() || Pixels[0].empty()) {
        return false;
    }

    std::ofstream ofs(file);
    if (!ofs) {
        return false;  // return false if file can't be opened for writing
    }

    // write the PGM header
    ofs << "P2\n";
    ofs << Pixels[0].size() << " " << Pixels.size() << "\n";
    ofs << "255\n";
    
    // initialize variables
    size_t count = 0;
    size_t total_pixels = Pixels.size() * Pixels[0].size();
    size_t pixels_written = 0;

    // write pixel values, 20 per line
    for (size_t i = 0; i < Pixels.size(); ++i) {
        for (size_t j = 0; j < Pixels[i].size(); ++j) {
            ofs << Pixels[i][j];
            ++pixels_written;
            ++count;

            // add newline after 20 pixels or at the end of the image
            if (count == 20 || pixels_written == total_pixels) {
                ofs << "\n";
                count = 0;
            } else {
                ofs << " ";  // add space between pixels, but not at the end of a line
            }
        }
    }
    return true;
}

bool Pgm::Create(size_t r, size_t c, size_t pv) {
    // check if the pixel value is within the valid range
    if (pv > 255) {
        return false;
    }
    // clear existing data and create a new image with correct dimensions and pixel values
    Pixels.clear();
    Pixels.resize(r, std::vector<int>(c, pv));
    return true;
}

bool Pgm::Clockwise() {
    // check if Pixels is empty 
    if (Pixels.empty() || Pixels[0].empty()) {
        return false;
    }

    // create a new vector to store the rotated image
    std::vector<std::vector<int> > rotated(Pixels[0].size(), std::vector<int>(Pixels.size()));

    // Perform 90-degree clockwise rotation
    for (size_t i = 0; i < Pixels.size(); ++i) {
        for (size_t j = 0; j < Pixels[0].size(); ++j) {
            rotated[j][Pixels.size() - 1 - i] = Pixels[i][j];
        }
    }
    // assign Pixels to the vector that got turned
    Pixels = rotated;
    return true;
}

bool Pgm::Cclockwise() {
    // check if Pixels is empty
    if (Pixels.empty() || Pixels[0].empty()) {
        return false;
    }

    // create a new vector to store the rotated image
    std::vector<std::vector<int> > rotated(Pixels[0].size(), std::vector<int>(Pixels.size()));

    // perform the 90-degree counter-clockwise rotation
    for (size_t i = 0; i < Pixels.size(); ++i) {
        for (size_t j = 0; j < Pixels[0].size(); ++j) {
            rotated[Pixels[0].size() - 1 - j][i] = Pixels[i][j];
        }
    }
    // assign Pixels to the vector that turned
    Pixels = rotated;
    return true;
}

bool Pgm::Pad(size_t w, size_t pv) {
    // check if the pixel value is valid and Pixels is nonempty
    if (pv > 255 || Pixels.empty() || Pixels[0].empty()) {
        return false;
    }
    // initialize variables
    size_t new_height = Pixels.size() + 2 * w;
    size_t new_width = Pixels[0].size() + 2 * w;

    // create a new padded vector filled with the padding value
    std::vector<std::vector<int> > padded(new_height, std::vector<int>(new_width, pv));

    // copy Pixels into the center of the padded vector
    for (size_t i = 0; i < Pixels.size(); ++i) {
        for (size_t j = 0; j < Pixels[0].size(); ++j) {
            padded[i + w][j + w] = Pixels[i][j];
        }
    }
    // assign Pixels to new vector
    Pixels = padded;
    return true;
}

bool Pgm::Panel(size_t r, size_t c) {
    // check if the parameters are valid and make sure that Pixels is nonempty
    if (r == 0 || c == 0 || Pixels.empty() || Pixels[0].empty()) {
        return false;
    }
    // initialize variables
    size_t orig_height = Pixels.size();
    size_t orig_width = Pixels[0].size();

    // create a new vector for the paneled image
    std::vector<std::vector<int> > paneled(orig_height * r, std::vector<int>(orig_width * c));

    // copy Pixels r*c times into the paneled image
    for (size_t i = 0; i < r; ++i) {
        for (size_t j = 0; j < c; ++j) {
            for (size_t y = 0; y < orig_height; ++y) {
                for (size_t x = 0; x < orig_width; ++x) {
                    paneled[i * orig_height + y][j * orig_width + x] = Pixels[y][x];
                }
            }
        }
    }
    // assign Pixels to the paneled vector
    Pixels = paneled;
    return true;
}

bool Pgm::Crop(size_t r, size_t c, size_t rows, size_t cols) {
    // check if the crop parameters are valid
    if (r + rows > Pixels.size() || c + cols > Pixels[0].size()) {
        return false;
    }

    // create a new vector to store the cropped image
    std::vector<std::vector<int> > cropped(rows, std::vector<int>(cols));

    // copy the specified region into the cropped image
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            cropped[i][j] = Pixels[r + i][c + j];
        }
    }
    // assign Pixels to the cropped region vector
    Pixels = cropped;
    return true;
}
