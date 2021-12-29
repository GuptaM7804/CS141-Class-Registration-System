/*main.cpp*/

//
// Author: Manav Gupta
//
// An intro to ClassReg class, and project 06.
//
// Date: 30th April 2021
//

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

#include "classreg.h"

using namespace std;

// list of all functions used
void inputFromFile(ifstream& infile, ClassReg& classreg, string classname, int capacity);
void inputClassData(ifstream& infile, ClassReg& cs111, ClassReg& cs141, ClassReg& cs151, ClassReg& cs211, ClassReg& cs251);
void printHelp();
void printNAME(ClassReg classreg);
void printInfo(ClassReg cs111, ClassReg cs141, ClassReg cs151, ClassReg cs211, ClassReg cs251);
void sortedNames(string array[], int cap);
string* Array(ClassReg classname, int cap);
void printList(ClassReg classname);
void increaseCap(ClassReg& classname, int capacity);
void enroll(ClassReg& classname, string netID);
void waitlist(ClassReg& classname, int priority, string netID);
void outputToFile(ofstream& outfile, ClassReg classname);
void printCommand(string classname, ClassReg& cs111, ClassReg& cs141, ClassReg& cs151, ClassReg& cs211, ClassReg& cs251);
void printIncrease(string classname, int capacity, ClassReg& cs111, ClassReg& cs141, ClassReg& cs151, ClassReg& cs211, ClassReg& cs251);
void printEnroll(string classname, string netID, ClassReg& cs111, ClassReg& cs141, ClassReg& cs151, ClassReg& cs211, ClassReg& cs251);
void printWaitlist(string classname, int prio, string netID, ClassReg& cs111, ClassReg& cs141, ClassReg& cs151, ClassReg& cs211, ClassReg& cs251);
void outputTheFile(string outputFile, ClassReg cs111, ClassReg cs141, ClassReg cs151, ClassReg cs211, ClassReg cs251);
void printCommand(string classname, ClassReg& cs111, ClassReg& cs141, ClassReg& cs151, ClassReg& cs211, ClassReg& cs251);

//
// input information given in the parameters to the given ClassReg object from the given input filename
//
void inputFromFile(ifstream& infile, ClassReg& classreg, string classname, int capacity)
{
    classreg.setName(classname); // object's name is set
    classreg.setCapacity(capacity); // object's capacity is set
    string enrollName;
    infile >> enrollName; // get netid from the file of students to be enrolled
    while(enrollName != "#") // while "#" isn't inputted from the file (stop enrolling mark)...
    {
        classreg.enrollStudent(enrollName); // keep enrolling
        infile >> enrollName; // keep getting netids from the file
    }
    string waitlistName;
    int prio;
    infile >> waitlistName; // get netid from the file of students to be waitlisted
    while (waitlistName != "#") // while "#" isn't inputted from the file (stop waitlisting mark)...
    {
        infile >> prio; // get the priority of that student...... keep getting priority
        classreg.waitlistStudent(waitlistName, prio); // keep waitlisting
        infile >> waitlistName; // keep getting the netids
    }
}

//
// inputs the data from the file into each of the class objects
//
void inputClassData(ifstream& infile, ClassReg& cs111, ClassReg& cs141, ClassReg& cs151, ClassReg& cs211, ClassReg& cs251)
{
    string classname;
    int capacity;
    
    infile >> classname; // get classname
    infile >> capacity; // get capacity
    while (!infile.eof()) // while not end-of-file
    {
        if (classname == "cs111") // if classname is cs111...
            inputFromFile(infile, cs111, classname, capacity); // call to function above to input information into the cs111 object

        // same as above but for different classes
        else if (classname == "cs141")
            inputFromFile(infile, cs141, classname, capacity);

        else if (classname == "cs151")
            inputFromFile(infile, cs151, classname, capacity);

        else if (classname == "cs211")
            inputFromFile(infile, cs211, classname, capacity);

        else if (classname == "cs251")
            inputFromFile(infile, cs251, classname, capacity);
        
        infile >> classname; // keep getting classname
        infile >> capacity; // keep getting capacity
    }
}

