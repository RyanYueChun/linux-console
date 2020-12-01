#ifndef CUSTOM_FILE
#define CUSTOM_FILE

#include <string>

class File
{
private:
    std::string name;
    std::string content;
public:
    File(std::string name);
    std::string getName();
    std::string getContent();
    void setContent(std::string content);
};


#endif