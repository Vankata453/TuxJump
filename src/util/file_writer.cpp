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

#include "util/file_system.hpp"
#include "util/log.hpp"

// File writer, using a file as a base.
FileWriter::FileWriter(const std::string& path, char separator) :
  m_file(path),
  m_stream(),
  m_separator(separator),
  m_base_stream(),
  m_category()
{
  if (!m_stream) Log::fatal("Cannot open file for writing: " + path);
}

// File writer, using a category in an existing file writer as a base.
FileWriter::FileWriter(FileWriter& base, const std::string& category) :
  m_file(base.get_file()),
  m_stream(),
  m_separator(base.m_separator),
  m_base_stream(&base.m_stream),
  m_category((base.m_category.empty() ? "" : base.m_category + FILE_CATEGORY_SEPARATOR) + category)
{
}

FileWriter::~FileWriter()
{
  if (m_base_stream) // Check if this is a sub-category writer.
    *m_base_stream << m_stream.rdbuf();
  else
    FileSystem::write_file(m_file, m_stream.str());
}


FileWriter
FileWriter::for_subcategory(const std::string& category)
{
  if (category.empty()) Log::fatal("No writer sub-category provided.");

  // Return a new writer, which writes data for a desired sub-category in the current writer.
  return FileWriter(*this, category);
}