//
// a simple cout function that outputs a list of all the commands, except for help
//
void printHelp()
{
    cout << "stats" << endl;
    cout << "list class" << endl;
    cout << "increase class capacity" << endl;
    cout << "enroll class netid" << endl;
    cout << "waitlist class netid priority" << endl;
    cout << "process filename" << endl;
    cout << "output filename" << endl;
    cout << "quit" << endl;
}

//
// a simple print functino that prints the classname and number of enrolled and waitlisted students the class object has
//
void printNAME(ClassReg classreg)
{
    cout << classreg.getName() << ": enrolled=" << classreg.numEnrolled() << ", " << "waitlisted=" << classreg.numWaitlisted() << endl;
}

//
// calls above function for all the given class objects
//
void printInfo(ClassReg cs111, ClassReg cs141, ClassReg cs151, ClassReg cs211, ClassReg cs251)
{
    printNAME(cs111);
    printNAME(cs141);
    printNAME(cs151);
    printNAME(cs211);
    printNAME(cs251);
}

//
// sorts a given array alphabetically
//
void sortedNames(string array[], int cap)
{
     for (int i = 0; i < cap-1; i++)
    {
        int minIndex = i;

        for (int j = i+1; j < cap; j++) // loops so that the smallest elemnts position is assigned to minindex
        {
            if (array[j] < array[minIndex]) // if element at j is less than element at i/minindex, minindex becomes j, otherwise nothing happens
            {
                minIndex = j;
            }
        }
        string temp = array[i]; // temp is assigned to element at i
        array[i] = array[minIndex]; // element at i becomes element at minindex
        array[minIndex] = temp; // element at minindex becomes element previously at i, now temp
    }
}

//
// creates an array of given capacity, and inputs netids of students from the given class object into it, the sorts the list alphabetically
string* Array(ClassReg classname, int cap)
{
    string* sortedEnrolledNames = new string[cap]; // new dynamic array of string
    for (int i = 0; i < cap; i++)
        sortedEnrolledNames[i] = classname.retrieveEnrolledStudent(i); // each array element is assigned a netid from the given class object
    sortedNames(sortedEnrolledNames, cap); // sorts this list by calling above function
    return sortedEnrolledNames; // returns the array
}

//
// outputs classname, capacity, and the students enrolled and waitlisted in it
//
void printList(ClassReg classname)
{
    cout << classname.getName() << endl; // get given class object name
    cout << "Capacity: " << classname.getCapacity() << endl; // get given class object capacity
    
    int cap = classname.numEnrolled(); // cap is assigned to number of enrolled students in the given class object
    cout << "Enrolled (" << classname.numEnrolled() << "): ";
    // the if statements are to check number of netids in the enrolled section of the class object...
    if (cap > 1) // if greater than 1...
    {
        string* names = Array(classname, cap); // creates and sorts the netids into an array...
        // and outputs them
        for (int i = 0; i < cap-1; i++)
            cout << names[i] << " ";
        cout << names[cap-1] << endl;
        delete []names;
    }
    
    else if (cap == 1) // if equal to 1
        cout << classname.retrieveEnrolledStudent(0) << endl; // outputs just that 1 netid
    
    else // else nothing is outputed (except new line)
        cout << endl;

    // same as above but for waitlisted students but no array or sort function
    int cap2 = classname.numWaitlisted();
    cout << "Waitlisted (" << classname.numWaitlisted() << "): ";
    if (cap2 > 1)
    {
        string waitlistID;
        int waitlistPRIO;
        for (int i = 0; i < cap2-1; i++)
        {
            classname.retrieveWaitlistedStudent(i, waitlistID, waitlistPRIO);
            cout << waitlistID << " (" << waitlistPRIO << ") ";
        }
        classname.retrieveWaitlistedStudent(cap2-1, waitlistID, waitlistPRIO);
        cout << waitlistID << " (" << waitlistPRIO << ")" << endl;
    }
    
    else if (cap2 == 1)
    {
        string waitlistID;
        int waitlistPRIO;
        classname.retrieveWaitlistedStudent(0, waitlistID, waitlistPRIO);
        cout << waitlistID << " (" << waitlistPRIO << ")" << endl;
    }
    
    else
        cout << endl;
}
//
// increases the capacity of the given class object, outputs and error if given capacity is less than the current capacity of the class
//
void increaseCap(ClassReg& classname, int capacity)
{
    int x = classname.getCapacity();
    if (x > capacity) // if capacity is less than class object's capacity...
        cout << "**Error, cannot decrease class capacity, ignored..." << endl; // error
    else // else...
    {
        classname.setCapacity(capacity);
        cout << classname.getName() << endl; // the name and...
        cout << "Capacity: " << classname.getCapacity() << endl; // new capacity is outputted
    }
}

