#pragma once

#include <string>
#include <vector>

class TextBufferInterface {
public:
  // "virtual" to enforce derived destructors to be called when pointer-to-base used
  // "= default" to not enforce destructor implementation in derived classes
  virtual ~TextBufferInterface() = default;

  virtual void InsertText(const std::pair<std::size_t, std::size_t> position, const std::string& text)     = 0;
  virtual void InsertText(const std::size_t rowIndex, const std::size_t colIndex, const std::string& text) = 0;

  virtual void DeleteText(const std::pair<std::size_t, std::size_t> position, const std::size_t length)     = 0;
  virtual void DeleteText(const std::size_t rowIndex, const std::size_t colIndex, const std::size_t length) = 0;

  virtual void ReplaceText(const std::pair<std::size_t, std::size_t> position,
                           const std::size_t                         length,
                           const std::string&                        text) = 0;
  virtual void ReplaceText(const std::size_t  rowIndex,
                           const std::size_t  colIndex,
                           const std::size_t  length,
                           const std::string& text) = 0;

  virtual void InsertLine(const std::size_t rowIndex, const std::string& line)  = 0;
  virtual void DeleteLine(const std::size_t rowIndex)                           = 0;
  virtual void ReplaceLine(const std::size_t rowIndex, const std::string& line) = 0;

  virtual std::size_t              GetNumberOfLines() const                        = 0;
  virtual std::size_t              GetLineLength(const std::size_t rowIndex) const = 0;
  virtual std::string              GetLine(const std::size_t rowIndex) const       = 0;
  virtual std::vector<std::string> GetTextBuffer() const                           = 0;
  virtual void                     ClearTextBuffer()                               = 0;
};
