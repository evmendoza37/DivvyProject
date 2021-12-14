/* ---------------------------------------------
Program 4: Divvy Data
    Program that quantifies and summarizes Divvy Bike trip data.
    Options available to analyze whole dataset.
    Analyzes patterns and similarities between weekday and a weekend data.

    Course: CS 141, Fall 2021. Tues 9am lab || 3pm lab
    System: Windows using CLion
    Author: Emily Mendoza & Kaustubha Medikundam

    Running the program looks like:

    Analyze Divvy bike ride information using September trip data.
    First select option 1 to read and clean the data.

    Select a menu option:
     1. Select datafile, display rides totals and clean data
     2. Display overall trip information
     3. Display percentage of members vs. casual riders
     4. Display weekday vs weekend usage
     5. Extra Credit: find closest station
     6. Exit
    Your choice -->1
     Select datafile:
     1. Small subset of data with 14 rides to help create your program
     2. Week day vs weekend rides
     3. All September 2021 data (not tested in Zybooks)
    Your selection-->1
     Total # of trips found in datafile: 12
     Total # of trips in clean data: 10
        . . .
---------------------------------------------
*/
#include <iostream>   // For Input and Output
#include <fstream>    // For file input and output
#include <cassert>    // For the assert statement
#include <cctype>     // access to tolower() or toupper() function
#include <vector>     // For vectors
#include <string>     // String operations
#include <algorithm>  // use of vector algorithms
#include <cmath>
#include<sstream>
#include <iomanip>
using namespace std;  // cmath library in C++

//function to convert degrees to radians
long double toRadians(const long double degree)
{
    // defines the constant
    // M_PI as the value of
    // pi accurate to 1e-30
    long double one_deg = (3.14159265358979323846) / 180;
    return (one_deg * degree);
}

//function to calculate the distance between two points using lat and long coordinate
long double distance(long double lat1, long double long1,long double lat2, long double long2){
    // Convert the latitudes
    // and longitudes
    // from degree to radians.
    lat1 = toRadians(lat1);
    long1 = toRadians(long1);
    lat2 = toRadians(lat2);
    long2 = toRadians(long2);

    // Haversine Formula
    long double dlong = long2 - long1;
    long double dlat = lat2 - lat1;

    long double ans = pow(sin(dlat / 2), 2) +
            cos(lat1) * cos(lat2) *
            pow(sin(dlong / 2), 2);

    ans = 2 * asin(sqrt(ans));

    // Radius of Earth in
    // Kilometers, R = 6371
    // Use R = 3956 for miles
    long double R = 3956;

    // Calculate the result
    ans = ans * R;

    return ans;
}

// Read file data from all_divvy_rides_september.csv into a vector
void allfromSept( vector <string> & list){
    // Read in dictionary into dictionary vector
    ifstream toReader;                                                  //create new ifstream object
    toReader.open( "all_divvy_rides_september.csv");                 //open file based on what we need//path chosen based on the input
    assert( toReader.fail() == false );                                // make sure the file opened correctly
    list.clear();                                                      // clear list

    string currentRide;                                                // Store a single input word
    while( toReader.good() ) {                                         // While there is another word to be read
        getline(toReader, currentRide, '\n');
        list.push_back( currentRide);                                  //add to the back of the vector
    }
    toReader.close();                                                  //close file
}

// Read file data from divvyridesampledata.csv into a vector
void allfromFile( vector <string> & list){
    // Read in dictionary into dictionary vector
    ifstream toReader;                                                  //create new ifstream object
    toReader.open( "divvyridesampledata.csv");                       //open file based on what we need//path chosen based on the input
    assert( toReader.fail() == false );                                // make sure the file opened correctly
    list.clear();                                                      // clear list

    string currentRide;                                               // Store a single input word
    while( toReader.good() ) {                                        // While there is another word to be read
        getline(toReader, currentRide, '\n');
        list.push_back( currentRide);                                 //add to the back of the vector
    }
    toReader.close();                                                 //close file
}

// Read file data from weekdayweekend.csv into a vector
void weekfromFile( vector <string> & list){
    // Read in dictionary into dictionary vector
    ifstream toReader;                                                  //create new ifstream object
    toReader.open( "weekdayweekend.csv");
    assert( toReader.fail() == false );                                 // make sure the file opened correctly
    list.clear();                                                       // clear list
    string currentRide;                                                 // Store a single input word
    while( toReader.good() ) {                                          // While there is another word to be read
        getline(toReader, currentRide, '\n');
        list.push_back( currentRide);                                  //add to the back of the vector
    }

    toReader.close();                                                 //close file
}