//
// enrolls the given netid in the given class object, with some exceptions...
//
void enroll(ClassReg& classname, string netID)
{
    if (classname.searchEnrolled(netID) == -1 && classname.numEnrolled() < classname.getCapacity()) // if given netid does not exist in class object
        // and there is still room for more enrollments in the class
    {
        classname.enrollStudent(netID); // student is enrolled in the class
        int pos = classname.searchWaitlisted(netID); // searches whether that student was in a waitlist before
        if (pos != -1) // if netid exists in class object's waitlist
            classname.removeWaitlistedStudent(pos); // removes the student netid from waitlist
        
        cout << "Student '" << netID << "' enrolled in " << classname.getName() << endl;
    }
    else if (classname.searchEnrolled(netID) == -1 && classname.numEnrolled() == classname.getCapacity()) // if given netid is not in class object's enrollment list
        // and class is full
    {
        if (classname.searchWaitlisted(netID) == -1)  // searches whether that student was in a waitlist before, if netid does not exist in class object's waitlist
        {
            if (classname.numWaitlisted() == 0) // if waitlist is empty
                classname.waitlistStudent(netID, 1); // gives the enrolling student a priority of 1 in the waitlist
            else // else...
            {
                string nope;
                int prio;
                classname.retrieveWaitlistedStudent(classname.numWaitlisted()-1, nope, prio);
                classname.waitlistStudent(netID, prio); // waitlists the student and gives them the same priority as the student at the end of the waitlist
            }
        }
        cout << "Class full, '" << netID << "' waitlisted for " << classname.getName() << endl;
    }
    else if (classname.searchEnrolled(netID) != -1) // if student is already enrolled in class...
        cout << "Student '" << netID << "' enrolled in " << classname.getName() << endl; // does nothing
}

//
// waitlists the students in the given class object
//
void waitlist(ClassReg& classname, int priority, string netID)
{
    if (classname.searchEnrolled(netID) == -1) // if student is not already enrolled...
    {
        if (classname.searchWaitlisted(netID) == -1) // if the students is not waitlisted
        {
            classname.waitlistStudent(netID, priority); // waitlists the student
            cout << "Student '" << netID << "' waitlisted for " << classname.getName() << endl;
        }
        else // else...
        {
            int pos = classname.searchWaitlisted(netID);
            classname.removeWaitlistedStudent(pos); // removes the student from their current position in the priority queue
            classname.waitlistStudent(netID, priority); // and moves them to the given priority inistead
            cout << "Student '" << netID << "' waitlisted for " << classname.getName() << endl;
        }
    }
    else // if student is already enrolled
    {
        cout << "Student '" << netID << "' enrolled in " << classname.getName() << endl; // does nothing
    }
}

