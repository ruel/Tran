/*
	File:			Tran.cpp
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

#include "stdafx.h"

int main(int argc, const char *argv[]) {
	std::string path;
	std::cout << "Tran 0.1 - Directory Cleaner" << std::endl
			  << "(c) Copyright 2010 Ruel Pagayon <ruel@ruel.me>" << std:: endl
			  << std::endl;
	if (argc > 1) {
		path = argv[1];
	} else {
		std::cout << "Enter Directory Path:\t";
		std::cin >> path;
		std::cin.ignore();
		std::cout << std::endl;
	}
	doClean(path);
}