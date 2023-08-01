#pragma once

#include <string>
using namespace std;

class User
{
public:
    User(std::string NAME = "", std::string NOTE = "", std::string BDAY = "", std::string QQ = "", std::string TITLE = "", std::string TEL = "", std::string EMAIL = "", std::string ORG = "")
    {
        this->NAME = NAME;
        this->NOTE = NOTE;
        this->BDAY = BDAY;
        this->QQ = QQ;
        this->TITLE = TITLE;
        this->TEL = TEL;
        this->EMAIL = EMAIL;
        this->ORG = ORG;
    }

    void setNAME(std::string NAME) { this->NAME = NAME; }
    void setNOTE(std::string NOTE) { this->NOTE = NOTE; }
    void setBDAY(std::string BDAY) { this->BDAY = BDAY; }
    void setQQ(std::string QQ) { this->QQ = QQ; }
    void setTITLE(std::string TITLE) { this->TITLE = TITLE; }
    void setTEL(std::string TEL) { this->TEL = TEL; }
    void setEMAIL(std::string EMAIL) { this->EMAIL = EMAIL; }
    void setORG(std::string ORG) { this->ORG = ORG; }

    std::string getNAME() const { return this->NAME; }
    std::string getNOTE() const { return this->NOTE; }
    std::string getBDAY() const { return this->BDAY; }
    std::string getQQ() const { return this->QQ; }
    std::string getTITLE() const { return this->TITLE; }
    std::string getTEL() const { return this->TEL; }
    std::string getEMAIL() const { return this->EMAIL; }
    std::string getORG() const { return this->ORG; }

private:
    std::string NAME;
    std::string NOTE;
    std::string BDAY;
    std::string QQ;
    std::string TITLE;
    std::string TEL;
    std::string EMAIL;
    std::string ORG;
};