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
#include <cstddef>

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
//
//bool operator==(AssociativeArray<int,string>& oldArray,AssociativeArray<int,string>& newArray ) {
//    return true;
//}

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
//            SubjectCodesCoursesSections[subjectCode][course]++;
            return;
        }
    }
    CoursesPerSubjectCodeDA[subjectCodeCount].SubjectCode = subjectCode;
    CoursesPerSubjectCodeDA[subjectCodeCount].CoursesPerSubjectCodeDAL[0] = course;
    CoursesPerSubjectCodeDA[subjectCodeCount].iterator++;
    subjectCodeCount++;
    TheSubjectCodesNumberOfCourses[subjectCode]++;
//    SubjectCodesCoursesSections[subjectCode][course]++;
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



    char* token;
    char buf[1000];
    const char* const tab = "\t";

    ifstream fin;
    fin.open("dvc-schedule.txt");
    if (!fin.good()) throw "I/O error";
    while (fin.good())
    {
        int duplicateValue = 0;
        string line;
        getline(fin, line);
        strcpy(buf, line.c_str());

        if (buf[0] == 0) continue;
        const string term(token = strtok(buf, tab));
        const string section((token = strtok(0, tab)) ? token : "");
        const string course((token = strtok(0, tab)) ? token : "");
        const string instructor((token = strtok(0, tab)) ? token : "");
        const string whenWhere((token = strtok(0, tab)) ? token : "");
        if (course.find('-') == string::npos) continue; // invalid line: no dash in course name
        const string subjectCode(course.begin(), course.begin() + course.find('-'));

        checkForDuplicates(NonDuplicateArray, SubjectArray, section, subjCount, subjectCode, dupeCount, stermCount, term, duplicateValue);
        count++;

        if (duplicateValue == 1){
            checkForDuplicateCourseWithinSunjectCode (CoursesPerSubjectCodeDA, course, subjectCode, subjectCodeCount, TheSubjectCodesNumberOfCourses, SubjectCodesCoursesSections, section);
        
            checkForTheCoursesNumberOfSections (SectionsPerCourseDA, course, section, CourseCount,TheCoursesNumberOfSections);

        }
        
    }
    fin.close();

    DynamicArray<SubjectAndCount> Alphabetize;
    Queue<string> SectionsWithinCourses;
    Queue<string> SubjectCodesCourses;
    
//    Queue<string> CoursesSectionsss;
//    Queue<string> SubjectCodesAndCourses;
//    SubjectCodesAndCourses = SubjectCodesCoursesSections.keys();
    
//    while (!SubjectCodesAndCourses.empty()){
//        string subjectCode = SubjectCodesAndCourses.front();
//        cout << subjectCode << endl;
//        CoursesSectionsss = SubjectCodesCoursesSections[subjectCode].keys();
//        while (!CoursesSectionsss.empty()){
//            cout << CoursesSectionsss.front() << endl;
//            CoursesSectionsss.pop();
//        }
//        SubjectCodesAndCourses.pop();
//    }
//
    SubjectCodesCourses   = TheSubjectCodesNumberOfCourses.keys();
    SectionsWithinCourses = TheCoursesNumberOfSections.keys();
    int ijj = 0;
    while (!SubjectCodesCourses.empty()){
        Alphabetize[ijj].TheSubject = SubjectCodesCourses.front();
        Alphabetize[ijj].subcount = TheSubjectCodesNumberOfCourses[SubjectCodesCourses.front()];
        ijj++;
        SubjectCodesCourses.pop();
    }
    while (!SectionsWithinCourses.empty()){
        Alphabetize[ijj].TheSubject = SectionsWithinCourses.front();
        Alphabetize[ijj].subcount = TheCoursesNumberOfSections[SectionsWithinCourses.front()];
        ijj++;
        SectionsWithinCourses.pop();
    }

    sort(Alphabetize, ijj);
    
    for (int i = 0; i < ijj; i++){
        string key ("-");
        if (Alphabetize[i].TheSubject.find(key) != std::string::npos) {
            cout <<  '\t';
            cout << Alphabetize[i].TheSubject << ", " << Alphabetize[i].subcount << " Section(s)\n";
            continue;
        }
        cout << Alphabetize[i].TheSubject << ",\t" << Alphabetize[i].subcount << " Course(s)\n";
    }
    return 0;
}
