// Programmer: Max Goshay
// Programmer's ID: 252053
#include <iostream>
#include "AssociativeArray.h"
#include "DynamicArray.h"
#include "Queue.h"
#include <string>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <cstring>

using namespace std;

struct TermsAndSections{
    string TheTerm = "";
    DynamicArray <string> SectionsInTerm;
    int scount = 0;
};

struct SubjectAndCount {
    string TheSubject;
    int subcount = 0;
};

struct CoursesPerSubjectCodeSTRC{
    string SubjectCode = "";
    DynamicArray <string> CoursesPerSubjectCodeDAL;
    int iterator = 0;
};

struct SectionsPerCourse{
    string Course = "";
    DynamicArray <string> SectionsPerCourse;
    int iterator = 0;
};

void sort(DynamicArray <SubjectAndCount> &SubjectArray, int &subjCount) {
    for (int i = 0; i < subjCount; i++)
    {
        if (SubjectArray[i].TheSubject == "")break;
        for (int j = i + 1; j < subjCount; j++)
        {
            if (SubjectArray[j].TheSubject == "")break;
            if (SubjectArray[j].TheSubject < SubjectArray[i].TheSubject)
                swap(SubjectArray[i], SubjectArray[j]);
        }
    }
    cout << endl;
}

void pushSubject(int& subjCount, string subjectCode, DynamicArray <SubjectAndCount> &SubjectArray)
{
    for (int a = 0; a < subjCount; a++)
    {
        if (subjectCode == SubjectArray[a].TheSubject)
        {
            SubjectArray[a].subcount++;
            return;
        }
    }
    SubjectArray[subjCount].TheSubject = subjectCode;
    SubjectArray[subjCount].subcount++;
    subjCount++;
}

void checkForDuplicateSection(DynamicArray <TermsAndSections> &NonDuplicateArray, DynamicArray <SubjectAndCount> &SubjectArray, int &i, string const &section, int& subjCount, string const & subjectCode, int & dupeCount, int& duplicateValue) {
    for (int j = 0; j <= NonDuplicateArray[i].scount; j++)
    {
        if (section == NonDuplicateArray[i].SectionsInTerm[j])
        {
            dupeCount++;
            return;
        }
    }
    //no dupe... add to array
    NonDuplicateArray[i].SectionsInTerm[NonDuplicateArray[i].scount] = section;
    NonDuplicateArray[i].scount++;
    pushSubject(subjCount, subjectCode, SubjectArray);
    duplicateValue++;
}

void checkForDuplicates(DynamicArray <TermsAndSections> &NonDuplicateArray, DynamicArray <SubjectAndCount> &SubjectArray, string const &section, int& subjCount, string const & subjectCode, int & dupeCount, int &stermCount, string const & term, int& duplicateValue) {
    for (int i = 0; i <= stermCount; i++)
    {
        if (term == NonDuplicateArray[i].TheTerm)
        {
            checkForDuplicateSection(NonDuplicateArray, SubjectArray, i, section, subjCount, subjectCode, dupeCount, duplicateValue);
            return;
        }
    }
    NonDuplicateArray[stermCount].TheTerm = term;
    NonDuplicateArray[stermCount].SectionsInTerm[0] = section;
    NonDuplicateArray[stermCount].scount++;
    stermCount++;
    pushSubject(subjCount, subjectCode, SubjectArray);
    duplicateValue++;
}


void checkForDuplicateCoursesWithinSubject(DynamicArray <TermsAndSections> &NonDuplicateArray, DynamicArray <SubjectAndCount> &SubjectArray, int &i, string const &section, int& subjCount, string const & subjectCode, int & dupeCount, int& duplicateValue) {
    for (int j = 0; j <= NonDuplicateArray[i].scount; j++)
    {
        if (section == NonDuplicateArray[i].SectionsInTerm[j])
        {
            dupeCount++;
            return;
        }
    }
    //no dupe... add to array
    NonDuplicateArray[i].SectionsInTerm[NonDuplicateArray[i].scount] = section;
    NonDuplicateArray[i].scount++;
    pushSubject(subjCount, subjectCode, SubjectArray);
    duplicateValue++;
}

void checkForTheCoursesNumberOfSections (DynamicArray <SectionsPerCourse> & SectionsPerCourseDA, string const &course, string const & section, int & CourseCount,AssociativeArray<int, string>& TheCoursesNumberOfSections) {
    for (int i = 0; i <= CourseCount; i++)
    {
        if (course == SectionsPerCourseDA[i].Course)
        {
            for(int j = 0; j < SectionsPerCourseDA[i].iterator; j++){
                //duplicate course
                if (course == SectionsPerCourseDA[i].SectionsPerCourse[j]){
                    return;}
            }
            int temp = SectionsPerCourseDA[i].iterator;
            SectionsPerCourseDA[i].SectionsPerCourse[temp] = section;
            SectionsPerCourseDA[i].iterator++;
            TheCoursesNumberOfSections[course]++;
            return;
        }
    }
    SectionsPerCourseDA[CourseCount].Course = course;
    SectionsPerCourseDA[CourseCount].SectionsPerCourse[0] = section;
    SectionsPerCourseDA[CourseCount].iterator++;
    CourseCount++;
    TheCoursesNumberOfSections[course]++;
}

