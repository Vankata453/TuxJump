//  TuxJump
//  Copyright (C) 2022 Vankata453
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef TUXJUMP_UTIL_FILE_WRITER_HEADER
#define TUXJUMP_UTIL_FILE_WRITER_HEADER

#include <string>
#include <vector>
#include <sstream>

#include "game/global.hpp"

// A class to allow writing key-entry structured files.
class FileWriter final
{
private:
  const std::string m_file;
  std::stringstream m_stream;
  const char m_separator;

  // Variables, related to sub-category writing.
  std::stringstream* m_base_stream;
  const std::string m_category;

public:
  FileWriter(const std::string path, const char separator = ' ');
  FileWriter(FileWriter& base, const std::string category);
  ~FileWriter();

  FileWriter for_subcategory(const std::string category);

  // Macro to help write key.
  #define WRITER_WRITE_KEY                                                                            \
    m_stream << (m_category.empty() ? "" : m_category + FILE_CATEGORY_SEPARATOR) << key << m_separator

  template<typename T>
  void write(const std::string key, const T& val)
  {
    WRITER_WRITE_KEY << val << std::endl;
  }

  template<typename T>
  void write_array(const std::string key, const std::vector<T>& arr, char delimiter = ',')
  {
    WRITER_WRITE_KEY;

    const char& newline = std::endl;
    const size_t arr_size = arr.size();
    for (size_t i = 0; i < arr_size; i++)
    {
      m_stream << arr[i] << (i < arr_size - 1 ? delimiter : newline);
    }
  }

  // Get properties
  const std::string& get_file() const { return m_file; }

private:
  FileWriter(const FileWriter&) = delete;
  FileWriter& operator=(const FileWriter&) = delete;
};

#endif