void cleanupAll(vector<string> &sample, vector<vector<string>> &cleanData){
    // separate by each individual ride
    for (int i = 1; i < sample.size(); i++){
        vector<string> ride;
        stringstream streamride(sample.at(i));

        //while there is data to be taken in in the ride instance
        while(streamride.good()) {
            string data;
            //separate by commas
            getline(streamride, data, ',');             //get first string delimited by comma
            ride.push_back(data);
        }

        bool populated = false;
        int numCorrect = 0;
        //iterate through the vector of data for the current ride and check to make sure that it is populated
        for (int i = 0; i < ride.size(); i++){
            if (ride.at(i) == "\0" ){
                break;
            }
            else {
                numCorrect++;
            }
        }
        if(numCorrect == ride.size()){
            cleanData.push_back(ride);
        }
    }
}

void readData(vector<string> & sample, vector<vector<string>> &clean){

    cout<<"Select datafile: \n 1. Small subset of data with 14 rides to help create your program \n"
          " 2. Week day vs weekend rides \n"
          " 3. All September 2021 data (not tested in Zybooks)"<<endl;
    int option;
    cout<<"Your selection--> ";
    cin>>option;
    if(option == 1){
        allfromFile(sample);
        cleanupAll(sample, clean);
        //subtract two because Zybooks has an extra empty line in their csv file
        cout << "Total # of trips found in datafile: " << sample.size()-2 << endl;
        cout << "Total # of trips in clean data: " << clean.size() << endl;
    }
    else if(option ==2){
        weekfromFile(sample);
        cleanupAll(sample, clean);
        //subtract two because Zybooks has an extra empty line in their csv file
        cout << "Total # of trips found in datafile: " << sample.size()-2 << endl;
        cout << "Total # of trips in clean data: " << clean.size() << endl;
    }
    else if(option ==3){
      allfromSept(sample);
      cleanupAll(sample, clean);
        //subtract two because Zybooks has an extra empty line in their csv file
        cout << "Total # of trips found in datafile: " << sample.size()-2 << endl;
        cout << "Total # of trips in clean data: " << clean.size() << endl;
    }
}

void tripInfo(vector<vector<string>> &clean){
    vector<long double> miles;
    long double totalMiles = 0;
    vector<string> currenttrip;

    //iterate through the filtered list and get the distance from each trip
    for(int i = 0; i < clean.size(); i++){
        //set holder for vector
        currenttrip = clean.at(i);

        //convert string to double
        long double slat = stold(currenttrip.at(6));
        long double slong = stold(currenttrip.at(7));
        long double flat = stold(currenttrip.at(8));
        long double flong = stold(currenttrip.at(9));

        //add distance to the miles list
        miles.push_back(distance(slat,slong,flat,flong));
    }

    //initialize starting index and value to the first trip in the vector
    int index = 0;
    long double greatestDist = miles.at(0);
    long double averageLength = 0;
    //find the greatest distance
    for(int i = 0; i < miles.size(); i++){
        totalMiles = totalMiles + miles.at(i);
        averageLength = averageLength + miles.at(i);
        //reset new distance if greater than current distance, save index in the vector
        if (miles.at(i) > greatestDist){
            greatestDist = miles.at(i);
            index = i;
        }
    }

    averageLength = averageLength / miles.size();
    cout << "   Total # of miles traveled: " << setprecision(0) << fixed<<totalMiles << endl;
    cout << "   Average length of trips in miles: " << setprecision(1) << fixed<<averageLength << endl;
    cout << endl;
    cout << "   Longest trip information below: " << endl;
    cout << "   -------------------------------" << endl;
    currenttrip = clean.at(index);
    cout << "   Trip ID: " << currenttrip.at(0) << endl;
    cout << "   Trip start location: " << currenttrip.at(4) << endl;
    cout << "   Trip end location: " << currenttrip.at(5) << endl;
    cout << "   Trip distance in miles: " << setprecision(1) << fixed << greatestDist << endl;
}//end of tripinfo function

