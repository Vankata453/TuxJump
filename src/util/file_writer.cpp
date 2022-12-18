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

#include "util/file_writer.hpp"

#include "util/log.hpp"

// File writer, using a file as a base.
FileWriter::FileWriter(const std::string path, const char separator) :
  m_file(path),
  m_stream(m_file),
  m_separator(separator),
  m_category()
{
  if (!m_stream) Log::fatal("Cannot open file for writing: " + path);
}

// File writer, using a category in an existing file writer as a base.
FileWriter::FileWriter(const FileWriter& base, const std::string category) :
  m_file(base.get_file()),
  m_stream(m_file),
  m_separator(base.get_separator()),
  m_category(category)
{
}

FileWriter::~FileWriter()
{
  m_stream.close();
}


FileWriter
FileWriter::for_subcategory(const std::string category)
{
  if (category.empty()) Log::fatal("No writer sub-category provided.");

  // Return a new writer, which writes data for a desired sub-category in the current writer.
  return FileWriter(*this, category);
}
