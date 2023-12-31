/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *   Copyright (C) 2006-2008 by Jim Pattee <jimp03@email.com>
 *   Copyright (C) 1998-2002 by Tal Davidson
 *   <http://www.gnu.org/licenses/lgpl-3.0.html>
 *
 *   This file is a part of Artistic Style - an indentation and
 *   reformatting tool for C, C++, C# and Java source files.
 *   <http://astyle.sourceforge.net>
 *
 *   Artistic Style is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU Lesser General Public License as published
 *   by the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Artistic Style is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public License
 *   along with Artistic Style.  If not, see <http://www.gnu.org/licenses/>.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */


#ifndef ASSTREAMITERATOR_H
#define ASSTREAMITERATOR_H

#include "astyle.h"
#include <iostream>

namespace astyle
{

class ASStreamIterator : virtual public ASSourceIterator
{
	public:
		bool checkForEmptyLine;

		// function declarations
		ASStreamIterator(std::istream *in, unsigned char extraEOFChar=255);
		virtual ~ASStreamIterator();
		std::string nextLine(bool emptyLineWasDeleted);
		std::string peekNextLine();
		void peekReset();
		void saveLastInputLine();

		// inline functions
		bool compareToInputBuffer(const std::string &nextLine) const { return nextLine == prevBuffer; }
		const char* getOutputEOL() const { return outputEOL; }
		bool hasMoreLines() const;

		int getStreamLength() const { return 0; }
		std::streamoff tellg() { return 0; }

        std::streamoff getPeekStart() const  { return 0; }

	private:
		std::istream * inStream;          // pointer to the input stream
		std::string buffer;         // current input line
		std::string prevBuffer;     // previous input line
		unsigned char extraEOFChar=255; //Additional EOF char that will signal a file done on STDIN
		int eolWindows;        // number of Windows line endings (CRLF)
		int eolLinux;          // number of Linux line endings (LF)
		int eolMacOld;         // number of old Mac line endings (CR)
		int peekStart;         // starting position for peekNextLine()
		char outputEOL[4];     // output end of line char
		bool prevLineDeleted;  // the previous input line was deleted
		bool AtEnd(char c=-1) const;
};

}

#endif
