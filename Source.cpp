#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Report
{
protected:
    std::vector<std::string> strings;
public:
    virtual void createReport(char* filepath) = 0;
    virtual void addString(std::string adding)
    {
        strings.push_back(adding);
    };
    virtual ~Report() {};
};

class TxtReport : public Report
{
public:
    void createReport(char* filepath)
    {
        std::ofstream out;
        out.open(filepath);

        for (std::string str : strings)
        {
            out << str << std::endl;
        }

        out.close();
    }
};

class XmlReport : public Report
{
public:
    void createReport(char* filepath)
    {
        std::ofstream out;
        out.open(filepath);

        out << "<?xml version=\"1.0\"?>" << std::endl;
        out << "<DOC>" << std::endl;

        for (std::string str : strings)
        {
            out << "    <LINE>" << str << "</LINE>" << std::endl;
        }

        out << "</DOC>";

        out.close();
    }
};

class JsonReport : public Report
{
public:
    void createReport(char* filepath)
    {
        std::ofstream out;
        out.open(filepath);

        out << "{" << std::endl;

        for (int i = 0; i < strings.size() - 1; i++)
        {
            out << "    \"line" << i << "\": \"" << strings[i] << "\"," << std::endl;
        }

        out << "    \"line" << strings.size() - 1 << "\": \"" << strings[strings.size() - 1] << "\"" << std::endl;

        out << "}";

        out.close();
    }
};

class Factory {
public:
    virtual Report* createReport() = 0;
    virtual ~Factory() {}
};

class TxtFactory : public Factory {
public:
    Report* createReport() { return new TxtReport; }
};

class XmlFactory : public Factory {
public:
    Report* createReport() { return new XmlReport; }
};

class JsonFactory : public Factory {
public:
    Report* createReport() { return new JsonReport; }
};

int main()
{
    TxtFactory* txt_factory = new TxtFactory;
    XmlFactory* xml_factory = new XmlFactory;
    JsonFactory* json_factory = new JsonFactory;

    std::vector<Report*> report_systems;
    report_systems.push_back(txt_factory->createReport());
    report_systems.push_back(xml_factory->createReport());
    report_systems.push_back(json_factory->createReport());

    std::string strs[] = { "first string", "second string", "third string" };

    for (std::string str : strs)
    {
        for (Report* rep : report_systems)
        {
            rep->addString(str);
        }
    }

    report_systems[0]->createReport((char*)"report.txt");
    report_systems[1]->createReport((char*)"report.xml");
    report_systems[2]->createReport((char*)"report.json");
}