//
// outputs information of the given class object into a given output file
//
void outputToFile(ofstream& outfile, ClassReg classname)
{
    outfile << classname.getName() << endl; // writes class name of that class object in the ouput file
    outfile << classname.getCapacity() << endl; // writes capacity of class object in outfile
    if (classname.numEnrolled() > 1) // if there is more than 1 stdent enrolled...
    {
        for (int i = 0; i < classname.numEnrolled()-1; i++)
            outfile << classname.retrieveEnrolledStudent(i) << " ";
        outfile << classname.retrieveEnrolledStudent(classname.numEnrolled()-1) << " #" << endl;
    }
    else if (classname.numEnrolled() == 1) // if only 1 student is enrolled...
        outfile << classname.retrieveEnrolledStudent(classname.numEnrolled()-1) << " #" << endl;
    
    else // else... 
        outfile << "#" << endl; // end of enrolled mark, "#," is outputted insted
    
    // similar to enrollments but for waitlisted students
    if (classname.numWaitlisted() > 1)
    {
        string waitlistID;
        int waitlistPrio;
        for (int i = 0; i < classname.numWaitlisted()-1; i++)
        {
            classname.retrieveWaitlistedStudent(i, waitlistID, waitlistPrio);
            outfile << waitlistID << " " << waitlistPrio << " ";
        }
        classname.retrieveWaitlistedStudent(classname.numWaitlisted()-1, waitlistID, waitlistPrio);
        outfile << waitlistID << " " << waitlistPrio << " #" << endl;
    }
    
    else if (classname.numWaitlisted() == 1)
    {
        string waitlistID;
        int waitlistPrio;
        classname.retrieveWaitlistedStudent(0, waitlistID, waitlistPrio);
        outfile << waitlistID << " " << waitlistPrio << " #" << endl;
    }
    
    else
        outfile << "#" << endl;
}

//
// compilation function for the printList function for each of the class, calls function for each classs depending on the given classname
//
void printCommand(string classname, ClassReg& cs111, ClassReg& cs141, ClassReg& cs151, ClassReg& cs211, ClassReg& cs251)
{
    if (classname == "cs111") // if cs111 inputted...
        printList(cs111); // then prinList for cs111 class object
    // same as above but for other classes
    else if (classname == "cs141")
        printList(cs141);
    else if (classname == "cs151")
        printList(cs151);
    else if (classname == "cs211")
        printList(cs211);
    else if (classname == "cs251")
        printList(cs251);
    else // error if unknown classname is given
        cout << "**Invalid class name, try again..." << endl;
}

//
// same as above but for the increaseCap function
//
void printIncrease(string classname, int capacity, ClassReg& cs111, ClassReg& cs141, ClassReg& cs151, ClassReg& cs211, ClassReg& cs251)
{
    if (classname == "cs111")
        increaseCap(cs111, capacity);
    else if (classname == "cs141")
        increaseCap(cs141, capacity);
    else if (classname == "cs151")
        increaseCap(cs151, capacity);
    else if (classname == "cs211")
        increaseCap(cs211, capacity);
    else if (classname == "cs251")
        increaseCap(cs251, capacity);
    else
        cout << "**Invalid class name, try again..." << endl;
}

//
// same as above but for enroll function
//
void printEnroll(string classname, string netID, ClassReg& cs111, ClassReg& cs141, ClassReg& cs151, ClassReg& cs211, ClassReg& cs251)
{
    if (classname == "cs111")
        enroll(cs111, netID);
    else if (classname == "cs141")
        enroll(cs141, netID);
    else if (classname == "cs151")
        enroll(cs151, netID);
    else if (classname == "cs211")
        enroll(cs211, netID);
    else if (classname == "cs251")
        enroll(cs251, netID);
    else
        cout << "**Invalid class name, try again..." << endl;
}

//
// same as above but for waitlist function
//
void printWaitlist(string classname, int prio, string netID, ClassReg& cs111, ClassReg& cs141, ClassReg& cs151, ClassReg& cs211, ClassReg& cs251)
{
    if (classname == "cs111")
        waitlist(cs111, prio, netID);
    else if (classname == "cs141")
        waitlist(cs141, prio, netID);
    else if (classname == "cs151")
        waitlist(cs151, prio, netID);
    else if (classname == "cs211")
        waitlist(cs211, prio, netID);
    else if (classname == "cs251")
        waitlist(cs251, prio, netID);
    else
        cout << "**Invalid class name, try again..." << endl;
}

//
// same as above but for the outputToFile function, except there are no if statements, also...
void outputTheFile(string outputFile, ClassReg cs111, ClassReg cs141, ClassReg cs151, ClassReg cs211, ClassReg cs251)
{
    ofstream outfile; // assigns outfile
            
    outfile.open(outputFile); // outfile opens file of given name

    // function called for each class object
    outputToFile(outfile, cs111);
    outputToFile(outfile, cs141);
    outputToFile(outfile, cs151);
    outputToFile(outfile, cs211);
    outputToFile(outfile, cs251);

    outfile.close(); // closes the file after everything is done
    
    cout << "Enrollment data output to '" << outputFile << "'" << endl;
}

