/*
	File:			stdafx.h
	Author:			Ruel Pagayon <ruel@ruel.me>
	Date Created:	November 29, 2010

    This file is part of Tran.

    Tran is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Tran is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Tran.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "targetver.h"

/// Header Files

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <Windows.h>

/// Function Prototypes

void doClean(std::string&);
void listDir(std::string&, std::vector<std::string>&, std::vector<std::string>&);
void clean(std::vector<std::string>&, std::vector<std::string>&, std::string&);
std::wstring s2ws(const std::string&);
std::string ws2s(const std::wstring&);
void err(std::string);
std::string DtoS(DWORD);
void pExt(void);
void split(std::string&, std::vector<std::string>&, const char&);

/// Extension vector

std::vector<std::string> exts;