void checkForDuplicateCourseWithinSunjectCode (DynamicArray <CoursesPerSubjectCodeSTRC> & CoursesPerSubjectCodeDA, string const &course, string const & subjectCode, int & subjectCodeCount,AssociativeArray<int, string>& TheSubjectCodesNumberOfCourses, AssociativeArray<AssociativeArray<int,string>, string>& SubjectCodesCoursesSections, string const& section) {
    for (int i = 0; i <= subjectCodeCount; i++)
    {
        if (subjectCode == CoursesPerSubjectCodeDA[i].SubjectCode)
        {
            for(int j = 0; j<CoursesPerSubjectCodeDA[i].iterator; j++){
                //duplicate course
                if (course == CoursesPerSubjectCodeDA[i].CoursesPerSubjectCodeDAL[j]){
                    return;}
            }
            int temp = CoursesPerSubjectCodeDA[i].iterator;
            CoursesPerSubjectCodeDA[i].CoursesPerSubjectCodeDAL[temp] = course;
            CoursesPerSubjectCodeDA[i].iterator++;
            TheSubjectCodesNumberOfCourses[subjectCode]++;
            SubjectCodesCoursesSections[subjectCode][course]++;
            return;
        }
    }
    CoursesPerSubjectCodeDA[subjectCodeCount].SubjectCode = subjectCode;
    CoursesPerSubjectCodeDA[subjectCodeCount].CoursesPerSubjectCodeDAL[0] = course;
    CoursesPerSubjectCodeDA[subjectCodeCount].iterator++;
    subjectCodeCount++;
    TheSubjectCodesNumberOfCourses[subjectCode]++;
    SubjectCodesCoursesSections[subjectCode][course]++;
}

int main()
{
    AssociativeArray<AssociativeArray<int,string>, string> SubjectCodesCoursesSections;
  
    
    DynamicArray <TermsAndSections> NonDuplicateArray(100);
    
    AssociativeArray<int, string> TheCoursesNumberOfSections;
    AssociativeArray<int, string> TheSubjectCodesNumberOfCourses;

    DynamicArray <CoursesPerSubjectCodeSTRC> CoursesPerSubjectCodeDA(100);
    int subjectCodeCount = 0;
    DynamicArray <SectionsPerCourse> SectionsPerCourseDA(100);
    int CourseCount = 0;
    
    
    int stermCount = 0;

    DynamicArray <SubjectAndCount> SubjectArray(115);
    int subjCount = 0;

    int dupeCount = 0;
    int count = 0;



    // for parsing the inputfile
    char* token;
    char buf[1000];
    const char* const tab = "\t";

    // open the input file
    ifstream fin;
    fin.open("dvc-schedule.txt");
    if (!fin.good()) throw "I/O error";

    // read the input file
    while (fin.good())
    {
        int duplicateValue = 0;
        // read the line
        string line;
        getline(fin, line);
        strcpy(buf, line.c_str());

        if (buf[0] == 0) continue; // skip blank lines
        //parse the line
        const string term(token = strtok(buf, tab));
        const string section((token = strtok(0, tab)) ? token : "");
        const string course((token = strtok(0, tab)) ? token : "");
        const string instructor((token = strtok(0, tab)) ? token : "");
        const string whenWhere((token = strtok(0, tab)) ? token : "");
        if (course.find('-') == string::npos) continue; // invalid line: no dash in course name
        const string subjectCode(course.begin(), course.begin() + course.find('-'));

        // if I get this far, then it's a valid record
//        cout << term << '|' << section << '|'
//            << course << '|' << instructor << '|'
//            << whenWhere << '|' << subjectCode << endl;

        //        cout << subjectCode << "\t" << course <<"\n";

//first check for duplicate
//then check for how many courses per subject code
////
//        cout << course << " = course \n" << subjectCode << " = subject code \n" <<section << " = sections" << endl;

        checkForDuplicates(NonDuplicateArray, SubjectArray, section, subjCount, subjectCode, dupeCount, stermCount, term, duplicateValue);
        count++;

        if (duplicateValue == 1){
            checkForDuplicateCourseWithinSunjectCode (CoursesPerSubjectCodeDA, course, subjectCode, subjectCodeCount, TheSubjectCodesNumberOfCourses, SubjectCodesCoursesSections, section);
        
            checkForTheCoursesNumberOfSections (SectionsPerCourseDA, course, section, CourseCount,TheCoursesNumberOfSections);

        }
        
    }
    fin.close();

//    sort(SubjectArray, subjCount);
//    outputSubjectsAndTermCounts(subjCount, dupeCount, stermCount, count, SubjectArray);
    Queue<string> SectionsWithinCourses;
    Queue<string> SubjectCodesCourses;
    SubjectCodesCourses   = TheSubjectCodesNumberOfCourses.keys();
    SectionsWithinCourses = TheCoursesNumberOfSections.keys();
    while (!SubjectCodesCourses.empty()){
        cout << SubjectCodesCourses.front() << "\t\t" <<  TheSubjectCodesNumberOfCourses[SubjectCodesCourses.front()] << endl;
        SubjectCodesCourses.pop();
    }
    for (int i = 0; i < 5; i++){
        cout << SectionsWithinCourses.front() << "\t\t" <<  TheCoursesNumberOfSections[SectionsWithinCourses.front()] << endl;
        
        SectionsWithinCourses.pop();
    }
    
 
    cout << SubjectCodesCoursesSections.size() << " number of unique SubjectCodes\n";
    
    return 0;
}
