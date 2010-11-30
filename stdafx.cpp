/*
	File:			stdafx.cpp
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

// Initiate other functions
void doClean(std::string &path) {
	std::vector<std::string> flist, fdir;
	std::cout << "Cleaning directory:\t" << path << std::endl
			  << std::endl;
	listDir(path, flist, fdir);
	clean(flist, fdir, path);
}

// Retrieve directory contents via Win32API
void listDir(std::string &path, std::vector<std::string> &flist, std::vector<std::string> &fdir) {
	WIN32_FIND_DATA fdata;
	std::string fpath = path + "\\*";
	HANDLE hlist = FindFirstFile(s2ws(fpath).c_str(), &fdata);
	if (hlist == INVALID_HANDLE_VALUE)
		err("Cannot open path:\t" + path);
	flist.clear(); fdir.clear();
	do {
		if (fdata.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
			fdir.push_back(ws2s(fdata.cFileName));
		else
			flist.push_back(ws2s(fdata.cFileName) + "|" + DtoS(fdata.nFileSizeLow));
	} while(FindNextFile(hlist, &fdata));
	FindClose(hlist);
}

// Do the main cleaning
void clean(std::vector<std::string> &flist, std::vector<std::string> &fdir, std::string &path) {
	std::vector<std::string> fs, fn;
	std::string fname, ext, ff, drive, dir;
	std::size_t dot, tsize, size;
	tsize = 0;
	pExt();
	for (std::vector<std::string>::iterator i = flist.begin(); i != flist.end(); i++) {
		fs.clear();
		fn.clear();
		split(*i, fs, '|');
		ff = fs[0];
		std::istringstream(fs[1]) >> size;
		//split(ff, fn, '.');
		dot = ff.find_last_of('.');
		ext = ff.substr(dot + 1);
		fname = ff.substr(0, dot);
		if ((ext == "gz" || ext == "bz2" || ext == "lzma") && (ff.substr(dot - 3, 3) == "tar")) {
			ext = ff.substr(dot - 3);
			fname = ff.substr(0,dot - 4);
		} else if (ext == "rar" && fname.length() > 7) {
			if (ff.substr(dot - 5, 4) == "part")
				fname = ff.substr(0, dot - 6);
			else if (ff.substr(dot - 6, 4) == "part")
				fname = ff.substr(0, dot - 7);
		}
		if (std::find(exts.begin(), exts.end(), ext) != exts.end()) {
			if (std::find(fdir.begin(), fdir.end(), fname) != fdir.end()) {
				std::cout << "Deleting:\t" << ff << std::endl;
				std::remove((path + "\\" + ff).c_str());
				tsize += size;
			}
		}
	}
	if (tsize > 0) {
		std::cout << std::endl
				  << "Total Estimated Size Deleted: " << (tsize / 1048576) << " MB" << std::endl;
	} else {
		std::cout << std::endl
				  << "Nothing to clean" << std::endl;
	}
}

// Split string
void split(std::string &string, std::vector<std::string> &tokens, const char &delim) {
	std::string ea;
	std::stringstream stream(string);
	while(getline(stream, ea, delim))
		tokens.push_back(ea);
}

// Output error
void err(std::string msg) {
	std::cerr << std::endl
			  << msg << std::endl;
	exit(-1);
}

std::string DtoS(DWORD value) {
    std::stringstream dt;
    dt << value;
    return dt.str();
}

// Ref: http://social.msdn.microsoft.com/Forums/en/Vsexpressvc/thread/0f749fd8-8a43-4580-b54b-fbf964d68375
// std::string to WCHAR
std::wstring s2ws(const std::string& s) { 
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}

// Ref: http://social.msdn.microsoft.com/Forums/en/Vsexpressvc/thread/0f749fd8-8a43-4580-b54b-fbf964d68375
// WCHAR to std::string
std::string ws2s(const std::wstring& s) {
	int len;
	int slength = (int)s.length() + 1;
	len = WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, 0, 0, 0, 0);
	char* buf = new char[len];
	WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, buf, len, 0, 0);
	std::string r(buf);
	delete[] buf;
	return r;
}

// Push valid extensions to vector
void pExt() {
	exts.push_back("7z");
	exts.push_back("s7z");
	exts.push_back("ace");
	exts.push_back("afa");
	exts.push_back("arc");
	exts.push_back("alz");
	exts.push_back("arj");
	exts.push_back("ba");
	exts.push_back("bh");
	exts.push_back("cab");
	exts.push_back("cfs");
	exts.push_back("cpt");
	exts.push_back("dar");
	exts.push_back("dgc");
	exts.push_back("gca");
	exts.push_back("ha");
	exts.push_back("hki");
	exts.push_back("ice");
	exts.push_back("j");
	exts.push_back("kgb");
	exts.push_back("lzh");
	exts.push_back("lha");
	exts.push_back("lzx");
	exts.push_back("partimg");
	exts.push_back("paq6");
	exts.push_back("paq7");
	exts.push_back("paq8");
	exts.push_back("pea");
	exts.push_back("pim");
	exts.push_back("pit");
	exts.push_back("qda");
	exts.push_back("rar");
	exts.push_back("rk");
	exts.push_back("sen");
	exts.push_back("sit");
	exts.push_back("sitx");
	exts.push_back("sqx");
	exts.push_back("tar");
	exts.push_back("gz");
	exts.push_back("bz2");
	exts.push_back("lzma");
	exts.push_back("tar.gz");
	exts.push_back("tar.lzma");
	exts.push_back("tar.bz2");
	exts.push_back("tgz");
	exts.push_back("tbz2");
	exts.push_back("tlz");
	exts.push_back("uca");
	exts.push_back("uha");
	exts.push_back("wim");
	exts.push_back("xar");
	exts.push_back("xp3");
	exts.push_back("yz1");
	exts.push_back("zip");
	exts.push_back("zoo");
	exts.push_back("zz");
}