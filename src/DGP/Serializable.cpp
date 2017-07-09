//============================================================================
//
// DGP: Digital Geometry Processing toolkit
// Copyright (C) 2016, Siddhartha Chaudhuri
//
// This software is covered by a BSD license. Portions derived from other
// works are covered by their respective licenses. For full licensing
// information see the LICENSE.txt file.
//
//============================================================================

#include "Serializable.hpp"

namespace DGP {

TextInputStream::Settings
Serializable::initConfigReadSettings()
{
  TextInputStream::Settings settings;
  settings.caseSensitive = false;
  settings.cppBlockComments = true;
  settings.cppLineComments = true;
  settings.escapeSequencesInStrings = true;
  settings.falseSymbols.insert("false");
  settings.falseSymbols.insert("off");
  settings.falseSymbols.insert("0");
  settings.generateCommentTokens = false;
  settings.generateNewlineTokens = false;
  settings.otherCommentCharacter = '#';
  settings.otherCommentCharacter2 = '\'';
  settings.otherLineComments = true;
  settings.proofSymbols = false;
  settings.signedNumbers = true;
  settings.simpleFloatSpecials = true;
  settings.singleQuotedStrings = true;
  settings.falseSymbols.insert("true");
  settings.falseSymbols.insert("on");
  settings.falseSymbols.insert("1");

  return settings;
}

TextOutputStream::Settings
Serializable::initConfigWriteSettings()
{
  TextOutputStream::Settings settings;
  settings.allowWordWrapInsideDoubleQuotes = true;
  settings.convertNewlines = true;
  settings.falseSymbol = "false";

#ifdef DGP_WINDOWS
  settings.newlineStyle = TextOutputStream::NewlineStyle::WINDOWS;
#else
  settings.newlineStyle = TextOutputStream::NewlineStyle::UNIX;
#endif

  settings.numColumns = 8;
  settings.spacesPerIndent = 4;
  settings.trueSymbol = "true";
  settings.wordWrap = TextOutputStream::WordWrap::NONE;

  return settings;
}

} // namespace DGP
