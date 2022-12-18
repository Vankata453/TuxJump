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

#include "util/file_reader.hpp"

#include <fstream>

#include "util/log.hpp"
#include "util/string.hpp"

// File reader, using a file as a base.
FileReader::FileReader(const std::string path, const char separator) :
  m_file(path),
  m_entries()
{
  std::ifstream reader(m_file);
  if (!reader) Log::fatal("Cannot open file for reading: " + m_file);

  // Read all lines of the file, parsing them into key-value entries.
  for (std::string line; std::getline(reader, line);)
  {
    std::string key;
    std::string value;
    bool key_found = false;
    for (char& ch : line)
    {
      if (key_found)
        value += ch;
      else if (ch == separator)
        key_found = true;
      else
        key += ch;
    }

    if (key.empty() || value.empty())
      Log::fatal("Line " + line + " has empty key or value. Use space for separation of key-value.");

    m_entries.insert({ key, value });
  }

  reader.close();
}

// File reader, using a category in an existing file reader as a base.
FileReader::FileReader(const FileReader& base, const std::string category) :
  m_file(base.get_file()),
  m_entries()
{
  for (const auto& entry : base.get_entries())
  {
    // Import all entries that start with the desired category string and an underscore.
    if (StringUtil::starts_with(entry.first, category + "_"))
      m_entries.insert({ entry.first.substr(category.size() + 1), entry.second });
  }
}

FileReader::~FileReader()
{
}


FileReader
FileReader::for_subcategory(const std::string category)
{
  if (category.empty()) Log::fatal("No reader sub-category provided.");

  // Return a new reader, which reads data from a desired sub-category in the current reader.
  return FileReader(*this, category);
}


const std::string&
FileReader::get_string(const std::string& key) const
{
  auto it = m_entries.find(key);
  if (it == m_entries.end())
    Log::fatal("Key \"" + key + "\" not found in file \"" + m_file + "\".");

  return it->second;
}


bool
FileReader::get(const std::string key, std::string& var)
{
  try
  {
    var = get_string(key);
  }
  catch (...)
  {
    return false;
  }
  return true;
}

// Macro to help get string value.
#define READER_GET_STRING_VALUE    \
  std::string val;                 \
  if (!get(key, val)) return false;

bool
FileReader::get(const std::string key, int& var)
{
  READER_GET_STRING_VALUE;
  var = std::stoi(val);
  return true;
}

bool
FileReader::get(const std::string key, float& var)
{
  READER_GET_STRING_VALUE;
  var = std::stof(val);
  return true;
}

bool
FileReader::get(const std::string key, bool& var)
{
  READER_GET_STRING_VALUE;
  var = (val == "1");
  return true;
}


std::vector<std::string>
FileReader::read_array(const std::string key, char delimiter) const
{
  std::string contents = get_string(key);
  std::vector<std::string> result;

  contents += delimiter;
  std::string current;
  for (char& ch : contents)
  {
    if (ch == delimiter)
    {
      result.push_back(current);
      current.clear();
      continue;
    }
    current += ch;
  }

  return result;
}

std::vector<int>
FileReader::read_int_array(const std::string key, char delimiter) const
{
  const std::vector<std::string> string_data = read_array(key, delimiter);
  std::vector<int> result;

  for (const std::string& str : string_data)
    result.push_back(std::stoi(str));

  return result;
}
