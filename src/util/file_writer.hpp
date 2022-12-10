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
#include <fstream>

// A class to allow writing key-entry structured files.
class FileWriter final
{
private:
  std::ofstream m_stream;
  const char m_separator;

public:
  FileWriter(const std::string path, const char separator = ' ');
  ~FileWriter();

  template<typename T>
  void write(const std::string key, const T& val)
  {
    m_stream << key << m_separator << val << std::endl;
  }

  template<typename T>
  void write_array(const std::string key, const std::vector<T>& arr, char delimiter = ',')
  {
    m_stream << key << m_separator;

    const char& newline = std::endl;
    const size_t arr_size = arr.size();
    for (size_t i = 0; i < arr_size; i++)
    {
      m_stream << arr[i] << (i < arr_size - 1 ? delimiter : newline);
    }
  }

private:
  FileWriter(const FileWriter&) = delete;
  FileWriter& operator=(const FileWriter&) = delete;
};

#endif