void percentage(vector<vector<string>> &clean){
    double member = 0.0;
    double casual = 0.0;
    vector<string> currentTrip;

    //iterate through all the clean data and count the members and casual drivers
    for (int i = 0; i < clean.size(); i++){
        currentTrip = clean.at(i);

        //get last data position
        int dataPos = currentTrip.size() - 1;
        string status = currentTrip.at(dataPos);

        //if first character C increment casual; if M, increment member
        if(currentTrip.at(dataPos).at(0) == 'c'){
            casual = casual + 1.0;
        }
        if(currentTrip.at(dataPos).at(0) == 'm'){
            member = member + 1.0;
        }
    }

    double total = clean.size();
    //calculate the percentage of each respective rider
    double perctMember = (member/total) * 100.0;
    double perctCasual = (casual/total) * 100.0;
    cout << endl;
    cout << "Casual Rider Percentage: " << setprecision(1) << fixed << perctCasual << "%" << endl;
    cout << "Member Rider Percentage: "<< setprecision(1) << fixed << perctMember << "%" << endl;
}

void countsOfRides(vector<vector<string>> &clean){
    vector <int> hoursOnWeekends;
    vector <int> hoursOnWeekdays;
    vector <string> currentTrip;

    //initialize 24 varibales to be incremented for each hour of weekends or weekdays
    for(int i = 0; i< 24 ; i++){
        hoursOnWeekends.push_back(0);
        hoursOnWeekdays.push_back(0);
    }
    //iterate through the entire
    for(int i = 0; i < clean.size(); i++){
        currentTrip = clean.at(i);
        // go to the index of the day within the data and sort if it is a weekday
        if(currentTrip.at(2).at(2) == '1'|| currentTrip.at(2).at(2) == '2'||currentTrip.at(2).at(2) == '3'){
            //find the index range of the location of the hours
            int start = currentTrip.at(2).find(" ");
            int done = currentTrip.at(2).find(":");
            int numb =  stoi (currentTrip.at(2).substr(start, done-1));
            hoursOnWeekdays.at(numb)++;
        }
        // go to the index of the day within the data and sort if it is a weekend
        if(currentTrip.at(2).at(2) == '4'||currentTrip.at(2).at(2) == '5'){
            //find the index range of the location of the hours
            int start = currentTrip.at(2).find(" ");
            int done = currentTrip.at(2).find(":");
            int numb =  stoi (currentTrip.at(2).substr(start, done-1));
            hoursOnWeekends.at(numb)++;
        }
    }

    //initialize greatest amount of rides
    int greatest = 0;
    //iterate through 24 "hours" (varibales)
    for(int i = 0; i < 24; i++){
        //update greatest to be the greatest number within the array
        if (hoursOnWeekdays.at(i) > greatest){
            greatest = hoursOnWeekdays.at(i);
        }
        if (hoursOnWeekends.at(i) > greatest){
            greatest = hoursOnWeekends.at(i);
        }
    }
    //print out greatest number of rides and table
    cout << "LargestNumberOfRides is: " << greatest << endl;
    cout << "   Rides per hour for weekday and weekend:" << endl;
    for(int i = 0; i < 24; i++){
        cout << "    " << i << ":     " << hoursOnWeekdays.at(i)<<"    "<<hoursOnWeekends.at(i)<<endl;
    }
}//end countsOfRides

//display graph to display the information
void fiftyColumnGraph(vector<vector<string>> &clean){
    vector <int> hoursOnWeekends;
    vector <int> hoursOnWeekdays;
    vector <string> currenttrip;
    //initialize 24 varibales to be incremented for each hour of weekends or weekdays
    for(int i = 0; i< 24 ; i++){
        hoursOnWeekends.push_back(0);
        hoursOnWeekdays.push_back(0);
    }
    //iterate through the entire
    for(int i = 0; i < clean.size(); i++){
        currenttrip = clean.at(i);
        // go to the index of the day within the data and sort if it is a weekday
        if(currenttrip.at(2).at(2) == '1'|| currenttrip.at(2).at(2) == '2' || currenttrip.at(2).at(2) == '3'){
            //find the index range of the location of the hours
            int start = currenttrip.at(2).find(" ");
            int done = currenttrip.at(2).find(":");
            int numb =  stoi (currenttrip.at(2).substr(start, done-1));
            hoursOnWeekdays.at(numb)++;
        }
        // go to the index of the day within the data and sort if it is a weekend
        if(currenttrip.at(2).at(2) == '4'||currenttrip.at(2).at(2) == '5'){
            //find the index range of the location of the hours
            int start = currenttrip.at(2).find(" ");
            int done = currenttrip.at(2).find(":");
            int numb =  stoi (currenttrip.at(2).substr(start, done-1));
            hoursOnWeekends.at(numb)++;
        }
    }

    //initialize greatest amount of rides
    double greatest = 0.0;
    //iterate through 24 "hours" (varibales)
    for(int i = 0; i < 24; i++){
        //update greatest to be the greatest number within the array
        if (hoursOnWeekdays.at(i) > greatest){
            greatest = hoursOnWeekdays.at(i);
        }
        if (hoursOnWeekends.at(i) > greatest){
            greatest = hoursOnWeekends.at(i);
        }
    }
    //display '@' signs and '+' for every 50 people
    for(int i = 0; i < 24; i++){
        cout<<i<<": ";
        //pull in data from the vector and divide by 50
        double at = (hoursOnWeekdays.at(i)/greatest)*50.0;
        //round total through truncating
        int ats = at;
        for(int a = 0 ; a < ats; a++){
            cout<<"@";
        }
        cout<<endl;
        //repeat same process with weekends
        double plus = (hoursOnWeekends.at(i)/greatest)*50;
        int pluses = plus;
        for(int p = 0; p < pluses; p++){
            cout<<"+";
        }
        cout<<endl;
    }
}// end of fiftyColumnGraph

