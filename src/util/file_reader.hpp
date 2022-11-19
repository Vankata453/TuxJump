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

#ifndef TUXJUMP_UTIL_FILE_READER_HEADER
#define TUXJUMP_UTIL_FILE_READER_HEADER

#include <string>
#include <vector>
#include <map>

class FileReader final
{
public:
  typedef std::map<std::string, std::string> ReaderEntries;

private:
  const std::string m_file;
  ReaderEntries m_entries;

public:
  FileReader(const std::string path);
  ~FileReader();

  const ReaderEntries& get_entries() const { return m_entries; }
  const std::string& get_string(const std::string key) const;

  void get(const std::string key, int& var, int default_val);
  void get(const std::string key, float& var, float default_val);

  std::vector<std::string> read_array(const std::string key, char delimiter = ',') const;
  std::vector<int> read_int_array(const std::string key, char delimiter = ',') const;

private:
  FileReader(const FileReader&) = delete;
  FileReader& operator=(const FileReader&) = delete;
};

#endif