//
// the main function that compiles all the functions above, processes all the commands from input
//
void processCommands(istream& input, bool promptUser, ClassReg& cs111, ClassReg& cs141, ClassReg& cs151, ClassReg& cs211, ClassReg& cs251)
{
    string command;    
    
    if (promptUser) // user is prompted for input, then true and if statement executes, else skip
    {
        cout << endl;
        cout << "Enter a command (help for more info, quit to stop)>" << endl;
    }
    
    input >> command;
    
    while (command != "quit" && command != "q") // while command is not equal to q or quit, keep looping
    {
        if (command == "help" || command == "h") // if h or help...
            printHelp(); // execute printHelp function
        
        else if (command == "stats" || command == "s") // same as above buut for stats
            printInfo(cs111, cs141, cs151, cs211, cs251);
        
        else if (command == "list" || command == "l") // same as above but for list
        {
            string classname;
            input >> classname;
            
            printCommand(classname, cs111, cs141, cs151, cs211, cs251);
        }
        else if (command == "increase" || command == "i") // same as above but for increase
        {
            string classname;
            input >> classname;
            int capacity;
            input >> capacity;
            
            printIncrease(classname, capacity, cs111, cs141, cs151, cs211, cs251);
        }
        else if (command == "enroll" || command == "e") // same as above but for
        {
            string classname, netID;
            input >> classname;
            input >> netID;
            
            printEnroll(classname, netID, cs111, cs141, cs151, cs211, cs251);
        }
        else if (command == "waitlist" || command == "w") // same as above but for
        {
            string classname, netID;
            input >> classname;
            input >> netID;
            int prio;
            input >> prio;
            
            printWaitlist(classname, prio, netID, cs111, cs141, cs151, cs211, cs251);
        }
        else if (command == "process" || command == "p") // if command is process or p
        {
            string processFile;
            input >> processFile;
            
            ifstream infile2;
            
            infile2.open(processFile); // opens inputted filename
            
            if (!infile2.good())
                cout << "**Unable to open command file '" << processFile << "'" << endl; // if file does not exist or open, error outputted and loop restarts
            else
            {
                cout << "**Processing commands from '" << processFile << "'" << endl;
                processCommands(infile2, false, cs111, cs141, cs151, cs211, cs251); // recursion of this function but with infile for input and false for promptuser
                // therefore only non user prompted inputs/inputs from the file
                cout << "**Done processing '" << processFile << "'" << endl;
            }
        }
        else if (command == "output" || command == "o") // same as above but for output
        {
            string outputFile;
            input >> outputFile;
            
            outputTheFile(outputFile, cs111, cs141, cs151, cs211, cs251);
        }
        else // if invalid command inputted
            cout << "**Invalid command, please try again..." << endl;
        
        if (promptUser) // same as above
        {
            cout << endl;
            cout << "Enter a command (help for more info, quit to stop)>" << endl;
        }
        
        input >> command; // keeps getting input to keep loop going
    }
}

int main()
{
    ClassReg cs111, cs141, cs151, cs211, cs251; // create ClassReg objects
    string filename;
    cout << "**CS Enrollment System**" << endl;
    cout << "Enter enrollments filename>" << endl;
    cin >> filename; // get file with enrollment information from user
    
    ifstream infile;
    
    infile.open(filename); // open the file
    
    if (!infile.good()) // if file not good...
    {
        cout << "**Unable to open command file '" << filename << "'" << endl; // error outputted and
        return 0; // code exits
    }
    
    else // if file good...
        inputClassData(infile, cs111, cs141, cs151, cs211, cs251); // inputClassData function called to input data from file into the class objects
    
    infile.close(); // close file after getting all the information
    
    processCommands(cin, true, cs111, cs141, cs151, cs211, cs251); // process commands function called but with cin for input and true for promptuser
    
    cout << "**Done**" << endl; // outputs done when user enters quit command
       
    return 0; // exits code after
}