void findClosestStation(vector<vector<string>> &clean){
  vector<long double> miles;
    long double totalMiles = 0;
    vector<string> currenttrip;
    long double flat, flong;

    cout << "Input latitude and longitude of the home: ";
    cin >> flat >> flong;
    cout << endl;
    cout << "You entered: "<< setprecision(1) << fixed << flat << " for latitude and "<< setprecision(1) << fixed << flong << " for longitude" << endl; 

    //iterate through the filtered list and get the distance from each trip
    for(int i = 0; i < clean.size(); i++){
        //set holder for vector
        currenttrip = clean.at(i);

        //convert string to double
        long double slat = stold(currenttrip.at(6));
        long double slong = stold(currenttrip.at(7));

        //add distance to the miles list
        miles.push_back(distance(slat,slong,flat,flong));
    }

    //initalize starting index and value to the first trip in the vector
    int index = 0;
    long double shortestDist = miles.at(0);
    //find the lowest distance
    for(int i = 0; i < miles.size(); i++){
        totalMiles = totalMiles + miles.at(i);

        //reset new distance if lower than current distance, save index in the vector
        if (miles.at(i) < shortestDist){
            shortestDist = miles.at(i);
            index = i;

        }
    }
  currenttrip = clean.at(index);
  //print out information of the shortest trip
  cout << "Closest Divvy station is: " << currenttrip.at(4) << " at " << currenttrip.at(6) << ", "
  << currenttrip.at(7) << ", " << setprecision(1) << fixed << shortestDist << " miles away." << endl;
}

void weekendVsweekday(vector<vector<string>> &clean){

    cout<<"Select type of display: "<<endl;
    cout << " 1. Counts of rides per hour in the day \n 2. Proportional 50 column graph with @ for weekday and + for weekend" << endl;
    int menu;
    cout<<"Your selection-->";
    cin>>menu;
    if(menu == 1){
        countsOfRides(clean);
    }

    else{
        fiftyColumnGraph(clean);
    }
}

int menuChoice(){
    int input = 0;
    cout << endl;
    cout << "Select a menu option: \n 1. Select datafile, display rides totals and clean data \n 2. Display overall trip information \n 3. Display percentage of members vs. casual riders \n 4. Display weekday vs weekend usage \n 5. Extra Credit: find closest station \n 6. Exit" <<endl;
    cout << "Your choice --> ";
    cin >> input;
    return input;
}

int main()
{
    vector<string> sample;
    vector<vector<string>> cleanList;
    vector<vector<string>> DayVEnd;

    bool running = true;
    bool one = false;
    cout << "Analyze Divvy bike ride information using September trip data.\n"
            "First select option 1 to read and clean the data." << endl;

    while(running){

        int menu = menuChoice();

        if (menu == 6){                                      //if user inputs 6, program will exit
            running = false;
            break;
        }
        //load in csv files
        else if (menu == 1){
            one = true;
            readData(sample, cleanList);
        }
        //if files loaded in, other options accessible
        if (one == true){
            //display find longest trip
            if (menu == 2){
                tripInfo(cleanList);
            }
            //display ratio of members to nonmembers
            else if (menu == 3){
                percentage(cleanList);
            }
            //compare weekend and weekday data
            else if (menu == 4){
                weekendVsweekday(cleanList);
            }
            //extra credit option: find closest station
            else if (menu == 5){
            findClosestStation(cleanList);
            }
          
        }

        else {
            cout << "First read in data by selecting menu option 1" << endl;
        }
    }
    return 0;
}