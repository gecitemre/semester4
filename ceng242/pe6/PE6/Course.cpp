#include "Student.h"
#include "Course.h"

// YOU CAN COMPLETELY CHANGE THIS FILE AS YOU NEED. //

vector<vector<Student *>> OpenCourse::opencourses;

/****************************************************/
/****               *** COURSE ***               ****/

/* Constructor : initializes <name> of the object to
   the given string.
*/
Course::Course(string name) : name(name) {}

/* Destructor  : It is NOT responsible of the
   destruction of the prerequisite courses and OpenCourse::students
   who take the course.
*/
Course::~Course() {}

/* Copy constructor : It totally applies shallow copy.
 */
Course::Course(const Course &course)
{
   name = course.name;
   prereqs = course.prereqs;
}

/* This method directly adds (without creating a copy) the
   given course as a prerequisite of the current course.
*/
void Course::addPrerequisite(const Course &course)
{
   prereqs.push_back(&course);
}

/* This method returns the prerequisites of the course.
 */
const vector<const Course *> Course::getPrerequisites() const
{
   return prereqs;
}

/* This method returns the name of the course.
 */
string Course::getName() const
{
   return name;
}

/* == operator overload : This method returns true if
   the two courses have the same name, false otherwise.
*/
bool Course::operator==(const Course &rhs) const
{
   return name == rhs.name;
}

/****************************************************/
/****             *** OPEN COURSE ***            ****/

/* Constructor : initializes the derived members of the
   Course class with the one given as first parameter.
   Also, initializes <term> of the object to the given
   string. Initializes the <course_index> and the <quota>
   to the given last two integers, respectively.

   course_index is the index of the course in the array
   of OpenCourses at Metu.

   quota is the upper limit for the number of OpenCourse::students
   who takes the course.
*/
OpenCourse::OpenCourse(const Course &course, string term, int course_index, int quota) : Course(course), term(term), course_index(course_index), quota(quota) {
   opencourses.push_back(vector<Student *>());
}

/* Destructor  : It is NOT responsible of the
   destruction of the prerequisite courses and OpenCourse::students
   who take the course.
*/
OpenCourse::~OpenCourse() {}

/* Copy constructor : It totally applies shallow copy.
 */
OpenCourse::OpenCourse(const OpenCourse &opencourse) : Course(opencourse), term(opencourse.term), course_index(opencourse.course_index), quota(opencourse.quota) {}

/* This method returns the ids of the OpenCourse::students who take
   the current OpenCourse.
   In order this method to reach the OpenCourse::students, it
   is advised to hold the OpenCourse::students taking the course
   in a "static" array variable.
*/
const vector<int> OpenCourse::showStudentList() const
{
   vector<int> ids;
   for (auto student : opencourses[course_index])
   {
      ids.push_back(student->getId());
   }
   return ids;
}

/* This method calls the gradeCourse() method to grade
   the current OpenCourse for each student who take
   the course.
   In order this method to reach the OpenCourse::students, it
   is advised to hold the OpenCourse::students taking the course
   in a "static" array variable.
*/
void OpenCourse::finalize()
{
   for (auto student : opencourses[course_index])
   {
      student->gradeCourse(*this);
   }
}

/****************************************************/
/****          *** COURSE INSTANCE ***           ****/

/* Constructor : initializes the derived members of the
   OpenCourse class with the one given as first parameter.
   Also, holds the information that the current
   CourseInstance object is owned by which student, by
   using the second parameter.
   HINT: For the related OpenCourse object to reach the
   entire student list, it is recommended to store the
   given student in a "static" array. This way of
   implementation may be beneficial in the other methods
   later.
   This method initializes the grade corresponding to
   this CourseInstance to Grade::NA.
*/
CourseInstance::CourseInstance(const OpenCourse &opencourse, Student &student) : OpenCourse(opencourse), student(student), grade(Grade::NA) {
   opencourses[course_index].push_back(&student);
}

/* Destructor  : It is NOT responsible of the
   destruction of the prerequisite courses and OpenCourse::students
   who take the course.
*/
CourseInstance::~CourseInstance() {}

/* This method saves the given grade value into the
   corresponding class member.
*/
void CourseInstance::setGrade(enum Grade grade)
{
   this->grade = grade;
}

/* This method returns the grade of the CourseInstance.
 */
enum Grade CourseInstance::getGrade() const
{
   return grade;
}