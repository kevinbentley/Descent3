/*
* Descent 3
* Copyright (C) 2024 Descent Developers
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <filesystem>
#include <vector>
#include <gtest/gtest.h>
#include "cfile.h"

#ifdef __LINUX__

TEST(D3, CFileCaseSensitiveSearch) {
  const std::vector<std::filesystem::path> test_paths = {
      std::filesystem::path("testdir") / "CamelCase.txt",
      std::filesystem::path("testdir") / "lowercase.txt",
      std::filesystem::path("testdir") / "UPPERCASE.TXT",
  };

  char filename[260];
  bool test = cf_FindRealFileNameCaseInsenstive("no-exist-dir", "no-exist-file.txt", filename);
  EXPECT_EQ(test, false);

  auto cwd = std::filesystem::current_path();
  for (auto const &item : test_paths) {
    auto directory = cwd / item.parent_path();
    std::filesystem::path file = item.filename();
    std::string file_lc = item.filename();
    std::transform(file_lc.begin(), file_lc.end(), file_lc.begin(), ::tolower);
    std::string file_uc = item.filename();
    std::transform(file_uc.begin(), file_uc.end(), file_uc.begin(), ::toupper);

    EXPECT_EQ(cf_FindRealFileNameCaseInsenstive(directory, file_lc, filename), true);
    EXPECT_EQ(cf_FindRealFileNameCaseInsenstive(directory, file_uc, filename), true);
    EXPECT_EQ(std::filesystem::path(filename), file);

    EXPECT_EQ(cf_FindRealFileNameCaseInsenstive(std::filesystem::path(), directory / file_lc, filename), true);
    EXPECT_EQ(cf_FindRealFileNameCaseInsenstive(std::filesystem::path(), directory / file_uc, filename), true);
    EXPECT_EQ(std::filesystem::path(filename), file);

  }
}
#endif // __LINUX__
