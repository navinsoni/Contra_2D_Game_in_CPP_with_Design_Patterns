#ifndef PARSEXML__H
#define PARSEXML__H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <expat.h>
using std::map;

using std::cout; using std::endl;
using std::string; 
const int PARSE_BUFSIZE = 128;

class ParseXML {
public:
  ParseXML( const string& fn ) : 
    lastElementTag(),
    lastNonTerminal(),
    filename(fn),
    parser(NULL), 
    nextToLastTag(), 
    lastTag(),
    xmlData()
  { 
  //  parseXML(); 
  }
  virtual ~ParseXML() { XML_ParserFree(parser); }
  virtual void parseXML();

  void displayData() const;

  const map<string, string> getXmlData() const { 
    if ( xmlData.size() == 0 ) {
      throw std::string("xmlData map is empty. Did you call parse()?");
    }
    return xmlData; 
  }

  const string& getLastTag() const { return lastTag; }
  const string& getNextToLastTag() const { return nextToLastTag; }

  float getXmlFloat(const string&) const;
  int getXmlInt(const string&) const;
  const string& getXmlStr(const string&) const;

  static void wrapper4Start(void *data, const char *el, const char **attr);
  static void wrapper4End(void *data, const char *el);
  static void wrapper4Chars(void *data, const char *text, int textlen);

protected:
  virtual void start(const char *el, const char *attr[]);
  virtual void end(const char *) {}
  virtual void chars(const char *text, int textlen);
  void stripTrailWhiteSpace(string&) const;

  string  lastElementTag;
  string  lastNonTerminal;

private:
  const string filename;
  XML_Parser parser;
  char buff[PARSE_BUFSIZE];
  string  nextToLastTag;
  string  lastTag;

  std::map<string, string> xmlData;

  ParseXML& operator=(const ParseXML&);
  ParseXML(const ParseXML&);
};

#endif
