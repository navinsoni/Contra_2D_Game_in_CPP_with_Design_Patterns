#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <expat.h>
#include "parseXML.h"

class ParseLsysXML : public ParseXML {
public:
  ParseLsysXML(const std::string& fn) : 
    ParseXML(fn),
    grammar()
  { }

  const std::multimap<char, std::string> getGrammar() const { 
    return grammar; 
  }

  static void wrapper4Start(void *data, const char *el, const char **attr);
  static void wrapper4End(void *data, const char *el);
  static void wrapper4Chars(void *data, const char *text, int textlen);

private:
  std::multimap<char, std::string> grammar;

  virtual void start(const char *el, const char *attr[]);
  virtual void end(const char *) {}
  virtual void chars(const char *text, int textlen);

  ParseLsysXML& operator=(const ParseLsysXML&);
  ParseLsysXML(const ParseLsysXML&);
};

